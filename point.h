#include "param.h"

typedef struct point2D{
    int x;
    int y;
    float r,v,b;
}Point2D;

Point2D *creer_point2D(int x, int y, float r, float v, float b);
void tracePoint(Point2D *p, float weight);
void traceLigne(Point2D *a, Point2D *b, int weight);
void traceTriangle(Point2D *a, Point2D *b, Point2D *c, int weight);
void traceRectangle(Point2D *a, Point2D *b, Point2D *c, Point2D *d,int weight);