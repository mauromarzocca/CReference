/*sorgente legato al file library.h*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*librerie personali necessarie*/
#include "utility.h"
#include "library.h"

void visualizza_librerie(FILE* lib)	//funzione che svolge la visualizzazione delle librerie
{
	int n_lib = 0;
	int ID = 0;
	int i = 0;
	int j = 0;
	int selezione = 0;

	char c[11] = { 0 };
	char n_lib_c[4] = { 0 };

	record_lib visualizza; /*struct sulla quale vengono caricati i record*/

	FILE* counter = NULL;
	counter = fopen("counter.dat", "rb");//dichiarazione e apertura del file counter, utile per la numerazione delle funzioni e delle librerie
	if (counter == NULL)		//controllo sull'apertura del file counter
	{
		printf(
				"L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");
		getchar();
	} else {
		system("cls");
		fseek(counter, sizeof(int), SEEK_SET);	//caricamento numero librerie
		fgets(n_lib_c, sizeof(int), counter);
		n_lib = atoi(n_lib_c);			//conversione del numero in intero
		system("cls");
		do {
			do {
				printf("----------------------------------\n"); /**/
				printf("| ID \t|\t Nome\n"); /* visualizzazione delle librerie presenti nel file*/
				printf("----------------------------------\n"); /**/
				for (i = 0; i < n_lib; i++) /**/
				{ /**/
					fseek(lib, (sizeof(visualizza) * i), SEEK_SET); /**/
					fgets(c, sizeof(visualizza.ID), lib); /**/
					visualizza.ID = atoi(c); /**/
					fseek(lib,((sizeof(visualizza) * i) + sizeof(visualizza.ID)),SEEK_SET); /**/
					fgets(visualizza.nome, sizeof(visualizza.nome), lib); /**/
					printf("| %d \t|\t %s", visualizza.ID, visualizza.nome); /**/
					printf("----------------------------------\n"); /**/
				}
				printf(
						"Inserire l'ID della libreria che si vuole visualizzare\n\n");//richiesta della libreria da visualizzare
				fgets(c, sizeof(c), stdin);
				fflush(stdin);									//pulizia buffer

				ID = atoi(c);

				if (ID == 0)					//controllo sul valore inserito
				{
					system("cls");
					printf("Il valore inserito non e' corretto\n\n");
					i = 0;
					getchar();
				} else {
					if (ID > n_lib)				//controllo sul valore inserito
					{
						system("cls");
						printf("La funzione selezionata non esiste\n\n");
						i = 0;
						getchar();
					} else {
						i = 1;				//se il valore è corretto flag==1
					}
				}
			} while (i == 0);

			visualizza = load_lib(lib, (ID - 1));

			system("cls");

			printf(
					"ID:\n%d\n\nNome:\n%s\n\nDescrizione:\n%s\n\nLicenza:\n%s\n\n",
					visualizza.ID, visualizza.nome, visualizza.descrizione,
					visualizza.licenza);		//visualizzazione funzione

			getchar();
			fflush(stdin);
			do {
				system("cls");
				printf("Si desidera visualizzare un altra libreria? \n\n1) Uscita\n"
						"2) Visualizzazione altra libreria\n\n");//viene chiesto se continuare o chiudere
				fgets(c, sizeof(c), stdin);

				fflush(stdin);
				selezione = atoi(c);

				switch (selezione) {
				case 1:
					j = 1;
					i = 1;
					system("cls");
					break;
				case 2:
					j = 0;
					i = 1;
					system("cls");
					break;
				default:
					printf("La selezione effettuata non e' valida \n");
					i = 0;
					getchar();
					fflush(stdin);
					system("cls");
				}
			} while (i == 0);
		} while (j == 0);
	}
}

