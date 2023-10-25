#include <iostream>
#include "glad.h"
#include "GLFW/glfw3.h"
#include "starlight.h"

GLFWwindow *window;

const int WINDOW_WIDTH=1024;
const int WINDOW_HEIGHT=768;

starlight::Loader *loader;
starlight::Renderer *renderer;
starlight::StaticShader *shader;

const std::string VERTEXFILE="res/shaders/Basic.vert";
const std::string FRAGMENTFILE="res/shaders/Basic.frag";


starlight::RawModel model;
starlight::Texture *texture;
starlight::Model *texturedModel;
starlight::Entity *entity;
starlight::Camera *camera;

/*float vertices[]={
        //left bottom triangle
        -0.5f,0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.5f,0.5f,0.0f,
};

int indices[]={
        0,1,3,
        3,1,2,
};

float textureCoords[]={
        0,0,
        0,1,
        1,1,
        1,0,
};*/
std::vector<float> vertices = {
        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,0.5f,-0.5f,

        -0.5f,0.5f,0.5f,
        -0.5f,-0.5f,0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,0.5f,0.5f,

        0.5f,0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f,
        0.5f,0.5f,0.5f,

        -0.5f,0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,0.5f,
        -0.5f,0.5f,0.5f,

        -0.5f,0.5f,0.5f,
        -0.5f,0.5f,-0.5f,
        0.5f,0.5f,-0.5f,
        0.5f,0.5f,0.5f,

        -0.5f,-0.5f,0.5f,
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,0.5f

};

std::vector<float> textureCoords = {

        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0,
        0,0,
        0,1,
        1,1,
        1,0


};

std::vector<int> indices = {
        0,1,3,
        3,1,2,
        4,5,7,
        7,5,6,
        8,9,11,
        11,9,10,
        12,13,15,
        15,13,14,
        16,17,19,
        19,17,18,
        20,21,23,
        23,21,22

};
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action==GLFW_PRESS && key==GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window,true);
    //if (action == GLFW_PRESS)
    camera->move(key);
}

int init(){
    if(!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,true);

    window= glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"game", nullptr, nullptr);

    if(!window){
        std::cout<<"Failed to create window\n";
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout<<"Failed to initialize GLAD\n";
        return false;
    }

    //glClearColor(0.6f,0.8f,1.0f,1.0f);
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(window,key_callback);
    return true;
}

int load(){
    loader=new starlight::Loader();

    int length=sizeof(vertices)/sizeof(vertices[0]);
    int indices_length=sizeof(indices)/sizeof (indices[0]);
    int textureCoords_length=sizeof(textureCoords)/sizeof(textureCoords[0]);

    model=loader->loadToVao(vertices,indices,textureCoords);
    texture=new starlight::Texture(loader->loadTexture("res/tile_0040.png"));
    texturedModel=new starlight::Model(model,*texture);

    entity=new starlight::Entity(*texturedModel, {0,0,-10},{0,0,0},{1.0f,1.0f,1.0f});
    camera=new starlight::Camera({0,0,0},0.0f,0.0f);
    shader=new starlight::StaticShader(VERTEXFILE,FRAGMENTFILE);
    renderer=new starlight::Renderer(*shader);
    return true;
}
int render(){
    renderer->init();
    shader->start();
    shader->loadViewMatrix(*camera);
    renderer->draw(*entity,*shader);
    shader->stop();
    return true;
}
int update(){
    while(!glfwWindowShouldClose(window)){
        entity->increaseRotation({0,0.02,0});
        render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    return true;
}

int main(){
    if(!init())
        return -1;

    if(!load())
        return -1;

    update();
    glfwTerminate();
    delete loader;
    delete renderer;
    delete shader;
    delete texture;
    delete texturedModel;
    delete entity;

    return 0;
}