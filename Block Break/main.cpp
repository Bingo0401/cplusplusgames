#include <iostream>
#include <raylib.h>
#include <deque>
#include <cmath>

using namespace std;

const Color COLOR_BACKGROUND = {18, 18, 48, 255};
const Color COLOR_FRAME = {200, 200, 200, 255};
const Color COLOR_BALL = {255, 233, 0, 255};
const Color COLOR_PADDLE = {0, 180, 255, 255};
const Color BLOCK_COLORS[5] = {
    {100, 255, 100, 255},
    {255, 150, 50, 255},
    {255, 100, 180, 255},
    {150, 100, 255, 255},  
    {255, 220, 100, 255}   
};


const int CELL_SIZE = 50;
const int CELL_COUNT_X = 10;
const int CELL_COUNT_Y = 15;
const int FRAME_WIDTH_SIDES = CELL_SIZE/2;
const int FRAME_WIDTH_TOP = CELL_SIZE/2;
const int FRAME_WIDTH_BOTTOM = CELL_SIZE;

class Block{
public:
    deque <Vector2> positions;
    float width = CELL_SIZE;
    float height = CELL_SIZE/4;

    void FillPositions()
    { 
        for (int i = 0; i < positions.size(); i++)
        {
            positions.pop_back();
        }
        for(float i = 0; i < CELL_COUNT_X; i++)
        {
            for(float j = 0; j < 4; j++)
            {
                positions.push_back({i * CELL_SIZE + FRAME_WIDTH_SIDES, j * CELL_SIZE + FRAME_WIDTH_TOP});
            }
        }
    }

    Block()
    {
        FillPositions();
    }

    void Reset()
    {
        FillPositions();
    }

    void Draw()
    {
        for (int i = 0; i < positions.size(); i++)
        {
            Rectangle segment = Rectangle{positions[i].x, positions[i].y, width, height};
            DrawRectangleRounded(segment, 0.5, 6, BLOCK_COLORS[int(positions[i].x / CELL_SIZE) % 5]);
        };
    }
};


class Ball{
public:
    float x = GetScreenWidth()/2 + FRAME_WIDTH_SIDES;
    float y = GetScreenHeight() * 3/4 + FRAME_WIDTH_TOP;
    int speed_x = 7;
    int speed_y = -7;
    int radius = 10;
    
    void Reset()
    {
        x = GetScreenWidth()/2 + FRAME_WIDTH_SIDES;
        y = GetScreenHeight() * 1/4 + FRAME_WIDTH_TOP;
        speed_x = 7;
        speed_y = 7;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
    }

    void Draw()
    {
        DrawCircle(x, y, radius, COLOR_BALL);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;
        if (x + radius >= GetScreenWidth() - FRAME_WIDTH_SIDES || x - radius <= 0 + FRAME_WIDTH_SIDES)
        {   
            speed_x *= -1;
        }
        if(y - radius <= 0 + FRAME_WIDTH_TOP)
        {
        speed_y *= -1;
        }
    }

};


class Paddle{
public:
    float x = GetScreenWidth()/2 - CELL_SIZE;
    float y = GetScreenHeight() - CELL_SIZE * 2 - FRAME_WIDTH_TOP;
    float width = CELL_SIZE * 2;
    float height = CELL_SIZE/2;
    float speed = 7;
    void Draw()
    {
        Rectangle segment = Rectangle{x, y, width, height};
        DrawRectangleRounded(segment, 0.5, 6, COLOR_PADDLE);
    }
    
    void Reset(){
        x = GetScreenWidth()/2 - CELL_SIZE;
        y = GetScreenHeight() - CELL_SIZE * 2 - FRAME_WIDTH_TOP;
    }

    void Update()
    {
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            x -= speed;
        };
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            x += speed;
        };
        if (x <= 0 + FRAME_WIDTH_SIDES)
        {
            x = 0 + FRAME_WIDTH_SIDES;
        }
        if (x >= GetScreenWidth() - width - FRAME_WIDTH_SIDES)
        {
            x = GetScreenWidth() - width - FRAME_WIDTH_SIDES;
        }
    }

};

class Game{
public:
    Block block;
    Ball ball;
    Paddle paddle;
    const Rectangle Background = {FRAME_WIDTH_SIDES, FRAME_WIDTH_TOP, CELL_SIZE * CELL_COUNT_X, CELL_SIZE * CELL_COUNT_Y}; 
    bool running = true;
    int score = 0;

    void GameOver()
    {
        running = false;
    }

    void RestartGame()
    {
        ball.Reset();
        paddle.Reset();
        block.Reset();
        score = 0;
        running = true;
    }

    void CheckCollisionWithPaddle()
    {
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddle.x, paddle.y, paddle.width, paddle.height}))
        {   
            ball.y = paddle.y - ball.radius;
            ball.speed_y *= -1;
        }
    }

    void CheckCollisionWithBlock()
    {
        for (int i = 0; i < block.positions.size(); i++)
        {
            if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{block.positions[i].x, block.positions[i].y, block.width, block.height}))
            {   
                if (ball.y > block.positions[i].y)
                {
                    ball.y = block.positions[i].y + block.height + ball.radius;
                    ball.speed_y = abs(ball.speed_y);
                }
                if (ball.y < block.positions[i].y)
                {
                    ball.y = block.positions[i].y - ball.radius;
                    ball.speed_y = -abs(ball.speed_y);
                }
                //ball.speed_y *= -1;
                score++;
                block.positions.erase(block.positions.begin() + i);
            }
        }
    }

    void CheckCollisionWithBottom()
    {
        if (ball.y + ball.radius >= GetScreenHeight() - FRAME_WIDTH_BOTTOM)
        {
        GameOver();
        }
    }

    void Draw()
    {   
        DrawRectangleRec(Background, COLOR_BACKGROUND);
        block.Draw();
        ball.Draw();
        paddle.Draw();
        DrawText(TextFormat("Score: %d", score), FRAME_WIDTH_SIDES, GetScreenHeight() - CELL_SIZE, CELL_SIZE, WHITE);
        if (running == false)
        {
            DrawText("Press Any Key to Restart", GetScreenWidth()/2 - MeasureText("Press Any Key to Restart", 35)/2, GetScreenHeight()/2, 35, WHITE);
        }
    }

    void Update()
    {
        if (running == true)
        {
            ball.Update();
            paddle.Update();
            CheckCollisionWithPaddle();
            CheckCollisionWithBlock();
            CheckCollisionWithBottom();
        }else if(GetKeyPressed())
        {
            RestartGame();
        }
    }
};

int main () {
    const int SCREEN_WIDTH = CELL_SIZE * CELL_COUNT_X + FRAME_WIDTH_SIDES * 2;
    const int SCREEN_HEIGHT = CELL_SIZE * CELL_COUNT_Y + FRAME_WIDTH_BOTTOM + FRAME_WIDTH_TOP;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Block Break");
    SetTargetFPS(60);

    Game game;
    while(WindowShouldClose() == false){

        game.Update();

        BeginDrawing();
        ClearBackground(COLOR_FRAME);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
}



//coded by Bingo
