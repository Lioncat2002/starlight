#pragma once
#include "glad.h"
#include "GLFW/glfw3.h"
#include "starlight.h"
namespace starlight {



    class Engine {
    public:
        Engine();
        int init(GLFWwindow **window, int WINDOW_WIDTH,int WINDOW_HEIGHT);
    };

} // starlight
