//
//  mathLib.hpp
//  mathLibrary
//
//  Created by Amit Singh on 18/01/18.
//  Copyright © 2018 Amit Singh. All rights reserved.
//

#ifndef mathLib_hpp
#define mathLib_hpp

#include <stdio.h>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <set>
#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#define PI 3.141592653589793238462643

namespace math_lib {

 
    
//-----------------------------------------DIGITS------------------------------------------------------//
    

    template <typename T>
    std::vector<int> numberToDigit(const T n){
        std::string str = std::to_string(n);
        unsigned long size = str.size();
        auto it = str.find('.');
        if(it!=std::string::npos){
            str.erase(it,it-2);
            size--;
            
        }
        std::vector<int> v(size);
        for(int i = 0;i<size;i++){
            try{ v.at(i)=stoi(str.substr(i,1));}
            catch(...){}
            
        }
        int flag = 0;
        for (int i = static_cast<int>(v.size())-1; i>=0; i--) {
            if(v[i]!=0)
                break;
            flag = i;
        }
        
        v.erase(v.begin()+flag);
        
        return v;
        
        
    }
    
 //-----------------------------------------DETERMINANT------------------------------------------------------//
    
   template<typename T>
    T determinant(std::vector<std::vector<T>> &v){
        
        if(v.size()!=v[0].size())
           throw std::string("MATRIX MUST SQUARE MATRIC!");
        
        if(v.size()==2){
            
            return (v[0][0]*v[1][1]-v[0][1]*v[1][0]);
        }
        T deter = 0;
       
        
        std::vector<std::vector<T>> vNew(v.size()-1,std::vector<T> (v.size()-1));
        int m = 0,n = 0,h=0;
        for (; h<v.size(); h++) {
            m=0;
            for(int i = 0; i<v.size();i++){
                n = 0;
                for (int j = 0; j<v.size(); j++) {
                    if(i!=0&&j!=h){
                        vNew[m][n] = v[i][j];
                        n++;
                    }
                    if(n==vNew.size()){
                        n=0;
                        m++;
                    }
                }
                
                if(n==vNew.size())
                    m=0;
                
            }
            
            deter += (static_cast<T>(std::pow(-1,h))*v[0][h]*determinant<T>(vNew));
        }
        
        
        return deter;
    }
    
    
//-----------------------------------------GCD------------------------------------------------------//
    
    template <typename T = unsigned int>
    unsigned int gcd(unsigned int x,unsigned int y){
        if(x==0)
            return y;
        else
            return gcd(y%x,x);
    }
    

//-----------------------------------------LCM------------------------------------------------------//
    
    template <typename T = unsigned int>
    unsigned int lcm(unsigned int x,unsigned int y){
        return (x*y)/gcd(x,y);
    }
    
//-----------------------------------------PRIME------------------------------------------------------//
    template <typename T = uint64_t>
    uint64_t power(uint64_t a, uint64_t n,uint64_t p){
        uint64_t res = 1;
        a = a % p;
        
        while (n > 0) {
            if(n & 1)
                res = (res * a) % p;
            n = n >> 1;
            a = (a * a) % p;
        }
        return res;
    }
    
    template <typename T = uint64_t>
    bool isPrime(uint64_t n , uint64_t k =3){
        
        if(n <= 1 || n == 4) return false;
        if(n <= 3) return true;
        
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        
        std::default_random_engine rand(static_cast<unsigned int>(seed));
        
        std::poisson_distribution<int> distribution(4.1);
        
        while (k>0) {
            
            int randNumber;
            
            while (true) {
                randNumber = distribution(rand);
                if(randNumber>=0&&randNumber<(n-4))
                    break;
            }
            
            
            int a = 2 + randNumber;
            
            if(power(a, n-1, n)!=1)
                return false;
            k--;
            
        }
        
        return true;
    }

//-------------------------------------------VECTORPRINT----------------------------------------------------//
    
    template <typename T = std::vector<std::string>>
    void print(T y){
        for(auto x : y){
            std::cout<<x<<std::endl;
        }
    }
    
//----------------------------------------ExpressionExtractor----------------------------------------------------//

    template<typename T = char>
    std::string charOperatorToString(char c){
        switch (c) {
            case '+':
                return std::string("+");
                break;
            case '*':
                return std::string("*");
                break;
            case '/':
                return std::string("/");
                break;
            case '-':
                return std::string("-");
                break;
                
            default:
                throw std::string("Operator Not Found!");
                break;
        }
    }
    
    template <typename T = std::string>
    void utiliy(std::string &expression,std::vector<T> &v,const int i,std::set<char> &oper,int j = 3){
        if(i!=expression.length()-1){
                char c = expression.at(i+1);
                //std::cout<<i<<std::endl;
            if(c=='^'){
                c = expression.at(i+j);}
            
                if(oper.end() == oper.find(c))
                    v.push_back("*");
                else{
                    v.push_back(charOperatorToString(c));
            }
        }
       
    }

