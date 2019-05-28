#ifndef TASK_H
#define TASK_H



#include <stdio.h>
#include <stdlib.h>
#include "misc.h"



typedef struct TASK {
	
	DT start, end;
	int del,status;
	char ref[10], p_id[10];
	char louder[25], infor[25];
	
} TASK;


typedef struct LIST {

	TASK task;
	struct LIST *next;

} LIST;

LIST *head = NULL, *tail = NULL;


typedef struct PROJECT {

	DT start, end;
	char title[20], id[10];
	int del, status;	

} PROJECT;



void f_verify_id_project();
int f_cnt_task();

void f_menu_task(PROJECT project);
void f_load_task(PROJECT project);
void f_save_task(PROJECT project);
void f_show_all_task(PROJECT project);
void f_del_task(PROJECT project);
void f_change_status_task(PROJECT project);
void f_show_task(PROJECT project);
void f_print_report_task(PROJECT project);
void f_sort_task(PROJECT project);
void f_end_task(PROJECT project);
void f_abso_del_task(PROJECT project);
void f_menu_add_task(PROJECT project);
void f_add_task(PROJECT project);
void f_add_last_task(PROJECT project);



/*int main(){
	
}*/



/*
	---------------------------------------------------------------------
	|*VERIFICA SI UN PROYECTO EXISTE, SI ES ASI, ABRE EL MENU DE TAREAS*
	--------------------------------------------------------------------
*/



void f_verify_id_project() {
	
	FILE *file = fopen("project.bin", "rb");


	
	if (file != NULL) {
		
		PROJECT aux;
		char id[10];
		int band = 0;
		


		//f_show_project();	
		
		wait(1);

		printf("\n\nIngrese el codigo del proyecto: ");

		gets(id);

		scr();

		fseek(file, 0, SEEK_SET);


		
		while( !feof(file) && fread(&aux, sizeof(PROJECT), 1, file) ) {
						
			if ( (compare(aux.id, id) ) == 0 || strcmp(id, aux.id) == 0 ) {

				band = 1;

				break;

			}



			puts("Verificando...");

			wait(0.2);

			scr();

		}


		
		fclose(file);


		
		if(band == 1){
		
			f_menu_task(aux);

			
		} else {

			printf("No hay proyecto guardado con el codigo %s\n",id);

			wait(1);

			scr();

		}


	} else {
	
		puts("\nNo hay informacion guardada.");	
		
	}
	
}



/*
	----------------------------------------------------------------------
	|*MENU DE ADMINISTRACION DE TAREAS*
	----------------------------------------------------------------------
*/

void f_menu_task(PROJECT project) {

	int op;
	


	f_load_task(project);


	
	do {
		
		printf(	"=================================\n"
				"= MENU ADMINISTRACION DE TAREAS =\n"
				"=================================\n\n");
		
		printf("Proyecto: %s.\n\n",project.title);
			
		printf(	"[0] Menu anterior\n"
				"[1] Crear Tareas\n"
				"[2] Eliminar Tareas\n"
				"[3] Finalizar Tareas\n"
				"[4] Mostrar Tareas\n"
				"[5] Reporte\n"
				"[6] Ordenar tareas\n"
				"[7] Fecha Fin tareas\n"
				"[8] Vaciar papelera\n\n"
				"Opcion => [ ]\b\b");

		scanf("%i", &op);

		buf();
		
		scr();



		switch (op) {
			
			case 0:
				
				f_save_task(project);

				wait(1);
								
				break;

			
			case 1234:
				
				f_show_all_task(project);

				getchar();
				
				break;

		
			case 1:

				f_menu_add_task(project);

				break;

			
			case 2:
				
				f_del_task(project);

				break;

			
			case 3:
				
				f_change_status_task(project);
				
				break;

				
			case 4:
			
				f_show_task(project);
				
				break;
			
			
			case 5:
				
				f_print_report_task(project);
				
				break;

				
			case 6:
				
				f_sort_task(project);
				
				break;

				
			case 7:
			
				f_end_task(project);
				
				break;

			
			case 8:
				
				f_abso_del_task(project);
				
				break;
				
			
			default:
				
				puts("Opcion Incorrecta");
			
		}
		
	} while (op != 0);
	
}


/*
	----------------------------------------------------------------------
	|*MENU DE ADMINISTRACION DE TAREAS*
	----------------------------------------------------------------------
*/


