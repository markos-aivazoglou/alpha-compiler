#include "vmachine.h"

int magicnumber =23522275;

unsigned int totalNamedLibFuncs = 0;
unsigned int totalUserFuncs = 0;
unsigned int totalNumConsts = 0;
unsigned int totalStrConsts = 0;
unsigned int globalvars = 0;

struct libraryfuncMap {
	char *id;
	library_func_t address;
	struct libraryfuncMap *next;
};

struct libraryfuncMap *libraryFunctionsMap[12]={NULL};

int pre_hashnum(char *s)
{
	unsigned int i;
	int hash=0;
	for(i=0; i<strlen(s); i++)
	{
		hash+= s[i];
	}
	return hash;
}



struct avm_memcell* avm_translate_operand (struct vmarg* arg,struct avm_memcell* reg){
	switch(arg->type){
		/* Variable */
		case global_a:	return &stack[AVM_STACKSIZE-1-arg->val];
		case local_a:	return &stack[topsp-arg->val];
		case formal_a:	return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
		case retval_a:	return &retval;
		
		case number_a:{
			reg->type = number_m;
			reg->data.numVal = consts_getnumber(arg->val);
			return reg;
		}
		case string_a:{
			reg->type = string_m;
			reg->data.strVal = consts_getstring(arg->val);
			return reg;
		}
		case bool_a:{
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			return reg;
		}
		case nil_a: reg->type = nil_m; return reg;
		case userfunc_a:{
			reg->type = userfunc_m;
			reg->data.funcVal = userFuncs[arg->val].address;
			return reg;
		}
		case libfunc_a:{
			reg->type = libfunc_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}
		default:
			puts("No type assigned.");
	}
}

void execute_cycle(void){
	if(executionFinished){
		return;
	}
	else if(pc == AVM_ENDING_PC){
		executionFinished = 1;
		return;
		}
	else{
		// printf("pc:%d\n",pc);
		assert(pc < AVM_ENDING_PC);
		struct instruction* instr = code + pc;
		assert(
			instr->opcode >= 0 &&
			instr->opcode <= AVM_MAX_INSTRUCTIONS
		);
		if(instr->srcLine)
			currLine = instr->srcLine;
		unsigned oldPC = pc;
		(*executeFuncs[instr->opcode])(instr);
		if(pc == oldPC)
			++pc;
	}
}


void avm_memcellclear (struct avm_memcell* m){
	if(m->type != undef_m){
		memclear_func_t f = memclearFuncs[m->type];
		if (f){
			(*f)(m);
		}
		m->type = undef_m;
	}
}

extern void memclear_string(struct avm_memcell* m){
	assert(m->data.strVal);
	free(m->data.strVal);
}


extern void memclear_table(struct avm_memcell* m){
	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal);
}



void execute_assign (struct instruction* instr) {
	struct avm_memcell* lv = avm_translate_operand(&instr->result,(struct avm_memcell*) 0);
	struct avm_memcell* rm = avm_translate_operand(&instr->arg1,&ax);
	// assert(lv);
	// assert(&stack[AVM_STACKSIZE-1] >= lv);
	// assert(lv > &stack[top]);
	assert(lv && ( &stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv == &retval));
	assert(rm);
	avm_assign(lv,rm);
}

void avm_assign (struct avm_memcell* lv,struct avm_memcell* rv){


	if(lv == rv){puts("Same cells to assign.");		// Same cells ? destructive to assign
		return;}	
		
	if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal)  // Same tables? no need to assign
		return;
		
	if (rv->type == undef_m)			// From undefined r-value : warning
		avm_warning("assigning from undef content!");
	
	avm_memcellclear(lv);
	
	memcpy(lv,rv,sizeof(struct avm_memcell));

	// Now take care of copied values or reference counting
	
	if(lv->type == string_m)
		lv->data.strVal = strdup(rv->data.strVal);
			
	else{
		if(lv->type == table_m)
			avm_tableincrefcounter(lv->data.tableVal);
	}
}



