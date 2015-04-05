#include "symtable.h"

struct node{
        char *key;
        void *value;
        struct node *next;
};


/*H synarthsh auth epistrefei ena kainourgio SymTable_T pou einai adeio.*/
SymTable_T SymTable_new(void){

        SymTable_T head;
        head=NULL;
        head=malloc(sizeof(struct node));
        head->next=NULL;

return head;
}

/*H synarthsh auth prepei na eleu8erwnei olh th mnhmh pou xrhsimopoihtai apo to oSymtable
  An to oSymtable einai NULL h synarthsh den kanei tipota.*/
void SymTable_free(SymTable_T oSymTable){

        assert(oSymTable != NULL);
        if( oSymTable!=NULL ){
                SymTable_T temp1, temp2;
                temp1=malloc(sizeof(struct node));
                temp2=malloc(sizeof(struct node));
                temp1=oSymTable;
                        while( temp1->next!=NULL ){
                                temp2=temp1->next;
                                free(temp1);
                                temp1=temp2;
                        }
        }
}

/*H synarthsh auth prepei na epistrefei ton ari8mo twn bindings sto oSymtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable){

        unsigned int i=0;
        SymTable_T temp;
        assert(oSymTable != NULL);
        temp=oSymTable;

        while( temp->next!=NULL ){
                i++;
                temp=temp->next;
        }

        /*free(temp);*/

return i;
}


/*H synarthsh auth prepei an den yparxei binding me kleidi pcKey sto oSymtable , na pros8etei ena
  kainourgio binding me kleidi to pcKey kai thn timh value kai 8a epistrefei 1.Alliws den allazei
  to oSymtable kai epistrefei 0 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue){

        int i;
        assert(oSymTable != NULL);
        i=SymTable_contains( oSymTable, pcKey);

        if( i==0 ){

                SymTable_T temp, newnode;
                temp=oSymTable;

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

        int i;

        assert(oSymTable != NULL);
        i=SymTable_contains( oSymTable, pcKey);

        if( i==1 ){

                SymTable_T previous, delete;
                delete=oSymTable;

                while( delete->next!=NULL ){
                        if( ( delete->key!=NULL ) && strcmp( pcKey, delete->key ) == 0 ){
                                if( delete==oSymTable ){
                                        oSymTable=delete->next;
                                        free(delete);
                                        return 1;
                                }
                                else{
                                        previous->next=delete->next;
                                        free(delete);
                                        return 1;
                                }
                        }
                        else{
                                previous=delete;
                                delete=delete->next;
                        }
                }


        }

return 0;
}

/*H synarthsh auth prepei na epistrefei 1 an to oSymtable periexei ena binding tou opoiou to
  kleidi einai pcKey kai 0 diaforetika. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){

        int i=0;
        SymTable_T temp;
        temp = oSymTable;
        assert(oSymTable != NULL);

        while( temp->next!=NULL ){
                if( ( temp->key!=NULL ) && strcmp( pcKey, temp->key ) == 0 )
                        return 1;
                else
                        temp=temp->next;

        }

return i;
}

/*H synarthsh auth prepei na epistrefei thn timh tou binding sto oSymtable tou opoiou
  to kleidi einai pcKey h NULL an den uparxei tetoio binding. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){

        int i=SymTable_contains( oSymTable, pcKey);

        if( i==1 ){

                SymTable_T temp;
                assert(oSymTable != NULL);
                temp=oSymTable;

                while( temp->next!=NULL ){
                        if( ( temp->key!=NULL ) && strcmp( pcKey, temp->key ) == 0 )
                                return (void *)temp->value;
                        else
                                temp=temp->next;
                }

        }

return NULL;
}


/*H synarthsh auth prepei na efarmozei thn sunarthsh *pfAplly se ka8e binding sto oSymtable
  pernontas to pvExtra ws epipleon parametro.*/
void SymTable_map(SymTable_T oSymTable,

                void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),

                const void *pvExtra){

                        SymTable_T temp;
                        assert(oSymTable != NULL);
                        assert(pfApply != NULL);
                        temp = oSymTable;
                        while (temp != NULL) {
                                if (temp->value != NULL)
                                        pfApply(temp->key, &(temp->value), (void *)pvExtra);
                                temp = temp->next;
                        }
                        return;
}



