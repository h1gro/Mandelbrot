#ifndef _MONDELBROT_
#define _MONDELBROT_

#include <stdio.h>
#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>

// struct window_t
// {
//     sf::VertexArray* pixels;
//     sf::RenderWindow* window;
//     int length;
//     int weight;
// };

struct window_t
{
    u_int length;
    u_int weigth;
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
    RED_COEF   = 18,
    GREEN_COEF = 10,
    BLUE_COEF  = 15,
};

const int MAX_CALCS = 256;

const double MAX_RADIUS = 10000;
const double ZOOM_CONST = 4.0;

void PixelsDefault         (sf::VertexArray& pixels, struct window_t* win_param);
void FillingPixels         (sf::VertexArray& pixels, struct window_t* win_param);
void PointAppropriation    (sf::VertexArray& pixels, int calcs, int x_curr, int y_curr, int index);
void DrawWindow            (sf::RenderWindow& window, sf::VertexArray& pixels, struct window_t* win_param);
void MandelbrotCalculation (sf::VertexArray& pixels, double x_first, double y_first, int x_curr, int y_curr, int index);
#endif

