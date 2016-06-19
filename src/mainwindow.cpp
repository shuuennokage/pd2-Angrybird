#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bird.h"
#include "pig.h"
#include "wood.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    back = new QGraphicsPixmapItem(QPixmap(":/image/back.png"));
    back->setPos(0,11);
    scene->addItem(back);
    dangon = new QGraphicsPixmapItem(QPixmap(":/image/dangone.png"));
    dangon->setPos(150,250);
    scene->addItem(dangon);
    restartB = new QPushButton;
    restartB->setIcon(QPixmap(":/image/re.png"));
    restartB->setGeometry(30,30,40,40);
    end = new QPushButton;
    end->setIcon(QPixmap(":/image/end.png"));
    end->setGeometry(60,60,60,40);
    scene->addWidget(end);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,1,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));

    // Create bird (You can edit here)
    birdie = new Bird(6.5f,9.0f,0.9f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdie->g_body->SetGravityScale(0);
    white = new Bird(1.0f,2.0f,0.9f,&timer,QPixmap(":/image/fast_bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    white->g_body->SetGravityScale(0);
    fast = new Bird(3.0f,2.0f,0.9f,&timer,QPixmap(":/image/egg_bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    many = new Bird(4.0f,2.0f,0.7f,&timer,QPixmap(":/image/many_bird.png").scaled(height()/12.0,height()/12.0),world,scene);
    teki = new Pig(20.0f,2.0f,0.9f,&timer,QPixmap(":/image/enemy_cry.png").scaled(height()/9.0,height()/9.0),world,scene);
    wood1 = new Wood(17.0f,3.6f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood2 = new Wood(23.0f,3.6f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood3 = new Wood(20.0f,5.6f,6.8f,1.0f,&timer,QPixmap(":/image/wood_ho.jpg").scaled(width()/4.5,height()/18.0),world,scene);
    wood4 = new Wood(18.0f,8.8f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood5 = new Wood(22.0f,8.8f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood6 = new Wood(20.0f,10.2f,5.2f,1.0f,&timer,QPixmap(":/image/wood_ho.jpg").scaled(width()/6.0,height()/18.0),world,scene);
    // Setting the Velocity
    birdie->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(birdie);
    itemList.push_back(white);
    itemList.push_back(fast);
    itemList.push_back(wood1);
    itemList.push_back(wood2);
    itemList.push_back(wood3);
    itemList.push_back(wood4);
    itemList.push_back(wood5);
    itemList.push_back(wood6);
    itemList.push_back(many);
    //white->setLinearVelocity(b2Vec2(5,5));
    //itemList.push_back(white);
    teki->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(teki);
    x2 = teki->g_body->GetPosition().x;
    // Timer
    connect(restartB,SIGNAL(clicked(bool)),this,SLOT(restart()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(press==0){
            std::cout << "Press !" << std::endl ;
            press = 1;
            unpress = 0;
            if(click==0 && bird==0){
                birdie->g_body->SetGravityScale(1);
                click = 1;
                release = 0;
            }
            if(click==2){
                if(bird==1 && fly==2){
                    x = white->g_body->GetLinearVelocity().x;
                    y = white->g_body->GetLinearVelocity().y;
                    white->g_body->SetLinearVelocity(b2Vec2(2*x,2*y));
                    bird++;
                    unpress = 1;
                    press = -1;
                }
            }else if(click==4){
                if(bird==2 && fly==3){
                    x = fast->g_body->GetLinearVelocity().x;
                    y = fast->g_body->GetLinearVelocity().y;
                    fast->g_body->SetLinearVelocity(b2Vec2(0,10*y));
                    bird++;
                    unpress = 1;
                    press = -1;
                }
            }else if(click==6){
                if(bird==3 && fly==4){
                    many->g_body->SetGravityScale(0);
                    many->setLinearVelocity(b2Vec2(0,0));
                    unpress = 1;
                    press = -1;
                    if(g==0){
                        many->g_body->SetGravityScale(1);
                        many->setLinearVelocity(b2Vec2(bx,(540-by)/30));
                        bird++;
                    }
                    g = 0;
                }
            }else{

            }
            if(click==0 && bird==1){
                white->g_body->SetGravityScale(1);
                click = 1;
                release = 0;
                fly = 0;
            }
            if(click==2 && bird==2){
                fast->g_body->SetGravityScale(1);
                click = 1;
                release = 0;
                fly = 0;
            }
            if(click==4 && bird==3){
                many->g_body->SetGravityScale(1);
                click = 1;
                release = 0;
                fly = 0;
            }
        }
        count++;
        if(count==5){
            press = 0;
            count = 0;
        }
        std::cout << press << std::endl ;
        /* TODO : add your code here */
        //std::cout << "Press !" << std::endl ;
    }
    if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *m = static_cast<QMouseEvent*>(event);
        bx = m->x();
        by = m->y();

        if(click==1 && release==0){
            if(bird==0){
                birdie->g_body->SetTransform(b2Vec2((400+bx)/150,(540-by)/30), 0);
            }
        }
        if(click==1 && release==0){
            if(bird==1){
                white->g_body->SetTransform(b2Vec2((400+bx)/150,(540-by)/30), 0);
            }
        }
        if(click==1 && release==0){
            if(bird==2){
                fast->g_body->SetTransform(b2Vec2((400+bx)/150,(540-by)/30), 0);
            }
        }
        if(click==1 && release==0){
            if(bird==3){
                many->g_body->SetTransform(b2Vec2((400+bx)/150,(540-by)/30), 0);
            }
        }
        /* TODO : add your code here */
        //std::cout << "Move !" << std::endl ;
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(unpress==0){
            std::cout << "Release !" << std::endl ;
            unpress = 1;
            press = 0;
            if(release==0 && bird==0){
                release = 1;
                click = 0;
                fly = 1;
                birdie->setLinearVelocity(b2Vec2((bx-190)/-10,(by-250)/10));
                bird++;
            }
            if(release==0 && bird==1){
                release = 1;
                click = 2;
                fly = 2;
                white->setLinearVelocity(b2Vec2((bx-190)/-10,(by-250)/10));
            }
            if(release==0 && bird==2){
                release = 1;
                click = 4;
                fly = 3;
                fast->setLinearVelocity(b2Vec2((bx-190)/-10,(by-250)/10));
            }
            if(release==0 && bird==3){
                release = 1;
                click = 6;
                fly = 4;
                many->setLinearVelocity(b2Vec2((bx-190)/-10,(by-250)/10));
            }
        }
        /* TODO : add your code here */
        //std::cout << "Release !" << std::endl ;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
    if(bird>3){
        endGame();
    }
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::restart()
{
    deleteIt();

    itemList.push_back(new Land(16,1.5,32,1,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene));
    // Create bird (You can edit here)
    birdie = new Bird(6.5f,9.0f,0.9f,&timer,QPixmap(":/bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    birdie->g_body->SetGravityScale(0);
    white = new Bird(1.0f,2.0f,0.9f,&timer,QPixmap(":/image/fast_bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    white->g_body->SetGravityScale(0);
    fast = new Bird(3.0f,2.0f,0.9f,&timer,QPixmap(":/image/egg_bird.png").scaled(height()/9.0,height()/9.0),world,scene);
    many = new Bird(4.0f,2.0f,0.7f,&timer,QPixmap(":/image/many_bird.png").scaled(height()/12.0,height()/12.0),world,scene);
    teki = new Pig(20.0f,2.0f,0.9f,&timer,QPixmap(":/image/enemy_cry.png").scaled(height()/9.0,height()/9.0),world,scene);
    wood1 = new Wood(17.0f,3.6f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood2 = new Wood(23.0f,3.6f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood3 = new Wood(20.0f,5.6f,6.8f,1.0f,&timer,QPixmap(":/image/wood_ho.jpg").scaled(width()/4.5,height()/18.0),world,scene);
    wood4 = new Wood(18.0f,8.8f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood5 = new Wood(22.0f,8.8f,1.0f,3.5f,&timer,QPixmap(":/image/wood_st.jpg").scaled(width()/27.0,height()/5.0),world,scene);
    wood6 = new Wood(20.0f,10.2f,5.2f,1.0f,&timer,QPixmap(":/image/wood_ho.jpg").scaled(width()/6.0,height()/18.0),world,scene);
    // Setting the Velocity
    birdie->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(birdie);
    itemList.push_back(white);
    itemList.push_back(fast);
    itemList.push_back(wood1);
    itemList.push_back(wood2);
    itemList.push_back(wood3);
    itemList.push_back(wood4);
    itemList.push_back(wood5);
    itemList.push_back(wood6);
    itemList.push_back(many);
    teki->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(teki);
    scene->removeItem(final);
    timer.start(100/6);
    press = 0;
    unpress = 0;
    click = 0;
    release = 0;
    fly = 0;
    bird = 0;
    g = 0;
    count = 0;
}

void MainWindow::deleteIt()
{
    timer.stop();
    for(int i=0; i<itemList.size();i++){
        delete itemList.at(i);
    }
    itemList.clear();
}

void MainWindow::endGame()
{
    x3 = teki->g_body->GetPosition().x;
    if(x3==x2){
        final = new QGraphicsPixmapItem(QPixmap(":/image/over.png").scaled(200,150));
        final->setPos(150,250);
        scene->addItem(final);
    }else{
        final = new QGraphicsPixmapItem(QPixmap(":/image/win.jpg").scaled(200,150));
        final->setPos(150,250);
        scene->addItem(final);
    }
    timer.stop();
}
