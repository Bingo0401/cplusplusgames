#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;
char GetPlayerChoice();
char GetComputerChoice();
void ShowPlayerChoice(char choice);
void ShowComputerChoice(char choice);
char ChooseWinner(char Player, char computer);
bool ReplayChoice();
void AnnounceWinner(char result);

int main(){
    cout <<"******[Rock Paper Scissors]******"<<endl;
    bool Replay = 1;
    int rounds = 0;
    do{
    rounds++;
    cout <<"************[round "<<rounds<<"]************"<<endl;
    char Player, computer, result;
 Player = GetPlayerChoice();
    ShowPlayerChoice (Player);
    computer = GetComputerChoice();
    ShowComputerChoice(computer);
    result = ChooseWinner (Player, computer);
    AnnounceWinner(result);
    cout<<"*********************************"<<endl;
    Replay = ReplayChoice();
    }while(Replay==1);
    cout <<"***********[Game Over]***********"<<endl;
    return 0;
}

char GetPlayerChoice(){
    char choice, Player;
    do{
        cout <<"'R' for Rock"<<endl;
        cout <<"'P' for Paper"<<endl;
        cout <<"'S' for Scissors"<<endl;
        cout <<"Enter your choice: ";
        cin >> choice;
    }while(choice!='R'&&choice!='P'&&choice!='S');
    return choice;
}
char GetComputerChoice(){
    int modifier;
    srand(time(0));
    modifier = rand()%3+1;
    switch(modifier){
        case 1:
        return 'R';
        case 2:
        return 'P';
        case 3:
        return 'S';
 }
}
char ChooseWinner(char Player, char computer){
    switch (Player){
        case 'R':
        switch(computer){
            case 'R':
            return 'T';
            case 'P':
            return 'C';
            case 'S':
            return 'P';
        }
        break;
        case 'P':
        switch(computer){
            case 'R':
            return 'P';
            case 'P':
            return 'T';
            case 'S':
            return 'C';
        }
        break;
        case 'S':
        switch(computer){
            case 'R':
            return 'C';
            case 'P':
            return 'P';
            case 'S':
            return 'T';
        break;
    }
}
}
void ShowPlayerChoice(char choice){
    switch (choice){
        case 'R':
        cout <<"You chose Rock"<<endl;
        break;
        case 'P':
        cout <<"You chose Paper"<<endl;
        break;
        case 'S':
        cout <<"You chose Scissors"<<endl;
        break;
    }
    exit(1);
}
void ShowComputerChoice(char choice){
    switch (choice){
        case 'R':
        cout <<"The computer chose Rock"<<endl;
        break;
        case 'P':
        cout <<"The computer chose Paper"<<endl;
        break;
        case 'S':
        cout <<"The computer chose Scissors"<<endl;
        break;
    }
    exit(1);
}
void AnnounceWinner(char result){
    switch (result){
        case 'P':
        cout <<"You win!"<<endl;
        break;
        case 'C':
        cout <<"You lose!"<<endl;
        break;
        case 'T':
        cout <<"It's a tie!"<<endl;
    }
    exit(1);
}
bool ReplayChoice(){
    char ReplayChoice;
    do{
        cout << "Play Again? [Y]Yes[N]No ";
        cin >> ReplayChoice;
        switch(ReplayChoice){
            case 'Y':
            return 1;
            break;
            case 'N':
            return 0;
            break;
        }
        }while(ReplayChoice != 'Y' && ReplayChoice != 'N');
}