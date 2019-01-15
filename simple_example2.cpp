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

// create four display objects
Bostu t1, t2, t3, b1;

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

SDL_WM_SetCaption("2D polygon collision detection using Akriti", 0);

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
if (t1.PointsN) if (filledTrigonRGBA (back_surface, t1.Points[0].x, t1.Points[0].y,  t1.Points[1].x, t1.Points[1].y, t1.Points[2].x, t1.Points[2].y, 255, 0, 0, 255) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (t2.PointsN) if (filledTrigonRGBA (back_surface, t2.Points[0].x, t2.Points[0].y,  t2.Points[1].x, t2.Points[1].y, t2.Points[2].x, t2.Points[2].y, 0, 255, 0, 150) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (t3.PointsN) if (filledTrigonRGBA (back_surface, t3.Points[0].x, t3.Points[0].y,  t3.Points[1].x, t3.Points[1].y, t3.Points[2].x, t3.Points[2].y, 100, 25, 100, 150) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (b1.PointsN) if (boxRGBA (back_surface, b1.Points[0].x, b1.Points[0].y, b1.Points[2].x, b1.Points[2].y, 0, 0, 255, 150)) fprintf (stderr, "Error: %s\n", SDL_GetError());
if (filledCircleRGBA(back_surface, WINDOW_WIDTH-40, 40, 15, collision, 0, 0, 255) < 0) fprintf (stderr, "Error: %s\n", SDL_GetError());
}

void Render_Physics (void)
{

Vec2D shadow[5];

if (m[0]) {
t1.Velocity.x -= 0.05;
}
if (m[1]) {
t1.Velocity.x += 0.05;
}
if (m[2]) {
t1.Velocity.y -= 0.05;
}
if (m[3]) {
t1.Velocity.y += 0.05;
}

if (t1.Velocity.x || t1.Velocity.y) {
acopy_shape (t1.Points, shadow, t1.PointsN);
dmat2d_translate (shadow, t1.PointsN, t1.Velocity.x, t1.Velocity.y);
if (acheck_polycollision (shadow, t1.PointsN, b1.Points, b1.PointsN) || acheck_polycollision (shadow, t1.PointsN, t2.Points, t2.PointsN) || acheck_polycollision (shadow, t1.PointsN, t3.Points, t3.PointsN)) {
collision = 255;
Vec2D temp = dvec2d_neg (t1.Velocity);
temp = dvec2d_mult (temp, 0.1);
while (acheck_polycollision (shadow, t1.PointsN, b1.Points, b1.PointsN) || acheck_polycollision (shadow, t1.PointsN, t2.Points, t2.PointsN) || acheck_polycollision (shadow, t1.PointsN, t3.Points, t3.PointsN)) {
dmat2d_translate (shadow, t1.PointsN, temp.x, temp.y);
}
dmat2d_translate (shadow, t1.PointsN, t1.Velocity.x, 0);
if (acheck_polycollision (shadow, t1.PointsN, b1.Points, b1.PointsN) || acheck_polycollision (shadow, t1.PointsN, t2.Points, t2.PointsN) || acheck_polycollision (shadow, t1.PointsN, t3.Points, t3.PointsN)) {
dmat2d_translate (shadow, t1.PointsN, -t1.Velocity.x, 0);
t1.Velocity.x = 0;
}
dmat2d_translate (shadow, t1.PointsN, 0, t1.Velocity.y);
if (acheck_polycollision (shadow, t1.PointsN, b1.Points, b1.PointsN) || acheck_polycollision (shadow, t1.PointsN, t2.Points, t2.PointsN) || acheck_polycollision (shadow, t1.PointsN, t3.Points, t3.PointsN)) {
dmat2d_translate (shadow, t1.PointsN, 0, -t1.Velocity.y);
t1.Velocity.y = 0;
}
acopy_shape (shadow, t1.Points, t1.PointsN);
}
else {
acopy_shape (shadow, t1.Points, t1.PointsN);
collision = 50;
}
}

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

// defines display objects and their positions
void Init_Sprite (void)
{
Vec2D shapes[10];

shapes[0].x = 0;
shapes[1].x = 50;
shapes[2].x = 0;
shapes[0].y = 0;
shapes[1].y = 50;
shapes[2].y = 100;

if (t1.create (3)) {
acopy_shape (shapes, t1.Points, t1.PointsN);
dmat2d_translate (t1.Points, t1.PointsN, 100, 80);
}

shapes[0].x = -100;
shapes[0].y = 0;
shapes[1].x = 120;
shapes[1].y = 0;
shapes[2].x = 120;
shapes[2].y = 80;
shapes[3].x = -100;
shapes[3].y = 80;

if (b1.create (4)) {
acopy_shape (shapes, b1.Points, b1.PointsN);
dmat2d_translate (b1.Points, b1.PointsN, 200, 200);
}

shapes[0].x = 0;
shapes[1].x = 50;
shapes[2].x = -50;
shapes[0].y = 0;
shapes[1].y = 50;
shapes[2].y = 50;

if (t2.create (3)) {
acopy_shape (shapes, t2.Points, t2.PointsN);
dmat2d_rotate (t2.Points, t2.PointsN, -45);
dmat2d_translate (t2.Points, t2.PointsN, 300, 300);
}

shapes[0].x = 0;
shapes[1].x = 50;
shapes[2].x = 150;
shapes[0].y = 0;
shapes[1].y = 150;
shapes[2].y = 100;

if (t3.create (3)) {
acopy_shape (shapes, t3.Points, t3.PointsN);
dmat2d_translate (t3.Points, t3.PointsN, 400, 100);
}

}
