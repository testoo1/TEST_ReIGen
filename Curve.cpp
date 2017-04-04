#include "Curve.hpp"


void Curve::calcLineWidth()
{
	if(m_widthIsZoomable){
		m_width = static_cast<int>(m_initWidth * m_scale);
		if(m_width < 1)
			m_width = 1;
	}else{
		m_width = m_initWidth;
	}
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
	m_width = m_widthIsZoomable? width * m_scale : width;
}