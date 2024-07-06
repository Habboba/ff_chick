#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include <QAudioOutput>


Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    QAudioOutput* mainthemeoutput = new QAudioOutput();
    mainthemeoutput ->setVolume(50);
    bulletsound = new QMediaPlayer();
    bulletsound ->setAudioOutput(mainthemeoutput);
    bulletsound->setSource(QUrl("qrc:/bullet-hit-metal-84818.mp3"));

    setPixmap(QPixmap(":/images/ship.png").scaled(100,100));
}

void Player::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
            setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
            setPos(x()+10,y());
    }

    else if (event->key() == Qt::Key_Space){

        Bullet * bullet = new Bullet();
        bullet->setPos(x()+45,y());
        scene()->addItem(bullet);
        bulletsound ->play();


    }
}

void Player::spawn(){

    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
