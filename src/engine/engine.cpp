//
// Created by gamed on 27-06-2024.
//

#include "engine.h"

namespace starlight {
    void key_callback(GLFWwindow* window1, int key, int scancode, int action, int mods)
    {
        if(action==GLFW_PRESS && key==GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window1,true);
        //if (action == GLFW_PRESS)
        //camera.move(key);

    }
    int Engine::init(GLFWwindow **window, int WINDOW_WIDTH,int WINDOW_HEIGHT) {
        if(!glfwInit())
            return -1;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

        *window= glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"game", nullptr, nullptr);

        if(!*window){
            fmt::println("failed to create window");
            glfwTerminate();

            return false;
        }

        glfwMakeContextCurrent(*window);

        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
            fmt::println("failed to initialize GLAD");
            return false;
        }

#ifdef _DEBUG
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(starlight::LogUtils::glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
#endif
        //glClearColor(0.6f,0.8f,1.0f,1.0f);
        glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);
        glEnable(GL_DEPTH_TEST);
        glfwSetKeyCallback(*window,key_callback);
        return true;
    }
    Engine::Engine() = default;


} // starlight