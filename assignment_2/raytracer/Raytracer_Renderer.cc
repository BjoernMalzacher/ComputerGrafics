#undef main
#include "Raytracer_Renderer.h"

Raytracer_Renderer::Raytracer_Renderer(int window_width, int window_height, char* title)
{
    this->window_width = window_width;
    this->window_height = window_height;
    this->title = title;
}

bool Raytracer_Renderer::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }
    /* Clean up on exit */
    atexit(SDL_Quit);

    /* Create a window */
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
        return false;
    }
    /*create a texture */
    //texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC,640, 480);
   /* if (texture == NULL)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        return false;
    }
    /* Create a renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
bool Raytracer_Renderer::paintPixel(){
     
    return false;
}

bool Raytracer_Renderer::render()
{   
    int i =0;
for (int y = 0; y < this->window_height; y++) {
	for (int x = 0; x < this->window_width; x++) {
        if(i%8 == 0){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawPoint(renderer, x, y);
            i++;
        }
        else{
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawPoint(renderer, x, y);
            i++;
        }
	}
}
   while (!quit) {
        Event();
   
        SDL_RenderPresent(renderer);
   } 
    
    return true;
}
void Raytracer_Renderer::Event()
{
    while (SDL_PollEvent(&this->event)) {
		switch (event.type) {
		case SDL_QUIT:
			this->quit = true;
			break;
            }
        
	}
}

bool Raytracer_Renderer::exit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return true;
}