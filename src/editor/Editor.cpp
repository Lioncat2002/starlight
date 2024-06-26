//
// Created by gamed on 26-06-2024.
//

#include "Editor.h"

namespace starlight {
    int Editor::init(GLFWwindow *window) {
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

    int Editor::update() {

        return true;
    }

    int Editor::render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::CreateContext();
        ImGui::NewFrame();

        {
            ImGui::Begin("Inspector");
            int i=0;
            for(auto &entity: starlight::World::entities){
                if(ImGui::TreeNode(fmt::format("tag: {} id: {}",entity.getTag(),i).c_str())){
                    ImGui::SliderFloat3("Position",&entity.position[0],-10,10);
                    ImGui::SliderFloat3("Rotation",&entity.rotation[0],-360,360);
                    ImGui::SliderFloat3("Scale",&entity.scale[0],0,100);
                    ImGui::TreePop();
                    i++;
                }
            }
            ImGui::End();
        }

        /*{
            ImGuiIO& io = ImGui::GetIO();
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            if(ImGui::TreeNode("root")){
                ImGui::Text("This is some useful text.");
                if(ImGui::TreeNode("kimton")){
                    ImGui::Text("Inner text.");
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }

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
*/

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        return true;
    }

    Editor::Editor() {

    }
} // starlight