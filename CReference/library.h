/**
@file	library.h

		libreria contenente funzioni per la modifica di librerie nei file.


		Autori: Marzocca Mauro
		Creazione: 24/10/2018
		Versione: 1.0

 */

/**
 *Funzione dedicata alla visualizzazione delle librerie e lib indica il puntatore al file "Lib.dat" contenente i record
 *
 *
 *@param lib (variabile FILE* contenente il puntatore al file di stream contenente tutte le librerie)
 *
 */
void visualizza_librerie(FILE* lib);		/*funzione dedicata alla visualizzazione delle librerie presenti nel file*/

/**
 *Funzione dedicata alla modifica delle librerie e lib indica il puntatore al file "Lib.dat" contenente i record
 *
 *
 *@param lib (variabile FILE* contenente il puntatore al file di stream contenente tutte le librerie)
 *
 */
void modifica_librerie(FILE* lib);			/*modifica le librerie scritte nei file*/

/**
 *Funzione dedicata all'aggiunta delle librerie e lib indica il puntatore al file "Lib.dat" contenente i record
 *
 *
 *@param lib (variabile FILE* contenente il puntatore al file di stream contenente tutte le librerie)
 *
 */
void aggiungi_librerie(FILE* lib);			/*aggiunge una libreria al file */

/**
 *Funzione dedicata alla visualizzazione delle librerie e lib indica il puntatore al file "Lib_sorted.dat" contenente i record, ma a differenza di "Lib.dat" qui i record sono ordinati secondo l'utente
 *
 *
 *@param lib (variabile FILE* contenente il puntatore al file di stream contenente tutte le librerie)
 *
 */
void visualizza_lib_sorted(FILE* lib);		/*visualizza le librerie presenti nel file ordinato */

/**
 *Legge il file "lib.dat" e crea un file "lib_sorted.dat" ordinato:
 *
 *ordine=1 secondo il nome
 *
 *ordine=2 secondo la licenza
 *
 *@param lib (variabile FILE* contenente il puntatore al file di stream contenente tutte le librerie)
 *
 *@param ordine (int che indica il parametro da considerare)
 *
 *@return puntatore a file in caso di ordinamento riuscito, altrimenti NULL
 */
FILE* ordinamento_librerie(FILE* lib, int ordine);		/*ordina le librerie secondo ordine=1) nome ; ordine=2) licenza*/



/**
 *cancella una libreria inserita dall'utente.
 *
 *
 *@param lib (variabile FILE* contenente il puntatore al file di stream contenente tutte le librerie)
 *
 */

void cancellazione_librerie(FILE* lib);		/*cancella una libreria inserita*/
