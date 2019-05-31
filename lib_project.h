#ifndef PROJECT_H
#define PROJECT_H



#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "misc.h"
#include "lib_task.h"

#define namefile "database.bin"





void f_menu_project();
void f_create_project();
void f_modi_project();
void f_show_project();
void f_del_project();
void f_abso_del_project();
void f_verify_project_id();
void f_find_project();

void f_printf_gantt();
int f_count_day(DT start,DT end);

/*
int main(){
	
	f_menu_project();
	
	return 0;
}


/*
	----------------------------------------------------------------------
	|*MENU DE ADMINISTRACION DE PROYECTO*
	----------------------------------------------------------------------
*/


void f_menu_project(){

	int op;
	
	do{
		scr();
			
		printf(	"====================================\n"
				"= MENU ADMINISTRACION DE PROYECTOS =\n"
				"====================================\n\n");
	
		puts("[0] Salir.");
		puts("[1] Crear Proyecto.");
		puts("[2] Modificar Proyecto.");
		puts("[3] Ver Proyectos.");
		puts("[4] Borrar Proyectos.");
		puts("[5] Vaciar Papelera.");
		puts("[6] Administrar Tareas.");
		puts("[7] Diagrama de Gantt.");
		
		printf("\n Opcion => [ ]\b\b");
		scanf("%i",&op);
		
		buf();
		scr();
		
		switch(op){
			
			case 0:
				
				
				
				break;
				
			case 1:
				
			
				f_create_project();
								
				break;
			
			case 2:
				
				
				f_modi_project();
				
				break;
				
			case 3:
				
				
				f_show_project();

				getchar();
				
				break;
				
			case 4:
				
				f_del_project();
				
				break;
				
			case 5:
				
				f_abso_del_project();
				
				break;
				
				
			case 6:
				
				
							
				f_verify_project_id();
				
				break;
			
			case 7:
				
				f_printf_gantt();
	//			f_printf_gantt();
				
				break;
					
			default:
				
				puts("Opcion incorrecta, vuelva a intentar");
				wait(1);
		}
	
		scr();
		
	}while(op!=0);

}


/*
	----------------------------------------------------------------------
	|*CREA UN PROYECTO Y LO GUARDA EN UN ARCHIVO .BIN*
	----------------------------------------------------------------------
*/

