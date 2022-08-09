#include <raylib.h>

#include "Game.hpp"

void Ball::Draw()
{
    DrawCircle((int)x, (int)y, radius, WHITE);
}

Rectangle Paddle::GetRect()
{
    return Rectangle{x - width / 2, y - height / 2, width, height};
}

void Paddle::Draw()
{
    DrawRectangleRec(GetRect(), WHITE);
}

Game::Game()
{
    mDefaultBallSpeed = GetScreenWidth() / 2.666667f;
    mDefaultBallRadius = GetScreenWidth() / 160.0f;
    mDefaultPaddleSpeed = GetScreenHeight() / 1.2f;
    mDefaultPaddleWidth = GetScreenWidth() / 80.0f;
    mDefaultPaddleHeight = GetScreenHeight() / 6.0f;

    mBall.x = GetScreenWidth() / 2.0f;
    mBall.y = GetScreenHeight() / 2.0f;
    mBall.speedX = mDefaultBallSpeed;
    mBall.speedY = mDefaultBallSpeed;
    mBall.radius = mDefaultBallRadius;

    mLeftPaddle.x = 50.0f;
    mLeftPaddle.y = GetScreenHeight() / 2;
    mLeftPaddle.width = mDefaultPaddleWidth;
    mLeftPaddle.height = mDefaultPaddleHeight;
    mLeftPaddle.speed = mDefaultPaddleSpeed;

    mRightPaddle.x = GetScreenWidth() - 50;
    mRightPaddle.y = GetScreenHeight() / 2;
    mRightPaddle.width = mDefaultPaddleWidth;
    mRightPaddle.height = mDefaultPaddleHeight;
    mRightPaddle.speed = mDefaultPaddleSpeed;

    mStarting = true;
}

Game::~Game()
{

}

void Game::Init()
{

}

void Game::Update(double deltaTime)
{
    if (mStarting)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            mStarting = false;
        }
    } else
    {
        mBall.x += mBall.speedX * deltaTime;
        mBall.y += mBall.speedY * deltaTime;

        if (mBall.y < 0 + mBall.radius)
        {
            mBall.y = 0 + mBall.radius;
            mBall.speedY *= -1;
        } else if (mBall.y > GetScreenHeight() - mBall.radius)
        {
            mBall.y = GetScreenHeight() - mBall.radius;
            mBall.speedY *= -1;
        }

        /*if (mBall.x < 0 + mBall.radius)
        {
            mBall.x = 0 + mBall.radius;
            mBall.speedX *= -1;
        } else if (mBall.x > GetScreenWidth() - mBall.radius)
        {
            mBall.x = GetScreenWidth() - mBall.radius;
            mBall.speedX *= -1;
        }*/

        if (IsKeyDown(KEY_W))
        {
            mLeftPaddle.y -= mLeftPaddle.speed * deltaTime;

            if (mLeftPaddle.y < 0 + mLeftPaddle.height / 2)
                mLeftPaddle.y = 0 + mLeftPaddle.height / 2;
        }
        if (IsKeyDown(KEY_S))
        {
            mLeftPaddle.y += mLeftPaddle.speed * deltaTime;

            if (mLeftPaddle.y > GetScreenHeight() - mLeftPaddle.height / 2)
                mLeftPaddle.y = GetScreenHeight() - mLeftPaddle.height / 2;
        }

        if (IsKeyDown(KEY_UP))
        {
            mRightPaddle.y -= mRightPaddle.speed * deltaTime;

            if (mRightPaddle.y < 0 + mRightPaddle.height / 2)
                mRightPaddle.y = 0 + mRightPaddle.height / 2;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            mRightPaddle.y += mRightPaddle.speed * deltaTime;

            if (mRightPaddle.y > GetScreenHeight() - mRightPaddle.height / 2)
                mRightPaddle.y = GetScreenHeight() - mRightPaddle.height / 2;
        }

        if (CheckCollisionCircleRec(Vector2{mBall.x, mBall.y}, mBall.radius, mLeftPaddle.GetRect()))
        {
            if (mBall.speedX < 0)
            {
                mBall.speedX *= -1.1f;
                mBall.speedY = (mBall.y - mLeftPaddle.y) / (mLeftPaddle.height / 2) * mBall.speedX;
            }
        }

        if (CheckCollisionCircleRec(Vector2{mBall.x, mBall.y}, mBall.radius, mRightPaddle.GetRect()))
        {
            if (mBall.speedX > 0)
            {
                mBall.speedX *= -1.1f;
                mBall.speedY = (mBall.y - mRightPaddle.y) / (mRightPaddle.height / 2) * -mBall.speedX;
            }
        }

        if (mBall.x < 0)
        {
            mWinnerText = "Right Player Wins!";
        } else if (mBall.x > GetScreenWidth())
        {
            mWinnerText = "Left Player Wins!";
        }

        if (mWinnerText && IsKeyPressed(KEY_SPACE))
        {
            mBall.x = GetScreenWidth() / 2.0f;
            mBall.y = GetScreenHeight() / 2.0f;
            mBall.speedX = mDefaultBallSpeed;
            if (GetRandomValue(0, 1) == 0)
            {
                mBall.speedX *= -1;
            }
            mBall.speedY = mDefaultBallSpeed;
            if (GetRandomValue(0, 1) == 0)
            {
                mBall.speedY *= -1;
            }
            mLeftPaddle.y = GetScreenHeight() / 2;
            mRightPaddle.y = GetScreenHeight() / 2;
            mWinnerText = nullptr;

            mStarting = true;
        }
    }
}

void Game::Render()
{
    BeginDrawing();
    {
        ClearBackground(BLACK);

        mBall.Draw();
        mLeftPaddle.Draw();
        mRightPaddle.Draw();

        DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), LIGHTGRAY);

        if (mStarting)
        {
            const char* text = "Press Space to Start";
            DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 30) / 2,
                     GetScreenHeight() / 2 - 15, 30, RED);
        }

        if (mWinnerText)
        {
            DrawText(mWinnerText, GetScreenWidth() / 2 - MeasureText(mWinnerText, 60) / 2, GetScreenHeight() / 2 - 30,
                     60, YELLOW);
            const char* text = "Press Space to Play Again";
            DrawText(text, GetScreenWidth() / 2 - MeasureText(text, 30) / 2, GetScreenHeight() / 2 + 40, 30, RED);
        }

        //DrawFPS(10, 10);
    }
    EndDrawing();
}
