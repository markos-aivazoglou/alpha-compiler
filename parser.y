%{
		#include "intermediate.h"
		#include "tcode.h"
		int yyerror (char* yaccProvidedMessage);
		int yylex(void);
		int scope,flag1,funcflag=0;
		enum SymbolTableType gType;
		extern unsigned int currQuad;
		extern int yylineno;
		extern char* yytext;
		extern FILE* yyin;
		int breakFlag=0;
		int funcInLoop=0;
		int conFlag=0;
		int loop = 0;
		int loopcounter=0;
		symTable Table;
		struct call{
			expr* elist;
			int method;
			char* name;
		};
		struct forVal{
			int test;
			int enter;
		};
		
%}

%union{
	char* stringValue;
	int   intValue;
	double realValue;
	struct expr* exprValue;
	struct forVal* forValue;
	struct symbol* symValue;
	struct call* callValue;
	}
%start program
%expect 1


%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND OR NOT TRUE FALSE NIL
%token <intValue> INTEGER
%token <stringValue> STRING
%token <realValue> REAL
%token <stringValue> ID
%token <stringValue> LOCAL
%token LBRACKET RBRACKET LTAB RTAB LPAR RPAR SEMICOLON COMMA COLON DCOLON FULLSTOP DOTDOT COMMENT_1  COMMENT_2 COMMENT_ERROR 
%token ERROR 
%token ASSIGNMENT MULTI  DIV  MOD  EQUAL  NEQUAL  PLUSPLUS  MINUSMINUS  GREATER  LESS  GREATEROREQ  LESSOREQ NEWLINE NEWTAB


	
%right ASSIGNMENT
%left OR
%left  AND
%nonassoc EQUAL NEQUAL
%nonassoc GREATER GREATEROREQ LESS LESSOREQ
%left PLUS 
%right MINUS
%left MULTI DIV MOD
%right NOT PLUSPLUS MINUSMINUS 
%left DOTDOT
%left LTAB RTAB
%left LPAR RPAR
%nonassoc UMINUS

%type<stringValue> funcname
%type<intValue> ifprefix elseprefix whilestart whilecond N M funcbody
%type<symValue> funcprefix  
%type<callValue> methodcall normcall callsuffix
%type<exprValue> break continue returnstmt2 returnstmt objectdef objectdef1 objectdef2 indexed indexed2 indexedelem funcdef 
%type<exprValue> expr lvalue term primary assignexpr stmt stmts ifstmt for  block block2 number member const call elist while loopstmt 
%type<exprValue> idlist idlist2
%type<forValue> forprefix
%type<exprValue> elist2 
%%
program : stmts
	| /*empty*/ 			{printf("empty statement \n");}
;


stmts : stmt				{$$ = (expr*)malloc(sizeof(expr));$$=$1;}
	| stmts stmt			{$$ = (expr*)malloc(sizeof(expr));$$=$2;
					if($1->breaklist){$$->breaklist = merge($1->breaklist,$2->breaklist);}
					if($1->conlist){$$->conlist = merge($1->conlist,$2->conlist);}
}
;


stmt : expr SEMICOLON 		{$$=$1;resetTemp();}
	| ifstmt			{$$=$1;resetTemp();}
	| while 			{$$=$1;resetTemp();}
	| for   			{$$=$1;resetTemp();}
	| returnstmt 		{$$=(expr*)malloc(sizeof(expr));$$=$1;resetTemp();}
	| block 			{$$=$1;resetTemp();}
	| funcdef 			{$$=lvalue_expr($1->sym);resetTemp();/*funcflag--;*/}
	| break 			{$$=(expr*)malloc(sizeof(expr));$$=$1;resetTemp();}
	| continue 			{$$=(expr*)malloc(sizeof(expr));$$=$1;resetTemp();}
	| SEMICOLON			{$$=(expr*)malloc(sizeof(expr));resetTemp();}
	
	;
