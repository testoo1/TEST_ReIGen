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




class Outline
{
public:
    sf::Color _color;
    int _thickness;

    Outline(const int thickness=1, const sf::Color color=sf::Color::Black):
        _color(color), _thickness(thickness) {}
};


class Figure{
public:
    sf::Vector2i _center;
    sf::Vector2i _size;
    sf::Vector2i _initSize;
    float _scale;

    int _depth;

    sf::Color _color;
    Outline _outline;

    sf::Vector2i _startPoint;

    Figure(const sf::Vector2i   &center,
           const sf::Vector2i   &initSize=sf::Vector2i(450,450),

           const int            depth=0,

           const sf::Color      &color=sf::Color::White,
           const Outline        &outline=Outline()):
                _center(center), _initSize(initSize), _scale(1),
                _color(color), _outline(outline),
                _depth(depth)
    {
        calcSize();
        calcStartPoint();
    }

    void draw(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window, int depth,
              sf::Vector2i position, sf::Vector2i size,
              int thickness);

    void calcSize(){
        _size.x = _initSize.x*_scale;
        _size.y = _initSize.y*_scale;
    }

    void calcStartPoint(){
        _startPoint.x = _center.x - _size.x/2;
        _startPoint.y = _center.y - _size.y/2;
    }
};


// Exist some problem with rounding of <Vector2i size> variable
// For example:
// if init <size.x> value = 200, is losed 2 pixel when program
// step into next recurtion level (200/3 -> 198)
void Figure::draw(sf::RenderWindow &window)
{
    draw(window, _depth, _startPoint, _size, _outline._thickness);
}

void Figure::draw(sf::RenderWindow &window, int depth,
                  sf::Vector2i position, sf::Vector2i size,
                  int thickness)
{
    sf::RectangleShape element;

    element.setFillColor(_color);

    element.setOutlineThickness(thickness);
    element.setOutlineColor(_outline._color);

    if (depth == 0){
        element.setSize(sf::Vector2f(size.x,size.y));
        element.setPosition(sf::Vector2f(_startPoint.x,_startPoint.y));
        window.draw(element);
        return;
    }

    element.setSize(sf::Vector2f(size.x/3, size.y/3));
    sf::Vector2i point(position);

    for (int i=1; i<=9; ++i)
    {
        if (i != 5){
            element.setPosition(sf::Vector2f(point.x,point.y));

            if (depth == 1)
                window.draw(element);
            else{

                draw(window, depth-1, point, size/3, thickness/2);
            }
         }
        if (!(i%3)){
            point.y += size.x/3;
            point.x =  position.x;
            continue;
        }
        point.x += size.y/3;
    }
}


int main()
{
    // SFML and ImGui Init
    sf::RenderWindow window(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                             sf::Style::Close);
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;


    // Set color settings
    sf::Color bgColor(30,80,120);
    int imGui_FillColor[4]{255,255,255,255};
    int imGui_outlineColor[4]{0,0,0,255};

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
        ImGui::SliderInt("##Recursion depth", &SierpinskiCarpet._depth, 0, 5);
        ImGui::Text("");

        ImGui::Text("Image Scale");
        if(ImGui::SliderFloat("##Image Scale", &SierpinskiCarpet._scale, 0.5, 2))
        {
           SierpinskiCarpet.calcSize();
           SierpinskiCarpet.calcStartPoint();
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
        }

        ImGui::Text("Outline Color");
        if(ImGui::DragInt4("##Outline Color", imGui_outlineColor, 1, 0, 255)){
           SierpinskiCarpet._outline._color.r = imGui_outlineColor[0];
           SierpinskiCarpet._outline._color.g = imGui_outlineColor[1];
           SierpinskiCarpet._outline._color.b = imGui_outlineColor[2];
           SierpinskiCarpet._outline._color.a = imGui_outlineColor[3];
        }

        ImGui::Text("");
        ImGui::Text("Outline Thickness");
        ImGui::SliderInt("##outline Thickness",
                         &SierpinskiCarpet._outline._thickness, 0, -16);

        ImGui::End();


        window.clear(bgColor);
        drawGrid(window);
        SierpinskiCarpet.draw(window);
        // ImGui::ShowTestWindow();
        ImGui::Render();
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
