#include <iostream>
#include <raylib.h>

using namespace std;


int player_score = 0;
int CPU_score =0;

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};


class Ball{
public:
float x, y;
int radius;
int speed_x, speed_y;   

void Draw()
{
    DrawCircle( x, y, radius, Yellow);
}
void Update()
{
    x += speed_x;
    y += speed_y;
    if (x + radius >= GetScreenWidth())
    {
        speed_x *= -1;
        player_score++;
        Reset();   
    }
    if(x - radius <= 0)
    {
        speed_x *= -1;
        CPU_score++;
        Reset();
    }
    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speed_y *= -1;
    }
};
void Reset()
{
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y *= speed_choices[GetRandomValue(0,1)];

};
};

class Paddle{
public:
float x, y;
float width, height;
int speed;

void Draw()
{
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
}
void Update()
{
    if (IsKeyDown(KEY_W) && y >= 0)
    y -= speed;
    if (IsKeyDown(KEY_S) && y + height <= GetScreenHeight())
    y += speed;
    if (y <= 0)
    y = 0;
    if (y + height >= GetScreenHeight())
    y = GetScreenHeight() - height;
}
};

class CPU_Paddle: public Paddle{
public :

void Update(int ball_y)
{
    if (ball_y < y + height/2 && y >= 0)
    {
        y -= speed;
    };
    if (ball_y > y + height/2 && y + height <= GetScreenHeight())
    {
        y += speed;
    };
    if (y <= 0)
    y = 0;
    if (y + height >= GetScreenHeight())
    y = GetScreenHeight() - height;
};
} ;





int main () {
const int screen_width = 1200;
const int screen_height = 800;
InitWindow(screen_width, screen_height, "PONG");
SetTargetFPS(60);

bool gameHasStarted = 0;

Ball DemoBall;
DemoBall.radius = 20;
DemoBall.x = screen_width/2;
DemoBall.y = screen_height/2;
DemoBall.speed_x = 7;
DemoBall.speed_y = 7;

CPU_Paddle DemoPaddle_1;
DemoPaddle_1.width = 25;
DemoPaddle_1.height = 120;
DemoPaddle_1.x = 10;
DemoPaddle_1.y = screen_height/2 - DemoPaddle_1.height/2;
DemoPaddle_1.speed = 6;

CPU_Paddle DemoPaddle_2;
DemoPaddle_2.width = 25;
DemoPaddle_2.height = 120;
DemoPaddle_2.x = screen_width - DemoPaddle_2.width -10;
DemoPaddle_2.y = screen_height/2 - DemoPaddle_2.height/2;
DemoPaddle_2.speed = 6;

while(gameHasStarted == 0 && WindowShouldClose() == false)
{

DemoBall.Update();
DemoPaddle_1.Update(DemoBall.y);
DemoPaddle_2.Update(DemoBall.y);

if(IsKeyDown(KEY_SPACE))
{
    gameHasStarted = 1;
}
if(CheckCollisionCircleRec(Vector2{DemoBall.x, DemoBall.y}, DemoBall.radius, Rectangle{DemoPaddle_1.x, DemoPaddle_1.y, DemoPaddle_1.width, DemoPaddle_1.height}))
{
DemoBall.speed_x *= -1;
}
if(CheckCollisionCircleRec(Vector2{DemoBall.x, DemoBall.y}, DemoBall.radius, Rectangle{DemoPaddle_2.x, DemoPaddle_2.y, DemoPaddle_2.width, DemoPaddle_2.height}))
{
DemoBall.speed_x *= -1;
}


BeginDrawing();
ClearBackground(Dark_Green);
DrawRectangle(0, 0, screen_width/2, screen_height, Green);
DrawCircle(screen_width/2, screen_height/2, 150, Light_Green);
DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
DemoBall.Draw();
DemoPaddle_1.Draw();
DemoPaddle_2.Draw();
DrawText(TextFormat("%i", CPU_score), screen_width*3/4 - 20, 20, 80, WHITE);
DrawText(TextFormat("%i", player_score), screen_width/4 - 20, 20, 80, WHITE);
DrawText("Press space to start", GetScreenWidth()/2 - MeasureText("Press space to start", 36)/2, GetScreenHeight() - 100, 36, WHITE);
DrawText("[W]UP   [S]DOWN", GetScreenWidth()/2 - MeasureText("[W]UP   [S]DOWN", 28)/2, GetScreenHeight() - 60, 28, WHITE);
EndDrawing();
}

player_score = 0;
CPU_score =0;

Ball GameBall;
GameBall.radius = 20;
GameBall.x = screen_width/2;
GameBall.y = screen_height/2;
GameBall.speed_x = 7;
GameBall.speed_y = 7;

Paddle PlayerPaddle;
PlayerPaddle.width = 25;
PlayerPaddle.height = 120;
PlayerPaddle.x = 10;
PlayerPaddle.y = screen_height/2 - PlayerPaddle.height/2;
PlayerPaddle.speed = 6;

CPU_Paddle CPU;
CPU.width = 25;
CPU.height = 120;
CPU.x = screen_width - CPU.width -10;
CPU.y = screen_height/2 - PlayerPaddle.height/2;
CPU.speed = 6;

while(WindowShouldClose() == false)
{

PlayerPaddle.Update();
GameBall.Update();
CPU.Update(GameBall.y);

if(CheckCollisionCircleRec(Vector2{GameBall.x, GameBall.y}, GameBall.radius, Rectangle{PlayerPaddle.x, PlayerPaddle.y, PlayerPaddle.width, PlayerPaddle.height}))
{
GameBall.speed_x *= -1;
}
if(CheckCollisionCircleRec(Vector2{GameBall.x, GameBall.y}, GameBall.radius, Rectangle{CPU.x, CPU.y, CPU.width, CPU.height}))
{
GameBall.speed_x *= -1;
}

BeginDrawing();
ClearBackground(Dark_Green);
DrawRectangle(0, 0, screen_width/2, screen_height, Green);
DrawCircle(screen_width/2, screen_height/2, 150, Light_Green);
DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
GameBall.Draw();
PlayerPaddle.Draw();
CPU.Draw();
DrawText(TextFormat("%i", CPU_score), screen_width*3/4 - 20, 20, 80, WHITE);
DrawText(TextFormat("%i", player_score), screen_width/4 - 20, 20, 80, WHITE);
EndDrawing();
}

CloseWindow();
}





//coded by Bingo