void execute_call (struct instruction* instr) {

	struct avm_memcell* func = avm_translate_operand(&instr->result, &ax);
	assert(func);
	avm_callsaveenvironment();
	switch (func->type) {
	
		case userfunc_m : {

			pc = userFuncs[func->data.funcVal].address;
			assert(pc < AVM_ENDING_PC);
			assert(code[pc].opcode == funcenter_v);
			break;
		}
		
		case string_m : avm_calllibfunc(func->data.strVal); break;
		case libfunc_m : avm_calllibfunc(func->data.libfuncVal);break;
		
		default : {
				char* s = avm_tostring(func);
				avm_error("call : cannot bind '%s' to function!",s);
				free(s);
				executionFinished = 1;
		}
	}
	
}


void avm_dec_top (void){   //CALLING FUNCTIONS
	if(!top){		//stack overflow
		executionFinished = 1;
		
	}
	else 
		--top;
		
}


void avm_push_envvalue(unsigned int val) {
	stack[top].type = number_m;
	stack[top].data.numVal = (double)val;
	avm_dec_top();
}

void avm_callsaveenvironment (void){
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top + totalActuals +2);
	avm_push_envvalue(topsp);
}


void execute_funcenter (struct instruction* instr){
		struct avm_memcell* func = avm_translate_operand(&instr->result,&ax);
		assert(func);
		assert(pc == func->data.funcVal); /*  func address should match pc*/
		/* Callee actions here */
		totalActuals = 0;
 		struct userfunc* funcInfo = avm_getfuncinfo(pc);
		topsp = top;
		top = top - funcInfo->localSize;
}
	
unsigned int avm_get_envvalue (unsigned int i) {
	assert(stack[i].type == number_m);
	unsigned int val = (unsigned int) stack[i].data.numVal;
	assert(stack[i].data.numVal == ((double) val));
	return val;
}

void execute_funcexit(struct instruction* unused) {				/* Epanafora prohgoumenou perivallontos,kai epistrofh apo thn klhsh */
	unsigned int oldTop = top;
	pc = 		avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	top = 		avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
	topsp = 	avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	while(oldTop++ <= top) /* Intentionally ignoring first*/     /* GARBADGE COLLECTION */
		avm_memcellclear(&stack[oldTop]);
}

void avm_calllibfunc(char* id) {
	library_func_t f = avm_getlibraryfunc(id);
	if(!f){
		avm_error ("unsupported lib func \'%s\' is called!",id);
		executionFinished = 1;
	}
	else {
		/* notice that enter function and exit function are calle manually!*/
		topsp = top;			/* Enter function sequence. Nos stack Locals.*/
		totalActuals = 0 ;
		(*f)();		/* Call library function */
		if(!executionFinished)			/* An error may naturally occur inside*/
			execute_funcexit((struct instruction*) 0);
	}
}


