#include <QApplication>
#include <QPushButton>
#include "Example.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto l= Example();
    l.start();
    return QApplication::exec();
}
