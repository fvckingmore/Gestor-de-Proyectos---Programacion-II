#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib_task.h"
#include "misc.h"


int main() {

	PROJECT project, project2;

	project.start.year = 2019;
	project.start.month = 5;
	project.start.day = 20;
	strcpy(project.title, "Proyecto1");
	strcpy(project.id, "HOL520");

	project2.start.year = 2019;
	project2.start.month = 5;
	project2.start.day = 20;
	strcpy(project2.title, "Proyecto2");
	strcpy(project2.id, "HI520");

	f_menu_task(project2);

return 0;
}