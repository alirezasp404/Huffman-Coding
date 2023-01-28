

#ifndef HUFFMANCODING_START_H
#define HUFFMANCODING_START_H



#include "QGraphicsView"
#include "../views/Label.h"
#include "../views/Button.h"
#include "../views/Background.h"
#include "Home.h"


class Start : public QGraphicsView {

private:
    QGraphicsScene *scene;
    Background* background;
    Button *button;
    Label* firstLabel;
public:
    Start();
    ~Start();
public slots:
    void showHome();
};


#endif //HUFFMANCODING_START_H