void modifica_librerie(FILE* lib) {
	int i = 0;				/*contatori*/
	int j = 0;
	int t = 0;
	
	int ID_int = 0;			/*varibili di caricamento da char*/
	int ID_appoggio = 0;
	int selezione_int = 0;
	
	int check = 0;				/*flag*/
	int boole = 0;

	record_lib modifica; /*struct che tiene salvato il record presente sul file*/
	record_lib appoggio; /*struct che legge da tastiera le modifiche da effettuare*/

	char ID_selezione[11] = { 0 };	/*variabili di caricamento da file*/
	char selezione[11] = { 0 };

	do {
		do {
			printf("Inserire l'ID della libreria che si vuole modificare o inserire x per uscire\n\n"); /*blocco necessario alla selezione della libreria da modificare*/
			fgets(ID_selezione, sizeof(int), stdin); /**/
			fflush(stdin); /**/
			if (ID_selezione[0] == 'x' || ID_selezione[0] == 'X') {
				i = 1;
				j = 1;
				boole = 1;
			} else {
				boole = 0;
				ID_int = atoi(ID_selezione);
				if (ID_int == 0) /**/
				{
					printf("Il valore inserito non e' valido\n\n"); /*controlli sulla selezione*/
					i = 0;
				} else {
					if (ID_int <= NUM_LIB) /*controlli sulla selezione*/
					{
						printf(
								"La libreria selezionata non e' modificabile \n\n");
						i = 0;
					} else {
						fseek(lib, (-(sizeof(modifica))), SEEK_END);
						fgets(ID_selezione, sizeof(int), lib);
						ID_appoggio = atoi(ID_selezione);
						if (ID_int > ID_appoggio) {
							printf("La libreria n %d non esiste\n\n", ID_int);
							i = 0;
						} else {
							i = 1;
						}
					}
				}
			}
		} while (i == 0);

		if (boole == 0) {
			modifica = load_lib(lib, (ID_int - 1)); /*funzione che permette il caricamento da file del record*/

			do {
				system("cls");
				printf(
						"Quale campo si desidera modificare? ID=%d \n\n1) Nome\t%s\n2) Descrizione\t%s\n3) Licenza\t%s\n4) Uscita\n\n",
						modifica.ID, modifica.nome, modifica.descrizione,
						modifica.licenza);
				fgets(selezione, sizeof(selezione), stdin); /*blocco dedicato alla selezione del valore da modificare*/
				fflush(stdin); /**/

				selezione_int = atoi(selezione); /**/

				if (selezione_int < 1) /*controllo sulla selezione*/
				{
					printf("Il valore inserito non e' valido, riprovare\n\n"); /**/
					i = 0; /**/
					system("cls");
				} else /**/
				{
					j = 0;
					system("cls");
				}

				if (j == 0) /*superati i controlli inizia il blocco dedicato alla modifica dei valori*/
				{
					switch (selezione_int) {
					case 1: /*modifica nome*/
						system("cls");
						fseek(lib,
								((sizeof(modifica) * (ID_int - 1))
										+ sizeof(modifica.ID)), SEEK_SET); /*lettura del valore da tastiera*/
						printf(
								"Inserire il nuovo nome da assegnare alla libreria:\n\n"); /**/
						fgets(appoggio.nome, sizeof(appoggio.nome), stdin); /**/
						check = strlen(appoggio.nome); /**/
						fflush(stdin); /**/

						if (check <= 1) /*controlli fatti sulla lunghezza della stringa inserita	check=lunghezza stringa*/
						{
							system("cls");
							printf(
									"\n\n\nNon e' stata inserita nessun nuovo nome, verrà mantenuto il vecchio nome\n\n"); /*messagggio di errore per la lunghezza inferiore a */
							getchar();
							system("cls");
						} else {
							strcpy(modifica.nome, appoggio.nome); /*superati i controlli viene scritto la stringa sul file*/
							fwrite(modifica.nome, sizeof(modifica.nome), 1,
									lib); /**/
							system("cls");
						}
						i = 0;
						break;

					case 2: /*modifica descrizione*/
						system("cls");
						fseek(lib,
								((sizeof(modifica) * (ID_int - 1))
										+ sizeof(modifica.ID)
										+ sizeof(modifica.nome)), SEEK_SET); /*lettura del valore da tastiera*/
						printf(
								"Inserire la nuova descrizione da assegnare alla libreria:\n\n"); /**/
						fgets(appoggio.descrizione,
								sizeof(appoggio.descrizione), stdin); /**/
						check = strlen(appoggio.descrizione); /**/
						fflush(stdin);

						if (check <= 1) /*controllo sulla lunghezza della stringa*/
						{
							system("cls");
							printf(
									"\n\n\nNon e' stata inserita nessuna nuova descrizione, verrà mantenuto la vecchia descrizione\n\n");
							getchar();
							system("cls");
						}

						else /*se la stringa è accettata*/
						{
							strcpy(modifica.descrizione, appoggio.descrizione);
							fwrite(modifica.descrizione,
									sizeof(modifica.descrizione), 1, lib);
							system("cls");
						}

						i = 0;
						break;

					case 3: /*modifica librerie*/
						system("cls");
						fseek(lib,
								((sizeof(modifica) * (ID_int - 1))
										+ sizeof(modifica.ID)
										+ sizeof(modifica.nome)
										+ sizeof(modifica.descrizione)),
										SEEK_SET); /*lettura valori da tastiera*/
						printf(
								"Inserire i la nuova licenza da assegnare alla funzione:\n\n"); /**/
						fgets(appoggio.licenza, sizeof(appoggio.licenza),
								stdin); /**/
						check = strlen(appoggio.licenza); /**/
						fflush(stdin);

						if (check <= 1) /*controllo sulla lunghezza della stringa*/
						{
							system("cls");
							printf(
									"\n\n\nNon e' stato inserita nessuna licenza, verranno mantenuti i vecchi valori\n\n");
							getchar();
							system("cls");
						}

						else /*se la stringa è accettata*/
						{
							strcpy(modifica.licenza, appoggio.licenza);
							fwrite(modifica.licenza, sizeof(modifica.licenza),
									1, lib);
							system("cls");
						}

						i = 0;
						break;

					case 4: /*uscita senza modifiche*/

						system("cls");
						i = 1;
						break;
					default:
						printf(
								"Il Valore inserito non corrisponde a nessuna selezione, riprovare \n\n");
						i = 0;
						system("cls");
					}
				}
			} while (i == 0);

			t = 0;

			while (t == 0) {
				system("cls");
				printf(
						"Si desidera selezionare una nuova libreria o uscire? \n\n1) Uscire\n2)Selezionare altra libreria\n\n");
				fgets(selezione, sizeof(selezione), stdin);
				fflush(stdin);

				selezione_int = atoi(selezione);

				switch (selezione_int) {
				case 1:
					t = 1;
					j = 1;
					system("cls");
					break;
				case 2:
					t = 1;
					j = 0;
					system("cls");
					break;
				default:
					printf("la selezione effettuata non e' valida\n\n");
					t = 0;
					j = 0;
					system("cls");
				}

			}
		}
	} while (j == 0);
	system("cls");
}

