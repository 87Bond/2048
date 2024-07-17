#include "widget.h"
#include <vector>
#include <fstream>

int t=0;
//Used to save the blank block position
struct Point
{
    int x;
    int y;
    Point(int a, int b)
    {
        x = a;
        y = b;
    }
};

Widget::Widget()
{
    /*Initialize the interface*/
    SIZE=3;
    Uphead=new QHBoxLayout;
    for(int i=0;i<2;i++)
        Div[i]=new QHBoxLayout;
    for (int i = 0; i < 4; i++)
        Layout[i] = new QHBoxLayout;
    MainLayout = new QVBoxLayout;
    archivebutton = new QPushButton("保存");
    ScoreLabel.setText("0");
    archivebutton->setStyleSheet("QPushButton { background-color: transparent; border: 1px solid black; border-radius: 4px; padding: 4px; }");
    connect(archivebutton, &QPushButton::clicked, this, &Widget::Save);
    QFont b;
    b.setPixelSize(9*SIZE);
    ScoreLabel.setFont(b);
    archivebutton->setFont(b);
    Score = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            block[i][j].setText(" ");
            block[i][j].setFixedSize(QSize(30*SIZE, 30*SIZE));
            block[i][j].setAlignment(Qt::AlignCenter);
            block[i][j].setFont(b);
            num[i][j] = 1;
        }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            Layout[i]->addWidget(&block[i][j]);
    MainLayout->addLayout(Uphead);
    for (int i = 0; i < 4; i++)
        MainLayout->addLayout(Layout[i]);
    for(int i=0;i<2;i++)
        Uphead->addLayout(Div[i]);
    Div[0]->addWidget(&ScoreLabel);
    Div[1]->addWidget(archivebutton);
    this->setLayout(MainLayout);
    /*create two number*/
    create();
    create();
    /*display number*/
    paint();

}

Widget::~Widget() {}

void Widget::create()
{
    int type = GetNumber(1, 10); //2 or 4
    std::vector<Point> PList;

    /*save the blank block position*/
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (num[i][j] == 1)
                PList.push_back(Point(i, j));

    /*Get a random blank block*/
    int randp = GetNumber(0, PList.size());
    Point tempp = PList.at(randp);

    /*set number*/
    if (type != 10) //10% is 4
        num[tempp.x][tempp.y] = 2;
    else
        num[tempp.x][tempp.y] = 4;
}

void Widget::paint()
{
    /*very simple*/
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            if (num[i][j]==1) {
                block[i][j].setText(" ");
                block[i][j].setStyleSheet("background-color:rgb(255,255,255);");
            }
            else
            {
                block[i][j].setText(QString::number(num[i][j]));
                block[i][j].setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(num[i][j]*37%128+128).arg(num[i][j]*17%256).arg(255-num[i][j]*512%37*6));
            }
        }
    ScoreLabel.setText("得分：" + QString::number(Score));
}

void Widget::up()
{
    int move = 0; //whether have been moved

    for (int a = 0; a < 4; a++) {
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++) {
                if (num[i][a] == num[j][a] && num[j][a] != 1) //whether is the same,then add up
                {
                    num[j][a] = 1;
                    move = 1;
                    num[i][a] *= 2;
                    Score += num[i][a];
                    break;
                }
                if (num[j][a] != 1)
                    break;
            }
    }

    for (int a = 0; a < 4; a++) //Make the block near the edge
    {
        for (int i = 0; i < 4; i++)
            if (num[i][a] == 1)
                for (int j = i + 1; j < 4; j++)
                    if (num[j][a] != 1) {
                        num[i][a] = num[j][a];
                        num[j][a] = 1;
                        move = 1;
                        break;
                    }
    }

    if (move == 1) //create a number
        create();
    paint();

    if (check() == 0)
        ScoreLabel.setText("你输啦！得分：" + QString::number(Score));
}

