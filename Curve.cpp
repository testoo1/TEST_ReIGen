#include "Curve.hpp"


void Curve::calcLineWidth()
{
	m_width = static_cast<int>(m_initWidth * m_scale);
	if(m_width < 1)
		m_width = 1;
}
	
void Curve::calculate()
{
	calcSize();
	calcStartPoint();
	
	calcLineWidth();
}


void  Curve::width(float width)
{
	m_initWidth = width;
    m_width     = width*m_scale;
}