    template <typename T = std::string>
    std::vector<std::string> expressionExtractorHelper(std::string expression){
        std::string ex;
        std::set<char> oper = {'+','-','*','/'};
        std::vector<std::string> v;
        std::cout<<expression<<'\n';
        for (int i=0; i<expression.length(); i++) {
             ex += expression.substr(i,1);
            char c = ex.at(0);
            if(oper.end()!=oper.find(c)){
                ex.clear();
                
            }
            
            //------------number---------//
            if((expression.at(i)>='1'&&expression.at(i)<='9')){
                for (int j = i; expression.at(j)<'1'&&expression.at(j)>'9'; j++) {
                    ex+=expression.substr(j,1);
                    
                }
                v.push_back(ex);
                utiliy(expression, v, i, oper);
                ex.clear();
            }
            
            //-----------x-----------//
            if(ex =="x"){
                if(expression.at(i+1)=='^'){
                    char c = expression.at(i+1);
                    int j;
                    for (j = i+1; oper.find(c)!=oper.end(); j++) {
                        c =expression.at(j);
                    }
                    ex+=expression.substr(i+1,expression.length()-j-2);
                    v.push_back(ex);
                    utiliy(expression, v, i, oper,static_cast<int>(expression.length()-j-1));
                    i+=expression.length()-j-1;
                    ex.clear();
                }
                else{
                    v.push_back(ex);
                    utiliy(expression, v, i, oper);
                    //std::cout<<i<<std::endl;
                    ex.clear();
                }
            }
            
            
        }
              print(v);
              return v;
    }
  
    
 //-------------------------------------------matrix inverse----------------------------------------------------//
//
//    template <typename T>
//    std::vector<std::vector<T>> mCoeffHelper(std::vector<std::vector<T>> &v){
//
//        std::vector<std::vector<T>> mCoeff(v.size(),std::vector<T>(v.size()));
//        std::vector<std::vector<T>> vNew(v.size()-1,std::vector<T> (v.size()-1));
//        int m = 0,n = 0,h=0;
//        for(int k = 0;k<v.size();k++){
//            for (; h<v.size(); h++) {
//                m=0;
//                for(int i = 0; i<v.size();i++){
//                    n = 0;
//                    for (int j = 0; j<v.size(); j++) {
//                        if(i!=0&&j!=h){
//                            vNew[m][n] = v[i][j];
//                            n++;
//                        }
//                        if(n==vNew.size()){
//                            n=0;
//                            m++;
//                        }
//                    }
//
//                    if(n==vNew.size())
//                        m=0;
//
//                }
//
//                mCoeff[k][h]= (static_cast<T>(std::pow(-1,h))*determinant<T>(vNew));
//            }
//     }
//        return mCoeff;
//
//    }
//
//    template <typename T>
//    std::vector<std::vector<T>> multiply(std::vector<std::vector<T>> &v){
//
//        int z = determinant<T>(v);
//        for(auto &x : v){
//            for(auto &y : x){
//                y/=z;
//            }
//        }
//        return v;
//    }
//
//
//    template <typename T>
//    std::vector<std::vector<T>> matrixInverse(std::vector<std::vector<T>> &v){
//
//        if(v.size()!=v[0].size())
//            throw std::string("MATRIX MUST SQUARE MATRIC!");
//
//        if(determinant(v)==0)
//            throw std::string("INVERSE DOES NOT EXIST!");
//
//        if(v.size()==2){
//            std::swap(v[0][0], v[1][1]);
//            v[0][1]=(-1)*v[0][1];
//            v[1][0]=(-1)*v[1][0];
//            v = multiply<T>(v);
//            return v;
//
//        }
//
//
//        std::vector<std::vector<T>> mCoeff(v.size(),std::vector<T>(v.size()));
//
//        mCoeff = mCoeffHelper<T>(v);
//
//
//        return v;
//    }
//-------------------------------------------RepeatRemover----------------------------------------------------//
    
    template <typename T = int>
    void repeatRemover(std::vector<T> &v){
        
        if(v.size()<10000){
            std::sort(v.begin(),v.end());
            v.erase(std::unique(v.begin(), v.end()), v.end());
           return;
        }
       
        std::set<T> set;
        for(auto x : v){
            set.emplace(x);
        }
        v.clear();
        v.assign(set.begin(),set.end());
        
    }
    
//------------------------------------------PrimeInGivenRange----------------------------------------------------//
    template <typename T = int>
    std::vector<int> primeInRange(const int &lower,const int &higher){
        
        if(lower==0){
            throw std::string("LOWER LIMIT CANNOT BE ZERO");
        }
        else if(lower>higher){
            throw std::string("LOWER LIMIT CANNOT BE GREATER THAN HIGHER LIMIT");
        }
        
        std::vector<int> v;
        
        for (int i = lower; i <= higher ; i++) {
            if(isPrime(i))
                v.emplace_back(i);
        }
        return v;
    }
//---------------------------------------PERMUATION&COMBINATION-------------------------------------------------//
    
