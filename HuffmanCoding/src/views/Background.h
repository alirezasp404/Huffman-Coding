//
// Created by Alireza on 1/18/2023.
//

#ifndef HUFFMANCODING_BACKGROUND_H
#define HUFFMANCODING_BACKGROUND_H


#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Background : public QGraphicsPixmapItem{
private:
    QString image;
public:
    bool initialized{false};
    Background(QString image ,QGraphicsItem *parent=nullptr);
    void  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


#endif //HUFFMANCODING_BACKGROUND_H
