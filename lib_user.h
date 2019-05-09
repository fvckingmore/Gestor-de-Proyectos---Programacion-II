/*

PARA ENTRAR EN MODO DEBUG, AL INGRESAR LA OPCION TECLEAR " 1234 "

*/



#ifndef USER_H
#define USER_H



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "misc.h"

//DEFINE LIBRERIAS SEGUN LA PLATAFORMA EN LA CUAL SE TRABAJA

#ifdef _WIN32		

	#include <conio.h>
	#include <windows.h>

#endif



//=============
/*ESTRUCTURAS*/	
//=============

typedef struct {	//ESTRUCTURA TIPO USUARIO

	char username[15], password[15];
	int level, del, id, admin_id;

} USER;



//============
/*PROTOTIPOS*/
//============


void f_show_all_users(void);		//MUESTRA TODOS LOS USUARIOS EN MODO DEBBUG
void f_absolute_users_delete(void);	//BORRA FISICAMENTE LOS USUARIOS
void f_add_users(int ID);			//AGREGA USUARIOS A LA BASE DE DATOS
void f_show_users(int ID);			//MUESTRA LOS USUARIOS
void f_relative_users_delete(int ID);//BORRA VIRTUALMENTE LOS USUARIOS
void f_admin_edit(int ID, int aux_level);//EDICION DE USUARIOS PARA ADMINISTRADORES
void f_standar_edit(int ID, char *aux_username);//EDICION DE USUARIO ESTANDAR
void f_standar_menu(USER user);		//MENU PARA USUARIO ESTANDAR
void f_admin_menu(USER user);		//MENU PARA ADMINISTRADOR
void f_admin_users_manager_menu(USER user);//MENU DE GESTION DE USUARIO PARA ADMINISTRADORES

int f_verify_id(int ID);			//VERIFICA EL IEDNTIFICADOR DE USUARIO
int f_verify_admin_id(int ID);		//VERIFICA EL IDENTIFICADOR DE ADMINISTRADOR DE USUARIO
int f_login(USER *user);			//SISTEMA DE INGRESO PARA USUARIOS
int f_verify_login( char *temp_user, char *temp_pass, USER *user );//VERIFICA EL INGRESO
int f_verify_username(char *temp_user);//VERIFICA SI EXISTE EL NOMRE DE USUARIO



//======
/*MAIN*/	//TEMPORAL
//======

