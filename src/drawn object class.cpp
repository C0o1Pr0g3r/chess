#include <SFML/Graphics.hpp>
#include "drawn object class.h"

using namespace sf;

void DrawnObject::Create(Texture doTexture, IntRect rect)
{
    DrawnObjectTexture = doTexture;
    DrawnObjectImage.setTexture(DrawnObjectTexture);
    DrawnObjectImage.setTextureRect(rect);
}

void DrawnObject::Create(Texture doTexture, IntRect rect, Vector2f position)
{
    DrawnObjectTexture = doTexture;
    DrawnObjectImage.setTexture(DrawnObjectTexture);
    DrawnObjectImage.setTextureRect(rect);
    DrawnObjectImage.setPosition(position);
}

void DrawnObject::SetPosition(Vector2f position)
{
    DrawnObjectImage.setPosition(position);
}

void DrawnObject::SetPosition(int x, int y)
{
    float x_f, y_f;

    x_f = (float) x;
    y_f = (float) y;

    DrawnObjectImage.setPosition({x_f, y_f});
}

void DrawnObject::Draw(RenderWindow & window)
{
    window.draw(DrawnObjectImage);
}
