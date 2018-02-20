#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "param.h"
#include "point.h"
#include "tas.h"
#include "sauvegarde.h"

#define NOMBRE_SEGMENTS_CIRCLE 50

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

void drawSquare(){
    glBegin(GL_QUADS);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
    glEnd();
}

void drawLandmark(){
   glBegin(GL_LINES);
   glColor3f(1,0,0);
   glVertex2f(-1,0);
   glVertex2f(1,0);

   glColor3f(0,1,0);
   glVertex2f(0,-1);
   glVertex2f(0,1);

   float i;
   glColor3f(1,1,1);
   for(i = -NB_X; i < NB_X; ++i){
        glVertex2f(i/NB_X,-0.01);
        glVertex2f(i/NB_X,0.01);
   }
   for(i = -NB_Y; i < NB_Y; ++i){
        glVertex2f(-0.01,i/NB_Y);
        glVertex2f(0.01,i/NB_Y);
   }

   glEnd();
}

void drawFilledCircle(){
    int i;
    double angle;
    glBegin(GL_POLYGON);


    for (i = 0; i < NOMBRE_SEGMENTS_CIRCLE; ++i){
        angle = 2*M_PI*((i*1.)/NOMBRE_SEGMENTS_CIRCLE);
        glVertex2f(cos(angle),sin(angle));
    }
    glEnd();
}

void drawCircle(){
    int i;
    double angle;

    
    
    glBegin(GL_LINES);
    for (i = 0; i < NOMBRE_SEGMENTS_CIRCLE; ++i){
        angle = 2*M_PI*((i*1.)/NOMBRE_SEGMENTS_CIRCLE);
        glVertex2f(cos(angle),sin(angle));
        angle = 2*M_PI*((i*1.+1)/NOMBRE_SEGMENTS_CIRCLE);
        glVertex2f(cos(angle),sin(angle));
    }
    glEnd();
}


/*
*   Ajoute au tas le point p
*   nbPoint = Nombre de points necessaire à la forme
*   Si il y a nbPoint points dans le tas alors affiche la forme   
*   si savePoint = 1 alors sauvegarde les points lors de l'affichage de la forme 
*/
void afficheForme(Point2D *p, int nbPoint, int savePoint){
    if(p != NULL){
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
}