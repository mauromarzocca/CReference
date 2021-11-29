/*Sorgente legato all'header function.h*/

/*librerie di sistema necessarie*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*librerie personali necessarie*/

#include "utility.h"
#include "function.h"

void visualizza_funzioni(FILE *funzioni)		
{
	int i=0;			/*contatore*/
	int j=0;

	int n_funzioni=0;		/*numero funzioni*/
	
	int ID=0;				/*ID funzione*/

	int selezione=0;		/* selezione in input da file*/

	

	char c[4]={0};
	FILE *counter=NULL;

	record_fun visualizza;						/*struct necessaria a caricare il record da visualizzare*/

	counter=fopen("counter.dat", "rb");
	/*nel file counter verrano salvati 1) cont.funzioni, 2)cont.librerie, 3), funzioni e librerie personalizzate*/
	if(counter==NULL)																							/*controllo sull'apertura del file*/
	{																											/**/
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");		/**/	
		getchar();
	}
	else
	{

		system("cls");								/*caricamento del numero delle funzioni da file*/
		fseek(counter, 0, SEEK_SET);				/**/
		fgets(c, sizeof(n_funzioni), counter);		/**/

		n_funzioni=atoi(c);							/**/

		do
		{
			do
			{
				printf("----------------------------------------------\n");												/**/
				for(i=0; i<n_funzioni; i++)															/**/
				{
					fseek(funzioni, (sizeof(visualizza)*i), SEEK_SET);								/**/		/*posizionamento del puntatore a file*/
					fgets(c, sizeof(visualizza.ID), funzioni);										/**/		/*lettura ID*/
					visualizza.ID=atoi(c);															/**/
					fseek(funzioni, ((sizeof(visualizza)*i)+sizeof(visualizza.ID)), SEEK_SET);		/**/		/*posizionamento del puntatore a file*/
					fgets(visualizza.nome, sizeof(visualizza.nome), funzioni);
					visualizza.nome[31] = ' ';
					fseek(funzioni, ((sizeof(visualizza)*i)+sizeof(visualizza.ID)+sizeof(visualizza.nome) + sizeof(visualizza.tipo)), SEEK_SET);
					fgets(visualizza.librerie, sizeof(visualizza.librerie), funzioni);/**/
					printf(" ID \t\t: \t%d\n Nome \t\t: \t%s Libreria \t: \t%s", visualizza.ID, visualizza.nome, visualizza.librerie);	/*lettura nome*/						/**/
					printf("----------------------------------------------\n");												/**/
				}
				printf("\n\nInserire l'ID della funzione che si vuole visualizzare\n\n");			/*lettura da tastieradell'ID da visualizzare*/
				fgets(c, sizeof(c), stdin); 													/**/	

				fflush(stdin);								
				ID=atoi(c);																		/**/

				if(ID==0)																		/*controlli sull'input*/
				{
					system("cls");
					printf("Il valore inserito non e' corretto\n\n");							/*valore errato*/
					i=0;
				}
				else							
				{
					if(ID>n_funzioni)															/*ID superiore al numero di funzioni*/
					{
						system("cls");
						printf("La funzione selezionata non esiste\n\n");
						i=0;
					}
					else																		/*ID corretto*/
					{
						i=1;
					}
				}

			}	while(i==0);

			visualizza=load_funzioni(funzioni, (ID-1));							/*caricamento delle funzioni da file dove il secondo parametro è il numero di record da saltare*/

			system("cls");
			printf("ID:\n%d\n\nNome:\n%s\n\nTipo:\n%s\n\nlibrerie:\n%s\n\nDescrizione:\n%s\n\nValori di ritorno:\n%s\n\nParametri d'ingresso\n%s\n\n", visualizza.ID, visualizza.nome, visualizza.tipo, visualizza.librerie, visualizza.descrizione, visualizza.ritorno, visualizza.parametri);		/*stampa la funzione scelta*/

			getchar();
			fflush(stdin);
			do 								/*sottomenu per scegliere se restare nel visualizza o meno*/
			{
				system("cls");
				printf("Si desidera visualizzare un altra funzione? \n\n1) Uscita\n2) Visualizzazione altra funzione\n\n");
				fgets(c, sizeof(c), stdin);


				fflush(stdin);
				selezione=atoi(c);

				switch(selezione)
				{
				case 1:
					j=1;
					i=1;
					system("cls");
					break;
				case 2:
					j=0;
					i=1;
					system("cls");
					break;
				default:
					printf("La selezione effettuata non e' valida \n");
					i=0;
					getchar();
					fflush(stdin);
					system("cls");
				}

			} while(i==0);
		} while (j==0);
		fclose(counter);
	}

}
