    template <typename T = int>
   const int permutation(const int n){
       
       if(n==0)
           return 1;
       std::stringstream ss;
       
       int p=1;
            for (int i = n; i>=1; i--) {
                p*=i;
            }
       return p;
        
    }
    
    template <typename T = int>
    int combination(const int &n , const int &r){
        
        if(n<0)
            throw std::string("n SHOULD BE POSTIVE NUMBER!");
        if(n==0&&r!=0)
            throw std::string("ERROR! r=0 or n >= r ");
        if(n<r)
            throw std::string(" n SHOULD BE GREATER THAN OR EQUAL TO r ");
        
        int d =permutation(n-r);
        int n1 = permutation(n);
        int r1 = permutation(r);
        return n1/(d*r1);
        
    }

//---------------------------------------CHARTONUMBER-------------------------------------------------//
    
    template <typename T = int>
    int charToNumber(char c){
        switch (c) {
            case '0':
                return 0;
                break;
            case '1':
                return 1;
                break;
            case '2':
                return 2;
                break;
            case '3':
                return 3;
                break;
            case '4':
                return 4;
                break;
            case '5':
                return 5;
                break;
            case '6':
                return 6;
                break;
            case '7':
                return 7;
                break;
            case '8':
                return 8;
                break;
            case '9':
                return 9;
                break;
                
            default: throw std::string("CHAR IS NOT A NUMBER");
                break;
        }
    }
//---------------------------------------AREA-------------------------------------------------//
    
    template <typename T>
    class polygon{
        T radius;
        T a;
        T b;
        T c;
        std::string name;
        int nameNumber;
    public:
       
        
        void assign();
        void circle(T radius);
        void triangle(T a,T b, T c);
        void rectangle(T a, T b);
        void square(T a);
        
        T circleArea();
        T triangleArea();
        T rectangleArea();
        T squareArea();
        
        T circleP();
        T triangleP();
        T rectangleP();
        T squareP();
        
        T area();
        T perimeter();
    };
    
    
    
    template <typename T>
    void polygon<T>::circle(T radius){
        this->name = std::string("circle");
        this->nameNumber = 1;
        this->radius = radius;
    }
    template <typename T>
    void polygon<T>::triangle(T a,T b, T c){
        this->name = std::string("triangle");
        this->nameNumber = 2;
        this->a = a;
        this->b = b;
        this->c = c;
    }
    template <typename T>
    void polygon<T>:: rectangle(T a, T b){
        this->name = std::string("rectangle");
        this->nameNumber = 3;
        this->a = a;
        this->b = b;
    }
    template <typename T>
    void polygon<T>:: square(T a){
        this->name = std::string("square");
        this->nameNumber = 4;
        this->a = a;
    }
    
    template <typename T>
    T polygon<T>::circleArea(){
        return PI*pow(this->radius,2);
    }
    template <typename T>
    T polygon<T>::triangleArea(){
        T semiperimeter = (this->a+this->b+this->c)/2;
        T h = semiperimeter - this->a;
        T g = semiperimeter - this->b;
        T f = semiperimeter - this->c;
        return sqrt(semiperimeter*h*g*f);
    }
    template <typename T>
    T polygon<T>:: rectangleArea(){
        return this->a*this->b;
    }
    template <typename T>
    T polygon<T>:: squareArea(){
        return pow(this->a, 2);
    }
    
    
    template <typename T>
    T polygon<T>::circleP(){
        return 2*PI*this->radius;
    }
    
    template <typename T>
    T polygon<T>::triangleP(){
        return this->a+this->b+this->c;
    }
    
    template <typename T>
    T polygon<T>:: rectangleP(){
        return 2*(this->a+this->b);
    }
    
    template <typename T>
    T polygon<T>:: squareP(){
        return 4*this->a;
    }
    
    template <typename T>
    T polygon<T>::area(){
        
        switch (this->nameNumber) {
            case 1:
                return circleArea();
                break;
            case 2:
                return triangleArea();
                break;
            case 3:
                return rectangleArea();
                break;
            case 4:
                return squareArea();
                break;
                
            default:
                throw std::string("PLEASE POLYGON!");
                break;
        }
        
    }
    
    template <typename T>
    T polygon<T>:: perimeter(){
            
            switch (this->nameNumber) {
                case 1:
                    return circleP();
                    break;
                case 2:
                    return triangleP();
                    break;
                case 3:
                    return rectangleP();
                    break;
                case 4:
                    return squareP();
                    break;
                    
                default:
                    throw std::string("PLEASE POLYGON!");
                    break;
            }
            
        
        
    }
    
    
}
#endif
