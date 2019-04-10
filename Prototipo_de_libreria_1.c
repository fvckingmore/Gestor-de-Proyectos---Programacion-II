#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Libreria conio.h para linux, habilita funcion getch
//Comentar si se va a utiliza Windows
#include "conio.c"

//Comentar si se va a utilizar Linux
//#include <conio.h>



//=============
/*ESTRUCTURAS*/	
//=============

typedef struct {

	char username[15], password[15];
	int level, del;

} USER;



//============
/*PROTOTIPOS*/
//============

void buf() { int c; while ( (c = fgetc(stdin)) != EOF && c != '\n' ) {} }
void scr() { system("clear"); }
void f_add_users();
void f_show_users();
int f_login(char *aux_username);
int f_verify_login(char *temp_user, char *temp_pass);
void f_standar_menu(char *aux_username);
void f_admin_menu(char *aux_username);
void f_relative_users_delete();
void f_absolute_users_delete();
int f_verify_username(char *temp_user);


//======
/*MAIN*/	//TEMPORAL
//======

int main() {	//TEMPORAL

	char aux_username[15];
	int op;	//TEMPORAL

	do {	//MENU TEMPORAL

		scr();

		printf("1. Agregar\n2. Mostrar\n3. Ingresar\n4. Borrar\n5. Vaciar papaelera\nOpcion: ");
		scanf("%d", &op); buf();

		switch (op) {

			case 1: 

				f_add_users();

				break;

			case 2: 

				f_show_users(); getchar();

				break;

			case 3: 

				if (f_login(aux_username) == 2) {

					f_standar_menu(aux_username);

				} else {

					f_admin_menu(aux_username);
				}

				break;

			case 4: 

				f_relative_users_delete();

				break;

			case 5: 

				f_absolute_users_delete();

				break;


			case 0: 

				puts("Salida");

				break;
		}


	} while (op != 0);

	//scr();
	//f_add_users(); scr();
	//f_show_users();

	

return 0;
}



//===========================
/*AÑADIR USUARIO AL ARCHIVO*/
//===========================

void f_add_users() {

	FILE *filep;
	USER aux;
	int op, v;

	scr();

	filep = fopen("users.bin", "ab");

	if (filep == NULL) {

		puts("Error al abrir el archivo"); getchar(); scr();

	} else {

		do {

			scr();

			aux.del = 0;

			do{

				printf("Ingrese su nombre de usuario: "); gets(aux.username);

				if ( f_verify_username(aux.username) == 1 ) {

					puts("El nombre de usuario ya existe, ingrese otro");
				}

			}while ( f_verify_username(aux.username) == 1 );

			printf("Ingrese su contraseña: "); 
				 gets(aux.password); puts("");

			do {

				printf("Nivel del Usuario\n\n1. Administrador\n2. Normal\n\n=> "); v = scanf("%d", &aux.level); buf();

				if (!v || !(aux.level >= 1 && aux.level <= 2)) {

					puts("Error, opcion incorrecta"); getchar(); scr();
				}

			} while (!v || !(aux.level >= 1 && aux.level <= 2));

			v = fwrite(&aux, sizeof(USER), 1, filep);

			if (v) {

				scr(); puts("Espere..."); system("sleep 1"); 
				puts("Usuario agregado correctamente"); /*getchar();*/ system("sleep 0.75");

				do{

					scr();

					printf("Desea agregar otro usuario?\n\n1. Si\n2. No\n\nOpcion: "); v = scanf("%d", &op); buf();

					if (!v || !(op >= 1 && op <= 2)) {

						puts("Opcion incorrecta, intente de nuevo"); getchar(); scr();
					}

				} while (!v || !(op >= 1 && op <= 2));

			} else {

				puts("Error al agregar el usuario");
			}

		} while (op != 2);
	}

	fclose(filep);
}



//===========================
/*MOSTRAR LISTA DE USUARIOS*/  //TEMPORAL
//===========================

