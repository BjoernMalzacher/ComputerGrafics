#include "opengl_renderer.h"
#include "wavefront.h"
#include <cassert>
#include <span>
#include <utility>


// geometric data as in original game and game coordinates
std::vector<Vector2df> spaceship = {
  Vector2df{-6.0f,  3.0f},
  Vector2df{-6.0f, -3.0f},
  Vector2df{-10.0f, -6.0f},
  Vector2df{14.0f,  0.0f},
  Vector2df{-10.0f,  6.0f},
  Vector2df{ -6.0f,  3.0f}
};

std::vector<Vector2df> flame = { 
  Vector2df{-6, 3},
  Vector2df{-12, 0},
  Vector2df{-6, -3}
};

std::vector<Vector2df> torpedo_points = { 
  Vector2df{0, 0},
  Vector2df{0, 1}
};

std::vector<Vector2df> saucer_points = {
  Vector2df{-16, -6},
  Vector2df{16, -6}, 
  Vector2df{40, 6}, 
  Vector2df{-40, 6},
  Vector2df{-16, 18},
  Vector2df{16, 18},
  Vector2df{40, 6},
  Vector2df{16, -6},
  Vector2df{8, -18},
  Vector2df{-8, -18},
  Vector2df{-16, -6},
  Vector2df{-40, 6}
};

std::vector<Vector2df> asteroid_1 = {
  Vector2df{ 0, -12},
  Vector2df{16, -24},
  Vector2df{32, -12},
  Vector2df{24, 0},
  Vector2df{32, 12},
  Vector2df{8, 24}, 
  Vector2df{-16, 24}, 
  Vector2df{-32, 12}, 
  Vector2df{-32, -12}, 
  Vector2df{-16, -24},
  Vector2df{0, -12}
};

std::vector<Vector2df> asteroid_2 = {
  Vector2df{6, -6},
  Vector2df{32, -12},
  Vector2df{16, -24}, 
  Vector2df{0, -16}, 
  Vector2df{-16, -24}, 
  Vector2df{-24, -12},
  Vector2df{-16, -0}, 
  Vector2df{-32, 12}, 
  Vector2df{-16, 24}, 
  Vector2df{-8, 16}, 
  Vector2df{16, 24}, 
  Vector2df{32, 6}, 
  Vector2df{16, -6},
};

std::vector<Vector2df> asteroid_3 = {
  Vector2df{-16, 0}, 
  Vector2df{-32, 6}, 
  Vector2df{-16, 24}, 
  Vector2df{0, 6}, 
  Vector2df{0, 24}, 
  Vector2df{16, 24},
  Vector2df{32, 6}, 
  Vector2df{32, 6}, 
  Vector2df{16, -24}, 
  Vector2df{-8, -24}, 
  Vector2df{-32, -6}
};

std::vector<Vector2df> asteroid_4 = {
  Vector2df{8,0}, 
  Vector2df{32,-6}, 
  Vector2df{32, -12}, 
  Vector2df{8, -24}, 
  Vector2df{-16, -24}, 
  Vector2df{-8, -12}, 
  Vector2df{-32, -12}, 
  Vector2df{-32, 12}, 
  Vector2df{-16, 24}, 
  Vector2df{8, 16}, 
  Vector2df{16, 24}, 
  Vector2df{32, 12}, 
  Vector2df{8, 0}
};

std::vector<Vector2df> spaceship_debris = {
  Vector2df{-2, -1}, 
  Vector2df{-10, 7}, 
  Vector2df{3, 1}, 
  Vector2df{7, 8},
  Vector2df{0, 3}, 
  Vector2df{6, 1},
  Vector2df{3, -1}, 
  Vector2df{ -5, -7},
  Vector2df{0, -4}, 
  Vector2df{-6, -6},
  Vector2df{-2, 2}, 
  Vector2df{2, 5}
};
    
std::vector<Vector2df> spaceship_debris_direction = {
 Vector2df{-40, -23},
 Vector2df{50, 15},
 Vector2df{0, 45},
 Vector2df{60, -15}, 
 Vector2df{10, -52}, 
 Vector2df{-40, 30}
};

