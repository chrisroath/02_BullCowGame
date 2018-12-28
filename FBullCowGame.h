#pragma once
#include "pch.h"

using FString = std::string;
using int32 = int;

struct FBullCowCount {     // all values are initialized to zero
	int32 Bulls = 0;
	int32 Cows  = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	Wrong_Length,
	Not_Isogram,
	Not_Lowercase,
	OK
};

class FBullCowGame {
public:
	FBullCowGame();
	~FBullCowGame();

	int32 GetMaxTries()const;
	int32 GetCurrentTries()const;
	int32 GetHiddenWordLength()const;
	bool IsGameWon()const;

	EGuessStatus CheckGuessValidity(FString guess)const;
	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString)const;
	bool IsLowercase(FString)const;
private:
	int32 MyCurrentTries;
	FString MyHiddenWord;
	bool bIsGameWon;
	std::vector<FString>MyHiddenWordList;
};


