#include "Background.hpp"

void Background::draw(sf::RenderTarget &window)
{
    if(_needRedraw){
        window.clear(_color);

        for (int i=0;i<3;++i){
            _grid.step(_step[i]);
            _grid.color(_color + sf::Color(_grad[i], _grad[i], _grad[i]));

            _grid.draw(window);
        }
    }
    _needRedraw = false;
}