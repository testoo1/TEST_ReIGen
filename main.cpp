#include "imgui.h"
#include "imgui-sfml.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Background.hpp"
#include "Figure.hpp"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


int main()
{
    // SFML and ImGui Init
    sf::RenderWindow window(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                             sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    std::array<sf::RenderTexture,2> renderTexture;  
    // [0] -> Background, [1] -> Figure

    for(auto &texture: renderTexture)
        texture.create(window.getSize().x, window.getSize().y);

    // Set color settings
    Background bg;
    int imGui_FillColor[4]{255,255,255,255};
    int imGui_outlineColor[4]{0,0,0,255};
    int imGui_bgColor[4]{bg.color().r, bg.color().g, bg.color().b, bg.color().a};


    // Set Figure settings
    int uiWidth = 200;
    sf::Vector2i canvasCenter((window.getSize().x - uiWidth)/2,
                               window.getSize().y/2);

    Figure  SierpinskiCarpet(canvasCenter, sf::Vector2i(450,450), 5);


    const char* type[]{"Curve","Gasket"};
    int typeIndex = 1;

    const char* gasketSubType[]{"Sierpinski sieves","Sierpinski carpet"};
    int gasketSubTypeIndex = 1;

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding.x = 32;
    // style.ItemSpacing.y   = 0;


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
        ImGui::SetNextWindowSize(ImVec2(uiWidth,600));

        ImGui::Begin("Settings", false, ImGuiWindowFlags_NoTitleBar|
                                        ImGuiWindowFlags_NoResize|
                                        ImGuiWindowFlags_NoMove|
                                        ImGuiWindowFlags_NoCollapse|
                                        ImGuiWindowFlags_ShowBorders);
        ImGui::Text("");
        ImGui::Text("Type");
        ImGui::Combo("##Type", &typeIndex, type,
                     IM_ARRAYSIZE(type));

        ImGui::Text("");
        ImGui::Text("Subtype");
        ImGui::Combo("##Subtype", &gasketSubTypeIndex, gasketSubType,
                     IM_ARRAYSIZE(gasketSubType));

        ImGui::Text("");
        ImGui::Separator();
        ImGui::Text("");

        ImGui::Text("Recursion depth");
        if(ImGui::SliderInt("##Recursion depth", &SierpinskiCarpet._depth, 0, 5)){
            SierpinskiCarpet.needRedraw();
        }
        ImGui::Text("");

        ImGui::Text("Image Scale");
        if(ImGui::SliderFloat("##Image Scale", &SierpinskiCarpet._scale, 0.5, 2))
        {
            SierpinskiCarpet.calcSize();
            SierpinskiCarpet.calcStartPoint();

            SierpinskiCarpet.needRedraw();
        }

        ImGui::Text("");
        ImGui::Separator();
        ImGui::Text("");

        ImGui::Text("Fill Color");
        if(ImGui::DragInt4("##Fill Color", imGui_FillColor, 1, 0, 255)){
            SierpinskiCarpet._color.r = imGui_FillColor[0];
            SierpinskiCarpet._color.g = imGui_FillColor[1];
            SierpinskiCarpet._color.b = imGui_FillColor[2];
            SierpinskiCarpet._color.a = imGui_FillColor[3];

            SierpinskiCarpet.needRedraw();
        }

        ImGui::Text("Outline Color");
        if(ImGui::DragInt4("##Outline Color", imGui_outlineColor, 1, 0, 255)){
            SierpinskiCarpet._outline._color.r = imGui_outlineColor[0];
            SierpinskiCarpet._outline._color.g = imGui_outlineColor[1];
            SierpinskiCarpet._outline._color.b = imGui_outlineColor[2];
            SierpinskiCarpet._outline._color.a = imGui_outlineColor[3];

            SierpinskiCarpet.needRedraw();
        }

        ImGui::Text("");
        ImGui::Text("Outline Thickness");
        if(ImGui::SliderInt("##outline Thickness",
                         &SierpinskiCarpet._outline._thickness, 0, -16)){
            SierpinskiCarpet.needRedraw();
        }

        ImGui::Text("");
        ImGui::Separator();
        ImGui::Text("");

        ImGui::Text("Background color");
        if(ImGui::DragInt4("##Background color", imGui_bgColor, 1, 0, 255)){
            bg.color(sf::Color(imGui_bgColor[0],imGui_bgColor[1],
                               imGui_bgColor[2],imGui_bgColor[3]));

            bg.needRedraw();
        }
        ImGui::End();


        bg.draw(renderTexture[0]);
        SierpinskiCarpet.draw(renderTexture[1]);

        window.clear();

        for(auto &texture: renderTexture)
            window.draw(sf::Sprite(texture.getTexture()));

        window.resetGLStates();

        //ImGui::ShowTestWindow();
        ImGui::Render();

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
