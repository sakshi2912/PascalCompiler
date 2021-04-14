#!/bin/bash

yacc -d yacc.y
lex lex.l
gcc y.tab.c -ll
./a.out < input_for.pas
