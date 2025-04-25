#include "Mandelbrot.h"
#include "FillingArrays.h"

void FillingArrays(sf::VertexArray& pixels, struct window_t* win_param)
{
    // assert(&pixels);
    // assert(win_param);

    struct arrays_t coords = {};

    double x_first = 0, y_first = 0;
    int index = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++)
    {
        coords.y0[VAL_ARRAY_SIZE] = {};
        y_first = CenterY(y_curr, win_param);

        for (int i = 0; i < VAL_ARRAY_SIZE; i++)
        {
            coords.y0[i] = y_first;
        }

        for (int x_curr = 0; x_curr < win_param->length; x_curr += VAL_ARRAY_SIZE)
        {
            coords.x0[VAL_ARRAY_SIZE] = {};

            for (int j = 0; (j < VAL_ARRAY_SIZE) && (x_curr + j < win_param->length); j++)
            {
                coords.x0[j] = CenterX(x_curr + j, win_param);
            }

            CalcsArraysMandelbrot(pixels, win_param, &coords, x_curr, y_curr);
        }
    }
}

void CalcsArraysMandelbrot(sf::VertexArray& pixels, struct window_t* win_param, struct arrays_t* coords, int x_curr, int y_curr)
{
    // assert(&pixels);
    // assert(win_param);

    int identificator = 0, calcs = 0, flag = 0;
    double old_x = 0;

    for(int i = 0; i < VAL_ARRAY_SIZE; i++)
    {
        coords->x[i] = coords->x0[i];
        coords->y[i] = coords->y0[i];
    }

    while ((identificator != 0x0F) && (calcs < MAX_CALCS))
    {
        for (int i = 0; i < VAL_ARRAY_SIZE; i++)
        {
            if (!(identificator & (1 << i)))
            {
                flag = CurrentCalcs(coords, i, &identificator);

                if (flag == 1)
                {
                    PointAppropriation(pixels, win_param, calcs, x_curr + i, y_curr);
                }
            }
        }
        calcs++;
    }
}

int CurrentCalcs (struct arrays_t* coords, int i, int* identificator)
{
    int flag = 0;
    double old_x = 0;

    old_x = coords->x[i];
    coords->x[i] = coords->x[i] * coords->x[i] - coords->y[i] * coords->y[i] + coords->x0[i];
    coords->y[i] = 2 * old_x * coords->y[i]                                  + coords->y0[i];

    if (coords->x[i] * coords->x[i] + coords->y[i] * coords->y[i] > MAX_RADIUS)
    {
        flag = 1;
        *identificator |= (1 << i);
    }

    return flag;
}

double CenterX(int x, struct window_t* win_param)
{
    return (x - X_MIDDLE) * ZOOM_CONST / (win_param->length * win_param->zoom) + win_param->horisontal_shift;
}

double CenterY(int y, struct window_t* win_param)
{
    return (y - Y_MIDDLE) * ZOOM_CONST / (win_param->weigth * win_param->zoom) + win_param->vertical_shift;
}
