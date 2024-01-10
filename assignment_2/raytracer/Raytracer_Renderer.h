#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <utility>
#include "math.h"
#include "geometry.h"

class Color{
    private:
        double r;
        double g;
        double b;
      
    public:
        Color(double r = 0, double g = 0, double b = 0):r(r),g(g),b(b){}
        double getR();
        double getG();
        double getB();
        
       Color operator+(Color addend) const {
    return Color(r + addend.r, g + addend.g, b+ addend.b);
  }

  Color operator*(Color factor) const {
    return Color(r * factor.r, g * factor.g, b * factor.b);
  }

  friend Color operator*(const double factor, Color color)  {
    return Color(factor * color.r, factor * color.g, factor * color.b);
  }
  Color operator/(double factor) const {
    return Color(r / factor, g / factor, b / factor);
  }
  friend Color operator/(Color factor, Color color)  {
    return Color(factor.r / color.r, factor.g / color.g, factor.b / color.b);
  }
  Color operator+=(Color addend) {
    r += addend.r;
    g += addend.g;
    b += addend.b;
    return *this;
  }
    
};
class Screen{
    private:
        int width;
        int height;
        std::unique_ptr<Color []> pixels;
    public:
    Screen(int width = 640, int height = 480):width(width),height(height),pixels(std::unique_ptr<Color []>( new Color[width * height] )){}
    void setPixel(int x, int y, Color c);
    void clearScreen(Color c = {0,0,0});
    int getWidth();
    int getHeight();
    Color getPixel(int x, int y);

};
class Camera {
    private:
        Vector3df eye, forward, right, up;
        float width, height;
    public:
       Camera(Vector3df eye, Vector3df upguide, Vector3df target, double width, double height);
        Ray3df makeRay(float x, float y);
};
class Light {
  Vector3df position;
  Color color;
public:
  Light(Vector3df position = {0.0, 0.0, 1000.0},
        Color color = Color(1.0, 1.0, 1.0) )
    : position(position), color(color) {
  }
 Vector3df getRandomPoint();
  Color getColor() const {
     return this->color;
  }

  Vector3df getPosition() const {
    return this->position;
  }
};

class Material {
private:
  Color color;
  double ambient, diffuse, specular, exponent, reflection;
public:
    Material(Color color = Color(1.0, 1.0, 1.0),
             double ambient = 0.1, double diffuse = 0.9,
             double specular = 0.9, double exponent = 10.0, double reflection = 0.0)
        : color(color), ambient(ambient), diffuse(diffuse),
        specular(specular), exponent(exponent), reflection(reflection)  {
    }
    double getReflection() const{
        return reflection;
    }
    Color getColor() const {
        return color;
    }
    
    double getAmbient() const {
        return ambient;
    }
    
    double getDiffuse() const {
        return diffuse;
    }
    
    double getSpecular() const {
        return specular;
    }
    
    double getExponent() const {
        return exponent;
    }
    Color operator+(Material& m);
    Color operator*(Material& m);
    };
    struct HitContext {
    bool sphere ;
    bool hit;
    Material m;
    double u,v, // may be used for U-V-Mapping, values depend on intersected object
        t;  // intersection = ray.origin + t * ray.direction
    Vector3df normal{},  // the intersection normal pointing away from the surface
                   intersection{};
};
class Scene{
private:
    std::vector<std::pair<Sphere3df,Material>> spheres;
    std::vector<std::pair<AABB3df,Material>> aabbs;

    std::vector<Light> lights;

public:

    void setAABB(AxisAlignedBoundingBox<float, 3u> aabb, Material material);
     
     void  addSphere(Sphere3df sphere, Material material);
    void addLight(Light light);
    void addAABB(AxisAlignedBoundingBox<float, 3u> aabb, Material material);
    std::vector<std::pair<Sphere3df, Material>> getSpheres();
    std::vector<Light> getLights();
    HitContext* nearestSphere(Ray3df & ray);
    std::vector<Light> findlights(HitContext &hit);
    Color lambert(int n, std::vector<Light> &lights, HitContext & con);


};
    class Raytracer_Renderer {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Event event;
        bool quit = false;
        int window_width;
        int window_height;
        char* title;
        

    public:
        Raytracer_Renderer(int window_width = 640, int window_height = 480, char* title = "Raytracer");

        bool init();
        bool render(Screen* screen);
        void Event();
        bool exit();
        int getWidth();
        int getHeight();
};

