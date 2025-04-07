#ifndef _MONDELBROT_
#define _MONDELBROT_

#include <stdio.h>
#include <assert.h>

const int WINDOW_LENGTH = 800;
const int WINDOW_WEIGHT = 600;

void DrawWindow    (sf::RenderWindow& window, sf::VertexArray& pixels);
void PixelsDefault (sf::VertexArray& pixels);
void FillingPixels (sf::VertexArray& pixels);

#endif

