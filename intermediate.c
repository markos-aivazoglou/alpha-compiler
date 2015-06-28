#include "intermediate.h"
#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

unsigned int programVarOffset  = 0;
unsigned int functionLocalOffset = 0;
unsigned int formalArgOffset = 0;
unsigned int scopeSpaceCounter = 1;
unsigned int tempCounter = 0;
char* tempArray[] ={"_t0","_t1","_t2","_t3","_t4","_t5","_t6","_t7","_t8","_t9","_t10","_t11","_t12","_t13","_t14","_t15","_t16","_t17","_t18","_t19","_t20","_t21","_t22","_t23","_t24"};
char* funcArray[25];
char* funcSupport[] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24"};
int i;
quad*	quads = (quad*) 0;
unsigned int total = 0;
unsigned int  currQuad = 0;

void initFuncArray(){
	for(i=0; i<25; i++){
		funcArray[i] = "";
	}
}



expr* emit_iftableitem(expr* e){
	expr* result;
	if(e->type != tableitem_e){
		return e;
	}
	else{		
	   	result = newexpr(var_e);
		result->sym = newtemp(Table);
		emit(tablegetelem,e,e->index,result,-1,yylineno);
	}
	return result;
}

unsigned int istempname(char* s){ //anagnwrish onomatwn temp
	return *s == '_';
}

unsigned int istempexpr(expr* e){
	return ((e->sym) && (e->sym->type == var_s) && (istempname(e->sym->name)));//change 0 to var_s
}

expr* newexpr_constnum(double i){
	expr* e = newexpr(constnum_e);
	e->numConst = i;
	return e;
}


expr* newexpr (enum expr_t t){
	expr* e = (expr*) malloc(sizeof(expr));
	memset(e,0,sizeof(expr));
	e->type = t;
	return e;
}



expr* newexpr_conststring(char* s){
	expr* e = newexpr(conststring_e);
	e->strConst = strdup(s);
	return e;
}

expr* newexpr_constbool(unsigned char c){
	expr* e = newexpr(constbool_e);
	e->boolConst = c;
	return e;
}

expr* reverse(expr* head){
	expr* reversed = NULL;
	expr* temp1 = NULL;
	expr* temp2 = NULL;
	expr* delete = NULL;
	while(head){
		temp1 = head;
		delete = temp1;
		while(temp1->next){
			
			delete = temp1;
			temp1 = temp1->next;
		}
		if(head->next){
			delete->next = NULL;
		}
		else{
			head = NULL;
		}
		if(reversed){
			temp2 = reversed;
			while(temp2->next){
				temp2 = temp2->next;
			}
			temp2->next = temp1;
		}
		else{
			reversed = temp1;
		}
	}
	return reversed;
}

expr* lvalue_expr(struct symbol* sym){
	
	assert(sym);
	expr* e = (expr*) malloc(sizeof(expr));
	memset(e,0,sizeof(expr));

	e->next = (expr*) 0;
	e->sym = sym;

	switch (sym->type) {
		case var_s		: e->type = var_e; break;
		case programfunc_s 	: e->type = programfunc_e; break;
		case libraryfunc_s	: e->type = libraryfunc_e; break;
		default: assert(0);
	}
	return e;
}

void resetformalargsoffset(void){
	formalArgOffset = 0;
}

void resetfunctionlocalsoffset(void){
	functionLocalOffset = 0;
}


void restorecurrscopeoffset(unsigned n) {
	switch (currscopespace()) {
		case programvar 	: programVarOffset = n; break;
		case functionlocal 	: functionLocalOffset = n; break;
		case formalarg	: formalArgOffset = n; break;
		default: assert(0);
	}
}

unsigned int nextquadlabel (void){
	return currQuad;
}

void patchlabel (unsigned int quadNo, unsigned int label){
	
	assert(quadNo < currQuad);
	quads[quadNo].label = label;
}

void expand (void){
	assert(total==currQuad);
	quad* p =(quad*)malloc (NEW_SIZE);
	if (quads) {
		memcpy(p,quads,CURR_SIZE);
		free(quads);
	}
	quads = p;
	total += EXPAND_SIZE;
}

