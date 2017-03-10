#include "Grid.hpp"

void Grid::draw(sf::RenderTarget &target)
{
    m_line.setFillColor(m_color);

    for (int dir=0; dir<2; ++dir){
        unsigned int limit;
        switch(dir){
            case 0:
                limit = target.getSize().y;
                m_line.setSize(sf::Vector2f(target.getSize().x, m_thickness));
                break;
            case 1:
                limit = target.getSize().x;
                m_line.setSize(sf::Vector2f(m_thickness, target.getSize().y));
                break;
        }
        for (int i=0; i<limit; i+= m_step){
            switch(dir){
                case 0: m_line.setPosition(0,i); break;
                case 1: m_line.setPosition(i,0); break;
                }
            target.draw(m_line);
        }
    }
}