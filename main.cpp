#include "raylib.h"
#include <iostream>

struct AnimData
{
	Rectangle rect;
	Vector2 pos;
	int frame;
	float updateTime;
	float runTime;
	float testTest;
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
	AnimData scarfyData;
	scarfyData.rect.width = scarfy.width / 6;
	scarfyData.rect.height = scarfy.height;
	scarfyData.rect.x = 0;
	scarfyData.rect.y = 0;
	scarfyData.pos.x = SCREENWIDTH / 2 - scarfyData.rect.width / 2;
	scarfyData.frame = 0;
	scarfyData.updateTime = 1.0 / 12.0;
	scarfyData.runTime = 0;

	//Nebula Hazard
	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	Rectangle nebulaRect{0.0, 0.0, nebula.width / 8, nebula.height / 8};
	Vector2 nebulaPos;
	nebulaPos.x = SCREENWIDTH;
	nebulaPos.y = SCREENHEIGHT - nebulaRect.height; 
	int nebulaFrame = 0; 
	float nebUpdateTime = 1.0/12.0;
	float nebRunTime = 0;


	Rectangle nebula2Rect{0, 0, nebula.width / 8, nebula.height / 8};
	Vector2 nebula2Pos{SCREENWIDTH + 300, SCREENHEIGHT - nebula2Rect.height};
	int nebula2Frame = 0; 
	float neb2UpdateTime = 1.0/18.0;
	float neb2RunTime = 0;

	int nebulaMoveSpeed = -200;

	int y_velocity = 0;
	int jump_velocity = -580; 
	const int GRAVITY = 1'000;
	bool has_jumped = true;

	while (!WindowShouldClose()) 
	{
		float dT = GetFrameTime();
		scarfyRunTime += dT;
		nebRunTime += dT;
		BeginDrawing();
		ClearBackground(WHITE);

		//Animate Scarfy
		scarfyRect.x = scarfyFrame * scarfyRect.width;
		if (scarfyRunTime >= scarfyUpdateTime && !has_jumped)
		{
			scarfyFrame++;
			scarfyRunTime = 0;
		}
		if (scarfyFrame > 5)
		{
			scarfyFrame = 0;
		}
		DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

		//Nebula stuff
		nebulaPos.x += nebulaMoveSpeed * dT;
		if (nebulaPos.x + nebulaRect.width < 0)
		{
			nebulaPos.x = SCREENWIDTH;
		}
		nebulaRect.x = nebulaFrame * nebulaRect.width;
		if (nebRunTime >= nebUpdateTime)
		{
			nebulaFrame ++;
			nebRunTime = 0;
		}
		if (nebulaFrame > 7)
		{
			nebulaFrame = 0;
		}
		DrawTextureRec(nebula, nebulaRect, nebulaPos, WHITE);

		neb2RunTime += dT;
		nebula2Pos.x += nebulaMoveSpeed * dT;
		nebula2Rect.x = nebula2Frame * nebula2Rect.width;
		if (nebula2Pos.x + nebula2Rect.width < 0)
		{
			nebula2Pos.x = SCREENWIDTH;
		}
		if (neb2RunTime >= neb2UpdateTime)
		{
			nebula2Frame ++;
			neb2RunTime = 0;
		}
		if (nebula2Frame > 7)
		{
			nebula2Frame = 0;
		}
		DrawTextureRec(nebula, nebula2Rect, nebula2Pos, WHITE);
		/*if (nebulaRect.y >= nebula.height - nebulaRect.height && nebulaFrame > 4)
		{			
			nebulaRect.y = 0;
			nebulaRect.x = 0;
		}*/
		

		//Ground check and if not on ground apply gravity progressively to velocity	
		if(scarfyPos.y >= SCREENHEIGHT - scarfyRect.height)
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
		
		scarfyPos.y += y_velocity * dT;

		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
	return 0;
	
}
