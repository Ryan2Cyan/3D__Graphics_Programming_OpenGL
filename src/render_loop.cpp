#include "render_loop.h"

void sdl_loop(SDL_Window* window) {

    SDL_Event event;
    bool running = true;

    while (running) {
        // Change color of window:
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);

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