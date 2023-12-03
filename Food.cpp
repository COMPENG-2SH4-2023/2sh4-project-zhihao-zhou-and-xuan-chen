#include "Food.h"

Food::Food()
{
    foodBucket = new objPosArrayList();
}



Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));
    const int totalFoodCount = 3;
    int generatedCount = 0;
    GameMechs foodGameMechs;
    const int totalBonusFoodCount = 2;
    int bonusFoodCount = 0;

    // Clear existing foodBucket
    while (foodBucket->getSize() > 0)
    {
        objPos removedPos;
        foodBucket->removeHead();
    }

    while (generatedCount < totalFoodCount)
    {
        objPos randPos;
        char symbol = '0'; // Default to regular food symbol '0'

        randPos.setObjPos((rand() % (foodGameMechs.getBoardSizeX() - 2)) + 1,
                          (rand() % (foodGameMechs.getBoardSizeY() - 2)) + 1, symbol);

        // Check if randPos is in blockOff
        bool positionOccupied = false;

        for (int i = 0; i < blockOff->getSize(); i++)
        {
            objPos blockPos;
            blockOff->getElement(blockPos, i);

            if (randPos.x == blockPos.x && randPos.y == blockPos.y)
            {
                positionOccupied = true;
                break;
            }
        }

        if (!positionOccupied)
        {
            foodBucket->insertHead(randPos);
            generatedCount++;
        }
    }

    while (bonusFoodCount < totalBonusFoodCount)
    {
        objPos randPos;
        char symbol;

        // Randomly decide if it's a good bonus or bad bonus
        bool isGoodBonus = rand() % 2 == 0;

        if (isGoodBonus)
        {
            symbol = 'g'; // Good bonus symbol 'g'
        }
        else
        {
            symbol = 'b'; // Bad bonus symbol 'b'
        }

        randPos.setObjPos((rand() % (foodGameMechs.getBoardSizeX() - 2)) + 1,
                          (rand() % (foodGameMechs.getBoardSizeY() - 2)) + 1, symbol);

        // Check if randPos is in blockOff
        bool positionOccupied = false;

        for (int i = 0; i < blockOff->getSize(); i++)
        {
            objPos blockPos;
            blockOff->getElement(blockPos, i);

            if (randPos.x == blockPos.x && randPos.y == blockPos.y)
            {
                positionOccupied = true;
                break;
            }
        }

        if (!positionOccupied)
        {
            foodBucket->insertHead(randPos);
            bonusFoodCount++;
        }
    }
}









objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}
