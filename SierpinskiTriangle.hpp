#ifndef SIERPINSKI_TRIANGLE_HPP
#define SIERPINSKI_TRIANGLE_HPP

#include "Figure.hpp"


class SierpinskiTriangle: public Figure
{
public:
	virtual void draw(sf::RenderTarget &target) override;
    virtual void calcStartPoint() override;

    void draw(sf::RenderTarget &target, int depth,
              sf::Vector2f position, sf::Vector2f size);
};

#endif
