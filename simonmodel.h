/*CS3505 Assignment 5
 * Austin Li & Lucas Zagal
 * 3/19
 *
 * Header file for the "Model" part of the game
 *
*/

#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include<QObject>
#include<vector>
#include <QRandomGenerator>

using std::vector;

class SimonModel : public QObject
{

Q_OBJECT

public:
    SimonModel();
    ~SimonModel();

    void updateDifficulty(int newDiff);

signals:
    void flashRed();
    void flashBlue();
    void playersTurn();
    void computerTurn();
    void gameOver();
    void updateProgress(int progress);

public slots:
    void startGame();
    void redPressed();
    void bluePressed();

private:
    enum Color{red, blue};
    int difficulty;
    int userSeqPosition;
    int turnNum;
    vector<Color> sequence;
    void checkUserInput(Color c);
    void prepareNextTurn();
    void playSequence();
    int calculateProgress();
    Color pickColor();
};

#endif // SIMONMODEL_H
