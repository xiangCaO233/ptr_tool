#include <QApplication>
#include <thread>
#include <QPushButton>
#include "macos/GlobalScreen.h"

using namespace std;

//键盘监听器
class KeyListener : public KeyboardListener {
    void onPress(const KeyboardEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "按键->" << keyMap::reverseKeyMap.at(keyMap::KeyTypeMap.at(e.getRawKeyCode())) << "按了" << endl
             << endl;
    }

    void onRelease(const KeyboardEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "按键->" << keyMap::reverseKeyMap.at(keyMap::KeyTypeMap.at(e.getRawKeyCode())) << "释放" << endl
             << endl;
    }

    void onPressed(const KeyboardEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "按键->" << keyMap::reverseKeyMap.at(keyMap::KeyTypeMap.at(e.getRawKeyCode())) << "按了" << endl
             << endl;
    }
};

//鼠标监听器
class MouseListener : public PointerListener {
public:
    void onPress(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "location->(x:" << e.getCoordinate().x << ", y:" << e.getCoordinate().y << ")" << endl;
        cout << "鼠标->" << e.getButton() << "按下" << endl << endl;
    }

    void onRelease(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "location->(x:" << e.getCoordinate().x << ", y:" << e.getCoordinate().y << ")" << endl;
        cout << "鼠标->" << e.getButton() << "释放" << endl << endl;
    }

    void onDragged(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "location->(x:" << e.getCoordinate().x << ", y:" << e.getCoordinate().y << ")" << endl;
        cout << "鼠标->" << e.getButton() << "拖动" << endl << endl;
    }

    void onClicked(const PointerEvent &e) override {
        cout << "event type->" << (int) e.getEventType() << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "location->(x:" << e.getCoordinate().x << ", y:" << e.getCoordinate().y << ")" << endl;
        cout << "鼠标->" << e.getButton() << "点击" << endl << endl;
    }
};

//鼠标运动监听器
class MouseMotionListener : public PointerMotionListener {
public:
    void onMove(const PointerEvent &e) override {
        cout << "鼠标移动了" << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "当前坐标->(x:" << e.getCoordinate().x << ", y:" << e.getCoordinate().y << ")" << endl << endl;
    }

    void onDrag(const PointerEvent &e) override {
        cout << "鼠标拖动了" << endl;
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "current->(x:" << e.getCoordinate().x << ", y:" << e.getCoordinate().y << ")" << endl << endl;
    }
};

//鼠标滚轮监听器
class MouseWheelListener : public PointerWheelListener {
    void onScroll(const PointerWheelEvent &e) override {
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "鼠标滚动了:[dx=" << e.getDx() << ", dy=" << e.getDy() << ", sumX=" << e.getSx() << ", sumY="
             << e.getSy() << ")" << endl << endl;
    }

    void onScrolled(const PointerWheelEvent &e) override {
        if (e.isShiftDown())cout << "shift down" << endl;
        if (e.isControlDown())cout << "control down" << endl;
        if (e.isAltDown())cout << "alt down" << endl;
        if (e.isCommandDown())cout << "command down" << endl;
        cout << "鼠标滚动结束(complete):[dx=" << e.getDx() << ", dy=" << e.getDy() << ", sumX=" << e.getSx()
             << ", sumY=" << e.getSy() << ")" << endl << endl;
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    GlobalScreen::startListen();

    //构造监听器
    auto l = KeyListener();
    auto l2 = MouseListener();
    auto l3 = MouseMotionListener();
    auto l4 = MouseWheelListener();

    //添加监听器
    GlobalScreen::globalScreenVal.addKeyListener(l);
    GlobalScreen::globalScreenVal.addPointerListener(l2);
    GlobalScreen::globalScreenVal.addPointerMotionListener(l3);
    GlobalScreen::globalScreenVal.addPointerWheelListener(l4);

    usleep(1000*1000);//1s
    CGPoint p;
    p.x = 1000;
    p.y = 20;
    GlobalScreen::moveMouse(p);
//    GlobalScreen::globalScreenVal.removeKeyListener(l);
//    GlobalScreen::globalScreenVal.removePointerListener(l2);
//    GlobalScreen::globalScreenVal.removePointerMotionListener(l3);

    return QApplication::exec();
}