void emit(enum iopcode op,expr* arg1,expr* arg2,expr* result,unsigned int label,unsigned int line){
	
	if(currQuad == total){
		expand();}
	quad* p   = quads+currQuad++;
	p->arg1   = arg1;
	p->arg2   = arg2;
	p->result = result;
	p->label  = label;
	p->line   = line;
	p->op 	   = op;
	// p->taddress = 0;
	if(!arg1){
		p->arg1 = (expr*)malloc(sizeof(expr));
		p->arg1->type = nil_e;
	}
	if(!arg2){
		p->arg2 = (expr*)malloc(sizeof(expr));
		p->arg2->type = nil_e;
	}
	if(!result){
		p->result = (expr*)malloc(sizeof(expr));
		p->result->type = nil_e;
	}
}

enum scopespace_t currscopespace(void){			//3h fash
	if (scopeSpaceCounter == 1 )
		return programvar;
	else{
		if ( scopeSpaceCounter % 2 == 0)
			return formalarg;
		else
			return functionlocal;
	}
}

unsigned int currscopeoffset(void){				//3h fash
	switch (currscopespace()) {
		case programvar	: return programVarOffset;
		case functionlocal	: return functionLocalOffset;
		case formalarg	: return formalArgOffset;
		default:assert(0);
	}
}


void inccurrscopeoffset(void){					//3h fash
	switch (currscopespace()) {
		case programvar	: ++programVarOffset; break;
		case functionlocal	: ++functionLocalOffset; break;
		case formalarg	: ++formalArgOffset; break;
		default:assert(0);
	}

}

void enterscopespace(void){						//3h fash
	++scopeSpaceCounter;
}

void exitscopespace(void){					//3h fash
	assert(scopeSpaceCounter>1); --scopeSpaceCounter;
}

expr* op_expr(symTable Table,enum iopcode op,expr* arg1,expr* arg2){

	expr* nExpr;
	struct symbol* symb;

	if((arg1->type == var_e || arg1->type == constnum_e || arg1->type==arithmexpr_e) && (arg2->type == var_e || arg2->type == constnum_e || arg2->type==arithmexpr_e)){
		nExpr = newexpr(var_e);
		symb = newtemp(Table);
		nExpr->sym = symb;
		emit(op,arg1,arg2,nExpr,-1,yylineno);
//		if(arg1->type == constnum_e && arg2->type == constnum_e){nExpr->type=constnum_e;}
	/*	nExpr->conlist = (struct list*)malloc(sizeof(struct list));
		nExpr->breaklist = (struct list*)malloc(sizeof(struct list));
		nExpr->truelist = (struct list*)malloc(sizeof(struct list));
		nExpr->falselist = (struct list*)malloc(sizeof(struct list));	*/
		nExpr->conlist = NULL;
		nExpr->breaklist = NULL;
		return nExpr;
	}
	else{
		printf("expr_op ERROR\n");
	}
	
}

expr* bool_expr(symTable Table,enum iopcode op,expr* arg1,expr* arg2){
	expr* nExpr;
	struct symbol* sym;
	int crit = 0;
	switch(op){
		case if_greater:
			crit = 1;
			break;
		case if_greatereq:
			crit = 1;
			break;
		case if_less:
			crit = 1;
			break;
		case if_lesseq:
			crit = 1;
			break;
		case if_eq:
			crit = 2;
			break;
		case if_noteq:
			crit = 2;
			break;
		case or:
			crit = 3;
			break;
		case and:
			crit = 3;
			break;
		case not:
			crit = 3;
			break;
		default:
			assert(0);
			break;
	}
	if(crit == 1){
		if((arg1->type == constnum_e ||arg1->type==var_e|| arg1->type == arithmexpr_e || arg1->type==constbool_e)&&(arg2->type==constbool_e || arg2->type == constnum_e || arg2->type == arithmexpr_e || arg2->type == var_e)){
			nExpr = newexpr(boolexpr_e);
			sym = newtemp(Table);
			nExpr->sym = sym;
			nExpr->truelist = newlist(nextquadlabel());nExpr->falselist = newlist(nextquadlabel()+2);puts("CRITERIA 1");
			emit(op,arg1,arg2,NULL,nextquadlabel()+3,yylineno);
			emit(assign,newexpr_constbool('0'),NULL,nExpr,-1,yylineno);
			emit(jump,NULL,NULL,NULL,nextquadlabel()+2,yylineno);
			emit(assign,newexpr_constbool('1'),NULL,nExpr,-1,yylineno);		
		}
		else{
			printf("Can't compare non-numeric args ERROR\n");
		}
	}
	else if(crit == 2){
		if((arg1->type == constnum_e ||arg1->type==var_e|| arg1->type == arithmexpr_e || arg1->type==constbool_e)&&(arg2->type == constnum_e || arg2->type == arithmexpr_e || arg2->type == var_e || arg2->type==constbool_e)){
			nExpr = newexpr(boolexpr_e);
			sym = newtemp(Table);
			nExpr->sym = sym;
			nExpr->truelist = newlist(nextquadlabel());nExpr->falselist = newlist(nextquadlabel()+2);puts("CRITERIA 2");
			emit(op,arg1,arg2,NULL,nextquadlabel()+3,yylineno);
			emit(assign,newexpr_constbool('0'),NULL,nExpr,-1,yylineno);
			emit(jump,NULL,NULL,NULL,nextquadlabel()+2,yylineno);
			emit(assign,newexpr_constbool('1'),NULL,nExpr,-1,yylineno);	
			}
		else{
			printf("Can't compare different types ERROR\n");
		}
	}
	else{
		printf("Not fit argument bool type GENERIC ERROR.\n");
		}
	if(nExpr){
	/*	nExpr->conlist = (struct list*)malloc(sizeof(struct list));
		nExpr->breaklist = (struct list*)malloc(sizeof(struct list));
		nExpr->truelist = (struct list*)malloc(sizeof(struct list));
		nExpr->falselist = (struct list*)malloc(sizeof(struct list));	*/
		nExpr->conlist = NULL;
		nExpr->breaklist = NULL;
		}
	return nExpr;
}
expr* member_item(expr* lvalue,char * id){
	lvalue = emit_iftableitem(lvalue);
	expr* item = newexpr(tableitem_e);
	item->sym = lvalue->sym;
	item->index = newexpr_conststring(id);
	return item;
}
	
