#ifndef _FILLING_ARRAYS_
#define _FILLING_ARRAYS_

const int VAL_ARRAY_SIZE = 4;

const int MAGIC_CONST_RED   = 5;
const int MAGIC_CONST_GREEN = 10;
const int MAGIC_CONST_BLUE  = 15;

double CenterX             (int x, struct window_t* win_param);

void FillingArrays         (sf::VertexArray& pixels, struct window_t* win_param);
void CalcsArraysMandelbrot (sf::VertexArray& pixels, struct window_t* win_param, int x_curr, int y_curr, double* x, double* y, int index);

#endif
