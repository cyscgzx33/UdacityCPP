#include "window.h"
#include <iostream>

Window::Window(const std::string& t, int w, int h) : title_(t), width_(w), height_(h) 
{
    if ( Initialize() == false )
    {
        // if successfully initialized, close the window
        closed_ = true;
    }
}

Window::~Window()
{
    // destroy window
    SDL_DestroyWindow(window_);
    // quit
    SDL_Quit();
}


bool Window::Initialize()
{
    // if SDL doesn't init
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        std::cerr << "Failed to initialize SDL.\n";
        return 0;
    }
    else
        std::cout << "Successful to initialize SDL!\n";

    // create window within SDL library
    window_ = SDL_CreateWindow(
        title_.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width_, height_,
        0
    );

    // check if window_ is created successfully
    if ( window_ == nullptr )
    {
        std::cerr << "Failed to create window.\n";
        return 0;
    }

    // Initialize successfully
    return true;
}

void Window::pollEvents()
{
    SDL_Event event;

    if ( SDL_PollEvent(&event) ) // it's looking for a pointer
    {
        switch ( event.type )
        {
        case SDL_QUIT: // SDL_QUIT is an enum, represents the "X" button of the window
                       // i.e., if we click the "X" button, the window closes
            closed_ = true;
            break;
        
        default: // the above is the only thing we're going to do now
            break;
        }
    }
}