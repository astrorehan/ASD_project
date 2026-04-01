#ifndef UI_H
#define UI_H

#include "models/Pesanan.h"

void tampilMenu();
void pauseSebelumMenu();
void clearConsole();
bool konfirmasiSebelumEnqueue(const Pesanan& pesananBaru);

#endif