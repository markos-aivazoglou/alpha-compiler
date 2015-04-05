#include "tcode.h"
#define TABLE_SIZE 1024
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern quad* quads;
extern unsigned int total;


/* Total elements in each specific Table */
unsigned int totalNumConsts = 0;
unsigned int totalStringConsts = 0;
unsigned int totalUserFuncs = 0;
unsigned int totalNamedLibfuncs = 0;

/* Instruction table etc. */
struct instruction* instructions = (struct instruction*) 0;
unsigned int totalInstructions = 0;
unsigned int currInstruction = 0;
unsigned int currprocessedquads;
unsigned int userfunc_table_size = 0;

/* Initing incomplete jumps list */
struct incomplete_jump*	ij_head = (struct incomplete_jump*) 0;
unsigned int		ij_total = 0;

/* Userfunc Stack */
struct userfunc* funcstack=NULL; 
int stack_size = 0;
int stack_top =0;

unsigned int totalVars = 0;


unsigned int nextinstructionlabel(){
	return currInstruction;
}

void reset_operand(struct vmarg *arg)
{
	arg=NULL;
}


typedef void (*generator_func_t)(quad*);

generator_func_t generators[] = {
	generate_ASSIGN,
	generate_ADD,
	generate_SUB,
	generate_MUL,
	generate_DIV,
	generate_MOD,
	generate_NOP,
	generate_AND,
	generate_OR,
	generate_NOT,
	generate_IF_EQ,
	generate_IF_NOTEQ,
	generate_IF_LESSEQ,
	generate_IF_GREATEREQ,
	generate_IF_LESS,
	generate_IF_GREATER,
	generate_CALL,
	generate_PARAM,
	generate_RETURN,
	generate_GETRETVAL,
	generate_FUNCSTART,
	generate_FUNCEND,
	generate_NEWTABLE,
	generate_TABLEGETELEM,
	generate_JUMP,	
	generate_TABLESETELEM
};

void expand_instructions(){
	assert(totalInstructions == currInstruction);
	struct instruction* t = NULL;
	t = (struct instruction*)malloc(NEW_SIZE);
	if(instructions){
		memcpy(t,instructions,CURR_SIZE);
		free(instructions);
	}
	instructions = t;
	totalInstructions += EXPAND_SIZE;
}

void emit_instruction(struct instruction* t){
	if(currInstruction == totalInstructions)
		expand_instructions();

	struct instruction* inst	= instructions+currInstruction++;
	inst->opcode = t->opcode;
	inst->result = t->result;
	inst->arg1 = t->arg1;
	inst->arg2 = t->arg2;
	inst->srcLine = t->srcLine;
}


void printInstructions(){
	struct instruction* temp = NULL;
	temp = instructions;
	unsigned int i=0;
	printf("\n^^^^^^^^^^^^^ Start printing Instruction Table ^^^^^^^^^^^^^\n");
	while(temp <= (instructions+nextinstructionlabel()-1)){
		printf("%d:",i);
		printInstrOp(temp->opcode);
		if(&temp->arg1){
			printVMarg(&temp->arg1);			
		}
		if(&temp->arg2){
			printVMarg(&temp->arg2);
		}
		if(&temp->result){
			printVMarg(&temp->result);
		}
		i++;
		temp = instructions+i;
		printf("\n");
	}
}




