#ifndef TABOL_H
#define TABOL_H
#include <stdio.h>
#define HASH_MULTIPLIER 65599
#define buckets 509
#include <assert.h>
#include <string.h>
#include <stdlib.h>


enum SymbolTableType {
	GLOBAL,  LOCALS, FORMAL,USERFUNC, LIBFUNC
};

enum scopespace_t{	//3h fash
	programvar,functionlocal,formalarg
};

enum symbol_t { //3h fash
		var_s,programfunc_s,libraryfunc_s
};


struct symbol {	//3h fash
	enum symbol_t   type;
	char* 	name;
	enum scopespace_t space;
	unsigned int totallocals;
	unsigned int offset;
	unsigned int scope;
	unsigned int line;
	unsigned int iaddress;
	unsigned int taddress;
	};

typedef struct Function {
	char *value;
	unsigned int lineNo;
	unsigned int scope;
} Function;

typedef struct Variable {
	char *value;
	unsigned int lineNo;
	unsigned int scope;
} Variable;

typedef struct SymbolTableEntry {
	int isActive;
	union {
		Variable *varVal;
		Function *funcVal;
	} cat;
	struct symbol* sym;
	enum SymbolTableType type;
	struct SymbolTableEntry *next;
	struct SymbolTableEntry *link;
} SymbolTableEntry;

typedef struct scopeLink{
 unsigned int scope;
 SymbolTableEntry *entries;
 struct scopeLink *next;
}scopeLink;

 scopeLink *ScopeHead;


typedef struct symTable{
	SymbolTableEntry *h_table[buckets];
	int entries;
} *symTable;

//Returning hash code.
static unsigned int makeHash(const char *value);

symTable createTable();
void assignType(SymbolTableEntry *entry, enum SymbolTableType type);
char* getType(SymbolTableEntry *entry);
SymbolTableEntry *newEntry(const char *value, enum SymbolTableType type,unsigned int lineNo,unsigned int scope);
SymbolTableEntry *initEntry();

void insert(symTable table, const char *value, enum SymbolTableType type,unsigned int lineNo,unsigned int scope);
int lookUp(symTable table, const char *value);
SymbolTableEntry* lookUpScope(symTable table, const char *value, enum SymbolTableType type, unsigned int scope);
void hide(symTable table, unsigned int scope);
void printActive(symTable table);
void addScopeNode( SymbolTableEntry *elemAdded, unsigned int scope);
void hide(symTable table, unsigned int scope);
void printTabol(symTable table);
#endif