break : BREAK SEMICOLON
	{if((funcflag==0 && funcInLoop ==0)||(funcflag>0 && funcInLoop==1)){
		if(loopcounter>0){
			breakFlag++;
			$$=(expr*)malloc(sizeof(expr));
			$$->conlist = NULL;
			$$->breaklist = newlist(nextquadlabel());
			emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			else{puts("error : NOT IN LOOP");}}else puts("Cannot use break without a loop ERROR.");
}
;
continue : CONTINUE SEMICOLON
	{if((funcflag==0 && funcInLoop ==0)||(funcflag>0 && funcInLoop==1)){
		if(loopcounter>0){
			conFlag++;
			$$=(expr*)malloc(sizeof(expr));
			$$->conlist = newlist(nextquadlabel());
			$$->breaklist = NULL;
			emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			else{puts("error : NOT IN LOOP");}}else puts("Cannot use continue without a loop ERROR.");
}
;	
expr : assignexpr  			{$$=$1;}
	| term				{$$=$1;}
	| expr PLUS expr 		{$$=op_expr(Table,add,$1,$3);}
	| expr MINUS expr 		{$$=op_expr(Table,sub,$1,$3);}
	| expr MULTI expr 		{$$=op_expr(Table,mul,$1,$3);}
	| expr DIV expr		{$$=op_expr(Table,divi,$1,$3);}
	| expr MOD expr 		{$$=op_expr(Table,mod,$1,$3);}
	| expr GREATER expr 		{$$=bool_expr(Table,if_greater,$1,$3);}
	| expr GREATEROREQ expr 	{$$=bool_expr(Table,if_greatereq,$1,$3);}
	| expr LESS expr 		{$$=bool_expr(Table,if_less,$1,$3);}
	| expr LESSOREQ expr 	{$$=bool_expr(Table,if_lesseq,$1,$3);}	
	| expr EQUAL expr		{$$=bool_expr(Table,if_eq,$1,$3);} 
	| expr NEQUAL expr 		{$$=bool_expr(Table,if_noteq,$1,$3);}
	| expr AND expr		{$$=$3;
						if($1 && $3 && $1->type!=5){
							$3->truelist = merge($1->falselist,$3->falselist);
						}
						if($1->type!=5){
							$1 = bool_expr(Table,if_eq,$1,newexpr_constbool('1'));
						}


						if($3){
							$$->falselist = merge($1->falselist,$3->falselist);
						}
						else{
							$$->falselist = $1->falselist;
						}
						struct list* temp = NULL;
						temp = $$->falselist;

						/*if($3->type!=5){
							while((temp)){
								patchlabel(temp->label,nextquadlabel()+2);
								temp = temp->next;							}						  
						}*/

						while(temp){	
							patchlabel(temp->label,nextquadlabel()+1);
							temp = temp->next;
						}
						$$->truelist = $3->truelist;
						
					}
	| expr OR expr 		{$$ = $3;
						if($1 && $3 && $1->type!=5){
							$3->truelist = merge($1->truelist,$3->truelist);
						}
						if($1->type!=5){
							$1 = bool_expr(Table,if_eq,$1,newexpr_constbool('1'));
						}
						if($3){
							$$->truelist = merge($1->truelist,$3->truelist);
						}
						else{
							$$->truelist = $1->truelist;
						}
						struct list* temp = NULL;
						temp = $$->truelist;	
					
						if($3->type!=5){
							while((temp)){
								patchlabel(temp->label,nextquadlabel()+2);
								temp = temp->next;							}						  
						}
						else{
							while((temp)){
								patchlabel(temp->label,nextquadlabel()-1);
								temp = temp->next;
							}
						}
						$$->falselist = $3->falselist;
												
					}
	  			
	;

term : LPAR expr RPAR		{$$=$2;printf("(expression) \n");}
	| MINUS expr %prec UMINUS	{
						checkuminus($2);
						$$ = newexpr(arithmexpr_e);
						$$->sym = newtemp(Table);
						emit(uminus,$2,NULL,$$,-1,yylineno);
						printf("-expression");}	  
	| NOT expr			{
						$$=newexpr(boolexpr_e);
						$$->sym = newtemp(Table);
						emit(not,$2,NULL,$$,-1,yylineno);
						$$->truelist = $2->falselist;
						$$->falselist = $2->truelist;
						printf("!expression \n");
					}
	| PLUSPLUS lvalue		{
						const char * val;
						val = $2->sym->name;
						if($2->type == tableitem_e){ 
							$$ = emit_iftableitem($2);
							emit(add,$$,newexpr_constnum(1),$$,-1,yylineno);
							emit(tablesetelem,$2,$2->index,$$,-1,yylineno);
						}																					
						else{
							emit(add,$2,newexpr_constnum(1),$2,-1,yylineno);
							$$=newexpr(arithmexpr_e);
							$$->sym = newtemp(Table);
							$$=lvalue_expr($$->sym);
							emit(assign,$2,NULL,$$,-1,yylineno);
						}
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);	
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR: cant ++ a func\n");
						}
						printf("++lvalue \n");
					} 
	| lvalue PLUSPLUS		{	
						$$=newexpr(var_e);
						$$->sym = newtemp(Table);
						expr* value;
						if($1->type == tableitem_e){
							value = emit_iftableitem($1);
							emit(assign,value,NULL,$$,-1,yylineno);
							emit(add,value,newexpr_constnum(1),value,-1,yylineno);
							emit(tablesetelem,$1,$1->index,value,-1,yylineno);
						}
						 						
						else{
						
							emit(assign,$1,NULL,$$,-1,yylineno);
							emit(add,$1,newexpr_constnum(1),$1,-1,yylineno);
						}						const char * val;val = $1->sym->name;
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR:cant func ++\n");
						}
						printf("lvalue++ \n");
					}

	| MINUSMINUS lvalue  	{
						if($2->type == tableitem_e){ 
							$$ = emit_iftableitem($2);
							emit(sub,$$,newexpr_constnum(1),$$,-1,yylineno);
							emit(tablesetelem,$2,$2->index,$$,-1,yylineno);
						}
							
						else{

							emit(sub,$2,newexpr_constnum(1),$2,-1,yylineno);
							$$=newexpr(arithmexpr_e);
							$$->sym = newtemp(Table);
							emit(assign,$2,NULL,$$,-1,yylineno);
						}
						const char * val;
						val = $2->sym->name;
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR\n");
						}
						printf("--lvalue \n");
					}
	| lvalue MINUSMINUS		{

						$$=newexpr(var_e);
						$$->sym = newtemp(Table);
						expr* value;
						 if($1->type == tableitem_e){
							value = emit_iftableitem($1);
							emit(assign,value,NULL,$$,-1,yylineno);
							emit(sub,value,newexpr_constnum(1),value,-1,yylineno);
							emit(tablesetelem,$1,$1->index,value,-1,yylineno);
						}

						
						else{
						
							emit(assign,$1,NULL,$$,-1,yylineno);
							emit(sub,$1,newexpr_constnum(1),$1,-1,yylineno);
						}
						const char * val;val = $1->sym->name;
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR\n");
						}
						printf("lvalue-- \n");}
	| primary			{$$=$1;printf("primary \n");}
	;
