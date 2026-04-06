"use client";

import { useState } from "react";
import { JENIS_SEPATU_MAP, JENIS_LAYANAN_MAP, DURASI_LAYANAN } from "@/app/lib/types";
import { api } from "@/app/lib/api";
import { PlusCircle } from "lucide-react";

interface AddOrderFormProps {
  onSuccess: () => void;
}

export default function AddOrderForm({ onSuccess }: AddOrderFormProps) {
  const [nama, setNama] = useState("");
  const [jenisSepatu, setJenisSepatu] = useState(0);
  const [jenisLayanan, setJenisLayanan] = useState(0);
  const [loading, setLoading] = useState(false);
  const [showForm, setShowForm] = useState(false);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    if (!nama.trim()) return;

    setLoading(true);
    try {
      await api.addOrder({
        namaPelanggan: nama.trim(),
        jenisSepatu,
        jenisLayanan,
      });
      setNama("");
      setJenisSepatu(0);
      setJenisLayanan(0);
      setShowForm(false);
      onSuccess();
    } catch {
      alert("Gagal menambahkan pesanan");
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="bg-white border border-slate-200 rounded-xl shadow-sm">
      {!showForm ? (
        <button
          onClick={() => setShowForm(true)}
          className="w-full flex items-center justify-center gap-2 py-4 text-cyan-600 hover:bg-cyan-50 rounded-xl transition-colors font-medium"
        >
          <PlusCircle size={20} />
          Tambah Pesanan Baru
        </button>
      ) : (
        <form onSubmit={handleSubmit} className="p-6 space-y-4">
          <h3 className="font-semibold text-slate-800">Pesanan Baru</h3>

          <div>
            <label className="block text-sm font-medium text-slate-600 mb-1">
              Nama Pelanggan
            </label>
            <input
              type="text"
              value={nama}
              onChange={(e) => setNama(e.target.value)}
              placeholder="Masukkan nama"
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
                  {label} ({DURASI_LAYANAN[Number(val)]} menit)
                </option>
              ))}
            </select>
          </div>

          <div className="flex gap-2">
            <button
              type="submit"
              disabled={loading || !nama.trim()}
              className="flex-1 bg-cyan-600 hover:bg-cyan-700 disabled:bg-cyan-300 text-white py-2 rounded-lg text-sm font-medium transition-colors"
            >
              {loading ? "Menyimpan..." : "Tambah ke Antrean"}
            </button>
            <button
              type="button"
              onClick={() => setShowForm(false)}
              className="px-4 py-2 bg-slate-100 hover:bg-slate-200 text-slate-600 rounded-lg text-sm transition-colors"
            >
              Batal
            </button>
          </div>
        </form>
      )}
    </div>
  );
}
