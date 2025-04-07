#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "mandelbrot.h"

int main()
{
    //init array of pixels and window for picture
    sf::VertexArray pixels(sf::Points, WINDOW_LENGTH * WINDOW_WEIGHT); //type Points!!!
    sf::RenderWindow window(sf::VideoMode({WINDOW_LENGTH, WINDOW_WEIGHT}), "Mandelbrot");

    PixelsDefault(pixels);
    FillingPixels(pixels);
    DrawWindow(window, pixels);

    return 0;
}

void FillingPixels(sf::VertexArray& pixels)
{
    assert(&pixels);

    int i = 0;

    for (int y = 0; y < WINDOW_WEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_LENGTH; x++)
        {
            int i = x + y * WINDOW_LENGTH;
            if (pixels[i].position.x * pixels[i].position.x + pixels[i].position.y * pixels[i].position.y <= 10000)
            {
                pixels[i].color = sf::Color::Yellow;
            }
        }
    }
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
    assert(&window);
    assert(&pixels);

    FillingPixels(pixels);

    while (window.isOpen()) //while window is open
    {
        FillingPixels(pixels);

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

        window.clear(); //clear content of the window and draw all window in black
        window.draw(pixels);
        window.display();
    }
}
