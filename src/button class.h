#ifndef BUTTON_CLASS_H_INCLUDED
#define BUTTON_CLASS_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
protected:
    Texture ButtonTexture;
    Sprite ButtonImage, ButtonImage2;
    Vector2u InitialButtonSize, ButtonSize;
    Vector2f InitialButtonPosition, ButtonPosition;
    bool ButtonEnabled;
public:
    void Create(Texture btnTexture, IntRect rect1, IntRect rect2, Vector2u btnSize, Vector2f btnPosition);
    void Draw(RenderWindow & window);
    bool IsEnabled(void);
    void SetEnabled(bool status);
    bool MouseEntered(RenderWindow & window);
    bool IsPressed(RenderWindow & window, bool click_status);
    void ChangePropertiesByCoefficient(Vector2f coeff);
};

#endif // BUTTON_CLASS_H_INCLUDED
