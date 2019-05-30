#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib_user.h"
#include "misc.h"
#include "lib_pro.h"

int main(void) {	

	int op, v;	

	USER user;


	
	if (1 == 1) {

		while (1) {

			scr();



			while (1) {

				scr();

				printf(	"=======================\n"
						"=      BIENVENIDO     =\n"
						"=                     =\n"
						"=          AL         =\n"
						"=                     =\n"
						"= GESTOR DE PROYECTOS =\n"
						"=======================\n\n"

						"[1] Ingresar\n"
						"[0] Salir\n\n"
						"Opcion => [ ]\b\b");

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

						puts("Entrando a modo GOD...");

						wait(1.5);

						scr();

						f_show_all_users();

						getchar();

					} else if (op == 0) {

						scr(); 

						//puts("Hasta luego"); 

						break;

					} else {

						puts("Error, opcion incorrecta"); 

						getchar();

					}

				} else {

					puts("Error, opcion incorrecta"); 

					getchar();
				}

			}

			

			if (op == 0) {

				break;
			}

		} 

	}

	if (1 == 0) {

		f_add_users(1);

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