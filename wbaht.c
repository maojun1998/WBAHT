#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>


#define TABLE_SIZE_SPACE_TWO        (2)
#define TABLE_SIZE_SPACE_FOUR       (4)
#define TABLE_SIZE_SPACE_EIGHT      (8)

int table_size = 0;
int lineNo = 0;

void buildJs (
    FILE *outHTML
    );
    
void
TokenScan (
    FILE *in, 
    FILE *out,
    FILE *inHTML,
    FILE *outHTML
    );

#define LANG_TYPE_C         (0)
#define LANG_TYPE_CPP       (1)
#define LANG_TYPE_JAVA      (2)
#define LANG_TYPE_PYTHON    (3)
#define LANG_TYPE_CSHARP    (4)
#define LANG_TYPE_ASM       (5)
#define LANG_TYPE_SHELL     (6)
#define LANG_TYPE_MAKEFILE  (7)
#define LANG_TYPE_POWERSH   (8)
#define LANG_TYPE_RUBY      (9)
#define LANG_TYPE_HASKELL   (10)
#define LANG_TYPE_LISP      (11)
#define LANG_TYPE_USER      (12)
#define LANG_TYPE_DEFAULT   (13)


int lang_type = 0;
int lang_table_size = 0;
char **table_p = NULL;

void token (
	FILE *in, 
	FILE *out,
	FILE *inHTML,
	FILE *outHTML,
    int TABLE_SIZE,
    int LANG_TYPE
	);
    
void 
WritOneLine (
	char *buff,
	FILE *outHTML
	);
static 
void 
insertSort (
    char *ararylist[],
    int arraySzie
    );
    
static 
int 
queryKey (
    char *ararylist[],
    int arraySzie,
    char *key
    );
    
static void testInsertSork();
static void testQuery();


static char oneLineBuffer[2048];
static char stringBuilder[2048];
static int reamder = 0;
static char tempBuffer[1024];
static unsigned int pointer = 0;
static unsigned int size = 0;
static int maxLineChars = 0;


static void initHtmlHeader(FILE *in, FILE *out);
static void initHtmltail(FILE *in, FILE *out);




//
// This Maroc is a bad define.
//

#define WRITE(buff, size) do {				\
		fwrite(buff, 1, size, outHTML);		\
    } while(0);
		
void WriteType (
	int type,
	char *buffer,
	char *outbuffer
	);

#define CTYPE_MAROC	    (0)
#define CTYPE_KEYWD	    (1)
#define CTYPE_NUMBER	(2)
#define CTYPE_OPREATOR	(3)
#define CTYPE_STRING	(4)
#define CTYPE_COMMENT   (5)

