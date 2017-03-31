#ifndef CURVE_KOCH_HPP
#define CURVE_KOCH_HPP

#include "Curve.hpp"


class Curve_Koch: public Curve
{
public:
        enum class Base{
    	LINE,
    	TRIANGLE,
    	SQUARE
    };

private:
	float m_angle = 45;

	sf::RenderTexture m_texture;
	sf::Sprite		  m_sprite;

	Base m_base = Base::LINE;

    std::map<Base, std::vector<std::pair<sf::Vector2f, int>>> m_steps;

public:
	virtual void draw(sf::RenderTarget &target) override;
    virtual void calcStartPoint() override;

    void draw(sf::RenderTarget &target, int depth,
              sf::Vector2f position, sf::Vector2f size, float angle);


    Curve_Koch();

// set
    void  angle(float angle) {m_angle = angle;}
    void  base (Base   base) {m_base  =  base;}

// get
    float angle() const {return m_angle;}
};

#endif
