#ifndef _WIGET_H
#define _WIGET_H

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <stdlib.h>
#include <QWidget>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QResizeEvent>

class Widget : public QWidget
{
     Q_OBJECT
public:

    int SIZE;
    QLabel block[4][4]; //Used to display number
    int num[4][4];      //Used to save number
    QHBoxLayout *Layout[4];  //Qt's things
    QHBoxLayout *Uphead;
    QVBoxLayout *MainLayout; //Qt's things
    QHBoxLayout *Div[2];
    QPushButton *archivebutton ;
    QLabel ScoreLabel; //Used to display score
    int Score;         //Used to save score

signals:
    void SaveSignal();

public slots:
    void Save();

public:
    Widget();
    ~Widget();

    void clear();
    int GetNumber(int a, int b)
    {
        srand(time(0));
        int num = 0;
        num = a + rand() % b;
        return num;
    }


    void create(); //create a number(2 or 4)
    void up(); //when move up
    void down();
    void left();
    void right();
    int check(); //check whether the game is over

    void paint(); //display num[][]

protected:
    void keyPressEvent(QKeyEvent *e); //keyboard interface
};
#endif
