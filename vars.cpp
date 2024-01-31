#include "vars.h"

VAR::VAR(char a, int b) : var(a), num(b) {}

VARS::VARS() : cnt(0) {}

int VARS::get_num(char a) {
    for (int i = 0; i < cnt; ++i) {
        if (vars[i].var == a) {
            return vars[i].num;
        }
    }
    return -1;
}

void VARS::add_var(char a, int b) {
    for(int i = 0; i<cnt;i++){
        if(vars[i].var == a){
            vars[i].num = b;
        }
    }
    VAR new_var(a, b);
    vars[cnt] = new_var;
    cnt++;
}