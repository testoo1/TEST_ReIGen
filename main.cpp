#include "imgui.h"
#include "imgui-sfml.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

// TEMP
enum class Direction{
    HORIZONTAL,
    VERTICAL,
    BOTH
};

void drawLine(sf::RenderWindow &window, sf::RectangleShape &line,
              const sf::Color &color=sf::Color::White, const int step=10,
              const Direction direction=Direction::BOTH, const int lineWidth=1)
{
    if(direction == Direction::BOTH){
        drawLine(window, line, color, step, Direction::HORIZONTAL);
        drawLine(window, line, color, step, Direction::VERTICAL);
    }
    else{
        sf::Vector2u winSize{window.getSize()};
        int edge{0};

        line.setFillColor(color);

        switch(direction){
            case Direction::HORIZONTAL:
                edge = window.getSize().x;
                line.setSize(sf::Vector2f(edge,lineWidth));
                break;
            case Direction::VERTICAL:
                edge = window.getSize().y;
                line.setSize(sf::Vector2f(lineWidth,edge));
                break;
        }


        for(int i=0; i<edge; i+=step){
            switch(direction){
                case Direction::HORIZONTAL:
                    line.setPosition(0,i);
                    break;
                case Direction::VERTICAL:
                    line.setPosition(i,0);
                    break;
            }
            window.draw(line);
        }
    }

}


void drawGrid(sf::RenderWindow &window)
{
    sf::RectangleShape line;

    int steps[]{12, 24, 96};
    sf::Color colors[]{sf::Color {35,85,125},
                       sf::Color {40,90,130},
                       sf::Color {60,110,150}};

    for(int i=0;i<3;++i)
        drawLine(window, line,colors[i], steps[i]);
}


// Exist some problem with rounding of <Vector2i size> variable
// For example:
// if init <size.x> value = 200, is losed 2 pixel when program
// step into next recurtion level (200/3 -> 198)
void drawFigure(      sf::RenderWindow &window,
                const sf::Vector2i     &position,
                const sf::Vector2i     &size,
                const int              depth,
                const sf::Color        &fillColor=sf::Color::White,
                const int              outlineThickness=-1,
                const sf::Color        &outlineColor=sf::Color(0,0,0,0))
{
    sf::RectangleShape element;

    element.setSize(sf::Vector2f(size.x/3, size.y/3));
    element.setFillColor(fillColor);

    element.setOutlineThickness(outlineThickness);
    element.setOutlineColor(outlineColor);


    sf::Vector2i point(position);

    if (depth == 0){
        element.setSize(sf::Vector2f(size.x,size.y));
        element.setPosition(sf::Vector2f(position.x,position.y));
        window.draw(element);
        return;
    }

    for (int i=0; i<9; ++i)
    {
        if (i != 4){
            if (i!= 0 && !(i%3)){
                point.y += size.x/3;
                point.x =  position.x;
            }

            element.setPosition(sf::Vector2f(point.x,point.y));

            if (depth == 1)
                window.draw(element);
            else{
                int thickness = outlineThickness < -1? outlineThickness/2 :
                                                       outlineThickness;
                drawFigure(window, point, size/3, depth-1,
                           fillColor, thickness, outlineColor);
            }
         }
         point.x += size.y/3;
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                             sf::Style::Close);
    ImGui::SFML::Init(window);


    sf::Color bgColor(30,80,120);
    int uiWidth = 200;

    sf::Clock deltaClock;


    sf::Vector2i canvasCenter((window.getSize().x - uiWidth)/2,
                               window.getSize().y/2);
    sf::Vector2i figureSize(450,450);
    sf::Vector2i figurePosition(canvasCenter.x - figureSize.x/2,
                                canvasCenter.y - figureSize.y/2);


    const char* type[]{"Curve","Gasket"};
    int typeIndex = 1;

    const char* gasketSubType[]{"Sierpinski sieves","Sierpinski carpet"};
    int gasketSubTypeIndex = 1;

    int recDepth = 5;

    sf::Color fillColor{255,255,255,255};
    int imGui_fillColor[4]{fillColor.r,
                           fillColor.g,
                           fillColor.b,
                           fillColor.a};

    sf::Color outlineColor{0,0,0,255};
    int imGui_outlineColor[4]{outlineColor.r,
                              outlineColor.g,
                              outlineColor.b,
                              outlineColor.a};

    int outlineThickness{0};

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
        ImGui::SliderInt("##Recursion depth", &recDepth, 0, 5);
        ImGui::Text("");

        ImGui::Separator();

        ImGui::Text("");
        ImGui::Text("Fill Color");
        if(ImGui::DragInt4("##Fill Color", imGui_fillColor, 1, 0, 255)){
            fillColor.r = imGui_fillColor[0];
            fillColor.g = imGui_fillColor[1];
            fillColor.b = imGui_fillColor[2];
            fillColor.a = imGui_fillColor[3];
        }
        ImGui::Text("Outline Color");
        if(ImGui::DragInt4("##Outline Color", imGui_outlineColor, 1, 0, 255)){
            outlineColor.r = imGui_outlineColor[0];
            outlineColor.g = imGui_outlineColor[1];
            outlineColor.b = imGui_outlineColor[2];
            outlineColor.a = imGui_outlineColor[3];
        }

        ImGui::Text("");
        ImGui::Text("Outline Thickness");
        ImGui::SliderInt("##outline Thickness", &outlineThickness, 0, 16);

        ImGui::End();


        window.clear(bgColor);
        drawGrid(window);
        drawFigure(window, figurePosition, figureSize, recDepth,
                    fillColor, -outlineThickness, outlineColor);
        // ImGui::ShowTestWindow();
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