void printVMarg(struct vmarg* arg){ 
		switch(arg->type){
		case label_a: printf("00, %d\t",arg->val);break; //	label_a
		case global_a: printf("01, %d:\t",arg->val);printVar(arg->val);break; //	global_a
		case formal_a: printf("02, %d:\t",arg->val);printVar(arg->val);break; //	formal_a
		case local_a: printf("03, %d:\t",arg->val);printVar(arg->val);break; //	local_a
		case number_a: printf("04, %d:\t",arg->val);printDouble(numConsts[arg->val]);break; //	number_a
		case string_a: printf("05, %d:%s\t",arg->val, stringConsts[arg->val]);break; //	string_a
		case bool_a: printf("06, %c\t",arg->val);break; //	bool_a
		case nil_a: /*printf("\t(nil_a)\t");*/break; //nil_a
		case userfunc_a: printf("08, %d:  %s\t",arg->val, userFuncs[arg->val].id);break; //	userfunc_a
		case libfunc_a: printf("09, %d:  %s\t",arg->val, namedLibfuncs[arg->val]);break; //	libfunc_a
		case retval_a: printf("10, retval\t");break; //	retval_a
		default: ;//printf("Asserting for arg->val=%d\n",arg->val);assert(0);
	}
}
void printDouble(double x){
	double z;
	int y;
    	y = (int)x;
   	z = (x-y);
   	if(z == 0)
               	printf("%.f\t",x);
   		else
                	printf("%f\t",x);
}
void printInstrOp(enum vmopcode op){
	switch(op){
		case assign_v:
			printf("ASSIGN\t");
			break;
		case add_v:
			printf("ADD\t\t");
			break;
		case sub_v:
			printf("SUB\t\t");
			break;
		case mul_v:
			printf("MUL\t\t");
			break;
		case div_v:
			printf("DIV\t\t");
			break;
		case mod_v:
			printf("MOD\t\t");
			break;
		case uminus_v:
			printf("UMINUS\t");
			break;
		case and_v:
			printf("AND");
			break;
		case or_v:
			printf("OR");
			break;
		case not_v:
			printf("NOT");
			break;
		case jump_v:
			printf("JUMP\t\t");
			break;
		case jeq_v:
			printf("Jump_If_Equal ");
			break;
		case jne_v:
			printf("Jump_If_NOTEqual ");
			break;
		case jle_v:
			printf("Jump_If_lessOREqual ");
			break;
		case jge_v:
			printf("Jump_If_greaterOREqual ");
			break;
		case jlt_v:
			printf("Jump_IFLESS\t");
			break;
		case jgt_v:
			printf("Jump_IFGREATER ");
			break;
		case call_v:
			printf("CALL\t\t");
			break;
		case pusharg_v:
			printf("PUSHARG\t");
			break;
		case funcenter_v:
			printf("FuncENTER\t");
			break;
		case funcexit_v:
			printf("FuncEXIT\t");
			break;
		case newtable_v:
			printf("NEWTABLE\t");
			break;
		case tablegetelem_v:
			printf("tableGETelem\t");
			break;
		case tablesetelem_v:
			printf("tableSETelem\t");
			break;
		case nop_v:
			printf("NOP");
			break;
	}
}

