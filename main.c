#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "type.h"

/*** TABLE for variable **/
typedef struct list_t {

	char *name;
	int value;
	struct list_t *next;

} list;


/*** TABLE for procedure **/
typedef struct list_p {

	char *name;
	NODE *node;
	struct list_p *next;

} listp;


list *stable=NULL;
listp *ptable=NULL;
/** stable functions:start **/



int stable_get(list *table,char *name){



	list **original=table;
	list *search=table;//*original;
	
	//printf("Comparandoifff2 [%s]\n",table->name);
	if((*original)!=NULL){
		for(;search!=NULL;search=search->next){
				//printf("Comparando1 [%s]\n",name);
				//printf("Comparando2 [%s]\n",search->name);
return 1;
				if(strcmp(name,search->name)==0){
					return search->value;
				}	
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

list* stable_duplicate(list *table){
	list *head=table;
	list *newlist=NULL;
	
	for(;head!=NULL;head=head->next){
		stable_add(&newlist,head->name,head->value);
	}

	return newlist;

}
void stable_print(list *table){
	printf("\n\n/**** List of Variable ****/\n");
	list *head=table;
	if(head!=NULL)
	do {
		printf("Name:%s Value:%i\n",head->name,head->value);
		head=head->next;
	} while(head!=NULL);

}

void stable_sigma(list *table){
	list *head=table;
	printf("sigma[");
	if(head!=NULL)
	do {
		printf("%s->%i,",head->name,head->value);
		head=head->next;
	} while(head!=NULL);
	printf("]");
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

/** ptable functions:begin **/

void ptable_add(listp *table,char *name,NODE *value){

	listp **original=table;
	listp *new_position=*original;
	listp *search=*original;
	
	if((*original)==NULL){
		(*original)=malloc(sizeof(list));
		(*original)->name=name;
		(*original)->node=value;
		(*original)->next=NULL;
	}else{
		for(;search!=NULL;search=search->next){
			//printf("Comparando %s e %s cmp value:%i\n",search->name,name,strcmp(name,search->name));
			if(strcmp(name,search->name)==0){
				search->node=value;
				return;
			}	
		}
		listp *new_node;
		new_node=malloc(sizeof(list));
		new_node->name=name;
		new_node->node=value;
		new_node->next=NULL;
		for(;new_position->next!=NULL;new_position=new_position->next);
		new_position->next=new_node;	
	}	
}

NODE* ptable_get(listp *table,char *name){

	listp **original=table;
	listp *search=*original;
	if((*original)!=NULL)
	for(;search!=NULL;search=search->next){
			//printf("Comparando [%s]==[%s]\n",name,search->name);
			if(strcmp(name,search->name)==0){
				return search->node;
			}
	}
	return NULL;

}

void ptable_print(listp *table){
	listp *head=table;
	printf("\n\n/**** List of procedure ****/\n");
	if(head!=NULL)
	do {
		printf("Name:%s addr:%i\n",head->name,head->node);
		head=head->next;
	} while(head!=NULL);
	else printf("envp[]\n");

}
/** ptable functions:end **/

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

pr_node(n,execute)
NODE *n;
int execute;
{
  if (n) {
  switch(n->type_node)
  {
    case COMMA:
	  print_sep();
  	  pr_node(n->fg,execute);
	  printf(", ");
	  print_sep();
  	  pr_node(n->fd,execute);
  	  break;
    case SEMI_COLON:
  	  print_sep();
	  print_sep();
  	  pr_node(n->fg,execute);
	  printf(" ;");
	  stable_sigma(stable);
	  printf("\n");
	  print_sep();
	  print_sep();
  	  pr_node(n->fd,execute);
  	  break;
    case WHILE:
  	  printf("\nWhile\n") ;
	  printf("(");
  	  pr_node(n->fg,execute);
	  printf(")");
	  printf("\nDo\n") ;
  	  pr_node(n->fd,execute);
	  printf("\nOd\n") ;
  	  break;
    case IF:
	  printf("\n If ") ;
  	  pr_node(n->fg,execute);
  	  pr_node(n->fd,0);
	  int res=stable_oper(&stable,n->fg);
  	  if(res==1){//go to then
		pr_node(n->fd->fg,execute);
		//pr_node(n->fd->fd,0);
	  } else{//go to else
		//pr_node(n->fd->fg,0);
		pr_node(n->fd->fd,execute);
	  }
  	  break;
    case THENELSE:
	  printf(" Then ") ;
  	  pr_node(n->fg,execute);
	  printf(" Else ") ;
  	  //pr_node(n->fd,execute);
	  //stable_sigma(stable);
  	  break;
    case BLOC:
    	  pr_node(n->fg,execute);
	  printf("\nBegin\n") ;
  	  pr_node(n->fd,execute);
	  printf("\nEnd\n") ;
  	  break;
    case ASSIGN:
	  pr_node(n->fg,execute);
	  printf(":=") ;
  	  pr_node(n->fd,execute);  
  	  
	  if(execute){
	  if(n->fd->type_node==NUM){
	  	stable_add(&stable,n->fg->val_node.u_str,n->fd->val_node.u_int);
	  }else if (n->fd->type_node==IDF){
		stable_print(stable);
		int val=stable_get(stable,n->fd->val_node.u_str);
		stable_add(&stable,n->fg->val_node.u_str,val);
	  }else if (n->fd->type_node==PLUS||n->fd->type_node==TIMES){
		int res=stable_oper(&stable,n->fd);
	  	stable_add(&stable,n->fg->val_node.u_str,res);
	  }else if (n->fd->type_node==IF){
		int res=stable_oper(&stable,n->fd);
	  	stable_add(&stable,n->fg->val_node.u_str,res);
	  }}
	  //stable_sigma(stable);
          break;
    case PLUS:
  	  pr_node(n->fg,execute);
	  print_sep();
	  printf(" + ");
  	  pr_node(n->fd,execute);
	  print_sep();
  	  break;
    case AND:
  	  pr_node(n->fg,execute);
	  print_sep();
  	  pr_node(n->fd,execute);
	  print_sep();
  	  printf(" and ");
	  break;
    case SUP:
  	  pr_node(n->fg,execute);
	  print_sep();
  	  pr_node(n->fd,execute);
	  print_sep();
	  printf(" > ");
  	  break;
    case EGAL:
  	  pr_node(n->fg,execute);
	  print_sep();
	  printf(" = ");
  	  pr_node(n->fd,execute);
	  print_sep();
  	  break;
    case NOT:
  	  printf("^");
	  printf("(");
  	  pr_node(n->fg,execute);
	  printf(")");
	  print_sep();
  	  break;	  
    case TIMES:
   	  pr_node(n->fg,execute);
	  print_sep();
  	  pr_node(n->fd,execute);
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
	  printf("Call ");
  	  pr_node(n->fg,execute);
	  printf("(");
	  pr_node(n->fd,execute);
	  printf(")\n");  	
	  NODE *node=ptable_get(&ptable,n->fg->val_node.u_str); 
	  pr_node(node->fd->fg,execute);
	  //stable_print(stable);
	  pr_node(node->fd->fd,execute);
	  break ;
    case PROC_DECL:
	  printf("\nProc %s\n",n->fg->val_node.u_str) ;
	  ptable_add(&ptable,n->fg->val_node.u_str,n);
	  //printf("\nProc") ;
	  //print_sep();
  	  //pr_node(n->fg,0);
  	  //printf("(");
  	  //pr_node(n->fd->fg,0);
  	  //printf(")\n");
  	  //pr_node(n->fd->fd,0);
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
  	//print_tree_other(root,1);

	pr_node(root,1);
	//print_node(root);
	//stable_add(&stable,"x",100);
	//stable_add(&stable,"y",2);
	
	//stable_stack_push(stable);
	//stable_stack_print(stable);
	
	stable_print(stable);

	//printf("enderecos fg:%i fd:%i\n",(int)root->fg,(int)root->fd);
	//ptable_add(&ptable,"principal",root);
	
	ptable_print(ptable);
	
	/* insert here the calls to the code generation main function */
  }
} 
