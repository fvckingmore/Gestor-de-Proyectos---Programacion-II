// --------------------------------------------------------------------------------------------------
// archivo :conio.h
// objetivo:archivo de cabecera para archivo conio.c con la funciones getch() y getche()
// lenguaje:gnu c
// autor   :jaor
// www.jaorsoftware.com
// --------------------------------------------------------------------------------------------------

// Incluye Librerías
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>


/* Función que lee un caracter desde el teclado, sin echo */
int getch(void);
/* Función que lee un caracter desde el teclado, con echo */
int getche(void);
/* Función que lee un caracter pendiente desde el teclado, sin echo */
int getchp(void);

/* Función que espera a que se leea un caracter en el teclado */
int kbhit(void);

/* Función que espera a que se leea un caracter en el teclado */
int kbhit2(void);
