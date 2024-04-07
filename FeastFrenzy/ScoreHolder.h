//
//  ScoreHolder.h
//  Feast Frenzy game
//
//  Created by Oscar Martinez on 1/Apr/2024.
//
#pragma once
#ifndef SCOREHOLDER_H
#define SCOREHOLDER_H
class ScoreHolder
{
private:
	int _score;
public:
	ScoreHolder();
	int GetScore();
	void IncScore();
	void DecScore();
};
#endif
