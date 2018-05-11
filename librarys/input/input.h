//Write by 33kingusp
#ifndef INPUT_H
#define INPUT_H

//扱いやすいようにボタン名で定義
#define IN_NONE        0
#define IN_UP          1
#define IN_DOWN        2
#define IN_LEFT        4
#define IN_RIGHT       8
#define IN_A           16
#define IN_B           32
#define IN_EXIT        2048

extern void SetupInput();
extern int Input();

#endif

