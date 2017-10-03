#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Grid.hpp"

class Background
{
private:
    Grid  m_grid;
    sf::Color m_color;

    int m_step[3] {12,24,96};
    int m_grad[3] {5,10,25};

    bool m_needRedraw=true;

public:
    Background(sf::Color color=sf::Color(30,80,120)) : m_color(color){}
// set
    void color(sf::Color color){m_color = color;}
    void needRedraw(){m_needRedraw=true;}
// get
    sf::Color color() const {return m_color;}

    void draw(sf::RenderTarget &window);
};

#endif
