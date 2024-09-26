#ifndef KEYEVENT_KEYEVENT_H
#define KEYEVENT_KEYEVENT_H
#include <unordered_map>

struct Modifiers {
  bool shift;
  bool control;
  bool option;
  bool command;
};

enum class KeyEventType { PRESS, RELEASE, PRESSED };

namespace Mapping {
// 不按住 Shift 时的输出
static std::unordered_map<int, const char *> normalKeyMap = {{0, "a"},
                                                             {11, "b"},
                                                             {8, "c"},
                                                             {2, "d"},
                                                             {14, "e"},
                                                             {3, "f"},
                                                             {5, "g"},
                                                             {4, "h"},
                                                             {34, "i"},
                                                             {38, "j"},
                                                             {40, "k"},
                                                             {37, "l"},
                                                             {46, "m"},
                                                             {45, "n"},
                                                             {31, "o"},
                                                             {35, "p"},
                                                             {12, "q"},
                                                             {15, "r"},
                                                             {1, "s"},
                                                             {17, "t"},
                                                             {32, "u"},
                                                             {9, "v"},
                                                             {13, "w"},
                                                             {7, "x"},
                                                             {16, "y"},
                                                             {6, "z"},
                                                             {29, "0"},
                                                             {18, "1"},
                                                             {19, "2"},
                                                             {20, "3"},
                                                             {21, "4"},
                                                             {23, "5"},
                                                             {22, "6"},
                                                             {26, "7"},
                                                             {28, "8"},
                                                             {25, "9"},
                                                             // 特殊键
                                                             {49, "Space"},
                                                             {36, "Enter"},
                                                             {48, "Tab"},
                                                             {56, "LShift"},
                                                             {59, "LCtrl"},
                                                             {58, "LAlt"},
                                                             {55, "LCommand"},
                                                             {60, "RShift"},
                                                             {257, "RCtrl"},
                                                             {61, "RAlt"},
                                                             {54, "RCommand"},
                                                             {53, "Esc"},
                                                             {57, "CapsLock"},
                                                             {179, "Fn"},
                                                             {63, "Fn"},
                                                             {51, "Backspace"},
                                                             {255, "Switch"},

                                                             // 功能键
                                                             {122, "F1"},
                                                             {120, "F2"},
                                                             {99, "F3"},
                                                             {118, "F4"},
                                                             {96, "F5"},
                                                             {97, "F6"},
                                                             {98, "F7"},
                                                             {100, "F8"},
                                                             {101, "F9"},
                                                             {109, "F10"},
                                                             {103, "F11"},
                                                             {111, "F12"},

                                                             // 符号键
                                                             {50, "`"},
                                                             {27, "-"},
                                                             {24, "="},
                                                             {33, "["},
                                                             {30, "]"},
                                                             {42, "\\"},
                                                             {41, ";"},
                                                             {39, "'"},
                                                             {43, ","},
                                                             {47, "."},
                                                             {44, "/"},

                                                             // 方向键
                                                             {123, "←"},
                                                             {124, "→"},
                                                             {126, "↑"},
                                                             {125, "↓"}};

// 按住 Shift 时的输出
static std::unordered_map<int, const char *> shiftKeyMap = {{0, "A"},
                                                            {11, "B"},
                                                            {8, "C"},
                                                            {2, "D"},
                                                            {14, "E"},
                                                            {3, "F"},
                                                            {5, "G"},
                                                            {4, "H"},
                                                            {34, "I"},
                                                            {38, "J"},
                                                            {40, "K"},
                                                            {37, "L"},
                                                            {46, "M"},
                                                            {45, "N"},
                                                            {31, "O"},
                                                            {35, "P"},
                                                            {12, "Q"},
                                                            {15, "R"},
                                                            {1, "S"},
                                                            {17, "T"},
                                                            {32, "U"},
                                                            {9, "V"},
                                                            {13, "W"},
                                                            {7, "X"},
                                                            {16, "Y"},
                                                            {6, "Z"},
                                                            {29, ")"},
                                                            {18, "!"},
                                                            {19, "@"},
                                                            {20, "#"},
                                                            {21, "$"},
                                                            {23, "%"},
                                                            {22, "^"},
                                                            {26, "&"},
                                                            {28, "*"},
                                                            {25, "("},

                                                            // 特殊键
                                                            {49, "Space"},
                                                            {36, "Enter"},
                                                            {48, "Tab"},
                                                            {56, "LShift"},
                                                            {59, "LCtrl"},
                                                            {58, "LAlt"},
                                                            {55, "LCommand"},
                                                            {60, "RShift"},
                                                            {257, "RCtrl"},
                                                            {61, "RAlt"},
                                                            {54, "RCommand"},
                                                            {53, "Esc"},
                                                            {57, "CapsLock"},
                                                            {179, "Fn"},
                                                            {63, "Fn"},
                                                            {51, "Backspace"},
                                                            {255, "Switch"},

                                                            // 功能键
                                                            {122, "F1"},
                                                            {120, "F2"},
                                                            {99, "F3"},
                                                            {118, "F4"},
                                                            {96, "F5"},
                                                            {97, "F6"},
                                                            {98, "F7"},
                                                            {100, "F8"},
                                                            {101, "F9"},
                                                            {109, "F10"},
                                                            {103, "F11"},
                                                            {111, "F12"},

                                                            // 符号键
                                                            {50, "~"},
                                                            {27, "_"},
                                                            {24, "+"},
                                                            {33, "{"},
                                                            {30, "}"},
                                                            {42, "|"},
                                                            {41, ":"},
                                                            {39, "\""},
                                                            {43, "<"},
                                                            {47, ">"},
                                                            {44, "?"},

                                                            // 方向键
                                                            {123, "←"},
                                                            {124, "→"},
                                                            {126, "↑"},
                                                            {125, "↓"}};
} // namespace Mapping

class KeyEvent {
  // 原始键值
  int rawCode;
  // 键
  const char *key;
  // 修饰符
  Modifiers modifiers;
  // 事件类型
  KeyEventType type;

public:
  KeyEvent(int r, const char *k, Modifiers &m, KeyEventType type);
  ~KeyEvent();

  int getRawCode() const;
  const char *getKey() const;
  Modifiers getModifiers() const;
  KeyEventType getType() const;
};

#endif // KEYEVENT_KEYEVENT_H
