#include "tabol.h"

static unsigned int makeHash(const char *value){
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; value[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTIPLIER + value[ui];
		return (uiHash%buckets);
	}

void assignType(SymbolTableEntry *entry,enum SymbolTableType type){
	switch(type){
		case GLOBAL:
			entry->type = GLOBAL;
			break;
		case LOCALS:
			entry->type = LOCALS;
			break;
		case FORMAL:
			entry->type = FORMAL;
			break;
		case USERFUNC:
			entry->type = USERFUNC;
			break;
		case LIBFUNC:
			entry->type = LIBFUNC;
			break;
	}
}

SymbolTableEntry *initEntry(){
	SymbolTableEntry *tempEntry;
	tempEntry = malloc(sizeof(SymbolTableEntry));
	tempEntry->isActive = 0;
	tempEntry->cat.varVal = NULL;
	tempEntry->cat.funcVal= NULL;
	tempEntry->type = LOCALS;
	tempEntry->next = NULL;
	tempEntry->link = NULL;
	return tempEntry;
}

SymbolTableEntry *newEntry(const char *value, enum SymbolTableType type, unsigned int lineNo, unsigned int scope){
	SymbolTableEntry *tempEntry;
	tempEntry = malloc(sizeof(SymbolTableEntry));
	tempEntry->isActive = 1;
	tempEntry->type = type;
	
	if (type == GLOBAL || type == LOCALS || type == FORMAL){
		Variable *newVar;
		newVar = malloc(sizeof(Variable));
		tempEntry->cat.varVal = newVar;
		newVar->value = strdup(value);
		newVar->lineNo = lineNo;
		newVar->scope = scope;
	}
	else{
		Function *newFunc;
		newFunc = malloc(sizeof(Function));
		tempEntry->cat.funcVal = newFunc;
		newFunc->value = strdup(value);
		newFunc->lineNo = lineNo;
		newFunc->scope = scope;
	}
	assignType(tempEntry,type);
	tempEntry->link = NULL;
	tempEntry->next = NULL;
	return tempEntry;
}
	
symTable createTable(){
	symTable table; 
	table = malloc(sizeof(struct symTable));
	table->entries = 0;
	SymbolTableEntry * temp;
	ScopeHead = malloc(sizeof(scopeLink));
 	ScopeHead->scope = 0;
 	ScopeHead->entries = NULL;
 	ScopeHead->next = NULL;
	int i;
	for (i=0; i<buckets; i++){
		temp = initEntry();
		table->h_table[i] = temp;
	}
	return table;
}
	
void insert(symTable table, const char *value, enum SymbolTableType type, unsigned int lineNo, unsigned int scope){
	unsigned int ui;
	ui = makeHash(value);
		SymbolTableEntry *curr;
	curr = table->h_table[ui];
	
	while (curr->next != NULL){
		curr = curr->next;
		
	}
	curr->next = newEntry(value, type, lineNo, scope);

	if(type == LIBFUNC){
		struct symbol* sym = NULL;
		sym = (struct symbol*)malloc(sizeof(struct symbol));
		sym->type = libraryfunc_s;
		sym->name = strdup(value);
		sym->space = programvar;
		sym->offset = 0;
		sym->scope = 0;
		sym->line = 0;
		curr->next->sym = sym;
	}
	addScopeNode(curr->next, scope);
}

int lookUp(symTable table, const char *value){
	size_t ui;
	ui = makeHash(value);
	SymbolTableEntry *curr;
	curr = table->h_table[ui];
	while ((curr->next != NULL) && (curr->isActive != 1)){
		curr = curr->next;
	}
	if (curr->isActive == 1){
		return 1;
	}
	else{
		return 0;
	}
}
SymbolTableEntry* lookUpScope(symTable table, const char *value, enum SymbolTableType type, unsigned int scope){
	size_t ui;
	ui = makeHash(value);
	SymbolTableEntry *curr;
	curr = table->h_table[ui];
	while(curr->next != NULL){
		if (curr->isActive == 1){
			if (((((curr->type == GLOBAL) || (curr->type == LOCALS) || (curr->type == FORMAL)) && ((type == USERFUNC) || (type == LIBFUNC))) || (((curr->type == USERFUNC) || (curr->type == LIBFUNC)) && ((type == GLOBAL) || (type == LOCALS) || (type == FORMAL))))&&(curr->cat.varVal->scope == scope)){
				return curr;
			}
			else{
				if ((curr->type == LOCALS) || (curr->type == GLOBAL) || (curr->type == FORMAL)){
					if(curr->cat.varVal->scope == scope) return curr;
				}
				else{
					if(curr->cat.funcVal->scope == scope) return curr;
				}
			}
		}
		curr = curr->next;
	}

	if (curr->isActive == 1){
			if (((((curr->type == GLOBAL) || (curr->type == LOCALS) || (curr->type == FORMAL)) && ((type == USERFUNC) || (type == LIBFUNC))) || (((curr->type == USERFUNC) || (curr->type == LIBFUNC)) && ((type == GLOBAL) || (type == LOCALS) || (type == FORMAL))))&&(curr->cat.varVal->scope == scope)){
				return curr;
			}
			else{
				if ((curr->type == LOCALS) || (curr->type == GLOBAL) || (curr->type == FORMAL)){
					if(curr->cat.varVal->scope == scope) return curr;
				}
				else{
					if(curr->cat.funcVal->scope == scope) return curr;
				}
			}
		}
		return NULL;
}




void addScopeNode( SymbolTableEntry *elemAdded, unsigned int scope){
 	scopeLink *scopeNode;
 	scopeNode = malloc(sizeof(scopeLink));
 	scopeNode = ScopeHead;
 	SymbolTableEntry *curr;
 	curr = malloc(sizeof(SymbolTableEntry));
 	while ((scopeNode->next != NULL) && (scopeNode->scope != scope)){
  		scopeNode = scopeNode->next;
 	}
	if (scopeNode->scope == scope){
    		curr = scopeNode->entries;
  		if(curr != NULL){
   			while (curr->link != NULL){
    				curr = curr->link;
   			}
  		}
 	 	if(curr == NULL){
  		  	curr = elemAdded;
  		}
  			else{
     				curr->link = elemAdded;
  			} 	
	 	}
 	else{
  		scopeLink *newScope;
  		newScope = malloc(sizeof(scopeLink));
  		newScope->scope = scope;
  		newScope->next = NULL;
  		newScope->entries = elemAdded;
 		scopeNode->next = newScope; 
		scopeNode = scopeNode->next;
		scopeNode->next = NULL;
 		}
	}
	
void hide(symTable table, unsigned int scope){
	scopeLink *scopeNode;
	scopeNode = ScopeHead;
	SymbolTableEntry *currEntry;
	while ((scopeNode->scope != scope) && (scopeNode->next != NULL)){
		scopeNode = scopeNode->next;
	}
	currEntry = scopeNode->entries;
	if (currEntry != NULL){
		while (currEntry->link != NULL){
			currEntry->isActive = 0;
			currEntry = currEntry->link;
		}
		currEntry->isActive = 0;
	}
}

char* getType(SymbolTableEntry *entry){
	switch(entry->type){
		case GLOBAL:
			return("GLOBAL");
		case LOCALS:
			return("LOCALS");
		case FORMAL:
			return("FORMAL");
		case USERFUNC:
			return("USERFUNC");
		case LIBFUNC:
			return("LIBFUNC");
	}
}

void printTabol(symTable table){
         unsigned int i;
         SymbolTableEntry *curr;
         for(i=0; i<buckets; i++){
                 curr = table->h_table[i];
                 while(curr !=NULL){
					if(curr->cat.varVal){
                         printf("%d:   value:%s   type:%s    scope:%d       isActive:  %d\n",curr->cat.varVal->lineNo,curr->cat.varVal->value,getType(curr),curr->cat.varVal->scope,curr->isActive);
					}
					curr = curr->next;
                 }
         }
 }





