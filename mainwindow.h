/*CS3505 Assignment 5
 * Austin Li & Lucas Zagal
 * 3/19
 *
 * Header file for the "View" part of the game
 *
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "simonmodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, SimonModel* m = nullptr);
    ~MainWindow();

private slots:
    void redFlash();
    void blueFlash();
    void enableButtons();
    void disableButtons();
    void startGame();
    void gameOver();
    void updateProgress(int progress);

private:
    Ui::MainWindow *ui;
    void updateDifficulty(int newDiff);


};
#endif // MAINWINDOW_H
