#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

const char* filename = "logo_imac_400x400.jpg";


void show_numbers(){

}

int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenÃªtre et crÃ©ation d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td04", NULL);
    resizeViewport();


    // TODO: Chargement et traitement de la texture
    SDL_Surface *tab_img[11];
    tab_img[10] = IMG_Load("img/numbers/colon.png");
    tab_img[0] = IMG_Load("img/numbers/0.png");
    tab_img[1] = IMG_Load("img/numbers/1.png");
    tab_img[2] = IMG_Load("img/numbers/2.png");
    tab_img[3] = IMG_Load("img/numbers/3.png");
    tab_img[4] = IMG_Load("img/numbers/4.png");
    tab_img[5] = IMG_Load("img/numbers/5.png");
    tab_img[6] = IMG_Load("img/numbers/6.png");
    tab_img[7] = IMG_Load("img/numbers/7.png");
    tab_img[8] = IMG_Load("img/numbers/8.png");
    tab_img[9] = IMG_Load("img/numbers/9.png");
    
    GLuint tab_textureID[11];
    


    int i;
    for(i=0; i<11; ++i){
        if(tab_img[i] == NULL)
            printf("ERREUR DE CHARGEMENT\n");
        glGenTextures(1, &tab_textureID[i]);
        glBindTexture(GL_TEXTURE_2D, tab_textureID[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            tab_img[i]->w,
            tab_img[i]->h,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            tab_img[i]->pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // ...

    // TODO: LibÃ©ration des donnÃ©es CPU
    // ...

    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // TODO: Code de dessin

        
        glClear(GL_COLOR_BUFFER_BIT);
        

        time_t secondes;
        struct tm instant;

        time(&secondes);
        instant=*localtime(&secondes);

    //instant.tm_hour, instant.tm_min, instant.tm_sec);

       
        int i;
        glEnable(GL_TEXTURE_2D); // On précise qu’on veut activer la fonctionnalité de texturing
        for (i = 0; i < 8; ++i)
        {
            int img;
            switch(i){
                case 0:
                img = instant.tm_hour/10;
                break;
                case 1:
                img = instant.tm_hour%10;
                break;
                case 2:
                img = 10;
                break;
                case 3:
                img = instant.tm_min/10;
                break;
                case 4:
                img = instant.tm_min%10;
                break;
                case 5:
                img = 10;
                break;
                case 6:
                img = instant.tm_sec/10;
                break;
                case 7:
                img = instant.tm_sec%10;
                break;
            }

            int width = 26, height = 42, margin = 10;
            glBindTexture(GL_TEXTURE_2D, tab_textureID[img]); // On bind la texture pour pouvoir l’utiliser
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0);
                glVertex2f(-1 + 2. * ((i)*width+margin) / WINDOW_WIDTH, -(-1 + 2. * (0)*height / WINDOW_HEIGHT));
                glTexCoord2f(1, 0);
                glVertex2f(-1 + 2. * ((i+1)*width+margin) / WINDOW_WIDTH, -(-1 + 2. * (0)*height / WINDOW_HEIGHT));
                glTexCoord2f(1,1);
                glVertex2f(-1 + 2. * ((i+1)*width+margin) / WINDOW_WIDTH, -(-1 + 2. * (1)*height / WINDOW_HEIGHT));
                glTexCoord2f(0, 1);
                glVertex2f(-1 + 2. * ((i)*width+margin) / WINDOW_WIDTH, -(-1 + 2. * (1)*height / WINDOW_HEIGHT));
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0); // On débind la texture
        }
        glDisable(GL_TEXTURE_2D); // On désactive le sampling de texture
        
        
        // ...


        // Fin du code de dessin

SDL_Event e;
while(SDL_PollEvent(&e)) {
    switch(e.type) {

        case SDL_QUIT:
        loop = 0;
        break;

        case SDL_VIDEORESIZE:
        WINDOW_WIDTH = e.resize.w;
        WINDOW_HEIGHT = e.resize.h;
        resizeViewport();

        default:
        break;
    }
}

SDL_GL_SwapBuffers();
Uint32 elapsedTime = SDL_GetTicks() - startTime;
if(elapsedTime < FRAMERATE_MILLISECONDS) {
    SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
}
}

    // TODO: LibÃ©ration des donnÃ©es GPU

// glDeleteTextures(1,&textureID);
// SDL_FreeSurface(surface);

    // Liberation des ressources associÃ©es Ã  la SDL
SDL_Quit();
return EXIT_SUCCESS;
}