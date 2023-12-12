#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include "math.h"
#include "geometry.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Raytracer_Renderer.h"
#include <fstream>

// Die folgenden Kommentare beschreiben Datenstrukturen und Funktionen
// Die Datenstrukturen und Funktionen die weiter hinten im Text beschrieben sind,
// hängen höchstens von den vorhergehenden Datenstrukturen ab, aber nicht umgekehrt.

/*
 if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
      exit(1);
    }


    atexit(SDL_Quit);

    SDL_Window* window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == NULL) {
      fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
      exit(1);
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
      fprintf(stderr, "Couldn't create renderer: %s\n", SDL_GetError());
      exit(1);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
     SDL_RenderDrawLine(renderer, 0, 0, 300, 240);
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



*/
// Ein "Bildschirm", der das Setzen eines Pixels kapselt
// Der Bildschirm hat eine Auflösung (Breite x Höhe)
// Kann zur Ausgabe einer PPM-Datei verwendet werden oder
// mit SDL2 implementiert werden.

// Eine "Kamera", die von einem Augenpunkt aus in eine Richtung senkrecht auf ein Rechteck (das Bild) zeigt.
// Für das Rechteck muss die Auflösung oder alternativ die Pixelbreite und -höhe bekannt sein.
// Für ein Pixel mit Bildkoordinate kann ein Sehstrahl erzeugt werden.


void raytrace(Camera &camera, Screen &screen, Scene &scene)
{
    Color color;
    for (int y = 0; y < screen.getHeight(); y++)
    {
        for (int x = 0; x < screen.getWidth(); x++)
        {
            color = Color(0.0, 0.0, 0.0);
            float cx = (2.0 * x) / screen.getWidth() - 1.0;
            float cy = (2.0 * y) / screen.getHeight() - 1.0;
            Ray3df ray = camera.makeRay(cx,cy);
            Sphere3df *nearestSphere = nullptr;
            float t = INFINITY;
            HitContext* con = scene.nearestObject(ray);
            if(con->hit)
            {
                std::vector<Light> lights = scene.findlights(*con);
                int n = scene.getLights().size();
                for (const auto& light : lights)
            {
                // Create a shadow ray from the hit point towards the light
                Vector3df toLight = light.getPosition() - con->intersection;
                toLight.normalize();
                Vector3df offsetOrigin = (con->intersection +((float)0.001)*(con->normal));
                Ray3df shadowRay(offsetOrigin, toLight);

                // Check if the shadow ray intersects any object
                HitContext* shadowCon = scene.nearestObject(shadowRay);
                if (shadowCon->hit && shadowCon->t < toLight.length())
                {
                    // The hit point is in shadow, so continue to the next light
                    continue;
                }

                // The hit point is not in shadow, so add the contribution of this light
                color = color + scene.lambert(n, lights, *con);
            }
            
            }
            else{
              for (size_t i = 0; i < scene.getAABBs().size(); i++)
              {
                AABB3df aabb = scene.getAABBs()[i].first;
                Material material = scene.getAABBs()[i].second;
                if(aabb.intersects(ray))
                {
                  color = material.getColor();
                }
              }
               
            }
            screen.setPixel(x, y, color);
            delete con;
        }
    }
}
// Für die "Farbe" benötigt man nicht unbedingt eine eigene Datenstruktur.
// Sie kann als Vector3df implementiert werden mit Farbanteil von 0 bis 1.
// Vor Setzen eines Pixels auf eine bestimmte Farbe (z.B. 8-Bit-Farbtiefe),
// kann der Farbanteil mit 255 multipliziert  und der Nachkommaanteil verworfen werden.

// Das "Material" der Objektoberfläche mit ambienten, diffusem und reflektiven Farbanteil.

// Ein "Objekt", z.B. eine Kugel oder ein Dreieck, und dem zugehörigen Material der Oberfläche.
// Im Prinzip ein Wrapper-Objekt, das mindestens Material und geometrisches Objekt zusammenfasst.
// Kugel und Dreieck finden Sie in geometry.h/tcc

// verschiedene Materialdefinition, z.B. Mattes Schwarz, Mattes Rot, Reflektierendes Weiss, ...
// im wesentlichen Variablen, die mit Konstruktoraufrufen initialisiert werden.

// Die folgenden Werte zur konkreten Objekten, Lichtquellen und Funktionen, wie Lambertian-Shading
// oder die Suche nach einem Sehstrahl für das dem Augenpunkt am nächsten liegenden Objekte,
// können auch zusammen in eine Datenstruktur für die gesammte zu
// rendernde "Szene" zusammengefasst werden.

// Die Cornelbox aufgebaut aus den Objekten
// Am besten verwendet man hier einen std::vector< ... > von Objekten.

// Punktförmige "Lichtquellen" können einfach als Vector3df implementiert werden mit weisser Farbe,
// bei farbigen Lichtquellen müssen die entsprechenden Daten in Objekt zusammengefaßt werden
// Bei mehreren Lichtquellen können diese in einen std::vector gespeichert werden.

// Sie benötigen eine Implementierung von Lambertian-Shading, z.B. als Funktion
// Benötigte Werte können als Parameter übergeben werden, oder wenn diese Funktion eine Objektmethode eines
// Szene-Objekts ist, dann kann auf die Werte teilweise direkt zugegriffen werden.
// Bei mehreren Lichtquellen muss der resultierende diffuse Farbanteil durch die Anzahl Lichtquellen geteilt werden.

// Für einen Sehstrahl aus allen Objekte, dasjenige finden, das dem Augenpunkt am nächsten liegt.
// Am besten einen Zeiger auf das Objekt zurückgeben. Wenn dieser nullptr ist, dann gibt es kein sichtbares Objekt.