std::vector<Vector2df> debris_points = {
 Vector2df{-32, 32}, 
 Vector2df{-32, -16}, 
 Vector2df{-16, 0}, 
 Vector2df{-16, -32}, 
 Vector2df{-8, 24},
 Vector2df{8, -24}, 
 Vector2df{24, 32}, 
 Vector2df{24, -24}, 
 Vector2df{24, -32}, 
 Vector2df{32, -8}
};
        
std::vector<Vector2df> digit_0 = { {0,-8}, {4,-8}, {4,0}, {0,0}, {0, -8} };
std::vector<Vector2df> digit_1 = { {4,0}, {4,-8} };
std::vector<Vector2df> digit_2 = { {0,-8}, {4,-8}, {4,-4}, {0,-4}, {0,0}, {4,0}  };
std::vector<Vector2df> digit_3 = { {0,0}, {4, 0}, {4,-4}, {0,-4}, {4,-4}, {4, -8}, {0, -8}  };
std::vector<Vector2df> digit_4 = { {4,0}, {4,-8}, {4,-4}, {0,-4}, {0,-8}  };
std::vector<Vector2df> digit_5 = { {0,0}, {4,0}, {4,-4}, {0,-4}, {0,-8}, {4, -8}  };
std::vector<Vector2df> digit_6 = { {0,-8}, {0,0}, {4,0}, {4,-4}, {0,-4} };
std::vector<Vector2df> digit_7 = { {0,-8}, {4,-8}, {4,0} };
std::vector<Vector2df> digit_8 = { {0,-8}, {4,-8}, {4,0}, {0,0}, {0,-8}, {0, -4}, {4, -4} };
std::vector<Vector2df> digit_9 = { {4, 0}, {4,-8}, {0,-8}, {0, -4}, {4, -4} };
  
std::vector< std::vector<Vector2df> * > vertice_data = {
  &spaceship, &flame,
  &torpedo_points, &saucer_points,
  &asteroid_1, &asteroid_2, &asteroid_3, &asteroid_4,
  &spaceship_debris, &spaceship_debris_direction,
  &debris_points,
  &digit_0, &digit_1, &digit_2, &digit_3, &digit_4, &digit_5, &digit_6, &digit_7, &digit_8, &digit_9 };   


// class OpenGLView

  OpenGLView::OpenGLView(GLuint vbo, unsigned int shaderProgram, size_t vertices_size, GLuint mode)
    : shaderProgram(shaderProgram), vertices_size(vertices_size), mode(mode) {
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0,
                            3,        // number of vertices (components)
                            GL_FLOAT, //
                            GL_FALSE, // no normalization
                            9 * sizeof(float), // no of bytes between each vertice (component)
                            (void*)0);
      glEnableVertexAttribArray(0);

      glVertexAttribPointer(1,
                            3,        // no vertices (components)
                            GL_FLOAT, //
                            GL_FALSE, // no normalization
                            9 * sizeof(float), // no of bytes between each color (component)
                            (void*)(6 * sizeof(float)) ); // offset to color data in the vbo
      glEnableVertexAttribArray(1);

      glVertexAttribPointer(2,
                            3,        // no vertices (components)
                            GL_FLOAT, //
                            GL_FALSE, // no normalization
                            9 * sizeof(float), // no of bytes between each color (component)
                            (void*)(3 * sizeof(float)) ); // offset to color data in the vbo
      glEnableVertexAttribArray(2);
                            

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  OpenGLView::~OpenGLView() {
   glDeleteVertexArrays(1, &vao);
  }

  void OpenGLView::render( SquareMatrix<float,4> & matrice) {
    debug(2, "render() entry...");
    glBindVertexArray(vao);
    glUseProgram(shaderProgram);
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "model");

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &matrice[0][0] );

    glDrawArrays(mode, 0, vertices_size/2 );

    debug(2, "render() exit.");
  }

