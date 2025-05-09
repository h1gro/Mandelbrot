#include "Mandelbrot.h"
#include "Intrin.h"
#include "FillingArrays.h"

void FillingIntrin(sf::VertexArray& pixels, struct window_t* win_param)
{
    // assert(&pixels);
    // assert(win_param);

    double x_first = 0, y_first = 0;
    int x_curr = 0, y_curr = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++) //TODO last simd version
    {
        __m128 y0 = _mm_set_ps1(CenterY(y_curr, win_param)); //filling y (4 values)

        for (int x_curr = 0; x_curr < win_param->length - VAL_ARRAY_SIZE; x_curr += VAL_ARRAY_SIZE)
        {
            __m128 x0 = _mm_setr_ps(CenterX(x_curr,     win_param), //filling x (4 values) for current y
                                    CenterX(x_curr + 1, win_param),
                                    CenterX(x_curr + 2, win_param),
                                    CenterX(x_curr + 3, win_param));

            BatchProc(pixels, win_param, x0, y0, x_curr, y_curr); //start processing 4 pairs (x,y)
        }
    }
}

void BatchProc(sf::VertexArray& pixels, struct window_t* win_param, __m128 x0, __m128 y0, int x_curr, int y_curr)
{
    int calcs = 0, id1 = 0;

    __m128 x = x0;
    __m128 y = y0;

    while ((id1 != 0x0F) && (calcs < MAX_CALCS))
    {
        __m128 mul_coef    = _mm_set_ps1(2);
        __m128 circle_size = _mm_set_ps1(MAX_RADIUS);

        __m128 old_x = x;
        x = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(x, x), _mm_mul_ps(y, y)), x0);
        y = _mm_add_ps(_mm_mul_ps(_mm_mul_ps(old_x, y), mul_coef), y0);

        int out_mask = _mm_movemask_ps(_mm_cmpge_ps(_mm_add_ps(_mm_mul_ps(x, x), _mm_mul_ps(y, y)), circle_size));
        int rezult   = out_mask & (~id1);

        if (rezult)
        {
            for (int i = 0; i < VAL_ARRAY_SIZE; i++)
            {
                if ((rezult & (1 << i)))
                {
                    PointAppropriation(pixels, win_param, calcs, x_curr + i, y_curr);
                    id1 |= (1 << i);
                }
            }
        }
        calcs++;
    }
}

int BatchMandCalc(sf::VertexArray& pixels, struct window_t* win_param, int* id1, __m128 x0, __m128 y0, __m128 x, __m128 y, int x_curr, int y_curr, int calcs)
{
    __m128 mul_coef    = _mm_set_ps1(2);
    __m128 circle_size = _mm_set_ps1(MAX_RADIUS);

    __m128 old_x = x;
    x = _mm_add_ps(_mm_sub_ps(_mm_mul_ps(x, x), _mm_mul_ps(y, y)), x0);
    y = _mm_add_ps(_mm_mul_ps(_mm_mul_ps(old_x, y), mul_coef), y0);

    return _mm_movemask_ps(_mm_cmpge_ps(_mm_add_ps(_mm_mul_ps(x, x), _mm_mul_ps(y, y)), circle_size));
}