// Die rekursive raytracing-Methode. Am besten ab einer bestimmten Rekursionstiefe (z.B. als Parameter übergeben) abbrechen.


void write_bmp(std::ostream & out,  Screen & screen) {
  unsigned long long size_of_bitmap_data = screen.getWidth() * screen.getHeight() * 4;
  out.put(0x42); out.put(0x4D); // "BM"
  out.put(0x00); out.put(0x00); out.put(0x00); out.put(0x00); // size of bmp file
  out.put(0x00); out.put(0x00);
  out.put(0x00); out.put(0x00);
  out.put(0x36); out.put(0x00);out.put(0x00); out.put(0x00); // offset to start of pixel array
  // Header
  out.put(0x28); out.put(0x00); out.put(0x00); out.put(0x00);  // 40 bytes Number of bytes in the DIB header (from this point)
  out.put( screen.getWidth() & 0xFF ); out.put( screen.getWidth() >> 8 & 0xFF );
  out.put(0x00); out.put(0x00); // width in pixel
  out.put( screen.getHeight() & 0xFF ); out.put( screen.getHeight() >> 8 & 0xFF );
  out.put(0x00); out.put(0x00); // height in pixel
  out.put(0x01); out.put(0x00); // 1 = number of color planes used
  out.put(0x18); out.put(0x00); // 24 bits per pixel (RGB)
  out.put(0x00); out.put(0x00); out.put(0x00); out.put(0x00); // 0 = no compression
  // size of raw bitmap data 16 bytes
  out.put(size_of_bitmap_data & 0xFF); 
  out.put(size_of_bitmap_data >> 8 & 0xFF); 
  out.put(size_of_bitmap_data >> 16 & 0xFF); 
  out.put(size_of_bitmap_data >> 32 & 0xFF); 
  out.put(0x13); out.put(0x0B); out.put(0x00); out.put(0x00); // 72 DPI resolution for printing
  out.put(0x13); out.put(0x0B); out.put(0x00); out.put(0x00); //           "
  out.put(0x00); out.put(0x00); out.put(0x00); out.put(0x00); // 0 colors in the palette
  out.put(0x00); out.put(0x00); out.put(0x00); out.put(0x00); // 0 = all colors are important
  // start of pixel map array, 4 byte alignment padding at end of line if nedded
  for (size_t y = 0u; y < screen.getHeight(); y++ ) {
    for (size_t x = 0u; x < screen.getWidth(); x++) {
      out.put( ((unsigned short) (screen.getPixel(x, screen.getHeight() - 1 - y).getR() * 255.0) ) & 0xFF );
      out.put( ((unsigned short) (screen.getPixel(x, screen.getHeight() - 1 - y).getG() * 255.0) ) & 0xFF );
      out.put( ((unsigned short) (screen.getPixel(x, screen.getHeight() - 1 - y).getB() * 255.0) ) & 0xFF );
    }
    for (size_t padding_bytes = 0u; padding_bytes < screen.getWidth() % 4; padding_bytes++) {
      out.put( 0x00 );
    }
  } 
}
int main(void){
    Scene scene;
     scene.addLight(Light({0.0, 2.0, 0.0}, Color(1.0, 1.0, 1.0)));
    int height = 3000;
    int width = 3000;
    
    scene.addAABB(AABB3df({0.0, 0.0, -2.0}, {2.0, 2.0, 0.1}), Material(Color(1.0, 0.0, 0.0), 0.1, 0.9, 0.9, 10.0));
   
   scene.addAABB(AABB3df({0.0, 0.0, 2.0}, {2.0, 2.0, 0.1}), Material(Color(0.0, 0.0, 1.0), 0.1, 0.9, 0.9, 10.0));

  
    scene.addAABB(AABB3df({2.0, 0.0, 0.0}, {0.1, 2.0, 2.0}), Material(Color(0.0, 1.0, 0.0), 0.1, 0.9, 0.9, 10.0));

 
    scene.addAABB(AABB3df({0.0, -2.0, 0.0}, {2.0 ,0.1, 2.0}), Material(Color(1.0, 1.0, 0.0), 0.1, 0.9, 0.9, 10.0));

    
    scene.addAABB(AABB3df({0.0, 2.0, 0.0}, {2.0, 0.1, 2.0}), Material(Color(1.0, 1.0, 0.0), 0.1, 0.9, 0.9, 10.0));

    scene.addSphere(Sphere3df({-0.4, -0.5, -0.5}, 0.5), Material(Color(0.5, 0.5, 1.0), 0.1, 0.9, 0.9, 10.0));
    scene.addSphere(Sphere3df({0.4, 0.5, 0.5}, 0.5), Material(Color(0.5, 0.8, 0.0), 0.1, 0.9, 0.9, 10.0));
   
    Screen screen = Screen(width, height);
    Camera camera = Camera({-2.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0},PI/4, (float)width / (float)height);
    Raytracer_Renderer renderer = Raytracer_Renderer(width, height, "Raytracer");
    //renderer.init();
    
    raytrace(camera, screen, scene);
    //renderer.render(&screen);
     std::ofstream output("test.bmp", std::ofstream::binary); // for windows
  
    write_bmp(output,screen);
    std::cout << "finished" << std::endl;
    output.close();
       // renderer.exit();

    // Bildschirm erstellen
    // Kamera erstellen
    // Für jede Pixelkoordinate x,y

    // Bildschirm erstellen
    // Kamera erstellen
    // Für jede Pixelkoordinate x,y
    //   Sehstrahl für x,y mit Kamera erzeugen
    //   Farbe mit raytracing-Methode bestimmen
    //   Beim Bildschirm die Farbe für Pixel x,y, setzten

    return 0;
}
