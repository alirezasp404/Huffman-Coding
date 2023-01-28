#include "Button.h"
#include <QFont>
#include <QTextDocument>
#include <QPainter>
Button:: Button(int width,int height,QString color):width(width),height(height), QGraphicsTextItem(){
    setDefaultTextColor(QColor(color));
    QFont font;
    font.setPixelSize(30);
    font.setBold(true);
    setFont(font);
    setTextWidth(width);
    document()->setDocumentMargin(10);
}
void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPixmap pixmap(":images/buttonBG");
    pixmap=pixmap.scaled(width,height);
    painter->setBrush(pixmap);
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter, option, widget);

}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsTextItem::mousePressEvent(event);
    emit press();
}