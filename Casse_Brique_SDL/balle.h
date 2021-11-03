#pragma once
#include "define.h"


class score;
class player;
class bric;
class balle
{
	SDL_Rect rectBalle;
	int vX, vY, paddleCenter, d;



public:

	//constructeur
	balle(int x, int y, int w, int h, int vx, int vy);

	//destructeur
	~balle();

	//accesseur 
	SDL_Rect getRectBalle();

	//mutateurs
	void setRectBalle(int x, int y, int w, int h);
	void deplacementBalle(int w);
	void rebondJoueur(SDL_Rect p);
	void rebondMur(int w);
	void rebondBric(bric* b, score* scr);

	void spawnBalle(score* game, int w, int h, player* p);

};
