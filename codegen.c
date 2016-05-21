#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include  "codegen.h"

FILE* createFile(char* name) {
   FILE *fp;
   fp = fopen(name, "w+");
   //intitial s file x86
   return fp;
}

void closeFile(FILE* fp){
	//end of s file x86
	fputs("\tmovl\t$0, %eax\n\tleave\n\t.cfi_def_cfa 7, 8\n\tret\n\t.cfi_endproc\n.LFE0:\n\t.size\tmain, .-main\n\t.ident\t\"GCC: (GNU) 6.1.1 20160501\"\n\t.section\t.note.GNU-stack,\"\",@progbits\n",fp);
	fclose(fp);
}

void putDataSection(FILE* fp,char dataSection[]){
	//section.data
	fputs("\t.section	.rodata\n.LC0:\n\t.string \"%ld\"\n.LC1:\n\t.string \"%s\"\n", fp);
	fputs(dataSection, fp);
	free(dataSection);
}

void putBssSection(FILE* fp,char bssSection[]){
	fputs("\t.file	\"test.c\"\n\t.globl\tfrom\n\t.bss\n\t.align 8\n\t.type\tfrom, @object\n\t.size\tfrom, 8\nfrom:\n\t.zero\t8\n", fp);
	fputs(bssSection, fp);
	//free(bssSection);
}

void putTextSection(FILE* fp,char textSection[]){
	fputs("\t.text\n\t.globl\tmain\n\t.type\tmain, @function\nmain:\n.LFB0:\n\t.cfi_startproc\n\tpushq\t%rbp\n\t.cfi_def_cfa_offset 16\n\t.cfi_offset 6, -16\n\tmovq\t%rsp, %rbp\n\t.cfi_def_cfa_register 6\n", fp);
	fputs(textSection,fp);
	free(textSection);
}

char* buildDataSection(char s1[],char s2[]){
	char *result = malloc(strlen(s1)+strlen(s2)+1);
	strcpy(result, s1);
	strcat(result, s2);
	free(s1);
	free(s2);
	return result;
}

char* buildBssSection(char s1[],char s2[]){
	char *result = malloc(strlen(s1)+strlen(s2)+1);
	strcpy(result, s1);
	strcat(result, s2);
	free(s1);
	free(s2);
	return result;
}

char* buildTextSection(char s1[],char s2[]){
	char *result = malloc(strlen(s1)+strlen(s2)+1);
	strcpy(result, s1);
	strcat(result, s2);
	free(s1);
	free(s2);
	return result;
}

char* movq(char s1[],char s2[]){

	char mv[] = "\tmovq\t";
	char comma[] = ", ";
	char *result = malloc(strlen(mv)+strlen(comma)+strlen("\n")+strlen(s1)+strlen(s2)+1);
	strcpy(result, mv);
    strcat(result, s1);
    strcat(result,comma);
	strcat(result,s2);
	strcat(result,"\n");
	return result;
}

char* movl(char s1[],char s2[]){

	char mv[] = "\tmovl\t";
	char comma[] = ", ";
	char *result = malloc(strlen(mv)+strlen(comma)+strlen("\n")+strlen(s1)+strlen(s2)+1);
	strcpy(result, mv);
    strcat(result, s1);
    strcat(result,comma);
	strcat(result,s2);
	strcat(result,"\n");
	return result;
}

char* add(char* s1,char* s2){
	char mv[] = "\taddq\t ";
	char comma[] = ", ";
	char *result = malloc(strlen(mv)+strlen(comma)+strlen("\n")+strlen(s1)+strlen(s2)+1);
	strcpy(result, mv);
    strcat(result, s1);
    strcat(result,comma);
	strcat(result,s2);
	strcat(result,"\n");
	return result;
}

char* cqto(){
    char *result = malloc(strlen("\tcqto\n"));
    strcpy(result,"\tcqto\n");
    return result;
}

char* sub(char* s1,char* s2){
	char mv[] = "\tsubq\t ";
	char comma[] = ", ";
	char *result = malloc(strlen(mv)+strlen(comma)+strlen("\n")+strlen(s1)+strlen(s2)+1);
	strcpy(result, mv);
    strcat(result, s1);
    strcat(result,comma);
	strcat(result,s2);
	strcat(result,"\n");
	return result;
}

char* imul(char* s1,char* s2){
	char mv[] = "\timulq\t ";
	char comma[] = ", ";
	char *result = malloc(strlen(mv)+strlen(comma)+strlen("\n")+strlen(s1)+strlen(s2)+1);
	strcpy(result, mv);
    strcat(result, s1);
    strcat(result,comma);
	strcat(result,s2);
	strcat(result,"\n");
	return result;
}

char* idiv(char* s1){
	char mv[] = "\tidivq\t ";
	char *result = malloc(strlen(mv)+strlen("\n")+strlen(s1)+1);
	strcpy(result, mv);
    strcat(result, s1);
	strcat(result,"\n");
	return result;
}

char* neg(char* s1){
	char mv[] = "\tnegq\t ";
	char *result = malloc(strlen(mv)+strlen("\n")+strlen(s1)+1);
	strcpy(result, mv);
    strcat(result, s1);
	strcat(result,"\n");
	return result;
}

char* compare(char* s1,char* s2){
	char mv[] = "\tcmpq\t ";
	char comma[] = ", ";
	char *result = malloc(strlen(mv)+strlen(comma)+strlen("\n")+strlen(s1)+strlen(s2)+1);
	strcpy(result, mv);
    strcat(result, s1);
    strcat(result,comma);
	strcat(result,s2);
	strcat(result,"\n");
	return result;
}

char* defineString(char* lc,char* str){
	char string[] = "\t.string";
	char *result = malloc(strlen(lc)+strlen(str)+strlen(string)+strlen("\"")+strlen("\"")+strlen(":")+6);
	strcpy(result,".");
	strcat(result,lc);
	strcat(result,":\n");
	strcat(result,string);
	strcat(result,"\t");
	strcat(result,str);
	strcat(result,"\n");
	return result;
}

char* buildLabel(char* label){
    char *result = malloc(strlen(label)+strlen(":")+strlen(".")+2);
    strcpy(result,".");
    strcat(result,label);
    strcat(result,":\n");
    return result;
}

char* buildJump(char* mode,char* label){
    char *result = malloc(strlen(label)+strlen(mode)+strlen(".")+4);
    strcpy(result,"\t");
    strcat(result,mode);
    strcat(result,"\t");
    strcat(result,".");
    strcat(result,label);
    strcat(result,"\n");
    return result;
}


char* sysCallPrint(){
	//int	0x80		; call kernel
	char* sysCall ="\tcall	printf\n";
	char *result = malloc(strlen(sysCall)+1);
	strcpy(result,sysCall);
	return result;
}


//int main(){
//	FILE *fp = createFile();
//	putDataSection(fp,buildDataSection(defineString("LC0","Hello, World!!! :> %d\\n"),defineString("LC1","%ld\\n")));
//	putTextSection(fp,buildTextSection(buildTextSection(buildTextSection(buildTextSection(
//                                                                                       buildTextSection(
//                                                                                                        compare("$0", "-8(%rbp)"),movq("$10","-8(%rbp)"))
//                                                                                       ,add("$8", "%rsp"))
//                                                                      ,buildJump("je","L2"))
//                                                     ,bulidLabel("L2"))
//                                    ,sysCallPrint()));
//	putBssSection(fp,"");
//	//putDataSection(fp,"");
//	//putTextSection(fp,"");
//	closeFile(fp);
//	return 0;
//}
