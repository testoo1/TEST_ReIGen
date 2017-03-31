#ifndef CURVE_HPP
#define CURVE_HPP

#include "Figure.hpp"


class Curve: public Figure
{
protected:
	int   m_initWidth = 1;
	int   m_width;

    sf::RectangleShape m_line;
    sf::CircleShape    m_circle;

public:
    void calcLineWidth();
	virtual void calculate() override;

// set
    void  width(float width);

// get
    float width() const {return m_initWidth;}
};

#endif