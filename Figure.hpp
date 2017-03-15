#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <SFML/Graphics.hpp>


class Figure{
protected:
    sf::Vector2f    m_center        ={0,0};
    sf::Vector2f    m_initSize      =sf::Vector2f(450,450);
    float           m_scale         =1;

    int             m_depth         =0;

    sf::Color       m_color         =sf::Color::White;

    sf::Vector2f    m_size;
    sf::Vector2f    m_startPoint;

    bool            m_needRedraw    =true;

public:
    create(sf::Vector2f center)
    {
        m_center = center;
        calculate();
    }

// set
    void center (sf::Vector2f center){m_center = center;}
    void scale  (float scale){m_scale = scale;}
    void depth  (int depth){m_depth = depth;}
    void color  (sf::Color color){m_color = color;}

// get
    sf::Vector2f center () const {return m_center;}
    float        scale  () const {return m_scale;}
    int          depth  () const {return m_depth;}
    sf::Color    color  () const {return m_color;}


    void draw(sf::RenderTarget &target);
    virtual void draw(sf::RenderTarget &target, int depth,
              sf::Vector2f position, sf::Vector2f size) = 0;

    void calcSize();
    virtual void calcStartPoint() = 0;

    void calculate(){calcSize();calcStartPoint();};

    void needRedraw(){m_needRedraw=true;}
};

#endif