void f_create_project(){
	
	FILE *file=fopen(namefile,"ab");
	
	if(file!=NULL){
		
		PROJECT project;
		int band=0,band2=0;
		
		puts("Crear proyecto.\n");
	
		printf("Titulo: ");
		gets(project.title);
		
		
		//VALIDADOR DE FECHA INICIO
		do{
			scr();
			
			puts("Fecha de inicio (dd/mm/aaaa): ");
			
			printf("Dia: ");
			scanf("%i",&project.start.day);
			//fflush(stdin);
			buf();
			printf("Mes: ");
			scanf("%i",&project.start.month);
			//fflush(stdin);
			buf();
			printf("Anio: ");
			scanf("%i",&project.start.year);			
			//fflush(stdin);
			buf();
			
			if((project.start.year<2030)&&(project.start.year>2000)){
			
				if((project.start.month==2) && (project.start.day<29)&&(project.start.day>0)){
					
					band=1;
					
				}
				else if((project.start.month==1)||(project.start.month==3)||(project.start.month==5)||(project.start.month==7)||(project.start.month==8)||(project.start.month==10)||(project.start.month==12)){
				
					if(project.start.day<32 && project.start.day>0){
						
						band=1;
						
					}			
				}
				else if((project.start.month==4)||(project.start.month==6)||(project.start.month==9)||(project.start.month==11)){
						
					if(project.start.day<31 && project.start.day>0){
						
						band=1;
						
					}
											
				}
			}
			else if((project.start.year%4)==0){
				
				if((project.start.month==2) && (project.start.day<30)&&(project.start.day>0)){
					
					band=1;
					
				}
				else if((project.start.month==1)||(project.start.month==3)||(project.start.month==5)||(project.start.month==7)||(project.start.month==8)||(project.start.month==10)||(project.start.month==12)){
				
					if(project.start.day<32 && project.start.day>0){
						
						band=1;
						
					}			
				}
				else if((project.start.month==4)||(project.start.month==6)||(project.start.month==9)||(project.start.month==11)){
						
					if(project.start.day<31 && project.start.day>0){
						
						band=1;
						
					}
											
				}
			}
			else{
			
				puts("Ingreso los datos de forma incorrecta.\n\nFecha: (dd/mm/aaaa)");
				wait(1);
				scr();			
			}
			
					
		}while(band!=1);
		
		
		do{
			scr();
			
			puts("Fecha Final.\n");
				
			printf("Dia: ");
			scanf("%i",&project.end.day);
			buf();
			
			printf("Mes: ");
			scanf("%i",&project.end.month);
			buf();
			
			printf("Anio: ");
			scanf("%i",&project.end.year);
			buf();
			
			band=0;
			band2=0;
			
			if((project.end.year<2030)&&(project.end.year>2000)){
			
				if((project.end.month==2) && (project.end.day<29)&&(project.end.day>0)){
					
					band=1;
					
				}
				else if((project.end.month==1)||(project.end.month==3)||(project.end.month==5)||(project.end.month==7)||(project.end.month==8)||(project.end.month==10)||(project.end.month==12)){
				
					if(project.end.day<32 && project.end.day>0){
						
						band=1;
						
					}			
				}
				else if((project.end.month==4)||(project.end.month==6)||(project.end.month==9)||(project.end.month==11)){
						
					if(project.end.day<31 && project.end.day>0){
						
						band=1;
						
					}
											
				}
			}
			else if((project.end.year%4)==0){
				
				if((project.end.month==2) && (project.end.day<30)&&(project.end.day>0)){
					
					band=1;
					
				}
				else if((project.end.month==1)||(project.end.month==3)||(project.end.month==5)||(project.end.month==7)||(project.end.month==8)||(project.end.month==10)||(project.end.month==12)){
				
					if(project.end.day<32 && project.end.day>0){
						
						band=1;
						
					}			
				}
				else if((project.end.month==4)||(project.end.month==6)||(project.end.month==9)||(project.end.month==11)){
						
					if(project.end.day<31 && project.end.day>0){
						
						band=1;
						
					}
											
				}
				
			}
			else{
			
				puts("Ingreso los datos de forma incorrecta.\n\nFecha: (dd/mm/aaaa)");
				wait(1);
							
			}
			
			if(f_compare_dt(project.end,project.start)==1){
				band2=1;
			}
			else{
				
				puts("La fecha de finalizacion debe ser mayor a la inicial.");
				wait(1);
				
			}
			
			if(band==1&&band2==1)
				break;
		}while(1);	
		
		scr();
		
		printf("El proyecto %s tiene planificado que empieze el %i-%i-%i \ny termine el %i-%i-%i.\n",
				project.title,project.start.day,project.start.month,project.start.year,
				project.end.day,project.end.month,project.end.year);
		wait(2);
		scr();		
		
		puts("Descripcion: \n");
		printf("Ingrese una breve descripcion del proyecto: ");
		gets(project.infor);
		
		scr();
		
		puts("Responsable. \n");
		printf("Ingrese el nombre del responsable: ");
		gets(project.louder);
		
		
		scr();
		
		puts("Ubicacion.\n");
		printf("Ubicacion del proyecto: ");
		gets(project.location);
		
		//ID DEL PROYECTO{
		
		int i,j;
		char aux[10];
		
		for(i=0,j=0;i<5;j++){
			if(isalnum(project.title[j])){
				aux[i]=toupper(project.title[j]);
				i++;
			}
		}
		aux[5]='\0';
		
		
		sprintf(project.id,"%s%i%i",aux,project.start.month,project.start.day);
		// }
		
		printf("Codigo del Proyecto: %s\n",project.id);
		wait(1);
		
		project.status=0;
		project.del=0;
		
		fwrite(&project,sizeof(PROJECT),1,file);
		
		puts("Creando proyecto...\n");	
		wait(0.5);	
		puts("Proyecto Creado");
		wait(2);
		scr();
	}
	else{
		
		puts("Error al crear el archivo");
		
	}
	
	
	fclose(file);
}



/*
	----------------------------------------------------------------------
	|*MODIFICA EL NOMBRE Y LA FECHA DE INICIO DE UN PROYECTO*
	----------------------------------------------------------------------
*/

