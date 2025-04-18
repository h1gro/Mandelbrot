#ifndef _INTRIN_
#define _INTRIN_

#include <xmmintrin.h>

// struct int_arr_t
// {
//     __m128 x;
//     __m128 y;
//     __m128 y0;
//     __m128 x0;
// };

void FillingIntrin (sf::VertexArray& pixels, struct window_t* win_param);
void BatchProc(sf::VertexArray& pixels, struct window_t* win_param, __m128 x0, __m128 y0, int x_curr, int y_curr);
void BatchMandCalc(sf::VertexArray& pixels, struct window_t* win_param, int* id1, __m128 x0, __m128 y0, __m128 x, __m128 y, int x_curr, int y_curr, int calcs);
//void CalcsArraysMandelbrotIntrin (sf::VertexArray& pixels, struct window_t* win_param, struct int_arr_t* coords, int x_curr, int y_curr);

//int CurrentCalcsIntrin (struct int_arr_t* coords, int i, int* identificator);
#endif
