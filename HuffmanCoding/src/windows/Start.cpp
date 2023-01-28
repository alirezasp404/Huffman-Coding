

#include <QPushButton>
#include "Start.h"

Start::Start() {
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width(), height());
    setScene(scene);
    background=new Background(":/images/startBG");
    scene->addItem(background);

    firstLabel = new Label(50, "white");
    firstLabel->setPlainText("FILE COMPRESSION\n\t\tusing\t\nHUFFMAN CODING");
    firstLabel->setPos(width() / 3, height() /8);
    scene->addItem(firstLabel);

    button = new Button(470, 150, "white");
    button->setPlainText("\t    Start Conversion");
    button->setPos(width() / 3, height() / 1.5);
    connect(button, &Button::press, this, &Start::showHome);
    scene->addItem(button);

}
Start::~Start() {
    delete background;
    delete firstLabel;
    delete button;
    delete scene;
}

void Start::showHome() {
    (new Home())->show();
    close();
}

