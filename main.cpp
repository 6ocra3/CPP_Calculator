#include <iostream>
#include <string>
#include <vector>
#include "vars.h"

using namespace std;

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

int isSign(string c){
    if(c != "+" && c != "-" && c != "*" && c != "/"){
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

STACK<int> q;

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

int oper(string c){
    int b = q.pop();
    int a = q.pop();
    if(c == "+"){
        return a+b;
    }
    else if(c == "-"){
        return a-b;
    }
    else if(c == "*"){
        return a*b;
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
    cout << s;
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
                    else if(curOper == "("){
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

    int last = 0;
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