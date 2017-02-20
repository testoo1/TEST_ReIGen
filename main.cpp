#include "imgui.h"
#include "imgui-sfml.h"

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

    int steps[]{12,24,96};
    sf::Color colors[]{sf::Color {35,85,125},
                       sf::Color {40,90,130},
                       sf::Color {60,110,150}};

    for(int i=0;i<3;++i)
        drawLine(window,line,colors[i],steps[i]);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                             sf::Style::Close);
    sf::Color bgColor(30,80,120);

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

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

        window.clear(bgColor);
        drawGrid(window);
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
