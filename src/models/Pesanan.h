#ifndef PESANAN_H
#define PESANAN_H
#include <string>   

using namespace std;

enum JenisSepatu{
    SNEAKERS,
    BOOTS,
    SANDALS,
    FORMAL,
    OLAHRAGA
};

inline string toString(JenisSepatu nilai) {
    switch (nilai) {
    case SNEAKERS: return "Sneakers";
    case BOOTS: return "Boots";
    case SANDALS: return "Sandals";
    case FORMAL: return "Formal";
    case OLAHRAGA: return "Olahraga";
    default: return "Tidak diketahui";
    }
};

enum JenisLayanan{
    REGULAR,
    DEEP_CLEANING,
    REPAIR,
    REPAINT,
    WHITENING
};

inline string toString(JenisLayanan nilai) {
    switch (nilai) {
        case REGULAR: return "Regular";
        case DEEP_CLEANING: return "Deep Cleaning";
        case REPAIR: return "Repair";
        case REPAINT: return "Repaint";
        case WHITENING: return "Whitening";
        default: return "Tidak diketahui";
    }
};

inline bool fromChoiceSepatu(int pilihan, JenisSepatu& hasil){
    switch (pilihan)
    {
        case 1: hasil = SNEAKERS; return true;
        case 2: hasil = BOOTS; return true;
        case 3: hasil = SANDALS; return true;
        case 4: hasil = FORMAL; return true;
        case 5: hasil = OLAHRAGA; return true;
        
        default: return false;
    }

};

inline bool fromChoiceLayanan(int pilihan, JenisLayanan& hasil){
    switch (pilihan)
    {
        case 1: hasil = REGULAR; return true;
        case 2: hasil = DEEP_CLEANING; return true;
        case 3: hasil = REPAIR; return true;
        case 4: hasil = REPAINT; return true;
        case 5: hasil = WHITENING; return true;
        
        default: return false;
    }
};

struct Pesanan{
    string namaPelanggan;
    JenisSepatu jenisSepatu;
    JenisLayanan jenisLayanan;
};



#endif