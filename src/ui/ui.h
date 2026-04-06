#ifndef UI_H
#define UI_H

#include "models/Pesanan.h"

class Queue;
class Stack;

void tampilMenu();
void pauseSebelumMenu();
void clearConsole();
bool konfirmasiSebelumEnqueue(const Pesanan& pesananBaru);

// Fitur edit/hapus pesanan
bool formEditPesanan(Queue& antrean);

// Fitur laporan
void tampilLaporan(const Queue& antrean, const Stack& riwayat);

#endif