assignexpr : lvalue ASSIGNMENT expr {

			if($1->type == tableitem_e){
				emit(tablesetelem,$1,$1->index,$3,-1,yylineno);
				$$=emit_iftableitem($1);
				$$->type = assignexpr_e;
			}
			else{
				emit(assign,$3,NULL,$1,-1,yylineno);
				$$=newexpr(assignexpr_e);
			}
			if(!$1->sym){
				printf("Den uparxei symbol    ERROR\n");
			}

			const char * val;val = $1->sym->name;
			SymbolTableEntry * temp=NULL;
			temp = lookUpScope(Table,val,USERFUNC,scope);
			if(temp){
				if(temp->type==USERFUNC)printf("ERROR\n");
				
			}
		}
;

primary : call			{$$=$1;flag1=0;}
	| lvalue			{$$ = emit_iftableitem($1);}	
	| objectdef			{$$ = $1;}
	| LPAR funcdef RPAR 		{$$ = newexpr(programfunc_e);
					 $$->sym = $2->sym;
					 }
	| const			{$$=$1;}
;	

lvalue : ID				{		
						const char* val = $1;struct symbol * sym = NULL;SymbolTableEntry *temp=NULL;
									if(lookUp(Table,val)==0){
										sym = newSymbol($1);
										sym->space = currscopespace();
										sym->offset = currscopeoffset();
										inccurrscopeoffset();
										$$ = lvalue_expr(sym);
										if(scope>0) {insert(Table,val,LOCALS,yylineno,scope);printf("new local id\n");}//use look up,make/reuse symbol,make lvalue
										else  {
											insert(Table,val,GLOBAL,yylineno,scope);printf("new global id\n");}
										temp = lookUpScope(Table,val,GLOBAL,scope);
										temp->sym = sym;
									}
									else{
											int i;
											temp = lookUpScope(Table,val,LOCALS,scope);
											for(i=scope;i>=0 && funcflag==0;i--){
												temp = lookUpScope(Table,val,LOCALS,i);
												if(temp){break;}
											}
											if(funcflag>0){
												/*temp = lookUpScope(Table,val,FORMAL,scope-1);
												if(!(temp->sym->type == FORMAL)){temp=NULL;}*/
											}
											if(!temp){
												temp = lookUpScope(Table,val,GLOBAL,0);
												if(!temp){
													printf("Cannot Access Value: %s\n",val);
												}
												else if(funcflag>0 && temp->type!=LIBFUNC && temp->type!=USERFUNC){$$=lvalue_expr(temp->sym);
													printf("Cannot Access %s in function ERROR\n",val);
													}
												else{$$=lvalue_expr(temp->sym);printf("%s - Found Globaly.\n",val);}
											}
											//else if(temp->type == LIBFUNC){printf("library function collision: %s\n",temp->cat.varVal->value);}
											//else if (temp->type == USERFUNC){printf("user function collision: %s\n",temp->cat.varVal->value);}
											else{
												if(!temp->sym){
													printf("%s Gamaei tw 8ew.     %d \n",val,yylineno);
													
												}
												else if(temp->sym->line==yylineno){
													//printf("var %s was undefined before this line ERROR\n",temp->sym->name);
												}
												$$=lvalue_expr(temp->sym);
												//printf("%s - Found in same scope.\n",val);
											} 
												
											
																				
									}
						}
				




							
	| LOCAL ID 			{	
						
						const char *val=$2;
						struct symbol * sym =NULL; 
						SymbolTableEntry *temp=NULL;
						if(scope>0){
							
							if(lookUp(Table,val)==1)
								temp = lookUpScope(Table,val,LOCALS,scope);
							if(temp){
								if(temp->type == USERFUNC){
									printf("user function collision: %s\n",temp->cat.varVal->value);
								}
								else{
									printf("%s - Found localy\n",val);
									$$ =lvalue_expr(temp->sym);
								}
							}
							else{
								sym = newSymbol($2);
								sym->space = currscopespace();
								sym->offset = currscopeoffset();
								inccurrscopeoffset();
								insert(Table,val,LOCALS,yylineno,scope);
								temp = lookUpScope(Table,val,LOCALS,scope);
								temp->sym = sym;
								$$= lvalue_expr(temp->sym);
							}
							printf("local id \n");
						}
						else{
							if(lookUp(Table,val)==0){insert(Table,val,GLOBAL,yylineno,0);
								sym = newSymbol($2);
								sym->space = currscopespace();
								sym->offset = currscopeoffset();
								inccurrscopeoffset();
								temp = lookUpScope(Table,val,GLOBAL,0);
								temp->sym = sym;
								if(temp->sym){printf("clein2\n");}
								$$= lvalue_expr(temp->sym);}
							else{printf("%s - Found Globally.\n",val);
								temp = lookUpScope(Table,val,GLOBAL,0);
								$$ = lvalue_expr(temp->sym);
							}
						}
					}
	
	| DCOLON ID			{		
						const char* val=$2; 
						if (lookUp(Table,val)== 0){
							printf("no %s as global variable\n",val);	
						}
						else{
							SymbolTableEntry *temp;
							temp = lookUpScope(Table,val,GLOBAL,0);
							if(temp == NULL){
								printf("no %s as global variable\n",val);
							}
							else{
								printf("Global variable %s found\n",val);
							}
							$$=lvalue_expr(temp->sym);
							printf("::id \n");
						}
					}
	| member			{
						$$=$1;printf("member \n");
					}
