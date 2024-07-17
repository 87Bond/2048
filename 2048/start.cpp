#include "start.h"
#include <fstream>
#include<QIcon>
#include<sstream>
StartWindow::StartWindow(Widget &tmpll):w(tmpll)
{
    int SIZE = 3;
    QVBoxLayout *mainlayout = new QVBoxLayout;
    QHBoxLayout *layout[6] = {new QHBoxLayout(), new QHBoxLayout(), new QHBoxLayout(), new QHBoxLayout(),new QHBoxLayout(), new QHBoxLayout()};
    QPushButton *startButton = new QPushButton("新游戏");
    QPushButton *archiveButton=new QPushButton("历史游戏");
    QLabel *tmp = new QLabel("2048");
    QLabel *tmp1 = new QLabel("Made by 郑仕博 and 董子扬");

    QFont b;
    b.setPixelSize(50); // 设置较大的字体大小
    tmp->setFont(b);

    b.setPixelSize(15); // 设置较小的字体大小
    tmp1->setFont(b);

    tmp->setAlignment(Qt::AlignCenter);
    tmp1->setAlignment(Qt::AlignCenter);

    // 设置标签的背景透明
    tmp->setStyleSheet("QLabel { background-color: transparent; }");
    tmp1->setStyleSheet("QLabel { background-color: transparent; }");

    // 设置按钮样式，包括背景透明和边框
    startButton->setStyleSheet("QPushButton { background-color: transparent; border: 2px solid white; border-radius: 10px; padding: 10px; }");
    archiveButton->setStyleSheet("QPushButton { background-color: transparent; border: 2px solid white; border-radius: 10px; padding: 10px; }");
    layout[0]->addItem(new QSpacerItem(1, 120)); // 增加占位符的高度，使2048移动到月亮下面
    layout[1]->addWidget(tmp);
    layout[2]->addItem(new QSpacerItem(1, 100)); // 调整占位符的高度
    layout[3]->addWidget(startButton);
    layout[4]->addWidget(archiveButton);
    layout[5]->addWidget(tmp1);

    layout[0]->setAlignment(Qt::AlignCenter);
    layout[1]->setAlignment(Qt::AlignCenter);
    layout[2]->setAlignment(Qt::AlignCenter);
    layout[3]->setAlignment(Qt::AlignCenter);
    layout[4]->setAlignment(Qt::AlignCenter);
    layout[5]->setAlignment(Qt::AlignCenter);

    mainlayout->addLayout(layout[0]);
    mainlayout->addLayout(layout[1]);
    mainlayout->addLayout(layout[2]);
    mainlayout->addLayout(layout[3]);
    mainlayout->addLayout(layout[4]);
    mainlayout->addLayout(layout[5]);
    connect(startButton, &QPushButton::clicked, this, &StartWindow::startGame);
    connect(archiveButton, &QPushButton::clicked, this, &StartWindow::archiveGame);

    // 设置背景图片
    backgroundLabel = new QLabel(this);
    QString currentPath = QDir::currentPath();
    QString resDir = currentPath;
    QString imagePath = QString("%1/EE441E53AC2667B0E22AB1BBF0B24F01.png").arg(resDir);

    // 检查图片是否存在

    QPixmap background(imagePath);
    backgroundLabel->setPixmap(background);
    backgroundLabel->setScaledContents(true); // 使图片自动缩放
    backgroundLabel->setGeometry(this->rect()); // 设置背景标签的大小为整个窗口
    backgroundLabel->lower(); // 将背景标签置于最底层


    // 设置布局
    setLayout(mainlayout);
}

void StartWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    backgroundLabel->setGeometry(this->rect());
}

void StartWindow::startGame()
{
    this->close();
    w.show();
}

void StartWindow::archiveGame()
{
    this->archive_save(w);
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
