#ifndef CSTATE_H
#define CSTATE_H

#include <SFML/Graphics.hpp>

class cState
{
public :
    virtual int run(sf::RenderWindow &Window) = 0;
};

#endif // CSTATE_H