void make_operand(expr* e,struct vmarg* arg){

	/*if(!e)
	{
		arg->type = nil_a;
		return;
	}*/
	switch(e->type){ 
		case var_e:{
		arg->val = e->sym->offset;
		newvar(e->sym->offset,e->sym->name);
			switch(e->sym->space){
				case programvar:		arg->type = global_a;	break;
				case functionlocal: 		arg->type = local_a;	       break;
				case formalarg:		arg->type = formal_a;	break;
				default: assert(0);
			}
			break;			/*n from case newtable_e */
		}				
		case tableitem_e:{			
		arg->val = e->sym->offset;
			switch(e->sym->space){
				case programvar:		arg->type = global_a; 	break;
				case functionlocal: 		arg->type = local_a;		break;
				case formalarg:		arg->type = formal_a;	break;
				default: assert(0);
			}
			break;			/*n from case newtable_e */
		}				
		case boolexpr_e:{
		newvar(e->sym->offset,e->sym->name);
		arg->val = e->sym->offset;
			switch(e->sym->space){
				case programvar:		arg->type = global_a; 	break;
				case functionlocal: 		arg->type = local_a;		break;
				case formalarg:		arg->type = formal_a;	break;
				default: assert(0);
			}
			break;			/*n from case newtable_e */
		}
		case assignexpr_e:{		
		arg->val = e->sym->offset;
		newvar(e->sym->offset,e->sym->name);
			switch(e->sym->space){
				case programvar:		arg->type = global_a;	break;
				case functionlocal: 		arg->type = local_a;	       break;
				case formalarg:		arg->type = formal_a;	break;
				default: assert(0);
			}
			break;			/*n from case newtable_e */
		}			
		case newtable_e:{			
		arg->val = e->sym->offset;
			switch(e->sym->space){
				case programvar:		arg->type = global_a; 	break;
				case functionlocal: 		arg->type = local_a;		break;
				case formalarg:		arg->type = formal_a;	break;
				default: assert(0);
			}
			break;			/*n from case newtable_e */
		}
		/* Constants */
		case constbool_e:{
			arg->val = e->boolConst;
			arg->type = bool_a;	break;
		}
		case conststring_e:{
			arg->val = consts_newstring(e->strConst);
			arg->type = string_a;	break;
		}
		case constnum_e:{
			arg->val = consts_newnumber(e->numConst);
			arg->type = number_a;	break;
		}
		case nil_e: arg->type = nil_a;	break;
		
		/* Functions */
		case programfunc_e:{
		    unsigned int index;
		    for(index =0; index<totalUserFuncs; index++){
			if(strcmp(e->sym->name,(userFuncs+index)->id)==0){
			    arg->val = index;
			}
		    }
			arg->type = userfunc_a;
			break;
		}
		case libraryfunc_e:{
			arg->type = libfunc_a;
			arg->val = libfuncs_newused(e->sym->name);
			break;
		}
		default: assert(0);
	}
}

void newvar(unsigned int offset, char* name){
	if(!varhead){
		varhead = (struct var_table*)malloc(sizeof(struct var_table));
		varhead->offset = offset;
		varhead->var_name = name;
		varhead->next = NULL;
	}
	else{
		struct var_table* temp=NULL;
		temp = varhead;
		while(temp->next){
			temp = temp->next;
		}
		struct var_table* newnode = (struct var_table*)malloc(sizeof(struct var_table));
		newnode->offset = offset;
		newnode->var_name = name;
		newnode->next = NULL;
		temp->next = newnode;
	}
	totalVars++;
}


void printVar(unsigned int offset){
	struct var_table* temp = NULL;
	temp = varhead;
	if(temp){
		while(temp){
			if(temp->offset == offset){
				printf("%s\t",temp->var_name);
				break;
			}
			temp = temp->next;
		}
	}
}

void printTables(){
	printNumTable();
	printStringTable();
	printUserfuncTable();
	printLibfuncTable();
}
void printTables_tofile(){
  
  
	int i = open("target.txt",O_RDWR|O_CREAT,S_IRWXU);
	unsigned int magicNumber=23522275;
	char buf[8];
	sprintf(buf,"%d",magicNumber);
	write(i,buf,sizeof(buf));
	write(i,"\n",1);
	printStringTable_tofile(i);
	printNumTable_tofile(i);
	printUserfuncTable_tofile(i);
 	printLibfuncTable_tofile(i);
 	printInstructions_tofile(i);
	close(i);
}
void printStringTable_tofile(int j){
	char buf[5];
	char *buf2;
	int i=0;
	memset(buf,'\0',sizeof(buf));
	sprintf(buf,"%d",totalStringConsts);
	buf[strlen(buf)]='\0';
	write(j,"strings ",8);
	write(j,buf,strlen(buf));
	write(j,"\n",1);
	for(i;i<totalStringConsts;i++){
	  buf2=strdup(stringConsts[i]);
	  write(j,buf2,strlen(buf2));
	  memset(buf2,'\0',sizeof(buf2));
	  write(j,"\n",1);
	}
  
  
}
void printNumTable_tofile(int j){
	char buf[8];
	int i=0;
	memset(buf,'\0',sizeof(buf));
	sprintf(buf,"%d",totalNumConsts);
	buf[strlen(buf)]='\0';
	
	write(j,"constants ",10);
	write(j,buf,strlen(buf));
	write(j,"\n",1);
	double z;
	int y;
	double x;
	memset(buf,'\0',sizeof(buf));
	for(i=0;i<totalNumConsts;i++){
	  x = numConsts[i];
	  y = (int)x;
	  z = (x-y);
	  if(z == 0)
               sprintf(buf,"%.f\t",x);
   	  else
               sprintf(buf,"%.3f\t",x);
	  buf[strlen(buf)]='\0';
	  write(j,buf,strlen(buf));
	  memset(buf,'\0',sizeof(buf));
	  write(j,"\n",1);
	  
	}
}

