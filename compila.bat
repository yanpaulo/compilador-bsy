@echo off
SET "MINGW_DIR=C:\MinGW\bin"
SET "FB_DIR=C:\Users\yanpa\Downloads\win_flex_bison-2.5.15"

SET PATH=%PATH%;%MINGW_DIR%;%FB_DIR%

win_flex analisador.l
win_bison -d parser.y
gcc parser.tab.c lex.yy.c -o calcula.exe