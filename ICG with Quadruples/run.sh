#!/bin/bash

yacc -d yacc.y
lex lex.l
gcc y.tab.c -lfl
./a.out < input_for.pas
