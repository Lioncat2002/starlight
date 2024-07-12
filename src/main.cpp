#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "starlight.h"
#include "game/barbarian/Barbarian.h"

GLFWwindow *window;

const int WINDOW_WIDTH=1024;
const int WINDOW_HEIGHT=768;

starlight::Editor editor;
starlight::Engine engine;


starlight::Loader loader;
starlight::Renderer renderer;
std::shared_ptr<starlight::StaticShader> shader;

starlight::Light light;

const std::string VERTEX_FILE="res/shaders/Basic.vert";
const std::string FRAGMENT_FILE="res/shaders/Basic.frag";

starlight::Camera camera;

/*starlight::Entity base_level;*/

game::Barbarian player_small_tower1;
game::Barbarian player_small_tower2;

/*starlight::Entity enemy_small_tower1;
starlight::Entity enemy_small_tower2;*/

std::unique_ptr<starlight::Entity> barbarian;

float lastFrame = 0.0f;

int init(){
    auto ok=engine.init(&window,WINDOW_WIDTH,WINDOW_HEIGHT);
    if(!ok){
        fmt::println("Something went wrong");
        return false;
    }
    editor.init(window);
    return true;
}

int load(){
    loader=starlight::Loader();
    camera=starlight::Camera({-3,12,3},-45.0f,-55.0f);

    light=starlight::Light({-2,4,-3},{1,1,1});


    /*base_level=starlight::AssetServer<game::Barbarian>::AssetLoader(loader,
                                                   "res/models/clash_royale_base_level.obj",
                                                   "res/models/clash_royale_base_level.png");

    base_level.setPosition({0,0,-5});
    base_level.setScale({2,2,2});
    base_level.setTag("ground");
    base_level.id=0;

    player_small_tower1=starlight::AssetServer::AssetLoader(loader,
                                                            "res/models/clash_royale_small_tower.obj",
                                                            "res/models/clash_royale_small_tower.png");
    player_small_tower1.setPosition({2,0,1});
    player_small_tower1.setTag("player_tower");
    player_small_tower1.id=1;

    player_small_tower2=player_small_tower1;
    player_small_tower2.setPosition({-2,0,1});
    player_small_tower2.setTag("player_tower");
    player_small_tower2.id=2;

    enemy_small_tower1=player_small_tower1;
    enemy_small_tower1.setPosition({2,0,-9});
    enemy_small_tower1.setTag("enemy_tower");
    enemy_small_tower1.data["health"]=10;
    enemy_small_tower1.id=3;

    enemy_small_tower2=player_small_tower1;
    enemy_small_tower2.setPosition({-2,0,-9});
    enemy_small_tower2.setTag("enemy_tower");
    enemy_small_tower2.data["health"]=10;
    enemy_small_tower2.id=4;
     */

   barbarian=starlight::AssetServer<game::Barbarian>::AssetLoader(loader,
                                                  "res/models/clash_royale_wip_barbarian.obj",
                                                  "res/models/clash_royale_wip_barbarian.png");
    barbarian->setPosition({2,0,-1});
    barbarian->setTag("barbarian");
    barbarian->setId(1);

    /*starlight::World::entities.push_back(player_small_tower1);
    starlight::World::entities.push_back(player_small_tower2);
    starlight::World::entities.push_back(enemy_small_tower1);
    starlight::World::entities.push_back(enemy_small_tower2);
    starlight::World::entities.push_back(base_level);*/

    shader= static_cast<const std::shared_ptr<starlight::StaticShader>>(new starlight::StaticShader(VERTEX_FILE,
                                                                                                    FRAGMENT_FILE));
    renderer=starlight::Renderer(*shader);
    return true;
}

int c=0;

int update(){
    float currentFrame = glfwGetTime();
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    //starlight::Entity *tower=nullptr;
    bool found=false;
    /*for(auto entity=starlight::World::entities.begin();entity!=starlight::World::entities.end();){

        if(entity->getTag()=="enemy_tower" && !found){
            tower=&(*entity);
            found=true;
        }
        //utter bs code,
        //TODO: better modularized solution
        if(entity->get()->getTag()=="barbarian" && tower!=nullptr){
            if(glm::distance(tower->getPosition(),entity->getPosition())>2){
                entity->position=starlight::Math::moveTowards(entity->getPosition(),tower->getPosition(),deltaTime,2);
            }else{
                if(c<5/deltaTime){
                    c+=1;
                }else{
                    entity->data["health"]-=2;
                    tower->data["health"]-=4;
                    c=0;
                    fmt::println("Barbarian health: {} Tower health: {}",entity->data["health"],tower->data["health"]);
                    if(tower->data["health"]<=0){
                        auto new_end = std::remove(starlight::World::entities.begin(), starlight::World::entities.end(), *tower);
                        entity=starlight::World::entities.erase(new_end, starlight::World::entities.end());

                        break;
                    }
                }
            }

        }
        entity++;
    }
*/
    editor.update();

    return true;
}


int render(){
    renderer.init();
    shader->start();
    shader->loadViewMatrix(camera);
    shader->loadLight(light);

    //for(auto entity=starlight::World::entities.begin();entity!=starlight::World::entities.end();){
     fmt::println("{}",barbarian->getId());
        renderer.draw(*barbarian,*shader);
    //}

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