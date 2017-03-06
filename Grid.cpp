#include "Grid.hpp"

void Grid::draw(sf::RenderTarget &window)
{
    _line.setFillColor(_color);

    for (int dir=0; dir<2; ++dir){
        unsigned int limit;
        switch(dir){
            case 0:
                limit = window.getSize().y;
                _line.setSize(sf::Vector2f(limit, _thickness));
                break;
            case 1:
                limit = window.getSize().x;
                _line.setSize(sf::Vector2f(_thickness, limit));
                break;
        }
        for (int i=0; i<limit; i+= _step){
            switch(dir){
                case 0: _line.setPosition(0,i); break;
                case 1: _line.setPosition(i,0); break;
                }
            window.draw(_line);
        }
    }
}