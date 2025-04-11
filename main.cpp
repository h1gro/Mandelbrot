#include "mandelbrot.h"

int main()
{
    struct window_t win_param = {};
    struct timeval start, end = {};

    WindowParamsCtor(&win_param);
    //init array of pixels and window for picture
    sf::RenderWindow window(sf::VideoMode({win_param.length, win_param.weigth}), "Mandelbrot");
    sf::VertexArray pixels(sf::Points, win_param.length * win_param.weigth);

    sf::View view = window.getDefaultView();

    PixelsDefault(pixels, &win_param);

    DrawWindow(window, pixels, view, &win_param, &start, &end);

    return 0;
}

void WindowParamsCtor(struct window_t* win_param)
{
    assert(win_param);

    win_param->length = WINDOW_LENGTH;
    win_param->weigth = WINDOW_WEIGHT;
    win_param->zoom   = 1.0f;
}