void modifica_funzioni(FILE* funzioni)
{
	char ID_selezione[4]={0};	/*variabili dedicate al caricamento di int da file*/
	char selezione[4]={0};

	int check=0;
	int selezione_int=0;
	
	int ID_valido=0;			/*variabili dedicate alla manipolazione degli ID*/
	int ID_appoggio=0;

	int i=0;					/*contatori*/
	int c=0;
	int j=0;
	int t=0;

	int boole=0;				/*flag*/

	record_fun modifica;
	record_fun appoggio;

	FILE* counter=NULL;

	counter=fopen("counter.dat", "rb");

	if(counter==NULL)																							/*controlli sull'apertura del file*/
	{																											/**/
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");		/**/
		getchar();	
	}																											/**/
	else
	{
		system("cls");
		while(c==0)
		{
			do
			{
				i=0;
				printf("Inserire l'ID della funzione che si desidera modificare o x per uscire:\n\n");			/*scelta della funzione da modificare*/
				fgets(ID_selezione, MAX_INT , stdin);															/**/
				if(ID_selezione[0]=='x' || ID_selezione[0]=='X')
				{
					i=0;
					c=1;
					boole=1;
				}
				else
				{
					boole=0;
					fflush(stdin);
					ID_valido=atoi(ID_selezione);

					if(ID_valido==0)																				/*controlli sull'input*/
					{
						system("cls");																				/**/
						printf("Il valore inserito non e' valido \n\n");											/**/
						getchar();
						system("cls");																				/**/
						i=1;
					}
					if(ID_valido<=NUM_FUNZIONI && i==0)																/*se la scelta è una funzione non modificabile*/
					{
						system("cls");																				/**/
						printf("La funzione selezionata non e' modificabile\n\n");									/**/
						getchar();
						system("cls");
						i=1;																						/**/
					}
					if(ID_valido>NUM_FUNZIONI && i==0)																/*la funzione è modificabile*/
					{
						fseek(counter, 0, SEEK_SET);
						fgets(ID_selezione, sizeof(int), counter);
						ID_appoggio=atoi(ID_selezione);

						if(ID_valido>ID_appoggio && i==0)															/*se la funzione selezionata ancora non esiste*/
						{
							system("cls");																			/**/
							printf("La funzione selezionata non esiste \n\n");										/**/
							getchar();
							system("cls");
							i=1;																					/**/
						}
						else
						{
							i=0;
						}
					}
				}
			} while (i>0);

			if(boole==0)
			{
				modifica=load_funzioni(funzioni, (ID_valido-1));			/*caricamento funzioni da file*/

				boole=0;
				while(boole==0)
				{
					system("cls");
					printf("Quale campo si desidera modificare? \n\nID=%d \n\n1) Nome\t%s\n2) Tipo\t%s\n3) librerie\t%s\n4) Descrizione\t%s\n5) Valori di ritorno \t%s\n6) Paramentri della funzione\t%s\n\n7) Uscita\n\n", modifica.ID, modifica.nome, modifica.tipo, modifica.librerie, modifica.descrizione, modifica.ritorno, modifica.parametri);
					fgets(selezione, sizeof(selezione), stdin);
					fflush(stdin);

					selezione_int=atoi(selezione);

					if(selezione_int==0 || selezione_int < 1)
					{
						printf("Il valore inserito non e' valido, riprovare\n\n");
						boole=0;
						j=1;
						system("cls");
					}
					else
					{
						j=0;
						system("cls");
					}
					if(j==0)
					{
						switch(selezione_int)
						{
						case 1: /*modifica nome*/
							system("cls");
							fseek(funzioni, ((sizeof(modifica)*(ID_valido-1))+sizeof(modifica.ID)), SEEK_SET);
							printf("Inserire il nuovo nome da assegnare alla funzione:\n\n");
							fgets(appoggio.nome, sizeof(appoggio.nome), stdin);
							check=strlen(appoggio.nome);
							fflush(stdin);

							if(check<=1)
							{
								system("cls");
								printf("\n\n\nNon e' stata inserita nessun nuovo nome, verrà mantenuto il vecchio nome\n\n");
								getchar();
								system("cls");
							}
							else
							{
								strcpy(modifica.nome, appoggio.nome);
								fwrite(modifica.nome, sizeof(modifica.nome),1,  funzioni);
								system("cls");
							}
							break;
						case 2:	/*modifica tipo*/
							system("cls");
							fseek(funzioni, ((sizeof(modifica)*(ID_valido-1))+sizeof(modifica.ID)+sizeof(modifica.nome)), SEEK_SET);
							printf("Inserire il nuovo tipo da assegnare alla funzione:\n\n");
							fgets(appoggio.tipo, sizeof(appoggio.tipo), stdin);
							check=strlen(appoggio.tipo);
							fflush(stdin);

							if(check<=1)
							{
								system("cls");
								printf("\n\n\nNon e' stata inserita nessun nuovo tipo, verrà mantenuto il vecchio tipo\n\n");
								getchar();
								system("cls");
							}
							else
							{
								strcpy(modifica.tipo, appoggio.tipo);
								fwrite(modifica.tipo, sizeof(modifica.tipo),1,  funzioni);
								system("cls");
							}
							break;
						case 3: /*modifica librerie*/
							system("cls");
							fseek(funzioni, ((sizeof(modifica)*(ID_valido-1))+sizeof(modifica.ID)+sizeof(modifica.nome) + sizeof(modifica.tipo)), SEEK_SET);
							printf("Inserire la nuova libreria da assegnare alla funzione:\n\n");
							fgets(appoggio.librerie, sizeof(appoggio.librerie), stdin);
							check=strlen(appoggio.librerie);
							fflush(stdin);

							if(check<=1)
							{
								system("cls");
								printf("\n\n\nNon e' stato inserito nessuna librerie, verranno mantenute le vecchie librerie\n\n");
								getchar();
								system("cls");
							}
							else
							{
								strcpy(modifica.librerie, appoggio.librerie);
								fwrite(modifica.librerie, sizeof(modifica.librerie),1,  funzioni);
								system("cls");
							}
							break;

						case 4:	/*modifica descrizione*/
							system("cls");
							fseek(funzioni, ((sizeof(modifica)*(ID_valido-1))+sizeof(modifica.ID)+sizeof(modifica.nome) + sizeof(modifica.tipo)+sizeof(modifica.librerie)), SEEK_SET);
							printf("Inserire una nuova descrizione da assegnare alla funzione:\n\n");
							fgets(appoggio.descrizione, sizeof(appoggio.descrizione), stdin);
							check=strlen(appoggio.descrizione);
							fflush(stdin);

							if(check<=1)
							{
								system("cls");
								printf("\n\n\nNon e' stata inserita nessuna descrizione, verrà mantenuto la vecchia descrizione\n\n");
								getchar();
								system("cls");
							}
							else
							{
								strcpy(modifica.descrizione, appoggio.descrizione);
								fwrite(modifica.descrizione, sizeof(modifica.descrizione),1,  funzioni);
								system("cls");
							}
							break;
						case 5:		/*modifica il valore di ritorno*/
							system("cls");
							fseek(funzioni, ((sizeof(modifica)*(ID_valido-1))+sizeof(modifica.ID)+sizeof(modifica.nome) + sizeof(modifica.tipo)+sizeof(modifica.librerie)+sizeof(modifica.descrizione)), SEEK_SET);
							printf("Inserire i nuovi valori di ritorno da assegnare alla funzione:\n\n");
							fgets(appoggio.ritorno, sizeof(appoggio.ritorno), stdin);
							check=strlen(appoggio.ritorno);
							fflush(stdin);

							if(check<=1)
							{
								system("cls");
								printf("\n\n\nNon e' stato inserito nessun valore, verrà mantenuto il vecchio valore\n\n");
								getchar();
								system("cls");
							}
							else
							{
								strcpy(modifica.ritorno, appoggio.ritorno);
								fwrite(modifica.ritorno, sizeof(modifica.ritorno),1,  funzioni);
								system("cls");
							}
							break;
						case 6:		/*modifica i parametri*/
							system("cls");
							fseek(funzioni, (sizeof(modifica)*(ID_valido-1)+sizeof(modifica.ID)+sizeof(modifica.nome) + sizeof(modifica.tipo)+sizeof(modifica.librerie)+sizeof(modifica.descrizione)+sizeof(modifica.ritorno)), SEEK_SET);
							printf("Inserire i nuovi parametri da assegnare alla funzione:\n\n");
							fgets(appoggio.parametri, sizeof(appoggio.parametri), stdin);
							check=strlen(appoggio.parametri);
							fflush(stdin);

							if(check<=1)
							{
								system("cls");
								printf("\n\n\nNon e' stato inserita nessun parametro, verranno mantenuti i vecchi parametri\n\n");
								getchar();
								system("cls");
							}
							else
							{
								strcpy(modifica.parametri, appoggio.parametri);
								fwrite(modifica.parametri, sizeof(modifica.parametri),1,  funzioni);
								system("cls");
							}
							break;

						case 7:	/*uscita*/
							boole=1;
							break;
						default:
							printf("Il Valore inserito non corrisponde a nessuna selezione, riprovare \n\n");
							boole=0;
							system("cls");
						}
					}
				}

				t=0;
				while(t==0)
				{
					system("cls");
					printf("Si desidera selezionare una nuova funzione o uscire? \n\n1) Uscire\n2)Selezionare altra funzione\n\n");		/*blocco che permette di modificare un altra funzione o uscire*/
					fgets(selezione, sizeof(selezione), stdin);


					fflush(stdin);
					selezione_int=atoi(selezione);



					switch(selezione_int)
					{
					case 1:
						t=1;
						c=1;
						system("cls");
						fclose(counter);
						break;
					case 2:
						t=1;
						c=0;
						system("cls");
						break;
					default:
						printf("la selezione effettuata non e' valida\n\n");
						t=0;
						c=0;
						system("cls");
					}

				}
			}
			system("cls");
		}
	}
}




