void printUserfuncTable_tofile(int i){
	char buf1[3];
	write(i,"User_Funcs ",11);
	sprintf(buf1,"%d",totalUserFuncs);
	write(i,buf1,strlen(buf1));
	write(i,"\n",1);
	unsigned int index;
	char *buf;
	for(index=0; index<totalUserFuncs; index++)
	{
	  buf = strdup(userFuncs[index].id);
	  write(i,buf,strlen(buf));
	  memset(buf,'\0',sizeof(buf));
	  write(i,"\n",1);
	}
	
  
  
}

void printLibfuncTable_tofile(int i){
	char buf1[3];
	write(i,"Library_Funcs ",14);
	sprintf(buf1,"%d",totalNamedLibfuncs);
	write(i,buf1,strlen(buf1));
	write(i,"\n",1);
	unsigned int index,strsize;
	char *buf;
	for(index=0; index<totalNamedLibfuncs; index++)
	{
	  buf = strdup(namedLibfuncs[index]);
	  write(i,buf,strlen(buf));
	  memset(buf,'\0',sizeof(buf));
	  write(i,"\n",1);
	}
	
}

void printInstructions_tofile(int j){
	struct instruction* temp = NULL;
	temp = instructions;
	unsigned int i=0;
	char buf3[4];
	write(j,"total_instructions ",19);
	memset(buf3,'\0',sizeof(buf3));
	printf("total instr %d\n",currInstruction);
	sprintf(buf3,"%d",currInstruction);
	write(j,buf3,strlen(buf3));
	write(j,"\n",1);
	while(temp <= (instructions+nextinstructionlabel()-1)){
		printInstrOp_tofile(temp->opcode,j);
		if(&temp->arg1){
			printVMarg_tofile(&temp->arg1,j);			
		}
		if(&temp->arg2){
			printVMarg_tofile(&temp->arg2,j);
		}
		if(&temp->result){
			printVMarg_tofile(&temp->result,j);
		}
		i++;
		temp = instructions+i;
		write(j,"\n",1);
	}
}




void printVMarg_tofile(struct vmarg* arg,int i){ 
		
		char buf4[10];
		memset(buf4,'\0',sizeof(buf4));
		switch(arg->type){
		case label_a: 
			      sprintf(buf4,"%d,%d\t",arg->type,arg->val);
			      write(i,buf4,strlen(buf4));
			      break; //	label_a
		case global_a: 	sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				write(i,buf4,strlen(buf4));
				break; //	global_a
		case formal_a:	sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				write(i,buf4,strlen(buf4)); 
				break; //	formal_a
		case local_a: 	sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				write(i,buf4,strlen(buf4));
				break; //	local_a
		case number_a: 	sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				write(i,buf4,strlen(buf4));
				break; //	number_a
		case string_a: 	sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				write(i,buf4,strlen(buf4));
				break; //	string_a
		case bool_a: 	sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				write(i,buf4,strlen(buf4));
				break; //	bool_a
		case nil_a: 	sprintf(buf4,"%d\t",arg->type);
				write(i,buf4,strlen(buf4));
				break; //nil_a
		case userfunc_a: sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				  write(i,buf4,strlen(buf4));
				  break; //	userfunc_a
		case libfunc_a:  sprintf(buf4,"%d,%d\t",arg->type,arg->val);
				  write(i,buf4,strlen(buf4));
				  break; //	libfunc_a
		case retval_a: 	sprintf(buf4,"%d\t",arg->type);
				write(i,buf4,strlen(buf4));
				break; //	retval_a
		default: ;//printf("Asserting for arg->val=%d\n",arg->val);assert(0);
	}
}

