#include <QApplication>
#include <thread>
#include <QPushButton>
#include "Example.h"
#include "macos/GlobalScreen.h"

using namespace std;

class KeyListener : public KeyboardListener {
    void onPress(const KeyboardEvent &e) override {
//        cout << "event type->" << (int) e.getEventType() << endl;
//        cout << "keyCode->" << e.getRawKeyCode() << "按了" << endl << endl;
    }

    void onRelease(const KeyboardEvent &e) override {
//        cout << "event type->" << (int) e.getEventType() << endl;
//        cout << "keyCode->" << e.getRawKeyCode() << "释放" << endl << endl;
    }

    void onPressed(const KeyboardEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "keyCode->" << e.getRawKeyCode() << "按了" << endl << endl;
    }
};

class MouseListener:public PointerListener{
public:
    void onPress(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "location->(x:" << e.getCoordinate().x<<", y:"<<e.getCoordinate().y<<")" << endl;
        cout << "keyCode->" << e.getButton() << "按下" << endl << endl;
    }

    void onRelease(const PointerEvent &e) override {

    }

    void onDragged(const PointerEvent &e) override {

    }

    void onClicked(const PointerEvent &e) override {

    }
};

class MouseMotionListener:public PointerMotionListener{
public:
    void onMove(const PointerEvent &e) override {
        cout<<"mouse move"<<endl;
        cout<<"current->(x:" << e.getCoordinate().x<<", y:"<<e.getCoordinate().y<<")"<<endl<<endl;
    }

    void onDrag(const PointerEvent &e) override {
        cout<<"mouse drag"<<endl;
        cout<<"current->(x:" << e.getCoordinate().x<<", y:"<<e.getCoordinate().y<<")"<<endl<<endl;
    }
};

void start() {
    GlobalScreen::startListen();
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto l = KeyListener();
    auto l2 = MouseListener();
    auto l3 = MouseMotionListener();
    GlobalScreen::startListen();

    GlobalScreen::globalScreenVal.addKeyListener(l);
    GlobalScreen::globalScreenVal.addPointerListener(l2);
    GlobalScreen::globalScreenVal.addPointerMotionListener(l3);

    return QApplication::exec();
}
