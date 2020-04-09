// ------------------------------- arbbinar.h -----------------------------
// ------------------------------------------------------------------------
// 	       MODULO DE CABECERAS PARA USO DE OBJETOS
//		   ARBOL BINARIO PURO EN INORDEN
// ------------------------------------------------------------------------
//	  	  INSTRUCCIONES PARA LA COMPILACION
//          1.- Define una estructura ab_[tip]_typo
//          2.- Sustituye [tip] por la palabra significativa
// ------------------------------------------------------------------------

#ifndef AB_CHAR_TYPO

#define AB_CHAR_TYPO

struct ab_char_typo   {
	char cadena [20];
	struct ardi_int_rep *punt_arr;
    };

typedef struct ab_char_ele *ab_char;

// ------------------------------------------------------------------------

ab_char ab_char_nuev (void);
int ab_char_vacio (ab_char a);
void ab_char_raiz (ab_char a, struct ab_char_typo *e);
void ab_char_mete (ab_char *a, struct ab_char_typo e,
		int (*cmp_char) (const void *, const void *));
void ab_char_saca (ab_char *a, struct ab_char_typo *e,
		int (*cmp_char) (const void *, const void *));
void ab_char_dest (ab_char *a);
void ab_char_copy (ab_char a, ab_char *d);
ab_char ab_char_find (ab_char a, struct ab_char_typo *e,
		int (*cmp_char) (const void *, const void *));
void ab_char_printf (ab_char a, int posicion);
void ab_char_glosario (FILE *fp, ab_char a);

#endif