#include <SFML/Graphics.hpp>
#include "button class.h"

using namespace sf;

Button::Button(const sf::Texture &texture)
:
    ButtonImage(texture),
    ButtonImage2(texture)
{}

void Button::Create(Texture btnTexture, IntRect rect1, IntRect rect2, Vector2u btnSize, Vector2f btnPosition)
{
    ButtonTexture = btnTexture;
    ButtonImage.setTexture(ButtonTexture);
    ButtonImage2.setTexture(ButtonTexture);
    ButtonImage.setTextureRect(rect1);
    ButtonImage2.setTextureRect(rect2);
    InitialButtonSize = ButtonSize = btnSize;
    InitialButtonPosition = ButtonPosition = btnPosition;
    ButtonImage.setPosition(InitialButtonPosition);
    ButtonImage2.setPosition(InitialButtonPosition);
    ButtonEnabled = true;
}

void Button::Draw(RenderWindow & window)
{
    if (MouseEntered(window) && IsEnabled())
        window.draw(ButtonImage2);
    else
        window.draw(ButtonImage);
}

bool Button::IsEnabled(void)
{
    return ButtonEnabled;
}

void Button::SetEnabled(bool status)
{
    ButtonEnabled = status;
}

bool Button::MouseEntered(RenderWindow & window)
{
    bool status = false;
    Vector2i mouse_pos = Mouse::getPosition(window);

    if (mouse_pos.x >= ButtonPosition.x && mouse_pos.x <= ButtonPosition.x + ButtonSize.x && mouse_pos.y >= ButtonPosition.y && mouse_pos.y <= ButtonPosition.y + ButtonSize.y)
        status = true;

    return status;
}

bool Button::IsPressed(RenderWindow & window, bool click_status)
{
    bool status = false;

    if (MouseEntered(window) && click_status && IsEnabled())
        status = true;

    return status;
}

void Button::ChangePropertiesByCoefficient(Vector2f coeff)
{
    Vector2f temp;
    temp = {(float) InitialButtonSize.x * coeff.x, (float) InitialButtonSize.y * coeff.y};
    ButtonSize = {static_cast<unsigned int>(temp.x - (int) temp.x < 0.5 ? (int) temp.x : (int) temp.x + 1), static_cast<unsigned int>(temp.y - (int) temp.y < 0.5 ? (int) temp.y : (int) temp.y + 1)};
    temp = {(float) InitialButtonPosition.x * coeff.x, (float) InitialButtonPosition.y * coeff.y};
    ButtonPosition = temp;
}
