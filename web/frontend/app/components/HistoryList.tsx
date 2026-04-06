"use client";

import { Pesanan, JENIS_SEPATU_MAP, JENIS_LAYANAN_MAP } from "@/app/lib/types";
import { History } from "lucide-react";

interface HistoryListProps {
  orders: Pesanan[];
}

export default function HistoryList({ orders }: HistoryListProps) {
  return (
    <div className="space-y-4">
      <h2 className="text-lg font-semibold text-slate-800">
        Riwayat ({orders.length})
      </h2>

      {orders.length === 0 ? (
        <div className="bg-slate-50 rounded-xl p-8 text-center text-slate-400">
          <History size={48} className="mx-auto mb-3 opacity-30" />
          <p>Belum ada riwayat pesanan</p>
        </div>
      ) : (
        <div className="space-y-3">
          {orders.map((order, i) => (
            <div
              key={i}
              className="bg-white border border-slate-200 rounded-xl p-4 shadow-sm"
            >
              <div className="flex items-center gap-2 mb-1">
                <span className="bg-green-100 text-green-700 text-xs font-bold px-2 py-0.5 rounded-full">
                  #{i + 1}
                </span>
                <h3 className="font-semibold text-slate-800">{order.namaPelanggan}</h3>
              </div>
              <div className="flex flex-wrap gap-x-4 gap-y-1 text-sm text-slate-500">
                <span>👟 {JENIS_SEPATU_MAP[order.jenisSepatu]}</span>
                <span>🛠️ {JENIS_LAYANAN_MAP[order.jenisLayanan]}</span>
                <span>⏱️ {order.durasiLayananMenit} menit</span>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
