#include <QApplication>
#include <thread>
#include <QPushButton>
#include "macos/GlobalScreen.h"

using namespace std;

class KeyListener : public KeyboardListener {
    void onPress(const KeyboardEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "keyCode->" << e.getRawKeyCode() << "按了" << endl << endl;
    }

    void onRelease(const KeyboardEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "keyCode->" << e.getRawKeyCode() << "释放" << endl << endl;
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
        cout << "鼠标->" << e.getButton() << "按下" << endl << endl;
    }

    void onRelease(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "location->(x:" << e.getCoordinate().x<<", y:"<<e.getCoordinate().y<<")" << endl;
        cout << "鼠标->" << e.getButton() << "释放" << endl << endl;
    }

    void onDragged(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "location->(x:" << e.getCoordinate().x<<", y:"<<e.getCoordinate().y<<")" << endl;
        cout << "鼠标->" << e.getButton() << "拖动" << endl << endl;
    }

    void onClicked(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        cout << "location->(x:" << e.getCoordinate().x<<", y:"<<e.getCoordinate().y<<")" << endl;
        cout << "鼠标->" << e.getButton() << "点击" << endl << endl;
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

class MouseWheelListener: public PointerWheelListener{
    void onScroll(const PointerWheelEvent &e) override {
        cout<<"mouse scroll:[dx="<< e.getDx()<<", dy="<<e.getDy()<<", sumX="<<e.getSx()<<", sumY="<<e.getSy()<<")"<<endl<<endl;
    }

    void onScrolled(const PointerWheelEvent &e) override {
        cout<<"mouse scrolled(complete):[dx="<< e.getDx()<<", dy="<<e.getDy()<<", sumX="<<e.getSx()<<", sumY="<<e.getSy()<<")"<<endl<<endl;
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GlobalScreen::startListen();

    auto l = KeyListener();
    auto l2 = MouseListener();
    auto l3 = MouseMotionListener();
    auto l4 = MouseWheelListener();

    GlobalScreen::globalScreenVal.addKeyListener(l);
    GlobalScreen::globalScreenVal.addPointerListener(l2);
    GlobalScreen::globalScreenVal.addPointerMotionListener(l3);
    GlobalScreen::globalScreenVal.addPointerWheelListener(l4);

    GlobalScreen::globalScreenVal.removeKeyListener(l);
    GlobalScreen::globalScreenVal.removePointerListener(l2);
    GlobalScreen::globalScreenVal.removePointerMotionListener(l3);

    return QApplication::exec();
}
