#include <stdlib.h>
#include <stdio.h>
#include "point.h"

Point2D *creer_point2D(int x, int y){
    Point2D *p = malloc(sizeof(Point2D));
    if(p == NULL){
        printf("ERREUR : CREATION DE POINT IMPOSSIBLE\n");
    }else{
        p->x = x;
        p->y = y;
    }

    return p;
}
