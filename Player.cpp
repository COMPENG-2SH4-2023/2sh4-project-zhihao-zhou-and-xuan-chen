#include "Player.h"
#include "Food.h"
#include <iostream>

Player::Player(GameMechs* thisGMRef, Food* thisFood) : exitFlag(false)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    food = thisFood;
    playerPosList = new objPosArrayList();

    
    objPos playerPos;
    playerPos.x = thisGMRef->getBoardSizeX() / 2;
    playerPos.y = thisGMRef->getBoardSizeY() / 2;// Initialize * position
    playerPos.symbol = '*';
    
    playerPosList->insertHead(playerPos);// Add the initial position to the player's position list
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   
    char input = mainGameMechsRef->getInput();

    switch (input)
    {
    case 'w':
        if (myDir != DOWN)
        {
            myDir = UP;
        }
        break;

    case 'a':
        if (myDir != RIGHT)
        {
            myDir = LEFT;
        }
        break;

    case 's':
        if (myDir != UP)
        {
            myDir = DOWN;
        }
        break;

    case 'd':
        if (myDir != LEFT)
        {
            myDir = RIGHT;
        }
        break;

    case ' ':
        exitFlag = mainGameMechsRef->getExitFlagStatus();
        break;

    case 'q': 
        myDir = STOP;
    }



    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    int newX = headPos.x;
    int newY = headPos.y;

    switch (myDir)
    {
    case UP:
        newY = (newY - 1 + mainGameMechsRef->getBoardSizeY()) % mainGameMechsRef->getBoardSizeY();
        break;
    case DOWN:
        newY = (newY + 1) % mainGameMechsRef->getBoardSizeY();
        break;
    case LEFT:
        newX = (newX - 1 + mainGameMechsRef->getBoardSizeX()) % mainGameMechsRef->getBoardSizeX();
        break;
    case RIGHT:
        newX = (newX + 1) % mainGameMechsRef->getBoardSizeX();
        break;
    default:
        break;
    }

    objPos newPos;
    newPos.x = newX;    // Aplayer position
    newPos.y = newY;

    if (newX == 0) 
    {
        newPos.x = mainGameMechsRef->getBoardSizeX() - 2;
    } 
    else if (newX == mainGameMechsRef->getBoardSizeX() - 1)     // go opposite side when edge

    {
        newPos.x = 1;
    }

    if (newY == 0) 
    {
        newPos.y = mainGameMechsRef->getBoardSizeY() - 2;
    } 
    else if (newY == mainGameMechsRef->getBoardSizeY() - 1) 
    {
        newPos.y = 1;
    }
    playerPosList->removeTail();
    playerPosList->insertHead(newPos);
}



int Player::checkFoodConsumption()
{
    // find head
    objPos headPos;
    objPos foodPos;
    playerPosList->getHeadElement(headPos);

    // find all food positions
    objPosArrayList* foodPosList = food->getFoodPos();

    // Iterate over all food positions
    for (int i = 0; i < foodPosList->getSize(); ++i) 
    {

        foodPosList->getElement(foodPos, i);

        // pos = pos?
        if (headPos.x == foodPos.x && headPos.y == foodPos.y) 
        {
            // Consume the food
            playerPosList->insertHead(foodPos);

            // Generate new food
            //food->generateFood(playerPosList);

            // Return the type of consumed food
            return (foodPos.symbol == '0') ? 0 : ((foodPos.symbol == 'g') ? 1 : 2);
        }
    }

    return -1; // No food consumed
}




void Player::increasePlayerLength()
{
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    playerPosList->insertTail(playerPos);
}





int Player::checkSelfCollision() 
{
    objPosArrayList* playerPosList = getPlayerPos();

    // if (playerPosList->getSize() < 4) {
    //     // no collision length < 4
    //     return false;
    // }

    objPos headPos;
    getPlayerPos()->getHeadElement(headPos);

    for (int i = 1; i < playerPosList->getSize(); i++)     //check collision

    {
        objPos bodyPos;
        playerPosList->getElement(bodyPos, i);

        if (headPos.x == bodyPos.x && headPos.y == bodyPos.y) //head vs each body
        {
            // Collision detected
            return 1;
        }
    }

    return 0;// No collision
}



