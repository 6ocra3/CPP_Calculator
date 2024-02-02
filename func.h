#include <string>
using namespace std;
#ifndef P1_CAL_FUNC_H
#define P1_CAL_FUNC_H

class FUNC{
public:
    char name;
    string expression;
    string num;
    FUNC(char a, string b, string temp);
    FUNC();
};

class FUNCS{
public:
    FUNC funcs[100];
    int cnt;
    FUNCS();
    void add_func(char a, string b, string num);
};

#endif //P1_CAL_FUNC_H