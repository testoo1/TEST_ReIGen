#include "Curve_Hilbert.hpp"


void Curve_Hilbert::calcStartPoint(){
    m_startPoint.x = m_center.x - m_size.x/2;
    m_startPoint.y = m_center.y - m_size.y/2;
}

void Curve_Hilbert::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color::Transparent);

        m_line.setFillColor(m_color);
        m_line.setPosition(m_startPoint);

        if(m_width > 1){
            m_circle.setPosition(m_startPoint);
            m_circle.setRadius(m_width/2);
            m_circle.setOrigin(m_width/2, m_width/2);
            m_circle.setFillColor(m_color);
            target.draw(m_circle);
        }

        int divider {1};
        for(int i=0;i<m_depth;++i)
            divider = divider*2 + 1;

        draw(target, m_depth, m_size.x/divider, NULL);

        m_needRedraw = false;
    }
}

void Curve_Hilbert::drawLine(sf::RenderTarget &target, float dx, float dy)
{
    if(dy == NULL)
    {
        m_line.setSize(sf::Vector2f(dx, m_width));
        m_line.setOrigin(0, m_width/2);
    }
    else
    {
        m_line.setSize(sf::Vector2f(m_width, dy));
        m_line.setOrigin(m_width/2, 0);
    }

    target.draw(m_line);

    m_line.move(sf::Vector2f(dx, dy));

    if(m_width > 1){
        m_circle.setRadius(m_width/2);
        m_circle.move(dx,dy);
        target.draw(m_circle);
    }
}

void Curve_Hilbert::draw(sf::RenderTarget &target, int depth,
                         float dx, float dy)
{
    m_line.setSize(sf::Vector2f(dx, dy));

    if(depth > 0)
        draw(target, depth - 1, dy, dx);

    drawLine(target, dx, dy);

    if(depth > 0)
        draw(target, depth - 1, dx, dy);

    drawLine(target, dy, dx);

    if(depth > 0)
        draw(target, depth - 1, dx, dy);

    drawLine(target, -dx, -dy);

    if(depth > 0)
        draw(target, depth - 1, -dy, -dx);
}
