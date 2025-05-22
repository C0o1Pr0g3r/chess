#ifndef RADIO_BUTTON_CLASS_H_INCLUDED
#define RADIO_BUTTON_CLASS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "button class.h"

using namespace sf;

class RadioButton : public Button
{
private:
    RadioButton * PreviousRadioBtn, * NextRadioBtn;
    Sprite ButtonImage3;
    bool ButtonChoosed;
public:
    RadioButton(const sf::Texture &texture);
    void Create(Texture btnTexture, IntRect rect1, IntRect rect2, IntRect rect3, Vector2u btnSize, Vector2f btnPosition, bool btnChoosed, RadioButton * previousRBtn, RadioButton * nextRBtn);
    void Draw(RenderWindow & window);
    bool IsChoosed(void);
    void SetChoosed(bool status);
    bool IsPressed(RenderWindow & window, bool click_status);
    void ChangeRadioGroupChoosed();
};

#endif // RADIO_BUTTON_CLASS_H_INCLUDED
