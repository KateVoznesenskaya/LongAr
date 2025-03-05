#include <algorithm>
#include <string>
#include <deque>
#include "iostream"
class LongAr{
    std::deque<long> integer;
    std::deque<long> fractional;
    bool isNeg;
    int sizeinteg;
    int sizefrac;
    public:
    LongAr();
    LongAr(const std::string n, const int& m, const int& k);
    LongAr(const LongAr &n);
    LongAr & operator=(const LongAr &n);
    ~LongAr();

    LongAr operator+(const LongAr &n) const;
    LongAr operator-(const LongAr &n) const;
    //LongAr operator*(const LongAr &n) const;
    //LongAr operator/(const LongAr &n) const;

    bool operator==(const  LongAr &n) const;
    bool operator!=(const  LongAr &n) const;
    bool operator<(const  LongAr &n) const;
    bool operator>(const  LongAr &n) const;

    friend std::ostream &operator<<(std::ostream &s, LongAr &n);

    // LongAr operator""_longnum(long double number);
};