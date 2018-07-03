#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include "Texture.h" 
#include <vector>

// using namespace Ather;

class Scoreboard : public GameEntity 
{
private:
	std::vector<Texture*> kScore; 

public: 
	Scoreboard();
	~Scoreboard(); 

	void Score(int score); 
	void Render(); 

private: 
	void ClearBoard(); 
}; 

#endif 