;

	
member : lvalue FULLSTOP ID		{
					$$ = member_item($1,$3);
				}
	| lvalue LTAB expr RTAB	{
					$1 = emit_iftableitem($1);
					$$ = newexpr(tableitem_e);
					$$->sym = $1->sym;
					$$->index = $3;}
	| call FULLSTOP ID		{
					printf("NEEDS TO BE COMPLETEEED \n");}
	| call LTAB expr RTAB	{
					printf("call [expression]\n");}
;	



call : call LPAR elist RPAR		{$$ = make_call($$,$3);
					}
	
	| lvalue{const char *  val;val=$1->sym->name;
			int i = scope;
			printf("lval name = %s\n",$1->sym->name);
			SymbolTableEntry * temp=NULL;
			if(lookUp(Table,val)==0 && $1->sym->type!=LIBFUNC){
				printf("%s undefined reference\n",val);
			}
			else{
				while(1){
					temp = lookUpScope(Table,val,USERFUNC,i);
					if(temp){
						if((temp->type==USERFUNC) || (temp->type==LIBFUNC)){ break;}
						else {temp=NULL;}
					}
					if(i==-1)break;
					i--;
				}
				if(temp && funcflag==0){printf("%s refers to function found in %d scope\n",val,i);}
				else{printf("%s undefined reference\n",val);}
			}	
	} callsuffix { if($3->method == 1 && $3->elist){
			expr* self = $1;
			$1 = emit_iftableitem(member_item(self,$3->name));//TODO : ADD FRONT
			$3->elist->next = (expr*)malloc(sizeof(expr*));
			$3->elist->next = self;
			}
			$$ = make_call($1,$3->elist);
	}		
	| LPAR funcdef RPAR LPAR elist RPAR 	{
							expr* func;
							func = newexpr(programfunc_e);
							func->sym = $2->sym;
							$2 = make_call(func,$5);
							}
