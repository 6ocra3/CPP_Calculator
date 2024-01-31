//
// Created by Макар Кряжев on 31.01.2024.
//

#ifndef P1_CALCULATOR_VARS_H
#define P1_CALCULATOR_VARS_H

class VAR{
public:
    char var;
    int num;
    VAR(char a, int b);
};

class VARS{
    VAR vars[100];
    int cnt;
    VARS();
    int get_num(char a);
    void add_var(char a, int b);
};

#endif
