/**
 *@file 		utility.h

		libreria contenente direttive al preprocessore di utilità generale e nuove tipologie di variabili.


@author		Marzocca Mauro

@version	Versione: 1.0	Creazione: 24/10/2018

 */

/*librerie di sistema necessarie*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*librerie personali necessarie*/




/*direttive al preprocessore per la definizione di costanti*/

///Se ID < NUM_FUNZIONI la funzione non è modificabile
#define NUM_FUNZIONI 64
///Se ID < NUM_LIB la libreria non è modificabile
#define NUM_LIB 6
///Dimensione della struct RECORD_FUN
#define DIM_STRUCT_FUN 656		
///Dimensione della struct RECORD_LIB
#define DIM_STRUCT_LIB 408		

///Lunghezza del campo "Tipo"
#define TIPO 56
///Lunghezza del campo "Nome"
#define LUNG_NOME 32
///Lunghezza del campo "Librerie"
#define LIBRERIA 64
///Lunghezza del campo "Descrizione"
#define DESCRIZIONE 308
///Lunghezza del campo "Ritorno"
#define RITORNO 64
///Lunghezza del campo "Licenza"
#define LICENZA 64
///Lunghezza del campo "Parametri"
#define PARAMETRI 128
///Massima lunghezza di un intero
#define MAX_INT 4

/*definizione nuovi tipi*/


/**
 *
 *Struct costruita per contenere i record dedicati alle funzioni contenuti nei file:
 *
 *function.dat
 *
 *fun_sorted.dat
 */

typedef struct
{
	///ID della funzione letta
	int ID; //4 byte
	///Nome della funzione letta
	char nome[LUNG_NOME]; //32 byte
	///Tipologia della funzione letta
	char tipo[TIPO]; //56 byte
	///libreria di appartenenza della funzione letta
	char librerie[LIBRERIA]; // 64 byte
	///Descrizione della funzione letta
	char descrizione[DESCRIZIONE]; //308 byte
	///Valore di ritorno della funzione letta
	char ritorno[RITORNO];		//64 byte 
	///parametri della funzione letta
	char parametri[PARAMETRI];	//128 byte
} record_fun ;		//struct per gestire i record delle funzioni

/**
 *struct costruita per contenere i record dedicati alle librerie contenuti nei file:
 *
 *lib.dat
 *
 *lib_sorted.dat
 *
 */

typedef struct 
{
	///ID della libreria letta
	int ID;		//4 byte
	///nome della libreria letta
	char nome[LUNG_NOME];		//32 byte
	///descrizione della libreria letta
	char descrizione[DESCRIZIONE];	//308 byte
	///licenza della libreria letta
	char licenza[LICENZA];	
} record_lib ;		//struct per la gestione dei record relativi alle librerie

/*dichiarazione di funzioni*/

/**
 *Funzione di ricerca all'interno dei due file principali del progetto
 *
 *@param funzioni (variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 *@param lib
 *
 *@return 0 se non trova nulla 1 se trova almeno un risultato
 */
int ricerca(FILE* funzioni, FILE* lib);		/*funzione dedicata alla ricerca*/


/**
 *Converte un intero in una stringa
 *
 *
 *
 *@param str[]
 *
 *@param num
 */
void tostring(char str[], int num);		/*conversione di un int in char*/


/**
 *Funzione implementata nell'ordinamento e dedicata allo swap di due funzioni adiacenti in un array
 *
 *
 *
 *@param *array
 *
 *@param i
 */
void scambio_funzioni(record_fun *array, int i);		/*funzione di scambio funzioni necessaria all'ordinamento dove *array è l'array da ordinare e i è il parametro da considerare per ordinare*/
/**
 *Funzione implementata nell'ordinamento e dedicata allo swap di due librerie adiacenti in un array
 *
 *
 *
 *@param *array
 *
 *@param i
 */
void scambio_lib(record_lib *array, int i);				/*funzione di scambio librerie necessaria all'ordinamento dove *array è l'array da ordinare e i è il parametro da considerare per ordinare*/
/**
 *Funzione che implementa il caricamento da file delle funzioni
 *
 *
 *
 *@param funzioni (variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 *@param i
 *
 *@return una struct "record_fun" se riesce la lettura, altrimenti NULL
 */
record_fun load_funzioni(FILE* funzioni,int i);			/*funzione che legge una struct dal file*/
/**
 *Funzione che implementa il caricamento da file delle librerie
 *
 *
 *
 *@param *lib
 *
 *@param i
 *
 *@return una struct "record_lib" se riesce la lettura, altrimenti NULL
 */
record_lib load_lib(FILE* lib,int i);					/*funzione che legge una struct dal file*/

