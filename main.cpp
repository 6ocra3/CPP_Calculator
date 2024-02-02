#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include "vars.h"
#include "vars.cpp"
#include <cmath>
#include "func.h"
#include "func.cpp"
#include "operations.h"
#include "operations.cpp"
using namespace std;

int main(){
    string s;
    getline(cin, s);
    string curDig = "";
    string curOper = "";
    VARS peremen;
    FUNCS funcs;
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
        else if (cur_s[0] >= 'A' && cur_s[0] <= 'Z') {
            string cur_exp;
            for (int i = cur_s.find('=')+2; i < cur_s.size(); i++) {
                cur_exp += cur_s[i];
            }
            string temp = "";
            temp += cur_s[4];
            funcs.add_func(cur_s[0], cur_exp,temp);
        }
    }
    for (long i = 0; i<322;++i){
        s = calc_var(peremen, s);
        s = calc_func(s,funcs);
    }
    s+=" ! ";
    vector<string> a;
    vector<string> la;
    STACK<string> pre;
    STACK<string> stack;
    for(int i = 0; i<s.length();i++){
        try{
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
                                if(curOper==""){
                                    continue;
                                }
                                else{
                                    stack.push(curOper);
                                }
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
        catch (out_of_range ex){
            cerr <<ex.what();
            return 0;
        }
    }

    double last = 0;
    for(int i = 0; i<la.size();i++){
        if(isSign(la[i])){
            try{
                last = oper(la[i]);
                q.push(last);
            }
            catch (invalid_argument ex){
                cerr<<ex.what();
                return 0;
            }
        }
        else{
            if(la[i] == ""){
                continue;
            }
            q.push(strToInt_Double(la[i]));
        }
    }


    if(la.size() == 1){
        cout << la[0];
    }
    else{
        cout << last;
    }

}