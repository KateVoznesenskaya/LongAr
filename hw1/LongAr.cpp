#include "LongAr.hpp"

int str_del2(std::string &n){
    int tmp=0;
    for (int i=0; i<n.length(); i++){
        int numb=tmp*10+(n[i]-'0');
        n[i]=numb/2+'0';
        tmp=numb%2;
        }
    if (tmp==0){
        return 0;
    }
    else{
        return 1;
    }
}
int str_mul2(std::string &n){
    int tmp=0;
    for (int i=n.length()-1; i>=0; i--){
        int numb=(n[i]-'0')*2+tmp;
        n[i]=numb%10+'0';
        if (numb>9){
            tmp=1;
        }
        else{
            tmp=0;
        }
    }
    if (tmp>0){
        return 1;
    }
    else{
        return 0;
    }
}
LongAr::LongAr(): isNeg(false), sizeinteg(1), sizefrac(1){
    integer.resize(sizeinteg, 0);
    fractional.resize(sizefrac, 0);
}
LongAr::LongAr(const std::string n, const int& m, const int& k){
    isNeg=false;
    sizeinteg=(m+31)/32;
    sizefrac=(k+31)/32;
    integer.resize(sizeinteg, 0);
    fractional.resize(sizefrac, 0);
    size_t point=n.find('.');
    std::string integerstr;
    std::string fractionalstr;
    if (point==std::string::npos){
        integerstr=n;
        fractionalstr="";
    }
    else{
        if (n[0]=='-'){
            integerstr=n.substr(1, point-1);
            fractionalstr=n.substr(point+1);
            isNeg=true;
        }
        else{
            integerstr=n.substr(0, point);
            fractionalstr=n.substr(point+1);
        }
    }
    for (int i=sizeinteg-1; i>=0; i--){
        for(int j=31; j>=0; j--){
            integer[i]=integer[i]|((str_del2(integerstr)&1)<<j);
        }
    }
    for (int i=0; i<sizefrac; i++){
        for(int j=0; j<32; j++){
            fractional[i]=fractional[i]|((str_mul2(fractionalstr)&1)<<j);
        }
    }
}
LongAr::LongAr(const LongAr &n):
integer(n.integer), fractional(n.fractional), isNeg(n.isNeg), sizeinteg(n.sizeinteg), sizefrac(n.sizefrac){}
LongAr &LongAr::operator=(const LongAr &n){
    this->integer=n.integer;
    this->fractional=n.fractional;
    this->isNeg=n.isNeg;
    this->sizeinteg=n.sizeinteg;
    this->sizefrac=n.sizefrac;
    return *this;
}
LongAr::~LongAr() {}