;	


callsuffix : normcall		{$$=$1;}
	| methodcall			{$$=$1;}
;	


normcall : LPAR elist RPAR 		{
					$$->elist = $2;
					$$->method = 0;
					$$->name = "";
				}
;


methodcall : DOTDOT ID LPAR elist RPAR		{
		$$->elist = $4;
		$$->method = 1;
		$$->name = $2;
	}
;


elist :  expr elist2	{		
					if(!$2){
						$$ = (expr*)malloc(sizeof(expr));
						$$->sym = (struct symbol*)malloc(sizeof(struct symbol));
						$1->next = NULL;
						$$ = $1;
					}
					else{	 
						expr* tmp;
						tmp = $$;
						while(tmp->next){
							tmp=tmp->next;
							
						}
						expr* temp2;
						temp2 = $2;
						while(temp2->next){
							temp2=temp2->next;
							
						}
						temp2->next = $1;
						$1->next = NULL;
						$$ = reverse($2);
					}
				}
	|/*empty*/	{$$ = (expr*)malloc(sizeof(expr));$$=NULL;}
;


elist2 : COMMA expr elist2		{expr * temp=NULL;
					temp = $3;
					if(temp){
						while(temp->next){
							temp = temp->next;
						}
						temp->next = $2;
						$$ = $3;
					}
					else{
						$$=$2;
					}
				}
	|/*empty*/{$$=NULL;}
	
objectdef : objectdef1	{$$=$1;}
		|objectdef2   {$$=$1;}
;



objectdef1: LTAB elist RTAB{	expr* t;
					t = newexpr(newtable_e);
					t->sym = newtemp(Table);
					printf("table name = %s\n",t->sym->name);
					emit(tablecreate,t,NULL,NULL,-1,yylineno);
					int i =0;
					while($2){
						emit(tablesetelem,t,NULL,$2,-1,yylineno);
						$2 = $2->next;
					}
					$$=t;
}
;
objectdef2 : LTAB indexed RTAB{
					expr* t;
					t = newexpr(newtable_e);
					t->sym = newtemp(Table);					
					emit(tablecreate,NULL,NULL,t,-1,yylineno);
					expr* tempHead;
					tempHead = $2;
					tempHead = reverse(tempHead);
					while (tempHead){
						
						emit(tablesetelem,tempHead,tempHead->index,t,-1,yylineno);
						tempHead = tempHead->next;
					}
					$$ = t;
		

					
}
;
	

