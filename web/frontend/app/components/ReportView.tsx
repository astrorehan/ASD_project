"use client";

import { ReportData } from "@/app/lib/types";

interface ReportViewProps {
  report: ReportData;
}

export default function ReportView({ report }: ReportViewProps) {
  return (
    <div className="space-y-4">
      <h2 className="text-lg font-semibold text-slate-800">Laporan Pesanan</h2>

      {/* Desktop table view */}
      <div className="hidden sm:block bg-white border border-slate-200 rounded-xl shadow-sm overflow-hidden">
        <table className="w-full text-sm">
          <thead className="bg-slate-50">
            <tr>
              <th className="text-left px-4 py-3 font-semibold text-slate-600">Layanan</th>
              <th className="text-center px-4 py-3 font-semibold text-slate-600">Dalam Antrean</th>
              <th className="text-center px-4 py-3 font-semibold text-slate-600">Selesai</th>
              <th className="text-center px-4 py-3 font-semibold text-slate-600">Total</th>
            </tr>
          </thead>
          <tbody className="divide-y divide-slate-100">
            {report.layanan.map((item) => (
              <tr key={item.name} className="hover:bg-slate-50">
                <td className="px-4 py-3 font-medium text-slate-700">{item.name}</td>
                <td className="px-4 py-3 text-center text-cyan-600 font-medium">{item.inQueue}</td>
                <td className="px-4 py-3 text-center text-green-600 font-medium">{item.completed}</td>
                <td className="px-4 py-3 text-center text-slate-600">{item.total}</td>
              </tr>
            ))}
          </tbody>
          <tfoot className="bg-slate-100">
            <tr>
              <td className="px-4 py-3 font-bold text-slate-700">Total</td>
              <td className="px-4 py-3 text-center font-bold text-cyan-600">{report.totalInQueue}</td>
              <td className="px-4 py-3 text-center font-bold text-green-600">{report.totalCompleted}</td>
              <td className="px-4 py-3 text-center font-bold text-slate-700">{report.totalAll}</td>
            </tr>
          </tfoot>
        </table>
      </div>

      {/* Mobile card view */}
      <div className="sm:hidden space-y-2">
        {report.layanan.map((item) => (
          <div
            key={item.name}
            className="bg-white border border-slate-200 rounded-xl p-4 shadow-sm"
          >
            <div className="flex items-center justify-between mb-3">
              <span className="font-semibold text-slate-800">{item.name}</span>
              <span className="bg-slate-100 text-slate-500 text-xs font-medium px-2 py-0.5 rounded-full">
                Total: {item.total}
              </span>
            </div>
            <div className="grid grid-cols-2 gap-2 text-sm">
              <div className="bg-cyan-50 rounded-lg p-2 text-center">
                <div className="text-xs text-cyan-500 mb-0.5">Antrean</div>
                <div className="font-bold text-cyan-600">{item.inQueue}</div>
              </div>
              <div className="bg-green-50 rounded-lg p-2 text-center">
                <div className="text-xs text-green-500 mb-0.5">Selesai</div>
                <div className="font-bold text-green-600">{item.completed}</div>
              </div>
            </div>
          </div>
        ))}

        {/* Mobile total footer */}
        <div className="bg-blue-50 border border-blue-200 rounded-xl p-4">
          <div className="text-center">
            <div className="text-xs text-blue-500 mb-1 font-medium">Total Keseluruhan</div>
            <div className="flex justify-center gap-4 text-sm">
              <span className="text-cyan-600 font-bold">{report.totalInQueue} antrean</span>
              <span className="text-green-600 font-bold">{report.totalCompleted} selesai</span>
              <span className="text-blue-600 font-bold">{report.totalAll} total</span>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}