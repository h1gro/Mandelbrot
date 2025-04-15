#include "mandelbrot.h"
#include "FillingArrays.h"

void DrawWindow(sf::RenderWindow& window, sf::VertexArray& pixels, sf::View& view, struct window_t* win_param, struct timeval* start, struct timeval* end, modes users_mode)
{
    assert(&pixels);
    assert(&window);
    assert(&view);
    assert(start);
    assert(win_param);

    int current_number_of_cadrs = 0;

    //TODO rdtsc (частота тиков проца, её нужно будет уножить на тактовую частоту) - способ расчёта времени
    while (window.isOpen()) //while window is open
    {
        gettimeofday(start, NULL); //start - recorded the current time of starting drawing a mandelbrote

        current_number_of_cadrs++;

        Handler(window, view, win_param); //processing event

        PixelsDefault(pixels, win_param); //black all

        StartUsersMode(pixels, win_param, users_mode);

        gettimeofday(end, NULL); //end - recorded the current time of ending drawing a mandelbrote
        //and after that - measure time of drawing
        current_number_of_cadrs = PrintFPS(start, end, current_number_of_cadrs);

        window.clear(); //clear content of the window and draw all window in black
        window.draw(pixels);
        window.display();
    }
}

//TODO git repo in include, src, examples, build и т.д. .gitignore
//TODO -O3 -O0 -O2 in make
void PictureShiftZoom(struct window_t* win_param, int scan_code)
{
    float speed_of_the_shift = 3.0f;

    switch (scan_code)
    {
        case LEFT:
        {
            win_param->horisontal_shift -= speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case RIGHT:
        {
            win_param->horisontal_shift += speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case UP:
        {
            win_param->vertical_shift -= speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case DOWN:
        {
            win_param->vertical_shift += speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case ZOOMIN:
        {
            win_param->zoom += ZOOM_CHANGE;
            break;
        }

        case ZOOMOUT:
        {
            win_param->zoom -= ZOOM_CHANGE;
            break;
        }

        case ZOOMMORE:
        {
            win_param->zoom *= exp(sqrt(speed_of_the_shift));
            break;
        }

        case ZOOMLESS:
        {
            win_param->zoom /= exp(sqrt(speed_of_the_shift));
            break;
        }

        case BACK:
        {
            win_param->horisontal_shift = 0;
            win_param->vertical_shift   = 0;
            win_param->zoom             = 1;

            break;
        }

        case COLOR:
        {
            win_param->color_shift++;
            break;
        }
    }
}

void StartUsersMode(sf::VertexArray& pixels, struct window_t* win_param, modes users_mode)
{
    assert(&pixels);
    assert(win_param);

    switch (users_mode)
    {
        case SIMPLE:
        {
            FillingPixels(pixels, win_param);
            break;
        }

        case ARRAY:
        {
            FillingArrays(pixels, win_param);
            break;
        }

        default:    perror("unexpectable value of users mode"
                           "(error somewhere in appropriation users_mode)\n");
    }
}


void Handler(sf::RenderWindow& window, sf::View& view, struct window_t* win_param)
{
    assert(&window);
    assert(&view);
    assert(win_param);

    sf::Event event; //don't need init!

    while (window.pollEvent(event)) //pollEvent take (событие!) andf out it on the argument - event
    {
        if (event.type == sf::Event::Closed)
        {
            window.close(); //close the window
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            PictureShiftZoom(win_param, event.key.code);
            window.setView(view);
        }

        else if (event.type == false)
        {
            perror("Error!\n");
        }
    }
}

void PixelsDefault(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    int index = 0;

    for (int y = 0; y < win_param->weigth; y++)
    {
        for (int x = 0; x < win_param->length; x++)
        {
            index = x + y * win_param->length;

            pixels[index].position = sf::Vector2f(x, y);
            pixels[index].color    = sf::Color::Black;
        }
    }
}


int PrintFPS(struct timeval* start, struct timeval* end, int cadrs)
{
    assert(start);
    assert(end);

    long sec  = end->tv_sec - start->tv_sec;
    long msec = end->tv_usec - start->tv_usec;
    printf("FPS: %5lf\n", cadrs / (double)(sec + msec * 1E-6));

    return 0;
}
