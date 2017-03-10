#include "Application.hpp"

void Application::processEvent(sf::Clock deltaClock)
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
                _window.close();
    }

    ImGui::SFML::Update(_window, deltaClock.restart());
}


void Application::render()
{
    _bg.draw(_renderTexture[0]);
    _figure.draw(_renderTexture[1]);

    _window.clear();

    for(auto &texture: _renderTexture)
        _window.draw(sf::Sprite(texture.getTexture()));

    _window.resetGLStates();

    UI();

    _window.display();
}


void Application::run()
{
    sf::Clock deltaClock;
    while (_window.isOpen())
    {
        processEvent(deltaClock);
        render();
    }

    ImGui::SFML::Shutdown();
}


void Application::UI(){


    int imGui_bgColor[4]{_bg.color().r, _bg.color().g, _bg.color().b, _bg.color().a};


    const char* type[]{"Curve","Gasket"};
    int typeIndex = 1;

    const char* gasketSubType[]{"Sierpinski sieves","Sierpinski carpet"};
    int gasketSubTypeIndex = 1;

// Config UI
    ImGui::SetNextWindowPos(ImVec2(600,0));
    ImGui::SetNextWindowSize(ImVec2(_uiWidth,600));

    ImGui::Begin("##Settings", false, ImGuiWindowFlags_NoTitleBar|
                                      ImGuiWindowFlags_NoResize|
                                      ImGuiWindowFlags_NoMove|
                                      ImGuiWindowFlags_NoCollapse|
                                      ImGuiWindowFlags_ShowBorders);

    ImGui::Text("");

    ImGui::Text("Type");
    ImGui::Combo("##Type", &typeIndex, type, IM_ARRAYSIZE(type));

    ImGui::Text("");

    ImGui::Text("Subtype");
    ImGui::Combo("##Subtype", &gasketSubTypeIndex, gasketSubType,
                 IM_ARRAYSIZE(gasketSubType));


    ImGui::Text("");
    ImGui::Separator();
    ImGui::Text("");


    ImGui::Text("Recursion depth");
    int depth{_figure.depth()};
    if(ImGui::SliderInt("##Recursion depth", &depth, 0, 5)){
        _figure.depth(depth);
        _figure.needRedraw();
    }

    ImGui::Text("");

    ImGui::Text("Image Scale");
    float scale{_figure.scale()};
    if(ImGui::SliderFloat("##Image Scale", &scale, 0.5, 2))
    {
        _figure.scale(scale);
        _figure.calcSize();
        _figure.calcStartPoint();

        _figure.needRedraw();
    }


    ImGui::Text("");
    ImGui::Separator();
    ImGui::Text("");


    ImGui::Text("Fill Color");
    int color[4]{255,255,255,255};
    if(ImGui::DragInt4("##Fill Color", color, 1, 0, 255)){
        _figure.color(sf::Color(color[0],color[1],color[2],color[3]));
        _figure.needRedraw();
    }

    ImGui::Text("Outline Color");
    int outlineColor[4]{0,0,0,255};
    if(ImGui::DragInt4("##Outline Color", outlineColor, 1, 0, 255)){
        _figure.outlineColor(sf::Color(outlineColor[0],outlineColor[1],
                                       outlineColor[2],outlineColor[3]));
        _figure.needRedraw();
    }

    ImGui::Text("");
    ImGui::Text("Outline Thickness");
    int outlineThickness{_figure.outlineThickness()};
    if(ImGui::SliderInt("##outline Thickness", &outlineThickness, 0, -16)){
        _figure.outlineThickness(outlineThickness);
        _figure.needRedraw();
    }

    ImGui::Text("");
    ImGui::Separator();
    ImGui::Text("");

    ImGui::Text("Background color");
    if(ImGui::DragInt4("##Background color", imGui_bgColor, 1, 0, 255)){
        _bg.color(sf::Color(imGui_bgColor[0],imGui_bgColor[1],
                           imGui_bgColor[2],imGui_bgColor[3]));

        _bg.needRedraw();
    }
    ImGui::End();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding.x = 32;

// Render UI
    ImGui::Render();
}
