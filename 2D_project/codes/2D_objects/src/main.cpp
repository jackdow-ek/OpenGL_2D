
#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <stb_image.h>
#include "Timer.hpp"
#include "FileLoader.hpp"
#include "ShaderProgram.hpp"
#include "GuiControl.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"
#include "VertexTypes.hpp"
#include "MeshManager.hpp"
#include "Mesh2D.hpp"
using namespace std;
ShaderProgram program;
GuiControl imguiWindow;
unsigned int textureId;
Timer timer;
bool lbutton_down = false;
MeshManager meshManager;
bool ilkCisim = false;
bool press = false;
std::vector<Mesh2D*> listem;
int i = -1;

glm::mat3 mtxTransform;
glm::vec2 vecMove;
float angle;
glm::vec2 scale = glm::vec2(1.0f,1.0f);

void sekilSilin(TYPE type){
    if(type==sil && i>0)
    {
        vecMove = listem[i-1]->getPosition();
        i -= 1;
        listem.pop_back();
        
    }
}

void sekilOlustur(SHAPETYPE type)
{
    if(type==SHAPE_CIRCLE)
    {
        ilkCisim = true;
        listem.push_back(new Mesh2D());
        i++;
        listem[i]= meshManager.createCircle();
        vecMove = glm::vec2(0.0f,0.0f);
        scale = glm::vec2(1.0f,1.0f);
    }
    if(type==SHAPE_SQUARE)
    {
        ilkCisim = true;
        listem.push_back(new Mesh2D());
        i++;
        listem[i]= meshManager.createSquare();
        vecMove = glm::vec2(0.0f,0.0f);
        scale = glm::vec2(1.0f,1.0f);
    }
    if(type==SHAPE_TRIANGLE)
    {
        ilkCisim = true;
        listem.push_back(new Mesh2D());
        i++;
        listem[i]= meshManager.createTriangle();
        vecMove = glm::vec2(0.0f,0.0f);
        scale = glm::vec2(1.0f,1.0f);
    }    
    if(type==SHAPE_HEXAGON)
    {
        ilkCisim = true;
        listem.push_back(new Mesh2D());
        i++;
        listem[i]= meshManager.createHexagon();
        vecMove = glm::vec2(0.0f,0.0f);
        scale = glm::vec2(1.0f,1.0f);
    }
}

unsigned int loadTexture(std::string fileName)
{
    unsigned int id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    int width,height,nrChannels;
    auto data = stbi_load(fileName.c_str(),&width,&height,&nrChannels,0);
  
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    return id;
}
void keyboard_callback(GLFWwindow* window,int key,int scanCode,int action,int mods)
{
    if(key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if(key==GLFW_KEY_LEFT)
        vecMove.x-=0.1;
        i = 1;
    if(key==GLFW_KEY_RIGHT)
        vecMove.x+=0.1;
    if(key==GLFW_KEY_UP)
        vecMove.y+=0.1;
    if(key==GLFW_KEY_DOWN)
        vecMove.y-=0.1;   
        
}



void cursorPositionCallBack(GLFWwindow* window,double xPos,double yPos)
{
    if(press == true){
        vecMove.x =  xPos/250 -1;
        vecMove.y =  -yPos/250 + 1; 
    }
    
}


void mouseButtonCallBack(GLFWwindow* window,int  button ,int action,int  mods){
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if(GLFW_PRESS == action)
            press = true;
            
        else if(GLFW_RELEASE == action)
            press = false;
    }
}

void initScene(GLFWwindow* window)
{
    program.attachShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    program.link();
    program.addUniform("uMtxTransform");

    imguiWindow.setPos(&vecMove);
    imguiWindow.setAngle(&angle);
    imguiWindow.setSca(&scale);
    imguiWindow.tiklaSekilOlustur= sekilOlustur;
    imguiWindow.sekilsil= sekilSilin;

    textureId =loadTexture("images/texture.jpg");

    imguiWindow.init(window);

    timer.start();
      
}
void draw()
{
    double elapsedTime = timer.elapsedSeconds();
    if(elapsedTime<0.016)
    {
        unsigned int miliseconds = (0.016-elapsedTime)*1000;

        timer.sleep(miliseconds);
    }
    glClearColor(0.3,0.4,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    program.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);  
    if(ilkCisim){
    
    listem[i]->setPosition(vecMove);
    listem[i]->setAngle(angle);
    listem[i]->draw(program);
    listem[i]->setScale(scale);
    
    
    
    
    for (auto &attack : listem) // access by reference to avoid copying
{  
    attack->draw(program);
}
    }

    
}

int main()
{
    if(!glfwInit())    return -1;

    GLFWwindow* window = glfwCreateWindow(500,500,"ilk program",0,0);
    if(window==nullptr)
    {
        std::cout<<"pencere olusmadi"<<std::endl;
        glfwTerminate();
        return -1;        
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window,keyboard_callback);
    glfwSetCursorPosCallback(window,cursorPositionCallBack);
    glfwSetMouseButtonCallback(window,mouseButtonCallBack);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"glad yukleme hatasi"<<std::endl;
    }
    

    initScene(window); 
   
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        draw();
        imguiWindow.createFrame();
        imguiWindow.createFrameItems();
        imguiWindow.draw();
        glfwSwapBuffers(window);
    }




    
}