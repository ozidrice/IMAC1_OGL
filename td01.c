#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void projection(){
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.,1.,-1.,1.);
}

void tracePoint(int x, int y){
    glBegin(GL_POINTS);
    glVertex2f(-1 + 2. * x / WINDOW_WIDTH, -(-1 + 2. * y / WINDOW_HEIGHT));
    glEnd();
}

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("LOL.", NULL);
    /* Boucle d'affichage */
    int loop = 1;
    float r, v, b;
    r=v=b=0.0;
    char selection;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
                
        /* Placer ici le code de dessin */



        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        projection();
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
            switch(e.type) {
                /* Clic souris */
                case SDL_MOUSEMOTION:
                    r = e.motion.x/(WINDOW_WIDTH*1.);
                    v = e.motion.y/(WINDOW_WIDTH*1.);           
                    break;
                case SDL_MOUSEBUTTONUP:
                    tracePoint(e.button.x,e.button.y); 
                    break;
                /* Touche clavier */
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case 'q':
                            SDL_Quit();
                            return EXIT_SUCCESS;
                            break;
                        default : 
                         break;
                    }
                    break;

                default:
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

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
