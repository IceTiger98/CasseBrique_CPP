#pragma once

class score
{
	int nbBrique;
	int life;
	int nbPoint;


public:

	score(int nbVie);

	//accesseur
	int getnbBric();
	int getnbLife();
	int getnbPoint();

	//mutateur 
	void addBrique();
	void addPoint();
	void substrLife();
	void substrBric();

	bool verifVictoire();



};
