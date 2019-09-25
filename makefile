program: instructions.o analyse.o parser.tab.o lex.yy.o
	g++ -Wall -o $@ $^
instructions.o: instructions.cpp instructions.hpp	
	g++ -Wall -c -o $@ $<
analyse.o: analyse.cpp analyse.hpp
	g++ -Wall -c -o $@ $<
parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -Wall -c -o $@ $<
lex.yy.o: lex.yy.c parser.tab.hpp	
	g++ -Wall -c -o $@ $<
parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -v -d $< 
lex.yy.c: lexer.lex 
	flex $<

		
.PHONY: clean
clean:
	rm -f *~ *tab* lex.yy.c *.o *.gch *.output
