/***
Authors: B. Omidvar Tehrani, J. Nascimento (MoSIG M1 Students)
Date: 11th November 2010
***/

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
	list *search=*original;
	
	//printf("Comparandoifff2 [%s]\n",name);
	if((*original)!=NULL){
		for(;search!=NULL;search=search->next){
	//			printf("Comparando1 [%s]\n",name);
	//			printf("Comparando2 [%s]\n",search->name);
				//return 1;
				if(strcmp(name,search->name)==0){
	//				printf("achou %i",search->value);
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

void stable_compare(list *table,list *other){
	list *head=table;
	list *tail=other;
	
	for(;head!=NULL;head=head->next){
		int found=1;
		for(;tail!=NULL;tail=tail->next){
			if(strcmp(head->name,tail->name)==0){
				found=0;
			}
		}

		if(found==1){
			stable_add(&stable,head->name,-1);
		}
	}

}

void stable_print(list *table){
	printf("\n<environment type=variable >\n");
	list *head=table;
	if(head!=NULL)
	do {
		if(head->value!=-1) printf("Name:%s Value:%i\n",head->name,head->value);
		head=head->next;
	} while(head!=NULL);
	printf("</environment>\n");
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
		//printf("chegou no igual\n");
		//printf("comparando [%i] [%i]",stable_oper(table,node->fg),stable_oper(table,node->fd));
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
	printf("\n<environment type=procedure >\n");
	if(head!=NULL)
	do {
		printf("Name:%s addr:%i\n",head->name,head->node);
		head=head->next;
	} while(head!=NULL);
	else printf("envp[]\n");
	printf("</environment>\n");
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
  list *customtable=NULL;
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
	  //printf(" ;\n");
	  //stable_sigma(stable);
	  print_sep();
	  print_sep();
  	  pr_node(n->fd,execute);
  	  break;
    case WHILE:
	  
	  printf("\n<while>\n");
	  
	  while(stable_oper(&stable,n->fg)){
		pr_node(n->fd);
	  }
	  //pr_node(n->fg,execute);
  	  //pr_node(n->fd,execute);
	  printf("\n</while>\n");
  	  break;
    case IF:
	  printf("\n<executing condition='") ;
  	  print_node(n->fg);
  	  pr_node(n->fg,execute);
  	  //pr_node(n->fd,0);
	  int res=stable_oper(&stable,n->fg);
	  printf("' going_to='%s'>\n",res==1?"if":"else") ;
  	  if(res==1){//go to then
		pr_node(n->fd->fg,execute);
	  } else{//go to else
		pr_node(n->fd->fd,execute);
	  }
	  printf("\n</executing>\n") ;
  	  break;
    case THENELSE:
	  printf(" Then ") ;
  	  pr_node(n->fg,execute);
	  printf(" Else ") ;
  	  //pr_node(n->fd,execute);
	  //stable_sigma(stable);
  	  break;
    case BLOC:
	  stable_print(stable);
    	  customtable=stable_duplicate(stable);
	  pr_node(n->fg,execute);
	  printf("\n");
	  //printf("\nBegin\n") ;
  	  pr_node(n->fd,execute);
	  //printf("\nEnd\n") ;
	  stable_print(stable);
	  stable_compare(stable,customtable);
  	  break;
    case ASSIGN:
	  pr_node(n->fg,execute);
	  //printf(":=") ;
  	  pr_node(n->fd,execute);  
  	  
	  if(execute){
	  	 int res=NULL;
		 if(n->fd->type_node==NUM){
	  		res=n->fd->val_node.u_int;
	  		//stable_add(&stable,n->fg->val_node.u_str,res);
	 	 }else if (n->fd->type_node==IDF){
			res=stable_oper(&stable,n->fd);
			//res=stable_get(stable,n->fd->val_node.u_str);
			//stable_add(&stable,n->fg->val_node.u_str,res);
	  	}else if (n->fd->type_node==PLUS||n->fd->type_node==TIMES){
			res=stable_oper(&stable,n->fd);
	 	 	//stable_add(&stable,n->fg->val_node.u_str,res);
	  	}else if (n->fd->type_node==IF){
			res=stable_oper(&stable,n->fd);
	  		//stable_add(&stable,n->fg->val_node.u_str,res);
	  	}
		printf("\n<assign variable=%s value=%i />\n",n->fg->val_node.u_str,res);
		stable_add(&stable,n->fg->val_node.u_str,res);
	  }
	  //stable_sigma(stable);
          printf("\n");
	  break;
    case PLUS:
  	  pr_node(n->fg,execute);
	  print_sep();
	  //printf(" + ");
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
	 // printf(" > ");
  	  break;
    case EGAL:
  	  pr_node(n->fg,execute);
	  //print_sep();
	  printf(" = ");
  	  pr_node(n->fd,execute);
	  //print_sep();
  	  break;
    case NOT:
  	  //printf("^");
	  //printf("(");
  	  pr_node(n->fg,execute);
	  //printf(")");
	  print_sep();
  	  break;	  
    case TIMES:
   	  pr_node(n->fg,execute);
	  print_sep();
  	  pr_node(n->fd,execute);
	  print_sep();
	  //printf(" * ");
  	  break;
    case NUM:
  	  //printf("%d",(n->val_node).u_int);
  	  break;
    case IDF:
  	  //printf("%s", (n->val_node).u_str);
  	  break;
    case CALL:
	  stable_print(stable);
	  printf("\n<call name=%s >\n",n->fg->val_node.u_str);
	  NODE *node=ptable_get(&ptable,n->fg->val_node.u_str); 
	  //pr_node(node->fd->fg,execute);
	  pr_node(node->fd->fd,execute);
	  stable_print(stable);
	  printf("\n</call>");
	break ;
    case PROC_DECL:
	  //printf("\nProc %s\n",n->fg->val_node.u_str) ;
	  ptable_add(&ptable,n->fg->val_node.u_str,n);
	  break;
  }
  }
}

void full_spaces(int num){
	int i;
	for(i=1;i<=num;i++)
		printf("\t");
		
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
	pr_node(root,1);
	ptable_print(ptable);
  }
} 
