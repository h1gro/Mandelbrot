#include "mandelbrot.h"
#include "FillingArrays.h"

void FillingArrays(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    //double x_first = 0, y_first = 0;

    //, xi[VAL_ARRAY_SIZE] = {};//, yi[VAL_ARRAY_SIZE] = {};
    int index = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++)
    {
        double y0[VAL_ARRAY_SIZE] = {};
        double y_first = (y_curr - Y_MIDDLE) / (win_param->weigth / 4.0);
        //y_first = (y_curr - Y_MIDDLE) * ZOOM_CONST / (win_param->weigth * win_param->zoom) + win_param->vertical_shift;
        for (int i = 0; i < VAL_ARRAY_SIZE; i++)
        {
            y0[i] = y_first;
            //y0[i] = y_first;
        }

        for (int x_curr = 0; x_curr < win_param->length; x_curr += VAL_ARRAY_SIZE)
        {
            double x0[VAL_ARRAY_SIZE] = {};
            for (int j = 0; (j < VAL_ARRAY_SIZE) && (x_curr + j < win_param->length); j++) {
                //xi[j] = CenterX(x_curr + j, win_param); x0[j] = xi[j];
                x0[j] = (x_curr + j - X_MIDDLE) / (win_param->length / 4.0);
            }

            //index = x_curr + y_curr * win_param->length;

            CalcsArraysMandelbrot(pixels, win_param, x_curr, y_curr, x0, y0);
        }
    }
}

void CalcsArraysMandelbrot(sf::VertexArray& pixels, struct window_t* win_param, int x_curr, int y_curr, double* x0, double* y0)
{
    assert(&pixels);
    assert(win_param);

    int identificator = 0;
    int calcs = 0;
    double x[VAL_ARRAY_SIZE] = {}, y[VAL_ARRAY_SIZE] = {};
    double old_x = 0;

    for(int i = 0; i < VAL_ARRAY_SIZE; i++)
    {
        x[i] = x0[i];
        y[i] = y0[i];
    }

    while ((identificator != 0x0F) && (calcs < MAX_CALCS))
    {
        for (int i = 0; i < VAL_ARRAY_SIZE; i++)
        {
            if (!(identificator & (1 << i)))
            {
                //flag = CurrentCalcs(xi, yi, x0, y0, i, &identificator);
                old_x = x[i];

                x[i] = x[i] * x[i] - y[i] * y[i] + x0[i];
                y[i] = 2 * old_x * y[i]          + y0[i];

                if (x[i] * x[i] + y[i] * y[i] > MAX_RADIUS)
                {
                    identificator |= (1 << i);

                    int red   = (calcs + win_param->color_shift) * RED_COEF   % MAX_CALCS;
                    int green = (calcs + win_param->color_shift) * GREEN_COEF % MAX_CALCS;
                    int blue  = (calcs + win_param->color_shift) * BLUE_COEF  % MAX_CALCS;

                    int index = x_curr + i + y_curr * win_param->length;

                    pixels[index].position = sf::Vector2f (x_curr + i, y_curr);
                    pixels[index].color    = sf::Color    (red, green, blue);
                }
            }
        }
        calcs++;
    }
}

int CurrentCalcs (double* xi, double* yi, double* x0, double* y0, int i, int* identificator)
{
    int flag = 0;
    double old_x   = 0;

    old_x = xi[i];
    xi[i] = xi[i] * xi[i] - yi[i] * yi[i] + x0[i];
    yi[i] = 2 * old_x * yi[i]             + y0[i];

    if (xi[i] * xi[i] + yi[i] * yi[i] > MAX_RADIUS)
    {
        flag = 1;
        *identificator |= (1 << i);
        fprintf(stderr, "id = %b\n", *identificator);
    }

    return flag;
}

double CenterX(int x, struct window_t* win_param)
{
    return (x - X_MIDDLE) * ZOOM_CONST / (win_param->length * win_param->zoom) + win_param->horisontal_shift;
}
