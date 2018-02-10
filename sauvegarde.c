#include <stdlib.h>
#include <stdio.h>
#include "point.h"

static ListePoint2D *listePoint;
static int sizeListePoint = 0;

void sauvegardePoint(ListePoint2D points){
	sizeListePoint++;
	if( listePoint == NULL){
		listePoint = (ListePoint2D*)malloc(sizeof(ListePoint2D*));
	}else{
		listePoint = realloc(listePoint,sizeof(ListePoint2D*)*sizeListePoint);
	}
	*(listePoint+(sizeof(ListePoint2D*)*(sizeListePoint-1))) = points;
}

int sizeofListePoint(ListePoint2D lstPoint){
	int size = 0;
	ListePoint2D tmp = lstPoint;
	while(tmp != NULL){
		tmp = tmp->next;
		size++;
	}
	return size;
}

void restaurePoint(){
	printf("STARTING RESTAURE___________\n",sizeListePoint);
	int i;
	for (i = 0; i < sizeListePoint; ++i){
		// printf("i=%d;sizeListePoint:%d;i < sizeListePoint:%d\n",i,sizeListePoint,i < sizeListePoint );
		// ListePoint2D *lstPoint = listePoint+(sizeof(ListePoint2D*)*i);
		// if(lstPoint != NULL && *lstPoint!=NULL){
		// 	int nbPointListe = sizeofListePoint(*lstPoint);
		// 	while(*lstPoint != NULL){
		// 		printPoint2D(*lstPoint);
		// 		afficheForme(*lstPoint,nbPointListe,0);
		// 		*lstPoint = (*(lstPoint))->next;
		// 		printf("%d\n",*lstPoint != NULL );
		// 	}
		// }
	}
	printf("ENDING RESTAURE___________\n");
}
