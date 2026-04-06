"use client";

import { useState, useEffect } from "react";
import { ReportData } from "../lib/types";
import { api } from "../lib/api";
import ReportView from "../components/ReportView";

export default function ReportPage() {
  const [report, setReport] = useState<ReportData | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchReport = async () => {
      try {
        const res = await api.getReport();
        if (res.success && res.data) {
          setReport(res.data);
        }
      } catch {
        // silent fail
      } finally {
        setLoading(false);
      }
    };
    fetchReport();
  }, []);

  return (
    <div className="space-y-6">
      <div>
        <h1 className="text-2xl font-bold text-slate-800 mb-1">Laporan</h1>
        <p className="text-slate-500 text-sm">
          Ringkasan pesanan per jenis layanan
        </p>
      </div>

      {loading ? (
        <div className="text-center py-12 text-slate-400">Memuat...</div>
      ) : report ? (
        <ReportView report={report} />
      ) : (
        <div className="text-center py-12 text-slate-400">
          Gagal memuat laporan
        </div>
      )}
    </div>
  );
}
