#include "Curve_Koch.hpp"
#include "math.h"
#include <iostream>

Curve_Koch::Curve_Koch(){
    m_steps[Base::LINE] =
        {std::make_pair(sf::Vector2f(-0.5,          0), 0)};
    m_steps[Base::TRIANGLE] =
        {std::make_pair(sf::Vector2f(   0,       -0.5), 60),
         std::make_pair(sf::Vector2f( 0.5, 0.5/0.5773), 120),
         std::make_pair(sf::Vector2f(  -1,          0), 120)};
    m_steps[Base::SQUARE] =
        {std::make_pair(sf::Vector2f( -0.5,      -0.5),  0),
         std::make_pair(sf::Vector2f(    1,         0), 90),
         std::make_pair(sf::Vector2f(    0,         1), 90),
         std::make_pair(sf::Vector2f(   -1,         0), 90)};


    m_texture.create(m_initSize.x * MAX_SCALE     + m_offset,
                     m_initSize.y * MAX_SCALE / 3 + m_offset * 2);

    m_sprite.setTexture(m_texture.getTexture());
    m_sprite.setOrigin(m_offset, m_texture.getSize().y - m_offset);
}

void Curve_Koch::calcStartPoint()
{
    // pass
}

void Curve_Koch::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color::Transparent);
        m_texture.clear(sf::Color::Transparent);

        m_line.setOrigin(0, m_width/2);
        m_line.setFillColor(m_color);

        if(m_width > 1){
            m_circle.setRadius(m_width/2);
            m_circle.setOrigin(m_width/2, m_width/2);
            m_circle.setFillColor(m_color);
            m_circle.setPosition(sf::Vector2f(m_offset, m_offset));
            m_texture.draw(m_circle);
        }

        draw(m_texture, m_depth, sf::Vector2f(m_offset,m_offset), m_size, 0);

        m_sprite.setPosition(m_center);
        m_sprite.setRotation(0);

        for(auto step: m_steps[m_base]){
            m_sprite.move(sf::Vector2f(step.first.x * m_size.x,
                                       step.first.y * m_size.y));
            m_sprite.rotate(step.second);
            target.draw(m_sprite);
        }

        m_needRedraw = false;
    }
}

void Curve_Koch::draw(sf::RenderTarget &target, int depth,
                  sf::Vector2f position, sf::Vector2f size, float angle)
{
    static double PI = 3.14159265359;
    static auto dCos = [](float angle){return (cos(angle*PI/180));};
    static auto dSin = [](float angle){return (sin(angle*PI/180));};

    if(depth == 0){
        m_line.setPosition(sf::Vector2f(position.x, position.y));
        m_line.setSize(sf::Vector2f(size.x, m_width));
        m_line.setRotation(angle);
        
        target.draw(m_line);

        if(m_width > 1){
            m_circle.setPosition(sf::Vector2f(position.x + size.x * dCos(angle),
                                              position.y + size.x * dSin(angle)));
            target.draw(m_circle);
        }
    }else{
        size /= 3.f;
        auto delta  = size.x*(dCos(60) - dCos(m_angle));
        auto deltaX = static_cast<float>(delta * dCos(angle));
        auto deltaY = static_cast<float>(delta * dSin(angle));

        auto p1 = position;
        auto p2 = p1 + sf::Vector2f(size.x * dCos(angle) + deltaX,
                                    size.x * dSin(angle) + deltaY);
        auto p3 = p2 + sf::Vector2f(size.x * dCos(angle + m_angle),
                                    size.x * dSin(angle + m_angle));
        auto p4 = p3 + sf::Vector2f(size.x * dCos(angle - m_angle),
                                    size.x * dSin(angle - m_angle));

        draw(target, depth-1, p2, size, angle + m_angle);
        draw(target, depth-1, p3, size, angle - m_angle);

        size.x +=  delta;
        draw(target, depth-1, p1, size, angle);
        draw(target, depth-1, p4, size, angle);


    }
}
