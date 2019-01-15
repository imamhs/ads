/*
    Copyright (C) 2014 Md Imam Hossain
    All rights reserved
*/

#include "def.h"

#include <SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

int m[4];

int run_loop = 1;
int fps = 0;
unsigned short int collision = 50;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

Vec2D t1[3], t2[3], b1[4], b2[4];
Vec2D colv;
float angle = 0.0f;
float scale = 1.0f;

Uint32 input_reg = 0;
Uint32 fps_reg = 0;
Uint32 col_reg = 0;
SDL_Surface *back_surface = NULL;
SDL_Event event;

void Render_Physics (void);
void Render_SDL (void);
void Render_Sprite (void);
void Get_Input (void);
void Shut_SDL (void);
void Init_Sprite (void);

int main (int argc, char *argv[])
{

fprintf (stdout ,"Status: Initializing SDL...\n");
if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1) {
    fprintf (stderr, "Error: Could not initialize SDL %s\n", SDL_GetError());
    exit (EXIT_FAILURE);
}
fprintf (stdout, "Status: SDL initialized\n");

if ((back_surface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    fprintf (stderr, "Could not set video mode %s\n", SDL_GetError());
    Shut_SDL ();
    exit (EXIT_FAILURE);
}

Init_Sprite ();

while (run_loop) {
    if ((SDL_GetTicks() - input_reg) > 10) {
        Get_Input ();
        Render_Physics ();
        input_reg = SDL_GetTicks ();
    }
    if ((SDL_GetTicks() - fps_reg) > 1000) {
        printf ("FPS: %d\n", fps);
        fps = 0;
        fps_reg = SDL_GetTicks ();
    }
Render_SDL ();
}

Shut_SDL ();

return EXIT_SUCCESS;
}

void Get_Input (void)
{
    while (SDL_PollEvent (&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        m[0] = 1;
                        break;
                    case SDLK_RIGHT:
                        m[1] = 1;
                        break;
                    case SDLK_UP:
                        m[2] = 1;
                        break;
                    case SDLK_DOWN:
                        m[3] = 1;
                        break;
                    case SDLK_ESCAPE:
                        run_loop = 0;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        m[0] = 0;
                        break;
                    case SDLK_RIGHT:
                        m[1] = 0;
                        break;
                    case SDLK_UP:
                        m[2] = 0;
                        break;
                    case SDLK_DOWN:
                        m[3] = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
          }
    }
}

void Render_Sprite (void)
{
if (SDL_FillRect (back_surface, NULL, SDL_MapRGB (back_surface->format, 255, 255, 255)) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (filledTrigonRGBA (back_surface, t1[0].x, t1[0].y,  t1[1].x, t1[1].y, t1[2].x, t1[2].y, 255, 0, 0, 255) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (filledTrigonRGBA (back_surface, t2[0].x, t2[0].y,  t2[1].x, t2[1].y, t2[2].x, t2[2].y, 0, 255, 0, 150) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (boxRGBA (back_surface, b1[0].x, b1[0].y, b1[2].x, b1[2].y, 0, 0, 255, 150)) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (boxRGBA (back_surface, b2[0].x, b2[0].y, b2[2].x, b2[2].y, 255, 0, 255, 150)) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (filledCircleRGBA(back_surface, WINDOW_WIDTH-40, 40, 15, collision, 0, 0, 255) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
}

void Render_Physics (void)
{

if (m[0]) {
dmat2d_translate (t1, 3, -1, 0);
}
if (m[1]) {
dmat2d_translate (t1, 3, 1, 0);
}
if (m[2]) {
dmat2d_translate (t1, 3, 0, -1);
}
if (m[3]) {
dmat2d_translate (t1, 3, 0, 1);
}

if (angle == 360) angle = 1.0f;
else angle += 1.0f;

t2[0].x = 0;
t2[1].x = 50;
t2[2].x = -50;
t2[0].y = 0;
t2[1].y = 50;
t2[2].y = 50;

dmat2d_rotate (t2, 3, angle);
dmat2d_translate (t2, 3, 300, 300);

if (scale > 5.0) scale = 1.0f;
else scale += 0.01;

b1[0].x = 0;
b1[0].y = 0;
b1[1].x = 40;
b1[1].y = 0;
b1[2].x = 40;
b1[2].y = 40;
b1[3].x = 0;
b1[3].y = 40;
dmat2d_scale (b1, 4, scale, scale);
dmat2d_translate (b1, 4, 400, 200);

if (acheck_polycollision (t1, 3, b1, 4) || acheck_polycollision (t1, 3, b2, 4) || acheck_polycollision (t1, 3, t2, 3)) {
collision = 255;
}
else collision = 50;

}


void Shut_SDL (void)
{
    fprintf (stdout, "Status: Quiting SDL...\n");

    SDL_Quit();

    fprintf (stdout, "Status: Success\n");
}

void Render_SDL (void)
{
    Render_Sprite ();
    SDL_Flip (back_surface);
    fps += 1;
}

void Init_Sprite (void)
{
t1[0].x = 0;
t1[1].x = 50;
t1[2].x = 0;
t1[0].y = 0;
t1[1].y = 50;
t1[2].y = 100;

dmat2d_reflect (t1, 3, 0, 1);
dmat2d_translate (t1, 3, 100, 100);

b1[0].x = 0;
b1[0].y = 0;
b1[1].x = 40;
b1[1].y = 0;
b1[2].x = 40;
b1[2].y = 40;
b1[3].x = 0;
b1[3].y = 40;

b2[0].x = 180;
b2[0].y = 200;
b2[1].x = 220;
b2[1].y = 200;
b2[2].x = 220;
b2[2].y = 240;
b2[3].x = 180;
b2[3].y = 240;

}
