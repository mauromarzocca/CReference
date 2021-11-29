#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/*librerie personali necessarie*/
#include "utility.h"
#include "library.h"
#include "function.h"

int main()
{
	FILE *lib=NULL;				/*variabili dedicate ai file di stream*/
	FILE *funzioni=NULL;					/* ""  */
	FILE *lib_sorted=NULL;					/* ""  */
	FILE *fun_sorted=NULL;					/* ""  */
	int selezione=0;
	int b=0;
	int j=0;


	int selezione_interna=0;
	char scelta[4];
	int selezione_visualizza=0;
	int n=0;
	int m=0;

	FILE *changelog;
	changelog = fopen("changelog.txt", "r");
	int size = 0;
	fseek(changelog, 0, SEEK_END);
	size = ftell(changelog);
	char cf[size];

	do
	{
		printf("..d8888b.       8888888b.           .d888                                                   \n");		/*Titolo progetto*/
		printf("d88P  Y88b      888   Y88b         d88P.                                                    \n");		/**/
		printf("888    888      888    888         888                                                      \n");		/**/
		printf("888             888   d88P .d88b.  888888 .d88b.  888d888 .d88b.  88888b.   .d8888b .d88b.  \n");		/**/
		printf("888             8888888P. d8P  Y8b 888   d8P  Y8b 888P.  d8P  Y8b 888 .88b d88P.   d8P  Y8b \n");		/**/
		printf("888    888      888 T88b  88888888 888   88888888 888    88888888 888  888 888     88888888 \n");		/**/
		printf("Y88b  d88P      888  T88b Y8b.     888   Y8b.     888    Y8b.     888  888 Y88b.   Y8b.     \n");		/**/
		printf("  Y8888P..      888   T88b  Y8888  888     Y8888  888      Y8888  888  888   Y8888P  Y8888  \n\n\n");	/**/

		printf("C Reference\n\nVersione 2.2\n\n");
		printf("Programma di Marzocca Mauro\n\nInserire il numero per selezionare una voce del menu' e premere invio\n\n");
		printf("1) Librerie\n2) Funzioni\n");							/*Menu principale di selezione*/
		printf("3) Changelog e Feature\n4) Ricerca\n5) Uscita\n\n");
		printf("Inserire Scelta: ");
		fflush(stdin);
		fgets(scelta, 3, stdin);					/*presa in input della selezione*/

		selezione=atoi(scelta);

		system("cls");
		switch(selezione)				/*accesso ai sottomenu*/
		{
		case 1:
			do
			{
				printf("1) Visualizza librerie\n2) Aggiungi librerie\n");		/*sottomenu librerie*/
				printf("3) Modifica librerie\n4) Cancella Librerie\n5) Uscita\n\n");
				printf("Inserire Scelta: ");
				fflush(stdin);
				fgets(scelta, 3, stdin);			/*presa in input della selezione*/

				selezione=atoi(scelta);
				fflush(stdin);

				switch(selezione) {
				case 1:
					system("cls");
					lib=fopen("lib.dat", "rb");
					if(lib==NULL)			/*controllo sull'apertura del file */
					{
						printf("file non aperto correttamente\n\nRiavviare il programma e riprovare\n\n");		/*Apertura del file non effettuata*/
					}
					else
					{
						//printf("file ''lib.dat'' aperto correttamente\n\n");				/*comunicazione dell'apertura corretta del file*/
						do
						{
							printf("Vuoi visualizzare i file secondo il loro ordine originale o ordinati? \n\n1) Ordina per nome\n2) Ordina per licenza\n3) Ordina per ID\n\n");	/*viene chiesto se ordinare il file o meno*/
							fgets(scelta, 3, stdin);		/*presa in input della selezione*/
							selezione_visualizza=atoi(scelta);
							fflush(stdin);
							if(selezione_visualizza > 0 && selezione_visualizza < 4)				/*controlli sulla selezione effettuata*/
							{
								if(selezione_visualizza > 0 && selezione_visualizza < 3)			/*   ""   */
								{
									lib_sorted=ordinamento_librerie(lib, selezione_visualizza);		/*funzione esterna per l'ordinamento dei file*/
									if(lib_sorted != NULL)
									{
										b=1;
										visualizza_lib_sorted(lib_sorted);				/*visualizzazione del file ordinato*/
										fclose(lib_sorted);
									}
									else
									{
										printf("file non aperto correttamente\n\nRiavviare il programma e riprovare\n\n");			/* messaggio di errore in caso di apertura errata */
										getchar();
										b=1;
									}
								}
								else
								{
									visualizza_librerie(lib);
									fclose(lib);				/* visualizzazione del file ordinato per ID */
									b=1;
								}
							}
							else
							{
								system("cls");
								printf("selezione non corretta \n\n");			/* Messaggio di errore in caso di selezione non valida*/
								b=0;
							}
						} while(b==0);

					}
					/* chiusura file lib*/
					break;

				case 2:
					system("cls");
					lib=fopen("lib.dat", "ab");			/* apertura stream da file*/
					if(lib==NULL)
					{
						printf("file non aperto correttamente\n\nRiavviare il programma e riprovare\n\n");				/*messaggio di errore per apertura file*/
						getchar();
					}
					else
					{
						aggiungi_librerie(lib);					/*funzione che permette l'aggiunta di nuove librerie*/
						fclose(lib);			/*chiusura stream da file*/
					}

					break;
				case 3:
					system("cls");
					lib=fopen("lib.dat", "rb+");					/*apertura file lib*/
					if(lib==NULL)
					{
						printf("file non aperto correttamente\n\n");			/* messaggio di errore apertura file*/
						getchar();
					}
					else
					{
						modifica_librerie(lib);		/* chiamata della funzione per modificare una libreria con parametri il file contenente le librerie*/
						fclose(lib);
					}

					break;
				case 4:
					system("cls");
					lib=fopen("lib.dat", "rb+");					/*apertura file lib*/
					if(lib==NULL)
					{
						printf("file non aperto correttamente\n\n");			/* messaggio di errore apertura file*/
						getchar();
					}
					else
					{
						cancellazione_librerie(lib);		/* chiamata della funzione per modificare una libreria con parametri il file contenente le librerie*/
					}
					break;
				case 5:
					j=1;
					system("cls");
					break;
				default:
					system("cls");
					printf("Selezione non corretta, inserire un nuovo valore\n\n");
					j=0;
					break;
				}
			} while (j==0);
			break;












		case 2: system("cls");			/* sottomenu dedicato alle funzioni*/
		do
		{
			printf("1) Visualizza Funzioni\n2) Aggiungi Funzioni\n");
			printf("3) Modifica Funzioni\n4) Cancella Funzioni\n5) Uscita\n\n");
			printf("Inserire Scelta: ");
			fflush(stdin);
			fgets(scelta, 3, stdin);

			selezione=atoi(scelta);
			fflush(stdin);

			switch(selezione){
			case 1:					/* Sezione dedicata alla visualizzazione delle funzioni*/
				system("cls");
				funzioni=fopen("function.dat", "rb");			/*apertura file funzioni*/
				if(funzioni==NULL)
				{
					printf("file non aperto correttamente\n\n");		/*messaggio da stampare in caso di errore*/
				}
				else
				{
					do
					{
						printf("Vuoi visualizzare i file secondo il loro ordine originale o ordinati? \n\n1) Ordina per nome\n2) Ordina per tipo\n3) Ordina per librerie\n4) Ordina per ID\n\n");		/*selezione dell'ordine da visualizzare*/
						fgets(scelta, 3, stdin);

						selezione_visualizza=atoi(scelta);

						fflush(stdin);
						if(selezione_visualizza > 0 && selezione_visualizza < 5)		/*controllo sulla selezione*/
						{
							if(selezione_visualizza > 0 && selezione_visualizza < 4)
							{
								fun_sorted=ordinamento_funzioni(funzioni, selezione_visualizza);
								if(fun_sorted != NULL)
								{
									b=1;
									visualizza_fun_sorted(fun_sorted);			/* visualizzazione funzioni ordinate*/
									fclose(fun_sorted);
								}
								else
								{
									printf("Ordinamento non riuscito, controllare i file nella directory dell'eseguibile e riprovare\n\n");		/* messaggio da visualizzare in caso di problemi nell'ordinamento*/
									b=0;
								}
							}
							else
							{
								visualizza_funzioni(funzioni);		/* visualizzazione delle funzioni*/
								b=1;
							}
						}
						else
						{
							system("cls");
							printf("selezione non corretta \n\n");
							b=0;
						}
					} while(b==0);
				}
				fclose(funzioni);
				break;

			case 2:
				system("cls");
				funzioni=fopen("function.dat", "ab");
				if(funzioni==NULL)
				{
					printf("file non aperto correttamente\n\n");
				}
				else
				{

					aggiungi_funzioni(funzioni);		/* aggiunge una funzione al file*/
					fclose(funzioni);
				}
				break;

			case 3:

				system("cls");
				funzioni=fopen("function.dat", "rb+");
				if(funzioni==NULL)
				{
					printf("file non aperto correttamente\n\n");
				}
				else
				{
					modifica_funzioni(funzioni);		/*modifica una funzione esistente nel file*/
				}
				fclose(funzioni);
				break;
			case 4:
				system("cls");
				funzioni=fopen("function.dat", "rb+");
				if(funzioni==NULL)
				{
					printf("file non aperto correttamente\n\n");
				}
				else
				{
					cancellazione_funzioni(funzioni);		/*modifica una funzione esistente nel file*/
				}
				break;

			case 5:
				j=1;
				system("cls");
				break;
			default:
				system("cls");
				printf("Selezione non corretta, inserire un nuovo valore\n\n");
				j=0;
			}
		} while (j==0);
		break;













		case 3:	/*sezione dedicata alla documentazione del progetto*/
			system("cls");
			fseek(changelog, 0, SEEK_SET);
			fgets(cf, sizeof(cf), changelog);
			printf("%s\n", cf);
			getchar();
			system("cls");
			break;


		case 4:
			funzioni=fopen("function.dat", "rb");
			lib=fopen("lib.dat", "rb");
			ricerca(funzioni, lib);		/*funzione di ricerca con parametri i due file in cui effettuare la ricerca*/
			fclose(funzioni);
			fclose(lib);
			system("cls");
			do
			{
				printf("si desidera visualizzare funzioni o librerie oppure tornare al menu' principale?\n\n1) Visualizzare Funzioni\n2) Visualizzare Librerie\n3) Menu' Principale \n\n");
				fflush(stdin);
				fgets(scelta, 3, stdin);

				selezione_interna=atoi(scelta);		/*sezione dedicata alla selezione post ricerca*/

				fflush(stdin);


				switch(selezione_interna)
				{
				case 1:
					funzioni=fopen("function.dat", "rb");
					visualizza_funzioni(funzioni);		/*viene richiama la visualizzazione delle funzioni*/
					fclose(funzioni);

					m=0;
					system("cls");
					break;
				case 2:
					lib=fopen("lib.dat", "rb");
					visualizza_librerie(lib);		/*viene richiamata la funzione di visualizzazione librerie*/
					fclose(lib);

					m=0;
					system("cls");
					break;
				case 3:
					m=1;
					n=0;
					system("cls");	/* *blocco* torna al menu principale*/
					break;
				default:
					printf("selezione non valida! \n\nRiprovare!\n\n");
					m=0;
					getchar();
				}
			} while(m==0);
			break;


		case 5:
			printf("Grazie di aver usato questo programma!\n		- Marzocca Mauro - \n\n"  );
			getchar();
			n=1;			/*chiusura programma*/
			break;

		default:
			printf("Selezione errata\n\nRiprovare\n\n");
			n=0;
			fflush(stdin);
			getchar();
			system("cls");
		}
	}while(n==0);
}