void printInstrOp_tofile(enum vmopcode op,int i){
	char buf5[2];
	memset(buf5,'\0',sizeof(buf5));
	
	switch(op){
		case assign_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case add_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case sub_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case mul_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case div_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case mod_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case uminus_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case and_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case or_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case not_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jump_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jeq_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jne_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jle_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jge_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jlt_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case jgt_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case call_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case pusharg_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case funcenter_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case funcexit_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case newtable_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case tablegetelem_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case tablesetelem_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
		case nop_v:
			sprintf(buf5,"%d\t",op);
			write(i,buf5,strlen(buf5));
			break;
	}
	
}


void printNumTable(){
	unsigned int index;
	puts("****************** NUM_TABLE Start ******************");
	for(index=0;index<totalNumConsts;index++){
		printf("%d|\t",index);printDouble(numConsts[index]);printf("\n");
	}
	puts("------------------ NUM_TABLE End ------------------");
}

void printStringTable(){
	unsigned int index;
	puts("****************** STRING_TABLE Start ******************");
	for(index=0;index<totalStringConsts;index++){
		printf("%d|\t%s\n",index,*(stringConsts+index));
	}
	puts("------------------ STRING_TABLE End ------------------");
}

void printUserfuncTable(){
  unsigned int index;
  puts("****************** USERFUNC_TABLE Start ******************");
  for(index=0;index<totalUserFuncs;index++){
      printf("%d|\t%s\n",index,(userFuncs[index].id));
  }
  puts("------------------ USERFUNC_TABLE End ------------------");
}

void printLibfuncTable(){
  unsigned int index;
  puts("****************** LIBFUNC_TABLE Start ******************");
  for(index=0; index < totalNamedLibfuncs;index++){
		printf("%d|\t%s()\n",index,*(namedLibfuncs+index));
		
	}
  puts("------------------ LIBFUNC_TABLE End ------------------");
}


unsigned int consts_newstring(char* s){
	assert(totalStringConsts < TABLE_SIZE);
	unsigned int index;
	assert(s);
	for(index=0; index<totalStringConsts; index++){
		if(strcmp(*(stringConsts+index),s)==0)
			return index;
	}
	stringConsts[totalStringConsts++] = s;
	return index;
}

unsigned int consts_newnumber(double n){
	assert(totalNumConsts < TABLE_SIZE);
	unsigned int index;
	for(index=0; index <= totalNumConsts; index++){
		if(numConsts[index] == n)
			return index;
	}
	numConsts[totalNumConsts] = n;
	return totalNumConsts++;
}

unsigned int userfuncs_newfunc(struct symbol* sym){
	if(totalUserFuncs == userfunc_table_size){
		struct userfunc* temp = NULL;
		temp = (struct userfunc*)malloc(sizeof(struct userfunc)*50+userfunc_table_size);
		if(userFuncs){
			memcpy(temp, userFuncs, userfunc_table_size);
			free(userFuncs);
		}
		userFuncs = temp;
		userfunc_table_size += 50;
	}
	
	unsigned int index;
	for(index =0; index<totalUserFuncs; index++){
		if(sym->taddress == (userFuncs+index)->address){
			return index;
		}
	}
	(userFuncs+totalUserFuncs)->address = sym->taddress;
	(userFuncs+totalUserFuncs)->id = sym->name;
	//TODO init localsize.
	return totalUserFuncs;
}

