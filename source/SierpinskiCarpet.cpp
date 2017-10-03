#include "SierpinskiCarpet.hpp"


void SierpinskiCarpet::calcStartPoint(){
    m_startPoint.x = m_center.x - m_size.x/2;
    m_startPoint.y = m_center.y - m_size.y/2;
}

void SierpinskiCarpet::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color::Transparent);
        draw(target, m_depth, m_startPoint, m_size);
        m_needRedraw = false;
    }
}

void SierpinskiCarpet::draw(sf::RenderTarget &target, int depth,
                  sf::Vector2f position, sf::Vector2f size)
{
    sf::RectangleShape element;
    element.setFillColor(m_color);

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
                draw(target, depth-1, point, size/3.f);
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