struct userfunc* avm_getfuncinfo(unsigned int index){
	// printf("ind:%d\ttotaluser:%d\n",index,totalUserFuncs);
	int i;
	for(i=0;i<totalUserFuncs;i++){
		if(index == userFuncs[i].address){
			return &userFuncs[i];
		}
	}
	// assert(index < totalUserFuncs);
}
unsigned int avm_totalactuals(void){
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

struct avm_memcell* avm_getactual(unsigned int i){
	assert(i < avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE + 1 +i];
		
  
}

/*		Implementation of the library function 'print'
		It displays every arguement at the console.
*/



void execute_pusharg (struct instruction* instr) { //TODO:Arguements passed in reverse order
	struct avm_memcell* arg = avm_translate_operand(&instr->result,&ax);
	assert(arg);
	/* This is actually stack[top] = arg, but we have to use avm_assign.*/
	avm_assign(&stack[top],arg);
	++totalActuals;
	avm_dec_top();
}

char* avm_tostring(struct avm_memcell* m) {
	assert(m->type >= 0 && m->type < undef_m);
	return (*tostringFuncs[m->type])(m);
}

double add_impl(double x, double y){
	return x+y;
}
double sub_impl(double x, double y){
	return x-y;
}
double mul_impl(double x, double y){
	return x*y;
}
double div_impl(double x, double y){
	if(y==0)
		printf("Cannot divide with 0\n");
	return x/y;
} 	// Prepei na ginei error check, gia /0 px. Oxi na trwme error tou gcc.
double mod_impl(double x, double y){
	if(y==0)
		printf("Cannot MOD with 0\n");
	return ((unsigned) x) % ((unsigned) y);		// Error check
}
void execute_arithmetic(struct instruction* instr){
	struct avm_memcell* lv = avm_translate_operand(&instr->result,(struct avm_memcell*)0);
	struct avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	assert(lv && (&stack[AVM_STACKSIZE-1] >=lv && lv > &stack[top] || lv==&retval));
	assert(rv1 && rv2);
	
	if(rv1->type != number_m || rv2->type != number_m){
		avm_error("not a number in arithmetic!\n");
		executionFinished = 1;
	}
	else{
		arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
		avm_memcellclear(lv);
		lv->type = number_m;
		lv->data.numVal	= (*op)(rv1->data.numVal, rv2->data.numVal);
	}
}

//Read 39/45.Read Lect.15 slide 26 Me omoio tropo, ulopoiountai entoles pou aforoun mono ari8mous.


unsigned char number_tobool (struct avm_memcell* m) { return m->data.numVal!=0;}
unsigned char string_tobool (struct avm_memcell* m) { return m->data.strVal[0] != 0;}
unsigned char bool_tobool (struct avm_memcell* m) { return m->data.boolVal;}
unsigned char table_tobool(struct avm_memcell* m) {return 1;}
unsigned char userfunc_tobool(struct avm_memcell* m) {return 1;}
unsigned char libfunc_tobool(struct avm_memcell* m) {return 1;}
unsigned char nil_tobool (struct avm_memcell* m) {return 0;}
unsigned char undef_tobool(struct avm_memcell* m) {assert(0); return 0;}

unsigned char avm_tobool(struct avm_memcell* m){
	assert(m->type >0 && m->type < undef_m);
	return (*toboolFuncs[m->type])(m);
}



void execute_jeq(struct instruction* instr){
	assert(instr->result.type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in equality!\n");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m){
		result = (rv1->type == nil_m && rv2->type == nil_m);
	}
	else if(rv1->type == bool_m || rv2->type == bool_m){
		printf("im in\n");
		result = (avm_tobool(rv1) == avm_tobool(rv2));
		// printf("result on eq:%d on pc:%d\n",result,pc);
	}
	else if(rv1->type != rv2 -> type){
		avm_error(
			"%s == %s is illegal!\n",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
		);
	}
	else{
		/* Equality check with dispatching. */
		switch(rv1->type){
			case number_m:{
				result= rv1->data.numVal == rv2->data.numVal;
				break;
			}
			case string_m: {
				if(strcmp(rv1->data.strVal, rv2->data.strVal)==0)
				{
					result =1;
				}
				else
				{
					result = 0;
				}
				break;
			}
			case userfunc_m: {
				result= rv1->data.funcVal == rv2->data.funcVal;
			}
			case libfunc_m: {
				if(strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal)==0)
				{
					result =1;
				}
				else
				{
					result = 0;
				}
				break;
			}
			case table_m: {
				if(rv1->data.tableVal == rv2->data.tableVal)
				{
					result =1;
				}
				else
				{
					result = 0;
				}
				break;
			}
			default: assert(0);
		}		
	}
	if(!executionFinished && result){
		printf("label on eq:%d\n",instr->result.val);
		pc = instr->result.val;
	}
}
void execute_jne(struct instruction* instr){
	assert(instr->result.type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in unequality!\n");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m){
		result = (rv1->type != nil_m || rv2->type != nil_m);
	}
	else if(rv1->type == bool_m || rv2->type == bool_m){
		result = (avm_tobool(rv1) != avm_tobool(rv2));
		printf("result:%d\n",result);
	}
	else if(rv1->type != rv2 -> type){
		avm_error(
			"%s != %s is illegal!\n",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
		);
	}
	else{
		/* Equality check with dispatching. */
		switch(rv1->type){
			case number_m:{
				result= rv1->data.numVal != rv2->data.numVal;
				break;
			}
			case string_m: {
				if(strcmp(rv1->data.strVal, rv2->data.strVal)!=0)
				{
					result =1;
				}
				else
				{
					result = 0;
				}
				break;
			}
			case userfunc_m: {
				result= rv1->data.funcVal != rv2->data.funcVal;
			}
			case libfunc_m: {
				if(strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal)!=0)
				{
					result =1;
				}
				else
				{
					result = 0;
				}
				break;
			}
			case table_m: {
				if(rv1->data.tableVal != rv2->data.tableVal)
				{
					result =1;
				}
				else
				{
					result = 0;
				}
				break;
			}
			default: assert(0);
		}		
	}
	if(!executionFinished && result)
		printf("label:%d\n",instr->result.val);
		pc = instr->result.val;
}

