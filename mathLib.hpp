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
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

namespace math_lib {
    
//-----------------------------------------DIGITS------------------------------------------------------//
    

    template <typename T>
    std::vector<int> numberToDigit(const T n){
        std::stringstream ss;
        ss<<n;
        std::string str = ss.str();
        unsigned long size = str.size();
        auto it = str.find('.');
        if(it!=std::string::npos){
            str.erase(it,it-1);
            size--;
            
        }
        std::vector<int> v(size);
        for(int i = 0;i<size;i++){
            v.at(i)=stoi(str.substr(i,1));
            
        }
        
        return v;
        
        
    }
    
 //-----------------------------------------DETERMINANT------------------------------------------------------//
    
   template<typename T>
    T determinant(std::vector<std::vector<T>> &v){
        
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
    template <typename T = unsigned int>
    int power(int a, unsigned int n,int p){
        int res = 1;
        a = a % p;
        
        while (n > 0) {
            if(n & 1)
                res = (res * a) % p;
            n = n >> 1;
            a = (a * a) % p;
        }
        return res;
    }
    
    template <typename T = unsigned int>
    bool isPrime(unsigned int n , unsigned int k =3){
        
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


//-------------------------------------------INTERGRATION----------------------------------------------------//

    template<typename T =std::string >
    std::vector<std::string> expressionExtract(std::string expression){
        
        std::vector<std::string> v;
        std::string c;
        
        for(int i = 0;i<expression.size();i++){
            c+=expression.substr(i,1);
            
            //------------------//
            if(c.at(0)==' '){
                c.clear();
                continue;
            }
            
            //--------x---------//
            
            if(c=="x"&&expression.substr(i+1,1)!="^"){
                v.emplace_back(std::string(c));
                c.clear();
                continue;
            }
            
            
            
            if(c=="x^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //--------sin---------//
            
            if((c == "sin(x)"||c == "sin x"||c == "sinx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            if(c == "sin(x)^"||c == "(sin x)^"||c == "(sinx)^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //--------cos---------//
            
            if(c == "cos(x)^"||c == "(cos x)^"||c == "(cosx)^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            if((c == "cos(x)"||c == "cos x"||c == "cosx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            //--------tan---------//
            
            if(c == "tan(x)^"||c == "(tan x)^"||c == "(tanx)^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            if((c == "tan(x)"||c == "tan x"||c == "(tanx)")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            //--------cot---------//
            
            if((c == "cot(x)"||c == "cot x"||c == "cotx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            if(c == "cot(x)^"||c == "(cot x)^"||c=="(cotx)^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //-------cosec----------//
            
            if((c == "cosec(x)"||c == "cosec x"||c == "cosecx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            if(c == "cosec(x)^"||c == "(cosec x)^"||c == "(cosecx)^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //--------sec---------//
            
            if((c == "sec(x)"||c == "sec x"||c == "secx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            if(c == "sec(x)^"||c == "(sec x)^"||c == "(secx)^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //--------e---------//
            
            if(c == "e^"){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            if((c == "exp(1)"||c == "e")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(c);
                c.clear();
                continue;
            }
            
            //--------ln---------//
            
            if((c == "ln(x)"||c == "ln x"||c == "lnx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(std::string(c));
                c.clear();
                continue;
            }
            
            
            
            if((c == "ln(x)^"||c == "(ln x)^"||c == "(lnx)^")){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //--------log---------//
            
            
            if((c == "log(x)"||c == "log x"||c == "logx")&&expression.substr(i+1,1)!="^"){
                v.emplace_back(std::string(c));
                c.clear();
                continue;
            }
            
            
            
            if((c == "log(x)^"||c == "(log x)^"||c == "(logx)^")){
                c+=expression.substr(i+1,1);
                v.emplace_back(c);
                i+=1;
                c.clear();
                continue;
            }
            
            //-----------------//
            
        }
        return v;
    }
   
}
#endif
