#include "glad.h"
#include "GLFW/glfw3.h"
#include "starlight.h"
GLFWwindow *window;

const int WINDOW_WIDTH=1024;
const int WINDOW_HEIGHT=768;

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

std::vector<starlight::Entity> entities;

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

// Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
    return true;
}

int load(){
    loader=starlight::Loader();
    camera=starlight::Camera({-3,12,3},-45.0f,-55.0f);

    light=starlight::Light({-2,4,-3},{1,1,1});

    auto groundRawModel=loader.loadModelFromFile("res/models/clash_royale_base_level.obj");
    auto texture=starlight::Texture(loader.loadTexture("res/models/clash_royale_base_level.png"));
    auto groundModel=starlight::Model(groundRawModel,texture);

    base_level=starlight::Entity(groundModel, {0,0,-5},{0,0,0},{2.0f,2.0f,2.0f},"ground");

    auto smallTowerRawModel=loader.loadModelFromFile("res/models/clash_royale_small_tower.obj");
    texture=starlight::Texture(loader.loadTexture("res/models/clash_royale_small_tower.png"));
    auto smallTowerModel=starlight::Model(smallTowerRawModel,texture);

    player_small_tower1=starlight::Entity(smallTowerModel,{2,0,1},{0,0,0},{1.0f,1.0f,1.0f},"tower");
    player_small_tower2=starlight::Entity(smallTowerModel,{-2,0,1},{0,0,0},{1.0f,1.0f,1.0f},"tower");

    enemy_small_tower1=starlight::Entity(smallTowerModel,{2,0,-9},{0,0,0},{1.0f,1.0f,1.0f},"enemy_tower");
    enemy_small_tower2=starlight::Entity(smallTowerModel,{-2,0,-9},{0,0,0},{1.0f,1.0f,1.0f},"enemy_tower");

    entities.push_back(player_small_tower1);
    entities.push_back(player_small_tower2);
    entities.push_back(enemy_small_tower1);
    entities.push_back(enemy_small_tower2);
    entities.push_back(base_level);

    shader= static_cast<const std::shared_ptr<starlight::StaticShader>>(new starlight::StaticShader(VERTEX_FILE,
                                                                                                    FRAGMENT_FILE));
    renderer=starlight::Renderer(*shader);
    return true;
}

int update(){

    // (Your code calls glfwPollEvents())
// ...
// Start the Dear ImGui frame

    for(auto entity: entities){
        if(entity.tag=="enemy_tower"){
            fmt::println("Enemy tower: {}",glm::to_string(entity.getPosition()));
        }
    }
    // Rendering
// (Your code clears your framebuffer, renders your other stuff etc.)

// (Your code calls glfwSwapBuffers() etc.)

    return true;
}


int render(){
    renderer.init();
    shader->start();
    shader->loadViewMatrix(camera);
    shader->loadLight(light);

    for(auto entity: entities){
        renderer.draw(entity,*shader);
    }

    shader->stop();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::CreateContext();

    ImGui::NewFrame();

    {
        ImGuiIO& io = ImGui::GetIO();
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)


        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)


        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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