void f_show_users() {

	FILE *filep;
	USER aux;
	filep = fopen("users.bin", "rb");

	if (filep == NULL) {

		puts("Error al abrir el archivo"); getchar(); scr();

	} else {

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ){

			if (!aux.del) {

				printf("Usuario: %s\n", aux.username);

				printf("Contraseña: %s\n", aux.password);

				switch(aux.level) {

					case 2: puts("Nivel: Normal"); break;

					case 1: puts("Nivel: Administrador"); break;

				}

				puts("");
			}
		}
	}

	fclose(filep);
}



//====================
/*SISTEMA DE INGRESO*/
//====================

int f_login(char *aux_username) {

	char temp_user[15], temp_pass[15], c;
	int v, i;

	do {

		//scr();

		printf("USUARIO: "); gets(temp_user); 

		i = 0;

		printf("CONTRASEÑA: ");	/*gets(temp_pass);*/

		 while ( c = getch() ) {	/*Oculta la contraseña y muestra "*" */

            if (c == '\n') {

					temp_pass[i] = '\0'; break;
                
            } else {

                if (i < 15) {

                    printf("*"); temp_pass[i] = c; i++;
                }
            }
        }

        puts("\n"); puts("Espere...\n"); system("sleep 1");

		/*if ( f_verify_login(temp_user, temp_pass) == 1 ) {

			v = 1;	

		} else {

			puts("Usuario o contraseña incorrecta, intente de nuevo");

			v = 0;
		}*/

		switch ( f_verify_login(temp_user, temp_pass) ) {

			case 1: 

				v = 1;
				break;

			case 2: 

				v = 2;
				break;

			default: 

				puts("Usuario o contraseña incorrecta, presione una tecla para continuar...");
				getchar(); v = 0; break;
		}

	} while (v == 0);

	strcpy(aux_username, temp_user);

return (v);
}



//=================
/*VALIDAR USUARIO*/
//=================

int f_verify_login(char *temp_user, char *temp_pass) {

	FILE *filep;
	USER aux;
	int valid;

	filep = fopen("users.bin", "rb");
	fseek(filep, 0, SEEK_SET);

	if (filep == NULL) {

		puts("Error al abrir el archivo");

	} else {

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ) {

			if ( strcmp(temp_user, aux.username) == 0 ) {

				if ( strcmp(temp_pass, aux.password) == 0 ) {

					switch(aux.level) {

						case 1: valid = 1; break;

						case 2: valid = 2; break;
					}
				}
			}
		}
	}

	fclose(filep);

return (valid);
}



//============================
/*MENU PARA USUARIO ESTANDAR*/
//============================

void f_standar_menu(char *aux_username) {

	int op, v;

	do {

		do {

			printf("Que desea hacer, %s: \n\n", aux_username);
			printf("1. Buscar proyectos\n2. Administrar tareas\n3. Reporte de tareas\n4. Grafica de Gantt\n0. Salir\n\nOpcion => ");
			v = scanf("%d", &op); buf();

			if ( !v || !(op >= 0 && op <= 4) ) {

				puts("Error, opcion incorrecta");
			}

		} while ( !v || !(op >= 0 && op <= 4) );

		switch (op) {

			case 1: 

				puts("Buscar");
				break;

			case 2: 

				puts("Tareas");
				break;

			case 3: 

				puts("Reporte");
				break;

			case 4: 

				puts("Grafica");
				break;

			case 0: 

				puts("Salir");
				break;

		}

	} while (op != 0);
}



//===============================
/*MENU USUARIOS ADMINISTRADORES*/
//===============================

void f_admin_menu(char *aux_username) {

	int op, v;

	do {

		do {

			printf("Que desea hacer, %s: \n\n", aux_username);
			printf("1. Administrar usuarios\n2. Administrar proyectos\n3. Administrar tareas\n4. Grafica de Gantt\n0. Salir\n\nOpcion => ");
			v = scanf("%d", &op); buf();

			if ( !v || !(op >= 0 && op <= 4) ) {

				puts("Error, opcion incorrecta");
			}

		} while ( !v || !(op >= 0 && op <= 4) );

		switch (op) {

			case 1: 

				puts("Administrar usuarios");
				break;

			case 2: 

				puts("Administrar proyectos");
				break;

			case 3: 

				puts("Administrar tareas");
				break;

			case 4: 

				puts("Grafica");
				break;

			case 0: 

				puts("Salir");
				break;

		}

	} while (op != 0);
}



