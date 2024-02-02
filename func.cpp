#include "func.h"

FUNC::FUNC(char a, string b,string temp): name(a), expression(b), num(temp) {};

FUNC::FUNC(): name(), expression() {};

FUNCS::FUNCS(): cnt(0) {}

void FUNCS::add_func(char a, std::string b,std::string num) {
    for(int i = 0; i<cnt;i++){
        if(funcs[i].name == a){
            funcs[i].expression = b;
            return;
        }
    }
    FUNC new_func(a, b, num);
    funcs[cnt] = new_func;
    cnt++;
}
