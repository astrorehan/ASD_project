"use client";

import { useState } from "react";
import { Pesanan, JENIS_SEPATU_MAP, JENIS_LAYANAN_MAP } from "@/app/lib/types";
import { api } from "@/app/lib/api";
import { Trash2, Edit3, Clock, CheckCircle, ClipboardList } from "lucide-react";

interface QueueListProps {
  orders: Pesanan[];
  onRefresh: () => void;
  onEdit: (index: number, order: Pesanan) => void;
}

export default function QueueList({ orders, onRefresh, onEdit }: QueueListProps) {
  const [processing, setProcessing] = useState(false);
  const [removing, setRemoving] = useState<number | null>(null);

  const handleProcess = async () => {
    setProcessing(true);
    try {
      await api.processNext();
      onRefresh();
    } catch {
      alert("Gagal memproses pesanan");
    } finally {
      setProcessing(false);
    }
  };

  const handleRemove = async (index: number) => {
    if (!confirm("Hapus pesanan ini?")) return;
    setRemoving(index);
    try {
      await api.removeOrder(index);
      onRefresh();
    } catch {
      alert("Gagal menghapus pesanan");
    } finally {
      setRemoving(null);
    }
  };

  return (
    <div className="space-y-4">
      <div className="flex items-center justify-between">
        <h2 className="text-lg font-semibold text-slate-800">
          Antrean ({orders.length})
        </h2>
        <button
          onClick={handleProcess}
          disabled={orders.length === 0 || processing}
          className="flex items-center gap-2 bg-green-600 hover:bg-green-700 disabled:bg-green-300 text-white px-4 py-2 rounded-lg transition-colors text-sm font-medium"
        >
          <CheckCircle size={18} />
          {processing ? "Memproses..." : "Proses Berikutnya"}
        </button>
      </div>

      {orders.length === 0 ? (
        <div className="bg-slate-50 rounded-xl p-8 text-center text-slate-400">
          <ClipboardList size={48} className="mx-auto mb-3 opacity-30" />
          <p>Belum ada pesanan dalam antrean</p>
        </div>
      ) : (
        <div className="space-y-3">
          {orders.map((order, i) => (
            <div
              key={i}
              className="bg-white border border-slate-200 rounded-xl p-4 shadow-sm hover:shadow-md transition-shadow"
            >
              <div className="flex-1 min-w-0">
                <div className="flex items-center gap-2 mb-1">
                  <span className="bg-cyan-100 text-cyan-700 text-xs font-bold px-2 py-0.5 rounded-full flex-shrink-0">
                    #{i + 1}
                  </span>
                  <h3 className="font-semibold text-slate-800 truncate">{order.namaPelanggan}</h3>
                </div>
                <div className="flex flex-wrap gap-x-3 gap-y-0.5 text-xs text-slate-500">
                  <span>{JENIS_SEPATU_MAP[order.jenisSepatu]}</span>
                  <span>{JENIS_LAYANAN_MAP[order.jenisLayanan]}</span>
                  <span>{order.durasiLayananMenit} menit</span>
                </div>
              </div>
              <div className="flex items-center gap-2 mt-2 sm:mt-0 flex-shrink-0">
                <div className="text-right hidden sm:block">
                  <div className="flex items-center gap-1 text-xs text-slate-500">
                    <Clock size={12} />
                    Estimasi
                  </div>
                  <div className="font-semibold text-cyan-600 text-sm">
                    {order.estimasiSelesai} menit
                  </div>
                </div>
                <div className="flex items-center gap-1 sm:ml-2">
                  <button
                    onClick={() => onEdit(i, order)}
                    className="p-2 text-blue-500 hover:bg-blue-50 rounded-lg transition-colors"
                    title="Edit"
                  >
                    <Edit3 size={15} />
                  </button>
                  <button
                    onClick={() => handleRemove(i)}
                    disabled={removing === i}
                    className="p-2 text-red-500 hover:bg-red-50 rounded-lg transition-colors disabled:opacity-50"
                    title="Hapus"
                  >
                    <Trash2 size={15} />
                  </button>
                </div>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
}
