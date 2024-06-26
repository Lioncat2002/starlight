#include "glad.h"
#include "GLFW/glfw3.h"
#include "starlight.h"
GLFWwindow *window;

const int WINDOW_WIDTH=1024;
const int WINDOW_HEIGHT=768;

starlight::Editor editor;


starlight::Loader loader;
starlight::Renderer renderer;
std::shared_ptr<starlight::StaticShader> shader;

starlight::Light light;

const std::string VERTEX_FILE="res/shaders/Basic.vert";
const std::string FRAGMENT_FILE="res/shaders/Basic.frag";

starlight::Camera camera;

starlight::Entity base_level;

starlight::Entity player_small_tower1;
starlight::Entity player_small_tower2;

starlight::Entity enemy_small_tower1;
starlight::Entity enemy_small_tower2;


void key_callback(GLFWwindow* window1, int key, int scancode, int action, int mods)
{
    if(action==GLFW_PRESS && key==GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window1,true);
    //if (action == GLFW_PRESS)
    //camera.move(key);
    
}

int init(){
    if(!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

    window= glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"game", nullptr, nullptr);

    if(!window){
        fmt::println("failed to create window");
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(window);

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
    glfwSetKeyCallback(window,key_callback);

    editor.init(window);
    return true;
}

int load(){
    loader=starlight::Loader();
    camera=starlight::Camera({-3,12,3},-45.0f,-55.0f);

    light=starlight::Light({-2,4,-3},{1,1,1});


    base_level=starlight::AssetServer::AssetLoader(loader,
                                                   "res/models/clash_royale_base_level.obj",
                                                   "res/models/clash_royale_base_level.png");

    base_level.setPosition({0,0,-5});
    base_level.setScale({2,2,2});
    base_level.setTag("ground");

    player_small_tower1=starlight::AssetServer::AssetLoader(loader,
                                                            "res/models/clash_royale_small_tower.obj",
                                                            "res/models/clash_royale_small_tower.png");
    player_small_tower1.setPosition({2,0,1});
    player_small_tower1.setTag("player_tower");

    player_small_tower2=player_small_tower1;
    player_small_tower2.setPosition({-2,0,1});
    player_small_tower2.setTag("player_tower");

    enemy_small_tower1=player_small_tower1;
    enemy_small_tower1.setPosition({2,0,-9});
    enemy_small_tower1.setTag("enemy_tower");

    enemy_small_tower2=player_small_tower1;
    enemy_small_tower2.setPosition({-2,0,-9});
    enemy_small_tower2.setTag("enemy_tower");

    starlight::World::entities.push_back(player_small_tower1);
    starlight::World::entities.push_back(player_small_tower2);
    starlight::World::entities.push_back(enemy_small_tower1);
    starlight::World::entities.push_back(enemy_small_tower2);
    starlight::World::entities.push_back(base_level);

    shader= static_cast<const std::shared_ptr<starlight::StaticShader>>(new starlight::StaticShader(VERTEX_FILE,
                                                                                                    FRAGMENT_FILE));
    renderer=starlight::Renderer(*shader);
    return true;
}

int update(){


    for(auto &entity: starlight::World::entities){
        if(entity.getTag()=="enemy_tower"){
            fmt::println("Enemy tower: {}",glm::to_string(entity.getPosition()));
        }
    }

    editor.update();

    return true;
}


int render(){
    renderer.init();
    shader->start();
    shader->loadViewMatrix(camera);
    shader->loadLight(light);

    for(auto entity: starlight::World::entities){
        renderer.draw(entity,*shader);
    }

    shader->stop();

    editor.render();
    return true;
}

int main(){
    if(!init())
        return -1;

    if(!load())
        return -1;


    while(!glfwWindowShouldClose(window)){


        update();

        glfwPollEvents();
        render();
        glfwSwapBuffers(window);

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}