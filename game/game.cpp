#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

const int H = 12;
const int W = 40;

String map[H] = {
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
"W                                      W",
"W    W                                 W",
"W    WWWWW WWW                         W",
"W    W  W   WWW                        W",
"W    W  W   WWWW                       W",
"W    W       WW                        W",
"W WWWWWWW    W                         W",
"W           W         W                W",
"W                                      W",
"W                                      W",
"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
};



class Player
{
public:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float currentFrame;

    Player(Texture &image)
    {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(15, 120, 110, 200));
        sprite.setPosition(50, 50);
        sprite.scale(0.3, 0.3);
        rect = FloatRect(50, 50, 35, 49);

        dx = dy = 0;
        currentFrame = 0;
    }

    void update(float time)
    {
        rect.left += dx * time;
        CollisionX();
        rect.top += dy * time;

        CollisionY();

        currentFrame += 0.02 * time;
        if (currentFrame > 7) currentFrame -= 7;

        if (dx > 0) sprite.setTextureRect(IntRect(15 + (110 * int(currentFrame)), 120, 110, 200));
        if (dx < 0) sprite.setTextureRect(IntRect(15 + (110 * int(currentFrame) + 110), 120, -110, 200));

        sprite.setPosition(rect.left, rect.top);

        dx = 0;
        dy = 0;
    }

    void CollisionX()
    {
        for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++)
        {
            for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++)
            {
                if (map[i][j] == 'W')
                {
                    if (dx > 0) rect.left = j * 50 - rect.width;
                    if (dx < 0) rect.left = j * 50 + 50;
                }
            }
        }
    }

    void CollisionY()
    {
        for (int i = rect.top / 50; i < (rect.top + rect.height) / 50; i++)
        {
            for (int j = rect.left / 50; j < (rect.left + rect.width) / 50; j++)
            {
                if (map[i][j] == 'W')
                {
                    if (dy > 0) rect.top = i * 50 - rect.height;
                    if (dy < 0) rect.top = i * 50 + 50;
                }
            }
        }
    }

};

int main()
{
    std::cout << "Hello World!\n";
    RenderWindow window(VideoMode(900, 600), "game");

    CircleShape Circle(100.f);
    Circle.setFillColor(Color::Green);

    Texture t;
    t.loadFromFile("res/pers.png");

    float currentFrameGo = 0;
    bool rightGo = true;

    Player p(t);

    Clock clock;

    RectangleShape rectangle(Vector2f(50, 50));

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 1300;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            rightGo = false;
            p.dx -= 0.15;
            
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            rightGo = true;
            p.dx += 0.15;
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
           
            p.dy -= 0.15;

            
            if (rightGo) p.sprite.setTextureRect(IntRect(15 + (110 * int(p.currentFrame)), 120, 110, 200));
            else p.sprite.setTextureRect(IntRect(15 + (110 * int(p.currentFrame) + 110), 120, -110, 200));
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            
            p.dy += 0.15;
            

            if (rightGo) p.sprite.setTextureRect(IntRect(15 + (110 * int(p.currentFrame)), 120, 110, 200));
            else p.sprite.setTextureRect(IntRect(15 + (110 * int(p.currentFrame) + 110), 120, -110, 200));
        }

        p.update(time);

        window.clear(Color::White);

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                rectangle.setFillColor(Color::Black);
                if (map[i][j] == 'W') rectangle.setFillColor(Color::Black);
                if (map[i][j] == ' ') continue;
                rectangle.setPosition(j * 50, i * 50);
                window.draw(rectangle);
            }
        }
        window.draw(p.sprite);
        window.display();
    }
    return 0;
}
