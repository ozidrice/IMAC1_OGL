#include <stdlib.h>
#include <stdio.h>
#include "point.h"

static ListePoint2D *listePoint = NULL; //Chaque élement du tableau est une forme 
/*
*	*(listePoint+0) --> a --> b --> c 	: C'est un triangle
*	*(listePoint+1) --> d 				: C'est un point 
*	etc..
*/
static int sizeListePoint = 0; //Nombre de formes sauvegardés
 

/*
*	Sauvegarde une forme
*/ 
void sauvegardePoint(ListePoint2D forme){
	sizeListePoint++;
	listePoint = realloc(listePoint,sizeof(ListePoint2D*)*sizeListePoint);
	
	*(listePoint+(sizeof(ListePoint2D*)*(sizeListePoint-1))) = forme;
}

/*
*	Retourne le nombre de point contenus dans une listePoint2D
*/
int sizeofListePoint(ListePoint2D lstPoint){
	int size = 0;
	ListePoint2D tmp = lstPoint;
	while(tmp != NULL){
		tmp = tmp->next;
		size++;
	}
	return size;
}


/*
*	Recré les formes sauvegardés
*	!!! BUG QUAND PLUS DE 4 FORMES A RESTAURER (sizeListePoint > 4 == segfault ?????) !!!
*/
void restaurePoint(){
	printf("STARTING RESTAURE___________\n");
	int i;
	for (i = 0; i < sizeListePoint; ++i){
		ListePoint2D tmpListPoint = *(listePoint+(sizeof(ListePoint2D*)*i) );
		int nbPointListe = sizeofListePoint(tmpListPoint);
		while(tmpListPoint != NULL){
			printPoint2D(tmpListPoint); //POUR DEBUG
			afficheForme(tmpListPoint,nbPointListe,0);
			tmpListPoint = tmpListPoint->next;
		}
	}
	printf("ENDING RESTAURE___________\n");
}

/*
*	Free tous les points contenus dans la liste des points ainsi que listePoint
*	!!! BUG QUAND PLUS DE 4 FORMES A FREE (sizeListePoint > 4 	== segfault ?????) !!!
*/
void freeSauvegarde(){
	int i;
	for (i = 0; i < sizeListePoint; ++i){
		ListePoint2D tmpListPoint = *(listePoint+(sizeof(ListePoint2D*)*i));
		while(tmpListPoint != NULL){
			ListePoint2D tmp = tmpListPoint;
			tmpListPoint = tmpListPoint->next;
			free(tmp);
		}

	}
	free(listePoint);
	listePoint = NULL;
	sizeListePoint = 0;
}

