#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <vector>

#include "vars.h"
#include "vars.cpp"
#include <cmath>

using namespace std;

vector<string> operations {"+","-","^","/","*","sin","cos","tg","ctg","arcsin","arccos","arctg","arcctg","log","ln","root"};
vector<string> preoperations {"sin","cos","tg","ctg","arcsin","arccos","arctg","arcctg","log","ln","root", "("};

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


string calc_var(VARS list, string str) {
    for (int i = 0; i < list.cnt; i++) {
        while (str.find(list.vars[i].var) != string::npos) {
            str.replace(str.find(list.vars[i].var), 1, list.vars[i].num);
        }
    }
    return str;
}

int isDigit(char c){
    if(c - '0' >= 0 && c - '0' <= 9){
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

int strToInt(string c){
    int itog = 0;
    for(int i = 0; i<c.length();i++){
        itog = itog * 10 + c[i] - '0';
    }
    return itog;
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
        return stack[cur - 1];
    }
};

STACK<double> q;

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
        return tempsin / tempcos;
    }
    else if(c=="ctg"){
        double temp = q.pop();
        double tempsin = sin(temp);
        double tempcos = cos(temp);
        return tempcos / tempsin;
    }
    else if(c == "log"){
        double num = log(q.pop()); // натуральный логарифм от числа
        double base = log(q.pop()); // натуральный логарифм от основания
        return num / base;
    }
    else if( c == "ln"){
        double temp = log (q.pop());;
        return temp;
    }
    else if (c== "root"){
        double num = q.pop(); // подкоренное выражение
        double base = q.pop(); // значение корня
        return pow(num,1/base);
    }
    else if (c == "arcsin"){
        return asin(q.pop());
    }
    else if (c == "arccos"){
        return acos(q.pop());
    }
    else if (c == "arctg"){
        return atan(q.pop());
    }
    else if (c == "arcctg"){
        double temp = atan(q.pop());
        return pi/2 - temp;
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
        return a/b;
    }

}



int main(){
    string s;
    getline(cin, s);
    cout << "Expression:\n" << s << "\n";
    string curDig = "";
    string curOper = "";
    VARS peremen;
    while (cin) {
        string cur_s;
        getline(cin, cur_s);
        if (cur_s[0] >= 'a' && cur_s[0] <= 'z') {
            string cur_num;
            for (int i = cur_s.find('=')+1; i < cur_s.size(); i++) {
                if (cur_s[i] != ' ') {
                    cur_num += cur_s[i];
                }
            }
            peremen.add_var(cur_s[0], cur_num);
        }
    }
    s = calc_var(peremen, s);
    s+=" ! ";
    vector<string> a;
    vector<string> la;
    STACK<string> pre;
    STACK<string> stack;
    for(int i = 0; i<s.length();i++){
        if(s[i] == ','){
            continue;
        }
        else if(s[i] != ' '){
            if(isDigit(s[i])){
                curDig += s[i];
            }
            else{
                curOper += s[i];
            }

        }
        else{
            if(curDig.length()){
                a.push_back(curDig);
                la.push_back(curDig);
                curDig = "";
            }
            else{
                if(stack.cur == 0){
                    stack.push(curOper);
                }
                else{
                    if(curOper == "!"){
                        while(stack.cur){
                            la.push_back(stack.pop());
                        }
                    }
                    else if(isPreoper(curOper)){
                        stack.push(curOper);
                    }
                    else if(curOper != ")"){
                        if(getPrioritet(stack.get()) >= getPrioritet(curOper) or (isPreoper(stack.get()))){
                            while((getPrioritet(stack.get()) >= getPrioritet(curOper) && stack.get() != "(" && stack.cur > 0) or ((isPreoper(stack.get()))&& stack.cur > 0&& stack.get() != "(")){
                                la.push_back(stack.pop());
                                if(stack.cur == 0){
                                    break;
                                }
                            }
                            stack.push(curOper);
                        }
                        else{
                            stack.push(curOper);
                        }
                    }
                    else{
                        while(stack.get() != "("){
                            la.push_back(stack.pop());
                        }
                        stack.pop();
                    }
                }
                curOper = "";
            }
        }
    }

    double last = 0;
    for(int i = 0; i<la.size();i++){
        if(isSign(la[i])){
            last = oper(la[i]);
            q.push(last);
        }
        else{
            if(la[i] == ""){
                continue;
            }
            q.push(strToInt(la[i]));
        }
    }


    if(la.size() == 1){
        cout << la[0];
    }
    else{
        cout << last;
    }

}