LongAr LongAr::operator+(const LongAr &n) const{
    LongAr res;
    if (this->isNeg==false && n.isNeg==true){
        res=*this-n;
        return res;
    }
    if (this->isNeg==true && n.isNeg==false){
        res=n-*this;
        return res;
    }
    if (this->isNeg==false && n.isNeg==false){
        res.isNeg=false;
    }
    else if (this->isNeg==true && n.isNeg==true){
        res.isNeg=true;
    }
    res.sizeinteg=std::max(this->sizeinteg, n.sizeinteg);
    res.sizefrac=std::max(this->sizefrac, n.sizefrac);
    res.integer.resize(res.sizeinteg, 0);
    res.fractional.resize(res.sizefrac, 0);
    int tm=0;
    for (int i=res.sizefrac-1; i>=0; i--){
        long a;
        long b;
        if (i>=this->sizefrac){
            a=0;
        }
        else{
            a=this->fractional[i];
        }
        if (i>=n.sizefrac){
            b=0;
        }
        else{
            b=n.fractional[i];
        }
        for(int j=31; j>=0; j--){
            int sum=((a>>j)&1)+((b>>j)&1)+tm;
            if (sum==3){
                res.fractional[i]=res.fractional[i]|(1<<j);
                tm=1;
            }
            else if (sum==2){
                tm=1;
            }
            else if (sum==1){
                res.fractional[i]=res.fractional[i]|(1<<j);
                tm=0;
            }
            else if(tm==0){
                tm=0;
            }
        }
    }
    for (int i=res.sizeinteg-1; i>=0; i--){
        long a;
        long b;
        if (this->sizeinteg>n.sizeinteg){
            a=this->integer[i];
            if (i>=n.sizeinteg){
                b=n.integer[res.sizeinteg-1-(this->sizeinteg-n.sizeinteg)];
            }
            else{
                b=0;
            }
        }
        else if (n.sizeinteg>this->sizeinteg){
            b=n.integer[i];
            if (i>=this->sizeinteg){
                a=this->integer[res.sizeinteg-1-(n.sizeinteg-this->sizeinteg)];
            }
            else{
                a=0;
            }
        }
        else{
            a=this->integer[i];
            b=n.integer[i];
        }
        for(int j=31; j>=0; j--){
            int sum=((a>>j)&1)+((b>>j)&1)+tm;
            if (sum==3){
                res.integer[i]=res.integer[i]|(1<<j);
                tm=1;
            }
            else if (sum==2){
                tm=1;
            }
            else if (sum==1){
                res.integer[i]=res.integer[i]|(1<<j);
                tm=0;
            }
            else if(tm==0){
                tm=0;
            }
        }
    }
    if (tm){
        long lb=1;
        long nlb=0;
        for(int i=0; i<res.sizeinteg; i++){
            nlb=(res.integer[i]>>31)&1;
            res.integer[i]=(res.integer[i]<<1)|lb;
            lb=nlb;
        }
        for(int i=0; i<res.sizefrac; i++){
            nlb=(res.fractional[i]>>31)&1;
            res.fractional[i]=(res.fractional[i]<<1)|lb;
            lb=nlb;
        } 
    }
    return res;
}
LongAr LongAr::operator-(const LongAr &n) const{
    LongAr res;
    if ((this->isNeg==false && n.isNeg==true)||(this->isNeg==true && n.isNeg==false)){
        res=*this+n;
        return res;
    }
    if (this->isNeg==true && n.isNeg==true){
        res=n-*this;
        return res;
    }
    if (*this==n){
        return res;
    }
    if (*this<n){
        res=n-*this;
        res.isNeg=true;
        return res;
    }
    else if (*this>n){
        res.isNeg=false;
    }
    res.sizeinteg=std::max(this->sizeinteg, n.sizeinteg);
    res.sizefrac=std::max(this->sizefrac, n.sizefrac);
    res.integer.resize(res.sizeinteg, 0);
    res.fractional.resize(res.sizefrac, 0);
    int tm=0;
    for (int i=res.sizefrac-1; i>=0; i--){
        long a;
        long b;
        if (i>=this->sizefrac){
            a=0;
        }
        else{
            a=this->fractional[i];
        }
        if (i>=n.sizefrac){
            b=0;
        }
        else{
            b=n.fractional[i];
        }
        for(int j=31; j>=0; j--){
            if (((a>>j)&1)==1 && tm==1){
                if (((b>>j)&1)==0){
                    tm=0;
                }
                else{
                    res.fractional[i]=res.fractional[i]|(1<<j);
                    tm=1;
                }
            }
            else if (((a>>j)&1)==1 && tm==0){
                if (((b>>j)&1)==0){
                    res.fractional[i]=res.fractional[i]|(1<<j);
                    tm=0;
                }
                else{
                    tm=0;
                }
            }
            else if (((a>>j)&1)==0 && tm==1){
                if (((b>>j)&1)==0){
                    res.fractional[i]=res.fractional[i]|(1<<j);
                    tm=1;
                }
                else{
                    tm=1;
                }
            }
            else if (((a>>j)&1)==0 && tm==0){
                if (((b>>j)&1)==0){
                    tm=0;
                }
                else{
                    res.fractional[i]=res.fractional[i]|(1<<j);
                    tm=1;
                }
            }
        }
    }
    for (int i=res.sizeinteg-1; i>=0; i--){
        long a;
        long b;
        if (this->sizeinteg>n.sizeinteg){
            a=this->integer[i];
            if (i>=n.sizeinteg){
                b=n.integer[res.sizeinteg-1-(this->sizeinteg-n.sizeinteg)];
            }
            else{
                b=0;
            }
        }
        else if (n.sizeinteg>this->sizeinteg){
            b=n.integer[i];
            if (i>=this->sizeinteg){
                a=this->integer[res.sizeinteg-1-(n.sizeinteg-this->sizeinteg)];
            }
            else{
                a=0;
            }
        }
        else{
            a=this->integer[i];
            b=n.integer[i];
        }
        for(int j=31; j>=0; j--){
            if (((a>>j)&1)==1 && tm==1){
                if (((b>>j)&1)==0){
                    tm=0;
                }
                else{
                    res.integer[i]=res.integer[i]|(1<<j);
                    tm=1;
                }
            }
            else if (((a>>j)&1)==1 && tm==0){
                if (((b>>j)&1)==0){
                    res.integer[i]=res.integer[i]|(1<<j);
                    tm=0;
                }
                else{
                    tm=0;
                }
            }
            else if (((a>>j)&1)==0 && tm==1){
                if (((b>>j)&1)==0){
                    res.integer[i]=res.integer[i]|(1<<j);
                    tm=1;
                }
                else{
                    tm=1;
                }
            }
            else if (((a>>j)&1)==0 && tm==0){
                if (((b>>j)&1)==0){
                    tm=0;
                }
                else{
                    res.integer[i]=res.integer[i]|(1<<j);
                    tm=1;
                }
            }
        }
    }
    return res;
}
LongAr LongAr::operator*(const LongAr &n) const{
    LongAr res;
    if ((this->isNeg==false && n.isNeg==true)||(this->isNeg==true && n.isNeg==false)){
        res.isNeg=true;
    }
    else{
        res.isNeg=false;
    }
    res.sizeinteg=std::max(this->sizeinteg, n.sizeinteg);
    res.sizefrac=std::max(this->sizefrac, n.sizefrac);
    res.integer.resize(res.sizeinteg, 0);
    res.fractional.resize(res.sizefrac, 0);
    int tm=0;
    bool fl=false;
    for (int i=n.sizefrac-1; i>=0; i--){
        long b;
        b=n.fractional[i];
        for(int j=31; j>=0; j--){
            if (((b>>j)&1)==1){
                fl=true;
                LongAr tmp=*this;
                long nlb=0;
                long lb=0;
                for(int k=0; k<tmp.sizefrac; k++){
                    nlb=(tmp.fractional[k]<<(32-tm));
                    tmp.fractional[k]=(tmp.fractional[k]>>tm)|lb;
                    lb=nlb;
                }
                for(int k=0; k<tmp.sizeinteg; k++){
                    nlb=(tmp.integer[k]<<(32-tm));
                    tmp.integer[k]=(tmp.integer[k]>>tm)|lb;
                    lb=nlb;
                }
                res=res+tmp;
            }
            if (fl==true){
                tm+=1;
            }
        }
    }
    int a=tm;
    for (int i=n.sizeinteg-1; i>=0; i--){
        long b;
        b=n.integer[i];
        for(int j=31; j>=0; j--){
            if (((b>>j)&1)==1){
                LongAr tmp=*this;
                long nlb=0;
                long lb=0;
                for(int k=0; k<tmp.sizefrac; k++){
                    nlb=(tmp.fractional[k]<<(32-tm));
                    tmp.fractional[k]=(tmp.fractional[k]>>tm)|lb;
                    lb=nlb;
                }
                for(int k=0; k<tmp.sizeinteg; k++){
                    nlb=(tmp.integer[k]<<(32-tm));
                    tmp.integer[k]=(tmp.integer[k]>>tm)|lb;
                    lb=nlb;
                }
                res=res+tmp;
            }
            tm+=1;
        }
    }
    long nlb=0;
    long lb=0;
    for(int i=0; i<res.sizeinteg; i++){
            nlb=(res.integer[i]>>(32-a));
            res.integer[i]=(res.integer[i]<<a)|lb;
            lb=nlb;
    }
    for(int i=0; i<res.sizefrac; i++){
            nlb=(res.fractional[i]>>(32-a));
            res.fractional[i]=(res.fractional[i]<<a)|lb;
            lb=nlb;
    } 
    return res;
}
void LongAr::sh(LongAr &b, int t) {
    long long nlb=0;
    long long lb=0;
    for (int k=0; k<t; k++){
    for(int i=0; i<b.sizefrac; i++){
        nlb=(b.fractional[i]&1);
        b.fractional[i]=(b.fractional[i]>>1)|(lb<<31);
        lb=nlb;
    }
    for(int i=0; i<b.sizeinteg; i++){
        nlb=(b.integer[i]&1);
        b.integer[i]=(b.integer[i]>>1)|(lb<<31);
        lb=nlb;
    }
    }

}
LongAr LongAr::operator/(const LongAr &n) const{
    LongAr res;
    if ((this->isNeg==false && n.isNeg==true)||(this->isNeg==true && n.isNeg==false)){
        res.isNeg=true;
    }
    else{
        res.isNeg=false;
    }
    res.sizeinteg=std::max(this->sizeinteg, n.sizeinteg);
    res.sizefrac=std::max(this->sizefrac, n.sizefrac);
    res.integer.resize(res.sizeinteg, 0);
    res.fractional.resize(res.sizefrac, 0);
    LongAr a=*this;
    LongAr b=n;
    a.isNeg=false;
    b.isNeg=false;
    int t=0;
    bool fl=false;
    for (int i=b.sizefrac-1; i>=0; i++){
        for (int j=31; j>=0; j--){
            if (((b.fractional[i]>>j)&1)==1){
                fl=true;
                break;
            }
            t+=1;
        }
        if (fl){
            break;
        }
    }
    t=32*n.sizefrac-t;
    b.sh(b,t);
    a.sh(a,t);
    int ap=0;
    int bp=0;
    fl=false;
    for (int i=0; i<a.sizeinteg; i++){
        for (int j=0; j<32; j++){
            if (((a.integer[i]>>j)&1)==1) {
                ap=i*32+j;
                fl=true;
                break;
            }
        }
        if (fl){
            break;
        }
    }
    fl=false;
    for (int i=0; i<b.sizeinteg; i++){
        for (int j=0; j<32; j++){
            if (((b.integer[i]>>j)&1)==1) {
                bp=i*32+j;
                fl=true;
                break;
            }
        }
        if (fl){
            break;
        }
    }
    int p=bp-ap;
    b.sh(b,p);
    if (a<b){
        long nlb=0;
        long lb=0;
            for(int i=0; i<b.sizeinteg; i++){
                nlb=(b.integer[i]>>31);
                b.integer[i]=(b.integer[i]<<1)|lb;
                lb=nlb;
            }
    }
    fl=false;
    bool fll=false;
    for (int i=0; i<a.sizeinteg; i++){
        for (int j=0; j<32; j++){
            if (((a.integer[i]>>j)&1)==1){
                fll=true;
                a=a-b;
                if (a.isNeg==true){
                fl=true;
                break;}
            res.integer[i]=res.integer[i]|(1<<j);
            }
            if (fll){
                long nlb=0;
                long lb=0;
                for(int i=0; i<b.sizeinteg; i++){
                    nlb=(b.integer[i]>>31)&1;
                    if (nlb){
                    fl=true;
                    break;
                }
                b.integer[i]=(b.integer[i]<<1)|lb;
                    lb=nlb;
            }
            }
        }
        if (fl){
            break;
        }
    }
    long nlb=0;
    long lb=0;
    for (int k=0; k<31-bp; k++){
        for(int i=0; i<res.sizeinteg; i++){
            nlb=(res.integer[i]>>31);
            res.integer[i]=(res.integer[i]<<1)|lb;
            lb=nlb;
        }
    }
    fl=false;
    for (int i=0; i<a.sizefrac; i++){
        for (int j=0; j<32; j++){
        
            if (((a.fractional[i]>>j)&1)==1){
                a=a-b;
                if (a.isNeg==true){
                fl=true;
                break;
            }
                res.fractional[i]=res.fractional[i]|(1<<j);
            }
            long nlb=0;
            long lb=0;
            for(int i=0; i<b.sizefrac; i++){
                nlb=(a.fractional[i]>>31);
                b.fractional[i]=(a.fractional[i]<<1)|lb;
                lb=nlb;
            }
            if (lb){
                fl=true;
                break;
            }
        }
        if (fl){
            break;
        }
    }
    return res;
}
bool LongAr::operator==(const  LongAr &n) const{
    if (this->isNeg!=n.isNeg){
        return false;
    }
    if (this->sizeinteg>n.sizeinteg){
        int s=this->sizeinteg-n.sizeinteg;
        for (int i=0; i<s; i++){
            if (this->integer[i]!=0){
                return false;
            }
        }
        for (int i=0; i<n.sizeinteg; i++){
            if (n.integer[i]!=this->integer[i+s]){
                return false; 
            }
        }
    }
    if (this->sizeinteg<n.sizeinteg){
        int s=n.sizeinteg-this->sizeinteg;
        for (int i=0; i<s; i++){
            if (n.integer[i]!=0){
                return false;
            }
        }
        for (int i=0; i<this->sizeinteg; i++){
            if (n.integer[i+s]!=this->integer[i]){
                return false;
            }
        }
    }
    if (this->sizeinteg==n.sizeinteg){
        for (int i=0; i<n.sizeinteg; i++){
            if (n.integer[i]!=this->integer[i]){
                return false;
            }
        }
    }
    long a=0;
    long b=0;
    int ms=std::max(this->sizefrac, n.sizefrac);
    for (int l=0; l<ms; l++){
        if (l>=n.sizefrac){
            b=0;
        }
        else{
            b=n.fractional[l];
        }
        if (l>=this->sizefrac){
            a=0;
        }
        else{
            a=this->fractional[l];
        }
        if (a!=b){
            return false;
        }
    }
    return true;
}
bool LongAr::operator!=(const  LongAr &n) const{
    if (*this==n){
        return false;
    }
    return true;
}
bool LongAr::operator>(const  LongAr &n) const{
    if (this->isNeg==false && n.isNeg==true){
        return true;
    }
    if (this->isNeg==true && n.isNeg==false){
        return false;
    }
    if (*this==n){
        return false;
    }
    if (this->isNeg==false && n.isNeg==false){
        if (this->sizeinteg>n.sizeinteg){
            int s=this->sizeinteg-n.sizeinteg;
            for (int i=0; i<s; i++){
                if (this->integer[i]!=0){
                    return true;
                }
            }
            for (int i=0; i<n.sizeinteg; i++){
                for (int j=0; j<32; j++){
                    if (((n.integer[i]>>j)&1)>((this->integer[i+s]>>j)&1)){
                        return false;
                    }
                    if (((n.integer[i]>>j)&1)<((this->integer[i+s]>>j)&1)){
                        return true;
                    }
                }
            }
        }
        if (this->sizeinteg<n.sizeinteg){
            int s=n.sizeinteg-this->sizeinteg;
            for (int i=0; i<s; i++){
                if (n.integer[i]!=0){
                    return false;
                }
            }
            for (int i=0; i<this->sizeinteg; i++){
                for (int j=0; j<32; j++){
                    if (((n.integer[i+s]>>j)&1)>((this->integer[i]>>j)&1)){
                        return false;
                    }
                    if (((n.integer[i+s]>>j)&1)<((this->integer[i]>>j)&1)){
                        return true;
                    }
                }
            }
        }
        if (this->sizeinteg==n.sizeinteg){
            for (int i=0; i<n.sizeinteg; i++){
                for (int j=0; j<32; j++){
                    if (((n.integer[i]>>j)&1)>((this->integer[i]>>j)&1)){
                        return false;
                    }
                    if (((n.integer[i]>>j)&1)<((this->integer[i]>>j)&1)){
                        return true;
                    }
                }
            }
        }
        long a=0;
        long b=0;
        int ms=std::max(this->sizefrac, n.sizefrac);
        for (int l=0; l<ms; l++){
            if (l>=n.sizefrac){
                b=0;
            }
            else{
                b=n.fractional[l];
            }
            if (l>=this->sizefrac){
                a=0;
            }
            else{
                a=this->fractional[l];
            }
            for (int k=0; k<32; k++){
                if (((b>>k)&1)>((a>>k)&1)){
                    return false;
                }
                if (((b>>k)&1)<((a>>k)&1)){
                    return true;
                }
            }
        }
    }
    else if (this->isNeg==true && n.isNeg==true){
        if (this->sizeinteg>n.sizeinteg){
            int s=this->sizeinteg-n.sizeinteg;
            for (int i=0; i<s; i++){
                if (this->integer[i]!=0){
                    return false;
                }
            }
            for (int i=0; i<n.sizeinteg; i++){
                for (int j=0; j<32; j++){
                    if (((n.integer[i]>>j)&1)<((this->integer[i+s]>>j)&1)){
                        return false;
                    }
                    if (((n.integer[i]>>j)&1)>((this->integer[i+s]>>j)&1)){
                        return true;
                    }
                }
            }
        }
        if (this->sizeinteg<n.sizeinteg){
            int s=n.sizeinteg-this->sizeinteg;
            for (int i=0; i<s; i++){
                if (n.integer[i]!=0){
                    return true;
                }
            }
            for (int i=0; i<this->sizeinteg; i++){
                for (int j=0; j<32; j++){
                    if (((n.integer[i+s]>>j)&1)<((this->integer[i]>>j)&1)){
                        return false;
                    }
                    if (((n.integer[i+s]>>j)&1)>((this->integer[i]>>j)&1)){
                        return true;
                    }
                }
            }
        }
        if (this->sizeinteg==n.sizeinteg){
            for (int i=0; i<n.sizeinteg; i++){
                for (int j=0; j<32; j++){
                    if (((n.integer[i]>>j)&1)<((this->integer[i]>>j)&1)){
                        return false;
                    }
                    if (((n.integer[i]>>j)&1)>((this->integer[i]>>j)&1)){
                        return true;
                    }
                }
            }
        }
        long a=0;
        long b=0;
        int ms=std::max(this->sizefrac, n.sizefrac);
        for (int l=0; l<ms; l++){
            if (l>=n.sizefrac){
                b=0;
            }
            else{
                b=n.fractional[l];
            }
            if (l>=this->sizefrac){
                a=0;
            }
            else{
                a=this->fractional[l];
            }
            for (int k=0; k<32; k++){
                if (((b>>k)&1)<((a>>k)&1)){
                    return false;
                }
                if (((b>>k)&1)>((a>>k)&1)){
                    return true;
                }
            }
        }
    }
    return true;
}
bool LongAr::operator<(const  LongAr &n) const{
    if (*this==n || *this>n){
        return false;
    }
    return true;
}
std::ostream &operator<<(std::ostream &s, LongAr &n){
    if (n.isNeg){
        s<<'-';
    }
    for (int i=0; i<n.sizeinteg; i++){
        for (int j=0; j<32; j++){
            s<<((n.integer[i]>>j)&1);
        }
    }
    s<<'.';
    for (int i=0; i<n.sizefrac; i++){
        for (int j=0; j<32; j++){
            s<<((n.fractional[i]>>j)&1);
        }
    }
    return s;
}
LongAr operator ""_longnum(long double number){
    std::string s=std::to_string(number);
    return LongAr(s, 1, 1);
}
