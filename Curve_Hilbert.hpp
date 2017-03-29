#ifndef CURVE_HILBERT_HPP
#define CURVE_HILBERT_HPP

#include "Figure.hpp"


class Curve_Hilbert: public Figure
{
private:
	int   m_width = 1;

    sf::RectangleShape m_line;
    sf::CircleShape    m_circle;

public:
	virtual void draw(sf::RenderTarget &target) override;
    virtual void calcStartPoint() override;

    void draw(sf::RenderTarget &target, int depth,
              float dx, float dy);

    void drawLine(sf::RenderTarget &target, float dx, float dy);

// set
    void  width(float width) {m_width = width;}

// get
    float width() const {return m_width;}
};

#endif
