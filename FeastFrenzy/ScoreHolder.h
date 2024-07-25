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
	static ScoreHolder& GetInstance();
	ScoreHolder();
	int GetScore();
	void IncScore();
	void IncScore(int value);
	void DecScore();
	void ReStart();
private:
	ScoreHolder(const ScoreHolder&) = delete;
	void operator=(const ScoreHolder&) = delete;
};
#endif
