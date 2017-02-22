#include "imgui.h"
#include "imgui-sfml.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

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
                const int              outlineThickness=1,
                const sf::Color        &outlineColor=sf::Color(0,0,0,0))
{
    sf::RectangleShape element;

    sf::Vector2i outerSize(size.x/3, size.y/3);
    sf::Vector2i innerSize(outerSize.x - outlineThickness*2,
                           outerSize.y - outlineThickness*2);

    element.setSize(sf::Vector2f(innerSize.x,innerSize.y));
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
                point.y += outerSize.x;
                point.x =  position.x;
            }

            element.setPosition(sf::Vector2f(point.x,point.y));

            if (depth == 1)
                window.draw(element);
            else{
                int thickness = outlineThickness > 1? outlineThickness/2 :
                                                      outlineThickness;
                drawFigure(window, point, outerSize, depth-1,
                           fillColor, thickness, outlineColor);
            }
         }
         point.x += outerSize.y;
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

        ImGui::End();

        window.clear(bgColor);
        drawGrid(window);
        drawFigure(window, figurePosition, figureSize, 0);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
