#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<time.h>
using namespace std;
int gn=1;
int res[5]={9,9,9,9,9};
class Blackjack
{
private:
    int dhand[5],phand[5],dhs,pSum,phs,dSum;
    char phit,pstand;
    bool playerDone,dealerDone;
    public:
    void addCard()
    {
        if (phs <= 5)
        {
            phand[phs] = 1 + (rand() % 11);
            phs++;
        }
        else
        {
            cout << "Sorry. You have reached the maximum number of cards (5)." << endl;
            playerDone = true;
        }
    }

    void addCard(int x)
    {
        if (dhs <= 5)
        {
            dhand[dhs] = 1 + (rand() % 11);
            dhs++;
        }
        else
        {
            dealerDone = true;
        }
    }
    void printHand()
    {
        cout << "Your current hand is...\n";

        for (int i = 0; i < phs; i++)
        {
            cout << "    | " << phand[i] << " |    \n\n";
        }

        cout << "Dealer's current hand is...\n";

        for (int j = 0; j < dhs; j++)
        {
            cout << "    | " << dhand[j] << " |    \n\n";
        }
    }

    void sumHands()
    {
        dSum = 0;
        pSum = 0;
        for (int i = 0; i < dhs; i++)
        {
            dSum += dhand[i];
        }

        for (int j = 0; j < phs; j++)
        {
            pSum += phand[j];
        }

        cout << "Current player hand sum is: " << pSum << endl;
    }
    Blackjack()
    {
        srand((unsigned)time(0));
        dhs = 0;
        phs = 0;
        dSum = 0;
        pSum = 0;
        playerDone = false;
        dealerDone = false;
    }
    int playGame()
    {
        cout << "Welcome to Blackjack!\n";
        addCard();
        addCard();
        addCard(1);
        addCard(1);
        sumHands();
        printHand();

        if (dSum == 21)
        {
            cout << "Dealer has blackjack. Dealer wins.\n";
            int a = gn-1;
            res[a]=2;
            return 42;
        }
        else if (pSum == 21)
        {
            cout << "Player has blackjack. Player wins.\n";
            int a = gn-1;
            res[a]=0;
            return 0;
        }

        while (dealerDone == false || playerDone == false)
        {
            if (playerDone == false)
            {
                cout << "Would you like to hit? (1 - Yes, 2 - No)\n";
                cin>>phit;
                if(phit!='1'&&phit!='2')
                {
                    for(int i=0;phit!='1'&&phit!='2';)
                    {
                        cout<<"Enter a Valid Option (1 - Yes, 2 - No)\n";
                        cin>>phit;
                    }

                }

                if (phit == '1')
                {
                    addCard();
                    printHand();
                    sumHands();

                    if (pSum > 21)
                    {
                        cout << "Player's hand exceeded 21. Player loses.\n";
                        int a = gn-1;
                        res[a]=2;
                        return 0;
                    }
                }
            }

            if (playerDone == false)
            {
                cout << "Would you like to stand? (1 - Yes, 2 - No)\n";
                cin >> pstand;
                if(pstand!= '1'&&pstand!='2')
                {
                    for(int i=0;pstand!= '1'&&pstand!='2';)
                    {
                        cout<<"Enter a Valid Option (1 - Yes, 2 - No)\n";
                        cin>>pstand;
                    }
                }

            }

            if (pstand == '1')
            {
                playerDone = true;
            }

            if (dSum < 17 && dealerDone == false)
            {
                addCard(1);
                printHand();
                sumHands();

                if (dSum > 21)
                {
                    cout << "Dealer hand exceeded 21. Dealer loses.\n";
                    int a = gn-1;
                    res[a]=0;
                    return 0;
                }
            }
            else if (dSum >= 17)
            {
                dealerDone = true;
            }

            if (pSum == 21 && dSum == 21)
            {
                cout << "Player and dealer reached 21.\n";
                int a = gn-1;
                    res[a]=1;
                return 0;
            }
            else if (pSum == 21)
            {
                cout << "Player reached 21. Player wins.\n";
                int a = gn-1;
                    res[a]=0;
                return 0;
            }
            else if (dSum == 21)
            {
                cout << "Dealer reached 21. Dealer wins.\n";
                int a = gn-1;
                    res[a]=2;
                return 0;
            }
            if ((playerDone == true && dealerDone == true) || (phs == 5 && dhs == 5))
            {
                if (dSum < pSum)
                {
                    cout << "Sum of your hand exceeds the dealer's sum of " << dSum << "! You win!";
                    int a = gn-1;
                    res[a]=0;
                    return 0;
                }
                else if (pSum == dSum)
                {
                    cout << "Dealer sum of " << dSum << " is equal to the sum of your hand. Tie game.";
                    int a = gn-1;
                    res[a]=1;
                    return 0;

                }
                else if (dSum > pSum)
                {
                    cout << "Sum of your hand is lower than the dealer's sum of " << dSum << ". You lose!";
                    int a = gn-1;
                    res[a]=2;
                    return 0;
                }
            }
        }
    }
};
void result()
    {
        float points=0;
        time_t now = time(0);
        char* dt = ctime(&now);
        ofstream ofile;
        ofile.open("FinalTest5.csv");
        ofile<<"Game Results, "<<endl<<" Time:, "<<dt;
        ofile<<endl<<endl<<"Game Number , Player Result , Dealer 	Result"<<endl;
        for(int i=0;i<5;i++)
        {
            if(res[i]==0)
            {
                ofile<<(i+1)<<", Win , Loss,"<<endl;
                points+=1;
            }
            else if(res[i]==1)
            {
                ofile<<(i+1)<<", Tie , Tie,"<<endl;
                points+=0.5;
            }
            else if(res[i]==2)
            {
                ofile<<(i+1)<<", Loss , Win,"<<endl;
            }
            else if(res[i]==9)
            {
                ofile<<(i+1)<<",- , - ,"<<endl;
            }
        }
        ofile<<"Total,"<<points<<","<<(gn-points-1)<<","<<endl<<endl<<endl;
        ofile<<"Win,1 Point" <<endl<<"Tie,0.5 points"<<endl<<" Loss,0 Points "<<endl<<endl<<"Thanks For Playing";
        ofile.close();
    }
int main()
{
    char rule;
    cout<<"Do you Wish to read the rules (1 - Yes)"<<endl;
    cin.get(rule);
    if(rule=='1')
    {
        cout<<"Game Rules:\nThe Goal of the game is to get the total value of their cards to 21. The Player Closest to 21 wins.\nIf the total value of cards is above 21, it will result in a instant loss.\nPlayer Receives 2 cards initially and has the option to take 3 extra cards.\nThe Player can receive upto 5 cards. The player can choose to stop if they are satisfied with their cards.\nAt the end of the game , you can see the results on an excel sheet."<<endl;
    }
    char exitGame = '1';
    do
    {
        Blackjack obj;
        obj.playGame();
        ++gn;
        cout << "\nWould you like to play again? (1 - Yes, 2 - No)"<<endl;
        cin >> exitGame;
        if(exitGame !='1'&&exitGame!='2')
        {
            for(int x=0;exitGame !='1'&&exitGame!='2';)
            {
                cout<<"Enter a Valid Option (1 - Yes, 2 - No)\n";
                cin>>exitGame;
            }
        }
        system("cls");
    }while (exitGame == '1');
    result();
    cout << "\nThanks for playing!\n";
    return 0;
}
