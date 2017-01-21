###############################################################################
# purpose: CSE 4713 / 6713 Assignment 1: Lexical Analyzer
# created: 8-25-2015
#  author: J. Edward Swan II
###############################################################################
.PRECIOUS = driver.cpp lexer.h lexer.cpp

_lex: lexer.o driver.o
	g++ -Wall -Wpedantic -o $@ $^

lexer.o: lexer.cpp lexer.h
	g++ -Wall -Wpedantic -o $@ -c lexer.cpp

driver.o: driver.cpp lexer.h
	g++ -Wall -Wpedantic -o $@ -c driver.cpp

clean: 
	$(RM) *.o _lex *~

