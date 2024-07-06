#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include <QMediaPlayer>
#include <QBrush>
#include <QImage>
#include <QAudioOutput>

Game::Game(QWidget *parent){

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    setBackgroundBrush(QBrush(QImage(":/images/backback.jpg").scaled(800,600)));


    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);


    player = new Player();
    player->setPos(400,500);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    scene->addItem(player);


    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    scene->addItem(health);


    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);


    QAudioOutput* mu = new QAudioOutput();
    mu ->setVolume(50);
    QMediaPlayer * music = new QMediaPlayer();
    music ->setAudioOutput(mu);
    music->setSource(QUrl("qrc:/077507_hen-40192.mp3"));
   // music->play();


    show();
}

void Game::checkGameOver()
{
    // if (health->getHealth() == 0 ) {

        scene->clear();
        QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over");
        QFont gameOverFont("times", 30);
        gameOverText->setFont(gameOverFont);
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setPos(300, 250);
        scene->addItem(gameOverText);
     // }
}
