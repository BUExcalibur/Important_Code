#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define nl printf("\n")
 
const int base = 1e9;
struct bigInt {
    deque<int>v;
    bool s=true;
};
void Set(bigInt &a) {
    while(a.v.size()>1&&a.v.back()==0)
        a.v.pop_back();
    if(a.v.size()==1&&a.v[0]==0)
        a.s=true;
}
void Print(bigInt a) {
    Set(a);
    if(a.s==false)
        printf("-");
    printf("%d",(a.v.size()==0)?0:a.v.back());
    for(int i=(a.v.size()-2); i>=0; i--)
        printf("%09d",a.v[i]);
}
bigInt toBigInt(string st) {
    bigInt ans;
    if(st[0]=='-') {
        ans.s=false;
        st.erase(st.begin());
    }
    if(st.size()==0) {
        ans.s=true;
        ans.v.push_back(0);
        return ans;
    }
    while(st.size()%9!=0)
        st='0'+st;
    for(int i=0; i<st.size(); i+=9) {
        int num=0;
        for(int j=i; j<i+9; j++)
            num=(num*10)+(st[j]-'0');
        ans.v.push_front(num);
    }
    Set(ans);
    return ans;
}
bigInt toBigInt(ll x) {
    string s="";
    bool ck=false;
    if(x<0) {
        ck=true;
        x=(-1)*x;
    }
    while(x>0) {
        s=char(x%10+'0')+s;
        x/=10;
    }
    if(ck)
        s='-'+s;
    return toBigInt(s);
}
bigInt toBigInt(int x) {
    return toBigInt((ll)x);
}
bool operator < (bigInt a, bigInt b) {
    if(a.s!=b.s) {
        if(a.s==false) {
            return true;
        } else
            return false;
    }
    if(a.v.size()!=b.v.size())
        return (a.v.size()<b.v.size());
    for(ll i=(a.v.size()-1); i>=0; i--) {
        if(a.v[i]!=b.v[i]) {
            return (a.v[i]<b.v[i]);
        }
    }
    return false;
}
bool operator > (bigInt a, bigInt b) {
    return b<a;
}
bool operator == (bigInt a, bigInt b) {
    return (!(a<b)&&!(b<a));
}
bool operator <= (bigInt a, bigInt b) {
    return (a<b||a==b);
}
bool operator >= (bigInt a, bigInt b) {
    return (b<a||a==b);
}
deque<int> Plus(deque<int> a, deque<int> b) {
    deque<int>ans;
    int carry=0;
    for(int i=0; i<max(a.size(),b.size()); i++) {
        if(i<a.size())
            carry+=a[i];
        if(i<b.size())
            carry+=b[i];
        ans.push_back(carry%base);
        carry/=base;
    }
    if(carry)
        ans.push_back(carry);
    return ans;
}
deque<int> Minus(deque<int> a, deque<int> b) {
    deque<int>ans;
    int carry=0;
    for(int i=0; i<a.size(); i++) {
        carry+=a[i]-(i<b.size()?b[i]:0);
        if(carry<0) {
            ans.push_back(carry+base);
            carry=-1;
        } else {
            ans.push_back(carry);
            carry=0;
        }
    }
    return ans;
}
bigInt operator + (bigInt a, bigInt b) {
    bigInt ans;
    if(a.s==b.s) {
        ans.s=a.s;
        ans.v=Plus(a.v,b.v);
    } else {
        if(a.s==false){
            a.s=true;
            if(a==b){
                ans=toBigInt(0);
            }
            if(a<b){
                ans.s=true;
                ans.v=Minus(b.v,a.v);
            }else{
                ans.s=false;
                ans.v=Minus(a.v,b.v);
            }
        }else{
            b.s=true;
            if(a==b){
                ans=toBigInt(0);
            }
            if(a<b){
                ans.s=false;
                ans.v=Minus(b.v,a.v);
            }else{
                ans.s=true;
                ans.v=Minus(a.v,b.v);
            }
        }
    }
    Set(ans);
    return ans;
}
bigInt operator - (bigInt a, bigInt b) {
    Set(a);
    Set(b);
    bigInt ans;
    if(b.s==true)
        b.s=false;
    else
        b.s=true;
    ans=a+b;
    return ans;
}
bigInt operator * (bigInt a, bigInt b) {
    Set(a);
    Set(b);
    bigInt ans;
    if(a.s==b.s)
        ans.s=true;
    else
        ans.s=false;
    ans.v.assign(a.v.size()+b.v.size(),0);
    for(int i=0; i<a.v.size(); i++) {
        ll carry= 0ll;
        for(int j=0;(j<b.v.size()||carry>0); j++) {
            ll sum=ans.v[i+j]+carry+(ll)a.v[i]*(j<b.v.size()?(ll)b.v[j]:0ll);
            ans.v[i+j]=sum%base;
            carry=sum/base;
        }
    }
    Set(ans);
    return ans;
}
bigInt operator/(bigInt a, bigInt b)
{
    if (b == toBigInt(0))
        return toBigInt(-1);
    if(b>a) return toBigInt(0);
    bigInt ans, cur;
    if(a.s!=b.s)ans.s=false;
    else ans.s=true;
    cur.s=b.s=true;
    for(int i=(a.v.size()-1);i>=0;i--){
        cur.v.push_front(a.v[i]);
        Set(cur);
        int x=0,L=0,R=base;
        while(L<=R){
            int mid=L+(R-L)/2;
            if(b*toBigInt(mid)>cur){
                x=mid;
                R=mid-1;
            }else{
                L=mid+1;
            }
        }
        cur=cur-toBigInt(x-1)*b;
        ans.v.push_front(x-1);
    }
    Set(ans);
    return ans;
}
bigInt Mod(bigInt a,bigInt b) {
    bigInt ans;
 
 
    return ans;
}
bigInt operator % (bigInt a, bigInt b) {
    if(b==toBigInt(0)) {
        return toBigInt(-1);
    }
    bigInt ans;
    ans.s=a.s;
    a.s=b.s=true;
    for(int i=(a.v.size()-1); i>=0; i--) {
        ans.v.push_front(a.v[i]);
        Set(ans);
        int x=0,L=0,R=base;
        while(L<=R) {
            int mid=L+(R-L)/2;
            if(b*toBigInt(mid)>ans) {
                x=mid;
                R=mid-1;
            } else {
                L=mid+1;
            }
        }
        ans=ans-toBigInt(x-1)*b;
    }
    Set(ans);
    return ans;
}
bigInt gcd(bigInt a, bigInt b) {
    while(!(b==toBigInt(0))) {
        bigInt r=a%b;
        a=b;
        b=r;
    }
    Set(a);
    return a;
}
bigInt lcm(bigInt a, bigInt b) {
    bigInt ans=(a/gcd(a,b))*b;
    Set(ans);
    return ans;
}
bigInt sqrt(bigInt a) {
    bigInt x0=a, x1=(a+toBigInt(1))/toBigInt(2);
    while(x1<x0) {
        x0=x1;
        x1=(x1+(a/x1))/toBigInt(2);
    }
    return x0;
}
bigInt pow(bigInt a, bigInt b) {
    if(b==toBigInt(0))
        return toBigInt(1);
    bigInt tmp=pow(a,b/toBigInt(2));
    if(b%toBigInt(2)==toBigInt(0))
        return tmp*tmp;
    return tmp*tmp*a;
}
int log(int n, bigInt a) {
    int ans=0;
    bigInt big_n=toBigInt(n);
    while(a>toBigInt(1)) {
        ans++;
        a=a/big_n;
    }
    return ans;
}
 
