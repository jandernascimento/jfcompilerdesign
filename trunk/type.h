/* constant used in the parser */


#define STRLENGTH 20	/* maximal length of an identifier */

#define PLUS 0		/* labels of the AST nodes */
#define TIMES 2
#define IDF 4
#define NUM 5
#define SEMI_COLON 6
#define NON_DEF -1
#define WORD_SIZE 1024
#define BLOC 7
#define VAR 8
#define ASSIGN 9
#define AND 10
#define WHILE 11
#define IF 12
#define THENELSE 13
#define EGAL 14
#define NOT 15
#define SUP 16
#define PROC_DECL 17
#define PROC 18
#define CALL 19
#define COMMA 20


typedef union {
    int u_int;			/* value associated to a NUM node */
    char u_str[STRLENGTH];	/* string associated to an IDF node */
} leaf ;

typedef struct node{
  int type_node ; 	/* node label */
  leaf val_node ;	/* node value, for IDF and NUM */
  struct node *fg ; 	/* left child */
  struct node *fd ;	/* right child */
} NODE;

typedef NODE *PTR_NODE ;
NODE *root ;		/* root of the AST */

