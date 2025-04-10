#ifndef _MONDELBROT_
#define _MONDELBROT_

#include <stdio.h>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <sys/time.h>

// struct window_t
// {
//     sf::VertexArray* pixels;
//     sf::RenderWindow* window;
//     int length;
//     int weight;
// };

struct window_t
{
    int color_shift;
    u_int length;
    u_int weigth;
    float zoom;
    float horisontal_shift;
    float vertical_shift;
};

enum win_parametres
{
    WINDOW_LENGTH = 800,
    WINDOW_WEIGHT = 800,
    X_MIDDLE      = 500,
    Y_MIDDLE      = 400,
};

enum color
{
    GREEN_COEF = 10,
    BLUE_COEF  = 15,
    RED_COEF   = 18,
};

enum scan_codes //TODO optimise scan_codes table
{
    ZOOMMORE = 4,  //e
    ZOOMLESS = 16, //q
    ZOOMOUT  = 18, //s
    ZOOMIN   = 22, //w
    COLOR    = 27, //1
    BACK     = 36, //Esc
    LEFT     = 71, //arrows:
    RIGHT    = 72,
    UP       = 73,
    DOWN     = 74,
};

const int MAX_CALCS = 256;

const float ZOOM_CHANGE        = 1.10;
const float CALIBR__ZOOM_PARAM = 100;

const double MAX_RADIUS = 10000;
const double ZOOM_CONST = 4.0;

int PrintFPS              (struct timeval* start, struct timeval* end, int cadrs);

void WindowParamsCtor      (struct window_t* win_param);
void PictureShiftZoom      (struct window_t* win_param, int scan_code);
void PixelsDefault         (sf::VertexArray& pixels, struct window_t* win_param);
void FillingPixels         (sf::VertexArray& pixels, struct window_t* win_param);
void Handler               (sf::RenderWindow& window, sf::View& view, struct window_t* win_param);
void PointAppropriation    (sf::VertexArray& pixels, struct window_t* win_param, int calcs, int x_curr, int y_curr, int index);
void MandelbrotCalculation (sf::VertexArray& pixels, struct window_t* win_param, double x_first, double y_first, int x_curr, int y_curr, int index);
void DrawWindow            (sf::RenderWindow& window, sf::VertexArray& pixels, sf::View& view, struct window_t* win_param, struct timeval* start, struct timeval* end);
#endif