void aggiungi_librerie(FILE* lib) {
	
	int i = 0; 	/*contatori*/
	int c = 0;

	int check = 0;				/*variabile per il controllo sugli input*/
	
	int n_lib = 0;	/*numero librerie*/

	char n_lib_c[4] = { 0 };	/*caricamento numero librerie da file*/
						

	FILE* counter = NULL;

	record_lib nuovo;

	counter = fopen("counter.dat", "rb+");
	if (counter == NULL) /*controllo sull'apertura del file "counter.dat"*/
	{
		printf(
				"L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");
		getchar();
	}

	else {
		system("cls");
		fseek(counter, sizeof(int), SEEK_SET);
		fgets(n_lib_c, sizeof(n_lib), counter);

		n_lib = atoi(n_lib_c);

		n_lib = n_lib + 1;

		tostring(n_lib_c, n_lib);

		printf("Libreria n.%d\n\nPremere invio o premere x per uscire\n\n",
				n_lib);
		c = getchar();
		system("cls");
		fflush(stdin);
		if (c != 'x' && c != 'X') {
			do {
				fwrite(n_lib_c, sizeof(int), 1, lib);
				fflush(stdin);
				printf("Nome : "); /*inserimento nome nuova libreria*/
				fgets(nuovo.nome, sizeof(nuovo.nome), stdin);
				fflush(stdin);
				system("cls");
				check = strlen(nuovo.nome);
				if (check <= 1) /*controlli sulla lunghezza dell'input*/
				{
					printf("Nessun valore inserito, riprovare\n\n"); /*input vuoto*/
					getchar();
					system("cls");
					i = 0;
				} else /*scrittura su file*/
				{
					fwrite(nuovo.nome, sizeof(nuovo.nome), 1, lib);
					system("cls");
					i = 1;
				}
			} while (i == 0);

			do {
				printf("Descrizione : "); /*inserimento nuova descrizione*/
				fgets(nuovo.descrizione, sizeof(nuovo.descrizione), stdin); /**/
				fflush(stdin); /**/
				system("cls"); /**/
				check = strlen(nuovo.descrizione); /**/

				if (check <= 1) /*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n"); /*valore errato*/
					getchar();
					system("cls");
					i = 0;
				} else /*scrittura su file*/
				{
					fwrite(nuovo.descrizione, sizeof(nuovo.descrizione), 1,
							lib);
					system("cls");
					i = 1;
				}
			} while (i == 0);

			do {
				printf("Licenza : "); /*inserimento nuova licenza*/
				fgets(nuovo.licenza, sizeof(nuovo.licenza), stdin); /**/
				fflush(stdin); /**/
				system("cls"); /**/
				check = strlen(nuovo.licenza); /**/

				if (check <= 1) /*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n"); /*valore errato*/
					getchar();
					system("cls");
					i = 0;
				} else {
					fwrite(nuovo.licenza, sizeof(nuovo.licenza), 1, lib); /*scrittura su file*/
					system("cls");
					i = 1;
				}

			} while (i == 0);

			printf("Nuova libreria aggiunta\n\n");

			fseek(counter, sizeof(int), SEEK_SET);
			fwrite(n_lib_c, sizeof(n_lib), 1, counter);
			fclose(counter);
			getchar();
			system("cls");
		}
	}
}