unsigned int libfuncs_newused(char* s){
	assert(totalNamedLibfuncs < TABLE_SIZE);
	unsigned int index;
	for(index=0; index < totalNamedLibfuncs;index++){
		if(strcmp(*(namedLibfuncs+index),s)==0)
			return index;
	}
	namedLibfuncs[totalNamedLibfuncs] = s;
	return totalNamedLibfuncs++;
}
/*
	Helper functions to produce common arguments for generated instructions, like 1, 0, "true", "false"
	and funciton return  values.
*/

void make_numberoperand(struct vmarg* arg, double val){
	arg->val = consts_newnumber(val);
	arg->type = number_a;
}

void make_booloperand(struct vmarg* arg, unsigned char val){
	arg->val = val;
	arg->type = bool_a;
}

void make_retvaloperand(struct vmarg* arg){
	arg->type = retval_a;
}

void add_incomplete_jump(unsigned instrNo, unsigned iaddress){
	struct incomplete_jump* temp;
	temp = ij_head;
	if(!temp){
		ij_head = (struct incomplete_jump*)malloc(sizeof(struct incomplete_jump));
		ij_head->iaddress = iaddress;
		ij_head->instrNo = instrNo;
		ij_head->next = NULL;
		temp = ij_head;
	}
	else{
		while(temp->next){
			temp = temp->next;
		}
		temp->next = (struct incomplete_jump*)malloc(sizeof(struct incomplete_jump));
		temp = temp->next;
		temp->iaddress = iaddress;
		temp->instrNo = instrNo;
	}
}

void generate_instr(enum vmopcode op,quad* quad){
	struct instruction t;
	t.opcode = op;
	make_operand(quad->arg1, &(t.arg1));
	make_operand(quad->arg2, &(t.arg2));	
	make_operand(quad->result, &(t.result));
	quad->taddress = nextinstructionlabel();
	emit_instruction(&t);      
}

void generate(void){
		unsigned int i;
		for(i=0;i<nextquadlabel();i++){
			(*generators[quads[i].op])(quads+i);
			
		}
		patch_incomplete_jumps(nextquadlabel(), currInstruction);
}

void generate_ADD (quad* quad) 						{ generate_instr(add_v, quad); }
void generate_SUB (quad* quad) 						{ generate_instr(sub_v, quad); }
void generate_MUL (quad* quad) 						{ generate_instr(mul_v, quad); }
void generate_DIV (quad* quad) 						{ generate_instr(div_v, quad); }
void generate_MOD (quad* quad) 						{ generate_instr(mod_v, quad); } 
void generate_NEWTABLE (quad* quad) 					{ generate_instr(newtable_v, quad); }
void generate_TABLEGETELEM (quad* quad) 					{ generate_instr(tablegetelem_v, quad); }
void generate_TABLESETELEM (quad* quad) 					{ generate_instr(tablesetelem_v, quad); }
void generate_ASSIGN (quad* quad) 						{ generate_instr(assign_v, quad); }
void generate_NOP ()								{ struct instruction t; t.opcode=nop_v; emit_instruction(&t); }
void generate_JUMP (quad* quad)						{ generate_relational(jump_v, quad); }
void generate_IF_EQ (quad* quad) 						{ generate_relational(jeq_v, quad); }
void generate_IF_NOTEQ(quad* quad) 					{ generate_relational(jne_v, quad); }
void generate_IF_GREATER (quad* quad) 					{ generate_relational(jgt_v, quad); }
void generate_IF_GREATEREQ(quad* quad) 					{ generate_relational(jge_v, quad); }
void generate_IF_LESS (quad* quad) 					{ generate_relational(jlt_v, quad); }
void generate_IF_LESSEQ (quad* quad) 					{ generate_relational(jle_v, quad); } 



