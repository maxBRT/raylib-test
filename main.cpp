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
	AnimData nebData{ 
		{0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Rect
		{SCREENWIDTH, SCREENHEIGHT - nebData.rect.height}, //Postion
		0, // Animation Frame
		1.0/12.0, // Update Time
		0 // Run Time
		};
	AnimData neb2Data{ 
		{0.0, 0.0, nebula.width / 8, nebula.height / 8}, // Rect
		{SCREENWIDTH + 300, SCREENHEIGHT - nebData.rect.height}, //Postion
		0, // Animation Frame
		1.0/12.0, // Update Time
		0 // Run Time
		};

	int nebulaMoveSpeed = -200;

	while (!WindowShouldClose()) 
	{
		float dT = GetFrameTime();
		scarfyData.runTime += dT;
		nebData.runTime += dT;
		neb2Data.runTime += dT;
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
		nebData.pos.x += nebulaMoveSpeed * dT;
		if (nebData.pos.x + nebData.rect.width < 0)
		{
			nebData.pos.x = SCREENWIDTH;
		}
		nebData.rect.x = nebData.frame * nebData.rect.width;
		if (nebData.runTime >= nebData.updateTime)
		{
			nebData.frame ++;
			nebData.runTime = 0;
		}
		if (nebData.frame > 7)
		{
			nebData.frame = 0;
		}
		DrawTextureRec(nebula, nebData.rect, nebData.pos, WHITE);

		neb2Data.runTime += dT;
		neb2Data.pos.x += nebulaMoveSpeed * dT;
		neb2Data.rect.x = neb2Data.frame * neb2Data.rect.width;
		if (neb2Data.pos.x + neb2Data.rect.width < 0)
		{
			neb2Data.pos.x = SCREENWIDTH;
		}
		if (neb2Data.runTime >= neb2Data.updateTime)
		{
			neb2Data.frame ++;
			neb2Data.runTime = 0;
		}
		if (neb2Data.frame > 7)
		{
			neb2Data.frame = 0;
		}
		DrawTextureRec(nebula, neb2Data.rect, neb2Data.pos, WHITE);

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