void Widget::down() //the same as up()
{

    int move = 0;
    for (int a = 0; a < 4; a++) {
        for (int i = 3; i > 0; i--)
            for (int j = i - 1; j >= 0; j--) {
                if (num[i][a] == num[j][a] && num[i][a] != 1) {
                    num[j][a] = 1;
                    move = 1;
                    num[i][a] *= 2;
                    Score += num[i][a];
                    break;
                }
                if (num[j][a] != 1)
                    break;
            }
    }

    for (int a = 0; a < 4; a++) {
        for (int i = 3; i > 0; i--)
            if (num[i][a] == 1) {
                for (int j = i - 1; j >= 0; j--)
                    if (num[j][a] != 1) {
                        num[i][a] = num[j][a];
                        num[j][a] = 1;
                        move = 1;
                        break;
                    }
            }
    }
    if (move == 1)
        create();
    paint();
    if (check() == 0)
        ScoreLabel.setText("你输啦！得分：" + QString::number(Score));
}

void Widget::left() //the same as up()
{
    int move = 0;
    for (int a = 0; a < 4; a++) {
        for (int i = 0; i < 4; i++)
            for (int j = i + 1; j < 4; j++) {
                if (num[a][i] == num[a][j] && num[a][j] != 1) {
                    num[a][j] = 1;
                    move = 1;
                    num[a][i] *= 2;
                    Score += num[a][i];
                    break;
                }
                if (num[a][j] != 1)
                    break;
            }
    }

    for (int a = 0; a < 4; a++) {
        for (int i = 0; i < 4; i++)
            if (num[a][i] == 1)
                for (int j = i + 1; j < 4; j++)
                    if (num[a][j] != 1) {
                        num[a][i] = num[a][j];
                        num[a][j] = 1;
                        move = 1;
                        break;
                    }
    }
    if (move == 1)
        create();
    paint();
    if (check() == 0)
        ScoreLabel.setText("你输啦！得分：" + QString::number(Score));
}

void Widget::right() //the same as up()
{
    int move = 0;
    for (int a = 0; a < 4; a++) {
        for (int i = 3; i > 0; i--)
            for (int j = i - 1; j >= 0; j--) {
                if (num[a][i] == num[a][j] && num[a][i] != 1) {
                    num[a][j] = 1;
                    move = 1;
                    num[a][i] *= 2;
                    Score += num[a][i];
                    break;
                }
                if (num[a][j] != 1)
                    break;
            }
    }

    for (int a = 0; a < 4; a++) {
        for (int i = 3; i > 0; i--)
            if (num[a][i] == 1) {
                for (int j = i - 1; j >= 0; j--)
                    if (num[a][j] != 1) {
                        num[a][i] = num[a][j];
                        num[a][j] = 1;
                        move = 1;
                        break;
                    }
            }
    }
    if (move == 1)
        create();
    paint();
    if (check() == 0)
        ScoreLabel.setText("你输啦！得分：" + QString::number(Score));
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    if (Qt::Key_S == key)
        down();
    if (Qt::Key_W == key)
        up();
    if (Qt::Key_A == key)
        left();
    if (Qt::Key_D == key)
        right();
}

int Widget::check()
{
    int temp = 0;
    /*whether have the same block */
    for (int i = 1; i < 3; i++)
        for (int j = 1; j < 3; j++)
            if ((num[i][j] == num[i][j - 1]) || (num[i][j] == num[i][j + 1])
                || (num[i - 1][j] == num[i][j]) || (num[i + 1][j] == num[i][j]) || (num[i][j] == 1))
                temp = 1;

    for (int i = 0; i < 3; i++)
        if (num[0][i] == num[0][i + 1] || num[i][0] == num[i + 1][0])
            temp = 1;

    for (int i = 3; i > 0; i--)
        if (num[3][i] == num[3][i - 1] || num[i][3] == num[i - 1][3])
            temp = 1;

    /*whether have blank block*/
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (num[i][j] == 1)
                temp = 1;

    return temp;
}

void Widget::clear()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            num[i][j]=1;
        }
    }
    Score=0;
}
void Widget::Save()
{
    std::ofstream outfile;
    outfile.open(".\\archive.txt");
    outfile<<this->Score<<"\n";
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
            outfile<<this->num[i][j]<<"\n";
    }

    clear();
    create();
    create();
    paint();

    this->close();
    emit SaveSignal();
}