//==============================
/*BORRADO RELATIVO DE USUSARIO*/
//==============================

void f_relative_users_delete() {

	FILE *filep;
	USER aux;
	char temp_user[15];
	int del, op, v;

	filep = fopen("users.bin", "rb+");

	if (filep == NULL) {

		puts("Error al abrir el archivo");

	} else {

		do {

			scr();

			fseek(filep, 0, SEEK_SET);

			f_show_users();

			printf("Ingrese el usuario que desea eliminar: "); 
			gets(temp_user); del = 0;

			do {

				printf("Esta seguro que desea eliminar a %s?\n\n", temp_user);
				printf("1. Si\n2. No\n\nOpcion: "); v = scanf("%d", &op);

				if ( !v || !(op >= 1 && op <= 2) ) {

					puts("Error, opcion incorrecta");
				}

			} while ( !v || !(op >= 1 && op <= 2) );

			if (op == 1) {

				while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ) {

					if ( (strcmp(temp_user, aux.username) == 0) && aux.del == 0 ) {

						fseek(filep, ftell(filep) - sizeof(USER), SEEK_SET);

						aux.del = 1;

						fwrite(&aux, sizeof(USER), 1, filep);

						del = 1; break;
					} 
				}

				if (del == 1) {

					scr(); puts("Espere..."); system("sleep 1"); puts("Usuario eliminado"); system("sleep 0.75"); scr();

				} else {

					scr(); puts("El usuario ingresado no existe"); getchar();

				}

				do {

					printf("Desea eliminar otro usuario?\n\n1. Si\n2. No\n\nOpcion: ");
					v = scanf("%d", &op); buf();

					if ( !v || !( op >= 1 && op <= 2 ) ) {

						puts("Error, opcion incorrecta");
					}

				} while ( !v || !( op >= 1 && op <= 2 ) );

			}

		} while (op != 2);
	} 

	fclose(filep);
}



//=========================================
/*VERIFIACAR SI UN USUARIO ESTA REGISRADO*/
//=========================================

int f_verify_username(char *temp_user) {

	FILE *filep;
	USER aux;
	int exist;

	filep = fopen("users.bin", "rb");
	fseek(filep, 0, SEEK_SET);

	if (filep == NULL) {

		puts("Error al abrir el archivo");

	} else {

		exist = 0;

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ) {

			if ( strcmp(temp_user, aux.username) == 0 ) {

				exist = 1; break;
			}
		}
	}

	fclose(filep);

return (exist);
}



//================================================
/*ELIMINA PERMANENTEMENTE LOS USUARIOS DEL DISCO*/
//================================================

void f_absolute_users_delete() {

	FILE *filep;
	FILE *filep_aux;
	USER aux;
	int del, v, op;
	
	filep = fopen("users.bin", "rb");
	filep_aux = fopen("temp.bin", "wb");
			
	if ( filep == NULL || filep_aux == NULL) {

		puts("Error al abrir el archivo");

	} else {

		do {

			scr();

			printf("Desea borrar permanentemente los usuarios?\n\n");
			printf("1. Si\n2. No\n\nOpcion: "); v = scanf("%d", &op); buf();

			if ( !v || !(op >= 1 && op <= 2) ) {

				puts("Error, opcion incorrecta");
			}

		} while ( !v || !(op >= 1 && op <= 2) );

		if (op == 1) {

			del = 0;

			while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep)) {

				if (aux.del != 1) {

					fwrite(&aux, sizeof(USER), 1, filep_aux);

					del = 1;
				}
			}
		} 

		if (del == 1) {

			scr(); puts("Espere..."); system("sleep 1"); puts("Usuarios eliminados correctamente"); system("sleep 0.75");

		}

		fclose(filep);
		fclose(filep_aux);
		
		remove("users.bin");
		rename("temp.bin", "users.bin");
	}
}