void f_load_task(PROJECT project) {
	
	char name_file[10];
	sprintf(name_file, "%s.bin", project.id);
	FILE *file = fopen(name_file, "ab");
	


	if (file == NULL) {

		puts("Error");

		
	} else {
		
		LIST *aux;
		TASK task;


		
		fseek(file, 0, SEEK_SET);


		
		while( !feof(file) && fread(&task, sizeof(TASK), 1, file) ) {
			
			aux = (LIST *) malloc (sizeof(LIST));
			


			if (aux == NULL) {
				
				puts("Fatal Error");
				

			} else {
				
				aux -> task = task;
			
				aux -> next = NULL;
				


				if (head == NULL) {
					
					head = aux;
					
					tail = aux;
					

				} else {
					
					tail -> next = aux;
					
					tail = aux;
					
				}
				
			}



			puts("Cargando tareas");

			wait(0.2);

			puts("Espere...");

			wait(0.2);

			scr();

		}


		
		//puts("Tareas cargadas!");

		wait(1);

		scr();

	}


		
	fclose(file);
}

/*
	----------------------------------------------------------------------
	|*GUARDA LA LISTA EN UN ARCHIVO .BIN*
	----------------------------------------------------------------------
*/

void f_save_task(PROJECT project) {
	
	FILE *file;
	LIST *aux;



	scr();
	


	if(head == NULL) {
		
		puts("No hay tareas para guardar");
		

	} else {
		
		char name_file[15];
		sprintf(name_file, "%s.bin", project.id);
		file = fopen(name_file, "wb");


		
		aux = head;
		


		while ( aux != NULL && fwrite(&aux -> task, sizeof(TASK), 1, file) ) {

			aux = aux -> next;

		}
		


		while(head != NULL) {
			
			free(head);
			
			head = head -> next;

		}



		puts("Guardando tareas.");

		wait(0.5);

		puts("Espere...\n");

		wait(1);

		puts("Tareas guardadas.");

		wait(1);
		
	}

	
	fclose(file);

}

/*
	----------------------------------------------------------------------
	|*MUESTRA TODOS LAS TAREAS DE UN PROYECTO, MODO DEBUG*
	----------------------------------------------------------------------
*/

void f_show_all_task(PROJECT project) {
	
	LIST *aux;



	scr();


	
	if (head != NULL) {
		
		aux = head;
		
		printf("%9s\t%6s\t%3s\t%10s\t%10s\t%10s\n", "Nombre", "Estatus", "Del", "Inicio", "Fin", "Proyecto");

		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");



		while (aux != NULL){
			
			printf("%9s\t", aux -> task.ref);

			printf("%6i\t", aux -> task.status);

			printf("%3i\t", aux -> task.del);

			printf("%2i-%2i-%4i\t", aux -> task.start.day, aux -> task.start.month, aux -> task.start.year);

			printf("%2i-%2i-%4i\t", aux -> task.end.day, aux -> task.end.month, aux -> task.end.year);

			printf("%10s\n",aux -> task.p_id);
					
			aux = aux -> next;		

		}
		
	}
	
}

/*
	----------------------------------------------------------------------
	|*MENU DE ADMINISTRACION DE TAREAS*
	----------------------------------------------------------------------
*/

/*void f_menu_task(PROJECT project) {

	f_load_task(project);
	int op;


	
	do {
		
		printf(	"=================================\n"
				"= MENU ADMINISTRACION DE TAREAS =\n"
				"=================================\n\n");
		
		printf("Proyecto: %s.\n\n", project.title);
			
		printf(	"[0] Menu anterior\n"
				"[1] Crear Tareas\n"
				"[2] Eliminar Tareas\n"
				"[3] Finalizar Tareas\n"
				"[4] Mostrar Tareas\n"
				"[5] Reporte\n"
				"[6] Ordenar tareas\n"
				"[7] Fecha Fin tareas\n"
				"[8] Vaciar papelera\n\n"
				"Opcion => [ ]\b\b");

		scanf("%i",&op);

		buf();
		
		scr();



		switch(op){
			
			case 0:
				
				f_save_task(project);
								
				break;

			
			case 1234:
				
				f_show_all_task(project);
				
				break;

		
			case 1:
					
				f_menu_add_task(project);
							
				break;

			
			case 2:
				
				f_del_task(project);
				
				break;

			
			case 3:
				
				f_change_status_task(project);
				
				break;

				
			case 4:
			
				f_show_task(project);
				
				break;

			
			case 5:
				
				f_print_report_task(project);
				
				break;

				
			case 6:
				
				f_sort_task(project);
				
				break;

				
			case 7:
			
				f_end_task(project);
				
				break;

			
			case 8:
				
				f_abso_del_task(project);
				
				break;
				
			
			default:
				
				puts("Opcion erronea.");
			
		}
		
	} while (op != 0);
	
}*/