// class TypedBodyView

  TypedBodyView::TypedBodyView(TypedBody * typed_body, GLuint vbo, unsigned int shaderProgram, size_t vertices_size, float scale, GLuint mode,
               std::function<bool()> draw, std::function<void(TypedBodyView *)> modify)
        : OpenGLView(vbo, shaderProgram, vertices_size, mode),  typed_body(typed_body), scale(scale), draw(draw), modify(modify) {
  }
  
  SquareMatrix4df TypedBodyView::create_object_transformation(Vector2df direction, float angle, float scale) {
    SquareMatrix4df  translation= { {1.0f,        0.0f,          0.0f, 0.0f},
                                    {0.0f,        1.0f,          0.0f, 0.0f},
                                    {0.0f,        0.0f,          1.0f, 0.0f},
                                    {direction[0], direction[1], 0.0f, 1.0f}
                                  };
    SquareMatrix4df rotation = { { std::cos(angle),  std::sin(angle), 0.0f, 0.0f},
                                 {-std::sin(angle),  std::cos(angle), 0.0f, 0.0f},
                                 { 0.0f,             0.0f,            1.0f, 0.0f},
                                 { 0.0f,             0.0f,            0.0f, 1.0f}
                               };
    SquareMatrix4df  scaling = { { scale,    0.0f, 0.0f,   0.0f},
                                 {  0.0f,   scale, 0.0f,   0.0f},
                                 {  0.0f,    0.0f, scale,  0.0f},
                                 {  0.0f,    0.0f, 0.0f,   1.0f}
                               };                                 

    return translation * rotation * scaling;
  }

  void TypedBodyView::render( SquareMatrix<float,4> & world) {
    debug(2, "render() entry...");
    if ( draw() ) {
      modify(this);
      auto transform = world * create_object_transformation(typed_body->get_position(), typed_body->get_angle(), scale);
      OpenGLView::render(transform);
      }
    debug(2, "render() exit.");
  }
  
 TypedBody * TypedBodyView::get_typed_body() {
   return typed_body;
 }

 void TypedBodyView::set_scale(float scale) {
   this->scale = scale;
 }


Material default_material = { {1.0f, 1.0f, 1.0f} };

/* assumes that the all i faces are triangles, more than three vertices of a face are ignored
   creates a vector of floats with the following layout
   [ face1 | face2 | ... | facei ]
   where each face consists of a sequence of 3 (=number of triangle vertices) * 9 floats
   x1 y1 z1 nx1 ny1 nz1 r1 g1 b1 | x2 y2 z2 nx2 ny2 nz2 r2 g2 b2 | x3 y3 z3 nx3 ny3 nz3 r3 g3 b3
     vertex   normal     color       vertex    normal     color     vertex    normal     color
     
  if no material is given for a face, then the default_material is used
  
  if you want to use other layouts, then adapt this code
*/     
std::vector<float> create_vertices(WavefrontImporter & wi) {
  std::vector<float> vertices;
  
  for (Face face : wi.get_faces() ) {
    for (ReferenceGroup group : face.reference_groups ) {
      for (size_t i = 0; i < 3; i++) {
        vertices.push_back( group.vertice[i]);
      }
      for (size_t i = 0; i < 3; i++) {
        vertices.push_back( group.normal[i] );
      }
      if (face.material == nullptr) face.material = &default_material;
      for (size_t i = 0; i < 3; i++) {
        vertices.push_back( face.material->ambient[i]);
      }
    } 
  }
  return vertices;
}

