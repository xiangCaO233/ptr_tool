#include <QApplication>
#include <QPushButton>
#include "Example.h"
#include "macos/GlobalScreen.h"

class KeyListener: public KeyboardListener{
    void onPress(const KeyboardEvent &e) override {

    }

    void onRelease(const KeyboardEvent &e) override {

    }

    void onPressed(const KeyboardEvent &e) override {
        cout<<"event type->"<<(int)e.getEventType()<<endl;
        cout<<"keyCode->"<<e.getRawKeyCode()<<endl;
    }
};

int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    auto l= Example();
//    l.start();
//    return QApplication::exec();

    auto s = GlobalScreen();
    auto l = KeyListener();
    s.addKeyListener(l);

    s.registerCoreGraphics();


    return 0;
}
