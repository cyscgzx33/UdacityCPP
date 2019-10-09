#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class Window
{
  public:
    Window(const std::string& t, int w, int h);
    ~Window();

    inline bool isClosed() const { return closed_; }
    // check if any events is polled within the window created
    void pollEvents();
  private:
    std::string title_;
    int width_;
    int height_;
    bool closed_ = false;
    SDL_Window* window_ = nullptr;

    // init SDL
    bool Initialize();
};

#endif /* WINDOW_H*/