#define AVM_STACKSIZE	4096
#define AVM_WIPEOUT(m)	memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE	211
/* **** Ylopoiisi ari8mitikwn entolwn start **** */
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS  (unsigned) nop_v
#define AVM_ENDING_PC  codeSize
#define AVM_NUMACTUALS_OFFSET		4
#define AVM_SAVEDPC_OFFSET		+3
#define AVM_SAVEDTOP_OFFSET		+2
#define AVM_SAVEDTOPSP_OFFSET		+1
#define EXPAND_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


double		numConsts[EXPAND_SIZE];
char*		stringConsts[EXPAND_SIZE];
char*		namedLibFuncs[EXPAND_SIZE];
struct 		userfunc* userFuncs;


enum avm_memcell_t{
	number_m 	=0,
	string_m	=1,
	bool_m		=2,
	table_m		=3,
	userfunc_m	=4,
	libfunc_m	=5,
	nil_m		=6,
	undef_m		=7
};
struct avm_memcell{
	enum avm_memcell_t type;
	union{
		double			numVal;
		char*			strVal;
		unsigned char 		boolVal;
		struct avm_table*	tableVal;
		unsigned int		funcVal;
		char*			libfuncVal;
	} data;
};




struct avm_table_bucket{
	struct	avm_memcell		key;
	struct	avm_memcell		value;
	struct	avm_table_bucket*	next;
};

struct avm_table{
	unsigned	refCounter;
	struct 		avm_table_bucket*	strIndexed[AVM_TABLE_HASHSIZE];
	struct		avm_table_bucket*	numIndexed[AVM_TABLE_HASHSIZE];
	unsigned	total;
};

enum vmarg_t{
	label_a			=0,
	global_a		=1,
	formal_a		=2,
	local_a			=3,
	number_a		=4,
	string_a		=5,
	bool_a			=6,
	nil_a			=7,
	userfunc_a		=8,
	libfunc_a		=9,
	retval_a		=10
};

enum vmopcode{
	assign_v,		add_v,			sub_v,
	mul_v,			div_v,			mod_v,
	uminus_v,		and_v,			or_v,
	not_v,			jump_v,			jeq_v,		jne_v,
	jle_v,			jge_v,			jlt_v,
	jgt_v,			call_v,			pusharg_v,
	funcenter_v,		funcexit_v,		newtable_v,
	tablegetelem_v,		tablesetelem_v,		nop_v
};	

struct vmarg{
	enum vmarg_t type;
	unsigned int val;
	};
/* Paragwgi telikou kwdika, mesw emit, apla exei to parakatw san epipleon orisma. */
struct instruction{
	enum vmopcode opcode;
	struct vmarg	result;
	struct vmarg	arg1;
	struct vmarg	arg2;
	unsigned int srcLine; // yylineno pi8anws
};

struct userfunc{
	unsigned int address;
	unsigned int localSize;
	char*	id;
	unsigned int index;
	struct userfunc* returnList;
};


typedef void (*library_func_t)(void);


typedef void (*memclear_func_t)(struct avm_memcell*);
extern void memclear_string(struct avm_memcell* s);
extern void memclear_table(struct avm_memcell* s);

memclear_func_t memclearFuncs[] = {
	0, /*number*/
	memclear_string,
	0, /*bool*/
	memclear_table,
	0, /*userfunc*/
	0, /*libfunc*/
	0, /*nill*/
	0  /*undef*/
};

/* Execution Cycle */

extern void execute_assign (struct instruction*);
extern void execute_add (struct instruction*);
extern void execute_sub (struct instruction*);
extern void execute_mul (struct instruction*);
extern void execute_div (struct instruction*);
extern void execute_mod (struct instruction*);
extern void execute_uminus (struct instruction*);
extern void execute_and (struct instruction*);
extern void execute_or (struct instruction*);
extern void execute_not (struct instruction*);
extern void execute_jeq (struct instruction*);
extern void execute_jne (struct instruction*);
extern void execute_jump(struct instruction*);
extern void execute_jle (struct instruction*);
extern void execute_jge (struct instruction*);
extern void execute_jlt (struct instruction*);
extern void execute_jgt (struct instruction*);
extern void execute_call (struct instruction*);
extern void execute_pusharg (struct instruction*);
extern void execute_funcenter(struct instruction*);
extern void execute_funcexit (struct instruction*);
extern void execute_newtable (struct instruction*);
extern void execute_tablegetelem (struct instruction*);
extern void execute_tablesetelem (struct instruction*);
extern void execute_nop (struct instruction*);





