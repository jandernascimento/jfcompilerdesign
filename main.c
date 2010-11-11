#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "type.h"

/*** MY TABLE **/
typedef struct list_t {

	char *name;
	int value;
	struct list_t *next;

} list;

list *stable=NULL;

void stable_init(list *table){
	//int value=0;
	//table->next=NULL;
}

void stable_add(list *table,char *name,int value){

	list *new_position=table;

	if(stable==NULL){
		stable=malloc(sizeof(list));
		stable->name=name;
		stable->value=value;
		stable->next=NULL;
	
	}else{

		list *new_node;
		new_node=malloc(sizeof(list));
		new_node->name=name;
		new_node->value=value;
		new_node->next=NULL;
		//list *old_next=table->next;
		for(;new_position->next!=NULL;new_position=new_position->next);
		new_position->next=new_node;	
		//new_node.next=old_next;
	}	
}

void stable_print(list *table){
	list *head=table;
	if(head!=NULL)
	do {
	
		printf("Name:%s Value:%i\n",head->name,head->value);
		head=head->next;
	}while(head!=NULL);

}


extern FILE *yyin;
extern print_tree() ;

int nb_lines = 1 ;

yyerror(char *s)
{
  printf ("%s at line %d\n",s,nb_lines) ;
}

usage () 
{
  	printf ("usage: while [file]\n") ;
	exit (1) ;
}

check (char *s)
{
   yyin = fopen (s, "r") ;
  if (yyin==NULL) usage() ;
}

pr_node(n)
NODE *n;
{
  if (n) {
  switch(n->type_node)
  {
    case COMMA:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case SEMI_COLON:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case WHILE:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case IF:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case THENELSE:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case BLOC:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case ASSIGN:
  	  //printf("ACHOU VAR!!!!\n");
  	  stable_add(stable,n->fg->val_node.u_str,n->fd->val_node.u_int);
  	  //stable_add(stable,"x",3);
  	  pr_node(n->fg);
  	  pr_node(n->fd);
          break;
    case PLUS:
  	 // printf("ACHOU PLUS!!!!\n");
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case AND:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case SUP:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case EGAL:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case NOT:
  	  pr_node(n->fg);
  	  break;
    case TIMES:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case NUM:
  	  //printf("%d",(n->val_node).u_int);
  	  break;
    case IDF:
  	  //printf("%s", (n->val_node).u_str);
  	  break;
    case VAR:
  	  printf("ACHOU VAR!!!!");
  	  break;
    case CALL:
  	  pr_node(n->fg);
	  pr_node(n->fd);
	  break ;
    case PROC_DECL:
  	  pr_node(n->fg);
  	  pr_node(n->fd->fg);
  	  pr_node(n->fd->fd);
	break;
  }
  }
}

main (int argc, char *argv[])
{
  int result ;

  switch (argc)
  {
    case 1 :
    	yyin = stdin ;
    	break ;
    case 2 :
    	check (argv[1]) ;
    	break ;
    default:
  	usage ();
  }

  result = yyparse() ; // call to the parser
  if (result==0){
   	//print_tree() ;
  	//print_node(root);
	//while(Droit(MyNode)!=NULL){
	//	MyNode=Droit(MyNode);
	//}
	
	pr_node(root);

	//printf("Type:%i\n",MyNode->type_node);
  	//print_node(MyNode);
	//stable_add(stable,"x",1);
	//stable_add(stable,"y",2);
	stable_print(stable);
	
	/* insert here the calls to the code generation main function */
  }
} 
