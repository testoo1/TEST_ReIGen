#ifndef CURVE_KOCH_HPP
#define CURVE_KOCH_HPP

#include "Figure.hpp"


class Curve_Koch: public Figure
{
private:
	float m_angle = 45;
	int   m_width = 2;

public:
	virtual void draw(sf::RenderTarget &target) override;
    virtual void calcStartPoint() override;

    void draw(sf::RenderTarget &target, int depth,
              sf::Vector2f position, sf::Vector2f size, float angle);

    void  angle(float angle) {m_angle = angle;}
    float angle() const {return m_angle;}
};

#endif
