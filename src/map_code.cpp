#include <iostream>
#include <unordered_map>
#include <string>

#include "rkeylogger.h"

// Using azerty keycode
// { CODE, { NORMAL_VALUE, IF_SHIFT_IS_PRESSED, IF_ALTGR_IS_PRESSED }}
std::unordered_map<int, KeyValue> layout = {
    //1st line of keyboard
    {1, { "ESC", "ESC", "ESC"}}, // KEY_ESC
    //...
    //TODO: F1 -> F2 ...

    //2nd line of keyboard
    {41,    {"²",   "~",    "¬"}},
    {2,     {"&",   "1",    "¹"}},
    {3,     {"é",   "2",    "~"}},
    {3,     {"é",   "2",    "~"}},
    {4,     {"\"",  "3",    "#"}},
    {5,     {"'",   "4",    "{"}},
    {6,     {"(",   "5",    "["}},
    {7,     {"-",   "6",    "|"}},
    {8,     {"è",   "7",    "`"}},
    {9,     {"_",   "8",    "\\"}},
    {10,    {"ç",   "9",    "^"}},
    {11,    {"à",   "0",    "@"}},
    {12,    {")",   "°",    "]"}},
    {13,    {"=",   "+",    "}"}},
    {14,    {"KEY_BACKSPACE",   "KEY_BACKSPACE",    "KEY_BACKSPACE"}},
    
    //3rd line of keyboard
    {15,    {"KEY_TAB",   "KEY_TAB",    "KEY_TAB"}},
    {16,    {"a",   "A",    "a"}},
    {17,    {"z",   "Z",    "z"}},
    {18,    {"e",   "E",    "€"}},
    {19,    {"r",   "R",    "r"}},
    {20,    {"t",   "T",    "t"}},
    {21,    {"y",   "Y",    "y"}},
    {22,    {"u",   "U",    "u"}},
    {23,    {"i",   "I",    "i"}},
    {24,    {"o",   "O",    "o"}},
    {25,    {"p",   "P",    "P"}},
    {26,    {"^",   "¨",    "^"}},
    {27,    {"$",   "£",    "¤"}},
    {43,    {"*",   "µ",    "*"}},

    //4th line of keyboard
    {30,    {"q",   "Q",    "q"}},
    {31,    {"s",   "S",    "s"}},
    {32,    {"d",   "D",    "d"}},
    {33,    {"f",   "F",    "f"}},
    {34,    {"g",   "G",    "g"}},
    {35,    {"h",   "H",    "h"}},
    {36,    {"i",   "I",    "i"}},
    {37,    {"j",   "J",    "j"}},
    {38,    {"k",   "K",    "k"}},
    {39,    {"l",   "L",    "l"}},
    {40,    {"m",   "M",    "m"}},
    {41,    {"ù",   "%",    "ù"}},
    {28,    {"KEY_ENTER",   "KEY_ENTER",    "KEY_ENTER"}},

    //5th line of keyboard
    {42,    {"KEY_LEFTSHIFT",   "KEY_LEFTSHIFT",    "KEY_LEFTSHIFT"}},
    {44,    {"w",   "W",    "w"}},
    {45,    {"x",   "X",    "x"}},
    {46,    {"c",   "C",    "c"}},
    {47,    {"v",   "V",    "v"}},
    {48,    {"b",   "B",    "b"}},
    {49,    {"n",   "N",    "n"}},
    {50,    {",",   "?",    ","}},
    {51,    {";",   ".",    ";"}},
    {52,    {":",   "/",    ":"}},
    {53,    {"!",   "§",    "!"}},
    {54,    {"KEY_RIGHTSHIFT",   "KEY_RIGHTSHIFT",    "KEY_RIGHTSHIFT"}},

    //6th line of keyboard
    {100,    {"KEY_RIGHTALT",   "KEY_RIGHTALT",    "KEY_RIGHTALT"}},
};

void setLayout(Layout layout){
    if(layout == Layout::QWERTY){
        //TODO
    }
}

int map_code(int code, int value){
    if(value == 0 && code == 11)
    return -1;
}