void aggiungi_funzioni(FILE *funzioni)
{
	int i=0;
	FILE* counter=NULL;
	int n_funzioni=0;
	record_fun nuovo;
	int check=0;
	char n_funzioni_c[4]={0};

	counter=fopen("counter.dat", "rb+");			/*apertura file counter*/
	if(counter==NULL)								/*controllo sull'apertura*/
	{
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");			/*errore nell'apertura*/
		getchar();
	}
	else
	{
		system("cls");
		fseek(counter, 0, SEEK_SET);						/*caricamento numero funzioni*/
		fgets(n_funzioni_c, sizeof(n_funzioni), counter);	/**/

		n_funzioni=atoi(n_funzioni_c);						/**/

		n_funzioni=n_funzioni+1;							/* creazione ID della nuova funzione*/

		tostring(n_funzioni_c, n_funzioni);					/**/

		printf("Inserire i dati della nuova funzione n.%d\n\n Premere invio per iniziare o inserire x per uscire", n_funzioni); 
		check=getchar();
		system("cls");
		fflush(stdin);
		if(check != 'x' && check != 'X')
		{
			do
			{
				fwrite(n_funzioni_c, sizeof(int), 1, funzioni);		/*scrittura sul file del nuovo ID*/
				fflush(stdin);
				printf("Nome : ");
				fgets(nuovo.nome, sizeof(nuovo.nome), stdin);			/*lettura da tastiera nuovo nome*/
				fflush(stdin);
				system("cls");
				check=strlen(nuovo.nome);
				if(check<=1)						/*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n");		/*lunghezza non corretta*/
					system("cls");
					i=0;
				}
				else
				{
					fwrite(nuovo.nome, sizeof(nuovo.nome),1,  funzioni);			/*scrittura su file*/
					system("cls");
					i=1;
				}
			} while(i==0);
			do
			{
				printf("Tipo : ");
				fgets(nuovo.tipo, sizeof(nuovo.tipo), stdin);			/*lettura da tastiera nuovo tipo*/
				fflush(stdin);
				system("cls");
				check=strlen(nuovo.tipo);
				if(check<=1)			/*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n");			/*lunghezza non corretta*/
					getchar();
					system("cls");
					i=0;
				}
				else
				{
					fwrite(nuovo.tipo, sizeof(nuovo.tipo),1,  funzioni);			/*scrittura su file*/
					system("cls");
					i=1;
				}
			} while(i==0);
			do
			{
				printf("librerie : ");
				fgets(nuovo.librerie, sizeof(nuovo.librerie), stdin);			/*lettura da tastiera nuova libreria*/
				fflush(stdin);
				system("cls");
				check=strlen(nuovo.librerie);
				if(check<=1)			/*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n");			/*lunghezza non corretta*/
					getchar();
					system("cls");
					i=0;
				}
				else
				{
					fwrite(nuovo.librerie, sizeof(nuovo.librerie),1,  funzioni);			/*scrittura su file*/
					system("cls");
					i=1;
				}
			} while(i==0);
			do
			{
				printf("Descrizione : ");
				fgets(nuovo.descrizione, sizeof(nuovo.descrizione), stdin);			/*lettura da tastiera nuova descrizione*/
				fflush(stdin);
				system("cls");
				check=strlen(nuovo.descrizione);
				if(check<=1)			/*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n");			/*lunghezza non corretta*/
					getchar();
					system("cls");
					i=0;
				}
				else
				{
					fwrite(nuovo.descrizione,  sizeof(nuovo.descrizione), 1,funzioni);			/*scrittura su file*/
					system("cls");
					i=1;
				}
			} while(i==0);
			do
			{
				printf("Ritorno : ");
				fgets(nuovo.ritorno, sizeof(nuovo.ritorno), stdin);		/*lettura da tastiera nuovo valore di ritorno*/
				fflush(stdin);
				system("cls");
				check=strlen(nuovo.ritorno);
				if(check<=1)		/*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n");		/*lunghezza non corretta*/
					getchar();
					system("cls");
					i=0;
				}
				else
				{
					fwrite(nuovo.ritorno,  sizeof(nuovo.ritorno), 1,funzioni);		/*scrittura su file*/
					system("cls");
					i=1;

				}
			} while(i==0);
			do
			{
				printf("Parametri : ");
				fgets(nuovo.parametri, sizeof(nuovo.parametri), stdin);			/*lettura da tastiera nuovo parametro*/
				fflush(stdin);
				system("cls");
				check=strlen(nuovo.parametri);
				if(check<=1)			/*controllo sulla lunghezza*/
				{
					printf("Nessun valore inserito, riprovare\n\n");			/*lunghezza non corretta*/
					getchar();
					system("cls");
					i=0;
				}
				else
				{
					fwrite(nuovo.parametri,  sizeof(nuovo.parametri), 1,funzioni);			/*scrittura su file*/
					system("cls");
					i=1;
				}
			} while(i==0);
			printf("Nuova Funzione Aggiunta\n\n");
			getchar();
			system("cls");
			fseek(counter, 0, SEEK_SET);
			fwrite(n_funzioni_c,  sizeof(n_funzioni), 1,counter);		/*scrittura counter aggiornato*/
			fclose(counter);
		}
	}
}








