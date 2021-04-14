#!/bin/bash

yacc -d yacc.y
lex lex.l
gcc -w  y.tab.c -lfl
./a.out < input_for.pas
