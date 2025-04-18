#ifndef _FILLING_ARRAYS_
#define _FILLING_ARRAYS_

struct arrays_t
{
    double x [VAL_ARRAY_SIZE]; //TODO че за бретто
    double y [VAL_ARRAY_SIZE];
    double y0[VAL_ARRAY_SIZE];
    double x0[VAL_ARRAY_SIZE];
};


const int MAGIC_CONST_RED   = 5;
const int MAGIC_CONST_GREEN = 10;
const int MAGIC_CONST_BLUE  = 15;

double CenterX             (int x, struct window_t* win_param);
double CenterY             (int y, struct window_t* win_param);

int CurrentCalcs           (struct arrays_t* coords, int i, int* identificator);
void FillingArrays         (sf::VertexArray& pixels, struct window_t* win_param);
void CalcsArraysMandelbrot (sf::VertexArray& pixels, struct window_t* win_param, struct arrays_t* coords, int x_curr, int y_curr);

#endif
