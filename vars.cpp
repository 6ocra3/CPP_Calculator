#include "vars.h"
#include <string>

VAR::VAR(char a, string b) : var(a), num(b) {}

VAR::VAR() : var('a'), num("0") {}

VARS::VARS() : cnt(0) {}

string VARS::get_num(char a) {
    for (int i = 0; i < cnt; ++i) {
        if (vars[i].var == a) {
            return vars[i].num;
        }
    }
    return "";
}

void VARS::add_var(char a, string b) {
    for(int i = 0; i<cnt;i++){
        if(vars[i].var == a){
            vars[i].num = b;
            return;
        }
    }
    VAR new_var(a, b);
    vars[cnt] = new_var;
    cnt++;
}