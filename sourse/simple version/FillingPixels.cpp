#include "mandelbrot.h"
#include "FillingArrays.h"

void FillingPixels(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    double y_first = 0, x_first = 0;
    int index = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++)
    {
        y_first = (y_curr - Y_MIDDLE) * ZOOM_CONST / (win_param->weigth * win_param->zoom) + win_param->vertical_shift;

        for (int x_curr = 0; x_curr < win_param->length; x_curr++)
        {
            x_first = (x_curr - X_MIDDLE) * ZOOM_CONST / (win_param->length * win_param->zoom) + win_param->horisontal_shift;

            index = x_curr + y_curr * win_param->length;

            MandelbrotCalculation(pixels, win_param, x_first, y_first, x_curr, y_curr);
        }
    }
}

void MandelbrotCalculation(sf::VertexArray& pixels, struct window_t* win_param, double x_first, double y_first, int x_curr, int y_curr)
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

    PointAppropriation(pixels, win_param, calcs, x_curr, y_curr);
}

void PointAppropriation(sf::VertexArray& pixels, struct window_t* win_param, int calcs, int x_curr, int y_curr)
{
    assert(&pixels);
    assert(win_param);

    int red   = (calcs + win_param->color_shift) * RED_COEF   % MAX_CALCS;
    int green = (calcs + win_param->color_shift) * GREEN_COEF % MAX_CALCS;
    int blue  = (calcs + win_param->color_shift) * BLUE_COEF  % MAX_CALCS;

    int index = x_curr + y_curr * win_param->length;

    pixels[index].position = sf::Vector2f (x_curr, y_curr);
    pixels[index].color    = sf::Color    (red, green, blue);
}


