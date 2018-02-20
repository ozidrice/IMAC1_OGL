#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "param.h"
#include "point.h"
#include "sauvegarde.h"
#include "tas.h"

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void projection(){
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER);
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.,1.,-1.,1.);
}


/*
*   Free tous les points
*/
void freePoints(){
    freeTas();
}

/*
*   Free tous les points et SDL
*/
int freeAll(){
    freePoints();
    SDL_Quit();
    return EXIT_SUCCESS;
}


int main(int argc, char** argv){
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("IMAPAINT", NULL);


    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {
        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();


        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

        
                /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            /* Quelques exemples de traitement d'evenements : */
            Point2D * lastDraw = NULL,*firstDraw = NULL;
            switch(e.type) {
                /* Clic souris */
                case SDL_BUTTON_LEFT:
                break;
                case SDL_BUTTON_RIGHT:
                if(firstDraw != NULL && lastDraw != NULL) {
                    afficheForme(lastDraw,2,1);
                    afficheForme(firstDraw,2,1);
                }
                break;
                case SDL_KEYDOWN:
                switch(e.key.keysym.sym){
                    case 'q':
                            //QUIT
                    return freeAll();
                    break;
                    case 'c':

                    freePoints();
                    glClear(GL_COLOR_BUFFER_BIT);
                    drawLandmark();


                    glMatrixMode(GL_MODELVIEW);
                    glScalef(NB_Y/NB_X < 1 ? NB_Y/NB_X : 1,NB_X/NB_Y < 1 ? NB_X/NB_Y : 1,1);
                    glTranslatef(1/NB_X, 2/NB_Y, 0);
                    glColor3f(1.,0.4,0.1);
                    drawCircle();
                    glRotatef(45, 0.0, 0.0, 1.0);
                    glColor3f(1.,0,0);
                    glTranslatef(1/NB_X, -2/NB_Y, 0);
                    drawSquare();
                    

                    glTranslatef(-4/NB_X, 0, 0);
                    glRotatef(-45, 0.0, 0.0, 1.0);
                    glColor3f(1.,0.7,0.0);
                    drawSquare();
                    break;
                    case 't':
                    default : 
                            //ON ENREGISTRE LE CARACTERE
                            // selectedChar = e.key.keysym.sym; 
                    break;
                }
                break;
                case SDL_VIDEORESIZE:
                WINDOW_WIDTH = e.resize.w;
                WINDOW_HEIGHT = e.resize.h;
                projection();
                break;

            }


        }
        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    return freeAll();
}