void f_modi_project(){
	
	FILE *file=fopen(namefile,"rb+");
	char title[20];
	int band=0,band2=0,op,cancel=0;
	PROJECT project;
	
	if(file!=NULL){
		
		fseek(file,0,SEEK_SET);
		puts("Modificar proyecto.\n");
		wait(1);
		printf("Ingrese el Codigo del proyecto: ");
		gets(title);
		scr();
		
		while((!feof(file))&&fread(&project,sizeof(PROJECT),1,file)&&band==0){
			
			if(strcmp(title,project.id)==0||compare(title,project.id)==0){
			
				band=1;
				break;
			}
			puts("Buscando...");
			wait(0.2);
			scr();
		}
		
		if(band==1){
			
			puts("Proyecto encontrado!.");
			wait(1);
			
			if(project.status==0){
				
				do{
					
					printf("PROYECTO : %s.\n\n",project.title);
					puts("Dato a modificar.");
					
					puts("[1] Titulo.");
					puts("[2] Fecha de inicio.");
					puts("[3] Fecha Fin.");
					puts("[4] Encargado.");
					puts("[5] Ubicacion.");
					
					puts("[0] Salir");
					
					printf("\nOpncion => [ ]\b\b");
					scanf("%i",&op);
					//fflush(stdin);
					buf();
					
					switch(op){
						case 1:
					
							printf("\nNuevo titulo: ");
							gets(project.title);		
							scr();
							break;
							
						case 2:
							
							do{
									
								puts("Nueva fecha de inicio (dd/mm/aaaa): ");
			
								printf("Dia: ");
								scanf("%i",&project.start.day);
							//	fflush(stdin);
								buf();
									
								printf("Mes: ");
								scanf("%i",&project.start.month);
							//	fflush(stdin);
								buf();
								
								printf("Anio: ");
								scanf("%i",&project.start.year);			
								//fflush(stdin);
								buf();
								scr();
								
								if((project.start.year<2030)&&(project.start.year>2000)){
									
									if((project.start.month==2) && (project.start.day<29)&&(project.start.day>0)){
										
										band2=1;
										
									}
									else if((project.start.month==1)||(project.start.month==3)||(project.start.month==5)||(project.start.month==7)||(project.start.month==8)||(project.start.month==10)||(project.start.month==12)){
									
										if(project.start.day<32 && project.start.day>0){
											
											band2=1;
											
										}			
									}
									else if((project.start.month==4)||(project.start.month==6)||(project.start.month==9)||(project.start.month==11)){
											
											if(project.start.day<32 && project.start.day>0){
											
											band2=1;
											
										}
																
									}
								}
								else if((project.start.year%4)==0){
									
									if((project.start.month==2) && (project.start.day<30)&&(project.start.day>0)){
										
										band2=1;
										
									}
									else if((project.start.month==1)||(project.start.month==3)||(project.start.month==5)||(project.start.month==7)||(project.start.month==8)||(project.start.month==10)||(project.start.month==12)){
										if(project.start.day<32 && project.start.day>0){
											
											band2=1;
											
										}			
									}
									else if((project.start.month==4)||(project.start.month==6)||(project.start.month==9)||(project.start.month==11)){
											
											if(project.start.day<31 && project.start.day>0){
											
											band2=1;
											
										}
																
									}
									
								}
								else{
								
									puts("Ingreso los datos de forma incorrecta.\n\nFecha: (dd/mm/aaaa)");
									wait(1);
									scr();
								}
								
								puts("\n");
					
								
							}while(band2!=1);
							
							break;
							
						case 0:
							
							do{
								scr();
								
								puts("Esta seguro de que no quiere continuar con la modificacion?");
								puts("[1] Si.");
								puts("[2] No.");
								
								printf("\nOpcion => [ ]\b\b");		
								scanf("%i",&op);
								//fflush(stdin);
								buf();
								switch(op){
									case 1:
										cancel=1;
										break;
									case 2:
										cancel=0;
										break;
									default:
										puts("Opcion incorrecta...");	
								}
									
							}while(op>2&&op<0);
							
							break;
								
						case 3:
							
							do{
								
								puts("Nueva fecha Fin (dd/mm/aaaa): ");
			
								printf("Dia: ");
								scanf("%i",&project.end.day);
							//	fflush(stdin);
								buf();
									
								printf("Mes: ");
								scanf("%i",&project.end.month);
							//	fflush(stdin);
								buf();
								
								printf("Anio: ");
								scanf("%i",&project.end.year);			
								//fflush(stdin);
								buf();
								scr();
								
								if((project.end.year<2030)&&(project.end.year>2000)){
									
									if((project.end.month==2) && (project.end.day<29)&&(project.end.day>0)){
										
										band2=1;
										
									}
									else if((project.end.month==1)||(project.end.month==3)||(project.end.month==5)||(project.end.month==7)||(project.end.month==8)||(project.end.month==10)||(project.end.month==12)){
									
										if(project.end.day<32 && project.end.day>0){
											
											band2=1;
											
										}			
									}
									else if((project.end.month==4)||(project.end.month==6)||(project.end.month==9)||(project.end.month==11)){
											
											if(project.end.day<32 && project.end.day>0){
											
											band2=1;
											
										}
																
									}
								}
								else if((project.end.year%4)==0){
									
									if((project.end.month==2) && (project.end.day<30)&&(project.end.day>0)){
										
										band2=1;
										
									}
									else if((project.end.month==1)||(project.end.month==3)||(project.end.month==5)||(project.end.month==7)||(project.end.month==8)||(project.end.month==10)||(project.end.month==12)){
										if(project.end.day<32 && project.end.day>0){
											
											band2=1;
											
										}			
									}
									else if((project.end.month==4)||(project.end.month==6)||(project.end.month==9)||(project.end.month==11)){
											
											if(project.end.day<31 && project.end.day>0){
											
											band2=1;
											
										}
																
									}
									
								}
								else{ 
								
									puts("Ingreso los datos de forma incorrecta.\n\nFecha: (dd/mm/aaaa)");
									wait(1);
									scr();
								}
								
								
							
								if(f_compare_dt(project.end,project.start)==1){
									band2=1;
								}	
								else{
									band2=0;
									puts("Error\nLa fecha final debe ser mayor a la de inicio.");
									wait(1);scr();
								}
								
								if(band2==1)
									break;
							}while(1);
							
							break;
							
						case 4:
							
							printf("Ingrese el nombre del nuevo Encargado: ");
							gets(project.louder);
							wait(1);
							scr();
								
							break;
							
						case 5:
							
							printf("Ingrese la nueva ubicacion: ");
							gets(project.location);
							wait(1);
							scr();
							
							break;
							
						default:
							puts("Opcion incorrecta.");
					}
					
					if(cancel==1)
						break;
								
				}while(op<1&&op>2);
				
			}
			else{
				
				puts("El proyecto no se puede modificar debido a que ya esta terminado!.");
				wait(2);
				scr();
				
			}
	
			if(cancel==0){
				
				fseek(file,ftell(file)-sizeof(PROJECT),SEEK_SET);
				
				scr();
				puts("Modificando...");
				wait(2);
				scr();
				
				if(fwrite(&project,sizeof(PROJECT),1,file))
				
					puts("Proyecto Modificado.");
			
				}
				
			}
			else{
			
				puts("\nEl proyecto no se encuentra en la base de datos.");
				wait(1);
				scr();
			}
		
	}
	else{
		
		puts("Error al abrir el archivo");
		wait(0.5);
		scr();
	}
	
	fclose(file);	
	
	
}


