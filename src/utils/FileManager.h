#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "../models/Pesanan.h"
#include "../data_structures/Queue.h"
#include "../data_structures/Stack.h"
#include <string>

class FileManager {
public:
    static const std::string SAVE_FILE;

    static void save(const Queue& antrean, const Stack& riwayat);
    static void load(Queue& antrean, Stack& riwayat);
};

#endif
