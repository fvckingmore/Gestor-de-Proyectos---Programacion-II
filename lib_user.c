/*

PARA COMPILAR EN WINDOWS SI ERRORES HACER LO SIGUIENTE:

1. COMENTAR LAS LLAMADAS DE LA FUNCION " scr(); " 
Y DESCOMENTAR LAS LLAMADAS A LA FUNCION " scrw(); "

2. COMENTAR " conio.c " Y DESCOMENTAR " conio.h "

3. EN LA LINEA 403, EN LA FUNCION " f_login() "
CAMBIAR " if (c == '\n') " POR " if (c == 13) "

*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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
	int level, del, id;

} USER;



//============
/*PROTOTIPOS*/
//============

//LIMPIA BUFFER
void buf() { int c; while ( (c = fgetc(stdin)) != EOF && c != '\n' ) {} }

//LIMPIA PANTALLA LINUX
void scr() { system("clear"); }

//LIMPIA PANTALLA WINDOWS
void scrw() { system("cls"); }


void f_add_users(int ID);
void f_show_users(int ID);
void f_standar_menu(USER user);
void f_admin_menu(USER user);
void f_relative_users_delete(int ID);
void f_absolute_users_delete();
void f_admin_users_manager_menu(USER user);

int f_login(USER *user);
int f_verify_login(char *temp_user, char *temp_pass, USER *user);
int f_verify_username(char *temp_user);
int f_verify_id(int ID);



//======
/*MAIN*/	//TEMPORAL
//======

/*int main() {	//TEMPORAL

	int op, v;	//TEMPORAL

	char aux_username[15]; //MUESTRA EL NOMBRE DE USUARIO AL INGRESAR
	int ID; //GUARDA EL ID DEL ADMIN PARA ADMINISTRAR USUARIOS 


		//f_add_users(ID);

		//f_show_users();
	

	do {	//MENU TEMPORAL


		scr();



		do {

			puts("BIENVENIDO");

			puts("1. Ingresar\n0. Salir\n");

			printf("Opcion => ");

			v = scanf("%d", &op);	buf();



			if ( !v || !( op >= 0 && op <= 1 ) ) {

				puts("Error, opcion incorrecta");

			} else if ( op == 1 ) {

				switch ( f_login(aux_username, &ID) ) {

					case 1: 

						f_admin_menu(aux_username, ID);

						break;

					case 2:

						f_standar_menu(aux_username);

						break;

				}

			}

		} while ( !v || !( op >= 0 && op <= 1 ) );

	} while (op != 0);

return 0;
}*/



//===========================
/*AÑADIR USUARIO AL ARCHIVO*/
//===========================

