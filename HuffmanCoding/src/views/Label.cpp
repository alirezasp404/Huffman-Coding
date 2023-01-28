

#include "Label.h"
#include <QFont>
#include <QTextDocument>

Label::Label(int size,QString color): QGraphicsTextItem() {
    setDefaultTextColor(QColor(color));
    QFont font;
    font.setPixelSize(size);
    font.setBold(true);
    font.setItalic(true);
    setFont(font);
    document()->setDocumentMargin(10);
}