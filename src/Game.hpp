#pragma once

struct Ball
{
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw();
};

struct Paddle
{
    float x, y;
    float speed;
    float width, height;

    Rectangle GetRect();

    void Draw();
};

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void Update(double deltaTime);
    void Render();

private:
    float mDefaultBallSpeed;
    float mDefaultBallRadius;
    float mDefaultPaddleSpeed;
    float mDefaultPaddleWidth;
    float mDefaultPaddleHeight;

    Ball mBall;
    Paddle mLeftPaddle;
    Paddle mRightPaddle;
    const char* mWinnerText = nullptr;
    bool mStarting;
};