int cmp_gt(double x, double y){return x>y;}
int cmp_ge(double x, double y){return x>=y;}
int cmp_lt(double x, double y){return x<y;}
int cmp_le(double x, double y){return x<=y;}

void execute_comparative(struct instruction* instr){
	assert(instr->result.type == label_a);
	struct avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	struct avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	cmp_func op;
	unsigned char result = 0;
	if(rv1->type != number_m || rv2->type != number_m) {
		avm_error("not a number in arithmetic!");
	}
	else{
		assert((instr->opcode - jle_v)>=0);
		op = comparisonFuncs[instr->opcode - jle_v];
		// printf("opcode:%d\n",instr->opcode - jle_v);
		result = (*op) (rv1->data.numVal, rv2->data.numVal);
		// printf("result on comp:%d\n",result);	
	}
	if(!executionFinished && result){
		// printf("label:%d\n",instr->result.val);
		pc = instr->result.val;
	}

}

void execute_jump(struct instruction* instr){
	assert(instr->result.type == label_a);
	pc = instr->result.val;	
	// printf("pc on jump:%d\n",pc);

}

/* End of equality operations */
// void execute_nop(instruction* instr){}



/* TABLES*/
void execute_newtable(struct instruction* instr){         
	struct avm_memcell* lv = avm_translate_operand(&instr->arg1, (struct avm_memcell*)0);
	assert(lv && (&stack[AVM_STACKSIZE-1] >=lv && &stack[top] < lv || lv == &retval));
	avm_memcellclear(lv);
	
	lv->type = table_m;
	lv->data.tableVal = avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
	
}

void execute_tablegetelem(struct instruction* instr){
	struct avm_memcell* lv = avm_translate_operand(&instr->result,(struct avm_memcell*)0);
	struct avm_memcell* t = avm_translate_operand(&instr->arg1,(struct avm_memcell*)0);
	struct avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
	assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && &stack[top] < lv || lv == &retval));
	assert(t && &stack[AVM_STACKSIZE-1] >= t && &stack[top] < t);
	assert(i);
	
	avm_memcellclear(lv);
	lv->type = nil_m; // Default value
	if(t->type != table_m){
		avm_error("illegal use of type %s as table!\n", typeStrings[t->type]);
	}
	else{
		struct avm_memcell* content = avm_tablegetelem(t->data.tableVal,i);
		if(content)
			avm_assign(lv, content);
		else{
			char* ts = avm_tostring(t);
			char* is = avm_tostring(i);
			avm_warning("%s[%s] not found!\n",ts,is);
			free(ts);
			free(is);
		}
	}
}

