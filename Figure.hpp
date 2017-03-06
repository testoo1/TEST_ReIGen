#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <SFML/Graphics.hpp>

class Outline
{
public:
    sf::Color _color;
    int _thickness;

    Outline(const int thickness=1, const sf::Color color=sf::Color::Black):
        _color(color), _thickness(thickness) {}
};


class Figure{
public:
    sf::Vector2i _center    ={0,0};
    sf::Vector2i _size      =sf::Vector2i(450,450);
    sf::Vector2i _initSize  =sf::Vector2i(450,450);
    float _scale            =1;

    int _depth              =0;

    sf::Color _color        =sf::Color::White;
    Outline _outline        =Outline();

    sf::Vector2i _startPoint;

    bool _needRedraw=true;

    Figure(){}

    Figure(const sf::Vector2i   &center,
           const sf::Vector2i   &initSize,

           const int            depth,

           const sf::Color      &color,
           const Outline        &outline):
                _center(center), _initSize(initSize),
                _color(color), _outline(outline),
                _depth(depth)
    {
        calcSize();
        calcStartPoint();
    }

    void center(sf::Vector2i center){_center = center;}
    void depth (int depth){_depth = depth;}

    void draw(sf::RenderTarget &window);
    void draw(sf::RenderTarget &window, int depth,
              sf::Vector2i position, sf::Vector2i size,
              int thickness);

    void calcSize(){
        _size.x = _initSize.x*_scale;
        _size.y = _initSize.y*_scale;
    }

    void calcStartPoint(){
        _startPoint.x = _center.x - _size.x/2;
        _startPoint.y = _center.y - _size.y/2;
    }

    void needRedraw(){_needRedraw=true;}
};

#endif
