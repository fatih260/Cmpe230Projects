#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void cardClicked();

private:
    void createGameGrid();
    void resetGame();
    void checkCards();
    void endGame();

    QGridLayout *gameGrid;
    QPushButton *cards[6][5];
    QLabel *scoreLabel;
    QLabel *triesLabel;

    int score;
    int triesRemaining;
    bool cardTurned;
    QPushButton *firstCard;
    QPushButton *secondCard;
};

#endif // MAINWINDOW_H
