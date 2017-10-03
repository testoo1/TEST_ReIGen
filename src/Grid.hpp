#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>

class Grid
{
private:
    sf::RectangleShape m_line;
    sf::Color m_color;

    int m_step;
    int m_thickness;

public:
    Grid(sf::Color color=sf::Color::White, int width=1):
        m_color(color), m_thickness(width){}
// set
    void step(int step){m_step = step;}
    void thickness(int thickness){m_thickness = thickness;}
    void color(sf::Color color){m_color = color;}
// get
    int step() const {return m_step;}
    int width() const {return m_thickness;}
    sf::Color color() const {return m_color;}

    void draw(sf::RenderTarget &target);
};

#endif
