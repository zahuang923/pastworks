#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Board
{
private:
    struct Space
    {
        string name;
        int points;
        Space *next;
        Space *prev;
    };
    
    Space *start;
    Space *player1;
    Space *player2;
    
public:
    //constructor
    Board()
    {
        start = nullptr;
        player1 = nullptr;
        player2 = nullptr;
    }
    
    //destructor frees up all the memory used by the board by deleting all the spaces
    ~Board()
    {
        if (start == nullptr)
            return;
        
        Space * p = start;
        Space * q;
        do
        {
            q = p;
            p = p->next;
            delete q;
        }while(p != start);
        start = nullptr;
    }
    
    string getSpaceName(int player)
    {
        if(player == 1)
           return player1->name;
        else if (player == 2)
            return player2->name;
        else
            return "please enter 1 or 2 only";
    }
    
    int getSpacePoints(int player)
    {
        if(player ==1)
            return player1->points;
        else if (player==2)
            return player2->points;
        else return 0;
    }
    
    //takes in a name and point value and dynamically allocates a new space to the board as a circularly linked list
    void addSpace(string name, int points)
    {
        Space * s = new Space;
        s->name = name;
        s->points = points;
        s->next = nullptr;
        s->prev = nullptr;
        
        if(start == nullptr) //case when list is empty
        {
            start = s;
            start->next = s;
            start->prev = s;
        }
        else //case for adding additional nodes when list is not empty
        {
            s->prev = start->prev;
            start->prev->next = s;
            s->next = start;
            start->prev = s;
        }
    }
    
    //move's pointers for player1 and player2
    void move(char direction, int playerNumber, int roll)
    {
            switch(toupper(direction))
            {
                case 'F':
                        if (playerNumber == 1)
                        {
                            switch (roll) {
                                case 1:
                                    player1 = player1->next;
                                    break;
                                case 2:
                                    player1 = player1->next->next;
                                    break;
                                case 3:
                                    player1 = player1->next->next->next;
                                    break;
                            }
                        }
                        else if (playerNumber == 2)
                        {
                            switch (roll) {
                                case 1:
                                    player2 = player2->next;
                                    break;
                                case 2:
                                    player2 = player2->next->next;
                                    break;
                                case 3:
                                    player2 = player2->next->next->next;
                                    break;
                            }
                        }
                        break;
                case 'B':
                    if(playerNumber == 1)
                    {
                        switch (roll) {
                            case 1:
                                player1 = player1->prev;
                                break;
                            case 2:
                                player1 = player1->prev->prev;
                                break;
                            case 3:
                                player1 = player1->prev->prev->prev;
                                break;
                        }
                    }
                    else if (playerNumber == 2)
                    {
                        switch (roll) {
                            case 1:
                                player2 = player2->prev;
                                break;
                            case 2:
                                player2 = player2->prev->prev;
                                break;
                            case 3:
                                player2 = player2->prev->prev->prev;
                                break;
                        }
                    }
                    break;
            }
    }

    //places player1 and player2 on the start space by setting their pointers to the address of the start space.
    void reset()
    {
        player1 = start;
        player2 = start;
    }
    
    //this method prints out all the board spaces and their point values and
    //also displays the space that each player is currently located on.
    void printBoard()
    {
        if(start == nullptr)
        {
            cout << "The board is empty." << endl;
        }
        else
        {
            Space* temp = start;
            
            cout << left << "Space" << "    " << right << "Points" << endl;
            
            do
            {
                cout.width(10);
                cout << left <<temp->name << "    " <<right << temp->points << "   " << right << endl;
                temp = temp->next;
            }
            while (temp != start);
            
            cout << endl;
            cout << "Player 1 is at " << getSpaceName(1) << endl; //" and has " << getSpacePoints(1)  << endl;
            cout << "Player 2 is at " << getSpaceName(2) << endl; // " and has " << getSpacePoints(2) << endl;
            cout << endl << endl;
        }
    }
};


