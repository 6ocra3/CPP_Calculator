
#include <cmath>
#include <stdexcept>
#include "operations.h"

using namespace std;
vector<string> operations {"+","-","^","/","*","sin","cos","tg","ctg","arcsin","arccos","arctg","arcctg","log","ln","root","not","fact"};
vector<string> preoperations {"sin","cos","tg","ctg","arcsin","arccos","arctg","arcctg","log","ln","root", "(","not","fact"};
//
double pi_eq(int a){
    double ans = 0;
    double div = 2;
    double temp = 0;
    for (long long i = 0;i<100000000;++i){
        temp = ((4*i+1) * (4*i+3));
        ans += div/temp;
    }
    return ans;
}

const double pi = pi_eq(1) * 4.0;



int isDigit(char c){
    if((c - '0' >= 0 && c - '0' <= 9) or (c=='.')){
        return 1;
    }
    return 0;
}

int isOper(string c){
    int temp = 0;
    for(int i = 0;i<operations.size();++i){
        if(c == operations[i]){
            temp = 1;
            break;
        }
    }
    if(temp == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int isPreoper(string c){
    int temp = 0;
    for(int i = 0;i<preoperations.size();++i){
        if(c == preoperations[i]){
            temp = 1;
            break;
        }
    }
    if(temp == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int isSign(string c){
    if(isOper(c)){
        return 1;
    }
    else{
        return 0;
    }
}

double strToInt_Double(string c){
    long long itog = 0;
    int a = c.find('.');
    if(a){
        return stod(c);
    }
    else{
        for(int i = 0; i<c.length();i++){
            itog = itog * 10 + c[i] - '0';
        }
        return itog;
    }
}

int getPrioritet(string s){
    if(s == "(" || s == ")"){
        return 1;
    }
    else if(s == "*" || s == "/"){
        return 3;
    }
    else if(s == "^"){
        return 4;
    }
    else{
        return 2;
    }
}

template<typename T>
class STACK{
public:
    T stack[100];
    int cur = 0;

    void push(T c){
        stack[cur] = c;
        cur++;
    }
    T pop(){
        cur--;
        return stack[cur];
    }
    T get(){
        if(cur == 0){
            throw out_of_range("incorrect input");
        }
        return stack[cur - 1];
    }
};

STACK<double> q;

//F ( x ) + G ( y ) + F ( 2 )
//F ( x ) = x + 3
//G ( y ) = y - 3
//x = 0
//y = 6

//root ( 3 , sin ( F ( x ) + G ( y ) ) )
//F ( x ) = log ( 3 , 2 )
//G ( y ) = ln ( y )
//x = 1
//y = 4

double oper(string c){
    if(c == "sin"){
        return sin(q.pop());
    }
    else if(c == "cos"){
        return cos(q.pop());
    }
    else if(c == "tg"){
        double temp = q.pop();
        double tempsin = sin(temp);
        double tempcos = cos(temp);
        if(tempcos == 0){
            throw invalid_argument(c + " is unidentified");
        }
        return tempsin / tempcos;
    }
    else if(c=="ctg"){
        double temp = q.pop();
        double tempsin = sin(temp);
        double tempcos = cos(temp);
        if ( tempsin==0){
            throw invalid_argument(c + " is unidentified");
        }
        return tempcos / tempsin;
    }
    else if(c == "log"){
        double num = q.pop(); // натуральный логарифм от числа
        double base = q.pop(); // натуральный логарифм от основания
        if(num<=0 or base<=0 or base == 1){
            throw invalid_argument(c + " is unidentified");
        }
        return log(num) / log(base);
    }
    else if( c == "ln"){
        double num = q.pop(); // натуральный логарифм от числа
        if(num<=0){
            throw invalid_argument(c + " is unidentified");
        }
        return log(num);
    }
    else if (c== "root"){
        double num = q.pop(); // подкоренное выражение
        double base = q.pop(); // значение корня
        if((base>0) and (base<10) and (base == int(base))){
            if(int(base) % 2 == 1){
                if(num < 0){
                    return 0 - pow(abs(num),1/abs(base));
                }
                else{
                    return pow(num,1/base);
                }
            }
            else{
                if(num < 0){
                    throw invalid_argument(c + " is unidentified");
                }
                else{
                    return pow(num,1/base);
                }
            }
        }
        else{
            throw invalid_argument(c + " is unidentified");
        }
    }
    else if (c == "arcsin"){
        double temp = q.pop();
        if(temp > 1 or temp < 1){
            throw invalid_argument(c + " is unidentified");
        }
        return asin(temp);
    }
    else if (c == "arccos"){
        double temp = q.pop();
        if(temp > 1 or temp < 1){
            throw invalid_argument(c + " is unidentified");
        }
        return acos(temp);
    }
    else if (c == "arctg"){
        return atan(q.pop());
    }
    else if (c == "arcctg"){
        double temp = atan(q.pop());
        return pi/2 - temp;
    }
    else if(c == "not"){
        return 0 - q.pop();
    }
    else if (c == "fact"){
        double temp = q.pop();
        if(int(temp) == temp){
            long long ans = 1;
            for(long i = 1;i<=int(temp);++i){
                ans*=i;
            }
            return ans;
        }
        else{
            throw invalid_argument(c + " is unidentified");
        }
    }
    double b = q.pop();
    double a = q.pop();
    if(c == "+"){
        return a+b;
    }
    else if(c == "-"){
        return a-b;
    }
    else if(c == "*"){
        return a*b;
    }
    else if (c == "^"){
        return pow(a,b);
    }
    else{
        if(b == 0){
            throw invalid_argument(c + " is unidentified");
        }
        return a/b;
    }

}

string calc_var(VARS list, string str) {
    for (int i = 0; i < list.cnt; i++) {
        while (str.find(list.vars[i].var) != string::npos) {
            str.replace(str.find(list.vars[i].var), 1, list.vars[i].num);
        }
    }
    return str;
}




string calc_func(string str, FUNCS funcs){
    for (int i = 0; i < funcs.cnt; i++) {
        while (str.find(funcs.funcs[i].name) != string::npos) {
            string temp = funcs.funcs[i].expression;
            string line = "";
            int curr = str.find(funcs.funcs[i].name) + 4;
            while(str[curr] != ' '){
                line += str[curr];
                curr+=1;
            }
            VARS makrak;
            makrak.add_var(funcs.funcs[i].num[0],line);
            temp = calc_var(makrak,temp);
            temp = "( " + temp + " )";
            str.replace(str.find(funcs.funcs[i].name),curr+2-str.find(funcs.funcs[i].name),temp);
        }
    }
    return str;
}