/*
	----------------------------------------------------------------------
	|*MUESTRA TODOS LOS PROYECTOS GUARDADOS A EXCEPCION DE LOS ELIMINADOS TEMP*
	----------------------------------------------------------------------
*/

void f_show_project(){
	
	FILE *file=fopen(namefile,"rb");
	
	if(file!=NULL){
		
		PROJECT aux;
		

		while(!(feof(file))&&fread(&aux,sizeof(PROJECT),1,file)){
			
				if(aux.del==0){
					
					if(aux.status==0){
						
						printf("Titulo: %s.\n",aux.title);
						printf("Descripcion: %s.\n",aux.infor);
						printf("Ubicacion: %s.\n",aux.location);
						printf("Responsable: %s\n",aux.louder);
						printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
						printf("Fecha de finalizacion: %i-%i-%i.\n",aux.end.day,aux.end.month,aux.end.year);
						printf("Estatus: En ejecucion.\n");
						printf("ID: %s\n",aux.id);					
					
					}
					
					else{	
						
						printf("Titulo: %s\n",aux.title);
						printf("Descripcion: %s\n",aux.infor);
						printf("Ubicacion: %s\n",aux.location);
						printf("Responsable: %s\n",aux.louder);
						printf("Fecha de inicio: %i-%i-%i\n",aux.start.day,aux.start.month,aux.start.year);
						printf("Fecha de finalizacion: %i-%i-%i\n",aux.end.day,aux.end.month,aux.end.year);
						printf("Estatus: Terminado\n");
						printf("ID: %s\n",aux.id);	
					}
					
				}
				wait(0.5);
				puts("\n");	
		}
		
		puts("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		
		wait(3);
	}
	else{
		
		puts("No hay proyectos guardados en la base de datos.");
		wait(1);
		scr();
	}

	fclose(file);
}

/*
	----------------------------------------------------------------------
	|*"ELIMINA TEMPORALMENTE" UN PROYECTO*
	----------------------------------------------------------------------
*/

void f_del_project(){
	
	FILE *file=fopen(namefile,"rb+");
	
	if(file==NULL){
		
		puts("\nNo hay proyectos guardados.");
		
	}
	else{
		
		char id[10];
		int band=0,op,cancel=0;
		PROJECT aux;
		
		fseek(file,0,SEEK_SET);
		
		puts("Borrar proyecto\n");
		wait(0.5);
		
		printf("\nIngrese el codigo del proyecto: ");
		gets(id);
		
		scr();
		
		while(!feof(file) &&fread(&aux,sizeof(PROJECT),1,file)&&band==0){
		
			puts("Buscando...");
			wait(0.5);
			scr();
			
			if(compare(aux.id,id)==0 || strcmp(aux.id,id)==0){
				
				puts("Encontrado!");
				wait(0.5);
				scr();
				
				do{
					printf("Esta seguro de eliminar el proyecto %s?\n",aux.title);
					printf("[1] Si.\n");
					printf("[2] No.\n");
					printf("[0] Salir.\n\n");
					printf("Opcion => [ ]\b\b");
					
					scanf("%i",&op);
					//fflush(stdin);
					buf();
					scr();
					
					switch(op){
						
						case 1:
							
							fseek(file,ftell(file)-sizeof(PROJECT),SEEK_SET);
							
							aux.del=1;
							
							puts("Borrando...");
							wait(0.5);	
						
							if(fwrite(&aux,sizeof(PROJECT),1,file))
							
								puts("\nProyecto enviado a la papelera.");
							
							band=1;
							
							break;
							
						case 2:
							
							puts("\nProyecto no eliminado.");
							
							break;
							
						case 0:
							
							do{
								puts("Esta seguro que no quiere continuar con la eliminacion?");
								puts("[1] Si.");	
								puts("[2] No.");	
								
								printf("\nOpcion => [ ]\b\b");
								scanf("%i",&op);
								buf();
								scr();
								switch(op){
									case 1:
										
										cancel=1;
										break;
										
									case 2:
										
										cancel=0;
										break;
									default:
										
										puts("\nOpcion incorrecta!.\n\n");
								}
								
								
							}while(op<1&&op>2);
							
							break;
							
						default:
							
							puts("\nOpcion erronea.");
						
					}
					
					if(cancel==1)
						break;
				}while(op<1&&op>2);
				
				band=1;
				break;
			}
			
			if(band==0){
				
				puts("\nEl Proyecto no se encuentra en la base de datos.\n\n");
				wait(1);
			}
		}
		
		
	}
	
	fclose(file);

}

/*
	----------------------------------------------------------------------
	|*ELIMINA PERMANENTEMENTE LAS TAREAS DE UNA LISTA*
	----------------------------------------------------------------------
*/

void f_abso_del_project(){
	
	FILE *file,*aux;
	PROJECT temp;
	int band=0,op,del,i=0;
	char file_task[15];
	
	file=fopen(namefile,"rb+");
	aux=fopen("temp.bin","wb");
	
		
	if(file==NULL){
		
		puts("No hay datos guardados.");
		
	}
	else{
		
		fseek(file,0,SEEK_SET);
		
		do{
			printf("Esta seguro de eliminar permanentemente los datos de la papelera?\n");
			printf("\n[1] Si.\n"
				   "[2] No.\n\n");
			
			printf("Opcion => [ ]\b\b");
			
			scanf("%i",&op);
			//fflush(stdin);
			buf();
			scr();
			
			switch(op){
				
				case 1:
					
					band=1;
					
					
					break;
					
				case 2:
					
					puts("Proyecto no eliminado.");
					wait(1);
					scr();
					break;
					
				default:
					
					puts("Opcion erronea.");
					wait(1);
					scr();
			}
			
		}while(op<1&&op>2);
		
		
		if(band==1){
			
			while(!feof(file)&&fread(&temp,sizeof(PROJECT),1,file)){
				puts("Borrando...");
				wait(0.5);
				scr();
				
				if(temp.del!=1){
					
					fwrite(&temp,sizeof(PROJECT),1,aux);
					
					i++;
					
				}
				else{
					
					sprintf(file_task,"%s.bin",temp.id);
					
					remove(file_task);
					
					del=1;
			
				}
			}	
			
		}
	
		if(del==1){
			
			puts("Datos eliminados");
			wait(1);
			scr();
			
		}	
		
		
		fclose(file);
		fclose(aux);
		
		if(i>0&&op==1){
			
			
			remove(namefile);
			rename("temp.bin",namefile);	
	
			
		}
	
		else if(i==0&&op==1){
			
			remove(namefile);
			remove("tem.bin");
			
			puts("No hay datos");
			wait(1);
			scr();	
		}
			
			
	}
	
	
}

void f_verify_project_id(){
	
	FILE *file;
	PROJECT aux;
	char id[10];
	int band=0;
		
	file = fopen(namefile,"rb+");

	if(file==NULL){
		
		puts("No hay proyectos guardados en la base de datos. ");
		wait(2);
		scr();
		
	}
	else{
		
		printf("Ingrese el codigo del proyecto: ");
		gets(id);
		wait(0.5);
		scr();
		
		
		while(fread(&aux,sizeof(PROJECT),1,file) && band==0 && !feof(file)){
			
			puts("Verificando...");
			wait(0.5);
			scr();
			
			
			if(compare(id,aux.id) == 0){
				

				band=1;		
				break;
			}
			
		
		}
		
		if(band){
			
			
			

			f_menu_task(aux);
			
		}
		else{
			
			printf("El proyecto de codigo %s no existe.",id);
			wait(0.5);
			puts("El proyecto no esta guardado en la base de dato.");
			wait(2);
		}
	
	}

	fclose(file);
	
	
	
	
}


void f_find_project(){
	
	FILE *file=fopen(namefile,"rb");
	char project_f[20];
	int op,op2,band;
	PROJECT aux;
	DT dt_find;
	
	
	if(file==NULL){
		
		
	}
	else{
		
		do{
			scr();
			puts("Buscar proyecto.\n\n");
			wait(1);
			scr();
			puts("Buscar proyecto por:\n");
			
			puts("[0] Salir.");
			puts("[1] Titulo.");
			puts("[2] Codigo.");
			puts("[3] Fecha de inicio.");
			
			printf("\nOpcion => [ ]\b\b");
			scanf("%i",&op);
			buf();
			puts("\nEspere...");
			wait(2);
			scr();
			band=0;
			
			switch(op){
				//Por Titulo
				case 1:
					
					do{
						
						puts("Buscar proyecto.\n");
						printf("Ingrese el titulo del proyecto: ");
						gets(project_f);
						
						puts("Espere...");
						wait(1);
						scr();
						
						while(fread(&aux,sizeof(PROJECT),1,file)&&!feof(file)&&band==0){
							
							puts("Buscando...");
							wait(1);
							scr();
							if(strcmp(aux.title,project_f)==0||compare(aux.title,project_f)==0){
								
								band=1;
								break;
							}
							
						}
						
						if(band){
							
							puts("Proyecto encontrado!!");
							wait(1);
							scr();
							
							if(aux.status==1){
								
								printf("Proyecto: %s.\n",aux.title);
								printf("Descripcion: %s.\n",aux.infor);
								printf("Ubicacion: %s.\n",aux.location);
								printf("Encargado: %s.\n",aux.louder);
								printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
								printf("Fecha Fin: %i-%i-%i.\n",aux.end.day,aux.end.month,aux.end.year);
								printf("Estatus: Terminado.");
								
							}
							else{
							
								printf("Proyecto: %s.\n",aux.title);
								printf("Descripcion: %s.\n",aux.infor);
								printf("Ubicacion: %s.\n",aux.location);
								printf("Encargado: %s.\n",aux.louder);
								printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
								printf("Fecha fin: -------.\n");
								printf("Estatus: En ejecucion.\n");
								
							}
							getchar();
							op2=2;
						}
						else{
							
							printf("El Proyecto %s no esta guardado en la base de datos",project_f);
							puts("\nIntente de nuevo.");
							puts("Quiere intentar de nuevo?");
							puts("[1] Si.");
							puts("[2] No.\n");
							
							printf("Opcion => [ ]\b\b");
							scanf("%i",&op2);
							buf();
							
							wait(1);
							scr();
						}
						
						if(op2==2)
							break;
						else if(band==1)
							break;	
					}while(1);
					
					break;
					
				//Por Codigo
				case 2:
					
					do{
						
						puts("Buscar proyecto.\n");
						printf("Ingrese el codigo del proyecto: ");
						gets(project_f);
						
						puts("Espere...");
						wait(1);
						scr();
						
						while(fread(&aux,sizeof(PROJECT),1,file)&&!feof(file)&&band==0){
							
							puts("Buscando...");
							wait(1);
							scr();
							if(strcmp(aux.id,project_f)==0||compare(aux.id,project_f)==0){
								
								band=1;
								break;
							}
							
						}
						
						if(band){
							
							puts("Proyecto encontrado!!");
							wait(1);
							scr();
							
							if(aux.status==1){
								
								printf("Proyecto: %s.\n",aux.title);
								printf("Descripcion: %s.\n",aux.infor);
								printf("Ubicacion: %s.\n",aux.location);
								printf("Encargado: %s.\n",aux.louder);
								printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
								printf("Fecha Fin: %i-%i-%i.\n",aux.end.day,aux.end.month,aux.end.year);
								printf("Estatus: Terminado.");
								
							}
							else{
							
								printf("Proyecto: %s.\n",aux.title);
								printf("Descripcion: %s.\n",aux.infor);
								printf("Ubicacion: %s.\n",aux.location);
								printf("Encargado: %s.\n",aux.louder);
								printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
								printf("Fecha fin: -------.\n");
								printf("Estatus: En ejecucion.\n");
								
							}
							getchar();
							op2=2;
						}
						else{
							
							printf("El Proyecto %s no esta guardado en la base de datos\n",project_f);
							wait(2);
							scr();
					
							puts("Quiere intentar de nuevo?");
							puts("[1] Si.");
							puts("[2] No.\n");
							
							printf("Opcion => [ ]\b\b");
							scanf("%i",&op2);
							buf();
							
							wait(1);
							scr();
						}
						
						if(op2==2)
							break;
						else if(band==1)
							break;
					}while(1);
						
				
					break;
				
				case 3:
					
					puts("Busqueda por fecha.\n");
					
					printf("Dia: ");
					scanf("%i",&dt_find.day);
					buf();
					
					printf("Mes: ");
					scanf("%i",&dt_find.month);
					buf();
					
					printf("Anio: ");
					scanf("%i",&dt_find.year);
					buf();
					
					while(!feof(file)&&fread(&aux,sizeof(PROJECT),1,file)&&band==0){
						puts("Buscando...");
						wait(1);
						scr();
						
						if(aux.start.day==dt_find.day  && aux.start.month==dt_find.month && aux.start.year==dt_find.year){
							
							band=1;
							break;
						}
						
					}			
					
					if(band==1){
						
						puts("Proyecto encontrado!!");
						wait(1);
						scr();
						
						if(aux.status==1){
							
							printf("Proyecto: %s.\n",aux.title);
							printf("Descripcion: %s.\n",aux.infor);
							printf("Ubicacion: %s.\n",aux.location);
							printf("Encargado: %s.\n",aux.louder);
							printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
							printf("Fecha Fin: %i-%i-%i.\n",aux.end.day,aux.end.month,aux.end.year);
							printf("Estatus: Terminado.");
							
						}
						else{
						
							printf("Proyecto: %s.\n",aux.title);
							printf("Descripcion: %s.\n",aux.infor);
							printf("Ubicacion: %s.\n",aux.location);
							printf("Encargado: %s.\n",aux.louder);
							printf("Fecha de inicio: %i-%i-%i.\n",aux.start.day,aux.start.month,aux.start.year);
							printf("Fecha fin: -------.\n");
							printf("Estatus: En ejecucion.\n");
							
						}
						getchar();
						op2=2;
					}	
					else{
						
						printf("El Proyecto %s no esta guardado en la base de datos\n",project_f);
						wait(1);
						scr();
					
						do{
							puts("Quiere intentar de nuevo?");
							puts("[1] Si.");
							puts("[2] No.\n");
							
							printf("Opcion => [ ]\b\b");
							scanf("%i",&op2);
							buf();
							
							wait(1);
							scr();
							
							if(op2==1 || op2==2)
								break;							
						}while(1);
						
					}
					break;
					
				case 0:
				
					
					op2=2;
					band=1;
					
					break;
						
				default:
					
					op=0;
					puts("Opcion erronea.");
					wait(1);
					scr();
					
			}
			
			if(op2==2)
				break;
			else if(band==1) 
				break;	
		}while(1);
		
	
		
		
	}
	
	fclose(file);
}

int f_count_day(DT start,DT end){
	

	int day_year[13]={0,31,56,90,120,151,181,212,243,273,304,334,365};
	int days=0,difyear=0,i;
	
	difyear=start.year-end.year;
	
	if(difyear==0){
		
		days+=(day_year[end.month-1]+end.day)-(day_year[start.month-1]+start.day);
		
		if(start.month<=2&&end.month>2){
			if((start.year%4)==0){
				days++;
			}
		}
		
	}
	else{
	
		days+=365-(day_year[start.month-1]+start.day);
	
		if(start.month<3){
			if((start.year%4)==0){
				days++;
			}
		}	
		
		for(i=start.year+1;i<end.year;i++){
			
			days+=365;
			
			if((i%4)==0){
				days++;
			}
			
		}
		
		
		days+=day_year[end.month-1]+end.day;
		
		if(end.month>2){
			if((end.year%4)==0){
				days++;
			}
		}
		
		
	}
	
	printf("Entre %i-%i-%i y %i-%i-%i hay %i dias",start.day,start.month,start.year,end.day,end.month,
			end.year,days);
	
	wait(1);
	scr();
	
	return days;
}

/*
	FALTA AGREGARLE LAS TAREAS Y LA SEMANA EN QUE FUE REALIZADA LA TAREA*

*/

void f_printf_gantt(){
	
	FILE *file=fopen(namefile,"rb"),*filet=fopen(name_file,"rb");
	TASK task;
	PROJECT aux;
	DT condition;
	char code[10];
	int band=0,i,j,k,m,days;
	
	if(file==NULL){
		
		puts("No hay datos guardados.");
		
	}
	else{
		
		puts("Diagrama de Gantt.\n");
		
		printf("Ingrese el codigo del proyecto: ");
		gets(code);
		
		
		while(fread(&aux,sizeof(PROJECT),1,file)&&!feof(file)&&band==0){
		
			puts("Buscando...");
		
			wait(0.5);
			scr();
			if(strcmp(aux.id,code)==0||compare(aux.id,code)==0){
				
		
				wait(1);
				scr();
				band=1;
				break;
			}
			
		}


		if(band==1){
			
			scr();
			
			days=f_count_day(aux.start,aux.end);
			
			for(i=0,j=0;i<days;i+=7,j++);
			
			
			printf("~~~~~~~~~~~~~");	
			
			for(i=0;i<j;i++){
				printf("~~~~~~~~~~~");
			}
			puts("~");
			
			printf("|  %s  |",aux.id);
			
			for(i=0;i<j;i++){
				
				printf(" Semana %i |",i+1);
			
			}	
			puts("");
			printf("~~~~~~~~~~~~~");	
			
			for(i=0;i<j;i++){
				printf("~~~~~~~~~~~");
			}
			puts("");
			
			
				
			while(!feof(filet)&&fread(&task,sizeof(TASK),1,filet)){
				
				if(compare(task.p_id,aux.id)==0){
					
					
					printf("|%12s|",task.ref);
				
					for(i=0;i<j;i++){
						
						condition.day=aux.start.day+i*7;
						condition.month=aux.start.month;
						condition.year=aux.start.year;
						
											
						switch(condition.month){
				
							case 1: case 3: case 5: case 7: case 8: case 10: case 12:
							
								if(condition.month==12&&condition.day>=32){
									condition.day-=31;
									condition.month-=11;
									condition.year++;
								}
								if(condition.day>=32){
									condition.day-=31;
									condition.month++;
								}
									
								break;
								
							case 2:
							
								if(condition.year%4==0){
									if(condition.day>=30)
									condition.day-=29;
									condition.month++;
								}
								else if(condition.day>=29){
									condition.day-=28;
									condition.month++;
								}
									
								break;
								
						
							case 4: case 6: case 9: case 11:
								if(condition.day>=31){
									condition.day-=30;
									condition.month++;
								}
																
								break;
						}						
						
					
						
						if(f_compare_dt(task.end,condition)==1){
						   	
						   	printf("%5c%5c|",'*',' ');
						   	
						}else{
							printf("%5c%5c|",' ',' ');
						}
			
					}
					
					
					puts("");
					printf("~~~~~~~~~~~~~");	
				
					for(m=0;m<j;m++){
					printf("~~~~~~~~~~~");
					}
					puts("");	
					
							
				}
				
			
			}


			if(aux.status==0){
				printf("\nTitulo: %s",aux.title);
				printf("\nEncargado: %s",aux.louder);
				printf("\nLugar: %s",aux.location);
				printf("\nDescripcion: %s",aux.infor);
				printf("\nInicio: %i-%i-%i",aux.start.day,aux.start.month,aux.start.year);
				printf("\nFin: %i-%i-%i",aux.end.day,aux.end.month,aux.end.year);	
				printf("\nEstatus: En ejecucion");


			} else {

				printf("\nTitulo: %s",aux.title);
				printf("\nEncargado: %s",aux.louder);
				printf("\nLugar: %s",aux.location);
				printf("Descripcion: %s",aux.infor);
				printf("Inicio: %i-%i-%i",aux.start.day,aux.start.month,aux.start.year);
				printf("Fin: %i-%i-%i",aux.end.day,aux.end.month,aux.end.year);	
				printf("Estatus: Terminado.");
			}
				
			k++;
			getchar();
			fclose(filet);
	
			fclose(file);
		}
		
		
	
		
	}
	
	
}

 #endif
