#ifndef CODEGEN_H_INCLUDED
#define CODEGEN_H_INCLUDED

FILE* createFile(char* name);
void closeFile(FILE* fp);
void putDataSection(FILE* fp,char dataSection[]);
void putBssSection(FILE* fp,char bssSection[]);
void putTextSection(FILE* fp,char textSection[]);
char* buildDataSection(char s1[],char s2[]);
char* buildBssSection(char s1[],char s2[]);
char* buildTextSection(char s1[],char s2[]);
char* movq(char s1[],char s2[]);
char* movl(char s1[],char s2[]);
char* add(char* s1,char* s2);
char* sub(char* s1,char* s2);
char* imul(char* s1,char* s2);
char* idiv(char* s1);
char* neg(char* s1);
char* compare(char* s1,char* s2);
char* defineString(char* lc,char* str);
char* buildLabel(char* label);
char* buildJump(char* mode,char* label);
char* sysCallPrint();
char* cqto(void);
#endif // CODEGEN_H_INCLUDED
