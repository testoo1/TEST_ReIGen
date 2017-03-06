#ifndef GREED_HPP
#define GREED_HPP

#include <SFML/Graphics.hpp>

class Grid
{
private:
    sf::RectangleShape _line;

    int _step;
    int _thickness;
    sf::Color _color;

public:
    Grid(sf::Color color=sf::Color::White, int width=1):
        _color(color), _thickness(width){}
// set
    void step(int step){_step = step;}
    void thickness(int thickness){_thickness = thickness;}
    void color(sf::Color color){_color = color;}
// get
    int step(){return _step;}
    int width(){return _thickness;}
    sf::Color color(){return _color;}

    void draw(sf::RenderTarget &window);
};

#endif
