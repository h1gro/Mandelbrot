#ifndef _MONDELBROT_
#define _MONDELBROT_

#include <stdio.h>
#include <assert.h>

const int WINDOW_LENGTH = 800;
const int WINDOW_WEIGHT = 600;

const int X0 = 500;
const int Y0 = 300;
const int MAX_CALCS = 256;

void DrawWindow            (sf::RenderWindow& window, sf::VertexArray& pixels);
void PixelsDefault         (sf::VertexArray& pixels);
void FillingPixels         (sf::VertexArray& pixels);

void MandelbrotCalculation(sf::VertexArray& pixels, double x0, double y0, int xi, int yi);
#endif

