#ifndef MISC_H
#define MISC_H



#ifdef __linux__

	#include <unistd.h>

#elif _WIN32

	#include <windows.h>

#endif


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
void wait(int n) {		// <-- wait(TIEMPO A ESPERAR EN SEGUNDOS)

	#ifdef __linux__

		sleep(n);

	#elif _WIN32

		n = n * 1000;
		Sleep(n);

	#endif

}



#endif