void OpenGLRenderer::createVbos() {
  std::fstream in("spaceship.obj");
  WavefrontImporter wi(in);
  wi.parse();
  const auto& vertices_spaceship = create_vertices(wi);

  std::fstream in2("UFO.obj");
  WavefrontImporter wi2(in2);
  wi2.parse();
  const auto& vertices_UFO = create_vertices(wi2);

  
  std::fstream in3("Torpedo.obj");
  WavefrontImporter wi3(in3);
  wi3.parse();
  const auto& vertices_torpedos = create_vertices(wi3);
  
  std::fstream in4("comet.obj");
  WavefrontImporter wi4(in4);
  wi4.parse();
  const auto& vertices_comet = create_vertices(wi4);

  std::fstream in5("debrees.obj");
  WavefrontImporter wi5(in5);
  wi5.parse();
  const auto& vertices_debrees = create_vertices(wi5);


  vbos = new GLuint[vertice_data.size()+5];
  glGenBuffers(vertice_data.size()+5, vbos);

 for (size_t i = 0; i < vertice_data.size(); i++) {
   glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
   glBufferData(GL_ARRAY_BUFFER, vertice_data[i]->size() * sizeof( Vector2df ), vertice_data[i]->data(), GL_STATIC_DRAW);
 }

  glBindBuffer(GL_ARRAY_BUFFER, vbos[vertice_data.size()]);
  glBufferData(GL_ARRAY_BUFFER, vertices_spaceship.size() * sizeof(float),vertices_spaceship.data(), GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbos[vertice_data.size()+1]);
  glBufferData(GL_ARRAY_BUFFER, vertices_comet.size() * sizeof(float),vertices_comet.data(), GL_STATIC_DRAW);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbos[vertice_data.size()+2]);
  glBufferData(GL_ARRAY_BUFFER, vertices_UFO.size() * sizeof(float),vertices_UFO.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbos[vertice_data.size()+3]);
  glBufferData(GL_ARRAY_BUFFER, vertices_torpedos.size() * sizeof(float),vertices_torpedos.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vbos[vertice_data.size()+4]);
  glBufferData(GL_ARRAY_BUFFER, vertices_debrees.size() * sizeof(float),vertices_debrees.data(), GL_STATIC_DRAW);
}

void OpenGLRenderer::create(Spaceship * ship, std::vector< std::unique_ptr<TypedBodyView> > & views) {
    debug(4, "create(Spaceship *) entry...");
    std::fstream in("spaceship.obj");
    WavefrontImporter wi(in);
    wi.parse();
  const auto& vertices_spaceship = create_vertices(wi);
  views.push_back(std::make_unique<TypedBodyView>(ship, vbos[vertice_data.size()], shaderProgram, vertices_spaceship.size(), 20.0f, GL_TRIANGLES,
                  [ship]() -> bool {return ! ship->is_in_hyperspace();}) // only show ship if outside hyperspace
                 );   
  views.push_back(std::make_unique<TypedBodyView>(ship, vbos[vertice_data.size()], shaderProgram, vertices_spaceship.size(), 20.0f, GL_TRIANGLES,
                  [ship]() -> bool {return ! ship->is_in_hyperspace() && ship->is_accelerating();}) // only show flame if accelerating
                 );   

    debug(4, "create(Spaceship *) exit.");
}

void OpenGLRenderer::create(Saucer * saucer, std::vector< std::unique_ptr<TypedBodyView> > & views) {
  debug(4, "create(Saucer *) entry...");
  std::fstream in2("UFO.obj");
  WavefrontImporter wi2(in2);
  wi2.parse();
  const auto& vertices_UFO = create_vertices(wi2);

  views.push_back(std::make_unique<TypedBodyView>(saucer, vbos[vertice_data.size()+2], shaderProgram, vertices_UFO.size(), 20.0f, GL_TRIANGLES));   
  debug(4, "create(Saucer *) exit.");
}


void OpenGLRenderer::create(Torpedo * torpedo, std::vector< std::unique_ptr<TypedBodyView> > & views) {
  debug(4, "create(Torpedo *) entry...");
    std::fstream in3("Torpedo.obj");
  WavefrontImporter wi3(in3);
  wi3.parse();
  const auto& vertices_torpedos = create_vertices(wi3);
  views.push_back(std::make_unique<TypedBodyView>(torpedo, vbos[vertice_data.size()+3], shaderProgram, vertices_torpedos.size(), 3.0f, GL_TRIANGLES)); 
  debug(4, "create(Torpedo *) exit.");
}