//
//  log(n)
//
static char *C_KEY_WORDS[] = {
    "auto",     "break",    "case",     "char",     "const",    "continue",     "default",  "do",
    "double",   "else",     "enum",     "extern",   "float",    "for",          "goto",      "if",
    "int",      "long",     "register", "return",   "short",    "signed",       "sizeof",   "static",
    "struct",   "switch",   "typedef",  "union",    "unsigned", "void",         "volatile", "while",
    
//
// for c11 extends.
//
#ifdef C11_KEY_DEFINE

//
// C11 INCLUDE C99
//
#define C99_KEY_DEFINE
    "_Alignas",    "_Alignof",    "_Static_assert",    "_Noreturn",    "_Thread_local",
#endif
//
// for c99 extends.
//
#ifdef C99_KEY_DEFINE
    "inline",   "restrict", "_Bool",    "_Complex", "_Imaginary", 
#endif

//
// for MicroSolfWare C Compiler extends.
//
#ifdef MSC_EXTENDS_KEY_WORDS
    "__asm",
#endif 

//
// for LLVM Clang extends.
// 
#ifdef GNU_GCC_EXTENDS_KEY_WORDS
#endif

//
// for GNU GCC extends.
//
#ifdef CLANG_CC_EXTENDS_KEY_WORDS
#endif 

//
// for user costomer Key Words.
//
#ifdef USER_COUSTOMER_KEY_WORDS
#endif 
};
static char *CPP_KEY_WORDS[] = {
    "asm",      "do",           "if",       "return",       "typedef",
    "auto",     "double",       "inline",   "short",        "typeid"
    "bool",     "dynamic_cast", "int",      "signed",       "typename",
    "break",    "else",         "long",     "sizeof",       "union",
    "case",     "enum",         "mutable",  "static",       "unsigned",
    "catch",    "explicit",     "namespace","static_cast",  "using",
    "char",     "export",       "new",      "struct",       "virtual",
    "class",    "extern",       "operator", "switch",       "void",
    "const",    "false",        "private",  "template",     "volatile",
    "const_cast","float",       "protected","this",         "wchar_t",
    "continue", "for",          "public",   "throw",        "while",
    "default",  "friend",       "register", "true",         "delete",
    "goto",     "reinterpret_cast",    "try",
    
//
// for C++11 extends.
//
#ifdef CPP11_KEY_DEFINE
    "alignas",  "alignof",  "char16_t", "char32_t",         "constexpr", 
    "decltype", "noexcept", "nullptr",  "static_assert",    "thread_local",
#endif
//
// for MicroSolfWare C Compiler extends.
//
#ifdef MSC_EXTENDS_KEY_WORDS
    "__asm",
#endif 

//
// for LLVM Clang extends.
// 
#ifdef GNU_GCC_EXTENDS_KEY_WORDS
#endif

//
// for GNU GCC extends.
//
#ifdef CLANG_CC_EXTENDS_KEY_WORDS
#endif 

//
// for user costomer Key Words.
//
#ifdef USER_COUSTOMER_KEY_WORDS
#endif 
};
//
// JAVA_KEY_WORDS
//
static char *JAVA_KEY_WORDS[] = {
    "abstract",     "assert",       "boolean",      "break",        "byte", 
    "case",         "catch",        "char",         "class",        "const", 
    "continue",	    "default",	    "do",	        "double",	    "else",
    "enum",	        "extends",	    "final",        "finally",	    "float",
    "for",	        "goto",	        "if",	        "implements",   "import",
    "instanceof",	"int",	        "interface",    "long",	        "native",
    "new",	        "package",	    "private",	    "protected",    "public",
    "return",	    "strictfp",	    "short",	    "static",	    "super",
    "switch",	    "synchronized",	"this",	        "throw",        "throws",
    "transient",	"try",	        "void",	        "volatile",	    "while",
};

static 
void 
insertSort (
    char *ararylist[],
    int arraySzie
    )
{
    int i;
    int j;
    char *tmp;
    assert(ararylist);
    
    for (i = 0; i < arraySzie; i++) {
        tmp= ararylist[i];
#ifdef  DBG
        printf("%d need insert int\n", j);
#endif //DBG
        for (j = i; j > 0; j--) {
            if (strcmp(tmp, ararylist[j - 1]) < 0) {
                ararylist[j] = ararylist[j - 1];
            } else {
                break;
            }
        }
#ifdef  DBG
        printf("%d insert int\n", j);
#endif //DBG
        ararylist[j] = tmp;
    }
    
}

static void testInsertSork()
{
    int i;
    
    insertSort(C_KEY_WORDS, sizeof(C_KEY_WORDS) / sizeof(char *));
    
    printf("%d key words\n\n", sizeof(C_KEY_WORDS) / sizeof(char *));
    
    for (i = 0; i < sizeof(C_KEY_WORDS) / sizeof(char *); i++) {
        printf("%s\n", C_KEY_WORDS[i]);
    }
    return ;
}

//
// queryKey function return values.
//
#define STATUS_FIND     (1)
#define STATUS_NOFIND   (0)

