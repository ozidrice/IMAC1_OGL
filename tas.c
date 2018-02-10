#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#define SIZE_TAS 5

static Point2D *tasPoint[5];
static int posTas = 0;

/*
*	Ajoute un element au tas
*/
void ajouterTas(Point2D *p){
	if(posTas >= SIZE_TAS-1){
		printf("ERR : TAS PLEIN\n");
	}else
		tasPoint[posTas++] = p;
}

/*
*	Vide les élements du tas
*	Remet pos tas = 0
*/
void resetTas(){
	for (int i = 0; i <= posTas; ++i){
		if(tasPoint[i] != NULL){
			// free(tasPoint[i]);
			tasPoint[i] = NULL;
		}
	}
	posTas = 0;
}

/*
*	Récupère l'élement d'id pos
*/
Point2D *getElemTas(int pos){
	if(pos > posTas){
		printf("ERR : POSITION INTROUVABLE\n");
		return NULL;
	}else 
		return tasPoint[pos];
}


/*
*	Retourne le nombre d'élements placés dans le tas
*/
int getNbElemTas(){
	return posTas;
}

