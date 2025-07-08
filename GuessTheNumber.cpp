#include<iostream>
#include<random>
#include<ctime>


using namespace std;


int main(){
srand(time(0));
int guess, ans, max, min, numberOfGuess;
numberOfGuess = 0;
const int ANS = rand()%98 + 2;
max = 100;
min = 0;

while(ANS != guess)
{
cout << "Guess a number between " << min << " and " << max << endl;
cout <<"Guess: ";
cin >> guess;
numberOfGuess++;
if (guess >= max || min >= guess)
cout << "Are You Stupid?" << endl;
else if (max > guess && guess > ANS)
max = guess;
else if (ANS > guess && guess > min)
min = guess;
}

cout << "Congradulations, You guessed the answer " << ANS << " in " << numberOfGuess << " guesses." << endl; 
}




//coded by Bingo