void generate_relational (int op,quad* quad) {
	struct instruction t;
	t.opcode = op;
	make_operand(quad->arg1, &t.arg1);
	make_operand(quad->arg2, &t.arg2);
	t.result.type = label_a;
	if (quad->label < currprocessedquad())
		t.result.val = (quads+quad->label)->taddress;
	else
		add_incomplete_jump(nextinstructionlabel(), quad->label);
	quad->taddress = nextinstructionlabel();
	emit_instruction(&t); /* TODO*/
}


unsigned int currprocessedquad(){
	return currprocessedquads;

}


void generate_AND (quad *quad) {
	struct instruction t;
	quad->taddress = nextinstructionlabel();
	t.opcode = jeq_v;
	make_operand(quad->arg1, &t.arg1);	
	make_booloperand(&t.arg2, '1');
	t.result.type = label_a;
	t.result.val = nextinstructionlabel()+4;
	emit_instruction(&t);
	
	make_operand(quad->arg2, &t.arg1);
	t.result.val = nextinstructionlabel()+3;	
	emit_instruction(&t);
	
	
	t.opcode = assign_v;
	make_booloperand(&t.arg1, '0');
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);
	
	
	
	t.opcode = jump_v;
	reset_operand (&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val = nextinstructionlabel()+2;
	emit_instruction(&t);
	
	
	
	t.opcode = assign_v;
	make_booloperand(&t.arg1, '1');
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);
}

void generate_NOT (quad* quad) {
	
	quad->taddress = nextinstructionlabel();
	struct instruction t;

	t.opcode = jeq_v;
	make_operand(quad->arg1, &t.arg1);
	make_booloperand(&t.arg2, '0');
	t.result.type = label_a;
	t.result.val  = nextinstructionlabel()+3;
	emit_instruction(&t); 

	t.opcode = assign_v;
	make_booloperand(&t.arg1, '0');
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);

	t.opcode = jump_v;
	reset_operand (&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val  = nextinstructionlabel()+2;
	emit_instruction(&t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, '1');
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);
}

void generate_OR (quad* quad) {

	quad->taddress = nextinstructionlabel();
	struct instruction t;

	t.opcode = jeq_v;
	make_operand(quad->arg1, &t.arg1);
	make_booloperand(&t.arg2, '1');
	t.result.type = label_a;
	t.result.val  = nextinstructionlabel()+4;
	emit_instruction(&t);

	make_operand(quad->arg2, &t.arg1);
	t.result.val  = nextinstructionlabel()+3;
	emit_instruction(&t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, '0');
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);

	t.opcode = jump_v;
	reset_operand (&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val  = nextinstructionlabel()+2;
	emit_instruction(&t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, '1');
	reset_operand(&t.arg2);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);
}

void generate_PARAM(quad* quad) {
	quad->taddress = nextinstructionlabel();
	struct instruction t;
	t.arg1.type = nil_a;
	t.arg2.type = nil_a;
	t.opcode = pusharg_v;
	make_operand(quad->result, &t.result);//printf("GAMW XRISTO     %d\n",quad->arg1->type);
	//printf("PUSHARG %d****\n",t.result.type);
	emit_instruction(&t);
}


void generate_CALL(quad* quad) {
	quad->taddress = nextinstructionlabel();
	struct instruction t;
	t.opcode = call_v;
	t.arg1.type = nil_a;
	t.arg2.type = nil_a;
	make_operand(quad->result, &t.result);
	//printf("CALL %d****%d\n",t.result.type,t.result.val);

	emit_instruction(&t);
}

void generate_GETRETVAL(quad* quad) {
	quad->taddress = nextinstructionlabel();
	struct instruction t;
	t.opcode = assign_v;
	make_operand(quad->result, &t.result);
	make_retvaloperand(&t.arg1);
	emit_instruction(&t);
}

