#pragma once
#include "starlight.h"

namespace starlight {

    class Editor {

    public:
        Editor();
        int init(GLFWwindow *window);
        int update();
        int render();

    };

} // starlight

