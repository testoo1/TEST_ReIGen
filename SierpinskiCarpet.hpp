#ifndef SIERPINSKI_CARPET_HPP
#define SIERPINSKI_CARPET_HPP

#import "Figure.hpp"


class SierpinskiCarpet: public Figure
{
public:
    virtual void draw(sf::RenderTarget &target, int depth,
              sf::Vector2f position, sf::Vector2f size) override;
    virtual void calcStartPoint() override;
};

#endif
