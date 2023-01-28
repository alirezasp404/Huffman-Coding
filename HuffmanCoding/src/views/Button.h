//
// Created by Alireza on 1/18/2023.
//

#ifndef HUFFMANCODING_BUTTON_H
#define HUFFMANCODING_BUTTON_H

#include <QGraphicsTextItem>



class Button : public QGraphicsTextItem {
Q_OBJECT
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int width;
    int height;
public:
    Button(int width,int height,QString color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void press();
};


#endif //HUFFMANCODING_BUTTON_H
