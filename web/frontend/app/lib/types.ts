export enum JenisSepatu {
  SNEAKERS = 0,
  BOOTS = 1,
  SANDALS = 2,
  FORMAL = 3,
  OLAHRAGA = 4,
}

export enum JenisLayanan {
  REGULAR = 0,
  DEEP_CLEANING = 1,
  REPAIR = 2,
  REPAINT = 3,
  WHITENING = 4,
}

export const JENIS_SEPATU_MAP: Record<number, string> = {
  0: "Sneakers",
  1: "Boots",
  2: "Sandals",
  3: "Formal",
  4: "Olahraga",
};

export const JENIS_LAYANAN_MAP: Record<number, string> = {
  0: "Regular",
  1: "Deep Cleaning",
  2: "Repair",
  3: "Repaint",
  4: "Whitening",
};

export const DURASI_LAYANAN: Record<number, number> = {
  0: 60,
  1: 90,
  2: 120,
  3: 150,
  4: 75,
};

export interface Pesanan {
  namaPelanggan: string;
  jenisSepatu: number;
  jenisSepatuStr: string;
  jenisLayanan: number;
  jenisLayananStr: string;
  durasiLayananMenit: number;
  estimasiSelesai: number;
}

export interface ApiResponse<T> {
  success: boolean;
  message?: string;
  data?: T;
  count?: number;
}

export interface ReportData {
  layanan: Array<{
    name: string;
    inQueue: number;
    completed: number;
    total: number;
  }>;
  totalInQueue: number;
  totalCompleted: number;
  totalAll: number;
}
