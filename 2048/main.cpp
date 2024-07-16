#include <QApplication>
#include <QFont>
#include "widget.h"
#include "start.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont b;

    Widget w;
    w.setFixedSize(QSize(140*w.SIZE, 160*w.SIZE));

    b.setPixelSize(15*w.SIZE);
    a.setFont(b);

    StartWindow startWindow(w);
    startWindow.setFixedSize(QSize(140*w.SIZE, 160*w.SIZE));

    QObject::connect(&w,&Widget::SaveSignal,&w,[&](){
        startWindow.show();
    });

    startWindow.show();

    return a.exec();
}
