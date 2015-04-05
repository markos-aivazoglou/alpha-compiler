#include "symtable.h"
#define HASH_MULTIPLIER 65599
#define buckets 509
	
SymTable_T *htable[buckets];	
	
struct node{
        char *key;
        void *value;
        struct node *next;
};
	
	
/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey){

	size_t ui;
	unsigned int uiHash = 0U;

	for (ui = 0U; pcKey[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
return uiHash;
}


/*H synarthsh auth epistrefei ena kainourgio SymTable_T pou einai adeio.*/
SymTable_T SymTable_new(void){
        
	SymTable_T *cell;
	int i;
	for(i=0; i<509; i++)
		cell[i]=NULL;

return (*cell);
}

/*H synarthsh auth prepei na eleu8erwnei olh th mnhmh pou xrhsimopoihtai apo to oSymtable
  An to oSymtable einai NULL h ynarthsh den kanei tipota.*/
void SymTable_free( SymTable_T oSymTable){

	assert(oSymTable != NULL);
	
	SymTable_T *cell = &oSymTable;
	int i;
	
	for(i=0; i<509; i++){
		if(cell[i] != NULL){
			SymTable_T temp1 = cell[i];
			SymTable_T temp2;
				while(temp1->next != NULL){
					temp2=temp1->next;
					free(temp1);
					temp1=temp2;	
				}
				free(temp2);
		}
	}
}

/*H synarthsh auth prepei na epistrefei ton ari8mo twn bindings sto oSymtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable){

	assert(oSymTable != NULL);
	
	SymTable_T *cell = &oSymTable;
	unsigned int i, res=0;
	
	for(i=0; i<509; i++){
		if(cell[i] != NULL){
			SymTable_T temp = cell[i];
				while(temp->next != NULL){
					res++;
					temp=temp->next;	
				}
		}
	}

return res;
}

/*H synarthsh auth prepei an den yparxei binding me kleidi pcKey sto oSymtable , na pros8etei ena
  kainourgio binding me kleidi to pcKey kai thn timh value kai 8a epistrefei 1.Alliws den allazei
  to oSymtable kai epistrefei 0 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){

   int i;
   assert(oSymTable != NULL);
   i=SymTable_contains( oSymTable, pcKey);
   
   if(i==0){
		
		SymTable_T newnode, *cell, temp;
        cell = &oSymTable;
		int index = SymTable_hash(pcKey);
		temp=cell[index];
		
		while( temp->next!=NULL )
			temp=temp->next;
						
			newnode=malloc(sizeof(struct node));
			temp->next=newnode;
			newnode->next=NULL;

			newnode->key=malloc(sizeof(strlen(pcKey)+1)*sizeof(char));
			strcpy( newnode->key, pcKey );
			newnode->value=(void *)pvValue;
		
		return 1;
   }

return 0;
}

/*H synarthsh auth prepei an yparxei binding me kleidi pcKey sto oSymtable , na afairei to
  binding apo to oSymtable kai na epistrefei 1.Alliws den allazei to oSymtable kai
  epistrefei 0 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey){


return 0;
}

/*H synarthsh auth prepei na epistrefei 1 an to oSymtable periexei ena binding tou opoiou to
  kleidi einai pcKey kai 0 diaforetika. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){


return 0;
}

/*H synarthsh auth prepei na epistrefei thn timh tou binding sto oSymtable tou opoiou
  to kleidi einai pcKey h NULL an den uparxei tetoio binding. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){


}

/*H synarthsh auth prepei na efarmozei thn sunarthsh *pfAplly se ka8e binding sto oSymtable
  pernontas to pvExtra ws epipleon parametro.*/
void SymTable_map(SymTable_T oSymTable,

                void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),

                const void *pvExtra){
				
				
				
				
}

