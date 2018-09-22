@echo off
SET "MINGW_DIR=C:\MinGW\bin"
SET "FLEX_BISON_DIR=.\win_flex_bison-2.5.15"

SET PATH=%PATH%;%MINGW_DIR%;%FLEX_BISON_DIR%

win_flex analisador.l
win_bison -d parser.y
gcc parser.tab.c lex.yy.c -o calcula.exe