indexed : indexedelem indexed2	{
					expr* tempHead;
					tempHead = $2;
					if(tempHead){
						while(tempHead->next){
							tempHead = tempHead->next;
							
						}
						tempHead->next= $1;
						tempHead->next->next = NULL;
						$$ = $2;
					}
					else{
						$$=$1;
						$$->next = NULL;
					}
}		
;


indexed2 : COMMA indexedelem indexed2	{
					$$ = (expr*)malloc(sizeof(expr));
					expr* tempHead;
					tempHead = $3;
					if(tempHead){
						while(tempHead->next){
							tempHead = tempHead->next;
						}
						tempHead->next = $2;
						tempHead->next->next=NULL;
						$$=$3;
					}
					else{
						$$=$2;
						$$->next = NULL;
					}
}
	| /*empty*/ 			{$$=NULL;}
;


indexedelem : LBRACKET expr COLON expr RBRACKET {
					$$= newexpr(tableitem_e);
					$2->index = $4;
					$$ = $2;
					$$->next = NULL;

}
;


block : LBRACKET{scope++;} block2  RBRACKET	{$$=$3;hide(Table,scope);printf("{...}\n");scope--;}
;
	

block2 : stmt block2		{$$=$1;$$->breaklist = merge($1->breaklist,$2->breaklist);$$->conlist = merge($1->conlist,$2->conlist);printf("{statement}\n");}
	|				{$$=(expr*)malloc(sizeof(expr));$$->breaklist = NULL;$$->conlist=NULL;printf("{}\n");}
;
		


funcdef : funcprefix funcargs funcbody {
			exitscopespace();
			$1->totallocals = $3;
			restorecurrscopeoffset(offsetPop(currscopeoffset()));
			$$ = newexpr(programfunc_e);
			$$->sym = $1;
			emit(funcend,NULL,NULL,lvalue_expr($1),-1,yylineno);
			funcflag--;
			if(funcInLoop==1)funcInLoop=0;
}
;



funcprefix : FUNCTION{funcflag++;} funcname{scope++;
		$$ = newSymbol($3);
		$$->type = programfunc_s;
		$$->iaddress = nextquadlabel();
		emit(funcstart,NULL,NULL,lvalue_expr($$),-1,yylineno);
		if(!isFull()){
			offsetPush(currscopeoffset());
		}
		enterscopespace();
		resetformalargsoffset();
		SymbolTableEntry * temp = NULL;
		temp = lookUpScope(Table,$3,GLOBAL,scope-1);
		if(temp)
		temp->sym = $$;
}
;
funcargs : LPAR idlist RPAR {scope--;
					enterscopespace();
					resetfunctionlocalsoffset();	
				}
;
funcbody : block {	
			$$ = currscopeoffset();
			exitscopespace();
		
			}
;











funcname :   ID     	{$$=$1;const char* val = $1;


				SymbolTableEntry * temp=NULL;
				temp = lookUpScope(Table,val,USERFUNC,scope);
				if(temp){
					if((temp->type == LOCALS)||(temp->type == FORMAL)||(temp->type == GLOBAL)){
						printf("REDEFINITION OF THIS NAME %s \n",temp->cat.varVal->value);
					}
					else{
						printf("%s() already exists in same scope\n",val);
					}
				}
				else{
					temp = lookUpScope(Table,val,USERFUNC,0);
					if(temp){
						if(temp->type == LIBFUNC){
							printf("error: %s function overrides library function\n",val);
						}
					}
					else{
						
						insert(Table,val,USERFUNC,yylineno,scope);
					}
				}
			}	
	|/*empty*/ {$$ = funcNameGen();

			insert(Table,$$,USERFUNC,yylineno,scope);


					}
	;


const : number			{$$=$1;}
	| STRING			{$$=newexpr_conststring($1);printf("STRING \n");}
	| NIL				{$$=newexpr_constbool(-1);printf("NIL \n");}
	| TRUE				{$$ = newexpr_constbool(1);printf("TRUE \n");}
	| FALSE			{$$ = newexpr_constbool(0);printf("FALSE \n");}
