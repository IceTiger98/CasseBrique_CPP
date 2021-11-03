#include "balle.h"

balle::balle(int x, int y, int w, int h, int vx, int vy)
{
	rectBalle.x = x;
	rectBalle.y = y;
	rectBalle.w = w;
	rectBalle.h = h;
	vX = vx;
	vY = vy;
	paddleCenter = 0;
	d = 0;
}

balle::~balle()
{
}

SDL_Rect balle::getRectBalle()
{
	return rectBalle;
}

void balle::setRectBalle(int x, int y, int w, int h)
{
	rectBalle.x = x;
	rectBalle.y = y;
	rectBalle.w = w;
	rectBalle.h = h;
}

void balle::deplacementBalle(int w)
{

	rectBalle.y += vY;

	rectBalle.x += vX;
}

void balle::rebondJoueur(SDL_Rect p)
{
	//calcul le rebond de la balle contre le paddle
	if ((rectBalle.x >= p.x) && (rectBalle.x <= p.x + p.w) && (rectBalle.y >= p.y) && (rectBalle.y <= p.y + p.h))
	{
		paddleCenter = p.x + (p.w / 2);
		d = paddleCenter - rectBalle.x;
		vX += d * -0.1;
		vY *= -1;
	}
}

void balle::rebondMur(int w)
{
	//Calcul le rebond de la balle contre les murs
	//Mur gauche droite
	if ((rectBalle.x < 1) || (rectBalle.x > w - 1))
	{
		vX *= -1;
	}
	//Mur du haut
	if (rectBalle.y < 1)
	{
		vY *= -1;
	}
}

void balle::rebondBric(bric* b, score* scr)
{
	if (((rectBalle.x + rectBalle.w / 2 >= b->getRect().x) && (rectBalle.x + rectBalle.w / 2 <= b->getRect().x + b->getRect().w) && (rectBalle.y >= b->getRect().y) && (rectBalle.y <= b->getRect().y + b->getRect().h))
		&& (b->getState() == true))
	{

		if (((rectBalle.x >= b->getRectMid().x) && (rectBalle.x <= b->getRectMid().x + b->getRectMid().w) && (rectBalle.y + rectBalle.h / 2 >= b->getRectMid().y) && (rectBalle.y + rectBalle.h / 2 <= b->getRectMid().y + b->getRectMid().h))
			|| ((rectBalle.x + rectBalle.w >= b->getRectMid().x) && (rectBalle.x + rectBalle.w <= b->getRectMid().x + b->getRectMid().w) && (rectBalle.y + rectBalle.h / 2 >= b->getRectMid().y) && (rectBalle.y + rectBalle.h / 2 <= b->getRectMid().y + b->getRectMid().h))
			&& (b->getState() == true))
		{
			vX *= -1;
			b->setState(false);
		}

		else

		{
			vY *= -1;
			b->setState(false);
		}
		scr->addPoint();
		scr->substrBric();

	}
}

void balle::spawnBalle(score* game, int w, int h, player* p)
{
	if (rectBalle.y > w + 50)
	{
		rectBalle.x = w / 2;
		rectBalle.y = h / 2;
		vX = 0;
		vY = 5;
		p->setPlayerPoseX(w / 2 - 50);
		p->setPlayerPoseY(h - 20);
		game->substrLife();
	}
}