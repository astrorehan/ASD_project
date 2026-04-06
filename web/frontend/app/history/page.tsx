"use client";

import { useState, useEffect } from "react";
import { Pesanan } from "../lib/types";
import { api } from "../lib/api";
import HistoryList from "../components/HistoryList";

export default function HistoryPage() {
  const [orders, setOrders] = useState<Pesanan[]>([]);
  const [loading, setLoading] = useState(true);

  const fetchHistory = async () => {
    setLoading(true);
    try {
      const res = await api.getHistory();
      if (res.success && res.data) {
        setOrders(res.data);
      }
    } catch {
      // silent fail
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    fetchHistory();
  }, []);

  return (
    <div className="space-y-6">
      <div>
        <h1 className="text-2xl font-bold text-slate-800 mb-1">Riwayat Pesanan</h1>
        <p className="text-slate-500 text-sm">
          Daftar pesanan yang sudah selesai diproses
        </p>
      </div>

      {loading ? (
        <div className="text-center py-12 text-slate-400">Memuat...</div>
      ) : (
        <HistoryList orders={orders} />
      )}
    </div>
  );
}
