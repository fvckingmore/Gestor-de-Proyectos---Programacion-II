#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib_user.c"


int main() {	

	int op, v;	

	USER user;


	
	do {

		scr();



		do {

			scr();

			puts("BIENVENIDO");

			puts("1. Ingresar\n0. Salir\n");

			printf("Opcion => ");

			v = scanf("%d", &op);	buf();



			if ( v || (op == 0) || (op == 1) || (op == 1234) ) {

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

					//scrw();

					puts("Entrando a modo debbug");

					system("sleep 1.5");

					scr();

					//scrw();

					f_show_all_users();

					getchar();

				} else if (op == 0) {

					scr(); puts("Hasta luego"); getchar(); break;

				} else {

					scr(); puts("Error, opcion incorrecta"); getchar();

				}

			} else {

				scr(); puts("Error, opcion incorrecta"); getchar();
			}

		} while ( v || (op == 1) || (op == 1234) );

		/*do {

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

		} while ( !v || !( op >= 0 && op <= 1 ) );*/

	} while (op != 0);

return 0;

}