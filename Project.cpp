#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"//
#include "Player.h" //
#include "Food.h" //    



using namespace std;

#define DELAY_CONST 200000

bool exitFlag;
bool loseFlag;

GameMechs *myGameMechs;
Player *myPlayer;
Food *myFood;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;
    loseFlag = false;
    // Initialize game objects
    myGameMechs = new GameMechs();
    myFood = new Food();

    myPlayer = new Player(myGameMechs, myFood);  // Pass both GameMechs and Food

    // Generate initial food
    myFood->generateFood(myPlayer->getPlayerPos());

    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();

}

void GetInput(void)
{
    if (myGameMechs -> getInput() == ' ')
    {
        exitFlag = true;
        myGameMechs -> setExitTrue();
    }
   
}



void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Check for self-collision
    if (myPlayer->checkSelfCollision()==1) {
        myGameMechs->setExitTrue();
        exitFlag = true;
        // Additional actions to end the game can be added here
    }

    // Check for food consumption and update score/length
    int foodType = myPlayer->checkFoodConsumption();
    switch (foodType) {
        case 0:  // Regular food
            myFood->generateFood(myPlayer->getPlayerPos());
            myGameMechs->incrementScore();
            break;

        case 1:  // Good bonus
            myFood->generateFood(myPlayer->getPlayerPos());
            for (int i = 0; i < 10; i++) {
                myGameMechs->incrementScore();
            }
            break;

        case 2:  // Bad bonus
            myFood->generateFood(myPlayer->getPlayerPos());
            for (int j = 0; j < 5; j++) {
                myPlayer->increasePlayerLength();
            }
            break;

        default:
            break;
    }
}




void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPosArrayList* tempPlayerPosList = myPlayer->getPlayerPos();
    objPosArrayList* foodPosList = myFood->getFoodPos();

    for (int i = 0; i < myGameMechs->getBoardSizeY(); i++)
    {
        for (int j = 0; j < myGameMechs->getBoardSizeX(); j++)
        {
            if (i == 0 || i == myGameMechs->getBoardSizeY() - 1 || j == 0 || j == myGameMechs->getBoardSizeX() - 1)
            {
                cout << "#";
            }
            else
            {
                // Check if the current position corresponds to the player, food, or empty space
                bool checkPlayerPos = false;
                bool checkFoodPos = false;
                int k; // Declare k here

                // Check player position
                for (k = 0; k < tempPlayerPosList->getSize(); k++)
                {
                    objPos tempPos;
                    tempPlayerPosList->getElement(tempPos, k);
                    if (tempPos.x == j && tempPos.y == i)
                    {
                        checkPlayerPos = true;
                        break;
                    }
                }

                // Check food positions
                for (k = 0; k < foodPosList->getSize(); k++)
                {
                    objPos tempPos;
                    foodPosList->getElement(tempPos, k);
                    if (tempPos.x == j && tempPos.y == i)
                    {
                        checkFoodPos = true;
                        break;
                    }
                }

                // Draw player ('*') or food ('0') or empty space (' ')
                if (checkPlayerPos)
                {
                    cout << "*";
                }
                else if (checkFoodPos)
                {
                    objPos tempPos;
                    foodPosList->getElement(tempPos, k);
                    
                    // Check the symbol of the food
                    if (tempPos.symbol == '0')
                    {
                        cout << "0";  // Regular food
                    }
                    else if (tempPos.symbol == 'g')
                    {
                        cout << "g";  // Good bonus
                    }
                    else if (tempPos.symbol == 'b')
                    {
                        cout << "b";  // Bad bonus
                    }
                }
                else
                {
                    cout << " ";
                }

            }
        }

        // Move to the next line after each row
        cout << endl;
    }

    // Display score
    cout << "Score: " << myGameMechs->getScore() << endl;
    cout << "============================================" << endl;
    cout << "'b' for punishment increase length\n'g' for bonus increase score\n'0' for normal"<<endl;
    cout << "Gameboard Size: " << myGameMechs->getBoardSizeX() << ", " << myGameMechs->getBoardSizeY() << endl;
    cout << "Player's length: " << tempPlayerPosList->getSize() << endl;

}






void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 
    objPosArrayList* tempPlayerPosList = myPlayer->getPlayerPos();

    if(myGameMechs -> getExitFlagStatus())
    {
        MacUILib_printf("Final Score:%d\n",myGameMechs -> getScore());
        MacUILib_printf("Game Over!\n");

        cout << "Player's length: " << tempPlayerPosList->getSize() << endl;
        MacUILib_uninit();
    }

    // if(myGameMechs -> getLoseFlagStatus())
    // {
    //     MacUILib_printf("Final Score:%d\n",myGameMechs -> getScore());
    //     MacUILib_printf("Game Over! You lose\n");
    //     MacUILib_uninit();
    // }

    // else
    // {
    //     MacUILib_uninit();
    // }
    delete myGameMechs;
    delete myPlayer;
    delete myFood;
}
