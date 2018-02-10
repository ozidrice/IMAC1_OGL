#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include "param.h"
#include "point.h"
#include "sauvegarde.h"

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
*   Retourne la valeur binaire de i
*/
int int_to_binary(int i) {
    if (i == 0) return 0;
    return (i % 2) + 10 * int_to_binary(i / 2);
}

/*
*   Affiche la palette de couleur
*   ATTENTION : EFFACE L AFFICHAGE COURANT
*/
void affichePannelCouleur(){
    int nbColor = 8;  
    int i;
    for(i = 0; i<nbColor; i++){
        char r = int_to_binary(i)/100;
        char v = (int_to_binary(i)/10)%10;
        char b = int_to_binary(i)%10;

        glColor3f(r,v,b);
        Point2D *topLeft = creer_point2D((WINDOW_WIDTH/nbColor)*i,0,r,v,b);
        Point2D *topRight = creer_point2D((WINDOW_WIDTH/nbColor)*(i+1),0,r,v,b);
        Point2D *bottomRight = creer_point2D((WINDOW_WIDTH/nbColor)*(i+1),WINDOW_HEIGHT,r,v,b);
        Point2D *bottomLeft = creer_point2D((WINDOW_WIDTH/nbColor)*i,WINDOW_HEIGHT,r,v,b);
        traceRectangle(topLeft,topRight,bottomRight,bottomLeft,3.);
        free(topLeft);
        free(topRight);
        free(bottomRight);
        free(bottomLeft);
    }  
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
    char selectedChar = 'p'; //Set point par défaut
    float selectedR=1,selectedV=1,selectedB=1; //Blanc par défaut
    char precmod[10] = "dessin", *mode = "dessin"; //mode dessin par défaut
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
            switch(e.type) {
                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    if(strcmp("palette",mode) == 0){
                        //Si en mode palette
                        int iCouleurPalette = e.button.x/(WINDOW_WIDTH/8);
                        selectedR = int_to_binary(iCouleurPalette)/100;
                        selectedV = (int_to_binary(iCouleurPalette)/10)%10;
                        selectedB = int_to_binary(iCouleurPalette)%10;
                    }else{
                        //Si en mode dessin
                        int nbPointNecessaires = 0;
                        switch(selectedChar){
                            case 'p':
                                //POINT
                                nbPointNecessaires = 1;
                                break;
                            case 'l':
                                //LIGNE
                                nbPointNecessaires = 2;
                                break;
                            case 't':
                                //TRIANGLE
                                nbPointNecessaires = 3;
                                break;
                            case 'r':
                                //RECTANGLE
                                nbPointNecessaires = 4;
                        }
                        afficheForme(creer_point2D(e.button.x,e.button.y,selectedR,selectedV,selectedB),nbPointNecessaires,1);
                    }
                    break;
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case 'q':
                            //QUIT
                            SDL_Quit();
                            return EXIT_SUCCESS;
                            break;
                        case ' ':
                            //MODE PALETTE
                            mode = "palette";
                            break;
                        default : 
                            //ON ENREGISTRE LE CARACTERE
                            selectedChar = e.key.keysym.sym; 
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    if(e.key.keysym.sym == ' ')
                        mode = "dessin";
                    break;
                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    projection();
                    break;

            }


            if(strcmp("palette",mode) == 0){
                //Si palette
                affichePannelCouleur();
            }else{
                if(strcmp(precmod,mode)!=0){
                    //Si on vient de repasser en dessin on efface tout
                    glClear(GL_COLOR_BUFFER_BIT);
                    restaurePoint();
                }
            }
            strcpy(precmod,mode);
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
