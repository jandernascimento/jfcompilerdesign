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
/** stable functions:start **/



int stable_get(list *table,char *name){

	list **original=table;
	list *search=*original;
	
	if((*original)!=NULL)
	for(;search!=NULL;search=search->next){
			//printf("Comparando [%s]==[%s]\n",name,search->name);
			if(strcmp(name,search->name)==0){
				return search->value;
			}	
	}

	 return NULL;

}

void stable_add(list *table,char *name,int value){

	list **original=table;
	list *new_position=*original;
	list *search=*original;
	
	if((*original)==NULL){
		(*original)=malloc(sizeof(list));
		(*original)->name=name;
		(*original)->value=value;
		(*original)->next=NULL;
	}else{
		for(;search!=NULL;search=search->next){
			//printf("Comparando %s e %s cmp value:%i\n",search->name,name,strcmp(name,search->name));
			if(strcmp(name,search->name)==0){
				search->value=value;
				return;
			}	
		}
		list *new_node;
		new_node=malloc(sizeof(list));
		new_node->name=name;
		new_node->value=value;
		new_node->next=NULL;
		for(;new_position->next!=NULL;new_position=new_position->next);
		new_position->next=new_node;	
	}	
}

void stable_print(list *table){
	list *head=table;
	if(head!=NULL)
	do {
		printf("Name:%s Value:%i\n",head->name,head->value);
		head=head->next;
	} while(head!=NULL);

}

void stable_sigma(list *table){
	list *head=table;
	printf("\tsigma[");
	if(head!=NULL)
	do {
		printf("%s->%i,",head->name,head->value);
		head=head->next;
	} while(head!=NULL);
	printf("]\n");
}

int stable_oper(list *table,NODE *node)
{
	if(node->type_node==NUM){
		return node->val_node.u_int;
	}else if(node->type_node==IDF){
		int val=stable_get(table,node->val_node.u_str);
		return val;		
	}else if(node->type_node==PLUS){
		return stable_oper(table,node->fg)+stable_oper(table,node->fd);		
	}else if(node->type_node==TIMES){
		return stable_oper(table,node->fg)*stable_oper(table,node->fd);		
	}else if(node->type_node==EGAL){
		return stable_oper(table,node->fg)==stable_oper(table,node->fd);		
	}else if(node->type_node==AND){
		return stable_oper(table,node->fg)&&stable_oper(table,node->fd);		
	}else if(node->type_node==SUP){
		return stable_oper(table,node->fg)>stable_oper(table,node->fd);		
	}else if(node->type_node==NOT){
		return !stable_oper(table,node->fg);		
	}
	
}

/** stable functions:end **/


/** stable stack functions:start **/

list *stable_stack[40];;
int stable_stack_size=0;

void stable_stack_push(list *pstable){

	stable_stack[stable_stack_size++]=pstable;

}

list *stable_stack_pop(){

	list *tmp=stable_stack[stable_stack_size];

	stable_stack[stable_stack_size--]=NULL;

	return tmp;


}

void stable_stack_print(){

	int x;
	for(x=0;x<stable_stack_size;x++){
		printf("Element %i in Addr: %i\n",x,(int)stable_stack[x]);
	}

}