typedef void (*execute_func_t)(struct instruction*);
execute_func_t executeFuncs[]={
	execute_assign,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	execute_uminus,
	execute_and,
	execute_or,
	execute_not,
	execute_jump,
	execute_jeq,
	execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jgt,
	execute_call,			
	execute_pusharg,		
	execute_funcenter,
	execute_funcexit,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	execute_nop
};


extern char* number_tostring(struct avm_memcell*);
extern char* string_tostring(struct avm_memcell*);
extern char* bool_tostring(struct avm_memcell*);
extern char* table_tostring(struct avm_memcell*);
extern char* userfunc_tostring(struct avm_memcell*);
extern char* libfunc_tostring(struct avm_memcell*);
extern char* nil_tostring(struct avm_memcell*);
extern char* undef_tostring(struct avm_memcell*);
typedef char* (*tostring_func_t)(struct avm_memcell*);
tostring_func_t tostringFuncs[] = {
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};


/* Dispatcher just for arithmetic functions. */

typedef double(*arithmetic_func_t)(double x,double y);
double add_impl(double x,double y);
double sub_impl(double x,double y);
double mul_impl(double x,double y);
double div_impl(double x,double y);
double mod_impl(double x,double y);
void execute_arithmetic(struct instruction* instr);

arithmetic_func_t arithmeticFuncs[]={
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
};

typedef unsigned char (*tobool_func_t)(struct avm_memcell*);
unsigned char number_tobool (struct avm_memcell* m);
unsigned char string_tobool (struct avm_memcell* m);
unsigned char bool_tobool (struct avm_memcell* m);
unsigned char table_tobool (struct avm_memcell* m);
unsigned char userfunc_tobool (struct avm_memcell* m);
unsigned char libfunc_tobool (struct avm_memcell* m);
unsigned char nil_tobool (struct avm_memcell* m);
unsigned char undef_tobool (struct avm_memcell* m);
tobool_func_t toboolFuncs[] = {
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};


char* typeStrings[]={
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfun",
	"nil",
	"undef"
};

struct avm_table;
struct instruction*	code = (struct instruction*) 0;
unsigned char 		executionFinished = 0;
unsigned int		pc = 0;
unsigned int		currLine = 0;
unsigned int		codeSize = 0;
unsigned int		totalActuals = 0; //refering to calling functions
// struct userfunc* funcInfo = avm_getfuncinfo(pc);
struct avm_memcell ax, bx, cx;
struct avm_memcell retval;
unsigned int top, topsp;
struct avm_memcell stack[AVM_STACKSIZE];




extern void avm_warning(char* format,...);//de kserw einai meta to ,
extern void avm_assign (struct avm_memcell* lv,struct avm_memcell* rv);

double consts_getnumber(unsigned int index);   
char* consts_getstring(unsigned int index);
struct userfunc* userfuncs_getfuncs(unsigned int index);
char* libfuncs_getused(unsigned int index);

void execute_arithmetic(struct instruction* instr);
extern void avm_error(char*format,...);
extern char* avm_tostring (struct avm_memcell*); //Caller frees
extern void avm_calllibfunc(char* funcName);//Calling functions
extern void avm_callsaveenvironment(void);
extern struct userfunc* avm_getfuncinfo(unsigned int address);
library_func_t avm_getlibraryfunc(char* id); /* Typical Hashing*/
void avm_registerlibfunc(char* id,library_func_t addr);


struct avm_table* avm_tablenew(void);
void  avm_tabledestroy(struct avm_table* t);
struct avm_memcell* avm_tablegetelem(struct avm_table*	table,struct avm_memcell* index);
void avm_tablesetelem(struct avm_table* table,struct avm_memcell* index,struct avm_memcell* content);
void avm_tablebucketsinit(struct avm_table_bucket** p);
void avm_tabledecrefcounter(struct avm_table* t);
void avm_tableincrefcounter(struct avm_table* t);
static void avm_initstack(void);
void avm_memcellclear(struct avm_memcell* m);
void  avm_tablebucketsdestroy(struct avm_table_bucket** p);
unsigned avm_get_envvalue (unsigned int i);
void libfunc_print(void);

void avm_readbinary(void);
void printDouble();
void printNumTable();
void printUserfuncTable();