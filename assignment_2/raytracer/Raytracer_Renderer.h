#include <SDL2/SDL.h>
#include <iostream>
#include <string>
class Raytracer_Renderer {
    private:
        SDL_Window* window = nullptr;
        SDL_Texture* texture = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Event event;
        bool quit = false;
        int window_width;
        int window_height;
        char* title;
    public:
        Raytracer_Renderer(int window_width = 640, int window_height = 480, char* title = "Raytracer");

        bool init();
        bool render();
        void Event();
        bool exit();
};