/** stable stack functions:start **/

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
	  print_sep();
  	  pr_node(n->fg);
	  printf(", ");
	  print_sep();
  	  pr_node(n->fd);
  	  break;
    case SEMI_COLON:
  	  print_sep();
	  print_sep();
  	  pr_node(n->fg);
	  //printf(" ;\n");
	  print_sep();
	  print_sep();
  	  pr_node(n->fd);
  	  break;
    case WHILE:
  	  pr_node(n->fg);
  	  pr_node(n->fd);
  	  break;
    case IF:
	  printf("\nIf ") ;
  	  pr_node(n->fg);
	  int res=stable_oper(&stable,n->fg);
  	  if(res==1) pr_node(n->fd->fg);
	  else pr_node(n->fd->fd);
	  stable_sigma(stable);
  	  break;
    case THENELSE:
	  printf(" Then ") ;
  	  pr_node(n->fg);
	  printf(" Else ") ;
  	  pr_node(n->fd);
  	  break;
    case BLOC:
    	  pr_node(n->fg);
	  printf("\nBegin\n") ;
  	  pr_node(n->fd);
	  printf("\nEnd\n") ;
  	  break;
    case ASSIGN:
	  pr_node(n->fg);
	  printf(":=") ;
  	  pr_node(n->fd);  
  	  if(n->fd->type_node==NUM){
	  	stable_add(&stable,n->fg->val_node.u_str,n->fd->val_node.u_int);
	  }else if (n->fd->type_node==IDF){
		int val=stable_get(stable,n->fd->val_node.u_str);
	  	stable_add(&stable,n->fg->val_node.u_str,val);
	  }else if (n->fd->type_node==PLUS||n->fd->type_node==TIMES){
		int res=stable_oper(&stable,n->fd);
	  	stable_add(&stable,n->fg->val_node.u_str,res);
	  }else if (n->fd->type_node==IF){
		int res=stable_oper(&stable,n->fd);
	  	stable_add(&stable,n->fg->val_node.u_str,res);
	  }
	  stable_sigma(stable);
          break;
    case PLUS:
  	  pr_node(n->fg);
	  print_sep();
	  printf(" + ");
  	  pr_node(n->fd);
	  print_sep();
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
	  print_sep();
  	  pr_node(n->fd);
	  print_sep();
	  printf(" = ");
  	  break;
    case NOT:
  	  pr_node(n->fg);
  	  break;
    case TIMES:
   	  pr_node(n->fg);
	  print_sep();
  	  pr_node(n->fd);
	  print_sep();
	  printf(" * ");
  	  break;
    case NUM:
  	  printf("%d",(n->val_node).u_int);
  	  break;
    case IDF:
  	  printf("%s", (n->val_node).u_str);
  	  break;
    case CALL:
  	  pr_node(n->fg);
	  pr_node(n->fd);
	  break ;
    case PROC_DECL:
  	  printf("\nProc") ;
	  print_sep();
  	  print_node(n->fg);
  	  printf("(");
  	  pr_node(n->fd->fg);
  	  printf(")\n");
  	  pr_node(n->fd->fd);
	  break;
  }
  }
}

/*** BUG ***/

char *decript(int val){
  switch(val)
  {
    case COMMA:      return(","); break;
    case SEMI_COLON: return(";"); break;
    case WHILE:      return("While"); break;
    case IF:         return("If"); break;
    case THENELSE:   return("ThenElse"); break;
    case BLOC:       return("Bloc"); break;
    case ASSIGN:     return(":="); break;
    case PLUS:       return("+"); break;
    case AND:        return("and"); break;
    case SUP:        return(">"); break;
    case EGAL:       return("="); break;
    case NOT:        return("NOT"); break;
    case TIMES:      return("*"); break;
    case NUM:        return("NUM"); break;
    case IDF:        return("IDF"); break;
    case CALL:       return("Call"); break ;
    case PROC_DECL:  return("Proc"); break;
  }
}

void full_spaces(int num){
	int i;
	for(i=1;i<=num;i++)
		printf("\t");
		
}

void print_tree_other(NODE *node, int level){
	if (node != NULL){
		printf("%s\n",decript(node->type_node));
		if (node->fg != NULL){
			full_spaces(level);
			printf("LEFT ");
			level++;
			print_tree_other(node->fg,level);
			level--;
		}
		if (node->fd != NULL){
			full_spaces(level);
			printf("RIGHT ");
			level++;
			print_tree_other(node->fd,level);
			level--;
		}
	}
}

/** FIM BUG **/


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

  	//printf("\nPRINT_TREE_OTHER\n\n");
  	//print_tree_other(root,1);
  	//printf("\nEND PRINT_TREE_OTHER\n\n\n");

	pr_node(root);
	//printf("Type:%i\n",MyNode->type_node);
  	//print_node(MyNode);
	//stable_add(&stable,"x",100);
	//stable_add(&stable,"y",2);
	
	//stable_stack_push(stable);
	//stable_stack_print(stable);
	//printf("Original addr:%i\n",(int)stable);			
	stable_print(stable);
	
	/* insert here the calls to the code generation main function */
  }
} 
