/**
 *@file	function.h

	si tratta di una libreria contenente tutte le funzioni inerenti alla manipolazione e visualizzazione
	delle funzioni contenute in un file

	Autori: Marzocca Mauro
	Creazione: 24/10/2018
	Versione: 1.0 Libreria & 2.0 Funzioni
 */

/**
 *Funzione che permette di aggiungere una funzione al file di stream
 *
 *@param funzioni (variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 *
 */
void aggiungi_funzioni(FILE *funzioni);				/* funzione necessaria per aggiungere funzioni al file*/

/**
 *Funzione che permette la modifica di funzioni precaricate (senza poter modificare quelle preinstallate nel programma)
 *
 *@param funzioni (variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 *
 */
void modifica_funzioni(FILE* funzioni);				/*funzione necessaria per modificare le funzioni contenute nel file (solo funzioni modificabili, cioè aggiunte dall'utente)*/

/**
 *Funzione che permette la visualizzazione delle funzione caricate nel file di stream
 *
 *@param funzioni (variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 */
void visualizza_funzioni(FILE *funzioni);			/* funzione che permette la visualizzazione delle funzioni contenute nel file*/

/**
 *Funzione dedicata all'ordinamento delle funzioni contenute nel file di stream
 *
 *ordine=1 ordina per nome
 *
 *ordine=2 ordina per tipo
 *
 *ordine=3 ordina per librerie
 *
 *@param funzioni (Variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 *@param ordine (Variabile Int che indica secondo quale parametro verranno ordinate le funzioni)
 *
 *@return FILE* contenente il puntatore al file ordinato fun_sorted.dat
 */
FILE* ordinamento_funzioni(FILE* funzioni, int ordine);		/*	permette l'ordinamento delle funzioni contenute nel file "function.dat". ordine = variabile che decide secondo quale parametro ordinare restituendo NULL se non riesce ad aprire il file e un puntatore al file se riesce a ordinarlo*/

/**
 *Funzione dedicata alla visualizzazione del file "fun_sorted" che implementa alla funzione di visualizzazione ordinaria un algoritmo di ricerca per l'ID
 *
 *@param funzioni (Variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni ma ordinate diversamente rispetto al file "function.dat")
 *
 *
 */
void visualizza_fun_sorted(FILE *funzioni);				/*visualizza le funzioni dal file ordinato "fun_sorted"*/


/**
 *cancella una funzione inserita dall'utente.
 *
 *
 *@param funzioni (variabile FILE* contenente il puntatore al file di stream contenente tutte le funzioni)
 *
 */
void cancellazione_funzioni(FILE* funzioni);
