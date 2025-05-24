#include <SFML/Graphics.hpp>
#include "radio button class.h"

using namespace sf;

RadioButton::RadioButton(const sf::Texture &texture)
:
    Button(texture),
    ButtonImage3(texture)
{}

void RadioButton::Create(Texture btnTexture, IntRect rect1, IntRect rect2, IntRect rect3, Vector2u btnSize, Vector2f btnPosition, bool btnChoosed, RadioButton * previousRBtn, RadioButton * nextRBtn)
{
    ButtonTexture = btnTexture;
    ButtonImage.setTexture(ButtonTexture);
    ButtonImage2.setTexture(ButtonTexture);
    ButtonImage3.setTexture(ButtonTexture);
    ButtonImage.setTextureRect(rect1);
    ButtonImage2.setTextureRect(rect2);
    ButtonImage3.setTextureRect(rect3);
    InitialButtonSize = ButtonSize = btnSize;
    InitialButtonPosition = ButtonPosition = btnPosition;
    ButtonImage.setPosition(InitialButtonPosition);
    ButtonImage2.setPosition(InitialButtonPosition);
    ButtonImage3.setPosition(InitialButtonPosition);
    ButtonEnabled = true;
    ButtonChoosed = btnChoosed;
    PreviousRadioBtn = previousRBtn;
    NextRadioBtn = nextRBtn;
}

void RadioButton::Draw(RenderWindow & window)
{
    if (IsChoosed() && IsEnabled())
        window.draw(ButtonImage3);
    else if (MouseEntered(window) && IsEnabled())
        window.draw(ButtonImage2);
    else
        window.draw(ButtonImage);
}

bool RadioButton::IsChoosed(void)
{
    return ButtonChoosed;
}

void RadioButton::SetChoosed(bool status)
{
    ButtonChoosed = status;
}

bool RadioButton::IsPressed(RenderWindow & window, bool click_status)
{
    bool status = false;

    if (MouseEntered(window) && click_status && IsEnabled() && !IsChoosed())
        status = true;

    return status;
}

void RadioButton::ChangeRadioGroupChoosed()
{
    RadioButton * temp;

    this->SetChoosed(true);

    temp = this;
    while ((temp = temp->PreviousRadioBtn) != NULL)
    {
        temp->SetChoosed(false);
    }

    temp = this;
    while ((temp = temp->NextRadioBtn) != NULL)
    {
        temp->SetChoosed(false);
    }
}