void generate_FUNCSTART(quad* quad){
	struct userfunc* f;
	f = (struct userfunc*)malloc(sizeof(struct userfunc));
	f->id=quad->result->sym->name;
	f->address = nextinstructionlabel();
	
	quad->taddress = nextinstructionlabel();
	userfuncs_newfunc(quad->result->sym);	//added 6/5 ore

	(userFuncs+totalUserFuncs)->address = f->address;
	(userFuncs+totalUserFuncs)->id = f->id;
	(userFuncs+totalUserFuncs)->localSize = f->localSize;
	f->index = totalUserFuncs-1;
	funcpush(f);
	
	struct instruction t;
	totalUserFuncs++;
	t.arg1.type = nil_a;
	t.arg2.type = nil_a;
	t.opcode = funcenter_v;
	make_operand(quad->result, &t.result);
	t.result.val = totalUserFuncs-1; //EDW
	emit_instruction(&t);
}

void generate_RETURN(quad* quad){
	quad->taddress = nextinstructionlabel();
	struct instruction t;
	t.opcode = assign_v;
	make_retvaloperand(&t.arg1);
	make_operand(quad->result, &t.result);
	emit_instruction(&t);
	
	struct userfunc* f;
	f = functop(funcstack);
	f->returnList = (struct userfunc*)malloc(sizeof(struct userfunc));
	append(f->returnList, nextinstructionlabel());
	
	t.opcode = jump_v;
	reset_operand(&t.arg1);
	t.arg1.type = nil_a;
	reset_operand(&t.arg2);
	t.result.type = label_a;
	//printf("%d  LABEL_A\n",f->returnList->address);
	emit_instruction(&t);
}

void generate_FUNCEND(quad* quad){
	struct userfunc* f;
	f=funcpop(funcstack);
	patch_returns(f->returnList, nextinstructionlabel());

	quad->taddress = nextinstructionlabel();
	struct instruction t;
	t.opcode = funcexit_v;
	t.arg1.type = nil_a;
	t.arg2.type = nil_a;
	make_operand(quad->result, &t.result);
	t.result.val = f->index;
	emit_instruction(&t);
}

void append(struct userfunc* head, unsigned int instNo){
    if(!head){
      head = (struct userfunc*)malloc(sizeof(struct userfunc));
      head->address = instNo;
    }
    else{
      struct userfunc* temp = head;
      while(temp->returnList){
	temp = temp->returnList;
      }
      temp->returnList = (struct userfunc*)malloc(sizeof(struct userfunc));
      temp->returnList->address = instNo;
    }
}

void patch_returns(struct userfunc* head, unsigned int instrNo){
  while(head){
    if((head->address)>0){
      (instructions+(head->address))->result.val = instrNo;
    }
    head = head->returnList;
  }
}

void patch_incomplete_jumps(unsigned int intermediate_code_size,unsigned int target_code_size){    /* Check code place */
	if(ij_head){
	while(ij_head){
		if (ij_head->iaddress == intermediate_code_size){   
			(instructions+(ij_head->instrNo))->result.val = target_code_size;
		}
		else
			(instructions+(ij_head->instrNo))->result.val = (quads+ij_head->iaddress)->taddress;
		ij_head = ij_head->next;
		}
	}
}

void funcpush(struct userfunc* f){
	assert(stack_size>=stack_top);
	if(stack_size == stack_top){
		struct userfunc* temp = NULL;
		temp = (struct userfunc*)malloc(sizeof(struct userfunc)*50+(sizeof(funcstack)));
		if(funcstack){
			memcpy(temp,funcstack, stack_size);
			free(funcstack);
		}
		funcstack = temp;
		stack_size += 50;
	}
	(funcstack+stack_top)->address = f->address;
	(funcstack+stack_top)->id = f->id;
	(funcstack+stack_top)->localSize = f->localSize;
	(funcstack+stack_top)->index = f->index+1;
	(funcstack+stack_top)->returnList = NULL;
	stack_top++;
}

struct userfunc* funcpop(){
	assert(stack_top);
	stack_top--;
	return (funcstack+stack_top);
}

struct userfunc* functop(){
	assert(stack_top);
	return (funcstack+(stack_top-1));
}
