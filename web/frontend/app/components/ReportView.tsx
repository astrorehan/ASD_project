"use client";

import { ReportData } from "@/app/lib/types";

interface ReportViewProps {
  report: ReportData;
}

export default function ReportView({ report }: ReportViewProps) {
  return (
    <div className="space-y-6">
      <h2 className="text-lg font-semibold text-slate-800">Laporan Pesanan</h2>

      <div className="bg-white border border-slate-200 rounded-xl shadow-sm overflow-hidden">
        <table className="w-full text-sm">
          <thead className="bg-slate-50">
            <tr>
              <th className="text-left px-4 py-3 font-semibold text-slate-600">
                Layanan
              </th>
              <th className="text-center px-4 py-3 font-semibold text-slate-600">
                Dalam Antrean
              </th>
              <th className="text-center px-4 py-3 font-semibold text-slate-600">
                Selesai
              </th>
              <th className="text-center px-4 py-3 font-semibold text-slate-600">
                Total
              </th>
            </tr>
          </thead>
          <tbody className="divide-y divide-slate-100">
            {report.layanan.map((item) => (
              <tr key={item.name} className="hover:bg-slate-50">
                <td className="px-4 py-3 font-medium text-slate-700">{item.name}</td>
                <td className="px-4 py-3 text-center text-cyan-600 font-medium">
                  {item.inQueue}
                </td>
                <td className="px-4 py-3 text-center text-green-600 font-medium">
                  {item.completed}
                </td>
                <td className="px-4 py-3 text-center text-slate-600">{item.total}</td>
              </tr>
            ))}
          </tbody>
          <tfoot className="bg-slate-100">
            <tr>
              <td className="px-4 py-3 font-bold text-slate-700">Total</td>
              <td className="px-4 py-3 text-center font-bold text-cyan-600">
                {report.totalInQueue}
              </td>
              <td className="px-4 py-3 text-center font-bold text-green-600">
                {report.totalCompleted}
              </td>
              <td className="px-4 py-3 text-center font-bold text-slate-700">
                {report.totalAll}
              </td>
            </tr>
          </tfoot>
        </table>
      </div>
    </div>
  );
}