/*
	----------------------------------------------------------
	|*"ELIMINA TEMPORALMENTE UNA TAREA"*
	----------------------------------------------------------------------
*/

void f_del_task(PROJECT project) {
	
	LIST *aux;



	scr();
	


	if (head == NULL) {
		
		puts("No hay tareas en la lista");

		getchar();
	

	} else {
		
		aux = head;
		
		int band = 0;

		char name[10], op;
		


		puts("Eliminar tarea.\n");

		printf("Ingrese el nombre de la tarea: ");

		gets(name);

		puts("\nEspere...");

		wait(1);

		scr();

		

		while ( aux != NULL && band == 0 ) {
			
			if ( compare(name, aux -> task.ref) == 0 || strcmp(name, aux -> task.ref) == 0 ) {
				
				puts("Tarea Encontrada");

				wait(0.75);

				band = 1;

				scr();

				break;


			} else {
				
				aux = aux -> next;
			
			}
			
		}


		
		if (band) {
		
			printf("\nEsta seguro de eliminar la tarea %s? (s/n)\n", aux -> task.ref);
		
			printf("\nOpcion => [ ]\b\b");

			scanf("%c", &op);

			buf();


			
 			switch ( toupper(op) ) {
			
				case 'S':
					
					aux -> task.del = 1;
					
					puts("\nEliminando\n");

					wait(0.5);

					puts("Espere...\n");

					wait(1.5);

					puts("Tarea Eliminada");

					wait(1);

					scr();

					break;

				
				case 'N':
					
					puts("Tarea no eliminada");				

					wait(0.75);

					scr();
					
					break;				
					
			}

			
		} else {
			
			puts("La tarea no se encuentra registrada");

			wait(0.75);

			scr();
			
		}

	}
	
}
/*
	----------------------------------------------------------------------
	|*CAMBIA STATUS DE UNA O MAS TAREAS* OJO!!NO CAMBIA EL STATUS DEL PROYECTO
	----------------------------------------------------------------------
*/

void f_change_status_task(PROJECT project) {
	
	LIST *aux, *aux2;



	scr();
	


	if (head == NULL) {
		
		puts("No hay tareas agregadas");

		getchar();
		

	} else {
	
		char name_task[10];
		int band = 0, v = 0, all = 0, pro = 0;



		aux = head;

		aux2 = head;
		
		printf("Ingrese el nombre de la tarea: ");

		gets(name_task);
		


		while ( aux != NULL && v == 0 ) {
		
		
			if ( compare(name_task, aux -> task.ref) == 0 || strcmp(name_task, aux -> task.ref) ) {
				
				v = 1;
				

			} else {
			
				aux = aux -> next;
			
			}
			
		}		


		
		if (v == 1) {
			
			if (aux -> task.end.day != 0) {
				
				while ( aux2 != NULL && band == 0 ) {	
					
					aux2 -> task.status = 1;
					


					if ( compare(name_task, aux2 -> task.ref) == 0 || strcmp(name_task, aux2 -> task.ref) == 0 ) {
						
						band = 1;
						
						

						if (aux2 -> next == NULL) {

							all = 1;

						}
						

					} else {
						
						aux2 = aux2 -> next;
						
					}
					
				}



				scr();

				puts("Se ha terminado la tarea, y tareas anteriores");

				wait(1);

				scr();



				if (all == 1) {
					
					//SIGNIFICA QUE TODAS LAS TAREAS HAN SIDO TERMINADAS, POR LO TANTO TAMBIEN EL PROYECTO
					//f_change_status_project(project.id);			

				}
				

			} else {
				
				puts("La tarea no pueden cambiar de status si no tienen fecha final");

				wait(1);

				scr();

			}


		} else {
			
			printf("La tarea %s no se encuentra en la base de datos", name_task);

			wait(1);
			
		}


		
		scr();

	}
	
}

