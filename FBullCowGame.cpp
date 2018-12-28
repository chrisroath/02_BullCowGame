#pragma once

#include "pch.h"
#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()  // default Ctor
{
	Reset();
}

FBullCowGame::~FBullCowGame()
{

}

int FBullCowGame::GetMaxTries()const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,12},{7,15},{8,17} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

int FBullCowGame::GetCurrentTries()const { return MyCurrentTries; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon()const { return bIsGameWon;  }

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess)const
{
	if (!IsIsogram(guess) ) { // if the guess is not an Isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess)) {    // if the guess is not all lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLength() ) {  // if the guess is the wrong length
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

void FBullCowGame::Reset()
{
	MyHiddenWordList = { "dog","planet","mop","month","four","cat","they",
		            "open","close","backward","forward","comfort","movie","faith"};
	std::random_device rd;  // only used once to initialize the seed engine
	std::mt19937 rng(rd()); // random number engine used
	std::uniform_int_distribution<int> uni(0,13);  // guaranteed unbiased 
	auto random_integer = uni(rng);
	MyHiddenWord = MyHiddenWordList[random_integer];
	MyCurrentTries = 1;
	bIsGameWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTries++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming the same length as guess
	// loop thru hidden word
	for (int32 MHWChar=0; MHWChar < WordLength; MHWChar++){ // i

		for (int32 GChar=0; GChar < WordLength; GChar++){ // j
			//compare letters against the guess
			if(Guess[GChar] == MyHiddenWord[MHWChar]){
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) { /// did player win game?
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	/* A Map is essentually a list of data that has values, in this case the <char,  >, in
	   the string Word and its value <    ,bool> is set to true when the Map is populated 
	   in the loop. So for the Word "Happy" value 'h' = true
	                                              'a' = true;
												  'p' = true;
												  'p' = false;
	   The second value 'p' already exisxts in the Map so it then returns false and exits the Map
	*/
	for (auto input : Word)
	{
		input = tolower(input);   // handle mixed case

		if (LetterSeen[input]) {  // if the letter is in the map
			return false; 	// we do not have not isogram
		}
		else {
			LetterSeen[input] = true; // add the letter to the map as seen
		}	
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
		if (!islower(Letter))
			return false;

	return true;
}
