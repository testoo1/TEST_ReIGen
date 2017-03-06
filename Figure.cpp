#include "Figure.hpp"

// Exist some problem with rounding of <Vector2i size> variable
// For example:
// if init <size.x> value = 200, is losed 2 pixel when program
// step into next recurtion level (200/3 -> 198)
void Figure::draw(sf::RenderTarget &window)
{
    if(_needRedraw){
        window.clear(sf::Color(0,0,0,0));
        draw(window, _depth, _startPoint, _size, _outline._thickness);
        _needRedraw = false;
    }
}

void Figure::draw(sf::RenderTarget &window, int depth,
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