// 
// Michael Shafae
// mshafae at fullerton.edu
// 
// The two Utah teapot floating in space. Camera can be rotated up/down
// and left right. The camera's transformations are defined/implemented
// in transformations.h/cpp.
//
// Each teapot has it's own shading program but share the two light sources.
// The lights are defined as objects named SpinningLight.
//
// This demonstration program requires that you provide your own GFXMath.h.
//
// $Id: two_shaders_glfw.cpp 5723 2015-04-15 22:25:35Z mshafae $
//

#include <cstdlib>
#include <cstdio>
#include <sys/time.h>

#include "GLFWApp.h"
#include "GFXMath.h"

#include "GLSLShader.h"
#include "transformations.h"
#include "hookes_law.cpp"

bool pause = false;
int width = 50;
int height = 50;
Mesh m = Mesh(width,height,1);
int counter = 0;
GLenum type = GL_FILL;

void saveFrame(int width, int height, string i){
  BYTE* pixels = new BYTE[3 * width * height];
  string name = "/Users/anacarolina/Documents/Fullerton/Academic Training/LiquidSimulation/Tests/two_shaders/imgs/test_"+i+".bmp";
  const char * filename = name.c_str();

  glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

  FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, 0x0000FF, 0xFF0000, 0x00FF00, false);
  FreeImage_Save(FIF_BMP, image, filename, 0);
  FreeImage_Unload(image);
  delete [] pixels;
}

Vec3 vertexNormal(int i){
  Vec3 normal = Vec3(0,0,0);
  
  return normal;
}

Vec3 normal(Vec3 a, Vec3 b, Vec3 c){
  Vec3 u,v;
  u = c - b;
  v = a - b;

  return normalize(cross(u,v));
}

Vec3 faceNormal(int i){
  Vec3 u,v;
  if (i < m.indexBuffer.size()-2){
    if(i % 2 == 0){
      // upper
      return normal(m.vertexList[m.indexBuffer[i+1]].oldPosition,m.vertexList[m.indexBuffer[i]].oldPosition,m.vertexList[m.indexBuffer[i+2]].oldPosition);
    }
    else{
      // lower
      return normal(m.vertexList[m.indexBuffer[i+2]].oldPosition,m.vertexList[m.indexBuffer[i]].oldPosition,m.vertexList[m.indexBuffer[i+1]].oldPosition);
    }
  }
  else{
    return Vec3(0,0,0);
  }
}

void drawMesh(){
  glPolygonMode(GL_FRONT_AND_BACK, type);
  glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < m.indexBuffer.size(); i++){
      glNormal3fv((float*)faceNormal(i));
      glVertex3fv((float*)m.vertexList[m.indexBuffer[i]].oldPosition);     
    }
  glEnd();
  glFlush();
}