/*int main() {	// TEMPORAL

	

	int op, v;	//TEMPORAL

	char aux_username[15]; //MUESTRA EL NOMBRE DE USUARIO AL INGRESAR
	int ID; //GUARDA EL ID DEL ADMIN PARA ADMINISTRAR USUARIOS 


		//f_add_users(ID);

		//f_show_users();
	

	do {	//MENU TEMPORAL


		scr();



		do {

			printf(	"BIENVENIDO\n\n
					1. Ingresar\n
					0. Salir\n");

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

	filep = fopen("users.bin", "ab");



	if (filep == NULL) {

		puts("Error al abrir el archivo"); 
		
		getchar(); 

		scr();


	} else {

		do {

			scr();

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


				printf(	"Nivel del Usuario\n\n"
						"[1] Administrador\n"
						"[2] Normal\n\n"
						"=> [ ]\b\b");
				
				v = scanf("%d", &aux.level); buf();



				if (!v || !(aux.level >= 1 && aux.level <= 2)) {

					puts("Error, opcion incorrecta, presione una tecla para continuar..."); 

					getchar(); 

					scr();


				} else {

					if ( aux.level == 1 ) {

						do {

							aux.admin_id = rand() % (80 - 1 + 1) + 1;

							aux.id = aux.admin_id;

						} while ( f_verify_admin_id(aux.admin_id) == 1 );


					} else if ( aux.level == 2 ) {

						aux.admin_id = ID;



						do {

							aux.id = rand() % (500 - 100 + 1) + 100;

						} while ( f_verify_id(aux.id) == 1 );

					}

				}

			} while (!v || !(aux.level >= 1 && aux.level <= 2));



			v = fwrite(&aux, sizeof(USER), 1, filep);



			if (v) {

				scr(); 

				puts("Espere..."); 

				wait(1);
				
				puts("Usuario agregado correctamente"); 
				
				/*getchar();*/ 

				wait(0.75);



				do{

					scr();

					printf(	"Desea agregar otro usuario?\n\n"
							"[1] Si\n"
							"[2] No\n\n"
							"Opcion => [ ]\b\b"); 
					
					v = scanf("%d", &op); buf();



					if (!v || !(op >= 1 && op <= 2)) {

						puts("Opcion incorrecta, intente de nuevo"); 
						
						getchar(); 

						scr();

					}

				} while (!v || !(op >= 1 && op <= 2));


			} else {

				puts("Error al agregar el usuario");

				getchar();

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



	scr();

	puts("Espere...");

	wait(1.5);

	scr();



	if (filep == NULL) {

		puts("Error al abrir el archivo"); 

		getchar(); 

		scr();


	} else {

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ){

			if ( !aux.del && aux.admin_id == ID ) {

				printf("Usuario: %s\n", aux.username);

				printf("Contraseña: %s\n", aux.password);



				switch(aux.level) {

					case 2: 

						puts("Nivel: Normal"); 

						printf("ADMIN ID: %d\n", aux.admin_id);	//TEMPORAL

						printf("ID: %d\n", aux.id);	//TEMPORAL

						break;


					case 1: 

						puts("Nivel: Administrador"); 

						printf("ADMIN ID: %d\n", aux.admin_id);	//TEMPORAL

						printf("ID: %d\n", aux.id);	//TEMPORAL

						break;

				}



				puts("");

				wait(0.40);

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

		scr();

		printf("USUARIO: ");

		gets(temp_user); 

		i = 0;



		#ifdef __linux__	//SISTEMA DE CONTRASEÑA PARA PLATAFORMA DE LINUX

			printf("CONTRASEÑA: ");	/*gets(temp_pass);*/

			system("stty -echo");	//OCULTA ENTRADA DE DATOS EN LINUX



			while (c = getchar()) {	/*Oculta la contraseña y muestra "*" */

				if (c == '\n') {

						temp_pass[i] = '\0';

						system("stty echo");	//RESTAURA ENTRADA DE DATOS EN LINUX

						break;

	                
				} else if (i < 15) {

	                    printf("*");

	                    temp_pass[i] = c;

	                    i++;

				}

	     	}


	    #elif _WIN32	//SISTEMA DE CONTRASEÑA PARA PLATAFORMA DE WINDOWS

			printf("CONTRASEÑA: ");	/*gets(temp_pass);*/



			while (c = getch()) {	/*Oculta la contraseña y muestra "*" */

				if (c == 13) {

						temp_pass[i] = '\0';

						break;


				} else if (c == 8 && i > 0) {

						putchar(8);

						putchar(' ');

						putchar(8);

						i--;


				} else if (i < 15 && c != 8) {

	                    printf("*");

	                    temp_pass[i] = c;

	                    i++;

				}

	     	}

	    #endif



        puts("\n");

        puts("Espere...\n");

        wait(1);



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



		if (v == 0) break; 

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

		getchar();

		scr();


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

		scr();



		do {

			printf(	"==================\n"
					"= MENU PRINCIPAL =\n"
					"==================\n\n");

			printf("Que desea hacer, %s: \n\n", user.username);

			printf(	"[1] Buscar proyectos\n"
					"[2] Administrar tareas\n"
					"[3] Reporte de tareas\n"
					"[4] Grafica de Gantt\n"
					"[5] Editar Usuario\n"
					"[0] Salir\n\n"
					"Opcion => [ ]\b\b");

			v = scanf("%d", &op); buf();



			if ( !v || !(op >= 0 && op <= 5) ) {

				puts("Error, opcion incorrecta, presione una tecla para continuar...");

				getchar();

				scr();

			}

		} while ( !v || !(op >= 0 && op <= 5) );



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


			case 5: 

				f_standar_edit(user.id, user.username);

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



		do {

			scr();

			printf(	"==================\n"
					"= MENU PRINCIPAL =\n"
					"==================\n\n");

			printf("Que desea hacer, %s: \n\n", user.username);

			printf(	"[1] Administrar usuarios\n"
					"[2] Administrar proyectos\n"
					"[3] Administrar tareas\n"
					"[4] Grafica de Gantt\n"
					"[0] Salir\n\n"
					"Opcion => [ ]\b\b");

			v = scanf("%d", &op);	buf();



			if ( !v || !(op >= 0 && op <= 4) ) {

				puts("Error, opcion incorrecta, presione una tecla para continuar...");

				getchar();

				scr();

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

		getchar();

		scr();


	} else {

		do {

			scr();

			fseek(filep, 0, SEEK_SET);

			f_show_users(ID);

			printf("Ingrese el usuario que desea eliminar: "); 

			gets(temp_user); 

			del = 0;

			puts("");



			do {

				printf("Esta seguro que desea eliminar a %s?\n\n", temp_user);

				printf(	"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();


				if ( !v || !( op >= 1 && op <= 2 ) ) {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			} while ( !v || !(op >= 1 && op <= 2) );



			if (op == 1) {

				while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ) {

					if ( (strcmp(temp_user, aux.username) == 0) && aux.del == 0 ) {

						if (ID == aux.admin_id) {

							fseek(filep, ftell(filep) - sizeof(USER), SEEK_SET);

							aux.del = 1;

							fwrite(&aux, sizeof(USER), 1, filep);

							del = 1; 

							break;

						} 

					} 

				}



				if (del == 1) {

					scr(); 

					puts("Espere...");	

					wait(1);

					puts("Usuario eliminado");	

					wait(0.75);

					scr();


				} else {

					scr();	

					puts("El usuario no existe o no puede ser borrado");

					getchar();

				}



				do {

					printf(	"Desea eliminar otro usuario?\n\n"
							"[1] Si\n"
							"[2] No\n\n"
							"Opcion => [ ]\b\b");

					v = scanf("%d", &op);	buf();


					if ( !v || !( op >= 1 && op <= 2 ) ) {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();

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

		getchar();

		scr();


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

void f_absolute_users_delete(void) {

	FILE *filep;
	FILE *filep_aux;
	USER aux;
	int del, v, op;
	


	filep = fopen("users.bin", "rb");

	filep_aux = fopen("temp.bin", "wb");
			


	if ( filep == NULL || filep_aux == NULL) {

		puts("Error al abrir el archivo");

		getchar();

		scr();


	} else {

		do {

			scr();

			printf("Desea borrar permanentemente los usuarios?\n\n");

			printf(	"[1] Si\n"
					"[2] No\n\n"
					"Opcion => [ ]\b\b"); 

			v = scanf("%d", &op);	buf();



			if ( !v || !(op >= 1 && op <= 2) ) {

				puts("Error, opcion incorrecta, presione una tecla para continuar...");

				getchar();

				scr();

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

			puts("Espere...");	

			wait(1);

			puts("Usuarios eliminados correctamente");	

			wait(0.75);

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

int f_verify_admin_id(int ID) {

	FILE *filep;
	USER aux;
	int exist;



	filep = fopen("users.bin", "rb");

	fseek(filep, 0, SEEK_SET);



	if (filep == NULL) {

		puts("Error al abrir el archivo");

		getchar();

		scr();


	} else {

		exist = 0;



		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ) {

			if ( ID == aux.admin_id ) {

				exist = 1; break;
			}

		}

	}


	fclose(filep);

return (exist);

}



//==========================
/*VALIDA EL ID DE USUARIOS*/
//==========================

int f_verify_id(int ID) {

	FILE *filep;
	USER aux;
	int exist;



	filep = fopen("users.bin", "rb");

	fseek(filep, 0, SEEK_SET);



	if (filep == NULL) {

		puts("Error al abrir el archivo");

		getchar();

		scr();


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



		do {

			scr();

			printf(	"==============================\n"
					"= ADMINISTRACION DE USUARIOS =\n"
					"==============================\n\n");

			printf("Que desea hacer %s: \n\n", user.username);

			printf(	"[1] Agregar Usuarios\n"
					"[2] Mostrar Usuarios\n"
					"[3] Borrar Usuarios\n"
					"[4] Vaciar papaelera\n"
					"[5] Editar Usuarios\n"
					"[0] Volver al menu anterior\n\n"
					"Opcion => [ ]\b\b"); 

			v = scanf("%d", &op);	buf();



			if ( !v || !( op >= 0 && op <= 5 ) ) {

				puts("Error, opcion incorrecta, presione una tecla para continuar...");

				getchar();

				scr();

			}

		} while ( !v || !( op >= 0 && op <= 5 ) );



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


			case 5: 

				f_admin_edit(user.id, user.level);

				break;


			case 0: 

				puts("Salida");

				break;
		}

	} while ( op != 0 );

}



//============================
/*MUESTRA TODOS LOS USUARIOS*/
//============================

void f_show_all_users(void) {

	FILE *filep;
	USER aux;
	filep = fopen("users.bin", "rb");



	if (filep == NULL) {

		puts("Error al abrir el archivo"); 

		getchar(); 

		scr();


	} else {

		while ( fread(&aux, sizeof(USER), 1, filep) && !feof(filep) ){

			printf("Usuario: %s\n", aux.username);

			printf("Contraseña: %s\n", aux.password);



			switch(aux.level) {

				case 2: 

					puts("Nivel: Normal"); 

					printf("ADMIN ID: %d\n", aux.admin_id);	//TEMPORAL

					printf("ID: %d\n", aux.id);	//TEMPORAL

					break;


				case 1: 

					puts("Nivel: Administrador"); 

					printf("ADMIN ID: %d\n", aux.admin_id);	//TEMPORAL

					printf("ID: %d\n", aux.id);	//TEMPORAL

					break;

			}



			puts("");

			wait(0.40);

		}

	}


	fclose(filep);

}



//==========================================
/*EDICION DE USUARIOS PARA ADMINISTRADORES*/
//==========================================

void f_admin_edit(int ID, int aux_level) {

	FILE *filep;
	USER aux;
	char aux_username[15];
	int exist, op, v;



	filep = fopen("users.bin", "rb+");

	srand(time(NULL));

	scr();



	while (1) {

		fseek(filep, 0, SEEK_SET);	/*<-- MUEVE EL CURSOR HACIA EL PRINCIPIO DEL ARCHIVO*/

		f_show_users(ID);	/*<-- MUESTRA LA LISTA DE USUARIOS QUE PUEDE EDITAR*/

		printf("Ingrese el nombre de usuario que desea modificar: ");

		gets(aux_username);

		exist = 0;

		

		/*BUSCA EN EL ARCHIVO, PARA VER SI EXISTE EL USUARIO QUE HA INGREASADO*/

		while ( fread( &aux, sizeof(USER), 1, filep ) && !feof(filep) ) {

			if ( strcmp(aux_username, aux.username) == 0 ) {

				if (aux.level == 2) {

					exist = 1;

					break;

				}

			}

		}



		/*SI EL USUARIO INGRESADO EXISTE*/

		if (exist) {

			scr();

			puts("DATOS DEL USUARIO\n");

			printf("Nombre: %s\n", aux.username);

			printf("Contraseña: %s\n", aux.password);

			printf("Tipo de usuario: ");

			

			switch (aux.level) {

				case 1:

					puts("Administrador\n");

					break;


				case 2:

					puts("Estandar\n");

					break;

			}



			puts("Elija los datos a modificar:\n");



			/*EDITAR EL NOMBRE DE USUARIO*/

			printf("Nombre actual: %s\n\n", aux.username);

			

			while (1) {

				printf(	"Desea modificar el nombre?\n\n"
						"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();

				

				if (v) {

					if (op >= 1 && op <= 2) {

						if (op == 1) {

							scr();

							printf("Ingrese nombre nuevo: ");

							gets(aux.username);

							break;


						} else if (op == 2) {

							break;

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();

					}


				} else {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			}



			scr();



			/*EDITAR CONTRASEÑA*/

			printf("Contraseña actual: %s\n\n", aux.password);

			

			while (1) {

				printf(	"Desea modificar la contraseña?\n\n"
						"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();

				

				if (v) {

					if (op >= 1 && op <= 2) {

						if (op == 1) {

							scr();

							printf("Ingrese contraseña nueva: ");

							gets(aux.password);

							break;


						} else if (op == 2) {

							break;

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();

					}	


				} else {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			}



			scr();



			/*EDITAR TIPO DE USUARIO*/

			if (aux_level == 1) {	//<-- SOLO SE EJECUTA SI EL USUARIO ES ADMINISTRADOR

				printf("Tipo de usuario actual: ");

				

				switch (aux.level) {

					case 1: 

						puts("Administrador\n");

						break;


					case 2: 

						puts("Estandar\n");

						break;

				}

				

				while (1) {

					printf(	"Desea modificar el tipo de usuario?\n\n"
							"[1] Si\n"
							"[2] No\n\n"
							"Opcion => [ ]\b\b");

					v = scanf("%d", &op); buf();

					

					if (v) {

						if (op >= 1 && op <= 2) {

							if (op == 1) {

								scr();



								while (1) {

									printf(	"Tipo de usuario:\n\n"
											"[1] Administrador\n"
											"[2] Estandar\n\n"
											"Opcion => [ ]\b\b");

									v = scanf("%d", &op); buf();

					

									if (v) {

										if (op >= 1 && op <= 2) {

											switch (op) {

												case 1:

													aux.level = 1;

													aux.admin_id = rand() % (80 - 1 + 1) + 1;

													aux.id = aux.admin_id;

													break;


												case 2:

													aux.level = 2;

													break;
											}



											break;

										} else {

											puts("Error, opcion incorrecta, presione una tecla para continuar...");

											getchar();

											scr();

										}


									} else {

										puts("Error, opcion incorrecta, presione una tecla para continuar...");

										getchar();

										scr();

									}

								}



								break;


							} else if (op == 2) {

								break;

							}


						} else {

							puts("Error, opcion incorrecta, presione una tecla para continuar...");

							getchar();

							scr();

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();

					}

				}

			}



			scr();



			/*CONFIRMAR EDICION DE USUSARIO*/

			while (1) {

				printf(	"Esta seguro que desea modificar el usuario:\n\n"
						"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();



				if (v) {

					if (op >= 1 && op <= 2) {

						if (op == 1) {

							fseek(filep, ftell(filep) - sizeof(USER), SEEK_SET);



							if ( fwrite(&aux, sizeof(USER), 1, filep) ) {

								scr();

								puts("Espere...\n");

								wait(1);

								puts("Usuario editado correctamente");

								wait(0.5);

								scr();


							} else {

								puts("Error, no se pudo editar el usuario");

								getchar();

								scr();

							}



							break;


						} else if (op == 2) {

							scr();

							puts("Edicion cancelada");

							wait(1);

							scr();

							break;

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();


					}


				} else {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			}



			if (aux_level == 1) {	//<-- SOLO SE EJECUTA SI EL USUARIO ES ADMINISTRADOR

				while (1) {

					printf(	"Desea editar otro usuario?\n\n"
							"[1] Si\n"
							"[2] No\n\n"
							"Opcion => [ ]\b\b");

					v = scanf("%d", &op); buf();



					if (v) {

						if ( op >= 1 && op <= 2) {

							break;


						} else {

							puts("Error, opcion incorrecta, presione una tecla para continuar...");

							getchar();

							scr();

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();

					}

				}


			} else {

				op = 2;

			}



			if (op == 1) {

				scr();


			} else if (op == 2) {

				break;

			}


		} else {

			scr();

			puts("El usuario no existe o no puede ser editado");

			getchar();

			break;

		}

	}


	fclose(filep);

}



//==============================
/*EDICION DE USUSARIO ESTANDAR*/
//==============================

void f_standar_edit(int ID, char *aux_username) {

	FILE *filep;
	USER aux;
	int exist, op, v;



	filep = fopen("users.bin", "rb+");

	srand(time(NULL));

	scr();



	while (1) {

		fseek(filep, 0, SEEK_SET);	/*<-- MUEVE EL CURSOR HACIA EL PRINCIPIO DEL ARCHIVO*/

		exist = 0;

		

		/*BUSCA EN EL ARCHIVO, PARA VER SI EXISTE EL USUARIO QUE HA INGREASADO*/

		while ( fread( &aux, sizeof(USER), 1, filep ) && !feof(filep) ) {

			if ( strcmp(aux_username, aux.username) == 0 ) {

				exist = 1;

				break;

			}

		}



		/*SI EL USUARIO INGRESADO EXISTE*/

		if (exist) {

			scr();

			puts("DATOS DEL USUARIO\n");

			printf("Nombre: %s\n", aux.username);

			printf("Contraseña: %s\n", aux.password);

			printf("Tipo de usuario: ");

			

			switch (aux.level) {

				case 1:

					puts("Administrador\n");

					break;


				case 2:

					puts("Estandar\n");

					break;

			}



			puts("Elija los datos a modificar:\n");



			/*EDITAR EL NOMBRE DE USUARIO*/

			printf("Nombre actual: %s\n\n", aux.username);

			

			while (1) {

				printf(	"Desea modificar el nombre?\n\n"
						"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();

				

				if (v) {

					if (op >= 1 && op <= 2) {

						if (op == 1) {

							scr();

							printf("Ingrese nombre nuevo: ");

							gets(aux.username);

							break;


						} else if (op == 2) {

							break;

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();


					}


				} else {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			}



			scr();



			/*EDITAR CONTRASEÑA*/

			printf("Contraseña actual: %s\n\n", aux.password);

			

			while (1) {

				printf(	"Desea modificar la contraseña?\n\n"
						"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();

				

				if (v) {

					if (op >= 1 && op <= 2) {

						if (op == 1) {

							scr();

							printf("Ingrese contraseña nueva: ");

							gets(aux.password);

							break;


						} else if (op == 2) {

							break;

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();


					}	


				} else {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			}



			scr();



			/*CONFIRMAR EDICION DE USUSARIO*/

			while (1) {

				printf(	"Esta seguro que desea modificar el usuario:\n\n"
						"[1] Si\n"
						"[2] No\n\n"
						"Opcion => [ ]\b\b");

				v = scanf("%d", &op); buf();



				if (v) {

					if (op >= 1 && op <= 2) {

						if (op == 1) {

							fseek(filep, ftell(filep) - sizeof(USER), SEEK_SET);



							if ( fwrite(&aux, sizeof(USER), 1, filep) ) {

								scr();

								puts("Espere...\n");

								wait(1);

								puts("Usuario editado correctamente");

								wait(0.5);

								scr();


							} else {

								puts("Error, no se pudo editar el usuario");

								getchar();

								scr();

							}



							break;


						} else if (op == 2) {

							scr();

							puts("Edicion cancelada");

							wait(1);

							scr();

							break;

						}


					} else {

						puts("Error, opcion incorrecta, presione una tecla para continuar...");

						getchar();

						scr();


					}


				} else {

					puts("Error, opcion incorrecta, presione una tecla para continuar...");

					getchar();

					scr();

				}

			}



			break;


		} else {

			puts("El usuario no existe");
		}

	}


	fclose(filep);

}



#endif