void execute_tablesetelem(struct instruction* instr){
	struct avm_memcell* t	= avm_translate_operand(&instr->result, (struct avm_memcell*)0);
	struct avm_memcell* i 	= avm_translate_operand(&instr->arg1, &ax);
	struct avm_memcell* c 	= avm_translate_operand(&instr->arg2, &bx);
	
	assert(t && &stack[0] <= t && &stack[top] > t);
	assert(i && c);
	
	if(t->type != table_m)
		avm_error("illegal use of type %s as table!\n",typeStrings[t->type]);
	else
		avm_tablesetelem(t->data.tableVal,i,c);
}

static void avm_initstack(void){
	unsigned int i;
	for(i=0; i<AVM_STACKSIZE; i++){
		AVM_WIPEOUT(stack[i]);
		stack[i].type = undef_m;
	}
}
/* LIB FUNCTIONS */

void avm_initialize(void) {

	avm_readbinary();
	avm_initstack();
	// printf("globals:%d\n",globalvars);
	top = AVM_STACKSIZE - 1 - globalvars;
	topsp = top;
	avm_registerlibfunc("print",libfunc_print);
	avm_registerlibfunc("typeof",libfunc_typeof);
	avm_registerlibfunc("totalarguments",libfunc_totalarguments);

	
	/* SAME FOR ALL THE REST LIBRARY FUNCTIONS */
	/* COMPLETE THE REST OF LIBRARY FUNCTIONS */
	
}
void libfunc_print(void){
	unsigned int n = avm_totalactuals();
	unsigned int i;
	for(i = 0;i<n;i++){
		char* s = strdup(avm_tostring(avm_getactual(i)));
		puts(s);
		free(s);
	}
}

void libfunc_typeof(void){
	unsigned n = avm_totalactuals();
	if(n != 1)
		avm_error("one argument (not %d) expected in \'typeof\'!\n",n);
	else{
		/* Thats how a library function returns a result.
			It has to only set the 'retval' register!*/
		avm_memcellclear(&retval);	// Don't forget to clean-it up
		retval.type = string_m;
		retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
	}
}

void libfunc_totalarguments(void){
	/* Get topsp of previous activation record. */
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	if(!p_topsp){//	if 0, no previous activation record
		avm_error("'totalarguments' called outside a function!\n");
		retval.type = nil_m;
	}
	else{
		/* Extract the number of actual arguments for 
		the previous activation record. */
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}
}
/* ==== End of lib Func section ==== */



/* 	For simplicity, we only show support for numeric and string keys.
	Bonus fir teams implementing keys for usre functions, library functions and booleans.
*/

void avm_tableincrefcounter(struct avm_table* t){
	++t->refCounter;
}
/*	Automatic garbage collection for tables when reference counter gets zero.
*/

void avm_tabledecrefcounter(struct avm_table* t){
	assert(t->refCounter > 0);
	if(!--t->refCounter)
		avm_tabledestroy(t);
}

void avm_tablebucketsinit(struct avm_table_bucket** p){
	unsigned int i;
	for (i=0; i<AVM_TABLE_HASHSIZE; ++i)
		p[i] = (struct avm_table_bucket*) 0;
}

/*
	The reference counter is initially zero.
*/

struct avm_table* avm_tablenew(void){
	struct avm_table* t = (struct avm_table*) malloc(sizeof(struct avm_table));
	AVM_WIPEOUT(*t);
	
	t->refCounter = t->total = 0;
	avm_tablebucketsinit(t->numIndexed);
	avm_tablebucketsinit(t->strIndexed);
	
	return t;
}


/*
	When a cell is cleared, it has to destroy all dynamic data content
	or reset its reference toa  table.
*/


void avm_tablebucketsdestroy(struct avm_table_bucket** p){
	unsigned int i;
	struct avm_table_bucket* b;
	for(i=0; i<AVM_TABLE_HASHSIZE; ++i){
		for( b = *p; b;){
			struct avm_table_bucket* del = b;
			b = b->next;
			avm_memcellclear(&del->key);
			avm_memcellclear(&del->value);
			free(del);
		}
		p[i] = (struct avm_table_bucket*)0;
	}
}