FILE* ordinamento_funzioni(FILE* funzioni, int ordine)
{

	FILE* counter=NULL;
	FILE* fun_sorted=NULL;

	char n_funzioni_c[4]={0};	/*carica ID da file*/

	int n_funzioni=0;		/*numero funzioni*/

	int i=0;			/*contatori*/
	int j=0;
	int l=0;

	int flag=0;

	counter=fopen("counter.dat", "rb");				/*apertura file counter e fun_sorted, necessari al corretto funzionamento dell'ordinamento*/
	fun_sorted=fopen("fun_sorted.dat", "rb+");		/**/
	if(counter==NULL || fun_sorted==NULL)			/*controlli sull'apertura*/
	{
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");		/*apertura non riuscita*/
		getchar();
		return NULL;
	}
	else
	{
		system("cls");
		fseek(counter, 0, SEEK_SET);
		fgets(n_funzioni_c, sizeof(n_funzioni), counter);				/*caricamento numero funzioni*/
		n_funzioni=atoi(n_funzioni_c);

		record_fun ord_funzioni[n_funzioni];

		for(i=0; i<n_funzioni; i++)
		{
			ord_funzioni[i]=load_funzioni(funzioni, i);			/*caricamento array con funzioni contenute in function.dat*/
		}
		switch(ordine)
		{
		case 1:
			//ordine nome
			for(l=0; l<n_funzioni; l++)
			{
				flag=0;
				for(i=0; i<(n_funzioni-1); i++)
				{
					j=strcmp(ord_funzioni[i+1].nome, ord_funzioni[i].nome);
					if(j<0)
					{
						scambio_funzioni(ord_funzioni, i);						/*swap delle funzioni nell'array*/
						flag=1;
					}
				}
				if(flag==0)
				{
					l=n_funzioni+1;
				}
			}
			break;

		case 2:
			//ordine tipo
			for(l=0; l<n_funzioni; l++)
			{
				flag=0;
				for(i=0; i<(n_funzioni-1); i++)
				{
					j=strcmp(ord_funzioni[i+1].tipo, ord_funzioni[i].tipo);
					if(j<0)
					{
						scambio_funzioni(ord_funzioni, i);				/*swap delle funzioni nell'array*/
						flag=1;
					}
				}
				if(flag==0)
				{
					l=n_funzioni+1;
				}
			}
			break;
		case 3:
			//ordine librerie
			for(l=0; l<n_funzioni; l++)
			{
				flag=0;
				for(i=0; i<(n_funzioni-1); i++)
				{
					j=strcmp(ord_funzioni[i+1].librerie, ord_funzioni[i].librerie);
					if(j<0)
					{
						scambio_funzioni(ord_funzioni, i);					/*swap delle funzioni nell'array*/
						flag=1;
					}
				}
				if(flag==0)
				{
					l=n_funzioni+1;
				}
			}
			break;

		default:
			system("cls");
			printf("selezione non valida! \n\n");

		}
		fseek(fun_sorted, 0, SEEK_SET);
		for(i=0; i<n_funzioni; i++)
		{
			tostring(n_funzioni_c, ord_funzioni[i].ID);													/*scrittura sul file fun_sorted*/

			fwrite(n_funzioni_c, sizeof(int), 1, fun_sorted);											/**/
			fwrite(ord_funzioni[i].nome, sizeof(ord_funzioni[i].nome), 1, fun_sorted);					/**/
			fwrite(ord_funzioni[i].tipo, sizeof(ord_funzioni[i].tipo), 1, fun_sorted);					/**/
			fwrite(ord_funzioni[i].librerie, sizeof(ord_funzioni[i].librerie), 1, fun_sorted);			/**/
			fwrite(ord_funzioni[i].descrizione, sizeof(ord_funzioni[i].descrizione), 1, fun_sorted);	/**/
			fwrite(ord_funzioni[i].ritorno, sizeof(ord_funzioni[i].ritorno), 1, fun_sorted);			/**/
			fwrite(ord_funzioni[i].parametri, sizeof(ord_funzioni[i].parametri), 1, fun_sorted);		/**/
		}
		return fun_sorted;
	}
}












