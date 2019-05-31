#ifndef MISC_H
#define MISC_H



#ifdef __linux__

	#include <unistd.h>

#elif _WIN32

	#include <windows.h>

#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



//=============
/*ESTRUCTURAS*/
//=============

typedef struct DT{
	
	int day, month, year;
	
} DT;


typedef struct TASK {
	
	DT start, end;
	int del, status;
	char ref[10], p_id[10], user[50];
	char information[100];
	
} TASK;


typedef struct LIST {

	TASK task;
	struct LIST *next;

} LIST;


typedef struct USER {	//ESTRUCTURA TIPO USUARIO

	char username[15], password[15], name[40];
	int level, del, id, admin_id;

} USER;


typedef struct PROJECT {

	char title[20], id[10];
	DT start, end;
	int del, status;	
	char louder[25], infor[100], location[30];
	
} PROJECT;

//===========
/*FUNCIONES*/
//===========



//LIMPIA EL BUFFER
void buf(void) { 

	#ifdef __linux__

		int c; while ( (c = fgetc(stdin)) != EOF && c != '\n' ) {}


	#elif _WIN32

		fflush(stdin);

	#endif

}

//LIMPIA PANTALLA
void scr(void) { 

	#ifdef __linux__

		system("clear");


	#elif _WIN32

		system("cls");

	#endif
}

//DETIENE EL PROGRAMA POR UN TIEMPO
void wait(float n) {		// <-- wait(TIEMPO A ESPERAR EN SEGUNDOS)

	#ifdef __linux__

		n = n * 1000000;

		usleep(n);

	#elif _WIN32

		n = n * 1000;
		Sleep(n);

	#endif

}

//COMPARACION DE CADENAS MEJORADA
int compare(char *string1, char *string2) {
	
	char aux[ strlen(string1) ], aux2[ strlen(string2) ];

	int i, j;
	


	for (i = 0, j = 0; i < strlen(string1); j++) {

		if ( isalnum(string1[j]) ) {

			aux[i] = toupper(string1[j]);

			i++;
		}

	}



	aux[i] = '\0';



	for (i = 0, j = 0; i < strlen(string2); j++) {

		if ( isalnum(string2[j]) ) {

			aux2[i] = toupper(string2[j]);

			i++;
		}

	}



	aux2[i] = '\0';


	
	if ( strcmp(aux, aux2) == 0 )

		return 0;


	else

		return 1;

}



//COMPARACION DE FECHAS
int f_compare_dt(DT date1, DT date2){
	
	int band = 2;


	
	if (date1.year > date2.year) {
		
		band = 1;

		
	} else if (date1.year == date2.year) {
		
		if (date1.month > date2.month) {
			
			band = 1;

		
		} else if (date1.month == date2.month) {
			
			if (date1.day > date2.day) {
				
				band = 1;
				

			} else if (date1.day == date2.day) {
				
				band = 0;
				
			}

		}
		
	}
	
return (band);

}



#endif