void avm_tabledestroy(struct avm_table* t){
	avm_tablebucketsdestroy(t->strIndexed);
	avm_tablebucketsdestroy(t->numIndexed);
	free(t);
}



double consts_getnumber(unsigned int index){return numConsts[index];}
char* consts_getstring(unsigned int index){return stringConsts[index];}
char* libfuncs_getused(unsigned int index){return namedLibFuncs[index];}


void avm_error(char* format,...){}


library_func_t avm_getlibraryfunc(char* id){
	int hashindex = (pre_hashnum(id)*211)%12;
	return libraryFunctionsMap[hashindex]->address;
}
struct avm_memcell* avm_tablegetelem(struct avm_table* table,struct avm_memcell* index){}

void avm_tablesetelem(struct avm_table* table,struct avm_memcell* index,struct avm_memcell* content){}

void avm_warning(char* format,...){}

void avm_registerlibfunc(char* id,library_func_t addr){
  	int hashindex = (pre_hashnum(id)*211)%12;
	struct libraryfuncMap *newbucket = (struct libraryfuncMap *)malloc(sizeof(struct libraryfuncMap));
	newbucket->id = strdup(id);
	newbucket->address = addr;
	libraryFunctionsMap[hashindex]=newbucket;
}


void execute_not(struct instruction* instr){}
void execute_uminus(struct instruction* instr){}
void execute_and(struct instruction* instr){}
void execute_or(struct instruction* instr){}


void execute_nop(struct instruction* instr){}



char* number_tostring(struct avm_memcell* m){
	char *buff;buff = malloc(sizeof(m->data.numVal));
	memset(buff,'\0',sizeof(buff));
	// sprintf(buff,"%f",m->data.numVal);
	double z,x=m->data.numVal;
	int y;
    y = (int)x;
   	z = (x-y);
   	if(z == 0)
       	sprintf(buff,"%.f",x);
   	else
       	sprintf(buff,"%f",x);
	return buff;
}
char* string_tostring(struct avm_memcell* m){
	return m->data.strVal;
}
char* bool_tostring(struct avm_memcell* m){
	char *buff;buff = malloc(sizeof(m->data.boolVal));
	memset(buff,'\0',sizeof(buff));
	sprintf(buff,"%c",m->data.boolVal);
	return buff;
}
char* table_tostring(struct avm_memcell* m){}
char* userfunc_tostring(struct avm_memcell* m){}
char* libfunc_tostring(struct avm_memcell* m){}
char* nil_tostring(struct avm_memcell* m){}
char* undef_tostring(struct avm_memcell* m){}



// void printDouble(double x){
// 	double z;
// 	int y;
//     y = (int)x;
//    	z = (x-y);
//    	if(z == 0)
//        	printf("%.f\t",x);
//    	else
//        	printf("%f\t",x);
// }
// void printNumTable(){
// 	unsigned int index;
// 	puts("****************** NUM_TABLE Start ******************");
// 	for(index=0;index<totalNumConsts;index++){
// 		printf("%d|\t",index);printDouble(numConsts[index]);printf("\n");
// 	}
// 	puts("------------------ NUM_TABLE End ------------------");
// }
// void printUserfuncTable(){
// 	unsigned int index;
// 	puts("****************** USERFUNC_TABLE Start ******************");
// 	for(index=0;index<totalUserFuncs;index++){
// 		printf("%d|\t%s\n",index,(userFuncs[index].id));
// 	}
// 	puts("------------------ USERFUNC_TABLE End ------------------");
// }

