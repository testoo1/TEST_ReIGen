#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "imgui.h"
#include "imgui-sfml.h"

#include "Background.hpp"
#include "Figure.hpp"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


class Application
{
private:
    sf::RenderWindow    _window;
    // [0] -> Background, [1] -> Figure
    std::array<sf::RenderTexture,2> _renderTexture;

    Background          _bg;
    Figure              _figure;

    int                 _uiWidth;
    sf::Vector2i        _canvasCenter;
public:
    Application(){
        // Window
        _window.create(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                        sf::Style::Close);
        _window.setVerticalSyncEnabled(true);
        
        _uiWidth = 200;
        _canvasCenter = sf::Vector2i{(_window.getSize().x - _uiWidth)/2,
                       _window.getSize().y/2};

        for(auto &texture: _renderTexture)
            texture.create(_window.getSize().x, _window.getSize().y);

        // UI
        ImGui::SFML::Init(_window);

        // Figure
        _figure.center(_canvasCenter);
        _figure.depth(5);
        _figure.calcSize();
        _figure.calcStartPoint();
      
    }

    void run();
    void processEvent(sf::Clock deltaClock);
    void render();
    void UI();
};

#endif
