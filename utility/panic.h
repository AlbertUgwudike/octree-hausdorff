#ifndef PANIC_H
#define PANIC_H

#include <iostream>
#include <string>

enum Message { IMG_LOAD, DATA_TYPE, TREE_ALLOC, EMPTY_TREE };

void panic(Message);
std::string panic_message(Message message);

#endif