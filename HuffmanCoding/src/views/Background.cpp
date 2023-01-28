
#include "Background.h"

Background::Background(QString image,QGraphicsItem* parent): image(image),QGraphicsPixmapItem(parent){}
void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter,option,widget);
    if(!initialized){
        auto sceneWidth=scene()->sceneRect().width();
        auto sceneHeight=scene()->sceneRect().height();
        QPixmap pixmap(image);
        setPixmap(pixmap.scaled(sceneWidth,sceneHeight,Qt::KeepAspectRatioByExpanding));
        setPos(0,0);
        initialized= true;
    }

}