void visualizza_lib_sorted(FILE* lib)//funzione che svolge la visualizzazione delle librerie
{

	int i = 0;				/*counter*/
	int j = 0;
	int l = 0;


	int selezione = 0;		/*variabile per input*/
	
	int indice_lib = 0;		
	
	int n_lib = 0;			/*numero librerie*/
	
	int ID = 0;
	
	char c[11] = { 0 };				/*variabili per il caricamento di int da file*/
	char n_lib_c[4] = { 0 };

	record_lib visualizza;

	FILE* counter = NULL;
	counter = fopen("counter.dat", "rb");//dichiarazione e apertura del file counter, utile per la numerazione delle funzioni e delle librerie
	if (counter == NULL)		//controllo sull'apertura del file counter
	{
		printf(
				"L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");
		getchar();
	} else {
		system("cls");
		fseek(counter, sizeof(int), SEEK_SET);	//caricamento numero librerie
		fgets(n_lib_c, sizeof(int), counter);
		n_lib = atoi(n_lib_c);			//conversione del numero in intero

		system("cls");
		do {
			do {
				printf("----------------------------------\n"); /**/
				printf("| ID \t|\t Nome\n"); /* visualizzazione delle librerie presenti nel file*/
				printf("----------------------------------\n"); /**/
				for (i = 0; i < n_lib; i++) /**/
				{ /**/
					fseek(lib, (sizeof(visualizza) * i), SEEK_SET); /**/
					fgets(c, sizeof(visualizza.ID), lib); /**/
					visualizza.ID = atoi(c); /**/
					fseek(lib,
							((sizeof(visualizza) * i) + sizeof(visualizza.ID)),
							SEEK_SET); /**/
					fgets(visualizza.nome, sizeof(visualizza.nome), lib); /**/
					printf("| %d \t|\t %s", visualizza.ID, visualizza.nome); /**/
					printf("----------------------------------\n"); /**/
				}
				printf(
						"Inserire l'ID della libreria che si vuole visualizzare\n\n");//richiesta della libreria da visualizzare
				fgets(c, sizeof(c), stdin);

				fflush(stdin);									//pulizia buffer
				ID = atoi(c);

				if (ID == 0)					//controllo sul valore inserito
				{
					system("cls");
					printf("Il valore inserito non e' corretto\n\n");
					i = 0;
					getchar();
				} else {
					if (ID > n_lib)				//controllo sul valore inserito
					{
						system("cls");
						printf("La funzione selezionata non esiste\n\n");
						i = 0;
						getchar();
					} else {
						i = 1;				//se il valore è corretto flag==1
					}
				}
			} while (i == 0);

			for (l = 0; l < n_lib; l++) {

				fseek(lib, ((sizeof(visualizza)) * (l)), SEEK_SET); /*posizionamento del puntatore al record da search_lre*/
				fgets(c, sizeof(c), lib); /*lettura valore in lib*/
				visualizza.ID = atoi(c);

				if (visualizza.ID == ID) {
					indice_lib = l;
					l = n_lib + 1;
				}
			}

			visualizza = load_lib(lib, indice_lib);

			system("cls");
			printf(
					"ID:\n%d\n\nNome:\n%s\n\nDescrizione:\n%s\n\nLicenza:\n%s\n\n",
					visualizza.ID, visualizza.nome, visualizza.descrizione,
					visualizza.licenza);		//visualizzazione funzione

			getchar();
			fflush(stdin);
			do {
				system("cls");
				printf(
						"Si desidera visualizzare un altra libreria? \n\n1) Uscita\n2) Visualizzazione altra libreria\n\n");//viene chiesto se continuare o chiudere
				fgets(c, sizeof(c), stdin);

				fflush(stdin);
				selezione = atoi(c);

				switch (selezione) /*controllo sulla correttezza dell'input*/
				{
				case 1:
					j = 1;
					i = 1;
					system("cls");
					break;
				case 2:
					j = 0;
					i = 1;
					system("cls");
					break;
				default:
					printf("La selezione effettuata non e' valida \n");
					i = 0;
					getchar();
					fflush(stdin);
					system("cls");
				}

			} while (i == 0);
		} while (j == 0);
	}
}

