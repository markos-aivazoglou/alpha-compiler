#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H
#include "tabol.h"
#include "stack.h"
#include "lists.h"
extern symTable Table;
extern int yylineno;
extern int scope;
enum iopcode{
	assign,add,sub,mul,divi,mod,
	uminus,and,or,not,if_eq,if_noteq,
	if_lesseq,if_greatereq,if_less,
	if_greater,call,param,
	ret,getretval,funcstart,funcend,
	tablecreate,	tablegetelem,jump,tablesetelem
};

enum expr_t{

	var_e,
	tableitem_e,
	programfunc_e,
	libraryfunc_e,
	arithmexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,
	constnum_e,
	constbool_e,
	conststring_e,
	nil_e
};
typedef struct expr{
	enum  expr_t	type;
	struct symbol* sym;
	struct expr*	index;
	int method;
	struct expr* elist;
	double	numConst;
	char*	strConst;
	unsigned char	boolConst;
	struct list* truelist;
	struct list* falselist;
	struct list* breaklist;
	struct list* conlist;
	struct expr*	next;
}expr;

struct quad {
	enum iopcode   op;
	expr*	  result;
	expr*	  arg1;
	expr*	  arg2;
	int label;
	unsigned int line;
	unsigned int target;
	unsigned int taddress;
};

typedef struct quad quad;

void emit(enum iopcode op,expr* arg1,expr* arg2,expr* result,unsigned int label,unsigned int line);
expr* emit_iftableitem(expr* e);

unsigned int currScope(void);


unsigned int istempname(char* s);//onomata temp metavlhtwn
unsigned int istempexpr(expr* e);

expr* newexpr (enum expr_t t);
expr* newexpr_constnum(double i);//
expr* newexpr_conststring(char* s);
expr* newexpr_constbool(unsigned char c);
expr* member_item(expr* lvalue,char * id);
expr* lvalue_expr(struct symbol* sym);
expr* op_expr(symTable Table,enum iopcode op,expr* arg1,expr* arg2);
expr* bool_expr(symTable Table,enum iopcode op,expr* arg1,expr* arg2);
expr* logic_expr(symTable Table,enum iopcode op,expr* arg1,expr* arg2);
expr* make_call(expr* lvalue,expr* elist);
expr* makeTarget(unsigned int i);
expr* reverse(expr* root);

void resetformalargsoffset(void);
void resetfunctionlocalsoffset(void);
void restorecurrscopeoffset(unsigned n);

unsigned int nextquadlabel (void);
void patchlabel (unsigned int quadNo, unsigned int label);

void expand (void);

enum scopespace_t currscopespace(void);		//new
unsigned int currscopeoffset(void);		//new
void inccurrscopeoffset(void);			//new
void enterscopespace(void);				//new
void exitscopespace(void);
				//new
void comperror(char* format);			//new
void checkuminus(expr* e);
				//new
char* newTempName(void);
struct symbol* newtemp(symTable Table);
struct symbol* newSymbol(const char* name);
void resetTemp(void);

void printQuads(void);
void printExpr(expr* arg);
void printOp(quad* p);
void printQuads2(void);
void printExpr2(expr* arg,FILE * fp);
void printOp2(quad* p,FILE * fp);

void initFuncArray(void);
char * funcNameGen(void);
unsigned int currScope(void);
#endif
