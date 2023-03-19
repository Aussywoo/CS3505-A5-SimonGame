/*CS3505 Assignment 5
 * Austin Li & Lucas Zagal
 * 3/19
 *
 * Source file for the "Model" part of the game that implements all the game logic and emits signals to the view
 *
*/

#include "simonmodel.h"
#include <QTimer>
/**
 * @brief SimonModel::SimonModel The constructor fo the SimonModel object
 */
SimonModel::SimonModel() : userSeqPosition(0), turnNum(0)
{
    difficulty = 0;
}

/**
 * @brief SimonModel::~SimonModel The destructor for the SimonModel object
 */
SimonModel::~SimonModel()
{
}

/**
 * @brief SimonModel::startGame When the start button is pressed, all values are reset and the game starts.
 */
void SimonModel::startGame()
{
    userSeqPosition = 0;
    turnNum = 0;
    sequence.clear();
    sequence.push_back(pickColor());
    QTimer::singleShot(1000, this, [&]() {playSequence();});
}

/**
 * @brief SimonModel::playSequence Plays the current sequence
 */
void SimonModel::playSequence()
{

    float diffScale = 1/(1 + (turnNum*0.25 + difficulty*turnNum*0.1));
    // Iterate through sequence
    for(unsigned int i = 0; i < unsigned (sequence.size()); i++) {

        switch(sequence[i])
        {
            case red:
                QTimer::singleShot(i*500*diffScale, this, [&](){emit flashRed();});
            break;

            case blue:
                QTimer::singleShot(i*500*diffScale, this, [&](){emit flashBlue();});
            break;
        }
    }

    // Start player's turn
    QTimer::singleShot(sequence.size()*500*diffScale, this, [&](){emit playersTurn();});
}

/**
 * @brief SimonModel::checkUserInput Checks if the user's current input is the correct one. If not, end the game.
 * @param c
 */
void SimonModel::checkUserInput(Color c)
{
    //If the input is correct, display that in the progress bar
    if(sequence[userSeqPosition] == c)
    {
        userSeqPosition++;
        emit updateProgress(calculateProgress());
    }
    //End game if player is wrong
    else
    {
        emit gameOver();
        return;
    }

    // Once player has matched the full sequence, add new moves
    if(userSeqPosition == int(sequence.size()) )
    {
        prepareNextTurn();
    }
}

/**
 * @brief SimonModel::redPressed Receives the redPressed signal and checks if it's correct
 */
void SimonModel::redPressed()
{
    checkUserInput(red);
}

/**
 * @brief SimonModel::bluePressed Receives the bluePressed signal and checks if it's correct
 */
void SimonModel::bluePressed()
{
    checkUserInput(blue);
}

/**
 * @brief SimonModel::prepareNextTurn Adds new colors to the sequence. The number added is dependent on the difficulty.
 */
void SimonModel::prepareNextTurn()
{
    turnNum++;
    userSeqPosition = 0;
    emit computerTurn();

    // Add one new color to the sequence
    sequence.push_back(pickColor());

    // If the difficulty is 3 or 4, add 1 or 2 more to the sequence
    for(int i = 2; i < difficulty; i++)
    {
        sequence.push_back(pickColor());
    }

    // Play the next sequence
    QTimer::singleShot(1000, this, [&](){playSequence(); emit updateProgress(0);});

}

/**
 * @brief SimonModel::pickColor
 * @return Returns either red or blue, chosen randomly
 */
SimonModel::Color SimonModel::pickColor()
{
        int zeroOrOne = rand() % 2;

        if(zeroOrOne == 0)
            return red;
        else
            return blue;
}

/**
 * @brief SimonModel::updateDifficulty Updates the difficulty
 * @param newDiff The new difficulty level
 */
void SimonModel::updateDifficulty(int newDiff)
{
    this->difficulty = newDiff;
}

/**
 * @brief SimonModel::calculateProgress
 * @return The percentage of the sequence that the player has made it through
 */
int SimonModel::calculateProgress()
{
    if( userSeqPosition == (int) sequence.size())
    {
        return 100;
    }

    float percentageDone = ((float)userSeqPosition/(float)sequence.size()) * 100;
    return percentageDone ;
}



