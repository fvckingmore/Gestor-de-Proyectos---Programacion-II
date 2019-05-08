#ifndef MISC_H
#define MISC_H

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

#endif