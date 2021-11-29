#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utility.h"

int ricerca(FILE* funzioni, FILE* lib)
{
	int i=0;
	int j=0;
	int check=0;
	int k=0;
	int x=0;
	int n=0;
	int y=0;
	int found_f=0;		/*flag che varia se si trova almeno un risultato tra le funzioni*/ 
	int found_l=0;		/*flag che varia se si trova almeno un risultato tra le librerie*/
	int n_funzioni=0;	/*numero di funzioni presenti nel file*/
	int n_lib=0;		/* numero di librerie presenti nel file*/
	int selezione_int=0;

	char selezione[4]={0};		/*legge la selezione da tastiera*/
	char n_funzioni_c[4]={0};	/*legge il numero di funzioni da file*/
	char n_lib_c[4]={0};		/*legge il numero di librerie da file*/
	char ID[4]={0};				/*legge l'ID da file*/
	char c=0;

	record_fun search_f;	/* variabile d'appoggio per le funzioni*/
	record_lib search_l;	/* variabile d'appoggio per le librerie*/

	char word[25]={0};
	char word_d[25]={0};
	char* result=NULL;

	FILE* counter=NULL;

	counter=fopen("counter.dat", "rb");   /*nel file counter verrano salvati 1) cont.funzioni, 2)cont.librerie*/

	if(counter==NULL)		/*se il file counter non viene aperto*/
	{
		printf("L'apertura del file non e' andata a buon fine\n\nRiavviare il programma e riprovare\n\n");
		getchar();
	}
	else
	{
		system("cls");
		fseek(counter, 0, SEEK_SET);
		fgets(n_funzioni_c, sizeof(n_funzioni), counter);		/*caricamento numero funzioni da file*/
		n_funzioni=atoi(n_funzioni_c);
		fseek(counter, sizeof(int), SEEK_SET);
		fgets(n_lib_c, sizeof(int), counter);					/*caricamento numero librerie da file*/
		n_lib=atoi(n_lib_c);
	}

	do
	{
		do
		{
			printf("Inserire la parola da cercare\n\n");
			fgets(word, sizeof(word), stdin);				/*presa in input della stringa da cercare*/
			check=strlen(word);
			fflush(stdin);
			if(check <= 1)		/*controllo sull'input*/
			{
				printf("Non e' stato inserito nessun parametro di ricerca\n\nRiprovare\n");
				getchar();
				system("cls");
				i=0;		/*flag per controllare il ciclo*/
			}
			else
			{
				i=1;		/*flag per controllare il ciclo*/
				system("cls");
			}
		} while(i==0);

		for(i=0; i < check; i++) /*ciclo che ottimizza la stringa in input rendendola tutta minuscola*/
		{
			x=islower(word[i]); //zero quando non è minuscolo
			if(x==0)					
			{
				c=word[i];
				word[i]=tolower(c);
			}
		}

		found_f=0;
		found_l=0;
		strcpy(word_d, word);
		k=(strlen(word_d)-1);
		word_d[k]=word_d[k]^word_d[k];

		for(i=0; i<n_funzioni; i++) /* ciclo for per caricamento e confronto dei record*/
		{
			fseek(funzioni, ((sizeof(search_f))*(i)), SEEK_SET); /*posizionamento del puntatore al record da search_fre*/
			fgets(ID, sizeof(ID), funzioni);						/*lettura valori funzioni*/
			search_f.ID=atoi(ID);
			fseek(funzioni, ((sizeof(search_f)*(i))+sizeof(search_f.ID)), SEEK_SET); /*posizionamento del puntatore*/
			fgets(search_f.nome, sizeof(search_f.nome), funzioni);					/*lettura nome da file*/

			check=strlen(search_f.nome);			

			for(n=0; n < check; n++)	/*trasforma in minuscolo la stringa*/
			{
				x=islower(search_f.nome[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_f.nome[n];
					search_f.nome[n]=tolower(c);
				}
			}

			fseek(funzioni, ((sizeof(search_f)*(i))+sizeof(search_f.ID)+sizeof(search_f.nome)), SEEK_SET);
			fgets(search_f.tipo, sizeof(search_f.tipo), funzioni);

			check=strlen(search_f.tipo);

			for(n=0; n < check; n++)
			{
				x=islower(search_f.tipo[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_f.nome[n];
					search_f.nome[n]=tolower(c);
				}
			}

			fseek(funzioni, ((sizeof(search_f)*(i))+sizeof(search_f.ID)+sizeof(search_f.nome) + sizeof(search_f.tipo)), SEEK_SET);
			fgets(search_f.librerie, sizeof(search_f.librerie), funzioni);

			check=strlen(search_f.librerie);

			for(n=0; n < check; n++)
			{
				x=islower(search_f.librerie[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_f.librerie[n];
					search_f.librerie[n]=tolower(c);
				}
			}

			fseek(funzioni, ((sizeof(search_f)*(i))+sizeof(search_f.ID)+sizeof(search_f.nome) + sizeof(search_f.tipo)+sizeof(search_f.librerie)+sizeof(search_f.descrizione)), SEEK_SET);
			fgets(search_f.ritorno, sizeof(search_f.ritorno), funzioni);

			check=strlen(search_f.ritorno);

			for(n=0; n < check; n++)
			{
				x=islower(search_f.ritorno[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_f.ritorno[n];
					search_f.ritorno[n]=tolower(c);
				}
			}

			fseek(funzioni, ((sizeof(search_f)*(i))+sizeof(search_f.ID)+sizeof(search_f.nome) + sizeof(search_f.tipo)+sizeof(search_f.librerie)+sizeof(search_f.descrizione)+sizeof(search_f.ritorno)), SEEK_SET);
			fgets(search_f.parametri, sizeof(search_f.parametri), funzioni);

			check=strlen(search_f.parametri);

			for(n=0; n < check; n++)
			{
				x=islower(search_f.parametri[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_f.parametri[n];
					search_f.parametri[n]=tolower(c);
				}
			}

			fseek(funzioni, ((sizeof(search_f)*(i))+sizeof(search_f.ID)+sizeof(search_f.nome) + sizeof(search_f.tipo)+sizeof(search_f.librerie)), SEEK_SET);
			fgets(search_f.descrizione, sizeof(search_f.descrizione), funzioni);

			check=strlen(search_f.descrizione);

			for(n=0; n < check; n++)
			{
				x=islower(search_f.descrizione[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_f.descrizione[n];
					search_f.descrizione[n]=tolower(c);
				}
			}


			k=strcmp(word, search_f.nome);			/* k diventa 0 se le due stringhe sono uguali */
			if(k==0)
			{
				printf("Funzioni: %d \t %s\n", search_f.ID, search_f.nome); 		/*stampa il risultato se sono uguali*/
				found_f++;
			}
			else
			{
				k=strcmp(word, search_f.tipo);
				if(k==0)
				{
					printf("Funzioni: %d \t %s\n", search_f.ID, search_f.nome);
					found_f++;
				}
				else
				{
					k=strcmp(word, search_f.librerie);
					if(k==0)
					{
						printf("Funzioni: %d \t %s\n", search_f.ID, search_f.nome);
						found_f++;
					}
					else
					{
						k=strcmp(word,search_f.ritorno);
						if(k==0)
						{
							printf("Funzioni: %d \t %s\n", search_f.ID, search_f.nome);
							found_f++;
						}
						else
						{
							k=strcmp(word, search_f.parametri);
							if(k==0)
							{
								printf("Funzioni: %d \t %s\n", search_f.ID, search_f.nome);
								found_f++;
							}
							else
							{
								result=strstr(search_f.descrizione, word_d);
								if(result!=NULL)
								{
									printf("Funzioni: %d \t %s\n", search_f.ID, search_f.nome);
									found_f++;
								}
							}
						}
					}
				}
			}
		}
		if(found_f == 0)
		{
			printf("Nessun risultato tra le funzioni!\n\n");			/* in caso non viene trovata nemmeno una corrispondenza stampa cio */
		}

		for(i=0; i < n_lib; i++)
		{

			fseek(lib, ((sizeof(search_l))*(i)), SEEK_SET); /*posizionamento del puntatore al record da search_lre*/
			fgets(ID, sizeof(ID), lib);						/*lettura valornlib*/
			search_l.ID=atoi(ID);

			fseek(lib, ((sizeof(search_l)*(i))+sizeof(search_l.ID)), SEEK_SET); /*posizionamento del puntatore*/
			fgets(search_l.nome, sizeof(search_l.nome), lib);

			check=strlen(search_l.nome);

			for(n=0; n < check; n++)
			{
				x=islower(search_l.nome[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_l.nome[n];
					search_l.nome[n]=tolower(c);
				}
			}

			fseek(lib, ((sizeof(search_l)*(i))+sizeof(search_l.ID)+sizeof(search_l.nome) + sizeof(search_l.descrizione)), SEEK_SET);
			fgets(search_l.licenza, sizeof(search_l.licenza), lib);

			check=strlen(search_l.licenza);

			for(n=0; n < check; n++)
			{
				x=islower(search_l.licenza[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_l.licenza[n];
					search_l.licenza[n]=tolower(c);
				}
			}

			fseek(lib, ((sizeof(search_l)*(i))+sizeof(search_l.ID)+sizeof(search_l.nome)), SEEK_SET);
			fgets(search_l.descrizione, sizeof(search_l.descrizione), lib);

			check=strlen(search_l.descrizione);

			for(n=0; n < check; n++)
			{
				x=islower(search_l.descrizione[n]); //zero quando non è minuscolo
				if(x==0)
				{
					c=search_l.descrizione[n];
					search_l.descrizione[n]=tolower(c);
				}
			}


			k=strcmp(word, search_l.nome);
			if(k==0)
			{
				printf("Librerie: %d \t %s\n", search_l.ID, search_l.nome);
				found_l++;
			}
			else
			{
				k=strcmp(word, search_l.licenza);
				if(k==0)
				{
					printf("Librerie: %d \t %s\n", search_l.ID, search_l.nome);
					found_l++;
				}
				else
				{
					result=strstr(search_l.descrizione, word_d);
					if(result!=NULL)
					{
						printf("Librerie: %d \t %s\n", search_l.ID, search_l.nome);
						found_l++;
					}
				}
			}
		}

		if(found_l == 0)
		{
			printf("Nessun risultato tra le librerie!\n\n");
		}
		getchar();
		system("cls");
		do 		/* Menu per la chiusura della funzione*/
		{
			printf("Si desidera selezionare una nuova funzione o uscire? \n\n1) Uscire\n2) Ricercare altra funzione\n\n");
			fgets(selezione, sizeof(selezione), stdin);

			fflush(stdin);
			selezione_int=atoi(selezione);

			switch(selezione_int)
			{
			case 1:
				j=1;
				y=1;
				system("cls");
				fclose(counter);
				break;
			case 2:
				j=0;
				y=1;
				system("cls");
				break;
			default:
				printf("la selezione effettuata non e' valida\n\n");
				y=0;
				system("cls");
			}
		} while(y==0);

	} while(j==0);
	if(found_l==0 && found_f==0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void tostring(char str[], int num)
{
	int i, rem, len = 0, n;

	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}



void scambio_funzioni(record_fun *array, int i)
{
	record_fun appoggio_fun;

	appoggio_fun.ID=array[i].ID;
	array[i].ID=array[i+1].ID;
	array[i+1].ID=appoggio_fun.ID;

	strcpy(appoggio_fun.nome, array[i].nome);
	strcpy(array[i].nome, array[i+1].nome);
	strcpy(array[i+1].nome, appoggio_fun.nome);

	strcpy(appoggio_fun.tipo, array[i].tipo);
	strcpy(array[i].tipo, array[i+1].tipo);
	strcpy(array[i+1].tipo, appoggio_fun.tipo);

	strcpy(appoggio_fun.librerie, array[i].librerie);
	strcpy(array[i].librerie, array[i+1].librerie);
	strcpy(array[i+1].librerie, appoggio_fun.librerie);

	strcpy(appoggio_fun.descrizione, array[i].descrizione);
	strcpy(array[i].descrizione, array[i+1].descrizione);
	strcpy(array[i+1].descrizione, appoggio_fun.descrizione);

	strcpy(appoggio_fun.ritorno, array[i].ritorno);
	strcpy(array[i].ritorno, array[i+1].ritorno);
	strcpy(array[i+1].ritorno, appoggio_fun.ritorno);

	strcpy(appoggio_fun.parametri, array[i].parametri);
	strcpy(array[i].parametri, array[i+1].parametri);
	strcpy(array[i+1].parametri, appoggio_fun.parametri);
}

void scambio_lib(record_lib *array, int i)
{
	record_lib appoggio_lib;

	appoggio_lib.ID=array[i].ID;
	array[i].ID=array[i+1].ID;
	array[i+1].ID=appoggio_lib.ID;

	strcpy(appoggio_lib.nome, array[i].nome);
	strcpy(array[i].nome, array[i+1].nome);
	strcpy(array[i+1].nome, appoggio_lib.nome);

	strcpy(appoggio_lib.descrizione, array[i].descrizione);
	strcpy(array[i].descrizione, array[i+1].descrizione);
	strcpy(array[i+1].descrizione, appoggio_lib.descrizione);

	strcpy(appoggio_lib.licenza, array[i].licenza);
	strcpy(array[i].licenza, array[i+1].licenza);
	strcpy(array[i+1].licenza, appoggio_lib.licenza);
}

record_fun load_funzioni(FILE* funzioni, int i)		//implementare ad ogni caricamento di struct
{
	record_fun load;
	char n_funzioni_c[4]={0};

	fseek(funzioni, ((sizeof(load))*i), SEEK_SET); /*posizionamento del puntatore al record da modificare*/
	fgets(n_funzioni_c, sizeof(n_funzioni_c), funzioni);						/*lettura valori funzioni*/
	load.ID=atoi(n_funzioni_c);
	fseek(funzioni, ((sizeof(load)*i)+sizeof(load.ID)), SEEK_SET); /*posizionamento del puntatore*/
	fgets(load.nome, sizeof(load.nome), funzioni);
	fseek(funzioni, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome)), SEEK_SET);
	fgets(load.tipo, sizeof(load.tipo), funzioni);
	fseek(funzioni, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome) + sizeof(load.tipo)), SEEK_SET);
	fgets(load.librerie, sizeof(load.librerie), funzioni);
	fseek(funzioni, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome) + sizeof(load.tipo)+sizeof(load.librerie)), SEEK_SET);
	fgets(load.descrizione, sizeof(load.descrizione), funzioni);
	fseek(funzioni, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome) + sizeof(load.tipo)+sizeof(load.librerie)+sizeof(load.descrizione)), SEEK_SET);
	fgets(load.ritorno, sizeof(load.ritorno), funzioni);
	fseek(funzioni, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome) + sizeof(load.tipo)+sizeof(load.librerie)+sizeof(load.descrizione)+sizeof(load.ritorno)), SEEK_SET);
	fgets(load.parametri, sizeof(load.parametri), funzioni);

	return load;
}

record_lib load_lib(FILE* lib, int i)
{
	record_lib load;
	char n_lib_c[4]={0};

	fseek(lib, ((sizeof(load))*i), SEEK_SET); /*posizionamento del puntatore al record da visualizzare*/
	fgets(n_lib_c, sizeof(n_lib_c), lib);						/*lettura valori lib*/
	load.ID=atoi(n_lib_c);
	fseek(lib, ((sizeof(load)*i)+sizeof(load.ID)), SEEK_SET); /*posizionamento del puntatore*/
	fgets(load.nome, sizeof(load.nome), lib);	/*lettura valori lib*/
	fseek(lib, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome)), SEEK_SET);	/*posizionamento del puntatore*/
	fgets(load.descrizione, sizeof(load.descrizione), lib);	/*lettura valori lib*/
	fseek(lib, ((sizeof(load)*i)+sizeof(load.ID)+sizeof(load.nome) + sizeof(load.descrizione)), SEEK_SET);	/*posizionamento del puntatore*/
	fgets(load.licenza, sizeof(load.licenza), lib);		/*lettura valori lib*/

	return load;
}
