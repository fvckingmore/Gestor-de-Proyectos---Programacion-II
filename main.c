#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib_user.c"


int main(void) {	

	int op, v;	

	USER user;


	
	while (1) {

		scr();



		while (1) {

			scr();

			printf(	"BIENVENIDO\n\n"
					"1. Ingresar\n"
					"0. Salir\n\n"
					"Opcion => ");

			v = scanf("%d", &op);	buf();



			if (v) {

				if ( op == 1 ) {

					switch ( f_login(&user) ) {

						case 1: 

							f_admin_menu(user);

							break;

						case 2:

							f_standar_menu(user);

							break;

					}

				} else if (op == 1234) {

					scr(); 

					puts("Entrando a modo debbug");

					#ifdef __linux__

						system("sleep 1.5");

					#elif _WIN32

						Sleep(1500);

					#endif

					scr();

					f_show_all_users();

					getchar();

				} else if (op == 0) {

					scr(); puts("Hasta luego"); break;

				} else {

					scr(); puts("Error, opcion incorrecta"); getchar();

				}

			} else {

				scr(); puts("Error, opcion incorrecta"); getchar();
			}

		}

		

		if (op == 0) {

			break;
		}

	} 

	


	//DESACTIVADO

	if (1 == 0){	

		do {

			puts("BIENVENIDO");

			puts("1. Ingresar\n0. Salir\n");

			printf("Opcion => ");

			v = scanf("%d", &op);	buf();



			if ( !v || !( op >= 0 && op <= 1 ) ) {

				puts("Error, opcion incorrecta");

			} else if ( op == 1 ) {

				switch ( f_login(&user) ) {

					case 1: 

						f_admin_menu(user);

						break;

					case 2:

						f_standar_menu(user);

						break;

				}

			}

		} while ( !v || !( op >= 0 && op <= 1 ) );

	}				

	//DESACTIVADO

	

return 0;

}