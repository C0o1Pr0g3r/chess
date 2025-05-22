#ifndef INSCRIPTION_CLASS_H_INCLUDED
#define INSCRIPTION_CLASS_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

class Label
{
private:
    Texture InscriptionTexture;
    Sprite InscriptionImage;
    Vector2f InscriptionPosition;
public:
    Label(const sf::Texture &texture);
    void Create(Texture iTexture, IntRect rect, Vector2f iPosition);
    void Draw(RenderWindow & window);
};

#endif // INSCRIPTION_CLASS_H_INCLUDED
