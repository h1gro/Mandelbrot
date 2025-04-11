#include "mandelbrot.h"

void FillingPixels(sf::VertexArray& pixels, struct window_t* win_param)
{
    assert(&pixels);
    assert(win_param);

    double y_first = 0, x_first = 0;
    int index = 0;

    for (int y_curr = 0; y_curr < win_param->weigth; y_curr++)
    {
        y_first = (y_curr - Y_MIDDLE) * ZOOM_CONST / (win_param->weigth * win_param->zoom) + win_param->vertical_shift;

        for (int x_curr = 0; x_curr < win_param->length; x_curr++)
        {
            x_first = (x_curr - X_MIDDLE) * ZOOM_CONST / (win_param->length * win_param->zoom) + win_param->horisontal_shift;

            index = x_curr + y_curr * win_param->length;

            MandelbrotCalculation(pixels, win_param, x_first, y_first, x_curr, y_curr, index);
        }
    }
}

void MandelbrotCalculation(sf::VertexArray& pixels, struct window_t* win_param, double x_first, double y_first, int x_curr, int y_curr, int index)
{
    assert(&pixels);
    int calcs = 0;
    double x = x_first, y = y_first, old_x = 0;

    while ((x * x + y * y <= MAX_RADIUS) && (calcs < MAX_CALCS))
    {
        old_x = x;
        x = x * x - y * y + x_first;
        y = 2 * old_x * y + y_first;
        calcs++;
    }

    PointAppropriation(pixels, win_param, calcs, x_curr, y_curr, index);
}

void PointAppropriation(sf::VertexArray& pixels, struct window_t* win_param, int calcs, int x_curr, int y_curr, int index)
{
    assert(&pixels);

    int red   = (calcs + win_param->color_shift) * RED_COEF   % MAX_CALCS;
    int green = (calcs + win_param->color_shift) * GREEN_COEF % MAX_CALCS;
    int blue  = (calcs + win_param->color_shift) * BLUE_COEF  % MAX_CALCS;

    pixels[index].position = sf::Vector2f (x_curr, y_curr);
    pixels[index].color    = sf::Color (red, green, blue);
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

void PictureShiftZoom(struct window_t* win_param, int scan_code)
{
    float speed_of_the_shift = 3.0f;

    switch (scan_code)
    {
        case LEFT:
        {
            //view.move(-speed_of_the_shift, 0);
            win_param->horisontal_shift -= speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case RIGHT:
        {
            //view.move(speed_of_the_shift, 0);
            win_param->horisontal_shift += speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case UP:
        {
            //view.move(0, -speed_of_the_shift);
            win_param->vertical_shift -= speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case DOWN:
        {
            //view.move(0, speed_of_the_shift);
            win_param->vertical_shift += speed_of_the_shift / (CALIBR__ZOOM_PARAM * win_param->zoom);
            break;
        }

        case ZOOMIN:
        {
            win_param->zoom += ZOOM_CHANGE;

            // win_param->horisontal_shift /= win_param->zoom;
            // win_param->vertical_shift   /= win_param->zoom;
            // view.move(0, 0);
            break;
        }

        case ZOOMOUT:
        {
            win_param->zoom -= ZOOM_CHANGE;

            //am i need it?
            //if (win_param->zoom < 0) {win_param->zoom = 1;}

            // win_param->horisontal_shift /= sqrt(win_param->zoom);
            // win_param->vertical_shift   /= sqrt(win_param->zoom);
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

void DrawWindow(sf::RenderWindow& window, sf::VertexArray& pixels, sf::View& view, struct window_t* win_param, struct timeval* start, struct timeval* end)
{
    assert(&pixels);
    assert(&window);
    assert(&view);
    assert(start);
    assert(win_param);

    int current_number_of_cadrs = 0;

    while (window.isOpen()) //while window is open
    {
        gettimeofday(start, NULL);

        current_number_of_cadrs++;

        Handler(window, view, win_param);

        PixelsDefault(pixels, win_param); //black all

        FillingPixels(pixels, win_param);

        gettimeofday(end, NULL);
        current_number_of_cadrs = PrintFPS(start, end, current_number_of_cadrs);

        window.clear(); //clear content of the window and draw all window in black
        window.draw(pixels);
        window.display();
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

int PrintFPS(struct timeval* start, struct timeval* end, int cadrs)
{
    assert(start);
    assert(end);

    long sec  = end->tv_sec - start->tv_sec;
    long msec = end->tv_usec - start->tv_usec;
    printf("FPS: %5lf\n", cadrs / (double)(sec + msec * 1E-6));

    return 0;
}
