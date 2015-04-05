
all : vma target

vma:
	gcc -g -o vm vmachine.c



target:
	bison -v --yacc --defines --output=parser.c parser.y
	flex --outfile=scanner.c al2.l
	gcc -g scanner.c parser.c tabol.c intermediate.c stack.c lists.c tcode.c
	
al.c : al2.l
	flex --outfile=al.c al2.l	

parser.c: parser.y
	bison --yacc -v --defines --output=parser.c parser.y
	
tabol.o:tabol.c tabol.h
	gcc -c tabol.c
	
intermediate.o:intermediate.c intermediate.h
	gcc -c intermediate.c

stack.o:stack.c stack.h
	gcc -c stack.c

lists.o:lists.c lists.h
	gcc -c lists.c

tcode.o:tcode.c tcode.h
	gcc -c tcode.c

vmachine.o:vmachine.c vmachine.h
	gcc -c vmachine.c

clean:
	rm -rf lex.yy.c
	rm -rf parser.output
	rm -rf tabol.o
	rm -rf stack.o
	rm -rf intermediate.o
	rm -rf lists.o
