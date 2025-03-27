#include <iostream>
#include <cassert>
#include "Expression.hpp"

void test_plus(){
  //Value
  auto left = std::make_shared<Value<double>>(2.0);
  auto right = std::make_shared<Value<double>>(3.0);
  std::map<std::string, double> v;

  BinOp<double> res_val(left, right, BinOp<double>::Operator::plus_);

  assert(res_val.eval(v)==5.0);
  std::cout<<"Test Plus Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=2.0;

  BinOp<double> res_var(left, x, BinOp<double>::Operator::plus_);

  assert(res_var.eval(v)==4.0);
  std::cout<<"Test Plus Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;


  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Plus Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==1.0);
  std::cout<<"Test Diff Plus Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}
void test_minus(){
  //Value
  auto left = std::make_shared<Value<double>>(2.0);
  auto right = std::make_shared<Value<double>>(3.0);
  std::map<std::string, double> v;

  BinOp<double> res_val(left, right, BinOp<double>::Operator::minus_);

  assert(res_val.eval(v)==-1.0);
  std::cout<<"Test Minus Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=2.0;

  BinOp<double> res_var(left, x, BinOp<double>::Operator::minus_);

  assert(res_var.eval(v)==0.0);
  std::cout<<"Test Minus Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;


  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Minus Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==-1.0);
  std::cout<<"Test Diff Minus Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}

void test_mul(){
  //Value
  auto left = std::make_shared<Value<double>>(2.0);
  auto right = std::make_shared<Value<double>>(3.0);
  std::map<std::string, double> v;

  BinOp<double> res_val(left, right, BinOp<double>::Operator::mul_);

  assert(res_val.eval(v)==6.0);
  std::cout<<"Test Plus Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=2.0;

  BinOp<double> res_var(left, x, BinOp<double>::Operator::mul_);

  assert(res_var.eval(v)==4.0);
  std::cout<<"Test Plus Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;


  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Plus Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==2.0);
  std::cout<<"Test Diff Plus Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}

void test_div(){
  //Value
  auto left = std::make_shared<Value<double>>(6.0);
  auto right = std::make_shared<Value<double>>(3.0);
  std::map<std::string, double> v;

  BinOp<double> res_val(left, right, BinOp<double>::Operator::div_);

  assert(res_val.eval(v)==2.0);
  std::cout<<"Test Div Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=2.0;

  BinOp<double> res_var(left, x, BinOp<double>::Operator::div_);

  assert(res_var.eval(v)==3.0);
  std::cout<<"Test Div Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;


  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Div Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==-1.5);
  std::cout<<"Test Diff Div Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}

void test_pow(){
  //Value
  auto left = std::make_shared<Value<double>>(2.0);
  auto right = std::make_shared<Value<double>>(3.0);
  std::map<std::string, double> v;

  BinOp<double> res_val(left, right, BinOp<double>::Operator::pow_);

  assert(res_val.eval(v)==8.0);
  std::cout<<"Test Pow Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=2.0;

  BinOp<double> res_var(x, left, BinOp<double>::Operator::pow_);

  assert(res_var.eval(v)==4.0);
  std::cout<<"Test Pow Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;


  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Pow Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==4.0);
  std::cout<<"Test Diff Pow Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}


void test_cos(){
  //Value
  auto var=std::make_shared<Value<double>>(0);
  std::map<std::string, double> v;

  MonOp<double> res_val(var, MonOp<double>::Function::cos_);
  
  assert(res_val.eval(v)==1.0);
  std::cout<<"Test Cos Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=0.0;

  MonOp<double> res_var(x, MonOp<double>::Function::cos_);

  assert(res_var.eval(v)==1.0);
  std::cout<<"Test Cos Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;
  
  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Cos Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==0.0);
  std::cout<<"Test Diff Cos Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}

void test_sin(){
  //Value
  auto var=std::make_shared<Value<double>>(0);
  std::map<std::string, double> v;

  MonOp<double> res_val(var, MonOp<double>::Function::sin_);
  
  assert(res_val.eval(v)==0.0);
  std::cout<<"Test Sin Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=0.0;

  MonOp<double> res_var(x, MonOp<double>::Function::sin_);

  assert(res_var.eval(v)==0.0);
  std::cout<<"Test Sin Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;
  
  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Sin Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==1.0);
  std::cout<<"Test Diff Sin Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}

void test_ln(){
  //Value
  auto var=std::make_shared<Value<double>>(1);
  std::map<std::string, double> v;

  MonOp<double> res_val(var, MonOp<double>::Function::ln_);
  
  assert(res_val.eval(v)==0.0);
  std::cout<<"Test Ln Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=1.0;

  MonOp<double> res_var(x, MonOp<double>::Function::ln_);

  assert(res_var.eval(v)==0.0);
  std::cout<<"Test Ln Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;
  
  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Ln Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==1.0);
  std::cout<<"Test Diff Ln Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}

void test_exp(){
  //Value
  auto var=std::make_shared<Value<double>>(0);
  std::map<std::string, double> v;

  MonOp<double> res_val(var, MonOp<double>::Function::exp_);
  
  assert(res_val.eval(v)==1.0);
  std::cout<<"Test Exp Value: "<<res_val.tostr()<<"=="<<res_val.eval(v)<<": OK"<<std::endl;

  //Variable
  auto x = std::make_shared<Variable<double>>("x");
  v["x"]=0.0;

  MonOp<double> res_var(x, MonOp<double>::Function::exp_);

  assert(res_var.eval(v)==1.0);
  std::cout<<"Test Exp Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<res_var.tostr()<<"=="<<res_var.eval(v)<<": OK"<<std::endl;
  
  //Diff
  std::string var_name = "x";
  auto df_val=res_val.diff(var_name);
  assert(df_val->eval(v)==0.0);
  std::cout<<"Test Diff Exp Value: "<<df_val->tostr()<<"=="<<df_val->eval(v)<<": OK" << std::endl;
  auto df_var=res_var.diff(var_name);
  assert(df_var->eval(v)==1.0);
  std::cout<<"Test Diff Exp Variable "<<x->tostr()<<"="<<x->eval(v)<<": "<<df_var->tostr()<<"=="<<df_var->eval(v)<<": OK" << std::endl;
}


int main() {
  test_plus();
  test_minus();
  test_mul();
  test_div();
  test_pow();
  test_cos();
  test_sin();
  test_ln();
  test_exp();
}