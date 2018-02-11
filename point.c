#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "tas.h"
#include "sauvegarde.h"

/*
*   Créé un point 
*   return NULL si impossible
*/
Point2D *creer_point2D(int x, int y, float r, float v, float b){
    Point2D *p = (Point2D *)malloc(sizeof(Point2D));
    if(p == NULL){
        printf("ERREUR : CREATION DE POINT IMPOSSIBLE\n");
    }else{
        p->x = x;
        p->y = y;
        p->r = r;
        p->v = v;
        p->b = b;
        p->next = NULL;
    }
    return p;
}


void printPoint2D(Point2D *p){
    printf("[x:%d;y:%d;r:%f;v:%f;b:%f;next:%p]\n",p->x,p->y,p->r,p->v,p->b,p->next);
}

/*
*   Affiche le point p aux coordonnées spéciéfié et à la couleur rvb spécifiée par la structure
*   R <= V <= B <= 1
*   R >= V >= B >= 0
*   Utilise l'épaisseur weight
*/
void tracePoint(Point2D *p, float weight){
    glColor3f(p->r,p->v,p->b);
    glPointSize(weight);
    glBegin(GL_POINTS);
    glVertex2f(-1 + 2. * p->x / WINDOW_WIDTH, -(-1 + 2. * p->y / WINDOW_HEIGHT));
    glEnd();
}

/*
*   Trace le segment AB avec les coordonnées spéciéfié par la structure
*   La couleur utilisée est celle du point a
*   R <= V <= B <= 1
*   R >= V >= B >= 0
*   Utilise l'épaisseur weight
*/
void traceLigne(Point2D *a, Point2D *b, int weight){
    glColor3f(a->r,a->v,a->b);
    glLineWidth(weight);
    glBegin(GL_LINES);
    glVertex2f(-1 + 2. * a->x / WINDOW_WIDTH, -(-1 + 2. * a->y / WINDOW_HEIGHT));
    glVertex2f(-1 + 2. * b->x / WINDOW_WIDTH, -(-1 + 2. * b->y / WINDOW_HEIGHT));
    glEnd();
}

/*
*   Trace le triangle ABC avec les coordonnées spéciéfié par la structure
*   La couleur utilisée est celle du point a
*   R <= V <= B <= 1
*   R >= V >= B >= 0
*   Utilise l'épaisseur weight
*/
void traceTriangle(Point2D *a, Point2D *b, Point2D *c, int weight){
    glColor3f(a->r,a->v,a->b);
    glLineWidth(weight);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1 + 2. * a->x / WINDOW_WIDTH, -(-1 + 2. * a->y / WINDOW_HEIGHT));
    glVertex2f(-1 + 2. * b->x / WINDOW_WIDTH, -(-1 + 2. * b->y / WINDOW_HEIGHT));
    glVertex2f(-1 + 2. * c->x / WINDOW_WIDTH, -(-1 + 2. * c->y / WINDOW_HEIGHT));
    glEnd();
}

/*
*   Trace le rectangle ABCD avec les coordonnées spéciéfié par la structure
*   a: Top Left
*   b: Top right
*   c: Bottom right
*   d: Bottom left
*   
*   La couleur utilisée est celle du point a
*   R <= V <= B <= 1
*   R >= V >= B >= 0
*   Utilise l'épaisseur weight
*/
void traceRectangle(Point2D *a, Point2D *b, Point2D *c, Point2D *d,int weight){
    glColor3f(a->r,a->v,a->b);
    glLineWidth(weight);
    glBegin(GL_QUADS);
    glVertex2f(-1 + 2. * a->x / WINDOW_WIDTH, -(-1 + 2. * a->y / WINDOW_HEIGHT));
    glVertex2f(-1 + 2. * b->x / WINDOW_WIDTH, -(-1 + 2. * b->y / WINDOW_HEIGHT));
    glVertex2f(-1 + 2. * c->x / WINDOW_WIDTH, -(-1 + 2. * c->y / WINDOW_HEIGHT));
    glVertex2f(-1 + 2. * d->x / WINDOW_WIDTH, -(-1 + 2. * d->y / WINDOW_HEIGHT));
    glEnd();
}

/*
*   Ajoute au tas le point p
*   nbPoint = Nombre de points necessaire à la forme
*   Si il y a nbPoint points dans le tas alors affiche la forme   
*   si savePoint = 1 alors sauvegarde les points lors de l'affichage de la forme 
*/
void afficheForme(Point2D *p, int nbPoint, int savePoint){
    if(getNbElemTas() < nbPoint )
        ajouterTas(p);
    if(getNbElemTas() == nbPoint ){
        switch(nbPoint){
            case 1:
                tracePoint(getElemTas(0), 3.);
                break;
            case 2:
                traceLigne(getElemTas(0), getElemTas(1), 3.);
                getElemTas(0)->next = getElemTas(1);
                break;
            case 3:
                traceTriangle(getElemTas(0), getElemTas(1), getElemTas(2), 3.);
                getElemTas(0)->next = getElemTas(1);
                getElemTas(1)->next = getElemTas(2);
                break;
            case 4:
                traceRectangle(getElemTas(0), getElemTas(1), getElemTas(2), getElemTas(3),3.);
                getElemTas(0)->next = getElemTas(1);
                getElemTas(1)->next = getElemTas(2);
                getElemTas(2)->next = getElemTas(3);
                break;
        }
        if(savePoint == 1)
            sauvegardePoint(getElemTas(0));
        resetTas();
    }
}