/*
	----------------------------------------------------------------------
	|*MUESTRA EN PANTALLA LAS TAREAS DE UN PROYECTO*
	----------------------------------------------------------------------
*/


void f_show_task(PROJECT project) {
	
	LIST *aux;
	


	if (head == NULL) {
		
		puts("No hay tareas disponible.");
		

	} else {
		
		aux = head;
		
		printf("%15s\t%15s\t%10s\t%10s\t%10s\n", "Nombre", "Estatus", "Inicio", "Fin", "Proyecto");

		puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		


		while (aux != NULL) {
		
			if (aux -> task.del == 0) {
					
				if (aux -> task.status == 0) {
					
					if ( aux -> task.end.day != 0 && aux -> task.end.month != 0 ) {
						
						printf("%15s\t", aux -> task.ref);

						printf("%15s\t", "En ejecucion");

						printf("%3s%i-%i-%i\t", " ", aux -> task.start.day, aux -> task.start.month, aux -> task.start.year);
						printf("%i-%i-%i\t", aux -> task.end.day, aux -> task.end.month, aux -> task.end.year);
						printf("%10s", aux -> task.p_id);


					} else {
						
						printf("%15s\t", aux -> task.ref);

						printf("%15s\t", "En ejecucion");

						printf("%3s%i-%i-%i\t", " ", aux -> task.start.day, aux -> task.start.month, aux -> task.start.year);

						printf("%10s\t", "-------");

						printf("%10s", aux -> task.p_id);

					}
				

				} else {	
					
					printf("%15s\t", aux -> task.ref);

					printf("%15s\t", "Terminado");

					printf("%3s%i-%i-%i\t", " ", aux -> task.start.day, aux -> task.start.month, aux -> task.start.year);

					printf("%i-%i-%i\t", aux -> task.end.day, aux -> task.end.month, aux -> task.end.year);

					printf("%10s", aux -> task.p_id);
				
				}
					
			}



			wait(0.3);

			puts("");	
			
			aux = aux -> next;

		}



		puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	}
	
}


/*
	----------------------------------------------------------------------
	|*IMPRIME EN UN ARCHIVO.TXT UN REPORTE DE UN PROYECTO*
	----------------------------------------------------------------------
*/