static 
int 
queryKey (
    char *ararylist[],
    int arraySzie,
    char *key
    )
{
    int middle;
    int left;
    int right;
    int result;
    
    assert(ararylist);
    assert(key);
    
    result = 0;
    left = 0;
    right = arraySzie - 1;
    
    while (left <= right) {
        middle = (left + right) / 2;
#ifdef DBG
        printf("left : %d, right : %d, middle :  %d\n", left, right, middle);
#endif 
        result = strcmp(key, ararylist[middle]);
        if (result == 0) {
            return STATUS_FIND;
        } else if (result < 0) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return STATUS_NOFIND;
}
static void testQuery()
{
    char *key = "int";
    if (queryKey(C_KEY_WORDS, sizeof(C_KEY_WORDS) / sizeof(char *), key)) {
        printf("find key %s\n", key);
    } else {
        printf("not find key %s\n", key);
    }
    key = "Int";
    if (queryKey(C_KEY_WORDS, sizeof(C_KEY_WORDS) / sizeof(char *), key)) {
        printf("find key %s\n", key);
    } else {
        printf("not find key %s\n", key);
    }
    key = "while";
    if (queryKey(C_KEY_WORDS, sizeof(C_KEY_WORDS) / sizeof(char *), key)) {
        printf("find key %s\n", key);
    } else {
        printf("not find key %s\n", key);
    }
}

char *copyright =   "BAHT(1.0) stable version. BAHT is tools which translate source code into high light html format.\n"
                    "Copyright (C) HACKING,BOBI.  All rights reserved.\n\n"
                    "The program was written by Hacking and Bobi(HACKING AND BOBI HTML TOOLS).\n"
                    "Report bug or have a good ideal,please sent Email to maojun@whatsmath.cn.\n"
                    "This code under the ICU.996 LISENCE.\n"
                    "See LISENCE detals : https://github.com/996icu/996.ICU";
                    

char *useage = "usage : \n"
                "        baht -l langtype -t tablesize -p templateHtml -f filename\n\n"
                "eaxmple:\n"
                "        baht -l C -t 4 -p token.html -f baht.c\n\n\n";


//
// Must finished the type switch code.
//
int main(int argc, char *argv[])
{
	FILE *in;
 	FILE *out;
	FILE *inHTML;
	FILE *outHTML;
	int t1;
    int t2;
    
	char outName[256];
	char htmlName[256];
	
    
    
    
	if (argc != 9) {
		printf("%s\n\n%s\n", copyright, useage);
		return 0;
	} 
    
    if (strcmp(argv[1], "-l") || strcmp(argv[3], "-t") || 
        strcmp(argv[5], "-p") || strcmp(argv[7], "-f")) {
        printf("%s\n\n%s\n", copyright, useage);
        return 0;
    }
    t2 = atoi(argv[4]);
    
    if (t2 < 1) {
        printf("%s\n\n%s\n", copyright, useage);
        return 0;
    }
    
    if (!strcmp("JAVA", argv[2])) {
        t1 = LANG_TYPE_JAVA;
        insertSort(JAVA_KEY_WORDS, sizeof(JAVA_KEY_WORDS) / sizeof(char *));
    } else if (!strcmp("CPP", argv[2])) {
        t1 = LANG_TYPE_CPP;
        insertSort(CPP_KEY_WORDS, sizeof(CPP_KEY_WORDS) / sizeof(char *));
    } else {
        t1 = LANG_TYPE_C;
        insertSort(C_KEY_WORDS, sizeof(C_KEY_WORDS) / sizeof(char *));
    }
    
	in = fopen(argv[8], "r");
	
	
	if (in == NULL) {
		printf("open FILE %s False.\n", argv[8]);
		return 0;
	}
	inHTML = fopen(argv[6], "r");
	
	if (inHTML == NULL) {
		printf("open FILE %s False.\n", "token.html");
		return 0;
	}
	
	outName[0] = 0;
	htmlName[0] = 0;
	
	strcat(outName, argv[8]);
	strcat(htmlName, argv[8]);
	
	strcat(outName, ".txt");
	strcat(htmlName, ".html");
	
	//
	// out = fopen(outName, "w");
    // make comportable
    //
	out = (FILE *)1;
    
	if (out == NULL) {
		printf("open FILE %s False.\n", outName);
		return 0;
	}
	outHTML = fopen(htmlName, "w");
	if (outHTML == NULL) {
		printf("open FILE %s False.\n", htmlName);
		return 0;
	}
    
    
    //
    // init the key words.
    //
    
	initHtmlHeader(inHTML, outHTML);
	
	token(in, out, inHTML, outHTML, t2, t1);
	
    buildJs(outHTML);
    
	initHtmltail(inHTML, outHTML);
	
	fclose(in);
    //
	//fclose(out);
	//
    fclose(inHTML);
	fclose(outHTML);
	
	
	return 0;
}

void token (
	FILE *in, 
	FILE *out,
	FILE *inHTML,
	FILE *outHTML,
    int  TABLE_SIZE,
    int LANG_TYPE
	)
{
    table_size = TABLE_SIZE;
    lang_type = LANG_TYPE;
    
    switch (lang_type) {
        case LANG_TYPE_C : {
            table_p = C_KEY_WORDS;
            lang_table_size = sizeof(C_KEY_WORDS) / sizeof(char *);
            break;
        }
        case LANG_TYPE_CPP : {
            table_p = CPP_KEY_WORDS;
            lang_table_size = sizeof(CPP_KEY_WORDS) / sizeof(char *);
            break;
        }
        case LANG_TYPE_JAVA : {
            table_p = JAVA_KEY_WORDS;
            lang_table_size = sizeof(JAVA_KEY_WORDS) / sizeof(char *);
        }
        
    }
	assert(in && out && inHTML && outHTML);
	TokenScan(in, out, inHTML, outHTML);
    
    
}

char tokenL[2];

//
// add a char number counter.
//

#define MAX_SIZE_BUFFER	(1024)
void
TokenScan (
	FILE *in, 
	FILE *out,
	FILE *inHTML,
	FILE *outHTML
	)
{
	int buffer_one_ptr;
	int buffer_two_ptr;
	char *bufferOne;
	char *bufferTwo;
	unsigned int sizeOfRead;
	int machine_status;

    char marocFlag = 0;
	char inputc;
    
    int sumCharNo = 0;
	//
	// bufferOne for read in
	// bufferTwo for save one token
	//
    
	bufferOne = (char *)malloc(MAX_SIZE_BUFFER);
	bufferTwo = (char *)malloc(MAX_SIZE_BUFFER);
	
	assert(bufferOne && bufferTwo);
	machine_status = 0;
	buffer_two_ptr = 0;
	lineNo = 0;
    
	oneLineBuffer[0] = 0;
    stringBuilder[0] = 0;
	do {
        
		sizeOfRead = fread(bufferOne, 1, MAX_SIZE_BUFFER, in);
		buffer_one_ptr = 0;
		
		while (buffer_one_ptr < sizeOfRead) {
			inputc = bufferOne[buffer_one_ptr];
			switch (machine_status) {
				case 0 : {
					if (isalpha((int)inputc & 0xff) || inputc == '_') {
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						machine_status = 1;
                        sumCharNo++;
					} else if (isdigit((int)inputc & 0xff)) {
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						machine_status = 2;
                        sumCharNo++;
					} else if (inputc == '/') {
						machine_status = 3;
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else if (inputc == '\'') {
						machine_status = 5;
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else if (inputc == '\"') {
						machine_status = 4;
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else if (inputc == '#') {
						machine_status = 6;
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else if (inputc == '(') {
                        WriteType(CTYPE_OPREATOR, "(", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
						sumCharNo++;
					} else if (inputc == ')') {
                        WriteType(CTYPE_OPREATOR, ")", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '[') {
                        WriteType(CTYPE_OPREATOR, "[", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == ']') {
                        WriteType(CTYPE_OPREATOR, "]", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '-') {
                        WriteType(CTYPE_OPREATOR, "-", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '.') {
                        WriteType(CTYPE_OPREATOR, ".", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '!') {
                        WriteType(CTYPE_OPREATOR, "!", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '~') {
                        WriteType(CTYPE_OPREATOR, "~", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '<') {
                        WriteType(CTYPE_OPREATOR, "&lt;", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '>') {
                        WriteType(CTYPE_OPREATOR, "&gt;", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == ':') {
                        WriteType(CTYPE_OPREATOR, ":", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '\?') {
                        WriteType(CTYPE_OPREATOR, "?", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '+') {
                        WriteType(CTYPE_OPREATOR, "+", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '*') {
                        WriteType(CTYPE_OPREATOR, "*", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '%') {
                        WriteType(CTYPE_OPREATOR, "%", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '=') {
                        WriteType(CTYPE_OPREATOR, "=", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '^') {
                        WriteType(CTYPE_OPREATOR, "^", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '&') {
                        WriteType(CTYPE_OPREATOR, "&amp;", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '|') {
                        WriteType(CTYPE_OPREATOR, "|", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '\t') {
                        reamder = table_size - (sumCharNo) % table_size;
                        sumCharNo += reamder;
                        while (reamder > 0) {
                            strcat(oneLineBuffer, "&nbsp;");
                            reamder--;
                        }
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
					} else if (inputc == '{') {
                        WriteType(CTYPE_OPREATOR, "{", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '}') {
                        WriteType(CTYPE_OPREATOR, "}", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
					} else if (inputc == '\n') {
                        WritOneLine(oneLineBuffer, outHTML);
						lineNo++;
						buffer_one_ptr++;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
					} else if (inputc == ' ') {
                        strcat(oneLineBuffer, "&nbsp;");
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
                    } else if (inputc == ';') {
                        WriteType(CTYPE_OPREATOR, ";", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
                    } else if (inputc == ',') {
                        WriteType(CTYPE_OPREATOR, ",", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_one_ptr++;
                        sumCharNo++;
                    } else if (isprint((int)inputc & 0xff)) {
                        tokenL[1] = 0;
                        tokenL[0] = inputc;
                        strcat(oneLineBuffer, tokenL);
						buffer_one_ptr++;
                        sumCharNo++;
                    } else {
                        strcat(oneLineBuffer, "&nbsp;");
						buffer_one_ptr++;
                        sumCharNo++;
					}
					break;
				}
				case 1 : {
					if (isalpha((int)inputc & 0xff) || isdigit((int)inputc & 0xff) || inputc == '_') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else {
						bufferTwo[buffer_two_ptr] = 0;
                        if(queryKey(table_p, lang_table_size, bufferTwo)) {
                            WriteType(CTYPE_KEYWD, bufferTwo, stringBuilder);
                            strcat(oneLineBuffer, stringBuilder);
                            stringBuilder[0] = 0;
                        } else {
                            strcat(oneLineBuffer, bufferTwo);
                            stringBuilder[0] = 0;
                        }
						machine_status = 0;
						buffer_two_ptr = 0;
					}
					break;
				}
				case 2 : {
					if (isdigit((int)inputc & 0xff)|| isalpha((int)inputc & 0xff) || inputc =='.') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else {
						bufferTwo[buffer_two_ptr] = 0;
                        WriteType(CTYPE_NUMBER, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						machine_status = 0;
						buffer_two_ptr = 0;
					}
					break;
				}
				case 3 : {
					if (inputc == '/') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						machine_status = 7;
                        sumCharNo++;
					} else if (inputc == '*') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						machine_status = 8;
                        sumCharNo++;
					} else {
                        WriteType(CTYPE_OPREATOR, "/", stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						machine_status = 0;
						buffer_two_ptr = 0;
					}
					break;
				}
				case 4 : {
					if (inputc == '\"') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
                        if (buffer_two_ptr < 2 || bufferTwo[buffer_two_ptr-2] != '\\') {
                            bufferTwo[buffer_two_ptr] = 0;
                            WriteType(CTYPE_STRING, bufferTwo, stringBuilder);
                            strcat(oneLineBuffer, stringBuilder);
                            stringBuilder[0] = 0;
                            machine_status = 0;
                            buffer_two_ptr = 0;
                        }
					} else if (inputc == '\n') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
						lineNo++;
						if (buffer_two_ptr < 2 || bufferTwo[buffer_two_ptr-2] != '\\') {
							machine_status = 0;
						}
                        WriteType(CTYPE_STRING, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
                        WritOneLine(oneLineBuffer, outHTML);
						buffer_two_ptr = 0;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
					} else {
                        if (inputc == '<') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'l';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '>') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'g';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == ' ') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'n';
                            bufferTwo[buffer_two_ptr + 2] = 'b';
                            bufferTwo[buffer_two_ptr + 3] = 's';
                            bufferTwo[buffer_two_ptr + 4] = 'p';
                            bufferTwo[buffer_two_ptr + 5] = ';';
                            buffer_two_ptr += 6;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '\t') {
                            buffer_one_ptr++;
                            bufferTwo[buffer_two_ptr] = 0;
                            reamder = table_size - (sumCharNo) % table_size;
                            sumCharNo += reamder;
                            while (reamder > 0) {
                                strcat(bufferTwo, "&nbsp;");
                                reamder--;
                                buffer_two_ptr += 6;
                            }
                        } else {
                            bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                            sumCharNo++;
                        }
					}
					break;
				}
				case 5 : {
					if (inputc == '\'') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        if (buffer_two_ptr < 2 || bufferTwo[buffer_two_ptr-2] != '\\') {
                            bufferTwo[buffer_two_ptr] = 0;
                            WriteType(CTYPE_STRING, bufferTwo, stringBuilder);
                            strcat(oneLineBuffer, stringBuilder);
                            stringBuilder[0] = 0;
                            machine_status = 0;
                            buffer_two_ptr = 0;
                        }
                        sumCharNo++;
					} else if (inputc == '\n') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
						lineNo++;
						if (buffer_two_ptr < 2 || bufferTwo[buffer_two_ptr-2] != '\\') {
							machine_status = 0;
						}
                        WriteType(CTYPE_STRING, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
                        WritOneLine(oneLineBuffer, outHTML);
						buffer_two_ptr = 0;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
					} else {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
                        if (inputc == '<') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'l';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            
                            sumCharNo++;
                        } else if (inputc == '>') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'g';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == ' ') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'n';
                            bufferTwo[buffer_two_ptr + 2] = 'b';
                            bufferTwo[buffer_two_ptr + 3] = 's';
                            bufferTwo[buffer_two_ptr + 4] = 'p';
                            bufferTwo[buffer_two_ptr + 5] = ';';
                            buffer_two_ptr += 6;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '\t') {
                            buffer_one_ptr++;
                            bufferTwo[buffer_two_ptr] = 0;
                            reamder = table_size - (sumCharNo) % table_size;
                            sumCharNo += reamder;
                            while (reamder > 0) {
                                strcat(bufferTwo, "&nbsp;");
                                reamder--;
                                buffer_two_ptr += 6;
                            }
                        } else {
                            bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                            sumCharNo++;
                        }
					}
					break;
				}
				case 6 : {
					if (inputc == '\n') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
						lineNo++;
						if (buffer_two_ptr < 2 || bufferTwo[buffer_two_ptr-2] != '\\') {
							machine_status = 0;
						}
                        WriteType(CTYPE_MAROC, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
                        WritOneLine(oneLineBuffer, outHTML);
						buffer_two_ptr = 0;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
                        marocFlag = 0;
					} else {
                        if (inputc == '<') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'l';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                            marocFlag = 0;
                        } else if (inputc == '>') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'g';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                            marocFlag = 0;
                        } else if (inputc == ' ') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'n';
                            bufferTwo[buffer_two_ptr + 2] = 'b';
                            bufferTwo[buffer_two_ptr + 3] = 's';
                            bufferTwo[buffer_two_ptr + 4] = 'p';
                            bufferTwo[buffer_two_ptr + 5] = ';';
                            buffer_two_ptr += 6;
                            buffer_one_ptr++;
                            sumCharNo++;
                            marocFlag = 0;
                        } else if (inputc == '\t') {
                            buffer_one_ptr++;
                            bufferTwo[buffer_two_ptr] = 0;
                            reamder = table_size - (sumCharNo) % table_size;
                            sumCharNo += reamder;
                            while (reamder > 0) {
                                strcat(bufferTwo, "&nbsp;");
                                reamder--;
                                buffer_two_ptr += 6;
                            }
                            marocFlag = 0;
                        } else {
                            switch(marocFlag) {
                                case 0: {
                                    if (inputc == '/') {
                                        marocFlag = 1;
                                    } else {
                                        marocFlag = 0;
                                    }
                                    break;
                                }
                                case 1: {
                                    if (inputc == '*') {
                                        marocFlag = 2;
                                    } else if (inputc == '/') {
                                        marocFlag = 3;
                                    } else {
                                        marocFlag = 0;
                                    }
                                    break;
                                }
                            }
                            assert(buffer_two_ptr < MAX_SIZE_BUFFER);
                            bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                            sumCharNo++;
                            
                            if (marocFlag == 2) {
                                marocFlag = 0;
                                machine_status = 8;
                                bufferTwo[buffer_two_ptr - 2] = 0;
                                WriteType(CTYPE_MAROC, bufferTwo, stringBuilder);
                                strcat(oneLineBuffer, stringBuilder);
                                stringBuilder[0] = 0;
                                
                                WriteType(CTYPE_COMMENT, "/*", stringBuilder);
                                strcat(oneLineBuffer, stringBuilder);
                                stringBuilder[0] = 0;
                                
                                buffer_two_ptr = 0;
                            } else if (marocFlag == 3) {
                                marocFlag = 0;
                                machine_status = 7;
                                bufferTwo[buffer_two_ptr - 2] = 0;
                                WriteType(CTYPE_MAROC, bufferTwo, stringBuilder);
                                strcat(oneLineBuffer, stringBuilder);
                                stringBuilder[0] = 0;
                                
                                WriteType(CTYPE_COMMENT, "//", stringBuilder);
                                strcat(oneLineBuffer, stringBuilder);
                                stringBuilder[0] = 0;
                                
                                buffer_two_ptr = 0;
                            }
                        }
					}
					
					break;
				}
				case 7 : {
					if (inputc == '\n') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
						lineNo++;
                        WriteType(CTYPE_COMMENT, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
                        WritOneLine(oneLineBuffer, outHTML);
						buffer_two_ptr = 0;
						machine_status = 0;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
					} else {
                         if (inputc == '<') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'l';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '>') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'g';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == ' ') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'n';
                            bufferTwo[buffer_two_ptr + 2] = 'b';
                            bufferTwo[buffer_two_ptr + 3] = 's';
                            bufferTwo[buffer_two_ptr + 4] = 'p';
                            bufferTwo[buffer_two_ptr + 5] = ';';
                            buffer_two_ptr += 6;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '\t') {
                            buffer_one_ptr++;
                            bufferTwo[buffer_two_ptr] = 0;
                            reamder = table_size - (sumCharNo) % table_size;
                            sumCharNo += reamder;
                            while (reamder > 0) {
                                strcat(bufferTwo, "&nbsp;");
                                reamder--;
                                buffer_two_ptr += 6;
                            }
                        } else {
                            assert(buffer_two_ptr < MAX_SIZE_BUFFER);
                            bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                            sumCharNo++;
                        }
					}
					break;
				}
				case 8 : {
					if (inputc == '*') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						machine_status = 9;
                        sumCharNo++;
					} else if (inputc == '\n') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
						lineNo++;
                        WriteType(CTYPE_COMMENT, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
                        WritOneLine(oneLineBuffer, outHTML);
						buffer_two_ptr = 0;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
					} else {
                        if (inputc == '<') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'l';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '>') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'g';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == ' ') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'n';
                            bufferTwo[buffer_two_ptr + 2] = 'b';
                            bufferTwo[buffer_two_ptr + 3] = 's';
                            bufferTwo[buffer_two_ptr + 4] = 'p';
                            bufferTwo[buffer_two_ptr + 5] = ';';
                            buffer_two_ptr += 6;
                            buffer_one_ptr++;
                            sumCharNo++;
                        } else if (inputc == '\t') {
                            buffer_one_ptr++;
                            bufferTwo[buffer_two_ptr] = 0;
                            reamder = table_size - (sumCharNo) % table_size;
                            sumCharNo += reamder;
                            while (reamder > 0) {
                                strcat(bufferTwo, "&nbsp;");
                                reamder--;
                                buffer_two_ptr += 6;
                            }
                        } else {
                            assert(buffer_two_ptr < MAX_SIZE_BUFFER);
                            bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                            sumCharNo++;
                        }
					}
					break;
				}
				case 9 : {
					if (inputc == '/') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
                        WriteType(CTYPE_COMMENT, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
						buffer_two_ptr = 0;
						machine_status = 0;
                        sumCharNo++;
					} else if (inputc == '*') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                        sumCharNo++;
					} else if (inputc == '\n') {
						assert(buffer_two_ptr < MAX_SIZE_BUFFER);
						bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
						bufferTwo[buffer_two_ptr] = 0;
						lineNo++;
                        WriteType(CTYPE_COMMENT, bufferTwo, stringBuilder);
                        strcat(oneLineBuffer, stringBuilder);
                        stringBuilder[0] = 0;
                        WritOneLine(oneLineBuffer, outHTML);
						buffer_two_ptr = 0;
						machine_status = 8;
                        maxLineChars = (sumCharNo > maxLineChars) ? sumCharNo : maxLineChars;
                        sumCharNo = 0;
					} else {
                        if (inputc == '<') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'l';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                            machine_status = 8;
                        } else if (inputc == '>') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'g';
                            bufferTwo[buffer_two_ptr + 2] = 't';
                            bufferTwo[buffer_two_ptr + 3] = ';';
                            buffer_two_ptr += 4;
                            buffer_one_ptr++;
                            sumCharNo++;
                            machine_status = 8;
                        } else if (inputc == ' ') {
                            bufferTwo[buffer_two_ptr    ] = '&';
                            bufferTwo[buffer_two_ptr + 1] = 'n';
                            bufferTwo[buffer_two_ptr + 2] = 'b';
                            bufferTwo[buffer_two_ptr + 3] = 's';
                            bufferTwo[buffer_two_ptr + 4] = 'p';
                            bufferTwo[buffer_two_ptr + 5] = ';';
                            buffer_two_ptr += 6;
                            buffer_one_ptr++;
                            sumCharNo++;
                            machine_status = 8;
                        } else if (inputc == '\t') {
                            buffer_one_ptr++;
                            bufferTwo[buffer_two_ptr] = 0;
                            reamder = table_size - (sumCharNo) % table_size;
                            sumCharNo += reamder;
                            while (reamder > 0) {
                                strcat(bufferTwo, "&nbsp;");
                                reamder--;
                                buffer_two_ptr += 6;
                            }
                            machine_status = 8;
                        } else {
                            assert(buffer_two_ptr < MAX_SIZE_BUFFER);
                            bufferTwo[buffer_two_ptr++] = bufferOne[buffer_one_ptr++];
                            machine_status = 8;
                            sumCharNo++;
                            machine_status = 8;
                        }
					}
					
				}
			}
		}
	} while (sizeOfRead == MAX_SIZE_BUFFER);
	
	free(bufferOne);
	free(bufferTwo);
#ifdef DBG
	printf("LineNo : %d\n", lineNo + 1);
#endif 
	
}
static void initHtmlHeader(FILE *in, FILE *out)
{
	int flag;
	
	flag = 0;
	
	do {
		pointer = 0;
		size = fread(tempBuffer, 1, 1024, in);
		while (pointer < size) {
			if (tempBuffer[pointer] == '$') {
				flag = 1;
				break;
			}
			pointer++;
		}
		if (flag) {
			fwrite(tempBuffer, 1, pointer, out);
			break;
		} else {
			fwrite(tempBuffer, 1, size, out);
		}
		
	} while (size == 1024);
	//
	// if we don't find the $ signal. than assert false.
	//
	assert(flag);
	
}
static void initHtmltail(FILE *in, FILE *out)
{
	fwrite(&tempBuffer[pointer + 1], 1, size - pointer - 1, out);
	
	do {
		size = fread(tempBuffer, 1, 1024, in);
		fwrite(tempBuffer, 1, size, out);
	} while (size == 1024);
	
}
void WriteType (
	int type,
	char *buffer,
	char *outbuffer
	)
{
    assert(buffer != outbuffer);
    
	switch (type) {
		case CTYPE_MAROC : {
			sprintf(outbuffer, "%s%s%s", "<span class=\"maroc\">", buffer, "</span>");
			break;
		}
		case CTYPE_KEYWD : {
			sprintf(outbuffer, "%s%s%s", "<span class=\"key\">", buffer, "</span>");
			break;
		}
		case CTYPE_NUMBER : {
			sprintf(outbuffer, "%s%s%s", "<span class=\"number\">", buffer, "</span>");
			break;
		}
		case CTYPE_OPREATOR : {
			sprintf(outbuffer, "%s%s%s", "<span class=\"op\">", buffer, "</span>");
			break;
		}
		case CTYPE_STRING : {
			sprintf(outbuffer, "%s%s%s", "<span class=\"string\">", buffer, "</span>");
			break;
		}
        case CTYPE_COMMENT : {
			sprintf(outbuffer, "%s%s%s", "<span class=\"comment\">", buffer, "</span>");
			break;
        }
		default:
			break;
	}
		
}
void 
WritOneLine (
	char *buff,
	FILE *outHTML
	)
{
	char one[] = "    <div class=\"online\">";
	char two[] = "    </div>\n";
	WRITE(one, sizeof(one) - 1);
	WRITE(buff, strlen(buff));
	WRITE(two, sizeof(two) - 1);
    buff[0] = 0;
}

void buildJs (
    FILE *outHTML
    )
{
    char bu[] =    		"<script type=\"text/javascript\">\n"
                        "    var number = %d;\n"
                        "    var maxLineChars = %d;\n"
                        "    document.body.style.width = (maxLineChars * 10 + 120).toString() + 'px';\n"
                        "    window.onload = function() {\n"
                        "    numberBox = document.getElementById(\"numberBox\");\n"
                        "        for (i = 1; i <= number; i++) {\n"
                        "            node = document.createElement(\"div\");\n"
                        "            node.innerHTML = i;\n"
                        "            node.className = \"noBox\";\n"
                        "            node.id=i;\n"
                        "            numberBox.appendChild(node);\n"
                        "        }\n"
                        "    }\n"
                        "</script>\n\n";
    sprintf(oneLineBuffer, bu, lineNo + 1, maxLineChars);
    WRITE(oneLineBuffer, strlen(oneLineBuffer));
}
