#include "Figure.hpp"


void Figure::calcSize()
{
    m_size.x = m_initSize.x*m_scale;
    m_size.y = m_initSize.y*m_scale;
}

void Figure::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(sf::Color(0,0,0,0));
        draw(target, m_depth, m_startPoint, m_size);
        m_needRedraw = false;
    }
}