void f_print_report_task(PROJECT project) {
	
	f_sort_task(project);
	char report_name[15];
	sprintf(report_name,"%s.txt",project.id);
	FILE *file = fopen(report_name, "w");
	LIST *aux;
	


	if (head == NULL) {

		printf("No hay Tareas en el proyecto %s\n",project.title);


	} else {
		
		scr();

		puts("Reporte.");

		wait(1);

		scr();
		
		aux=head;
		 
		fprintf(file,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"- Proyecto   %s                             -\n",project.title);
		fprintf(file,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fprintf(file,"|%10s\t%10s\t%8s\t%8s  |\n","Nombre","Estatus","Inicio","Fin");
		fprintf(file,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");



		while (aux != NULL) {
			
			if (aux -> task.status == 1) {
				
				fprintf(file, "|%10s\t%10s\t%2i-%2i-%4i\t%2i-%2i-%4i|\n", aux->task.ref, "Terminado", aux -> task.start.day, aux -> task.start.month, aux -> task.start.year, aux -> task.end.day, aux -> task.end.month, aux -> task.end.year);
				

			} else {
				
				fprintf(file,"|%10s\t%10s\t%2i-%2i-%4i\t%8s|\n", aux->task.ref, "En ejecucion", aux -> task.start.day, aux -> task.start.month, aux -> task.start.year, "----------");

			}
			


			puts("Imprimiendo...");

			wait(0.3);

			scr();		

			aux = aux -> next;

		}
		
		

		fprintf(file,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

		puts("Impresion completa. Revise el archivo de texto.");

		wait(1);

		scr();

	}


	
	fclose(file);

}




/*
	----------------------------------------------------------------------
	|*REORDENA LAS TAREAS DE UNA LISTA SEGUN SU FECHA DE INICIO*
	----------------------------------------------------------------------
*/

void f_sort_task(PROJECT project) {
	
	LIST *actual, *prev, *next;
	


	if(head == NULL) {
		
		puts("No hay datos en la lista.");

		
	} else {
		
		puts("Ordenar Tarea.\n");

		wait(0.3);

		actual = head;
		
		prev = NULL;
		
		next = actual -> next;
		


		while ( next != NULL ) {
			
			if ( f_compare_dt(actual -> task.start, next -> task.start) == 1 ) {
				
				if (prev == NULL) {
					
					head = next;
				
					actual -> next = next -> next;
				
					next -> next = actual;
					

				} else {
					
					prev -> next = next;
					
					actual -> next = next -> next;
					
					next -> next = actual;
					
				}
				


				actual = head;
				
				next = actual -> next;
				
				prev = NULL;

				
			} else {
				
				prev = actual;
				
				actual = next;
				
				next = next -> next;
				
			}



			if (next == NULL) {
				
				tail = actual;
				
			}



			scr();

			puts("Se estan organizando las tareas.");

			wait(0.3);

			puts("Por favor, espere...");

			wait(0.6);

			scr();
			
		}



		puts("Se han organizado las tareas.");

		wait(1);

		scr();

	}
	
}




/*

	----------------------------------------------------------------------
	|*LE ASIGNA LA FICHA FINAL A UNA TAREA, DESDE LA FECHA INICIAL DE LA SIGUIENTE*
	----------------------------------------------------------------------
*/


void f_end_task(PROJECT project) {
	
	LIST *aux;


	
	if (head == NULL) {
		
		puts("No hay datos guardados.");
		

	} else {

		puts("Finalizar tarea.\n");

		aux = head;
		


		while(aux != NULL) {
			
			if (aux -> next != NULL) {
				
				aux -> task.end = aux -> next -> task.start;
					
			}



			scr();

			puts("Se estan organizando las fechas.");

			wait(0.3);

			puts("Por favor espere...");	

			wait(0.3);

			scr();
			
			aux = aux -> next;

		}
		


		puts("\n\nSe han organizado las fechas de las tareas del proyecto.");

		wait(1);

		scr();

	}
	
}


/*
	----------------------------------------------------------------------
	|*ELIMINA PERMANENTEMENTE LAS TAREAS DE UNA LISTA*
	----------------------------------------------------------------------
*/

void f_abso_del_task(PROJECT project) {
	
	LIST *aux;


	
	if(head == NULL) {
		
		puts("No hay tareas en la lista.");
		

	} else {
		
		int op, i = 0;
		


		aux = head;
		


		do {

			printf(	"Desea borrar permanentemente las tareas?\n\n"
					"1.Si\n"
					"2.No\n\n"
					"Opcion => [ ]\b\b");

			scanf("%i", &op);

			buf();
			


			if ( op != 1 && op != 2 ) {
				
				puts("Opcion incorrecta.");
				
			}		
			
		} while ( op != 1 && op != 2 );


		
		if (op == 1) {
			
			if (aux -> task.del == 1) {
			
				head = aux -> next;

				free(aux);

				i++;

				scr();

				puts("Eliminando...");
				
				wait(0.2);
				
				scr();

			}


			
			while (aux -> next != NULL) {
				
				if(aux -> next -> task.del == 1) {
					
					aux -> next = aux -> next -> next;

					i++;

					free(aux -> next);

				
				} else {
					
					aux = aux -> next;
					
				}
			
			}


			
			printf("Se han eliminado %i elementos permanentemente.",i);

			wait(1);

			scr();


		} else {
			
			puts("No se ha vaciado la papelera.");

			wait(1);

			scr();

		}

	}
		
}



void f_menu_add_task(PROJECT project) {
	
	int op;



	scr();
	


	do{

		printf(	"Nueva Tarea.\n\n"
				"[1] Nueva tarea\n"
				"[2] Ultima tarea\n\n"
				"Opcion => [ ]\b\b");

		scanf("%i", &op);

		buf();


		
		switch(op){
			
			case 1:
				
				f_add_task(project);
				
				break;

				
			case 2:
				
				f_add_last_task(project);
			
				break;

			
			default:
				
				puts("Opcion incorrecta");

				wait(0.3);

				scr();

		}
		
		
	} while ( op < 1 && op > 2);
	


	scr();

}



void f_add_task(PROJECT project) {
	
	LIST *task, *aux;
	


	task = (LIST *) malloc (sizeof(LIST));

	scr();


	
	if (task == NULL) {
		
		puts("No hay memoria disponible");

		getchar();
		

	} else {
		
		if (f_cnt_task() == 1) {
		
			FILE *file;
			char name_file[15];
			char rep;
			int band = 0, band2 = 0, band3 = 1;
		
			

			aux = head;
			
			sprintf(name_file,"%s.bin", project.id);
			
			file = fopen(name_file, "ab");
			
			if (file == NULL) {
				
				puts("Error al abrir el archivo");
				

			} else {
				
				do {

					wait(0.3);

					scr();

					puts("Nueva Tarea\n");

					printf("Nombre: ");

					gets(task -> task.ref);

					puts("");
					


					do {

						band = 0;
						
						puts("Fecha de inicio (dd/mm/aaaa): \n");
						
						printf("Dia: ");

						scanf("%i", &task -> task.start.day);

						buf();

						printf("Mes: ");

						scanf("%i", &task -> task.start.month);

						buf();
						
						printf("Anio: ");

						scanf("%i", &task -> task.start.year);

						buf();

						
						
						if ((task -> task.start.year < 2030) && 
							(task -> task.start.year > 2000)) {
							
							if ((task->task.start.month == 2) && 
								(task -> task.start.day < 29) && 
								(task -> task.start.day > 0)) {
								
								band = 1;

								
							} else if ( (task -> task.start.month == 1) || 
										(task -> task.start.month == 3) || 
										(task -> task.start.month == 5) || 
										(task -> task.start.month == 7) || 
										(task -> task.start.month == 8) || 
										(task -> task.start.month == 10) || 
										(task -> task.start.month == 12) ) {
								
								if (task -> task.start.day < 32 && 
									task->task.start.day > 0) {
									
									band = 1;
									
								}			


							} else if ( (task -> task.start.month == 4) || 
										(task -> task.start.month == 6) || 
										(task -> task.start.month == 9) || 
										(task -> task.start.month == 11) ){
								
								if (task -> task.start.day < 31 && 
									task->task.start.day > 0) {	
									
									band=1;

								}
														
							}


						} else if ( (task -> task.start.year % 4) == 0 ) {
							
							if ((task -> task.start.month == 2) && 
								(task -> task.start.day < 30) && 
								(task -> task.start.day > 0)) {
								
								band = 1;
								

							} else if ( (task -> task.start.month == 1) || 
										(task -> task.start.month == 3) || 
										(task -> task.start.month == 5) || 
										(task -> task.start.month == 7) || 
										(task -> task.start.month == 8) || 
										(task -> task.start.month == 10) || 
										(task -> task.start.month == 12) ) {
								
								if (task -> task.start.day < 32 && 
									task -> task.start.day > 0) {
									
									band = 1;
									
								}			


							} else if ( (task -> task.start.month == 4) || 
										(task -> task.start.month == 6) || 
										(task -> task.start.month == 9) || 
										(task -> task.start.month == 11) ) {
								
								if (task -> task.start.day < 31 && 
									task -> task.start.day > 0) {	
									
									band = 1;

								}
														
							}
							
						}



						if (band == 0) {
						
							puts("Ingreso los datos de forma incorrecta\n\nFecha: (dd/mm/aaaa)");
						
						}
						
						//SE EVALUA SI LA FECHA DE INICIO DE LAS TAREAS ES MAYOR A LA DEL PROYECTO	
						if (f_compare_dt(task -> task.start, project.start) == 1 || 
							f_compare_dt(task -> task.start, project.start) == 0) {
							
							band2 = 1;
							

						} else {
							
							puts("\nRecuerde que la fecha de inicio de las tareas debe ser la misma o \nposterior de la fecha de inicio del proyecto");
							
							band = 0;
						
						}
						
						

						puts("\n");
						
						
						
						if ( band == 1 && band2 == 1 ) break;
						
					} while (1);


					
					task -> task.status = 0;
					
					task -> task.del = 0;
					
					task -> task.end.day = 0;
					task -> task.end.month = 0;
					task -> task.end.year = 0;
					
					strcpy(task -> task.p_id, project.id);			
					
					task -> next = NULL;
					


					if (head == NULL) {
					
						head = task;
					
						tail = task;
					

					} else {
						
						tail -> next = task;
						
						tail = task;
						
					}


					
					puts("Espere un momento...\n");

					wait(1);						

					puts("Tarea Creada!\n\n");

					wait(1);

					scr();
					
					puts("Quiere agregar otra tarea?(s/n)");

					printf("\nOpcion => [ ]\b\b");

					scanf("%c", &rep);

					buf();
					
					rep = toupper(rep);
					


					if (rep == 'S') {
		
						
						if (f_cnt_task() == 0) {
							
							puts("Error.");
			
							puts("El proyecto no puede contener mas de 20 tareas");
							
							wait(1);

							scr();

							rep = 'N';


						} else {
							
							task = (LIST *) malloc (sizeof(LIST));
							
						}
						
					}
				
				} while (rep != 'N');
				


				wait(0.2);

				scr();
				
			}
			

		} else {
			
			puts("Error");
			
			puts("El proyecto no puede contener mas de 20 tareas");
			
			wait(1);

			scr();

		}
		
	}

}



void f_add_last_task(PROJECT project) {
	
	LIST *task, *aux;
	


	task = (LIST *) malloc (sizeof(LIST));

	scr();
	


	if (head != NULL && task != NULL) {
		
		int band = 0, band3 = 0;
		


		aux = head;

		scr();

		puts("Ultima Tarea\n");
		
		printf("Nombre: ");

		gets(task -> task.ref);


		
		do {
			
			puts("Fecha de Inicio (dd/mm/aaaa): ");
			
			printf("Dia: ");

			scanf("%i", &task -> task.start.day);

			buf();
			
			printf("Mes: ");

			scanf("%i", &task -> task.start.month);

			buf();
			
			printf("Anio: ");

			scanf("%i", &task -> task.start.year);

			buf();
				
			band = 0;


				
			if ((task -> task.start.year < 2030) && 
				(task -> task.start.year > 2000)) {
				
				if ((task -> task.start.month == 2) && 
					(task -> task.start.day < 29) && 
					(task -> task.start.day > 0)) {
					
					band = 1;

					
				} else if ( (task -> task.start.month == 1) || 
							(task -> task.start.month == 3) || 
							(task -> task.start.month == 5) || 
							(task -> task.start.month == 7) || 
							(task -> task.start.month == 8) || 
							(task -> task.start.month == 10) || 
							(task -> task.start.month == 12) ) {
					
					if (task -> task.start.day < 32 && 
						task -> task.start.day > 0) {
						
						band = 1;
						
					}			


				} else if ( (task -> task.start.month == 4) || 
							(task -> task.start.month == 6) || 
							(task -> task.start.month == 9) ||
							(task -> task.start.month==11) ) {
					
					if (task -> task.start.day < 31 && 
						task -> task.start.day>  0) {	
						
						band = 1;

					}
											
				}


			} else if ( (task -> task.start.year % 4) == 0 ) {
				
				if ((task -> task.start.month == 2) && 
					(task -> task.start.day < 30) &&
					(task -> task.start.day > 0)) {
					
					band = 1;

					
				} else if ( (task -> task.start.month == 1) ||
							(task -> task.start.month == 3) ||
							(task -> task.start.month == 5) ||
							(task -> task.start.month == 7) ||
							(task -> task.start.month == 8) ||
							(task -> task.start.month == 10) ||
							(task -> task.start.month == 12) ) {
					
					if (task -> task.start.day < 32 && 
						task -> task.start.day > 0) {
						
						band = 1;
						
					}


				} else if ( (task -> task.start.month == 4) ||
							(task -> task.start.month == 6) ||
							(task -> task.start.month == 9) ||
							(task -> task.start.month == 11) ) {
					
					if (task -> task.start.day < 31 && 
						task -> task.start.day > 0) {	
						
						band = 1;

					}
											
				}
				
			}



			if (band == 0) {
			
				puts("Ingreso los datos de forma incorrecta\n\nFecha: (dd/mm/aaaa)");
			
			}
			

		
			//SI TIENE AL MENOS UN ELEMENTO GUARDADO
			if (aux != NULL) {
				
				while (aux != NULL && band3 == 0) {
					
					if (aux -> next == NULL) {
					
						band3 = 1;
					
					} else {
						
						aux = aux -> next;
					
					}
					
				}


				
				band3 = 0;
				
				//EVALUA SI LA FECHA DE INICIO DEL NUEVO ES MAYOR QUE LA ANTERIOR
				//EN CASO DE SER VERDADERO VALIDA A BAND3 Y LE ASIGNA LA FECHA DE FIN 
				
				if ( f_compare_dt(task -> task.start, aux->task.start) ) {
					
					band3 = 1;
				
				} else {
					
					puts("La tarea debe tener una fecha mayor a la anterior");
					
					band3 = 0;

				}
				
			}
			
			
			
			/*puts("\n");
			
			printf("band=%i,%i", band, band3);*/
			
			if ( band == 1 && band3 == 1) break;
			
		} while (1);
		


		f_end_task(project);


		
		//Fecha de Finalizacion
		do {
			
			puts("Fecha de Finalizacion (dd/mm/aaaa): ");
			
			printf("Dia: ");

			scanf("%i", &task -> task.end.day);

			buf();
			
			printf("Mes: ");

			scanf("%i", &task -> task.end.month);

			buf();
			
			printf("Anio: ");

			scanf("%i", &task -> task.end.year);

			buf();
			
			band = 0;

			band3 = 0;


			
			if ((task -> task.end.year < 2030) &&
				(task -> task.end.year > 2000)) {
				
				if( (task -> task.end.month == 2) && 
					(task -> task.end.day < 29) &&
					(task -> task.end.day > 0) ) {
					
					band = 1;
					

				} else if ( (task -> task.end.month == 1) ||
							(task -> task.end.month == 3) ||
							(task -> task.end.month == 5) ||
							(task -> task.end.month == 7) ||
							(task -> task.end.month == 8) ||
							(task -> task.end.month == 10) ||
							(task -> task.end.month == 12) ) {
					
					if (task -> task.end.day < 32 &&
						task -> task.end.day > 0) {
						
						band = 1;
						
					}			
				} else if ( (task -> task.end.month == 4) ||
							(task -> task.end.month == 6) ||
							(task -> task.end.month == 9) ||
							(task -> task.end.month == 11) ) {
					
					if (task -> task.end.day < 31 && 
						task -> task.end.day > 0) {	
						
						band = 1;

					}
											
				}


			} else if ( (task -> task.end.year % 4) == 0 ) {
				
				if ((task -> task.end.month == 2) && 
					(task -> task.end.day < 30) &&
					(task -> task.end.day > 0)) {
					
					band = 1;
					

				} else if ( (task -> task.end.month == 1) ||
							(task -> task.end.month == 3) ||
							(task -> task.end.month == 5) ||
							(task -> task.end.month == 7) ||
							(task -> task.end.month == 8) ||
							(task -> task.end.month == 10) ||
							(task -> task.end.month == 12) ) {
					
					if (task -> task.end.day < 32 && 
						task -> task.end.day > 0) {
						
						band = 1;
						
					}			


				} else if ( (task -> task.end.month == 4) ||
					(task -> task.end.month == 6) ||
					(task -> task.end.month == 9) ||
					(task -> task.end.month == 11) ) {
					
					if (task -> task.end.day < 31 && 
						task -> task.end.day > 0) {	
						
						band = 1;

					}
											
				}
				
			}



			if (band == 0) {
			
				puts("Ingreso los datos de forma incorrecta.\n\nFecha: (dd/mm/aaaa)");

				wait(0.3);
				
			}
			
			
			
			while ( aux != NULL && band3 == 0 ) {
				
				if (aux -> next == NULL) {
					
					band3 = 1;


				} else {
					
					aux = aux -> next;
					
				}

			}
			


			//COMPARA SI LA ULTIMA TAREA ES MAYOR QUE LA ANTERIOR
			if ( f_compare_dt(task -> task.start, aux -> task.start) == 1 ) {
					
					band3 = 1;
					
					aux -> task.end = task -> task.start;
				

				} else {
					
					puts("La tarea debe tener una fecha mayor a la anterior");

					wait(0.3);	

					band3 = 0;

				}
			
			if ( band ==1 && band3 == 1 ) break;

		} while (1);

		
		
		task -> task.status = 0;
		
		task -> task.del = 0;
		
		strcpy(task -> task.p_id, project.id);			
		
		task -> next = NULL;
			
		tail -> next = task;
			
		tail = task;
			
		//f_end_project(project);
		
		puts("\nPor favor espere...");

		wait(0.3);

		puts("\nCreando tarea");

		wait(1);

		puts("\n\nTarea creada!");

		wait(1);

		scr();


	} else {
		
		puts("No hay tareas");
		
	}

}



int f_cnt_task() {
	
	LIST* aux;
	


	if (head != NULL) {
		
		aux = head;
		int i = 0;
		


		while (aux != NULL) {
			
			i++;

			aux = aux -> next;

		}	


		
		if (i <= 19)

			return 1;


		else 

			return 0;


	} else 

		return 1;

}





#endif