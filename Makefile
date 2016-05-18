all: elemcompiler

elemcompiler: elemcompiler.c elemcompiler.l elemcompiler.y elemcompiler.h
	bison -d elemcompiler.y
	flex -o elemcompiler.lex.c elemcompiler.l
	gcc -Wall elemcompiler.c elemcompiler.tab.c elemcompiler.lex.c -o $@ -lm

%.c: %.y
