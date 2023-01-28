#include <QApplication>
#include <QPushButton>
#include "src/windows/Start.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Start start;
    start.show();
    return QApplication::exec();
}