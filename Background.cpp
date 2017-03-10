#include "Background.hpp"

void Background::draw(sf::RenderTarget &target)
{
    if(m_needRedraw){
        target.clear(m_color);

        for (int i=0;i<3;++i){
            m_grid.step(m_step[i]);
            m_grid.color(m_color + sf::Color(m_grad[i], m_grad[i], m_grad[i],
            						         m_color.a));

            m_grid.draw(target);
        }
    }
    m_needRedraw = false;
}