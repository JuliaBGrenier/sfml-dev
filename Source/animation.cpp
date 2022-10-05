#include "../Include/animation.h"

/*const sf::Time TimePerFrameAnimation = sf::seconds(1.f/12.f);

sf::Time timeSinceLastUpdate;

void animation(sf::Sprite &sprite, sf::Time dt)
{
    timeSinceLastUpdate += dt;

    sf::Vector2i textureBounds(sprite.getTexture()->getSize());
    sf::IntRect textureRect = sprite.getTextureRect();

    while (timeSinceLastUpdate > TimePerFrameAnimation)
    {
        textureRect.left += textureRect.width;

        if (textureRect.left + textureRect.width > textureBounds.x)
        {
            textureRect.left = 0;
        }

        timeSinceLastUpdate -= TimePerFrameAnimation;

    }
    sprite.setTextureRect(textureRect);
}
*/

void animation(sf::Sprite &sprite, sf::Time dt)
{
    sf::Vector2i textureBounds(sprite.getTexture()->getSize());
    sf::IntRect textureRect = sprite.getTextureRect();

    textureRect.left += textureRect.width;

    if (textureRect.left + textureRect.width > textureBounds.x)
    {
        textureRect.left = 0;
    }

    sprite.setTextureRect(textureRect);
}