FILE* ordinamento_librerie(FILE* lib, int ordine) /*funzione necessaria ad ordinale i record presenti nel file "lib.dat", restituisce NULL se non apre i file e un puntatore a file in caso di riuscita*/
{

	char n_lib_c[4] = { 0 };		/*caricamento numero librerie*/

	int n_lib = 0;					/**/

	int flag = 0;				

	int i = 0;						/*contatori*/
	int j = 0;
	int l = 0;

	FILE* counter = NULL;
	FILE* lib_sorted = NULL;

	lib_sorted = fopen("lib_sorted.dat", "rb+"); /*apertura file "lib.dat"*/
	counter = fopen("counter.dat", "rb"); /*apertura file "counter.dat"*/
	if (counter == NULL || lib_sorted == NULL) {
		printf(
				"L'apertura dei file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");
		getchar();
		return NULL;
	} else {
		system("cls"); /*caricamento numero librerie dal counter*/
		fseek(counter, sizeof(int), SEEK_SET); /**/
		fgets(n_lib_c, sizeof(n_lib), counter); /**/
		n_lib = atoi(n_lib_c); /**/

		record_lib ord_lib[n_lib]; /*dichiarazione vettore da ordinare*/

		for (i = 0; i < n_lib; i++) {
			ord_lib[i] = load_lib(lib, i); /*caricamento record da file*/

		}
		switch (ordine) /*selezione del parametro da ordinare*/
		{
		case 1:

			for (l = 0; l < n_lib; l++) /*ordina in funzione del nome*/
			{
				flag = 0;
				for (i = 0; i < (n_lib - 1); i++) {
					j = strcmp(ord_lib[i + 1].nome, ord_lib[i].nome); /*controlla l' ordine dei due elementi*/
					if (j < 0) {
						scambio_lib(ord_lib, i); /*funzione che scambia i due record dell'array dove ord_lib è l'intero array mentre i è l'indice del valore da scambiare*/
						flag = 1; /*cambia il flag da controllare in seguito*/
					}
				}
				if (flag == 0) /*se il flag è 0, cioè se non sono stati fatti scambi, esce dal ciclo*/
				{
					l = n_lib + 1;
				}
			}
			break;

		case 2:

			for (l = 0; l < n_lib; l++) /*ordina in funzione della licenza*/
			{
				flag = 0;
				for (i = 0; i < (n_lib - 1); i++) {
					j = strcmp(ord_lib[i + 1].licenza, ord_lib[i].licenza); /*controlla l'ordine dei due elementi*/
					if (j < 0) {
						scambio_lib(ord_lib, i); /*funzione che scambia i due record dell'array dove ord_lib è l'intero array mentre i è l'indice del valore da scambiare*/
						flag = 1; /*cambia il flag da controllare in seguito*/
					}
				}
				if (flag == 0) /*se il flag è 0, cioè se non sono stati fatti scambi, esce dal ciclo*/
				{
					l = n_lib + 1;
				}
			}
			break;

		default:
			system("cls");
			printf("selezione non valida\n");
		}
		fseek(lib_sorted, 0, SEEK_SET);
		for (i = 0; i < n_lib; i++) /*scrittura del file ordinato*/
		{
			tostring(n_lib_c, ord_lib[i].ID);
			fwrite(n_lib_c, sizeof(int), 1, lib_sorted);
			fwrite(ord_lib[i].nome, sizeof(ord_lib[i].nome), 1, lib_sorted);
			fwrite(ord_lib[i].descrizione, sizeof(ord_lib[i].descrizione), 1,
					lib_sorted);
			fwrite(ord_lib[i].licenza, sizeof(ord_lib[i].licenza), 1,
					lib_sorted);
		}
		return lib_sorted;
	}
}

