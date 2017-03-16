#import "Curve_Koch.hpp"
#import "math.h"


void Curve_Koch::calcStartPoint(){
    m_startPoint.x = m_center.x - m_size.x/2;
    m_startPoint.y = m_center.y;
}

void Curve_Koch::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color(0,0,0,0));
        draw(target, m_depth, m_startPoint, m_size, 0);
        m_needRedraw = false;
    }
}

void Curve_Koch::draw(sf::RenderTarget &target, int depth,
                  sf::Vector2f position, sf::Vector2f size, float angle)
{

    sf::RectangleShape element;
    element.setFillColor(m_color);
    element.setOrigin(0,m_width/2);
    element.rotate(angle);

    if (depth == 0){
        element.setSize(sf::Vector2f(m_size.x, m_width));
        element.setPosition(m_startPoint);
        target.draw(element);
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

        element.setSize(line);
        element.setPosition(point);

        switch(i){
            case(1):
                element.rotate(0);
                break;
            case(2):
                element.rotate(-m_angle);
                break;
            case(3):
                element.rotate(2*m_angle);
                break;
            case(4):
                element.rotate(-m_angle);
                break;
        }

        if (depth == 1)
            target.draw(element);
        else{
            draw(target, depth-1, point, line, element.getRotation());
        }

        point.x += element.getSize().x * cos(element.getRotation()*PI/180);
        point.y += element.getSize().x * sin(element.getRotation()*PI/180);
    }
}
