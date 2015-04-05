#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0

typedef struct node *SymTable_T;

/*H synarthsh auth epistrefei ena kainourgio SymTable_T pou einai adeio.*/
SymTable_T SymTable_new(void);

/*H synarthsh auth prepei na eleu8erwnei olh th mnhmh pou xrhsimopoihtai apo to oSymtable
  An to oSymtable einai NULL h ynarthsh den kanei tipota.*/
void SymTable_free( SymTable_T oSymTable);

/*H synarthsh auth prepei na epistrefei ton ari8mo twn bindings sto oSymtable*/
unsigned int SymTable_getLength(SymTable_T oSymTable);

/*H synarthsh auth prepei an den yparxei binding me kleidi pcKey sto oSymtable , na pros8etei ena
  kainourgio binding me kleidi to pcKey kai thn timh value kai 8a epistrefei 1.Alliws den allazei
  to oSymtable kai epistrefei 0 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);

/*H synarthsh auth prepei an yparxei binding me kleidi pcKey sto oSymtable , na afairei to
  binding apo to oSymtable kai na epistrefei 1.Alliws den allazei to oSymtable kai
  epistrefei 0 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);

/*H synarthsh auth prepei na epistrefei 1 an to oSymtable periexei ena binding tou opoiou to
  kleidi einai pcKey kai 0 diaforetika. */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

/*H synarthsh auth prepei na epistrefei thn timh tou binding sto oSymtable tou opoiou
  to kleidi einai pcKey h NULL an den uparxei tetoio binding. */
void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

/*H synarthsh auth prepei na efarmozei thn sunarthsh *pfAplly se ka8e binding sto oSymtable
  pernontas to pvExtra ws epipleon parametro.*/
void SymTable_map(SymTable_T oSymTable,

                void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),

                const void *pvExtra);

