#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "arbbinar.h"
#include "arrdina.h"

#define PAGINA 60

// ------------------------------------------------------------------------

int cmp_int (const void *a, const void *b)   {
	return (*((int *) a) - *((int *) b));
    }

// ------------------------------------------------------------------------

int cmp_char (const void *a, const void *b)   {
	return (strcmp ((char *) a, (char *) b));
   }

// ------------------------------------------------------------------------

void blancos (char cadena [25])    {
	int i;
	for (i = 0; i < strlen (cadena); i++)   cadena [i] = ' ';
   }

// ------------------------------------------------------------------------

int delimitador (char c)    {
        return ((strchr ("+-*/=%|!��?()[]{}#&$.,:;<>��", c)) ? 1 : 0);
   }

// ------------------------------------------------------------------------

void fichero_arbol (char *argv [], ab_char *a)    {
    FILE *fp;
    char palabra [25];
    ab_char basura;
    struct ab_char_typo arbol;
    struct ardi_int_typo array;
    int linea = 1, pagina = 1, i = 0, aparicion;
    char c;

    if ((fp = fopen (argv [1], "rt")) == NULL)   {
	 fprintf (stderr, "Fichero_arbol: El fichero %s no existe.\n", argv [1]);
	 exit (1);
      }

    printf ("\n\n\n\t N�mero m�ximo de apariciones permitidas para los t�rminos: ");
    scanf ("%d", &aparicion);

    basura = ab_char_nuev ();

    while ((c = fgetc (fp)) != EOF)    {
         if ((!delimitador (c)) && (!isdigit (c)) && (c != ' ') &&
             (c != '\n') && (c != '"') && (c != '\0'))   {
	        palabra [i] = c;
	        i++;
	    }
	 else     {
	      palabra [i] = '\0';
	      i = 0;
	      if (palabra [i] != '\0')    {
		   arbol.punt_arr = NULL;
		   strcpy (arbol.cadena, palabra);
		   array.x = pagina;

		   if (ab_char_find (basura, &arbol, cmp_char) == NULL)   {
		       if (ab_char_find (*a, &arbol, cmp_char) == NULL)   {
			    arbol.punt_arr = ardi_int_const (1, array);
			    ab_char_mete (a, arbol, cmp_char);
			 }
		       else  {
			    if (ardi_int_tamlog (arbol.punt_arr) < aparicion)
				  ardi_int_aumd (arbol.punt_arr, array);
			    else    {
				  ab_char_saca (a, &arbol, cmp_char);
				  arbol.punt_arr = ardi_int_nuev ();
				  ab_char_mete (&basura, arbol, cmp_char);
			      }
			 }
		     }
		   blancos (palabra);
		}
	   }

	 if (c == '\n')   linea++;
	 if (linea > PAGINA)    {
		linea = 1;
		pagina++;
	   }
      }

    fclose (fp);

    ab_char_dest (&basura);
  }

// ------------------------------------------------------------------------
//			    PROGRAMA PRINCIPAL
// ------------------------------------------------------------------------

int main (int argc, char *argv [])   {
      FILE *fp;
      ab_char arbol;
      int pos = 0;

      if (argc != 3)    {
             fprintf (stderr, "\tError: N�mero de par�metros incorrecto.\n");
             fprintf (stderr, "\tUso: programa <fichero entrada> <fichero glosario>\n");
             exit (1);
         }

      printf ("\n\n\t\t 'GENERACI�N DE UN GLOSARIO DE T�RMINOS'\n\n");
      printf ("\n\t Espere un momento......");

      arbol = ab_char_nuev ();
      fichero_arbol (argv, &arbol);

      clrscr ();
      ab_char_printf (arbol, pos);

      if ((fp = fopen (argv [2], "wt")) != NULL)
		ab_char_glosario (fp, arbol);
      else fprintf (stderr, "Ha ocurrido un error al abrir el fichero %s.\n", argv [2]);
      fclose (fp);

      ab_char_dest (&arbol);
      return;
  }

// ------------------------------------------------------------------------