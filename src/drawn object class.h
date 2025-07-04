#ifndef CHESS_PIECES_CLASS_H_INCLUDED
#define CHESS_PIECES_CLASS_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace sf;

class DrawnObject
{
private:
    Texture DrawnObjectTexture;
    Sprite DrawnObjectImage;
public:
    DrawnObject(const sf::Texture &texture);
    void Create(Texture doTexture, IntRect rect);
    void Create(Texture doTexture, IntRect rect, Vector2f position);
    void SetPosition(Vector2f position);
    void SetPosition(int x, int y);
    void Draw(RenderWindow & window);
};

#endif // CHESS_PIECES_CLASS_H_INCLUDED
