#include "Figure.hpp"


void Figure::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color(0,0,0,0));
        draw(target, m_depth, m_startPoint, m_size, m_outline.m_thickness);
        m_needRedraw = false;
    }
}

void Figure::draw(sf::RenderTarget &target, int depth,
                  sf::Vector2f position, sf::Vector2f size,
                  int thickness)
{
    sf::RectangleShape element;

    element.setFillColor(m_color);
    element.setOutlineThickness(thickness);
    element.setOutlineColor(m_outline.m_color);


    if (depth == 0){
        element.setSize(size);
        element.setPosition(m_startPoint);
        target.draw(element);
        return;
    }

    element.setSize(size/3.f);
    sf::Vector2f point(position);

    for (int i=1; i<=9; ++i)
    {
        if (i != 5){
            element.setPosition(point);

            if (depth == 1)
                target.draw(element);
            else{
                draw(target, depth-1, point, size/3.f, thickness/2);
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
