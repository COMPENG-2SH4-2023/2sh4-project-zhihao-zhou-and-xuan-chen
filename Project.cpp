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

    // Initial game objects newnewnew deletedelete delete
    myGameMechs = new GameMechs();
    myFood = new Food();

    myPlayer = new Player(myGameMechs, myFood);  // Pass Game and Food

    myFood->generateFood(myPlayer->getPlayerPos());    //  food


    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();

}

void GetInput(void)
{
    if (myGameMechs -> getInput() == ' ')//kill the games with space
    {
        exitFlag = true;
        myGameMechs -> setExitTrue();
    }
   
}



void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();


    if (myPlayer->checkSelfCollision()==1)     // Check suicide
    {
        myGameMechs->setExitTrue();
        exitFlag = true; //lose game
    }

    int foodType = myPlayer->checkFoodConsumption();    // eat food length score

    switch (foodType) {
        case 0:  // Regular food
            myFood->generateFood(myPlayer->getPlayerPos());
            myGameMechs->incrementScore();
            break;

        case 1:  // Good food
            myFood->generateFood(myPlayer->getPlayerPos());
            for (int i = 0; i < 10; i++) {
                myGameMechs->incrementScore();
            }
            break;

        case 2:  // Bad food
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
                cout << "#";//////
            }
            else
            {
                bool checkPlayerPos = false;                // Check position player food
                bool checkFoodPos = false;
                int k;

                for (k = 0; k < tempPlayerPosList->getSize(); k++)//playrt pos
                {
                    objPos tempPos;
                    tempPlayerPosList->getElement(tempPos, k);
                    if (tempPos.x == j && tempPos.y == i)
                    {
                        checkPlayerPos = true;
                        break;
                    }
                }

                for (k = 0; k < foodPosList->getSize(); k++)    // food pos

                {
                    objPos tempPos;
                    foodPosList->getElement(tempPos, k);
                    if (tempPos.x == j && tempPos.y == i)
                    {
                        checkFoodPos = true;
                        break;
                    }
                }

                if (checkPlayerPos)
                {
                    cout << "*"; //palyer head?
                }
                else if (checkFoodPos)
                {
                    objPos tempPos;
                    foodPosList->getElement(tempPos, k);
                    
                    if (tempPos.symbol == '0')    
                    {
                        cout << "0";  // regular food
                    }
                    else if (tempPos.symbol == 'g')
                    {
                        cout << "g";  // good bonus
                    }
                    else if (tempPos.symbol == 'b')
                    {
                        cout << "b";  // bad bonus
                    }
                }
                else
                {
                    cout << " ";
                }

            }
        }

        cout << endl;   //change line
    }

    // Display info
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


    delete myGameMechs;
    delete myPlayer;
    delete myFood;
}
