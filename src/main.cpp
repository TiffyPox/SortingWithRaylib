#include "raylib.h"
#include "raymath.h"

#include <array>
#include <string>
#include <iostream>

int screenWidth = 1280;
int screenHeight = 720;
int maxNum = 100;

float sortTimer = 0.01f;
bool sorted = false;
int swappedIndex = 0;

std::array<int, 51> nums;

void RenderArray()
{
    int padding = 5;
    int x = 0;
    int y = screenHeight;
    float numCount = (float) nums.size();
    float rectWidth = (screenWidth ) / numCount - padding;
    Color color = RED;

    int curr = 1;
    for(int num : nums)
    {
        float rectHeight = screenHeight / maxNum * num;
        Vector2 vecPos { x, y - rectHeight };
        Vector2 vecSize { rectWidth, rectHeight };

        if (sorted)
        {
            color = GREEN;
        }
        else
        {
            color = (curr - 1 == swappedIndex ? WHITE : RED);
        }

        DrawRectangleV(vecPos, vecSize, color);
        DrawText(std::to_string(curr++).c_str(), x, y - rectHeight - 12, 12, WHITE);
        x += rectWidth + padding;
    }
}


void BubbleSort()
{
    int curr = 0;

    int next = 0;
    for (int i = swappedIndex; i < nums.size() - 1; i++)
    {
        curr = nums[i];
        next = nums[i + 1];

        if (curr > next)
        {
            nums[i] = next;
            nums[i + 1] = curr;
            swappedIndex = i;
            return;
        }
    }

    if(swappedIndex == 0)
    {
        sorted = true;
    }

    swappedIndex = 0;
}

void GenerateArray()
{
    for(int i = 0; i < nums.size(); ++i)
    {
        float r = ((double) rand() / (RAND_MAX));
        nums[i] = (int)(r * maxNum);
    }
}

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Sorting with RayLib");
    InitAudioDevice();
    SetTargetFPS(60);

    Color bgColor { 50, 50, 80 };

    GenerateArray();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(bgColor);

        if(sortTimer < 0)
        {
            BubbleSort();
            sortTimer = 0.01f;
        }
        else
        {
            sortTimer -= GetFrameTime();
        }

        RenderArray();

        EndDrawing();
    }

    CloseWindow();
}