expr* make_call(expr* lvalue,expr* elist){
	expr* func ;
	func = emit_iftableitem(lvalue);
	
	if(elist!=NULL){
	elist = reverse(elist);
	}
	while(elist){
		printf("elis:%d\n",elist->numConst);
		emit(param,NULL,NULL,elist,-1,yylineno);
		elist = elist->next;
	}
	emit(call,NULL,NULL,func,-1,yylineno);
	expr* result;
	result = newexpr(var_e);
	result->sym = newtemp(Table);
	emit(getretval,NULL,NULL,result,-1,yylineno);
	return result;
}


expr* logic_expr(symTable Table,enum iopcode op,expr* arg1,expr* arg2){}
void comperror(char* format){}

expr* makeTarget(unsigned int i){
	expr* target = NULL;
	target = (expr*)malloc(sizeof(expr));
	target->type = constnum_e;
	target->numConst = nextquadlabel()+i;
	return target;
}

void checkuminus(expr* e){
	if((e->type == constbool_e)	||
	  (e->type == conststring_e)||
	  (e->type == nil_e)		||
	  (e->type == newtable_e)	||
	  (e->type == programfunc_e)||
	  (e->type == libraryfunc_e)	||
	  (e->type == boolexpr_e))
	  comperror("Illegal expr to unary -");
}


char * newTempName(){
	return tempArray[tempCounter++];
}

struct symbol * newtemp(symTable Table){
	SymbolTableEntry* entry = NULL;
	char * name = newTempName();
	entry = lookUpScope(Table,name,LOCALS,currScope());
	if(entry){
		printf("newTemp:%s\n",entry->sym->name);
		return entry->sym;
	}
	else{
		struct symbol* sym = NULL;
		sym = (struct symbol*)malloc(sizeof(struct symbol));
		sym->type = var_e;
		sym->name = name;
		sym->space = currscopespace();
		sym->offset = currscopeoffset();
		sym->scope = currScope();
		sym->line = yylineno;
		inccurrscopeoffset();
		insert(Table,name,LOCALS,yylineno,currScope());
		entry = lookUpScope(Table,name,LOCALS,currScope());
		entry->sym = sym;
		return sym;
	}
}


struct symbol* newSymbol(const char * name){
		
		struct symbol* sym = NULL;
		sym = (struct symbol*)malloc(sizeof(struct symbol));
		sym->type = var_s;
		sym->name = strdup(name);
		sym->space = currscopespace();
		sym->offset = currscopeoffset();
		sym->scope = currScope();
		sym->line = yylineno;
		return sym;
}	


void resetTemp(){
	tempCounter = 0;
}

char* funcNameGen(){
	int count;
	for (count= 0; count<25; count++){
		if (strcmp(funcArray[count],"")==0){
			break;
		}
	}
	char* temp1 = strdup(funcSupport[count]);
	char temp[5];
	strcpy(temp,"_f");
	strcat(temp,temp1);
	funcArray[count] = strdup(temp);
	return funcArray[count];
	}






