#include "SierpinskiTriangle.hpp"
#include "math.h"

void SierpinskiTriangle::calcStartPoint(){
    m_startPoint.x = m_center.x - m_size.x/2;
    m_startPoint.y = m_center.y - m_size.y/2;
}

void SierpinskiTriangle::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color::Transparent);
        draw(target, m_depth, m_startPoint, m_size);
        m_needRedraw = false;
    }
}

void SierpinskiTriangle::draw(sf::RenderTarget &target, int depth,
                  sf::Vector2f position, sf::Vector2f size)
{
    sf::CircleShape element;
    element.setFillColor(m_color);
    element.setPointCount(3);

    if (depth == 0){
        element.setRadius(size.x/2.f);
        element.setPosition(m_startPoint);
        target.draw(element);
        return;
    }

    element.setRadius(size.x/4);
    sf::Vector2f point(sf::Vector2f(position.x + size.x/4,position.y));


    for (int i=1; i<=3; ++i)
    {
        element.setPosition(point);

        if (depth == 1)
            target.draw(element);
        else{
            draw(target, depth-1, point, size/2.f);
        }

        if (i==1){
            point.y =  position.y + size.y * 3/8;
            point.x -= size.x/4 * std::sqrt(3)/2;
            continue;
        }
        point.x += size.x/4 * std::sqrt(3);
    }
}
