#include "raylib.h"
#include <iostream>

struct AnimData
{
	Rectangle rect;
	Vector2 pos;
	int frame;
	float updateTime;
	float runTime;
};


int main () 
{
	//Initialize window
	const float SCREENWIDTH = 640;
	const float SCREENHEIGHT = 320;
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Dasher");		
	SetTargetFPS(60);


	//Scarfy
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyData{
		{0, 0 ,scarfy.width / 6, scarfy.height}, //Rect 
		{SCREENWIDTH / 2 - scarfyData.rect.width / 2, SCREENHEIGHT - scarfy.height}, // Position
		0, // Amimation frame
		1.0/ 12.0, // Update time
		0	// Runtime
		};

	int y_velocity = 0;
	int jump_velocity = -580; 
	const int GRAVITY = 1'000;
	bool has_jumped = true;

	//Nebula Hazard
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

	const int SIZEOFNEBULEA{6};	
	AnimData nebulea[SIZEOFNEBULEA];
	for (int i = 0; i < SIZEOFNEBULEA; i++)
	{
		nebulea[i].rect.x = 0.0;
		nebulea[i].rect.y = 0.0;
		nebulea[i].rect.width = nebula.width / 8;
		nebulea[i].rect.height = nebula.height / 8;
		nebulea[i].pos.y = SCREENHEIGHT - nebula.height / 8;
		nebulea[i].pos.x = SCREENWIDTH + i * 300;
		nebulea[i].frame = 0;
		nebulea[i].runTime = 0.0;
		nebulea[i].updateTime = 1.0 / 18.0;
	}

	int nebulaMoveSpeed = -250;

	while(!WindowShouldClose())
	{
	float dT = GetFrameTime();
	scarfyData.runTime += dT;
	for(int i = 0; i < SIZEOFNEBULEA; i++)
	{
		nebulea[i].runTime += dT;
	}
	BeginDrawing();
	ClearBackground(WHITE);

	//Animate Scarfy
	scarfyData.rect.x = scarfyData.frame * scarfyData.rect.width;
	if (scarfyData.runTime >= scarfyData.updateTime && !has_jumped)
	{
		scarfyData.frame++;
		scarfyData.runTime = 0;
	}
	if (scarfyData.frame > 5)
	{
		scarfyData.frame = 0;
	}
	DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

	//Nebula stuff
	for (int i = 0; i < SIZEOFNEBULEA; i++)
	{
		nebulea[i].pos.x += nebulaMoveSpeed * dT;
		nebulea[i].rect.x = nebulea[i].frame * nebulea[i].rect.width;
		if (nebulea[i].runTime >= nebulea[i].updateTime)
		{
			nebulea[i].frame ++;
			nebulea[i].runTime = 0;
		}
		if (nebulea[i].frame > 7)
		{
			nebulea[i].frame = 0;
		}
		DrawTextureRec(nebula, nebulea[i].rect, nebulea[i].pos, WHITE);
	}

	//Ground check and if not on ground apply gravity progressively to velocity	
	if(scarfyData.pos.y >= SCREENHEIGHT - scarfyData.rect.height)
	{
		has_jumped = false;
		y_velocity = 0;
	}
	else
	{
		y_velocity += GRAVITY * dT;
	}		

	//Jump impulse
	if(IsKeyPressed(KEY_SPACE) && !has_jumped)
	{
		y_velocity = jump_velocity;
		has_jumped = true;
	} 
	
	scarfyData.pos.y += y_velocity * dT;

	EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
	return 0;
	
}
