#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QResizeEvent> // Include this header for QResizeEvent
#include "widget.h"
#include <QDir>
#include <QFile>
#include <QSpacerItem>
#include <QElapsedTimer>
#include <QApplication>
#include <QPropertyAnimation>

class StartWindow : public QWidget
{
    Q_OBJECT
public:
    Widget &w;
    StartWindow(Widget &tmp);
    void archive_save(Widget &w);

signals:
    void startGameSignal();
    void archiveGameSignal();

public slots:
    void startGame();
    void archiveGame();

protected:
    void resizeEvent(QResizeEvent* event) override; // Declare the resizeEvent method

private:
    QLabel *backgroundLabel;
};

#endif // STARTWINDOW_H
