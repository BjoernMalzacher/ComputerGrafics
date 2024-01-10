#undef main
#include "Raytracer_Renderer.h"

Raytracer_Renderer::Raytracer_Renderer(int window_width, int window_height, char *title)
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
     /* Create a renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
bool Raytracer_Renderer::render(Screen *screen)
{
    
    for (int y = 0; y < this->window_height; y++)
    {
        for (int x = 0; x < this->window_width; x++)
        {
           SDL_SetRenderDrawColor(renderer, screen->getPixel(x, y).getR() * 255, screen->getPixel(x, y).getG() * 255, screen->getPixel(x, y).getB() * 255, 0);
         /*
            std::cout << " red: " << screen->getPixel(x, y).getR();
            std::cout << " green: " << screen->getPixel(x, y).getG();
            std::cout << " blue: " << screen->getPixel(x, y).getB();
            std::cout << " x: " << x;
            std::cout << " y: " << y << std::endl;
            */
            SDL_RenderDrawPoint(renderer, x, y);
           
        }
    }
    while (!quit)
    {
        Event();
        SDL_RenderPresent(renderer);
    }

    return true;
}
int Raytracer_Renderer::getWidth()
{
    return this->window_width;
}
int Raytracer_Renderer::getHeight()
{
    return this->window_height;
}
void Raytracer_Renderer::Event()
{
    while (SDL_PollEvent(&this->event))
    {
        switch (event.type)
        {
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
// -- Color --
double Color::getR()
{
    return this->r;
}
double Color::getG()
{
    return this->g;
}
double Color::getB()
{
    return this->b;
}
// -- Color end --
// --Material --
// -- Material end --
// -- Screen --
void Screen::setPixel(int x, int y, Color c)
{
    this->pixels[y * this->width + x] = c;
}
void Screen::clearScreen(Color c)
{
    for (int i = 0; i < this->width * this->height; i++)
    {
        this->pixels[i] = c;
    }
}
Color Screen::getPixel(int x, int y)
{
    return this->pixels[y * this->width + x];
}
int Screen::getWidth()
{
    return this->width;
}
int Screen::getHeight()
{
    return this->height;
}
// -- Screen end --
// -- Camera --
Camera::Camera(Vector3df eye, Vector3df upguide, Vector3df target, double fov, double aspect_ratio) : eye(eye), forward(target - eye), right(forward.cross_product(upguide)), up(right.cross_product(forward))
{
    this->height = tan(fov);
    this->width = height * aspect_ratio;
    this->forward.normalize();
    this->right.normalize();
    this->up.normalize();
}
Ray3df Camera::makeRay(float x, float y)
{
    Vector3df direction = forward + x * width * right + y * height * up;
    direction.normalize();
    Ray3df ray = {eye, direction};
    return ray;
}
// -- Camera end --
//-- Scene --
void Scene::addSphere(Sphere3df sphere, Material material)
{
    this->spheres.push_back(std::pair<Sphere3df, Material>(sphere, material));
}
void Scene::addLight(Light light)
{
    this->lights.push_back(light);
}
std::vector<Light> Scene::getLights()
{
    return this->lights;
}

std::vector<std::pair<Sphere3df, Material>> Scene::getSpheres()
{
    return this->spheres;
}


HitContext *Scene::nearestSphere(Ray3df &ray )
{
    double tmin = INFINITY;
    HitContext *hitContext = new HitContext();
    Intersection_Context<float, 3> context;
    for (long unsigned int i = 0; i < spheres.size(); i++)
    {
      
        if (spheres[i].first.intersects(ray, context)&& context.t < tmin )
            {
            
                
                hitContext->hit = true;
                hitContext->t = context.t;
                hitContext->u = context.u;
                hitContext->v = context.v;
                hitContext->normal = context.normal;
                hitContext->intersection = context.intersection;
                hitContext->m = spheres[i].second;
                tmin = context.t;
            }
    }
    return hitContext;
}
Vector3df Light::getRandomPoint()
{
    float theta = ((float) rand() / (RAND_MAX)) * 2.0f * M_PI;
    float phi = acos(2.0f * ((float) rand() / (RAND_MAX)) - 1.0f);

    float x = sin(phi) * cos(theta);
    float y = sin(phi) * sin(theta);
    float z = cos(phi);

    Vector3df randomPointOnUnitSphere({x, y, z});

    return position + 0.3f * randomPointOnUnitSphere;
}
    
std::vector<Light> Scene::findlights(HitContext &hit)
{
    std::vector<Light> vis_lights;
    for(Light light : lights)
    {
        Vector3df offset =0.001f* hit.normal; // Adjust the magnitude of the offset as needed
        Ray3df shadowRay = {hit.intersection + offset, light.getPosition() - hit.intersection};
        HitContext *shadowHitContext = nearestSphere(shadowRay);
        if(shadowHitContext->hit && shadowHitContext->t >= 1.0f){
            vis_lights.push_back(light);
        }
        delete shadowHitContext;
    }
    return vis_lights;
}
Color Scene::lambert(int n, std::vector<Light> &vis_lights, HitContext &con)
{
    Color matColor = con.m.getColor();
    float ambient = con.m.getAmbient();
    Color color = matColor * ambient;
    for (Light &light : vis_lights)
    {
        Vector3df lightPos = light.getPosition();
        Vector3df lightDir = lightPos - con.intersection;
        lightDir.normalize();
        double lambert = std::max(0.0f, con.normal * lightDir);
        color += lambert * light.getColor() * matColor;
    }

    return color;
}
// -- Scene end --
