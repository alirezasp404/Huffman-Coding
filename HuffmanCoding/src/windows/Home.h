
#ifndef HUFFMANCODING_HOME_H
#define HUFFMANCODING_HOME_H


#include <QGraphicsView>
#include "../views/Background.h"
#include "../views/Button.h"
#include "../views/Label.h"
#include "../views/Huffman.h"
#include <QFileDialog>

class Home : public QGraphicsView {

private:
    QGraphicsScene *scene;
    Background *background;
    Button *browseButton;
    Button *convertButton;
    Button *exitButton;
    Label *resultLabel;
    Label *inAddressLabel;
    Label *outAddressLabel;
    QString inputFilePath;
    QString outputFilePath;
    QString fileType;
    long long inputFileSize;
    long long outputFileSize;

public:
    Home();

    ~Home();

public slots:

    void browse();


    void convertFile();

    void exitSlot();

    QString checkFile();
    void displayResult(QString text);
    void displayPercent();
};


#endif //HUFFMANCODING_HOME_H