void visualizza_fun_sorted(FILE *funzioni)		
{
	int i=0;		/*contatori*/
	int j=0;
	int l=0;

	int n_funzioni=0;		/*numero funzioni*/
	int ID=0;
	int selezione=0;
	
	int indice_fun=0;

	char c[4]={0};
	FILE *counter=NULL;

	record_fun visualizza;			/*struct che carica il record dal file*/

	counter=fopen("counter.dat", "rb");		/*apertura counter*/

	if(counter==NULL)			/*controllo sulla corretta apertura*/
	{
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n"); /*errore nell'apertura*/
		getchar();
	}
	else
	{
		system("cls");
		fseek(counter, 0, SEEK_SET);			/*caricamento numero funzioni da file counter*/
		fgets(c, sizeof(n_funzioni), counter);	/**/

		n_funzioni=atoi(c);						/**/

		do
		{
			do
			{										/*stampa lista di funzioni presenti all'interno del file*/
				printf("----------------------------------------------\n");												/**/
				for(i=0; i<n_funzioni; i++)															/**/
				{
					fseek(funzioni, (sizeof(visualizza)*i), SEEK_SET);								/**/		/*posizionamento del puntatore a file*/
					fgets(c, sizeof(visualizza.ID), funzioni);										/**/		/*lettura ID*/
					visualizza.ID=atoi(c);															/**/
					fseek(funzioni, ((sizeof(visualizza)*i)+sizeof(visualizza.ID)), SEEK_SET);		/**/		/*posizionamento del puntatore a file*/
					fgets(visualizza.nome, sizeof(visualizza.nome), funzioni);
					fseek(funzioni, ((sizeof(visualizza)*i)+sizeof(visualizza.ID)+sizeof(visualizza.nome) + sizeof(visualizza.tipo)), SEEK_SET);
					fgets(visualizza.librerie, sizeof(visualizza.librerie), funzioni);/**/		/*lettura nome*/
					printf(" ID \t\t: \t%d\n Nome \t\t: \t%s Libreria \t: \t%s", visualizza.ID, visualizza.nome, visualizza.librerie);	/*lettura nome*/						/**/
					printf("----------------------------------------------\n");											/**/
				}
				printf("Inserire l'ID della funzione che si vuole visualizzare\n\n");				/*lettura ID funzione da visualizzare*/
				fgets(c, sizeof(c), stdin);	

				/**/
				fflush(stdin);																		/**/
				ID=atoi(c);	

				if(ID==0)																			/*controlli sull'ID*/
				{
					system("cls");
					printf("Il valore inserito non e' corretto\n\n");								/*ID non numerico*/
					i=0;
				}

				else
				{
					if(ID>n_funzioni)											
					{
						system("cls");
						printf("La funzione selezionata non esiste\n\n");							/*se ID è maggiore del numero delle funzioni*/
						i=0;
					}
					else
					{
						i=1;
					}
				}

			}	while(i==0);

			for(l=0; l < n_funzioni; l++)
			{
				fseek(funzioni, ((sizeof(visualizza))*(l)), SEEK_SET); /*posizionamento del puntatore al record da search_lre*/
				fgets(c, sizeof(c), funzioni);						/*lettura valornlib*/
				visualizza.ID=atoi(c);

				if(visualizza.ID == ID)
				{
					indice_fun=l;
					l=n_funzioni+1;
				}
			}
			visualizza=load_funzioni(funzioni, indice_fun);

			system("cls");
			printf("ID:\n%d\n\nNome:\n%s\n\nTipo:\n%s\n\nlibrerie:\n%s\n\nDescrizione:\n%s\n\nValori di ritorno:\n%s\n\nParametri d'ingresso\n%s\n\n", visualizza.ID, visualizza.nome, visualizza.tipo, visualizza.librerie, visualizza.descrizione, visualizza.ritorno, visualizza.parametri);

			getchar();
			fflush(stdin);
			do
			{
				system("cls");
				printf("Si desidera visualizzare un altra funzione? \n\n1) Uscita\n2) Visualizzazione altra funzione\n\n");		/*menu che permette all'utente di scegliere se continuare a visualizzare o tornare al menu*/
				fgets(c, sizeof(c), stdin);

				fflush(stdin);
				selezione=atoi(c);

				switch(selezione)
				{
				case 1:
					j=1;
					i=1;
					fflush(stdin);
					system("cls");
					break;
				case 2:
					j=0;
					i=1;
					fflush(stdin);
					system("cls");
					break;
				default:
					printf("La selezione effettuata non e' valida \n");
					i=0;
					getchar();
					fflush(stdin);
					system("cls");
				}
			} while(i==0);
		} while (j==0);
		fclose(counter);
	}
}

