#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <cmath>
template <typename Tvalue>
class Expression{
    
    public:
    virtual ~Expression()=default;
    
    virtual std::string tostr()=0;
    virtual Tvalue eval(std::map<std::string, Tvalue> &n)=0;
    virtual std::shared_ptr<Expression> diff(std::string &n)=0;

};

template <typename Tvalue>
class Value : public Expression<Tvalue>
{
    Tvalue value;
    public:
    Value(Tvalue value);
    Value(const Value &)=default;
    Value & operator=(const Value &)=default;
    Value(Value &&)=default;
    Value & operator=(Value &&)=default;
    ~Value() override=default;
    
    std::string tostr() override;
    Tvalue eval(std::map<std::string, Tvalue> &n) override;
    std::shared_ptr<Expression<Tvalue>> diff(std::string &n) override;

};

template <typename Tvalue>
class Variable : public Expression<Tvalue>
{
    std::string name;
    public:
    Variable(std::string name);
    Variable(const Variable &)=default;
    Variable & operator=(const Variable &)=default;
    Variable(Variable &&)=default;
    Variable & operator=(Variable &&)=default;
    ~Variable() override=default;

    std::string tostr() override;
    Tvalue eval(std::map<std::string, Tvalue> &n) override;
    std::shared_ptr<Expression<Tvalue>> diff(std::string &n) override;

};
template <typename Tvalue>
class BinOp: public Expression<Tvalue>
{
    public:
    enum class Operator{
        plus_, minus_, div_, mul_, pow_
    };

    BinOp (std::shared_ptr<Expression<Tvalue>> left, std::shared_ptr<Expression<Tvalue>> right, Operator op);

    std::string tostr() override;
    Tvalue eval(std::map<std::string, Tvalue> &n) override;
    std::shared_ptr<Expression<Tvalue>> diff(std::string &n) override;
    public:
    std::shared_ptr<Expression<Tvalue>> left;
    std::shared_ptr<Expression<Tvalue>> right;
    Operator op;

};
template <typename Tvalue>
class MonOp: public Expression<Tvalue>
{
    public:
    enum class Function{
        sin_, cos_, ln_, exp_
    };

    MonOp (std::shared_ptr<Expression<Tvalue>> var, Function fun);

    std::string tostr() override;
    Tvalue eval(std::map<std::string, Tvalue> &n) override;
    std::shared_ptr<Expression<Tvalue>> diff(std::string &n) override;
    public:
    std::shared_ptr<Expression<Tvalue>> var;
    Function fun;
};

//Value

template <typename Tvalue>
Value<Tvalue>::Value(Tvalue value): value(value) {}

template <typename Tvalue>
std::string Value<Tvalue>::tostr() {
    std::stringstream s;
    s<<value;
    return s.str();
}

template <typename Tvalue>
Tvalue Value<Tvalue>::eval(std::map<std::string, Tvalue> &n){
    return value;
}

template <typename Tvalue>
std::shared_ptr<Expression<Tvalue>> Value<Tvalue>::diff(std::string &n){
    return std::make_shared<Value<Tvalue>>(Value<Tvalue>(0));
}

//Variable

template <typename Tvalue>
Variable<Tvalue>::Variable(std::string name): name(name) {}

template <typename Tvalue>
std::string Variable<Tvalue>::tostr() {
    return name;
}

template <typename Tvalue>
Tvalue Variable<Tvalue>::eval(std::map<std::string, Tvalue> &n){
    return n[name];
}

template <typename Tvalue>
std::shared_ptr<Expression<Tvalue>> Variable<Tvalue>::diff(std::string &n){
    if (n==name){
        return std::make_shared<Value<Tvalue>>(1);
    }
    else{
        return std::make_shared<Value<Tvalue>>(0);
    }
}

//BinOp

template <typename Tvalue>
BinOp<Tvalue>::BinOp(std::shared_ptr<Expression<Tvalue>> left, std::shared_ptr<Expression<Tvalue>> right, Operator op): left(left), right(right), op(op){}

template <typename Tvalue>
std::string BinOp<Tvalue>::tostr() {
    std::string tm;
    switch (op)
    {
    case Operator::plus_: tm="+";
        break;
    case Operator::minus_: tm="-";
        break;
    case Operator::mul_: tm="*";
        break;
    case Operator::div_: tm="/";
        break;
    case Operator::pow_: tm="^";
        break;
    default:
        break;
    }
    return "("+left->tostr()+" "+tm+" "+right->tostr()+")";
}

template <typename Tvalue>
Tvalue BinOp<Tvalue>::eval(std::map<std::string, Tvalue> &n){
    Tvalue leftval = left->eval(n);
    Tvalue rightval=right->eval(n);
    switch (op)
    {
    case Operator::plus_:
        return leftval+rightval;
    case Operator::minus_:
        return leftval-rightval;
    case Operator::mul_:{
        if (leftval==0  || rightval==0){
            return 0;
        }
        return leftval*rightval;};
    case Operator::div_:
        return leftval/rightval;
    case Operator::pow_:
        return pow(leftval, rightval);
    default:
        return 0;
    }
}

