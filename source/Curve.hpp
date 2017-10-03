#ifndef CURVE_HPP
#define CURVE_HPP

#include "Figure.hpp"


class Curve: public Figure
{
protected:
	int   m_initWidth {1};
	int   m_width;

    sf::RectangleShape m_line;
    sf::CircleShape    m_circle;

    bool m_widthIsZoomable {false};

public:
    void calcLineWidth();
	virtual void calculate() override;

// set
    void  width(float width);
    void  widthIsZoomable(bool value) {m_widthIsZoomable = value;}

// get
    float width() const {return m_initWidth;}
    bool  widthIsZoomable() const {return m_widthIsZoomable;}
};

#endif