#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"
#include <QAudioOutput>
#include <QMessageBox>

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    int random_number = rand() % 700;
    setPos(random_number,0);


    setPixmap(QPixmap(":/images/evil.png").scaled(100,100));



    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));


    timer->start(50);
    QAudioOutput* mu = new QAudioOutput();
    mu ->setVolume(50);
    music = new QMediaPlayer();
    music ->setAudioOutput(mu);
    music->setSource(QUrl("qrc:/077507_hen-40192.mp3"));

    QAudioOutput* death = new QAudioOutput();
    death ->setVolume(50);
    music2 = new QMediaPlayer();
    music2 ->setAudioOutput(mu);
    music2->setSource(QUrl("qrc:/death-sound-1-165630.mp3"));



}

void Enemy::move() {
    setPos(x(), y() + 5);

    if (pos().y() > 600) {
        scene()->removeItem(this);
        delete this;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Player) && game->health->getHealth() > 0) {
            game->health->decrease();
            scene()->removeItem(this);
            delete this;
            music2->play();


            return;
        }
    }

    if (game->health->getHealth() <= 0) {
        game->scene->clear();
        music2->play();
        QMessageBox::critical(nullptr, "GAME OVER !","Your score is "+ QString::number(game->score->getScore()));
        game->checkGameOver();
        QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over");
        QFont gameOverFont("times", 30);
        gameOverText->setFont(gameOverFont);
        gameOverText->setDefaultTextColor(Qt::white);
        gameOverText->setPos(300, 250);
        game->scene->addItem(gameOverText);

    }
}

