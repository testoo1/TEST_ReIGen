#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "imgui.h"
#include "imgui-sfml.h"

#include "Background.hpp"
#include "Figure_allType.hpp"

#include "Constants.hpp"

#include <memory>

class Application
{
private:
    sf::RenderWindow    m_window;
    // [0] -> Background, [1] -> Figure
    std::array<sf::RenderTexture,2> m_renderTexture;
    std::array<sf::Sprite,2>        m_sprite;

    Background              m_bg;
    std::unique_ptr<Figure> m_figure;

    int                     m_uiWidth;
    sf::Vector2f            m_canvasCenter;
    sf::Vector2f            m_point;

    bool                    m_mouseInActiveZone {false};
    bool                    m_figureIsGrabbed   {false};

public:
    Application(){
        // Window
        m_window.create(sf::VideoMode(800,600),"ReIGen", sf::Style::Titlebar|
                                                         sf::Style::Close);
        // m_window.setVerticalSyncEnabled(true);
        m_window.setFramerateLimit(60);

        m_uiWidth = 200;
        m_canvasCenter = sf::Vector2f{(m_window.getSize().x - m_uiWidth)/2,
                       m_window.getSize().y/2};

        m_point = m_canvasCenter;

        for(int i=0; i<2; ++i)
        {
            m_renderTexture[i].create(m_window.getSize().x,
                                      m_window.getSize().y);
            m_sprite[i].setTexture(m_renderTexture[i].getTexture());
            m_sprite[i].setOrigin(0, m_renderTexture[i].getSize().y);
            m_sprite[i].setScale(1,-1);
        }

        // UI
        ImGui::SFML::Init(m_window);

        // Figure
        m_figure = std::make_unique<SierpinskiTriangle>();
        m_figure->create(m_canvasCenter);
        m_figure->depth(5);

    }

    void run();
    void processEvent(sf::Clock deltaClock);
    void render();
    void UI();
};

#endif
