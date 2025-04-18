#include "mandelbrot.h"

int main(int argc, char* argv[])
{
    struct window_t win_param = {};
    struct timeval start, end = {};

    modes users_mode = DefineMode(argv);

    if (users_mode == ERROR) {return 1;}

    WindowParamsCtor(&win_param);
    //init array of pixels and window for picture
    sf::RenderWindow window(sf::VideoMode({win_param.length, win_param.weigth}), "Mandelbrot");
    sf::VertexArray pixels(sf::Points, win_param.length * win_param.weigth);

    sf::View view = window.getDefaultView();

    PixelsDefault(pixels, &win_param);
    printf("ну тут же я был\n");
    DrawWindow(window, pixels, view, &win_param, &start, &end, users_mode);

    return 0;
}

modes DefineMode(char* argv[])
{
    assert(argv);

    if (!strcmp(argv[1], "simple"))
    {
        return SIMPLE;
    }

    else if (!strcmp(argv[1], "array"))
    {
        return ARRAY;
    }

    else
    {
        perror("error mode!\n");
        return ERROR;
    }
}

void WindowParamsCtor(struct window_t* win_param)
{
    assert(win_param);

    win_param->length = WINDOW_LENGTH;
    win_param->weigth = WINDOW_WEIGHT;
    win_param->zoom   = 1.0f;
}