void avm_readbinary(void){
	int i,j;
	FILE *fp;
	char buf[50],*tok[2];
	double number;
	unsigned int inst1,inst2,inst;
	memset(buf,'\0',sizeof(buf));
	
	fp = fopen("target.txt","r");
	fscanf(fp,"%s",buf);
	i = atoi(buf);
	
	if (i != magicnumber){
		puts("wrong identifier");
	}
	fscanf(fp,"%s",buf);//Table name
	fscanf(fp,"%s",buf);//STR Contents

	i = atoi(buf);
	totalStrConsts = i;
	/*read string table*/
	
	for(j=0;j<i;j++){
	    fscanf(fp,"%s",buf);
	    stringConsts[j] = strdup(buf);
	}
	fscanf(fp,"%s",buf);//Table name
	/*read num table*/
	int test;
	fscanf(fp,"%s",buf);//Num Contents
	i = atoi(buf);
	totalNumConsts = i;
	for(j=0;j<i;j++){
	  fscanf(fp,"%s",buf);
	  number = strtod(buf,NULL);
	  numConsts[j] = number;
	}
	fscanf(fp,"%s",buf);//Table name
	fscanf(fp,"%s",buf);//UsrFunc Contents
	i = atoi(buf);
	totalUserFuncs = i;
	userFuncs = (struct userfunc*)malloc(sizeof(struct userfunc)*totalUserFuncs);
	/*read user funcs table*/
	for(j=0;j<i;j++){
	    fscanf(fp,"%s",buf);
	    // printf("addr:%s\n",buf);
	    userFuncs[j].address = atoi(buf);
	    fscanf(fp,"%s",buf);
	    userFuncs[j].localSize = atoi(buf);
	    fscanf(fp,"%s",buf);
	    userFuncs[j].id = strdup(buf);
	}
	fscanf(fp,"%s",buf);//Table name
	fscanf(fp,"%s",buf);//LibFunc Contents
	i = atoi(buf);
	totalNamedLibFuncs = i;
	/*read lib funcs table*/
	for(j=0;j<i;j++){
	    fscanf(fp,"%s",buf);
	    namedLibFuncs[j] = strdup(buf);
	}
	fscanf(fp,"%s",buf);//Table name
	fscanf(fp,"%s",buf);//Instruction Contents
	i = atoi(buf);
	codeSize = i-1;
	code=(struct instruction*)malloc(sizeof(struct instruction)*i);


	/*read instructions table*/
	for(j=0;j<i;j++){
	    fscanf(fp,"%s",buf);
	    inst = strtol(buf,NULL,10);
	    (code+j)->opcode = inst;
	    
	    fscanf(fp,"%s",buf);
	    tok[0] = strtok(buf,",");
	    inst1 = strtol(tok[0],NULL,10);
	    (code+j)->arg1.type = inst1;
	    tok[1] = strtok(NULL,",");
	    if(tok[1]){
			inst2 = strtol(tok[1],NULL,10);
			(code+j)->arg1.val = inst2;
			if((inst1==1 || inst1==8) && globalvars<=inst2){
				globalvars++;
			}
	    }
	    tok[0]=NULL;
	    tok[1]=NULL;
	    
	    fscanf(fp,"%s",buf);
	    tok[0] = strtok(buf,",");
	    inst1 = strtol(tok[0],NULL,10);
	    (code+j)->arg2.type = inst1;
	    tok[1] = strtok(NULL,",");
	    if(tok[1]){
			inst2 = strtol(tok[1],NULL,10);
			(code+j)->arg2.val = inst2;
			if((inst1==1 || inst1==8) && globalvars<=inst2){
				globalvars++;
			}
	    }
	    tok[0]=NULL;
	    tok[1]=NULL;
	    
	    
	    fscanf(fp,"%s",buf);
	    tok[0] = strtok(buf,",");
	    inst1 = strtol(tok[0],NULL,10);
	    (code+j)->result.type = inst1;
	    tok[1] = strtok(NULL,",");
	    if(tok[1]){
			inst2 = strtol(tok[1],NULL,10);
			(code+j)->result.val = inst2;
			if((inst1==1 || inst1==8) && globalvars<=inst2){
				globalvars++;
			}
	    }
	    tok[0]=NULL;
	    tok[1]=NULL;
	}
}

void main(void){
    avm_initialize();
    while(!executionFinished){
		execute_cycle();
    }
  
}
