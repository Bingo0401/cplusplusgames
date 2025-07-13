#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

Color green = {173, 204, 96, 255};
Color dark_green = {43, 51, 24, 255};

float cellSize = 30;
float cellCount = 25;

double lastUpdateTime = 0;

bool EventTriggered(double interval);
bool ElementInDeque(Vector2 element, deque<Vector2> deque);

class Food{
public:
    Vector2 position = {5, 6};
    Texture2D food_texture;


    Food(deque <Vector2> snake_body)
    {
        Image food_image = LoadImage("graphics/food.png");
        food_texture = LoadTextureFromImage(food_image);
        UnloadImage(food_image); 
        position = GenerateRandomPosition(snake_body);
    }

    ~Food()
    {
        UnloadTexture(food_texture);
    }

    void Draw()
    {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, WHITE);
        //DrawTexture(food_texture, position.x * cellSize, position.y * cellSize, WHITE);
    }
    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x,y};
    }
    Vector2 GenerateRandomPosition(deque<Vector2> snake_body)
    {
        Vector2 position = GenerateRandomCell();
        while(ElementInDeque(position, snake_body))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Snake{
    public:
    
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9},Vector2{4,9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            int x = body.at(i).x;
            int y = body.at(i).y;
            Rectangle segment = Rectangle{x * cellSize, y * cellSize, cellSize, cellSize};
            DrawRectangleRounded(segment, 0.5, 6, dark_green);
        }
    };

    void Update()
    {   
        body.push_front(Vector2Add(body.at(0), direction));
        if (addSegment == true)
        {
            addSegment = false;
        }else
        {
            body.pop_back();
        }
    }
    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9},Vector2{4,9}};
        direction = {1, 0};
        addSegment = false;
    }



};

class Game{
    public:
    Snake snake;
    Food food = Food(snake.body);
    bool running = true;
    Sound eatSound;
    Sound wallSound;
  Game()
    {
        InitAudioDevice();
        eatSound = LoadSound("sounds/eat.mp3");
        wallSound = LoadSound("sounds/wall.mp3");
    }

    ~Game()
    {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }

    void Draw()
    {
        food.Draw();  
        snake.Draw();
        if (running == false)
        {
            DrawText("Press Any Key to Continue", 10, GetScreenHeight() - 30, 20, DARKGREEN);
        }
    };
    
    void GameOver()
    {
        PlaySound(wallSound);
        cout << "Game Over" << endl;
        running = false;
    }

    void Restart()
    {
        snake.Reset();
        food.GenerateRandomPosition(snake.body);
        running = true;
    }
    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body.at(0), food.position))
        {
            food.position = food.GenerateRandomPosition(snake.body);
            snake.addSegment = true;
            PlaySound(eatSound);
        }
    };

    void CheckCollisionWithEdges()
    {
        if(snake.body.at(0).x == cellCount || snake.body.at(0).x == -1)
        {   
            GameOver();
        }
        if(snake.body.at(0).y == cellCount || snake.body.at(0).y == -1)
        {
            GameOver();
        }
    };

    void CheckCollisionWithTail()
    {
        deque<Vector2> headless_body = snake.body;
        headless_body.pop_front();
        if(ElementInDeque(snake.body.at(0), headless_body))
        {
            GameOver();
        }
    };

    void Update()
    {
        if(running == true)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            CheckCollisionWithTail();
        }
    };
};
int main () {

    cout << "Starting the Game......" << endl;
    const int SCREEN_WIDTH = cellSize*cellCount;
    const int SCREEN_HEIGHT = cellSize*cellCount;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Snake");
    SetTargetFPS(60);
    Game game = Game();

    while(WindowShouldClose() == false)
    {
        if(IsKeyPressed(KEY_W) == true && game.snake.direction.y != 1)
        {
            game.snake.direction = {0, -1};
        };
        if(IsKeyPressed(KEY_S) == true && game.snake.direction.y != -1)
        {
            game.snake.direction = {0, 1};
        };
        if(IsKeyPressed(KEY_A) == true && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1, 0};
        };
        if(IsKeyPressed(KEY_D) == true && game.snake.direction.x != -1)
        {
            game.snake.direction = {1, 0};
        };

        if(EventTriggered(0.2))
        {
            game.Update();
        }    

        if (GetKeyPressed() != 0 && game.running == false)
        {
            game.Restart();
        }

        BeginDrawing();
        ClearBackground(green);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}


bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
};

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (int i =0; i < deque.size(); i++)
    {
        if(Vector2Equals(element, deque.at(i)))
        {
            return true;
        }
    }
    return false;
}


//coded by Bingo