;	


number : INTEGER			{$$=newexpr_constnum($1);printf("INTEGER \n");}
	| REAL				{$$=newexpr_constnum($1);printf("REAL \n");}
;


idlist : ID	idlist2{
						const char* val = $1;
			
						struct symbol* sym;						
						sym = newSymbol($1);
						sym->space = currscopespace();
						sym->offset = currscopeoffset();
						inccurrscopeoffset();
						$$ = lvalue_expr(sym);
					if($2){
						expr* temp2;
						temp2 = $2;
						while(temp2->next){
							temp2=temp2->next;
						}
						temp2->next = lvalue_expr(sym);
						$2->next->next = NULL;
						$$ = reverse($2);
					}
			insert(Table,val,FORMAL,yylineno,scope);
SymbolTableEntry *temp=NULL;			
temp = lookUpScope(Table,val,GLOBAL,scope);
temp->sym = sym;
			printf("new formal id with name %s\n",val);
			
		}	
		|{$$=(expr*)malloc(sizeof(expr));$$=NULL;}/*empty*/
;


idlist2 : 	COMMA ID idlist2 {const char* val = $2;
					expr * temp=NULL;
					temp = $3;
					struct symbol* sym;						
					sym = newSymbol($2);
					sym->space = currscopespace();
					sym->offset = currscopeoffset();
					inccurrscopeoffset();
					$$ = lvalue_expr(sym);

					if(temp){
						while(temp->next){
							temp = temp->next;
						}
						temp->next = lvalue_expr(sym);
						$3->next->next = NULL;
						$$ = $3;
					}
	    				insert(Table,val,FORMAL,yylineno,scope);
					SymbolTableEntry *temp2=NULL;			
					temp2 = lookUpScope(Table,val,GLOBAL,scope);
					temp2->sym = sym;
		    	}		
	|{$$=(expr*)malloc(sizeof(expr));$$=NULL;}	/*empty*/
	;	
	


ifstmt : ifprefix stmt elseprefix stmt{$$=$2;
			$$=(expr*)malloc(sizeof(expr));
			
			if($2 && $2->breaklist){
				if($4){puts("NAI");
					$$->breaklist=merge($2->breaklist,$4->breaklist);}
				else
					$$->breaklist = $2->breaklist;
			}
			else if($4 && $4->breaklist){
				if($2)
					$$->breaklist = merge($4->breaklist,$2->breaklist);
				else
					$$->breaklist = $4->breaklist;
			}
			else{
				$$->breaklist = NULL;
			}
			if($2 && $2->conlist){
				if($4)
					$$->conlist=merge($2->conlist,$4->conlist);
				else
					$$->conlist = $2->conlist;	
			}
			else if($4 && $4->conlist){
				if($2)
					$$->conlist = merge($4->conlist,$2->conlist);
				else
					$$->conlist = $4->conlist;
			}
			else{
				$$->conlist = NULL;
			}
			patchlabel($1,$3+1);
			patchlabel($3,nextquadlabel());
			}
	| ifprefix stmt{$$=$2;
				patchlabel($1,nextquadlabel());}
;


ifprefix : IF LPAR expr RPAR{
		emit(if_eq,$3,newexpr_constbool('1'),NULL,nextquadlabel()+2,yylineno);
		$$ = nextquadlabel();
		emit(jump,NULL,NULL,NULL,-1,yylineno);
					}
;







elseprefix : ELSE  			{
					$$ = nextquadlabel();
					emit(jump,NULL,NULL,NULL,-1,yylineno);
		}
;
	

while : whilestart whilecond loopstmt M{emit(jump,NULL,NULL,NULL,$1,yylineno);

					patchlabel($2,nextquadlabel());

					struct list* temp = $3->breaklist;
					while(temp){puts("BREAK awpignaoignaga");
						patchlabel(temp->label,nextquadlabel());
						temp = temp->next;
					}

					temp = $3->conlist;
					/*while(temp){
						patchlabel(temp->label,$1);
						temp = temp->next;
					}*/


					$$ = (expr*)malloc(sizeof(expr));




					/*if($3->breaklist){
					if(breakFlag!=0)
						patchlabel($3->breaklist->label,nextquadlabel());
					}
					if ($3->conlist){
					if(conFlag!=0)
						patchlabel($3->conlist->label,$1);
					}*/
					patchlabel($4,$1);
					puts("while done");
				}