void cancellazione_funzioni(FILE* funzioni)		/*funzione dedicata alla cancellazione delle funzioni dal file*/
{
	int c=0;				/*contatori*/
	int i=0;


	int ID_valido=0;		/*variabili di caricamento*/
	int ID_appoggio=0;


	int flag=0;				/*variabili flag*/
	int boole=0;

	record_fun array[2];

	char ID_selezione[4]={0};				/*variabili di caricamento da file*/
	char ID_appoggio_c[4]={0};


	FILE* counter=NULL;					/*puntatori a FILE*/
	FILE* new_fun=NULL;

	new_fun=fopen("new_fun.dat", "wb+");
	counter=fopen("counter.dat", "rb+");

	if(counter==NULL || new_fun==NULL)																							/*controlli sull'apertura del file*/
	{																											/**/
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");		/**/
		getchar();
	}																											/**/
	else
	{
		system("cls");

		while(c==0)
		{
			do
			{
				i=0;
				printf("Inserire l'ID della funzione che si desidera cancellare o inserire x per uscire:\n\n");							/*scelta della funzione da cancellare*/
				fgets(ID_selezione, MAX_INT , stdin);															/**/
				if (ID_selezione[0] != 'x' && ID_selezione[0] != 'X')
				{
					boole=0;
					fflush(stdin);
					ID_valido=atoi(ID_selezione);																	/**/

					if(ID_valido==0)																				/*controlli sull'input*/
					{
						system("cls");																				/**/
						printf("Il valore inserito non e' valido \n\n");											/**/
						getchar();
						system("cls");																				/**/
						i=1;
					}
					if(ID_valido<=NUM_FUNZIONI && i==0)																/*se la scelta è una funzione non cancellabile*/
					{
						system("cls");																				/**/
						printf("La funzione selezionata non e' eliminabile\n\n");									/**/
						getchar();
						system("cls");
						i=1;																						/**/
					}
					if(ID_valido>NUM_FUNZIONI && i==0)																/*la funzione è cancellabile*/
					{
						fseek(counter, 0, SEEK_SET);
						fgets(ID_selezione, sizeof(int), counter);
						ID_appoggio=atoi(ID_selezione);

						if(ID_valido>ID_appoggio && i==0)															/*se la funzione selezionata ancora non esiste*/
						{
							system("cls");																			/**/
							printf("La funzione selezionata non esiste \n\n");										/**/
							getchar();
							system("cls");
							i=1;																					/**/
						}
						else
						{
							i=0;
						}
					}
				}
				else
				{
					boole=1;
					system("cls");
				}


			} while (i>0);

			if(boole==0)
			{
				for(i=0; i < ID_appoggio; i++)
				{
					if(i==(ID_valido-1))
					{
						flag=1;
					}

					if(flag==0)																																																			/*trascrizione dei record sui nuovi file*/
					{
						fseek(funzioni, ((sizeof(array[0]))*(i)), SEEK_SET); /*posizionamento del puntatore al record da array[0]re*/
						fgets(ID_appoggio_c, sizeof(array[0].ID), funzioni);						/*lettura valori funzioni*/
						array[0].ID=atoi(ID_appoggio_c);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)), SEEK_SET); /*posizionamento del puntatore*/
						fgets(array[0].nome, sizeof(array[0].nome), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome)), SEEK_SET);
						fgets(array[0].tipo, sizeof(array[0].tipo), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)), SEEK_SET);
						fgets(array[0].librerie, sizeof(array[0].librerie), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)), SEEK_SET);
						fgets(array[0].descrizione, sizeof(array[0].descrizione), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)), SEEK_SET);
						fgets(array[0].ritorno, sizeof(array[0].ritorno), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)+sizeof(array[0].ritorno)), SEEK_SET);
						fgets(array[0].parametri, sizeof(array[0].parametri), funzioni);

						tostring(ID_appoggio_c, array[0].ID);

						fseek(new_fun, (sizeof(array[0])*(i)), SEEK_SET);
						fwrite(ID_appoggio_c,  sizeof(ID_selezione), 1,new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i))+sizeof(array[0].ID)), SEEK_SET);
						fwrite(array[0].nome, sizeof(array[0].nome),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome)), SEEK_SET);
						fwrite(array[0].tipo, sizeof(array[0].tipo),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)), SEEK_SET);
						fwrite(array[0].librerie, sizeof(array[0].librerie),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)), SEEK_SET);
						fwrite(array[0].descrizione, sizeof(array[0].descrizione),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)), SEEK_SET);
						fwrite(array[0].ritorno, sizeof(array[0].ritorno),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)+sizeof(array[0].ritorno)), SEEK_SET);
						fwrite(array[0].parametri, sizeof(array[0].parametri),1,  new_fun);
					}

					if(flag==1 && i != (ID_valido-1))																																/*trascrizione record su nuovi file ma senza quello cancellato*/
					{
						fseek(funzioni, ((sizeof(array[0]))*(i)), SEEK_SET); /*posizionamento del puntatore al record da array[0]re*/
						fgets(ID_appoggio_c, sizeof(array[0].ID), funzioni);						/*lettura valori funzioni*/
						array[0].ID=atoi(ID_appoggio_c);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)), SEEK_SET); /*posizionamento del puntatore*/
						fgets(array[0].nome, sizeof(array[0].nome), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome)), SEEK_SET);
						fgets(array[0].tipo, sizeof(array[0].tipo), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)), SEEK_SET);
						fgets(array[0].librerie, sizeof(array[0].librerie), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)), SEEK_SET);
						fgets(array[0].descrizione, sizeof(array[0].descrizione), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)), SEEK_SET);
						fgets(array[0].ritorno, sizeof(array[0].ritorno), funzioni);
						fseek(funzioni, ((sizeof(array[0])*(i))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)+sizeof(array[0].ritorno)), SEEK_SET);
						fgets(array[0].parametri, sizeof(array[0].parametri), funzioni);

						array[0].ID=array[0].ID-1;
						tostring(ID_appoggio_c, array[0].ID);

						fseek(new_fun, (sizeof(array[0])*(i-1)), SEEK_SET);
						fwrite(ID_appoggio_c,  sizeof(ID_selezione), 1,new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i-1))+sizeof(array[0].ID)), SEEK_SET);
						fwrite(array[0].nome, sizeof(array[0].nome),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i-1))+sizeof(array[0].ID)+sizeof(array[0].nome)), SEEK_SET);
						fwrite(array[0].tipo, sizeof(array[0].tipo),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i-1))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)), SEEK_SET);
						fwrite(array[0].librerie, sizeof(array[0].librerie),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i-1))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)), SEEK_SET);
						fwrite(array[0].descrizione, sizeof(array[0].descrizione),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i-1))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)), SEEK_SET);
						fwrite(array[0].ritorno, sizeof(array[0].ritorno),1,  new_fun);
						fseek(new_fun, ((sizeof(array[0])*(i-1))+sizeof(array[0].ID)+sizeof(array[0].nome) + sizeof(array[0].tipo)+sizeof(array[0].librerie)+sizeof(array[0].descrizione)+sizeof(array[0].ritorno)), SEEK_SET);
						fwrite(array[0].parametri, sizeof(array[0].parametri),1,  new_fun);
					}
				}

				ID_valido=ID_appoggio-1;

				tostring(ID_selezione, ID_valido);

				fseek(counter, 0, SEEK_SET);
				fwrite(ID_selezione,  sizeof(ID_selezione), 1,counter);		/*scrittura counter aggiornato*/
				fclose(counter);											/*chiusura file*/
				fclose(funzioni);
				fclose(new_fun);
				remove("function.dat");
				rename("new_fun.dat", "function.dat");
				printf("Eliminazione avvennuta con successo\n\n");
				getchar();
				c=1;
			}
			else
			{
				c=1;
			}

		} //chiusura while c==0
	}
}
