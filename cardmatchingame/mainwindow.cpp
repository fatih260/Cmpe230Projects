#include "mainwindow.h"
#include <QMessageBox>
#include <cstdlib> // Include this header for qrand()
#include <QtGlobal>
#include <QTimer>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), score(0), triesRemaining(12), cardTurned(false), firstCard(nullptr), secondCard(nullptr)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gameGrid = new QGridLayout(centralWidget);

    scoreLabel = new QLabel("Score: 0", this);
    triesLabel = new QLabel("No. of Tries Remaining: 12", this);

    QPushButton *newGameButton = new QPushButton("New Game", this);
    connect(newGameButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    gameGrid->addWidget(scoreLabel, 0, 0);
    gameGrid->addWidget(triesLabel, 0, 1);
    gameGrid->addWidget(newGameButton, 0, 2);

    createGameGrid();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createGameGrid()
{
    QStringList colors = { "blue", "yellow", "red", "green","black", "white" };


    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 6; ++col)
        {
             QPushButton *card = new QPushButton("?", this);
            connect(card, &QPushButton::clicked, this, &MainWindow::cardClicked);
             gameGrid->addWidget(card, row + 1, col);
            cards[row][col] = card;

             int colorIndex = rand() % colors.size();

            card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

             QString cardText = colors[colorIndex];
            card->setProperty("cardText", cardText);

        }
    }
}

void MainWindow::resetGame()
{
    score = 0;
    triesRemaining = 12;
    scoreLabel->setText("Score: 0") ;
    triesLabel->setText("No. of Tries Remaining: 12");

    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 6; ++col)
        {
             cards[row][col]->setText("?");
            cards[row][col]->setEnabled(true);


        }}
}

void MainWindow::cardClicked()
{
    QPushButton *clickedCard = qobject_cast<QPushButton*>(sender());
    if (!clickedCard || !clickedCard->isEnabled())
        return;

    clickedCard->setEnabled(false);
    clickedCard->setText(clickedCard->property("cardText").toString());

    if (!cardTurned)
    {
        firstCard = clickedCard;
        cardTurned = true;
    }
    else
    {
        triesRemaining--;
        secondCard = clickedCard;
        checkCards();
        triesLabel->setText("No. of Tries Remaining: " + QString::number(triesRemaining));

    }

}

void MainWindow::checkCards()
{
    if (firstCard->property("cardText") == secondCard->property("cardText"))
    {
        // Cards match
        score++;
        scoreLabel->setText("Score: " + QString::number(score));
        firstCard->setEnabled(false);
        secondCard->setEnabled(false);
        firstCard = nullptr;
        secondCard = nullptr;
        cardTurned = false;
    }
    else
    {
        // Cards do not match
        QTimer::singleShot(500, this, [this]() {
            firstCard->setEnabled(true);
            firstCard->setText("?");
            secondCard->setEnabled(true);
            secondCard->setText("?");
            firstCard = nullptr;
            secondCard = nullptr;
            cardTurned = false;
        });

        if (triesRemaining == 0)
        {
            endGame();
        }
    }
}

void MainWindow::endGame()
{
    QMessageBox::information(this, "Game Over", "No more tries remaining. Game Over!");
    resetGame();
}

