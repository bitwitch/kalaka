#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	Score(0);
}

Scoreboard::~Scoreboard()
{
	ClearBoard(); 
}

void Scoreboard::ClearBoard()
{
	for (int i=0; i<kScore.size(); i++)
	{
		delete kScore[i];
		kScore[i] = NULL; 
	}
	kScore.clear(); 
}

void Scoreboard::Score(int score)
{
	ClearBoard(); 

	// TODO(shaw): put colors in a common location 
	SDL_Color offwhite = { 230, 230, 230 }; 
	if (score == 0)
	{	
		for (int i=0; i<2; i++)
		{
			kScore.push_back(new Texture("0", "emulogic.ttf", 24, offwhite));
			kScore[i]->Parent(this); 
			kScore[i]->Pos(Vector2(-24.0f*i, 0.0f)); 
		}
	}
	else 
	{
		std::string str = std::to_string(score); 
		int lastIndex = str.length() - 1; 
		for (int i=0; i <= lastIndex; i++)
		{
			kScore.push_back(new Texture(str.substr(i, 1), "emulogic.ttf", 24, offwhite));
			kScore[i]->Parent(this); 
			kScore[i]->Pos(Vector2(-24.0f*(lastIndex - i), 0.0f)); 
		}
	}
}

void Scoreboard::Render()
{
	for (int i=0; i<kScore.size(); i++)
	{
		kScore[i]->Render(); 
	}
}