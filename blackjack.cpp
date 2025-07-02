#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;


void displayHand(const vector<int> hand, const int handSize);
int calculateHand(const vector<int> hand, const int handSize);
void hit(vector<int> &hand);

void dealStartingHands();
void playerAction();
void dealerAction();

vector<int> dealerHand;
vector<int> playerHand;
int dealerTotal, playerTotal;


int main(){
    dealStartingHands();
    cout << "The Dealer has:";
    displayHand(dealerHand, dealerHand.size());
    cout << "You have:";
    displayHand(playerHand, playerHand.size());
    playerAction();
    dealerTotal = calculateHand(dealerHand, dealerHand.size());
    dealerAction();
    cout << "Dealer Total: " << dealerTotal << endl;
    cout << "Your Total: " << playerTotal << endl;
    if (playerTotal > dealerTotal){
        cout << "[You Win]" << endl;
    }else if(playerTotal == dealerTotal){
        cout << "[Tie]" << endl;
    }else if (playerTotal < dealerTotal){
        cout << "[You Lost]" << endl;
    }
}


void hit(vector<int> &hand){
    srand(time(0));
    hand.push_back(rand()%13+1);
}
void displayHand(const vector<int> hand, const int handSize){
    cout <<"{ ";
    for (int i = 0; i < handSize; i++){
        switch(hand.at(i)){
            case(1):
                cout << "A" << " ";
                break;
            case(11):
                cout << "J" << " ";
                break;
            case(12):
                cout << "Q" << " ";
                break;
            case(13):
                cout << "K" << " ";
                break;
            default:
                cout << hand.at(i) << " ";
                break;
        }
    }
    cout << "}"<< endl;
}
int calculateHand(const vector<int> hand, const int handSize){
    int total = 0;
    bool hasA = 0;
    for (int i = 0; i < handSize; i++){
        switch(hand.at(i)){
            case(1):
            hasA = 1;
            total +=1;
            break;
            case(11):
            total +=10;
            break;
            case(12):
            total +=10;
            break;
            case(13):
            total +=10;
            break;
            default:
            total +=hand.at(i);
            break;
        }
    }

    if(hasA == 1 && total <= 11)
    total +=10; 

    return total;
}


void dealStartingHands(){

    srand(time(0));

    dealerHand.push_back(rand()%13+1);
    dealerHand.push_back(rand()%13+1);

    playerHand.push_back(rand()%13+1);
    playerHand.push_back(rand()%13+1);

}
void playerAction(){
    playerTotal = calculateHand(playerHand, playerHand.size());
    char hitOrStand;
        if (playerHand.size() > 4){
        cout << "You have a Charlie's Five" << endl;
        cout << "You Won" << endl;
        exit(0);
    }
    cout << "[H]Hit or [S]Stand" << endl;
    cin >> hitOrStand;
    switch (hitOrStand){
        case ('H'):
        hit(playerHand);
        cout << "[You Hit]" << endl;
        playerTotal = calculateHand(playerHand, playerHand.size());
        displayHand(playerHand, playerHand.size());
        if (playerTotal > 21){
            cout << "You have Busted" << endl;
            cout << "You Lost" << endl;
            exit(0);
        }
        playerAction();
        break;
        case ('S'):
        cout << "[You Stand]" << endl;
        break;
        default:
        cout << "[Invalid Input]" << endl;
        cout << "[Try Again]" << endl;
        playerAction();
        break;

    }
}
void dealerAction(){
    if (dealerTotal > 21){
        cout << "The Dealer has Busted" << endl;
        cout << "You Win" << endl;
        exit(0);
    }
    if (dealerTotal < playerTotal && dealerTotal < 18){
        hit(dealerHand);
        cout << "[Dealer Hit]" << endl;
        cout << "Dealer has:";
        displayHand(dealerHand, dealerHand.size());
        dealerTotal = calculateHand(dealerHand, dealerHand.size());
        dealerAction();
    }else{
        cout << "[Dealer Stands]" << endl;
    }
}







//coded by Bingo