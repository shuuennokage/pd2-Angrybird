#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QLabel>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <pig.h>
#include <wood.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void restart();
    void deleteIt();
    void endGame();
private:
    float x;
    float x2;
    float x3;
    float y;
    QPushButton *restartB;
    QPushButton *end;
    int count = 0;
    int g;
    int press = 0;
    int unpress = 0;
    int bird = 0;
    int click = 0;
    int release = 0;
    int fly = 0;
    float bx;
    float by;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    Bird *birdie;
    Bird *white;
    Bird *fast;
    Bird *many;
    Pig *teki;
    Wood *wood1;
    Wood *wood2;
    Wood *wood3;
    Wood *wood4;
    Wood *wood5;
    Wood *wood6;
    QGraphicsPixmapItem *back;
    QGraphicsPixmapItem *dangon;
    QGraphicsPixmapItem *final;

};

#endif // MAINWINDOW_H