void msglVersion(void){
  fprintf(stderr, "OpenGL Version Information:\n");
  fprintf(stderr, "\tVendor: %s\n", glGetString(GL_VENDOR));
  fprintf(stderr, "\tRenderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stderr, "\tOpenGL Version: %s\n", glGetString(GL_VERSION));
  fprintf(stderr, "\tGLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void instructions(void){
  fprintf(stderr, "Keyboard control:\n");
  fprintf(stderr, "\tP - pause\n");
  fprintf(stderr, "\tU - unpause\n");
  fprintf(stderr, "\tR - restart camera and lights positions\n");
  fprintf(stderr, "\tQ/Escape - quit\n");
  fprintf(stderr, "\tArrow keys - control camera\n");
  fprintf(stderr, "\tW,A,S and D - control light 1\n");
  fprintf(stderr, "\tY,G,H and J - control light 2\n");
  fprintf(stderr, "\tEnter - capture screenshot\n");
  fprintf(stderr, "\tSpace - reapply force\n");
}

class SpinningLight{
public:
  Vec3 d;
  Vec3 upVector;

  SpinningLight( ){ }
  SpinningLight(Vec3& color, Vec3& position, Vec3& center) :
    _color(color), _position(position), _center(center){
      // Fill me in!
      d = direction();
      Vec3 aux = Vec3(d[0]+1, d[1], d[2]);
      upVector = cross(d,aux);

    }

  Vec4 color( ){return Vec4(_color, 1.0);}
  Vec4 position( ){return Vec4(_position, 1.0);}
  
  void rotateUp(float degrees){
    // Fill me in!
    Vec3 axis = normalize(cross(_position, upVector));
    Mat4 rotation = rotate(degrees, axis);
    Mat3 rotMat;

    rotMat[0][0] = rotation[0][0];
    rotMat[0][1] = rotation[0][1];
    rotMat[0][2] = rotation[0][2];
    rotMat[1][0] = rotation[1][0];
    rotMat[1][1] = rotation[1][1];
    rotMat[1][2] = rotation[1][2];
    rotMat[2][0] = rotation[2][0];
    rotMat[2][1] = rotation[2][1];
    rotMat[2][2] = rotation[2][2];

    _position = (rotMat * (_position - _center)) + _center;

    upVector = normalize(rotMat*upVector);
    
  }

  void rotateLeft(float degrees){
    // Fill me in!

    Vec3 upNorm = normalize(upVector);
    Mat4 rotation = rotate(degrees, upNorm);
    Mat3 rotMat;

    rotMat[0][0] = rotation[0][0];
    rotMat[0][1] = rotation[0][1];
    rotMat[0][2] = rotation[0][2];
    rotMat[1][0] = rotation[1][0];
    rotMat[1][1] = rotation[1][1];
    rotMat[1][2] = rotation[1][2];
    rotMat[2][0] = rotation[2][0];
    rotMat[2][1] = rotation[2][1];
    rotMat[2][2] = rotation[2][2];

    _position = (rotMat * (_position - _center)) + _center;
  }
  
  void roll(float degrees){
    // Fill me in!

    Vec3 axis = normalize((_center - _position));
    Mat4 rotation = rotate(degrees, axis);
    Mat3 rotMat;

    rotMat[0][0] = rotation[0][0];
    rotMat[0][1] = rotation[0][1];
    rotMat[0][2] = rotation[0][2];
    rotMat[1][0] = rotation[1][0];
    rotMat[1][1] = rotation[1][1];
    rotMat[1][2] = rotation[1][2];
    rotMat[2][0] = rotation[2][0];
    rotMat[2][1] = rotation[2][1];
    rotMat[2][2] = rotation[2][2];

    upVector = normalize(rotMat*upVector);
  }
  
private:
  Vec3 _color;
  Vec3 _position;
  Vec3 _center;
  Vec3 _tangent;
  
  Vec3 direction( ){
    Vec3 d;
    // Fill me in!
    d = _center - _position;

    return d;
  }
};

class TwoShadersApp : public GLFWApp{
private:
  float rotationDelta;

  Vec3 centerPosition;
  Vec3 eyePosition;
  Vec3 upVector;

  // Vec3 teapotTranslation_A;
  // Vec3 teapotTranslation_B;

  Mat4 modelViewMatrix;
  Mat4 projectionMatrix;
  Mat4 normalMatrix;
  
  GLSLProgram shaderProgram;
  // GLSLProgram shaderProgram_A;
  // GLSLProgram shaderProgram_B;

  SpinningLight light0;
  SpinningLight light1; 

  // Variables to set uniform params for lighting fragment shader 
  unsigned int uModelViewMatrix;
  unsigned int uProjectionMatrix;
  unsigned int uNormalMatrix;
  unsigned int uLight0_position;
  unsigned int uLight0_color;
  unsigned int uLight1_position;
  unsigned int uLight1_color;

  // unsigned int uModelViewMatrix_A;
  // unsigned int uProjectionMatrix_A;
  // unsigned int uNormalMatrix_A;
  // unsigned int uLight0_position_A;
  // unsigned int uLight0_color_A;
  // unsigned int uLight1_position_A;
  // unsigned int uLight1_color_A;
  
  // unsigned int uModelViewMatrix_B;
  // unsigned int uProjectionMatrix_B;
  // unsigned int uNormalMatrix_B;
  // unsigned int uLight0_position_B;
  // unsigned int uLight0_color_B;
  // unsigned int uLight1_position_B;
  // unsigned int uLight1_color_B;
  
public:
  TwoShadersApp(int argc, char* argv[]) :
    GLFWApp(argc, argv, std::string("Liquid Simulation").c_str( ), 
            1024, 768){ }
  
  void initCenterPosition( ){
    centerPosition = Vec3(width/2, 10.0, height/2);
  }
  
  void initEyePosition( ){
    eyePosition = Vec3(20.0, 20.0, 20.0);
  }

  void initUpVector( ){
    upVector = Vec3(0.0, 1.0, 0.0);
  }

  void initRotationDelta( ){
    rotationDelta = 5.0;
  }
   
  void initLights( ){
    // AJUSTAR ESSE CARALHO
    Vec3 color0(0.0, 0.0, 1.0);
    Vec3 position0(0,25,0);
    // Vec3 position0(0.13979, 0.34947, 15.88587);
    Vec3 color1(0.0, 0.0, 1.0);
    Vec3 position1(20,25,20);
    // Vec3 position1(0.13979, 0.34947, 15.88587);
    light0 = SpinningLight(color0, position0, centerPosition);
    light1 = SpinningLight(color1, position1, centerPosition);
  }
  
  // void initTeapotTransforms( ){
  //   teapotTranslation_A = Vec3(3.0, 0.0, 0.0);
  // //   teapotTranslation_B = Vec3(-3.0, 0.0, 0.0);
  // }
  
  bool begin( ){
    msglError( );
    initCenterPosition( );
    initEyePosition( );
    initUpVector( );
    initRotationDelta( );
    initLights( );
    // initTeapotTransforms( );
    
    // Load shader program 
    // const char* vertexShaderSource = "blinn_phong.vert.glsl";
    // const char* fragmentShaderSource = "blinn_phong.frag.glsl";
    const char* vertexShaderSource = "gouraud.vert.glsl";
    const char* fragmentShaderSource = "gouraud.frag.glsl";
    FragmentShader fragmentShader(fragmentShaderSource);
    VertexShader vertexShader(vertexShaderSource);
    shaderProgram.attach(vertexShader);
    shaderProgram.attach(fragmentShader);
    shaderProgram.link( );
    shaderProgram.activate( );
    
    printf("Shader program A built from %s and %s.\n",
           vertexShaderSource, fragmentShaderSource);
    if( shaderProgram.isActive( ) ){
      printf("Shader program is loaded and active with id %d.\n", shaderProgram.id( ) );
    }else{
      printf("Shader program did not load and activate correctly. Exiting.");
      exit(1);
    }

    // // Load shader program A
    // const char* vertexShaderSource_A = "gouraud.vert.glsl";
    // const char* fragmentShaderSource_A = "gouraud.frag.glsl";
    // FragmentShader fragmentShader_A(fragmentShaderSource_A);
    // VertexShader vertexShader_A(vertexShaderSource_A);
    // shaderProgram_A.attach(vertexShader_A);
    // shaderProgram_A.attach(fragmentShader_A);
    // shaderProgram_A.link( );
    // shaderProgram_A.activate( );
    
    // printf("Shader program A built from %s and %s.\n",
    //        vertexShaderSource_A, fragmentShaderSource_A);
    // if( shaderProgram_A.isActive( ) ){
    //   printf("Shader program is loaded and active with id %d.\n", shaderProgram_A.id( ) );
    // }else{
    //   printf("Shader program did not load and activate correctly. Exiting.");
    //   exit(1);
    // }
    
    // // Load shader program B
    // const char* vertexShaderSource_B = "blinn_phong.vert.glsl";
    // const char* fragmentShaderSource_B = "blinn_phong.frag.glsl";
    // FragmentShader fragmentShader_B(fragmentShaderSource_B);
    // VertexShader vertexShader_B(vertexShaderSource_B);
    // shaderProgram_B.attach(vertexShader_B);
    // shaderProgram_B.attach(fragmentShader_B);
    // shaderProgram_B.link( );
    // shaderProgram_B.activate( );
    
    // printf("Shader program B built from %s and %s.\n",
    //        vertexShaderSource_B, fragmentShaderSource_B);
    // if( shaderProgram_B.isActive( ) ){
    //   printf("Shader program is loaded and active with id %d.\n", shaderProgram_B.id( ) );
    // }else{
    //   printf("Shader program did not load and activate correctly. Exiting.");
    //   exit(1);
    // }
    
    // Set up uniform variables for shader program A
    uModelViewMatrix = glGetUniformLocation(shaderProgram.id( ), "modelViewMatrix");
    uProjectionMatrix = glGetUniformLocation(shaderProgram.id( ), "projectionMatrix");
    uNormalMatrix = glGetUniformLocation(shaderProgram.id( ), "normalMatrix");
    uLight0_position = glGetUniformLocation(shaderProgram.id( ), "light0_position");
    uLight0_color = glGetUniformLocation(shaderProgram.id( ), "light0_color");
    uLight1_position = glGetUniformLocation(shaderProgram.id( ), "light1_position");
    uLight1_color = glGetUniformLocation(shaderProgram.id( ), "light1_color");

    // // Set up uniform variables for shader program A
    // uModelViewMatrix_A = glGetUniformLocation(shaderProgram_A.id( ), "modelViewMatrix");
    // uProjectionMatrix_A = glGetUniformLocation(shaderProgram_A.id( ), "projectionMatrix");
    // uNormalMatrix_A = glGetUniformLocation(shaderProgram_A.id( ), "normalMatrix");
    // uLight0_position_A = glGetUniformLocation(shaderProgram_A.id( ), "light0_position");
    // uLight0_color_A = glGetUniformLocation(shaderProgram_A.id( ), "light0_color");
    // uLight1_position_A = glGetUniformLocation(shaderProgram_A.id( ), "light1_position");
    // uLight1_color_A = glGetUniformLocation(shaderProgram_A.id( ), "light1_color");
    
    // // Set up uniform variables for shader program B
    // uModelViewMatrix_B = glGetUniformLocation(shaderProgram_B.id( ), "modelViewMatrix");
    // uProjectionMatrix_B = glGetUniformLocation(shaderProgram_B.id( ), "projectionMatrix");
    // uNormalMatrix_B = glGetUniformLocation(shaderProgram_B.id( ), "normalMatrix");
    // uLight0_position_B = glGetUniformLocation(shaderProgram_B.id( ), "light0_position");
    // uLight0_color_B = glGetUniformLocation(shaderProgram_B.id( ), "light0_color");
    // uLight1_position_B = glGetUniformLocation(shaderProgram_B.id( ), "light1_position");
    // uLight1_color_B = glGetUniformLocation(shaderProgram_B.id( ), "light1_color");
    
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    msglVersion( );
    instructions( );
    
    return !msglError( );
  }
  
  bool end( ){
    windowShouldClose( );
    return true;
  }
  
  void activateUniforms(Vec4& _light0, Vec4& _light1){
    glUniformMatrix4fv(uModelViewMatrix, 1, false, modelViewMatrix);    
    glUniformMatrix4fv(uProjectionMatrix, 1, false, projectionMatrix);
    glUniformMatrix4fv(uNormalMatrix, 1, false, normalMatrix);
    glUniform4fv(uLight0_position, 1, _light0);
    glUniform4fv(uLight0_color, 1, light0.color( ));
    glUniform4fv(uLight1_position, 1, _light1);
    glUniform4fv(uLight1_color, 1, light1.color( ));
  }
  
  // void activateUniforms_A(Vec4& _light0, Vec4& _light1){
  //   glUniformMatrix4fv(uModelViewMatrix_A, 1, false, modelViewMatrix);    
  //   glUniformMatrix4fv(uProjectionMatrix_A, 1, false, projectionMatrix);
  //   glUniformMatrix4fv(uNormalMatrix_A, 1, false, normalMatrix);
  //   glUniform4fv(uLight0_position_A, 1, _light0);
  //   glUniform4fv(uLight0_color_A, 1, light0.color( ));
  //   glUniform4fv(uLight1_position_A, 1, _light1);
  //   glUniform4fv(uLight1_color_A, 1, light1.color( ));
  // }
  
  // void activateUniforms_B(Vec4& _light0, Vec4& _light1){
  //   glUniformMatrix4fv(uModelViewMatrix_B, 1, false, modelViewMatrix);
  //   glUniformMatrix4fv(uProjectionMatrix_B, 1, false, projectionMatrix);
  //   glUniformMatrix4fv(uNormalMatrix_B, 1, false, normalMatrix);
  //   glUniform4fv(uLight0_position_B, 1, _light0);
  //   glUniform4fv(uLight0_color_B, 1, light0.color( ));
  //   glUniform4fv(uLight1_position_B, 1, _light1);
  //   glUniform4fv(uLight1_color_B, 1, light1.color( ));
  // }
  
  bool render( ){
    Vec4 _light0;
    Vec4 _light1;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Vec2i w = windowSize( );
    double ratio = double(w[0]) / double(w[1]);
    glFrustum(-ratio, ratio, -ratio, ratio, 1.0f, 40.0f);

    projectionMatrix = perspective(90.0, ratio, 1.0, 25.0);

    Mat4 lookAtMatrix = lookat(eyePosition, centerPosition, upVector);

    // Set light & material properties for the teapot;
    // lights are transformed by current modelview matrix
    // such that they are positioned correctly in the scene.
    _light0 = lookAtMatrix * light0.position( );
    _light1 = lookAtMatrix * light1.position( );
    
    modelViewMatrix = lookAtMatrix * translate(Vec3(0,0,0));
    normalMatrix = modelViewMatrix.inverse( ).transpose( );
    shaderProgram.activate( );
    activateUniforms(_light0, _light1);

    // modelViewMatrix = lookAtMatrix * translate(teapotTranslation_A);
    // normalMatrix = modelViewMatrix.inverse( ).transpose( );
    // shaderProgram_A.activate( );
    // activateUniforms_A(_light0, _light1);
    // // _glutSolidTeapot(1.0);
    
    // // Let's reuse _light0 and _light1
    // modelViewMatrix = lookAtMatrix * translate(teapotTranslation_B);
    // normalMatrix = modelViewMatrix.inverse( ).transpose( );
    // shaderProgram_B.activate( );
    // activateUniforms_B(_light0, _light1);
    // // _glutSolidTeapot(1.0);

    drawMesh();
    if (counter <2000 && !pause){
      m.waves();
      // saveFrame(w[0], w[1], to_string(counter));
      counter ++;
    }
    
    if(isKeyPressed('Q')){
      end( );      
    }else if(isKeyPressed('P')){
      pause = true;
      cout<<"Paused, press U to unpause"<<endl;
    }else if(isKeyPressed('U')){
      pause = false;
    }else if(isKeyPressed('L')){
      type = GL_LINE;
    }else if(isKeyPressed('F')){
      type = GL_FILL;
    }else if(isKeyPressed(GLFW_KEY_ENTER)){
      // saveFrame(w[0], w[1], "");
    }else if(isKeyPressed(GLFW_KEY_SPACE)){
      m = Mesh(width,height,1);
      counter = 0;
    }else if(isKeyPressed(GLFW_KEY_EQUAL)){
      eyePosition = Vec3(eyePosition[0]-0.05,eyePosition[1]-0.05,eyePosition[2]-0.05);
    }else if(isKeyPressed(GLFW_KEY_MINUS)){
      eyePosition = Vec3(eyePosition[0]+0.05,eyePosition[1]+0.05,eyePosition[2]+0.05);
    }else if(isKeyPressed('R')){
      initEyePosition( );
      initUpVector( );
      initRotationDelta( );
      initLights( );  
      printf("Eye position, up vector and rotation delta reset.\n");
    }else if(isKeyPressed(GLFW_KEY_LEFT)){
      rotateCameraLeft(-rotationDelta, eyePosition,
                       centerPosition, upVector);
    }else if(isKeyPressed(GLFW_KEY_RIGHT)){
      rotateCameraLeft(rotationDelta, eyePosition,
                       centerPosition, upVector);
    }else if(isKeyPressed(GLFW_KEY_UP)){
      rotateCameraUp(-rotationDelta, eyePosition,
                     centerPosition, upVector);
    }else if(isKeyPressed(GLFW_KEY_DOWN)){
      rotateCameraUp(rotationDelta, eyePosition,
                     centerPosition, upVector);
    }else if(isKeyPressed('W')){
      light0.rotateUp(rotationDelta);
    }else if(isKeyPressed('S')){
      light0.rotateUp(-rotationDelta);
    }else if(isKeyPressed('A')){
      light0.rotateLeft(rotationDelta);
    }else if(isKeyPressed('D')){
      light0.rotateLeft(-rotationDelta);
    }else if(isKeyPressed('X')){
      light0.roll(rotationDelta);
    }else if(isKeyPressed('Y')){
      light1.rotateUp(rotationDelta);
    }else if(isKeyPressed('H')){
      light1.rotateUp(-rotationDelta);
    }else if(isKeyPressed('G')){
      light1.rotateLeft(rotationDelta);
    }else if(isKeyPressed('J')){
      light1.rotateLeft(-rotationDelta);
    }else if(isKeyPressed('N')){
      light1.roll(rotationDelta);
    }
    return !msglError( );
  }
    
};


int main(int argc, char* argv[]){
  TwoShadersApp app(argc, argv);
  return app();
}
