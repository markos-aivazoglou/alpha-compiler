#ifndef TCODE_H
#define TCODE_H
#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(struct instruction))
#define NEW_SIZE (EXPAND_SIZE*sizeof(struct instruction)+CURR_SIZE)	
#define MAGIC_NUMBER 22752352
#include <stdio.h>
#include <string.h>
#include "intermediate.h"

double		numConsts[EXPAND_SIZE];
char*		stringConsts[EXPAND_SIZE];
char*		namedLibfuncs[EXPAND_SIZE];
struct 		userfunc* userFuncs;
char**		varConsts;

struct var_table* varhead;
struct var_table{
	unsigned int offset;
	char*	var_name;
	struct var_table* next;
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
	assign_v=0,
	add_v=1,			
	sub_v=2,
	mul_v=3,			
	div_v=4,			
	mod_v=5,
	uminus_v=6,
	and_v=7,			
	or_v=8,
	not_v=9,			
	jump_v=10,			
	jeq_v=11,		
	jne_v=12,
	jle_v=13,			
	jge_v=14,			
	jlt_v=15,
	jgt_v=16,			
	call_v=17,			
	pusharg_v=18,
	funcenter_v=19,		
	funcexit_v=20,		
	newtable_v=21,
	tablegetelem_v=22,		
	tablesetelem_v=23,		
	nop_v=24
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

struct incomplete_jump{
	unsigned int instrNo;	// The jump instruction number.
	unsigned int iaddress;	// The i-code jump-target address.
	struct incomplete_jump*	next;	// A trivial linked list.
};

void expand_instructions(void);
void emit_instruction(struct instruction* t);
void printInstructions();
void printVMarg(struct vmarg* arg);
void printInstrOp(enum vmopcode op);
void printTables();
void printStringTable();
void printNumTable();
void printUserfuncTable();
void printLibfuncTable();
void newvar(unsigned int offset, char* name);
void printVar(unsigned int offset);
unsigned int consts_newstring(char* s);
unsigned int consts_newnumber(double n);
unsigned int userfuncs_newfunc(struct symbol* sym);  //Pinakes sta8erwn timwn  KAI synarthsewn
unsigned int libfuncs_newused(char* s);
void printLibfuncTable_tofile(FILE* fp);
void printStringTable_tofile(FILE* fp);
void printUserfuncTable_tofile(FILE* fp);
void printNumTable_tofile(FILE* fp);
void printInstructions_tofile(FILE* fp);
void printVMarg_tofile(struct vmarg* arg,FILE* fp);
void printInstrOp_tofile(enum vmopcode op,FILE* fp);
void make_operand(expr* e, struct vmarg* arg);
void make_numberoperand(struct vmarg* arg, double val);
void make_booloperand(struct vmarg* arg, unsigned char val);
void make_retvaloperand(struct vmarg* arg);
void generate_instr(enum vmopcode op,quad* quad);
void generate(void);
void generate_relational (int op,quad* quad);
void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void append(struct userfunc* head, unsigned int instNo);
void patch_returns(struct userfunc* head, unsigned int instrNo);
void printDouble(double x);
/* Texniki paragwgis telikou kwdika */
extern void generate_ADD (quad* quad);
extern void generate_SUB (quad* quad);
extern void generate_MUL (quad* quad);
extern void generate_DIV (quad* quad);
extern void generate_MOD (quad* quad);
extern void generate_NEWTABLE (quad* quad);
extern void generate_TABLEGETELEM (quad* quad); //Anti gia tablegetelm pou exei sto front5.
extern void generate_TABLESETELEM (quad* quad);
extern void generate_ASSIGN (quad* quad);
extern void generate_NOP ();
extern void generate_JUMP (quad* quad);
extern void generate_IF_EQ (quad* quad);
extern void generate_IF_NOTEQ (quad* quad);
extern void generate_IF_GREATER (quad* quad);
extern void generate_IF_GREATEREQ (quad* quad);
extern void generate_IF_LESS (quad* quad);
extern void generate_IF_LESSEQ (quad* quad);
extern void generate_NOT (quad* quad);
extern void generate_OR (quad* quad);
extern void generate_AND(quad* quad);
extern void generate_PARAM (quad* quad);
extern void generate_CALL (quad* quad);
extern void generate_GETRETVAL (quad* quad);
extern void generate_FUNCSTART (quad* quad);
extern void generate_RETURN (quad* quad);
extern void generate_FUNCEND (quad* quad);
void patch_incomplete_jumps(unsigned int intermediate_code_size,unsigned int target_code_size);
void funcpush(struct userfunc* f);
struct userfunc* funcpop();
struct userfunc* functop();
unsigned int currprocessedquad();
unsigned int nextinstructionlabel();
void reset_operand(struct vmarg *arg);
#endif

	