unsigned int currScope(void){
		return scope;
}


void printQuads(){
 	quad * tempQuad = (quad *)0;
	tempQuad = quads;
	int i=0;
	printf("8==============> QUAD PRINTING STARTING HERE <================8\n");
 	while(i<nextquadlabel()){		
  		printf("%d:",i);
  		printOp(tempQuad);
  		if(tempQuad->arg1){
  			 printExpr(tempQuad->arg1);}
  		else{
   			//printf("");
		}
  		if(tempQuad->arg2){
   			printExpr(tempQuad->arg2);
		}
  		else{
   			printf("");
		}
  		if(tempQuad->result){
   			 printExpr(tempQuad->result);
  		}
		else{printf("");}
  		if(tempQuad->label != -1){
			printf(" %d \n",tempQuad->label);
		}
		else{printf("\n");}
  		tempQuad++;
		i++;
 	}
}

void printExpr(expr* arg){
 	double x,z;
 	int y;
  	switch(arg->type){
  	case var_e:   		
		printf("\t%s",arg->sym->name);
   		break;
  	case tableitem_e:
   		printf("\t%s",arg->sym->name);
   		break;
  	case programfunc_e:
  		 printf("\t%s",arg->sym->name);
   		break;
  	case libraryfunc_e:
   		printf("\t%s",arg->sym->name);
   		break;
  	case arithmexpr_e:
   		printf("\t%s",arg->sym->name);
   		break;
  	case boolexpr_e:
		 printf("\t%s",arg->sym->name);
  		 break;
  	case assignexpr_e:
   		printf("\t%s",arg->sym->name);
  		 break;
  	case newtable_e:
   		printf("\t%s",arg->sym->name);
   		break;
  	case constnum_e://numConst
    		x = arg->numConst;
    		y = (int)x;
   		z = (x-y);
   		if(z == 0)
                	printf("\t%.f",x);
   		else
                	printf("\t%f",x);
   	break;
  	case constbool_e://boolConst
   		if(arg->boolConst == '1'){
  		 	printf(" TRUE");
		}
		else if(arg->boolConst == '0'){
		 	printf(" FALSE");
		}  		
		break;
  	case conststring_e://strConst
   		printf("\t%s",arg->strConst);
   		break;
	case nil_e:
		//printf("\tNIL");
		break;
  	default:
   		printf("ASSERT\n");//assert(0);
 	}
}


void printOp(quad* p){
 	switch(p->op){
 	case assign:
  		printf("ASSIGN\t");
  		break;
 	case add:
  		printf("ADD");
  		break;
 	case sub:
  		printf("SUB\t");
  		break;
 	case mul:
  		printf("MUL\t");
  		break;
 	case divi:
  		printf("DIV\t");
  		break;
 	case mod:
  		printf("MOD\t");
  		break;
 	case uminus:
  		printf("UMINUS\t");
  		break;
 	case and:
  		printf("AND\t");
  		break;
 	case or:
  		printf("OR\t");
  		break;
 	case not:
  		printf("NOT\t");
  		break;
 	case if_eq:
  		printf("IF_EQ\t");
  		break;
 	case if_noteq:
  		printf("IF_NOTEQ\t");
  		break;
 	case if_lesseq:
  		printf("IF_LESSEQ\t");
  		break;
 	case if_greatereq:
  		printf("IF_GREATEREQ\t");
  		break;
 	case if_less:
  		printf("IF_LESS\t");
  		break;
 	case if_greater:
  		printf("IF_GREATER\t");
  		break;
 	case call:
  		printf("CALL\t");
  		break;
 	case param:
  		printf("PARAM\t");
 		break;
 	case ret:
  		printf("RET\t");
  		break;
 	case getretval:
  		printf("GETRETVAL\t");
 		break;
 	case funcstart:
  		printf("FUNCSTART\t");
  		break;
 	case funcend:
  		printf("FUNCEND\t");
  		break;
 	case tablecreate:
  		printf("TABLECREATE\t");
  		break;
 	case tablegetelem:
  		printf("TABLEGETELEM\t");
  		break;
 	case jump:
  		printf("JUMP\t");
  		break;
 	case tablesetelem:
  		printf("TABLESETELEM\t");
  		break;
 
 	default:assert(0);
	}
}



