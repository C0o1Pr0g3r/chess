#include <SFML/Graphics.hpp>
#include "label class.h"

using namespace sf;

void Label::Create(Texture iTexture, IntRect rect, Vector2f iPosition)
{
    InscriptionTexture = iTexture;
    InscriptionImage.setTexture(InscriptionTexture);
    InscriptionImage.setTextureRect(rect);
    InscriptionImage.setPosition(iPosition);
}

Sprite Label::Draw(RenderWindow & window)
{
    window.draw(InscriptionImage);
}