template <typename Tvalue>
std::shared_ptr<Expression<Tvalue>> BinOp<Tvalue>::diff(std::string &n){
    auto leftdf=left->diff(n);
    auto rightdf=right->diff(n);
    switch (op)
    {
    case Operator::plus_:
        return std::make_shared<BinOp<Tvalue>>(leftdf, rightdf, BinOp<Tvalue>::Operator::plus_);
    case Operator::minus_:
        return std::make_shared<BinOp<Tvalue>>(leftdf, rightdf, BinOp<Tvalue>::Operator::minus_);
    case Operator::mul_:
        return std::make_shared<BinOp<Tvalue>>(std::make_shared<BinOp<Tvalue>>(leftdf, right, BinOp<Tvalue>::Operator::mul_), std::make_shared<BinOp<Tvalue>>(left, rightdf, BinOp<Tvalue>::Operator::mul_), BinOp<Tvalue>::Operator::plus_);
    case Operator::div_:
        return std::make_shared<BinOp<Tvalue>>(std::make_shared<BinOp<Tvalue>>(std::make_shared<BinOp<Tvalue>>(leftdf, right, BinOp<Tvalue>::Operator::mul_), std::make_shared<BinOp<Tvalue>>(left, rightdf, BinOp<Tvalue>::Operator::mul_), BinOp<Tvalue>::Operator::minus_), std::make_shared<BinOp<Tvalue>>(right, right, BinOp<Tvalue>::Operator::mul_), BinOp<Tvalue>::Operator::div_);
    case Operator::pow_:{
        // (u^v)' = v * u^(v-1) * u' + ln(u) * u^v * v'
        auto a2=std::make_shared<BinOp<Tvalue>>(left, std::make_shared<BinOp<Tvalue>>(right, std::make_shared<Value<Tvalue>>(1.0), BinOp<Tvalue>::Operator::minus_), BinOp<Tvalue>::Operator::pow_);
        auto a3=std::make_shared<BinOp<Tvalue>>(right, a2, BinOp<Tvalue>::Operator::mul_);
        auto a=std::make_shared<BinOp<Tvalue>>(a3, leftdf, BinOp<Tvalue>::Operator::mul_);
        auto b1=std::make_shared<MonOp<Tvalue>>(left, MonOp<Tvalue>::Function::ln_);
        auto b2=std::make_shared<BinOp<Tvalue>>(left, right, BinOp<Tvalue>::Operator::pow_);
        auto b3=std::make_shared<BinOp<Tvalue>>(b1, b2, BinOp<Tvalue>::Operator::mul_);
        auto b=std::make_shared<BinOp<Tvalue>>(b3, rightdf, BinOp<Tvalue>::Operator::mul_);
        return std::make_shared<BinOp<Tvalue>>(a, b, BinOp<Tvalue>::Operator::plus_);};
    default:
        return nullptr;
    }
}

//MonOp

template <typename Tvalue>
MonOp<Tvalue>::MonOp(std::shared_ptr<Expression<Tvalue>> var, Function fun){
    this->var=var;
    this->fun=fun;
}

template <typename Tvalue>
std::string MonOp<Tvalue>::tostr() {
    std::string tm;
    switch (fun)
    {
    case Function::cos_: tm="cos";
        break;
    case Function::sin_: tm="sin";
        break;
    case Function::ln_: tm="ln";
        break;
    case Function::exp_: tm="exp";
        break;
    default:
        break;
    }
    return tm+"("+var->tostr()+")";
}

template <typename Tvalue>
Tvalue MonOp<Tvalue>::eval(std::map<std::string, Tvalue> &n){
    Tvalue val = var->eval(n);
    switch (fun)
    {
    case Function::cos_:
        return std::cos(val);
    case Function::sin_:
    return std::sin(val);
    case Function::ln_:
    return std::log(val);
    case Function::exp_:
    return std::exp(val);
    default:
        return 0;
    }
}

template <typename Tvalue>
std::shared_ptr<Expression<Tvalue>> MonOp<Tvalue>::diff(std::string &n){
    auto vardf=var->diff(n);
    switch (fun)
    {
    case Function::cos_:{
        auto minsin=std::make_shared<BinOp<Tvalue>>(std::make_shared<Value<Tvalue>>(Value<Tvalue>(Tvalue(-1.0))), std::make_shared<MonOp<Tvalue>>(var, MonOp<Tvalue>::Function::sin_), BinOp<Tvalue>::Operator::mul_);
        return std::make_shared<BinOp<Tvalue>>(minsin, vardf, BinOp<Tvalue>::Operator::mul_);};
    case Function::sin_:
        return std::make_shared<BinOp<Tvalue>>(std::make_shared<MonOp<Tvalue>>(var, MonOp<Tvalue>::Function::cos_), vardf, BinOp<Tvalue>::Operator::mul_);
    case Function::ln_:
        return std::make_shared<BinOp<Tvalue>>(vardf, var, BinOp<Tvalue>::Operator::div_);
    case Function::exp_:
        return std::make_shared<BinOp<Tvalue>>(vardf, std::make_shared<MonOp<Tvalue>>(MonOp<Tvalue>(var, MonOp<Tvalue>::Function::exp_)), BinOp<Tvalue>::Operator::mul_);
    default:
        return nullptr;
    }
}