;


whilestart : WHILE {
			$$ = nextquadlabel();
			} 
;


whilecond : LPAR expr RPAR{	
				 emit(if_eq,$2,newexpr_constbool('1'),NULL,nextquadlabel()+2,yylineno);
				 $$ = nextquadlabel();
				 emit(jump,NULL,NULL,NULL,-1,yylineno);	

				}




for : forprefix N elist RPAR N{} loopstmt N{
	struct list* temp = $7->breaklist;
	while(temp){
		patchlabel(temp->label,nextquadlabel());
		temp = temp->next;
	}
	temp = $7->conlist;
	while(temp){
		patchlabel(temp->label,$2+1);
		temp = temp->next;
	}
	
	patchlabel($1->enter,$5+1);
	patchlabel($2,nextquadlabel());
	patchlabel($5,$1->test);
	patchlabel($8,$2+1);
}

forprefix : FOR LPAR elist SEMICOLON M expr SEMICOLON{
		$$ =(struct forVal*)malloc(sizeof(struct forVal));
		$$->test = $5;
		$$->enter = nextquadlabel();
		emit(if_eq,$6,newexpr_constbool('1'),NULL,0,yylineno);
}

N : {$$ = nextquadlabel();emit(jump,NULL,NULL,NULL,0,yylineno);}

M : {$$ = nextquadlabel();}


loopstmt : loopstart stmt loopend{$$ = (expr*)malloc(sizeof(expr));$$ = $2;if(funcflag>0)funcInLoop=1;}
loopstart :  {++loopcounter;}
loopend   :  {--loopcounter;}

returnstmt : RETURN returnstmt2 SEMICOLON	{$$=(expr*)malloc(sizeof(expr));$$=$2;printf("RETURN\n");if(funcflag==0){printf("Cannot use return while not in function ERROR\n");}}
;

returnstmt2 : expr			{if(funcflag>0){$$=(expr*)malloc(sizeof(expr));$$=$1;emit(ret,NULL,NULL,$1,-1,yylineno);}else{printf("Cannot use return outside a function ERROR\n");}}
	|	{if(funcflag>0){$$=(expr*)malloc(sizeof(expr));emit(ret,NULL,NULL,NULL,-1,yylineno);}else{printf("Cannot use return outside a function ERROR\n");}}
	;
	
%%	
	
int yyerror (char* yaccProvidedMessage){
	fprintf(stderr, "%s: at line %d, before token: %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");
}	
	
	
	
	
int main(int argc, char **argv)
{
	if(argc>1)
	{
		yyin=fopen(argv[1], "r");
		if(yyin==NULL)
		{
			fprintf(stderr, "Cannot open file.\n");
			return -1;
		}
	}
	else
	{
		yyin=stdin;
	}
		initFuncArray();
		Table = createTable();
		insert(Table,"print",LIBFUNC,0,0);
		insert(Table,"input",LIBFUNC,0,0);
		insert(Table,"objectmemberkeys",LIBFUNC,0,0);
		insert(Table,"objecttotalmembers",LIBFUNC,0,0);
		insert(Table,"objectcopy",LIBFUNC,0,0);
		insert(Table,"totalarguements",LIBFUNC,0,0);
		insert(Table,"arguement",LIBFUNC,0,0);
		insert(Table,"typeof",LIBFUNC,0,0);
		insert(Table,"strtonum",LIBFUNC,0,0);
		insert(Table,"sqrt",LIBFUNC,0,0);
		insert(Table,"cos",LIBFUNC,0,0);
		insert(Table,"sin",LIBFUNC,0,0);

		yyparse();
		
		

	 	 
	    printTabol(Table);
	if(nextquadlabel()){
	    //printQuads2();
	    printQuads();
	}
	generate();
	printTables();
	printInstructions();
	printTables_tofile();
	return 0;
}