void printQuads2(){
 	quad * tempQuad = (quad *)0;
	tempQuad = quads;
	int i=0;
	FILE *fp;
	if(fp = fopen("intermediate.txt","w")){
 	while(tempQuad->label){
		
  		fprintf(fp,"%d:",i);
  		printOp2(tempQuad,fp);
  		if(tempQuad->arg1){
  			 printExpr2(tempQuad->arg1,fp);}
  		else{
   			//printf("");
		}
  		if(tempQuad->arg2){
   			printExpr2(tempQuad->arg2,fp);
		}
  		else{
   			printf("");
		}
  		if(tempQuad->result){
   			 printExpr2(tempQuad->result,fp);
  		}
		else{printf("");}
  		if(tempQuad->label > 0){
			fprintf(fp," %d \n",tempQuad->label);
		}
		else{fprintf(fp,"\n");}
  		tempQuad++;
		i++;
 	}
	}//file's if
	else
		printf("Error opening intermediate.txt\n");
}

void printExpr2(expr* arg, FILE* fp){
 	double x,z;
 	int y;
//if(arg->sym){
  	switch(arg->type){
  	case var_e:
   		fprintf(fp,"  %s  ",arg->sym->name);
   		break;
  	case tableitem_e:
   		fprintf(fp,"");
   		break;
  	case programfunc_e:
  		fprintf(fp,"  %s  ",arg->sym->name);
   		break;
  	case libraryfunc_e:
   		fprintf(fp,"");
   		break;
  	case arithmexpr_e:
   		fprintf(fp,"");
   		break;
  	case boolexpr_e:
		fprintf(fp," %s ",arg->sym->name);
  		break;
  	case assignexpr_e:
   		fprintf(fp,"  %s  ",arg->sym->name);
  		break;
  	case newtable_e:
   		fprintf(fp,"");
   		break;
  	case constnum_e://numConst
    		x = arg->numConst;
    		y = (int)x;
   		z = (x-y);
   		if(z == 0)
                	fprintf(fp,"  %.f  ",x);
   		else
                	fprintf(fp,"  %f  ",x);
   	break;
  	case constbool_e://boolConst
   		if(arg->boolConst == '1'){
  		 	fprintf(fp,"  TRUE");
		}
		else if(arg->boolConst == '0'){
		 	fprintf(fp,"  FALSE");
		}   		
		break;
  	case conststring_e://strConst
   		fprintf(fp,"  %s  ",arg->strConst);
   		break;
  	default:
   		printf("ASSERT\n");//assert(0);
 	}//}
}


void printOp2(quad* p, FILE* fp){
 	switch(p->op){
 	case assign:
  		fprintf(fp,"ASSIGN");
  		break;
 	case add:
  		fprintf(fp,"ADD");
  		break;
 	case sub:
  		fprintf(fp,"SUB");
  		break;
 	case mul:
  		fprintf(fp,"MUL");
  		break;
 	case divi:
  		fprintf(fp,"DIV");
  		break;
 	case mod:
  		fprintf(fp,"MOD");
  		break;
 	case uminus:
  		fprintf(fp,"UMINUS");
  		break;
 	case and:
  		fprintf(fp,"AND");
  		break;
 	case or:
  		fprintf(fp,"OR");
  		break;
 	case not:
  		fprintf(fp,"NOT");
  		break;
 	case if_eq:
  		fprintf(fp,"IF_EQ");
  		break;
 	case if_noteq:
  		fprintf(fp,"IF_NOTEQ");
  		break;
 	case if_lesseq:
  		fprintf(fp,"IF_LESSEQ");
  		break;
 	case if_greatereq:
  		fprintf(fp,"IF_GREATEREQ");
  		break;
 	case if_less:
  		fprintf(fp,"IF_LESS");
  		break;
 	case if_greater:
  		fprintf(fp,"IF_GREATER");
  		break;
 	case call:
  		fprintf(fp,"CALL");
  		break;
 	case param:
  		fprintf(fp,"PARAM");
 		break;
 	case ret:
  		fprintf(fp,"RET");
  		break;
 	case getretval:
  		fprintf(fp,"GETRETVAL");
 		break;
 	case funcstart:
  		fprintf(fp,"FUNCSTART");
  		break;
 	case funcend:
  		fprintf(fp,"FUNCEND");
  		break;
 	case tablecreate:
  		fprintf(fp,"TABLECREATE");
  		break;
 	case tablegetelem:
  		fprintf(fp,"TABLEGETELEM");
  		break;
 	case jump:
  		fprintf(fp,"JUMP");
  		break;
 	case tablesetelem:
  		fprintf(fp,"TABLESETELEM");
  		break;
 
 	default:assert(0);
	}
}








