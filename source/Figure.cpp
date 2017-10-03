#include "Figure.hpp"


void Figure::calcSize()
{
    m_size.x = m_initSize.x*m_scale;
    m_size.y = m_initSize.y*m_scale;
}