int main() {
    bigInt a,b,c,d;
    string p="1024345678987654";
    char q[]="8888";
    ll r=123456787654;
    int s=765432;
    a=toBigInt(p);
    b=toBigInt(q);
    c=toBigInt(r);
    d=toBigInt(s);
    cout<<"a : ";
    Print(a);nl;
    cout<<"b : ";
    Print(b);nl;
    cout<<"c : ";
    Print(c);nl;
    cout<<"d : ";
    Print(d);nl;
    cout<<"Less Operator : a<b : ";
    cout<<(a<b);nl;
    cout<<"Greater Operator : a>b : ";
    cout<<(a>b);nl;
    cout<<"Equal Operator : d==d : ";
    cout<<(d==d);nl;
    cout<<"Less or equal Operator : a<=b : ";
    cout<<(a<=b);nl;
    cout<<"Greater or equal Operator : b>=c : ";
    cout<<(b>=c);nl;
    cout<<"max Operator : max(a,b) : ";
    Print(max(a,b));nl;
    cout<<"min Operator : min(a,b) : ";
    Print(min(a,b));nl;
    cout<<"a+b : ";
    Print(a+b);nl;
    cout<<"a-b : ";
    Print(a-b);nl;
    cout<<"a*b : ";
    Print(a*b);nl;
    cout<<"a/b : ";
    Print(a/b);nl;
    cout<<"a%b : ";
    Print(a%b);nl;
    cout<<"gcd(a,b) : ";
    c=gcd(a,b);
    Print(c);nl;
    cout<<"lcm(a,b) : ";
    d=lcm(a,b);
    Print(d);nl;
    cout<<"sqrt(b) : ";
    Print(sqrt(b));nl;
    cout<<"pow(a,b) : ";
    Print(pow(a,b));nl;
    cout<<"log(100,b) : ";
    cout<<(log(100,b));nl;
    return 0;
}
