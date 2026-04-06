"use client";

import { useState, useEffect } from "react";
import { Pesanan, JENIS_SEPATU_MAP, JENIS_LAYANAN_MAP } from "@/app/lib/types";
import { api } from "@/app/lib/api";
import { X } from "lucide-react";

interface EditOrderModalProps {
  index: number;
  order: Pesanan;
  onClose: () => void;
  onSuccess: () => void;
}

export default function EditOrderModal({
  index,
  order,
  onClose,
  onSuccess,
}: EditOrderModalProps) {
  const [nama, setNama] = useState(order.namaPelanggan);
  const [jenisSepatu, setJenisSepatu] = useState(order.jenisSepatu);
  const [jenisLayanan, setJenisLayanan] = useState(order.jenisLayanan);
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    const handleEsc = (e: KeyboardEvent) => {
      if (e.key === "Escape") onClose();
    };
    window.addEventListener("keydown", handleEsc);
    return () => window.removeEventListener("keydown", handleEsc);
  }, [onClose]);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    try {
      await api.updateOrder(index, {
        namaPelanggan: nama.trim(),
        jenisSepatu,
        jenisLayanan,
      });
      onSuccess();
      onClose();
    } catch {
      alert("Gagal mengedit pesanan");
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="fixed inset-0 bg-black/50 flex items-center justify-center z-50 p-4">
      <div className="bg-white rounded-2xl shadow-xl w-full max-w-md">
        <div className="flex items-center justify-between p-4 border-b">
          <h3 className="font-semibold text-slate-800">Edit Pesanan #{index + 1}</h3>
          <button
            onClick={onClose}
            className="p-1 hover:bg-slate-100 rounded-lg transition-colors"
          >
            <X size={20} />
          </button>
        </div>

        <form onSubmit={handleSubmit} className="p-4 space-y-4">
          <div>
            <label className="block text-sm font-medium text-slate-600 mb-1">
              Nama Pelanggan
            </label>
            <input
              type="text"
              value={nama}
              onChange={(e) => setNama(e.target.value)}
              required
              className="w-full border border-slate-300 rounded-lg px-3 py-2 text-sm focus:outline-none focus:ring-2 focus:ring-cyan-500"
            />
          </div>

          <div>
            <label className="block text-sm font-medium text-slate-600 mb-1">
              Jenis Sepatu
            </label>
            <select
              value={jenisSepatu}
              onChange={(e) => setJenisSepatu(Number(e.target.value))}
              className="w-full border border-slate-300 rounded-lg px-3 py-2 text-sm focus:outline-none focus:ring-2 focus:ring-cyan-500"
            >
              {Object.entries(JENIS_SEPATU_MAP).map(([val, label]) => (
                <option key={val} value={val}>
                  {label}
                </option>
              ))}
            </select>
          </div>

          <div>
            <label className="block text-sm font-medium text-slate-600 mb-1">
              Jenis Layanan
            </label>
            <select
              value={jenisLayanan}
              onChange={(e) => setJenisLayanan(Number(e.target.value))}
              className="w-full border border-slate-300 rounded-lg px-3 py-2 text-sm focus:outline-none focus:ring-2 focus:ring-cyan-500"
            >
              {Object.entries(JENIS_LAYANAN_MAP).map(([val, label]) => (
                <option key={val} value={val}>
                  {label}
                </option>
              ))}
            </select>
          </div>

          <div className="flex gap-2 pt-2">
            <button
              type="submit"
              disabled={loading}
              className="flex-1 bg-cyan-600 hover:bg-cyan-700 disabled:bg-cyan-300 text-white py-2 rounded-lg text-sm font-medium transition-colors"
            >
              {loading ? "Menyimpan..." : "Simpan Perubahan"}
            </button>
            <button
              type="button"
              onClick={onClose}
              className="px-4 py-2 bg-slate-100 hover:bg-slate-200 text-slate-600 rounded-lg text-sm transition-colors"
            >
              Batal
            </button>
          </div>
        </form>
      </div>
    </div>
  );
}
