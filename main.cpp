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

bool IsOnGround(AnimData data, int windowheight)
{
	return data.pos.y >= windowheight - data.rect.height;
};

AnimData UpdtAnimation(AnimData data, float deltaTime, int maxFrame)
	{
		data.rect.x = data.frame * data.rect.width;
		if (data.runTime >= data.updateTime)
		{
			data.frame++;
			data.runTime = 0;
		}
		if (data.frame > maxFrame)
		{
			data.frame = 0;
		}
		return data;
	};

void DrawXground(float xPos, Texture2D image)
{
	Vector2 bg1Pos{xPos, 0.0};
	DrawTextureEx(image, bg1Pos, 0, 2, WHITE);
	Vector2 bg2Pos{xPos + image.width * 2, 0.0};
	DrawTextureEx(image, bg2Pos, 0, 2, WHITE);
};

float UpdtXGroundPos(float xPos, Texture2D image, int scrollamount, float delta)
{
	xPos -= 20 * delta;
	if(xPos <= (image.width * 2) * -1)
	{
		xPos = 0.0;
	}
	return xPos;
}

int main () 
{
	//Initialize window
	const float SCREENWIDTH = 500;
	const float SCREENHEIGHT = 320;
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Dasher");		
	SetTargetFPS(60);
	
	//Backgrounds Textures
	Texture2D background = LoadTexture("textures/far-buildings.png");
	float bgX{};
	Texture2D midground = LoadTexture("textures/back-buildings.png");
	float mgX{};
	Texture2D foreground = LoadTexture("textures/foreground.png");
	float fgX{};

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

	//Draw and update backgroud
	float bgX{};
	bgX = (bgX, background, 90, dT);
	DrawXground(bgX, background);

	mgX -= 30 * dT;
	if(mgX <= (midground.width * 2) * -1)
	{
		bgX = 0.0;
	}
	DrawXground(mgX, midground);
	
	fgX -= 60 * dT;
	if(fgX <= (foreground.width * 2) * -1)
	{
		fgX = 0.0;
	}
	DrawXground(fgX, foreground);


	//Animations
	if(!has_jumped)
	{ 
		scarfyData = UpdtAnimation(scarfyData, dT, 5); // Update Scarfy
	}
	DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

	for (int i = 0; i < SIZEOFNEBULEA; i++) //Update and move nebulea
	{
		nebulea[i].pos.x += nebulaMoveSpeed * dT;
		nebulea[i] = UpdtAnimation(nebulea[i], dT, 7);
		DrawTextureRec(nebula, nebulea[i].rect, nebulea[i].pos, WHITE);
	}

	//Ground check and if not on ground apply gravity progressively to velocity	
	if(IsOnGround(scarfyData, SCREENHEIGHT))
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
	UnloadTexture(background);
	UnloadTexture(midground);
	UnloadTexture(foreground);
	CloseWindow();
	return 0;
	
}