void OpenGLRenderer::create(Asteroid * asteroid, std::vector< std::unique_ptr<TypedBodyView> > & views) {
  debug(4, "create(Asteroid *) entry...");
    std::fstream in("comet.obj");
    WavefrontImporter wi(in);
    wi.parse();  
    const auto& vertices_spaceship = create_vertices(wi);
 
  views.push_back(std::make_unique<TypedBodyView>(asteroid, vbos[vertice_data.size()+1], shaderProgram,vertices_spaceship.size(), 25.0f, GL_TRIANGLES)); 
  debug(4, "create(Asteroid *) exit.");
}

void OpenGLRenderer::create(SpaceshipDebris * debris, std::vector< std::unique_ptr<TypedBodyView> > & views) {
  debug(4, "create(SpaceshipDebris *) entry...");
  std::fstream in5("debrees.obj");
  WavefrontImporter wi5(in5);
  wi5.parse();
  const auto& vertices_debrees = create_vertices(wi5);

  views.push_back(std::make_unique<TypedBodyView>(debris, vbos[vertice_data.size()+4], shaderProgram, vertices_debrees.size(), 20.0f, GL_TRIANGLES,
            []() -> bool {return true;},
            [debris](TypedBodyView * view) -> void { view->set_scale( 0.2f * (SpaceshipDebris::TIME_TO_DELETE - debris->get_time_to_delete()));}));   
  debug(4, "create(SpaceshipDebris *) exit.");
}

void OpenGLRenderer::create(Debris * debris, std::vector< std::unique_ptr<TypedBodyView> > & views) {
  debug(4, "create(Debris *) entry...");
    std::fstream in5("debrees.obj");
  WavefrontImporter wi5(in5);
  wi5.parse();
  const auto& vertices_debrees = create_vertices(wi5);
  views.push_back(std::make_unique<TypedBodyView>(debris, vbos[vertice_data.size()+4], shaderProgram, vertices_debrees.size(), 50.0f, GL_TRIANGLES,
            []() -> bool {return true;},
            [debris](TypedBodyView * view) -> void { view->set_scale(Debris::TIME_TO_DELETE - debris->get_time_to_delete());}));   
  debug(4, "create(Debris *) exit.");
}

void OpenGLRenderer::createSpaceShipView() {
  spaceship_view = std::make_unique<OpenGLView>(vbos[0], shaderProgram, vertice_data[0]->size(), GL_LINE_LOOP);
}

void OpenGLRenderer::createDigitViews() {
  for (size_t i = 0; i < 10; i++ ) {
    digit_views[i] = std::make_unique<OpenGLView>(vbos[11 + i], shaderProgram, vertice_data[11 + i]->size(), GL_LINE_STRIP);
  }
}


void OpenGLRenderer::renderFreeShips(SquareMatrix4df & matrice) {
  constexpr float FREE_SHIP_X = 128;
  constexpr float FREE_SHIP_Y = 64;
  const float PIf = static_cast<float> ( PI );
  Vector2df position = {FREE_SHIP_X, FREE_SHIP_Y};
  SquareMatrix4df rotation = {   { std::cos(-PIf / 3.0f),  std::sin(-PIf / 3.0f), 0.0f, 0.0f},
                                 {-std::sin(-PIf / 3.0f),  std::cos(-PIf / 3.0f), 0.0f, 0.0f},
                                 { 0.0f,                 0.0f,                1.0f, 0.0f},
                                 { 0.0f,                 0.0f,                0.0f, 1.0f}
                               };
  for (int i = 0; i < game.get_no_of_ships(); i++) {
    SquareMatrix4df  translation= { {1.0f,        0.0f,         0.0f, 0.0f},
                                    {0.0f,        1.0f,         0.0f, 0.0f},
                                    {0.0f,        0.0f,         1.0f, 0.0f},
                                    {position[0], position[1],  0.0f, 1.0f} };
    SquareMatrix4df render_matrice = matrice * translation * rotation;
    spaceship_view->render( render_matrice );
    position[0] += 20.0;
  }
}

