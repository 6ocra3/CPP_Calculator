#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;



int isDigit(char c){
    if(c - '0' >= 0 && c - '0' <= 9){
        return 1;
    }
    return 0;
}

int isSign(string c){
    if(c != "+" && c != "-" && c != "*" && c != "/" and c != "^" and c != "sin" and c!= "cos" and c!="tg" and c!="ctg" and c!="log"){
        return 0;
    }
    return 1;
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

double fact(double num){
    double ans = 1;
    for(long long i = 1;i<=num;++i){
        ans *= i;
    }
    return ans;
}

double sinv(double num){
    double ans = 0;
//    for(int i = 0;i<1000;++i){
//        ans+= (pow(-1,i) *  pow(num,2*i+1))/(fact(2 * i +1));
//    }
    ans = sin(num);
    return ans;
}

double cosv(double num){
    double ans = 0;
//    for(int i = 0;i<1000;++i){
//        ans+= (pow(-1,i) *  pow(num,2*i))/(fact(2 * i));
//    }
    ans = cos(num);
    return ans;
}


double oper(string c){
    if(c == "sin"){
       double temp = sinv(q.pop());
       return temp;
    }
    else if(c == "cos"){
        double temp = cosv(q.pop());
        return temp;
    }
    else if(c == "tg"){
        double temp = q.pop();
        double tempsin = sinv(temp);
        double tempcos = cosv(temp);
        return tempsin / tempcos;
    }
    else if(c=="ctg"){
        double temp = q.pop();
        double tempsin = sinv(temp);
        double tempcos = cosv(temp);
        return tempcos / tempsin;
    }
    else if(c == "log"){
        double temp = q.pop();
        return temp;
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
    s+=" ! ";
    vector<string> a;
    vector<string> la;
    STACK<string> stack;
    for(int i = 0; i<s.length();i++){
        if(s[i] != ' '){
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
                    else if((curOper == "(") or (curOper =="sin") or (curOper == "cos")){
                        stack.push(curOper);
                    }
                    else if(curOper != ")"){
                        if(getPrioritet(stack.get()) >= getPrioritet(curOper)){
                            while(getPrioritet(stack.get()) >= getPrioritet(curOper) && stack.get() != "(" && stack.cur > 0){
                                la.push_back(stack.pop());
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