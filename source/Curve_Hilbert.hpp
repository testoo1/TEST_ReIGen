#ifndef CURVE_HILBERT_HPP
#define CURVE_HILBERT_HPP

#include "Curve.hpp"


class Curve_Hilbert: public Curve
{
public:
	virtual void draw(sf::RenderTarget &target) override;
    virtual void calcStartPoint() override;

    void draw(sf::RenderTarget &target, int depth,
              float dx, float dy);

    void drawLine(sf::RenderTarget &target, float dx, float dy);
};

#endif