void OpenGLRenderer::renderScore(SquareMatrix4df & matrice) {
  constexpr float SCORE_X = 128 - 48;
  constexpr float SCORE_Y = 48 - 4;
  

  long long score = game.get_score();
  int no_of_digits = 0;
  if (score > 0) {
    no_of_digits = std::trunc( std::log10( score ) ) + 1;
  }

  Vector2df position = {SCORE_X + 20.0f * no_of_digits,  SCORE_Y};  
  do {
    int d = score % 10;
    score /= 10;
    SquareMatrix4df scale_translation= { {4.0f,        0.0f,         0.0f, 0.0f},
                                         {0.0f,        4.0f,         0.0f, 0.0f},
                                         {0.0f,        0.0f,         1.0f, 0.0f},
                                         {position[0], position[1],  0.0f, 1.0f} };
    SquareMatrix4df render_matrice = matrice * scale_translation;
    digit_views[d]->render( render_matrice );
    no_of_digits--;
    position[0] -= 20;

  } while (no_of_digits > 0);
}
void compile_shader(GLint shader, const char * source) {
  glShaderSource(shader, 1, &source, NULL) ;
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    std::cerr << " Shader did not compile." << std::endl;
    char log[512];
    glGetShaderInfoLog( shader, 512, NULL, log) ;
    error(log);
    throw EXIT_FAILURE;
  }
}

void check_link_status(GLint shader_program) {
  GLint status;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    GLint length;
    glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &length);
    GLchar *log = new char[length + 1];
    glGetProgramInfoLog(shader_program, length, &length, &log[0]);
    error(log);
    throw EXIT_FAILURE;
  }
}

void OpenGLRenderer::create_shader_programs() {
  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n" 
    "layout (location = 1) in vec3 incolor;\n"
    "layout (location = 2) in vec3 innormal;\n"
    "out vec3 color;\n"
    "out vec3 normal;\n"  // Changed from vec4 to vec3
    "out vec3 fragPos;\n"  // Add fragment position for better lighting
    "uniform mat4 model;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = model * vec4(position, 1.0);\n"
    "    color = incolor;\n"
    "    // Transform normal to world space and normalize\n"
    "    normal = normalize(mat3(model) * innormal);\n"  // Use mat3 to avoid translation effects
    "    fragPos = vec3(model * vec4(position, 1.0));\n"  // Fragment position in world space
    "}\0";

  // Fixed fragment shader with proper lighting calculation
  const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 outColor;\n"
    "in vec3 color;\n"
    "in vec3 normal;\n"
    "in vec3 fragPos;\n"
    "void main() {\n"
    "    // Ambient lighting\n"
    "    float ambientStrength = 0.3;\n"
    "    vec3 ambient = ambientStrength * color;\n"
    "    \n"
    "    // Diffuse lighting\n"
    "    vec3 lightDir = normalize(vec3(0.0,10.0, -4.0));\n"  // Light direction\n"
    "    float diff = max(dot(normalize(normal), lightDir), 0.0);\n"
    "    vec3 diffuse = diff * color;\n"
    "    \n"
    "    vec3 result = ambient + diffuse;\n"
    "    outColor = vec4(result, 1.0);\n"
    "}\n\0";
  
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  compile_shader(vertexShader, vertexShaderSource);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  compile_shader(fragmentShader, fragmentShaderSource);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);
  check_link_status(shaderProgram);
  
  // Clean up shaders (they're linked into the program now)
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

bool OpenGLRenderer::init() {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    error( std::string("Could not initialize SDL. SDLError: ") + SDL_GetError() );
  } else {
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if( window == nullptr ) {
      error( std::string("Could not create Window. SDLError: ") + SDL_GetError() );
    } else {
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

      context = SDL_GL_CreateContext(window);
      
      GLenum err = glewInit(); // to be called after OpenGL render context is created
      if (GLEW_OK != err) {
        error( "Could not initialize Glew. Glew error message: " );
        error( glewGetErrorString(err) );
      }
      debug(1, "Using GLEW Version: ");
      debug(1, glewGetString(GLEW_VERSION) );
      glEnable(GL_DEPTH_TEST);
      SDL_GL_SetSwapInterval(1);
      
      create_shader_programs();
      createVbos();
      createSpaceShipView();
      createDigitViews();
      return true;
    }
  }
  return false;
}

