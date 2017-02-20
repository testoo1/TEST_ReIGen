#include "imgui.h"
#include "imgui-sfml.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                             sf::Style::Close);

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    window.resetGLStates();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                    window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowPos(ImVec2(600,0));
        ImGui::SetNextWindowSize(ImVec2(200,600));
        ImGui::Begin("Settings", false, ImGuiWindowFlags_NoTitleBar|
                                        ImGuiWindowFlags_NoResize|
                                        ImGuiWindowFlags_NoMove|
                                        ImGuiWindowFlags_NoCollapse|
                                        ImGuiWindowFlags_ShowBorders);

        ImGui::End();

        window.clear();
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