int main()
{
    //initialize values
    int score1 = 50;
    int score2 = 50;
    int turnnum = 1;
    int dice;
    string player;
    int playerNumber;
    char input;

    Board gameboard;
    
    //create game board as doubly circular linked list by adding spaces and their values.
    gameboard.addSpace("Start", 0);
    gameboard.addSpace("Alpha", 10);
    gameboard.addSpace("Beta", -15);
    gameboard.addSpace("Gamma", 27);
    gameboard.addSpace("Delta", -32);
    gameboard.addSpace("Epsilon", 12);
    gameboard.addSpace("Zeta", -45);
    gameboard.addSpace("Eta", 42);
    gameboard.addSpace("Iota", -62);
    gameboard.addSpace("Kappa", 80);
    gameboard.addSpace("Theta", -22);
    gameboard.addSpace("Lambda", 99);
    
    //set player1 and player2 to Start
    gameboard.reset();
    
    //start game
    do
    {
        if(turnnum %2 == 0)
        {
            player = "two's";
            playerNumber = 2;
        }
        else
        {
            player = "one's";
            playerNumber = 1;
        }
        
        //display current turn, scoreboard, and player board locations
        cout << "Turn #: " << turnnum << endl;
        cout << "Player " << player << " turn." << endl;
        cout << "Score -->["<< score1 << ":" << score2 << "]" << endl;
        cout << "Player1 Space: " << gameboard.getSpaceName(1) << endl;
        cout << "Player2 Space: " << gameboard.getSpaceName(2) << endl;
        cout << "(F)orward, (B)ackward, (P)rint Board, or (Q)uit: ";
        cin >> input;
        cout << "--------------------------------------" << endl;
        
        //User interface menu allows player to move forward, move backward, print, or quit the game
        //if during the turn, the player wants to print first, the player is free to do so without using up their turn.
        switch (toupper(input)) {
            case 'F':
                dice = rand()%3+1; //roll dice for 1,2,3
                gameboard.move('F', playerNumber, dice);
                cout << "You rolled a " << dice << endl;
                cout << "You landed on " << gameboard.getSpaceName(playerNumber) << " for " << gameboard.getSpacePoints(playerNumber) <<  " points." << endl;
                cout << "--------------------------------------" << endl;
                //update score
                    if(playerNumber == 1)
                        score1 = score1 + gameboard.getSpacePoints(1);
                    else if(playerNumber == 2)
                        score2 = score2 + gameboard.getSpacePoints(2);
                turnnum++;
                break;
            case 'B':
                dice = rand()%3+1; //roll dice for 1,2,3
                gameboard.move('B', playerNumber, dice);
                cout << "You rolled a " << dice << endl;
                cout << "You landed on " << gameboard.getSpaceName(playerNumber) << " for " << gameboard.getSpacePoints(playerNumber) << " points." << endl;
                cout << "--------------------------------------" << endl;
                //update score
                    if(playerNumber == 1)
                        score1 = score1 + gameboard.getSpacePoints(1);
                    else if(playerNumber == 2)
                        score2 = score2 + gameboard.getSpacePoints(2);
                 turnnum++;
                break;
            case 'P':
                gameboard.printBoard();
                
                break;
            case 'Q':
                input = 'Q'; //quits game
                break;
        }
        
        //turnnum++;//increment turn counter by 1
        cout << endl << endl;
        
    }while(input !='Q' && (score1 <= 200 && score2 <= 200) && (score1 >= 0 && score2 >= 0));
    //play until either player has scored 200 or higher or 0 or lower or a player has quit.
    
    //end the game and summarize game final score and total number of turns.
    cout << "Game Over!" << endl;
    cout << "Final Score:" << endl;
    cout << "Player One: " << score1 << endl;
    cout << "Player Two: " << score2 << endl;
    cout << "Total Turns: " << turnnum << endl;

    return 0;
}
