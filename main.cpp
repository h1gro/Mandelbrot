#include "mandelbrot.h"

int main()
{
    struct window_t win_param = {};

    win_param.length = WINDOW_LENGTH;
    win_param.weigth = WINDOW_WEIGHT;

    //init array of pixels and window for picture
    sf::RenderWindow window(sf::VideoMode({win_param.length, win_param.weigth}), "Mandelbrot");
    sf::VertexArray pixels(sf::Points, win_param.length * win_param.weigth);

    PixelsDefault(pixels, &win_param);

    DrawWindow(window, pixels, &win_param);

    return 0;
}

void FillingPixels(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    double y_first = 0, x_first = 0;
    int index = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++)
    {
        y_first = (y_curr - Y_MIDDLE) / (win_param->weigth / ZOOM_CONST);

        for (int x_curr = 0; x_curr < win_param->length; x_curr++)
        {
            x_first = (x_curr - X_MIDDLE) / (win_param->length / ZOOM_CONST);

            index = x_curr + y_curr * win_param->length;

            MandelbrotCalculation(pixels, x_first, y_first, x_curr, y_curr, index);
        }
    }
}

void MandelbrotCalculation(sf::VertexArray& pixels, double x_first, double y_first, int x_curr, int y_curr, int index)
{
    assert(&pixels);
    int calcs = 0;
    double x = x_first, y = y_first, old_x = 0;

    while ((x * x + y * y <= MAX_RADIUS) && (calcs < MAX_CALCS))
    {
        old_x = x;
        x = x * x - y * y + x_first;
        y = 2 * old_x * y + y_first;
        calcs++;
    }

    PointAppropriation(pixels, calcs, x_curr, y_curr, index);
}

void PointAppropriation(sf::VertexArray& pixels, int calcs, int x_curr, int y_curr, int index)
{
    assert(&pixels);

    int red   = calcs * RED_COEF   % MAX_CALCS;
    int green = calcs * GREEN_COEF % MAX_CALCS;
    int blue  = calcs * BLUE_COEF  % MAX_CALCS;

    pixels[index].position = sf::Vector2f (x_curr, y_curr);
    pixels[index].color    = sf::Color (red, green, blue);
}

void PixelsDefault(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    int index = 0;

    for (int y = 0; y < win_param->weigth; y++)
    {
        for (int x = 0; x < win_param->length; x++)
        {
            index = x + y * win_param->length;
            pixels[index].position = sf::Vector2f(x, y);
            pixels[index].color    = sf::Color::Black;
        }
    }
}

void DrawWindow(sf::RenderWindow& window, sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(&window);
    assert(win_param);

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

        //PixelsDefault(pixels);//black all

        FillingPixels(pixels, win_param);

        window.clear(); //clear content of the window and draw all window in black
        window.draw(pixels);
        window.display();
    }
}
