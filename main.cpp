#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>

#include "mandelbrot.h"

int main()
{
    //init array of pixels and window for picture
    sf::VertexArray pixels(sf::Points, WINDOW_LENGTH * WINDOW_WEIGHT); //type Points!!!
    sf::RenderWindow window(sf::VideoMode({WINDOW_LENGTH, WINDOW_WEIGHT}), "Mandelbrot");
    window.setVerticalSyncEnabled(true);
    PixelsDefault(pixels);
    //FillingPixels(pixels);
    DrawWindow(window, pixels);

    return 0;
}

void FillingPixels(sf::VertexArray& pixels)
{
    assert(&pixels);

    double y0 = 0, x0 = 0;
    int index = 0;

    for (int yi = 0; yi < WINDOW_WEIGHT; yi++)
    {
        y0 = (yi - Y0) / (WINDOW_WEIGHT / 4.0);
        for (int xi = 0; xi < WINDOW_LENGTH; xi++)
        {
            x0 = (xi - X0) / (WINDOW_LENGTH / 4.0);

            index = xi + yi * WINDOW_LENGTH;

            MandelbrotCalculation(pixels, x0, y0, xi, yi, index);
        }
    }
}

void MandelbrotCalculation(sf::VertexArray& pixels, double x0, double y0, int xi, int yi, int index)
{
    assert(&pixels);
    int calcs = 0;
    double old_x = 0;
    double x = x0, y = y0;

    while ((x * x + y * y <= 10000) && (calcs < MAX_CALCS))
    {
        old_x = x;
        x = x * x - y * y + x0;
        y = 2 * old_x * y + y0;
        calcs++;
    }

    int index = xi + yi * WINDOW_LENGTH;
    pixels[index].position = sf::Vector2f (xi, yi);
    pixels[index].color    = sf::Color(calcs * 18 % MAX_CALCS, calcs * 10 % MAX_CALCS, calcs * 15 % MAX_CALCS);
}

void PixelsDefault(sf::VertexArray& pixels)
{
    assert(&pixels);

    int i = 0;

    for (int y = 0; y < WINDOW_WEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_LENGTH; x++)
        {
            i = x + y * WINDOW_LENGTH;
            pixels[i].position = sf::Vector2f(x, y);
            pixels[i].color    = sf::Color::Black;
        }
    }
}

void DrawWindow(sf::RenderWindow& window, sf::VertexArray& pixels)
{
    assert(&pixels);
    assert(&window);

    while (window.isOpen()) //while window is open
    {
        sf::Event event; //don't need init!
        while (window.pollEvent(event)) //pollEvent take (событие!) andf out it on the argument - event
        {
            if (event.type == sf::Event::Closed)
            {
                window.close(); //close the window
            }
            else if (event.type == false)
            {
                perror("Error!\n");
            }
        }

        PixelsDefault(pixels);//black all

        FillingPixels(pixels);

        window.clear(); //clear content of the window and draw all window in black
        window.draw(pixels);
        window.display();
    }
}