/* tile positions in world coordinates
   used to draw objects seemless between boundary
  +---+---+---+   
  | 5 | 7 | 2 |
  +---+---+---+
  | 4 | 0 | 1 |
  +---+---+---+
  | 6 | 8 | 3 |
  +---+---+---+
*/
static Vector2df tile_positions [] = {
                         {0.0f, 0.0f},
                         {1024.0f, 0.0f},
                         {1024.0f, 768.0f},
                         {1024.0f, -768.0f},
                         {-1024.0f, 0.0f},
                         {-1024.0f, 768.0f},
                         {-1024.0f, -768.0f},
                         {0.0f, 768.0f},
                         {0.0f, -768.0f} };

void OpenGLRenderer::render() {
  debug(2, "render() entry...");

  // transformation to canonical view and from left handed to right handed coordinates
  SquareMatrix4df world_transformation =
                         SquareMatrix4df{
                           { 2.0f / 1024.0f,           0.0f,            0.0f,  0.0f},
                           {       0.0f,     -2.0f / 768.0f,            0.0f,  0.0f}, // (negative, because we have a left handed world coord. system)
                           {       0.0f,               0.0f,  2.0f / 1024.0f,  0.0f},
                           {      -1.0f,               1.0f,           -1.0f,  1.0f}
                         };
                                                 
  glClearColor ( 0.0, 0.0, 0.0, 1.0 );
  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  debug(2, "remove views for deleted objects");

  // remove all views for typed bodies that have to be deleted 
  erase_if(views, []( std::unique_ptr<TypedBodyView> & view) { return view->get_typed_body()->is_marked_for_deletion();}); 

  auto new_bodies = game.get_physics().get_recently_added_bodies();
  for (Body2df * body : new_bodies) {
    assert(body != nullptr);
    TypedBody * typed_body = static_cast<TypedBody *>(body);
    auto type = typed_body->get_type();
    if (type == BodyType::spaceship) {
      create( static_cast<Spaceship *>(typed_body), views );
    } else if (type == BodyType::torpedo ) {
      create( static_cast<Torpedo *>(typed_body), views );
    } else  if (type == BodyType::asteroid) {
      create( static_cast<Asteroid *>(typed_body), views );
    } else if (type == BodyType::saucer) {
      create( static_cast<Saucer *>(typed_body), views );
    } else if (type == BodyType::spaceship_debris ) {
      create( static_cast<SpaceshipDebris *>(typed_body), views );
    } else if (type == BodyType::debris) {
      create( static_cast<Debris *>(typed_body), views );
    }
  }

  debug(2, "render all views");
for (size_t i = 0; i <= 3; i++){
for (size_t j = 0; j <= 2; j++){
  auto move = SquareMatrix4df{
    {1.0f, 0.0f, 0.0f,},
    {0.0f, 1.0f, 0.0f, },
    {0.0f, 0.0f, 1.0f, 0.0f},
    { tile_positions[i*3+j][0], tile_positions[i*3+j][1], 0.0f, 1.0f}
  };
  for (auto & view : views) {
    
    if(game.ship_exists()) {  

      SquareMatrix4df  spaceship_translation= { {1.0f,        0.0f,          0.0f, 0.0f},
                                    {0.0f,        1.0f,          0.0f, 0.0f},
                                    {0.0f,        0.0f,          1.0f, 0.0f},
                                    {-game.get_ship()->get_position()[0]+512, -game.get_ship()->get_position()[1]+368, 0.0f, 1.0f}};

        auto final_tramsform = world_transformation*move*spaceship_translation;
        
                view->render( final_tramsform );
    }else if(view->get_typed_body()->get_type() != BodyType::spaceship) {
        auto final_tramsform = world_transformation*move;
                view->render( final_tramsform );
    }
  }
}
}

  
  renderFreeShips(world_transformation);
  renderScore(world_transformation);

  SDL_GL_SwapWindow(window);
  debug(2, "render() exit.");
}

void OpenGLRenderer::exit() {
  views.clear();
  glDeleteBuffers(vertice_data.size(), vbos);
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow( window );
  SDL_Quit();
}
 
