CC = g++ -O2 -Wno-deprecated

    tag = -i
    test_out_tag = -ll

    ifdef linux
    tag = -n
    test_out_tag = -lfl
    endif
    

gtest: Record.o Comparison.o ComparisonEngine.o Schema.o File.o FileHandler.o DBFile.o y.tab.o lex.yy.o gtest-all.o gtest.o
	$(CC) -o gtest Record.o Comparison.o ComparisonEngine.o Schema.o File.o FileHandler.o DBFile.o y.tab.o lex.yy.o gtest-all.o gtest.o -ll

gtest-all.o: test/gtest-all.cc
	$(CC) -g -c test/gtest-all.cc

test.out: Record.o Comparison.o ComparisonEngine.o Schema.o File.o FileHandler.o DBFile.o y.tab.o lex.yy.o test.o
	$(CC) -o test.out Record.o Comparison.o ComparisonEngine.o Schema.o File.o FileHandler.o DBFile.o y.tab.o lex.yy.o test.o -ll

main: Record.o Comparison.o ComparisonEngine.o Schema.o File.o FileHandler.o DBFile.o y.tab.o lex.yy.o main.o
	$(CC) -o main Record.o Comparison.o ComparisonEngine.o Schema.o File.o FileHandler.o DBFile.o y.tab.o lex.yy.o main.o -ll


test.o: test.cc
	$(CC) -g -c test.cc

main.o: main.cc
	$(CC) -g -c main.cc

Comparison.o: Comparison.cc
	$(CC) -g -c Comparison.cc

ComparisonEngine.o: ComparisonEngine.cc
	$(CC) -g -c ComparisonEngine.cc

DBFile.o: DBFile.cc
	$(CC) -g -c DBFile.cc

File.o: File.cc
	$(CC) -g -c File.cc

Record.o: Record.cc
	$(CC) -g -c Record.cc

Schema.o: Schema.cc
	$(CC) -g -c Schema.cc

y.tab.o: Parser.y
	yacc -d Parser.y
	sed $(tag) -e "s/  __attribute__ ((__unused__))$$/# ifndef __cplusplus\n  __attribute__ ((__unused__));\n# endif/" y.tab.c
	g++ -c y.tab.c

lex.yy.o: Lexer.l
	lex  Lexer.l
	gcc  -c lex.yy.c

clean:
	rm -f *.o
	rm -f *.out
	rm -f y.tab.c
	rm -f lex.yy.c
	rm -f y.tab.h