void cancellazione_librerie(FILE* lib)				/*funzione dedicata alla cancellazione di record dallo stream*/
{
	int c = 0;						/*contatori*/
	int i = 0;


	int ID_valido = 0;				/*variabili di caricamento ID*/
	int ID_appoggio = 0;


	int flag = 0;					/*flag*/
	int boole = 0;

	record_lib array[2];

	char ID_selezione[4] = { 0 };	/*variabili per la manipolazione di interi*/
	char ID_appoggio_c[4] = { 0 };
	char ID[4] = { 0 };

	FILE* counter = NULL;
	FILE* new_lib = NULL;

	new_lib = fopen("new_lib.dat", "wb+");
	counter = fopen("counter.dat", "rb+");

	if (counter == NULL || new_lib == NULL) /*controlli sull'apertura del file*/				/*controllo sull'apertura dei file*/
	{ /**/
		printf(
				"L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n"); /**/
		getchar();
	} /**/
	else {
		system("cls");

		while (c == 0) {
			do {
				i = 0;
				printf(
						"Inserire l'ID della librerie che si desidera eliminare o inserire x per uscire:\n\n"); /*scelta della funzione da cancellare*/
				fgets(ID_selezione, sizeof(int), stdin); /**/
				if (ID_selezione[0] != 'x' && ID_selezione[0] != 'X') {
					boole = 0;
					fflush(stdin);
					ID_valido = atoi(ID_selezione);

					if (ID_valido == 0) /*controlli sull'input*/
					{
						system("cls"); /**/
						printf("Il valore inserito non e' valido \n\n"); /**/
						getchar();
						system("cls"); /**/
						i = 1;
					}
					if (ID_valido <= NUM_LIB && i == 0) /*se la scelta è una funzione non cancellabile*/
					{
						system("cls"); /**/
						printf(
								"La libreria selezionata non e' eliminabile\n\n"); /**/
						getchar();
						system("cls");
						i = 1; /**/
					}
					if (ID_valido > NUM_LIB && i == 0) /*la funzione è cancellabile*/
					{
						fseek(counter, sizeof(int), SEEK_SET);
						fgets(ID_selezione, sizeof(int), counter);
						ID_appoggio = atoi(ID_selezione);

						if (ID_valido > ID_appoggio && i == 0) /*se la funzione selezionata ancora non esiste*/
						{
							system("cls"); /**/
							printf("La libreria selezionata non esiste \n\n"); /**/
							getchar();
							system("cls");
							i = 1; /**/
						} else {
							i = 0;
						}
					}
				} else {
					boole = 1;
					system("cls");
				}

			} while (i > 0);

			if (boole == 0) {													/*trascizione dei record su un nuovo file*/
				for (i = 0; i < ID_appoggio; i++) {
					if (i == (ID_valido - 1)) {
						flag = 1;
					}

					if (flag == 0) {
						fseek(lib, ((sizeof(array[0])) * (i)), SEEK_SET); /*posizionamento del puntatore al record da array[0]re*/
						fgets(ID, sizeof(array[0].ID), lib); /*lettura valori lib*/
						array[0].ID = atoi(ID);
						fseek(lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)),
								SEEK_SET); /*posizionamento del puntatore*/
						fgets(array[0].nome, sizeof(array[0].nome), lib);
						fseek(lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)
										+ sizeof(array[0].nome)), SEEK_SET);
						fgets(array[0].descrizione,
								sizeof(array[0].descrizione), lib);
						fseek(lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)
										+ sizeof(array[0].nome)
										+ sizeof(array[0].descrizione)),
										SEEK_SET);
						fgets(array[0].licenza, sizeof(array[0].licenza), lib);

						tostring(ID_appoggio_c, array[0].ID);

						fseek(new_lib, (sizeof(array[0]) * (i)), SEEK_SET);
						fwrite(ID_appoggio_c, sizeof(ID_selezione), 1, new_lib);
						fseek(new_lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)),
								SEEK_SET);
						fwrite(array[0].nome, sizeof(array[0].nome), 1,
								new_lib);
						fseek(new_lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)
										+ sizeof(array[0].nome)), SEEK_SET);
						fwrite(array[0].descrizione,
								sizeof(array[0].descrizione), 1, new_lib);
						fseek(new_lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)
										+ sizeof(array[0].nome)
										+ sizeof(array[0].descrizione)),
										SEEK_SET);
						fwrite(array[0].licenza, sizeof(array[0].licenza), 1,
								new_lib);
					}

					if (flag == 1 && i != (ID_valido - 1)) {						/*trascrizione record sul file saltando il record da cancellare*/
						fseek(lib, ((sizeof(array[0])) * (i)), SEEK_SET); /*posizionamento del puntatore al record da array[0]re*/
						fgets(ID, sizeof(array[0].ID), lib); /*lettura valori lib*/
						array[0].ID = atoi(ID);
						fseek(lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)),
								SEEK_SET); /*posizionamento del puntatore*/
						fgets(array[0].nome, sizeof(array[0].nome), lib);
						fseek(lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)
										+ sizeof(array[0].nome)), SEEK_SET);
						fgets(array[0].descrizione,
								sizeof(array[0].descrizione), lib);
						fseek(lib,
								((sizeof(array[0]) * (i)) + sizeof(array[0].ID)
										+ sizeof(array[0].nome)
										+ sizeof(array[0].descrizione)),
										SEEK_SET);
						fgets(array[0].licenza, sizeof(array[0].licenza), lib);

						array[0].ID = array[0].ID - 1;
						tostring(ID_appoggio_c, array[0].ID);

						fseek(new_lib, (sizeof(array[0]) * (i - 1)), SEEK_SET);
						fwrite(ID_appoggio_c, sizeof(ID_selezione), 1, new_lib);
						fseek(new_lib,
								((sizeof(array[0]) * (i - 1))
										+ sizeof(array[0].ID)), SEEK_SET);
						fwrite(array[0].nome, sizeof(array[0].nome), 1,
								new_lib);
						fseek(new_lib,
								((sizeof(array[0]) * (i - 1))
										+ sizeof(array[0].ID)
										+ sizeof(array[0].nome)), SEEK_SET);
						fwrite(array[0].descrizione,
								sizeof(array[0].descrizione), 1, new_lib);
						fseek(new_lib,
								((sizeof(array[0]) * (i - 1))
										+ sizeof(array[0].ID)
										+ sizeof(array[0].nome)
										+ sizeof(array[0].descrizione)),
										SEEK_SET);
						fwrite(array[0].licenza, sizeof(array[0].licenza), 1,
								new_lib);
					}
				}

				ID_valido = ID_valido - 1;

				ID_appoggio = ID_appoggio - 1;

				tostring(ID_selezione, ID_appoggio);

				fseek(counter, sizeof(int), SEEK_SET);
				fwrite(ID_selezione, sizeof(ID_selezione), 1, counter); /*scrittura counter aggiornato*/
				fclose(counter);								/*chiusura file*/
				fclose(lib);
				fclose(new_lib);
				remove("lib.dat");
				rename("new_lib.dat", "lib.dat");
				printf("Eliminazione avvennuta con successo\n\n");
				getchar();
				fflush(stdin);
				system("cls");
				c = 1;
			} else {
				c = 1;
			}
		} //chiusura while c==0
	}
}
