#include <string>
using namespace std;

#ifndef P1_CALCULATOR_VARS_H
#define P1_CALCULATOR_VARS_H

class VAR{
public:
    char var;
    string num;
    VAR(char a, string b);
    VAR();
};

class VARS{
public:
    VAR vars[100];
    int cnt;
    VARS();
    string get_num(char a);
    void add_var(char a, string b);
};

#endif
