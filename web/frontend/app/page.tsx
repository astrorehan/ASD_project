"use client";

import { useState, useEffect, useCallback } from "react";
import { Pesanan } from "./lib/types";
import { api } from "./lib/api";
import QueueList from "./components/QueueList";
import AddOrderForm from "./components/AddOrderForm";
import EditOrderModal from "./components/EditOrderModal";

export default function HomePage() {
  const [queue, setQueue] = useState<Pesanan[]>([]);
  const [loading, setLoading] = useState(true);
  const [editTarget, setEditTarget] = useState<{ index: number; order: Pesanan } | null>(null);

  const fetchQueue = useCallback(async () => {
    try {
      const res = await api.getQueue();
      if (res.success && res.data) {
        setQueue(res.data);
      }
    } catch {
      // silent fail
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => {
    fetchQueue();
  }, [fetchQueue]);

  return (
    <div className="space-y-6">
      <div>
        <h1 className="text-2xl font-bold text-slate-800 mb-1">Antrean Cuci Sepatu</h1>
        <p className="text-slate-500 text-sm">
          Kelola pesanan laundry sepatu dengan mudah
        </p>
      </div>

      <AddOrderForm onSuccess={fetchQueue} />

      {loading ? (
        <div className="text-center py-12 text-slate-400">Memuat...</div>
      ) : (
        <QueueList
          orders={queue}
          onRefresh={fetchQueue}
          onEdit={(index, order) => setEditTarget({ index, order })}
        />
      )}

      {editTarget && (
        <EditOrderModal
          index={editTarget.index}
          order={editTarget.order}
          onClose={() => setEditTarget(null)}
          onSuccess={fetchQueue}
        />
      )}
    </div>
  );
}
