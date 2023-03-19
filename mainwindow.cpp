#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTimer>
#include "simonmodel.h"

MainWindow::MainWindow(QWidget *parent, SimonModel* m)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the signals from the model to the interface
    connect(m, &SimonModel::flashRed, this, &MainWindow::redFlash);
    connect(m, &SimonModel::flashBlue, this, &MainWindow::blueFlash);
    connect(m, &SimonModel::playersTurn, this, &MainWindow::enableButtons);
    connect(m, &SimonModel::computerTurn, this, &MainWindow::disableButtons);
    connect(m, &SimonModel::gameOver, this, &MainWindow::gameOver);
    connect(m, &SimonModel::updateProgress, this, &MainWindow::updateProgress);

    this->disableButtons();

    // Set initial properties
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(50,50,200);} QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->gameOverMsg->setVisible(false);
    ui->diffLabel->setText(QString::fromStdString("Difficulty: 0"));
    ui->progressBar->setValue(0);
    ui->progressBar->setStyleSheet(QString("QProgressBar:chunk {background-color: rgb(100,50,200);} QProgressBar {text-align: center;}"));

    // Connect ui signals to model slots
    connect(ui->difficultySlider, &QSlider::sliderMoved, m, [&](){m->updateDifficulty(ui->difficultySlider->sliderPosition());});
    connect(ui->difficultySlider, &QSlider::sliderMoved, this, [&](){this->updateDifficulty(ui->difficultySlider->sliderPosition());});
    connect(ui->redButton, &QPushButton::released, m, &SimonModel::redPressed);
    connect(ui->blueButton, &QPushButton::released, m, &SimonModel::bluePressed);
    connect(ui->startButton, &QPushButton::released, m, &SimonModel::startGame);
    connect(ui->startButton, &QPushButton::released, this, &MainWindow::startGame);
}

/**
 * @brief MainWindow::~MainWindow Destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::startGame Sets up the ui to start a new game
 */
void MainWindow::startGame()
{
    ui->gameOverMsg->setVisible(false);
    ui->startButton->setEnabled(false);
    ui->progressBar->setValue(0);
}

/**
 * @brief MainWindow::gameOver Disables the colored buttons and displays a game over message.
 */
void MainWindow::gameOver()
{
    ui->gameOverMsg->setVisible(true);
    disableButtons();
    ui->startButton->setEnabled(true);
    //label
}

/**
 * @brief MainWindow::redFlash Briefly flashes the red button
 */
void MainWindow::redFlash()
{
    QTimer::singleShot(0, this, [&](){ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(255,150,150);}" ));} );
    QTimer::singleShot(100, this, [&](){ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,50,50);} QPushButton:pressed {background-color: rgb(255,150,150);}"));} );
}

/**
 * @brief MainWindow::blueFlash Briefly flashes the blue button
 */
void MainWindow::blueFlash()
{
    QTimer::singleShot(0, this, [&](){ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(150,150,255);}" ));} );
    QTimer::singleShot(100, this, [&](){ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(50,50,200);} QPushButton:pressed {background-color: rgb(150,150,255);}"));} );
}

/**
 * @brief MainWindow::enableButtons Enables the colored buttons
 */
void MainWindow::enableButtons()
{
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

/**
 * @brief MainWindow::disableButtons Disables the colored buttons
 */
void MainWindow::disableButtons()
{
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

/**
 * @brief MainWindow::updateDifficulty Sends the position of the difficultySlider to the model when it changes
 *
 * @param newDiff The new difficulty
 */
void MainWindow::updateDifficulty(int newDiff)
{
    ui->diffLabel->setText(QString::fromStdString("Difficulty: " + std::to_string(newDiff)));
}

/**
 * @brief MainWindow::updateProgress
 * @param progress Displays the inputted progress value
 */
void MainWindow::updateProgress(int progress)
{
    ui->progressBar->setValue(progress);
}

