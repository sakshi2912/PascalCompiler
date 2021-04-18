#!/bin/bash

yacc -d yacc.y -Wnone
lex lex.l
gcc y.tab.c -lfl
./a.out < input_for.pas
