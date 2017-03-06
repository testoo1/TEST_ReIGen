#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Grid.hpp"

class Background
{
private:
    Grid  _grid;
    sf::Color _color;

    int _step[3] {12,24,96};
    int _grad[3] {5,10,25};

    bool _needRedraw=true;

public:
    Background(sf::Color color=sf::Color(30,80,120)) : _color(color){}
// set
    void color(sf::Color color){_color = color;}
    void needRedraw(){_needRedraw=true;}
// get
    sf::Color color(){return _color;}

    void draw(sf::RenderTarget &window);
};

#endif
