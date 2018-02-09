#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "point.h"

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
    }
    return p;
}


/*
*   Affiche le point p aux coordonnées spéciéfié et à la couleur rvb spécifiée par la structure
*   R <= V <= B <= 1
*   R >= V >= B >= 0
*   Utilise l'épaisseur weight
*   free les points
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
*   free les points
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
*   free les points
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
*   free les points
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