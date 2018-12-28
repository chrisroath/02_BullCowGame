#pragma once

#include "pch.h"
#include "FBullCowGame.h"

using FText = std::string;

using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCowGame BCGame;

int main() 
{
	PrintIntro();
	PlayGame();

	system("PAUSE");
	return 0;
}

void PrintIntro() {  
	std::cout << "Welcome to Bulls and Cows a Word Game";
	std::cout <<
		R"(
 .-=-.                .-=-.            .=     ,        =.
  `) )              ( (`      _  _   /'/    )\,/,/(_   \ \
 .' /                \ '.      `//-.|  (  ,\\)\//\)\/_  ) |
(  (   _.-'`::`'-._   )  )     //___\   `\\\/\\/\/\\///'  /
 \  `'`    .::.    `'`  /   ,-"~`-._ `"--'_   `"""`  _ \`'"~-,_
  `-._\`~`      `~`/_.-'    \       `-.  '_`.      .'_` \ ,-"~`/
 _,=` /            \ `=,_    `.__.-'`/   (-\        /-) |-.__,'
(    ,(^\        /^),    )     ||   |     \O)  /^\ (O/  |
 `~~` \0)\      /(0/ `~~`      `\\  |         /   `\    /
       | /`    '\ |              \\  \       /      `\ /
       |          |               `\\ `-.  /' .---.--.\
       |          |                 `\\/`~(, '()      ('
       |          |                  /(O) \\   _,.-.,_)
       /          \                 //  \\ `\'`      /
       \()      ()/               / |  ||   `""""~"`
        `._-==-_.'               /'  |__||
           `""`                        `o
           BULL           AND                 COW
                   A word game

)";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram Im thinking of ? \n"; 
	std::cout << "Word List: dog, planet, mop, month, four, cat, they\n";
	std::cout << "	open, close, backward, forward, comfort, movie, faith";
	std::cout << std::endl;
}

void PlayGame()
{
	do {
		int32 maxTries = BCGame.GetMaxTries();
		
		for (int32 count = 1; count <= maxTries; count++) {
			FText Guess = GetValidGuess();

			if (BCGame.IsGameWon() == true) {
				std::cout << "Conradulations You've Won\n";
				break;
			}
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
			std::cout << "Bulls =  " << BullCowCount.Bulls;
			std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		}
	} 
	while (AskToPlayAgain() ); 
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again: Y or N:? ";
	FText response = "";
	std::getline(std::cin, response);
	if ((response[0] == 'Y') || (response[0] == 'y')){
		std::cout << "OK. Play again ... Here we Go ...\n\n";
		BCGame.Reset();
		PrintIntro();
		return true;
	}
	else{
		std::cout << "\nOK Thanx for Playing Bulls n Cows, C ya next time...\n";
		return false;
	}
}

FText GetValidGuess() {
	int32 currentTries = BCGame.GetCurrentTries();
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText guess = "";
	do
	{
		if (BCGame.IsGameWon() == true) {
			break;
		}	
		std::cout << "Try Number: " << currentTries << " of " << BCGame.GetMaxTries();
			std::cout <<"  - Enter your guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please Enter only lowercase letters\n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);

	currentTries++;
	if (currentTries > BCGame.GetMaxTries()) {
		std::cout << "You Lose ... better luck next time\n";
		return guess;
	}
	return guess;
}


