#include <iostream>
#include "glad.h"
#include "GLFW/glfw3.h"
#include "starlight.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
GLFWwindow *window;

const int WINDOW_WIDTH=1024;
const int WINDOW_HEIGHT=768;

starlight::Loader loader;
starlight::Renderer renderer;
std::shared_ptr<starlight::StaticShader> shader;

const std::string VERTEX_FILE="res/shaders/Basic.vert";
const std::string FRAGMENT_FILE="res/shaders/Basic.frag";

starlight::RawModel model;
starlight::Texture texture;
starlight::Model texturedModel;
starlight::Entity entity;
starlight::Camera camera;

void key_callback(GLFWwindow* window1, int key, int scancode, int action, int mods)
{
    if(action==GLFW_PRESS && key==GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window1,true);
    //if (action == GLFW_PRESS)
    camera.move(key);
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
    loader=starlight::Loader();
    std::string path="res/models/another_tree.obj";
    model=loader.loadModelFromFile(path);
    texture=starlight::Texture(loader.loadTexture("res/models/another_tree.png"));
    texturedModel=starlight::Model(model,texture);

    entity=starlight::Entity(texturedModel, {0,0,-10},{0,0,0},{1.0f,1.0f,1.0f});
    camera=starlight::Camera({0,2,10},0.0f,0.0f);

    shader= static_cast<const std::shared_ptr<starlight::StaticShader>>(new starlight::StaticShader(VERTEX_FILE,
                                                                                                    FRAGMENT_FILE));
    renderer=starlight::Renderer(*shader);
    return true;
}
int render(){
    renderer.init();
    shader->start();
    shader->loadViewMatrix(camera);
    renderer.draw(entity,*shader);
    shader->stop();
    return true;
}
int update(){
    while(!glfwWindowShouldClose(window)){
        entity.increaseRotation({0,0.02,0});
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
    return 0;
}