#include "Curve_Koch.hpp"
#include "math.h"

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

    m_texture.create(m_initSize.x*2, (m_initSize.y/4)*2);

    m_sprite.setTexture(m_texture.getTexture());
    m_sprite.setOrigin(0, m_texture.getSize().y);
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

        draw(m_texture, m_depth, sf::Vector2f(), m_size, 0);

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
    sf::RectangleShape m_line;

    m_line.setFillColor(m_color);
    m_line.setOrigin(0,m_width/2);
    m_line.rotate(angle);

    if (depth == 0){
        m_line.setSize(sf::Vector2f(m_size.x, m_width));
        m_line.setPosition(m_startPoint);
        target.draw(m_line);
        return;
    }

    const static double PI = 3.14159265359;
    sf::Vector2f line;
    sf::Vector2f point(position);


    for (int i=1; i<=4; ++i)
    {
        if(i == 1 || i == 4)
            line.x = size.x/4.f * (1 + (1 - cos(m_angle*PI/180)));
        else
            line.x = size.x/4.f;

        line.y = m_width;

        m_line.setSize(line);
        m_line.setPosition(point);

        switch(i){
            case(1):
                m_line.rotate(0);
                break;
            case(2):
                m_line.rotate(m_angle);
                break;
            case(3):
                m_line.rotate(-2*m_angle);
                break;
            case(4):
                m_line.rotate(m_angle);
                break;
        }

        if (depth == 1)
            target.draw(m_line);
        else{
            draw(target, depth-1, point, line, m_line.getRotation());
        }

        point.x += m_line.getSize().x * cos(m_line.getRotation()*PI/180);
        point.y += m_line.getSize().x * sin(m_line.getRotation()*PI/180);
    }
}
