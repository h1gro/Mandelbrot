#include "mandelbrot.h"
#include "FillingArrays.h"

void FillingArrays(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    double x_first = 0, y_first = 0;

    double xi[VAL_ARRAY_SIZE] = {};
    double yi[VAL_ARRAY_SIZE] = {};
    int index = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++)
    {
        y_first = (y_curr - Y_MIDDLE) * ZOOM_CONST / (win_param->weigth * win_param->zoom) + win_param->vertical_shift;

        for (int i = 0; i < VAL_ARRAY_SIZE; i++) {yi[i] = y_first;}

        for (int x_curr = 0; x_curr < win_param->length; x_curr += VAL_ARRAY_SIZE)
        {
            //x_first  = (x_curr - X_MIDDLE) * ZOOM_CONST / (win_param->length * win_param->zoom) + win_param->horisontal_shift;
            for (int j = 0; (j < VAL_ARRAY_SIZE) && (x_curr + j < win_param->length); j++) {xi[j] = CenterX(x_curr + j, win_param);}

            index = x_curr + y_curr * win_param->length;

            CalcsArraysMandelbrot(pixels, win_param, x_curr, y_curr, xi, yi, index);
        }
    }
}

void CalcsArraysMandelbrot(sf::VertexArray& pixels, struct window_t* win_param, int x_curr, int y_curr, double* xi, double* yi, int index)
{
    assert(&pixels);
    assert(win_param);

    int calcs = 0;
    double old_x = 0, x_first = 0, y_first = 0;

    for (int i = 0; i < VAL_ARRAY_SIZE; i++)
    {
        x_first = xi[i]; //TODO xi[5] - its the first varuyable for current i: 0 <= i < 4
        y_first = yi[i];

        while ((xi[i] * xi[i] + yi[i] * yi[i] <= MAX_RADIUS) && (calcs < MAX_CALCS))
        {
            old_x = xi[i];
            xi[i] = xi[i] * xi[i] - yi[i] * yi[i] + x_first;
            yi[i] = 2 * old_x * yi[i]             + y_first;
            calcs++;
        }

        //pixels[index].position = sf::Vector2f (x_curr, y_curr);
        //pixels[index].color    = sf::Color ((calcs + win_param->color_shift)*7/123, (calcs + win_param->color_shift)* 5/217, (calcs + win_param->color_shift)* 4/876);
        PointAppropriation(pixels, win_param, calcs, x_curr, y_curr, index);

        x_curr++;
        index++;
        calcs = 0;
    }
}

double CenterX(int x, struct window_t* win_param)
{
    return (x - X_MIDDLE) * ZOOM_CONST / (win_param->length * win_param->zoom) + win_param->horisontal_shift;
}
