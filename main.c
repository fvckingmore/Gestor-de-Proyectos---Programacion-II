#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib_user.h"
#include "misc.h"

int main(void) {	

	int op, v;	

	USER user;


	
	while (1) {

		scr();



		while (1) {

			scr();
			
			/*printf(	"      .       ......      ..     ........     ....      ...\n"
					" .lxdooodk,  xXoooooc  lkdoodxd :oooXNdool .xOdccdOd.  cWdooxO,\n"
					".Xx       .  xO       ,Mc           O0     Kd      k0  cN.   kO\n"
					"lN.   .''..  xNxxxxxl  l00kdl;.     O0    ,M,      ;M. cW:;;o0'\n"
					":W,   :ccNo  xO           ..,dN'    O0    .W:      lN. cW:,lXc\n"
					" oXo'. .'Xo  x0...... 'l,....oX.    O0     :Ko'..'dK;  cN.  .x0;\n"
					"   ,coooc,   'cccccc;  ,clooc,      ,;       ,cooc,    .:     'c.\n\n"

					".XOxxxkd'   .XOxxxxx'\n"
					".M;    ,0x  .M,      \n"
					".M;     'Mc .Mkooooo.\n"
					".M;     ,M: .M,      \n"
					".M;   .:0l  .M,      \n"
					".kdoooo:.   .kdooooo.\n\n"


					".ooool;   cooooc.     'loooo;   ;c     ;c  coooooo;   .;lool;.:ooooooool  .cooooc.    .coooc;.\n"
					".Mo...xX. 00...:N:   xK;   .dX. .Ok   o0.  Kk.....   dKc....c: ...kX.... cXc.  .cX;  oK,...,l,\n"
					".Ml   ;W' 0O   .Nc  :W.      kO   xO'kk    K0,,,,,. oW'           xK    .W:      lN. xK,..    \n"
					".M0oodx,  0Xod0K,   lN       dK    oMd     K0;,,,,. OX            xK    ,M,      ;M.  'coxxOx'\n"
					".Ml       0O  .OO.  .Wc     .Xo    ,M:     Kx       cMc           xK     Kx      OO         K0\n"
					".Ml       0O    :Ko. 'kkoclxOc     ,M:     KXooooo;  ;kklccox:    xK     .xOdccdOd.  dkocclxO'\n"
					"                        ....                            ....                ....       ....   \n");*/

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

					puts("Entrando a modo debbug");

					wait(1.5);

					scr();

					f_show_all_users();

					getchar();

				} else if (op == 0) {

					scr(); 

					//puts("Hasta luego"); 

					break;

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