// ------------------------------- arbbinar.c -----------------------------
// ------------------------------------------------------------------------
// 	       MODULO DE CABECERAS PARA USO DE OBJETOS
//		   ARBOL BINARIO PURO EN INORDEN
// ------------------------------------------------------------------------
//	  	  INSTRUCCIONES PARA LA COMPILACION
//          1.- Sustituye [tip] por la palabra significativa
// ------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbbinar.h"
#include "arrdina.h"

struct ab_char_ele    {
	struct ab_char_typo val;
	struct ab_char_ele *izq, *der;
    };

// ------------------------------------------------------------------------
//			FUNCIONES PRIVADAS
// ------------------------------------------------------------------------

void ab_char_error (char primit [20], int error)    {
	switch (error)    {
		case 1:	fprintf (stderr, "\n\t %s: No hay suficiente memoria.\n", primit);
			break;
		case 2: fprintf (stderr, "\n\t %s: El arbol binario esta vacio.\n", primit);
			break;
	  }
   }

// ------------------------------------------------------------------------
//			FUNCIONES PUBLICAS
// ------------------------------------------------------------------------

ab_char ab_char_nuev ()   {

	return (NULL);
   }

// ------------------------------------------------------------------------

int ab_char_vacio (ab_char a)   {

	return (a == NULL);
    }

// ------------------------------------------------------------------------

void ab_char_raiz (ab_char a, struct ab_char_typo *e)   {

	if (!a)    {
		ab_char_error ("ab_char_raiz", 2);
		exit (1);
	   }

	*e = a -> val;
    }

// ------------------------------------------------------------------------

void ab_char_mete (ab_char *a, struct ab_char_typo e,
		int (*cmp_char) (const void *, const void *))   {

	if (!*a)   {
		*a = (struct ab_char_ele *) malloc (sizeof (struct ab_char_ele));
		if (!*a)    {
			ab_char_error ("ab_char_mete", 1);
			exit (1);
		    }
		(*a) -> izq = (*a) -> der = NULL;
		(*a) -> val = e;
	  }
	else   {
		if (cmp_char (&(*a) -> val, &e) > 0)
		     ab_char_mete (&(*a) -> izq, e, cmp_char);
		else if (cmp_char (&(*a) -> val, &e) < 0)
			  ab_char_mete (&(*a) -> der, e, cmp_char);
	 }
    }

// ------------------------------------------------------------------------

void ab_char_saca (ab_char *a, struct ab_char_typo *e,
		int (*cmp_char) (const void *, const void *))     {
	ab_char *corr, viejo;

	if (!*a)    {
		ab_char_error ("ab_char_saca", 2);
		exit (1);
	    }
	else  {
		if (cmp_char (&(*a) -> val, e) > 0)
		    ab_char_saca (&(*a) -> izq, e, cmp_char);
		else if (cmp_char (&(*a) -> val, e) < 0)
		    ab_char_saca (&(*a) -> der, e, cmp_char);
		else   {
			*e = (*a) -> val;
			  // Destruimos el tipo de dato que almacena
			ardi_int_dest (&(*a) -> val.punt_arr);
			corr = &(*a) -> der;
			if (*corr)    {
				while ((*corr) -> izq)
					corr = &(*corr) -> izq;
				(*a) -> val = (*corr) -> val;
				viejo = *corr;
				*corr = (*corr) -> der;
				free (viejo);
			   }
			 else  {
				viejo = *a;
				*a = (*a) -> izq;
				free (viejo);
			   }
		   }
	    }
     }

// ------------------------------------------------------------------------

void ab_char_dest (ab_char *a)   {


	if (*a)   {
	      ab_char_dest (&(*a) -> izq);
	      ab_char_dest (&(*a) -> der);
	      // Destruimos el tipo de dato que almacena
	      ardi_int_dest (&(*a) -> val.punt_arr);
	      free (*a);
	      *a = NULL;
	 }
    }

// ------------------------------------------------------------------------

void ab_char_copy (ab_char a, ab_char *d)    {
	int prim = 0, count;

	if (a)   {
		*d = (struct ab_char_ele *) malloc (sizeof (struct ab_char_ele));
		if (!*d)    {
			ab_char_error ("ab_char_copy", 1);
			exit (1);
		    }

		  // Copiamos el tipo de dato que almacena
		strcpy ((*d) -> val.cadena, a -> val.cadena);
		count = ardi_int_tamlog (a -> val.punt_arr);
		(*d) -> val.punt_arr = ardi_int_copy (a -> val.punt_arr, prim, count);

		ab_char_copy (a -> der, &(*d) -> der);
		ab_char_copy (a -> izq, &(*d) -> izq);
	    }
	 else *d = NULL;
    }

// ------------------------------------------------------------------------

ab_char ab_char_find (ab_char a, struct ab_char_typo *e,
		int (*cmp_char) (const void *, const void *))    {

	if (!a) return (NULL);
	if (cmp_char (&a -> val, e) > 0)
	      return (ab_char_find (a -> izq, e, cmp_char));
	else if (cmp_char (&a -> val, e) < 0)
	      return (ab_char_find (a -> der, e, cmp_char));
	else    {
		*e = a -> val;
		return (a);
	 }
   }

// ------------------------------------------------------------------------

void ab_char_printf (ab_char a, int posicion)     {

	if (a) {
		ab_char_printf (a -> der, posicion + 6);
		printf ("%*s \n", posicion, a -> val.cadena);
		ab_char_printf (a -> izq, posicion + 6);
	   }
    }

// -------------------------------------------------------------------------

void ab_char_glosario (FILE *fp, ab_char a)   {
	struct ardi_int_typo e, d;
	int tam, i;

	if (a)    {
	      ab_char_glosario (fp, a -> izq);
              tam = ardi_int_tamlog (a -> val.punt_arr);
              fprintf (fp, "%s", a -> val.cadena);
              fprintf (fp, "%c", ':');
              d.x = 0;
	      for (i = 0; i < tam; i++)   {
		     ardi_int_obti (a -> val.punt_arr, i, &e);
                     if (d.x != e.x)    {
                          fprintf (fp, "%c", ' ');
		          fprintf (fp, "%d", e.x);
                          fprintf (fp, "%c", ',');
                       }
                     d.x = e.x;
		 }
	      fprintf (fp, "%c", '\n');
	      ab_char_glosario (fp, a -> der);
	  }
   }

// -----------------------------------------------------------------------