void f_add_users(int ID) {

	FILE *filep;
	USER aux;
	int op, v;



	srand(time(NULL));

	scr();

	//scrw();

	filep = fopen("users.bin", "ab");



	if (filep == NULL) {

		puts("Error al abrir el archivo"); 
		
		getchar(); 

		scr();

		//scrw();

	} else {

		do {

			scr();

			//scrw();

			aux.del = 0;



			do{

				printf("Ingrese su nombre de usuario: "); 
				
				gets(aux.username);


				if ( f_verify_username(aux.username) == 1 ) {

					puts("El nombre de usuario ya existe, ingrese otro");

				}

			}while ( f_verify_username(aux.username) == 1 );



			printf("Ingrese su contraseña: "); 
			
			gets(aux.password); puts("");



			do {


				printf("Nivel del Usuario\n\n1. Administrador\n2. Normal\n\n=> ");
				
				v = scanf("%d", &aux.level); buf();



				if (!v || !(aux.level >= 1 && aux.level <= 2)) {

					puts("Error, opcion incorrecta"); 

					getchar(); 

					scr();

					//scrw();

				} else {

					if ( aux.level == 1 ) {

						do {

							aux.id = rand() % (20 - 1 + 1) + 1;

						} while ( f_verify_id(aux.id) == 1 );

					} else if ( aux.level == 2 ) {

						aux.id = ID;

					}

				}

			} while (!v || !(aux.level >= 1 && aux.level <= 2));



			v = fwrite(&aux, sizeof(USER), 1, filep);



			if (v) {

				scr(); 

				//scrw();

				puts("Espere..."); system("sleep 1"); 
				
				puts("Usuario agregado correctamente"); 
				
				/*getchar();*/ system("sleep 0.75");


				do{

					scr();

					//scrw();

					printf("Desea agregar otro usuario?\n\n1. Si\n2. No\n\nOpcion => "); 
					
					v = scanf("%d", &op); buf();


					if (!v || !(op >= 1 && op <= 2)) {

						puts("Opcion incorrecta, intente de nuevo"); 
						
						getchar(); 

						scr();

						//scrw();

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

void f_show_users(int ID) {

	FILE *filep;
	USER aux;
	filep = fopen("users.bin", "rb");



	if (filep == NULL) {

		puts("Error al abrir el archivo"); 

		getchar(); 

		scr();

		//scrw();

	} else {

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ){

			if ( !aux.del && aux.id == ID ) {

				printf("Usuario: %s\n", aux.username);

				printf("Contraseña: %s\n", aux.password);


				switch(aux.level) {

					case 2: 

						puts("Nivel: Normal"); 

						printf("ID: %d\n", aux.id);	//TEMPORAL

						break;


					case 1: 

						puts("Nivel: Administrador"); 

						printf("ID: %d\n", aux.id);

						break;

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

int f_login(USER *user) {

	char temp_user[15], temp_pass[15], c;
	int v, i;



	do {

		//scr();

		printf("USUARIO: ");	gets(temp_user); 

		i = 0;

		printf("CONTRASEÑA: ");	/*gets(temp_pass);*/



		while (c = getch()) {	/*Oculta la contraseña y muestra "*" */

            if (c == '\n') {

					temp_pass[i] = '\0';

					break;
                
            } else {

                if (i < 15) {

                    printf("*");

                    temp_pass[i] = c;

                    i++;

                }

            }

     	}



        puts("\n");

        puts("Espere...\n");

        system("sleep 1");



		/*if ( f_verify_login(temp_user, temp_pass) == 1 ) {

			v = 1;	

		} else {

			puts("Usuario o contraseña incorrecta, intente de nuevo");

			v = 0;
		}*/



		switch ( f_verify_login(temp_user, temp_pass, user) ) {

			case 1: 

				v = 1;	break;


			case 2: 

				v = 2;	break;

				
			default: 

				puts("Usuario o contraseña incorrecta, presione una tecla para continuar...");

				getchar(); v = 0;	break;

		}

	} while (v == 0);

return (v);

}



//=================
/*VALIDAR USUARIO*/
//=================

int f_verify_login(char *temp_user, char *temp_pass, USER *user) {

	FILE *filep;
	USER aux;
	int valid;



	filep = fopen("users.bin", "rb");



	if (filep == NULL) {

		puts("Error al abrir el archivo");

	} else {

		fseek(filep, 0, SEEK_SET);

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ) {

			if ( strcmp(temp_user, aux.username) == 0 ) {

				if ( strcmp(temp_pass, aux.password) == 0 ) {

					switch(aux.level) {

						case 1: 

							valid = 1;	

							*user = aux;

							break;


						case 2: 

							valid = 2;	

							*user = aux;

							break;
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

void f_standar_menu(USER user) {

	int op, v;



	do {

		do {

			printf("Que desea hacer, %s: \n\n", user.username);

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

void f_admin_menu(USER user) {

	int op, v;



	do {

		scr();

		//scrw();



		do {

			printf("Que desea hacer, %s: \n\n", user.username);

			printf("1. Administrar usuarios\n2. Administrar proyectos\n3. Administrar tareas\n4. Grafica de Gantt\n0. Salir\n\nOpcion => ");

			v = scanf("%d", &op);	buf();



			if ( !v || !(op >= 0 && op <= 4) ) {

				puts("Error, opcion incorrecta");

			}

		} while ( !v || !(op >= 0 && op <= 4) );


		switch (op) {

			case 1: 

				f_admin_users_manager_menu(user);

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
/*BORRADO RELATIVO DE USUARIO*/
//==============================

void f_relative_users_delete(int ID) {

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

			//scrw();

			fseek(filep, 0, SEEK_SET);

			f_show_users(ID);

			printf("Ingrese el usuario que desea eliminar: "); 

			gets(temp_user); del = 0;



			do {

				printf("Esta seguro que desea eliminar a %s?\n\n", temp_user);

				printf("1. Si\n2. No\n\nOpcion => "); v = scanf("%d", &op);


				if ( !v || !( op >= 1 && op <= 2 ) ) {

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

					scr(); 

					//scrw();

					puts("Espere...");	system("sleep 1"); 

					puts("Usuario eliminado");	system("sleep 0.75");	

					scr();

					//scrw();

				} else {

					scr();	

					//scrw();

					puts("El usuario ingresado no existe");	getchar();

				}



				do {

					printf("Desea eliminar otro usuario?\n\n1. Si\n2. No\n\nOpcion => ");

					v = scanf("%d", &op);	buf();


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

			//scrw();

			printf("Desea borrar permanentemente los usuarios?\n\n");

			printf("1. Si\n2. No\n\nOpcion => "); 

			v = scanf("%d", &op);	buf();



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

			scr();	

			//scrw();

			puts("Espere...");	system("sleep 1");

			puts("Usuarios eliminados correctamente");	system("sleep 0.75");

		}



		fclose(filep);

		fclose(filep_aux);
		
		remove("users.bin");

		rename("temp.bin", "users.bin");
	}

}



//==================================
/*VALIDA EL ID DE USUARIOS ADMIN*/
//==================================

int f_verify_id(int ID) {

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

			if ( ID == aux.id ) {

				exist = 1; break;
			}

		}

	}


	fclose(filep);

return (exist);

}



//======================================
/*MENU PARA ADMINISTRACION DE USUARIOS*/
//======================================

void f_admin_users_manager_menu(USER user) {

	int op, v;



	do {

		scr();

		//scrw();



		do {

			printf("Que desea hacer %s: \n\n", user.username);

			printf("1. Agregar Usuarios\n2. Mostrar Usuarios\n3. Borrar Usuarios\n4. Vaciar papaelera\n0. Volver al menu anterior\n\nOpcion => "); 

			v = scanf("%d", &op);	buf();



			if ( !v || !( op >= 0 && op <= 4 ) ) {

				puts("Error, opcion incorrecta");

				getchar();

			}

		} while ( !v || !( op >= 0 && op <= 4 ) );



		switch (op) {

			case 1: 

				f_add_users(user.id);

				break;


			case 2: 

				f_show_users(user.id); getchar();

				break;


			case 3: 

				f_relative_users_delete(user.id);

				break;


			case 4: 

				f_absolute_users_delete();

				break;


			case 0: 

				puts("Salida");

				break;
		}

	} while ( op != 0 );

}