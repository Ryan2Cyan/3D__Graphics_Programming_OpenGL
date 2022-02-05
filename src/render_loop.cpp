#include "render_loop.h"

void sdl_loop(SDL_Window* window) {

    SDL_Event event;
    bool running = true;

    while (running) {
        // Change color of window:
        change_window_colour(1.0f, 0.0f, 0.0f, 1.0f, window);

        while (SDL_PollEvent(&event) != 0) {  // Check for user input
            switch (event.type)
            {
            case SDL_QUIT:                    // Quit application
                running = false;
                break;
            default:
                break;
            }
        }
    }
}

