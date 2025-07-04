#include <SFML/Graphics.hpp>
#include "label class.h"

using namespace sf;

Label::Label(const sf::Texture &texture)
:
    InscriptionImage(texture)
{}

void Label::Create(Texture iTexture, IntRect rect, Vector2f iPosition)
{
    InscriptionTexture = iTexture;
    InscriptionImage.setTexture(InscriptionTexture);
    InscriptionImage.setTextureRect(rect);
    InscriptionImage.setPosition(iPosition);
}

void Label::Draw(RenderWindow & window)
{
    window.draw(InscriptionImage);
}
