all: elemcompiler

elemcompiler: elemcompiler.c elemcompiler.l elemcompiler.y elemcompiler.h codegen.c codegen.h
	bison -d elemcompiler.y
	flex -o elemcompiler.lex.c elemcompiler.l
	gcc -Wall elemcompiler.c elemcompiler.tab.c elemcompiler.lex.c codegen.c -o $@ -lm -g

%.c: %.y
	test
