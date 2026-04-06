import { Pesanan, ApiResponse, ReportData } from "./types";

const BASE_URL = process.env.NEXT_PUBLIC_API_URL || "http://localhost:8080";

async function request<T>(
  method: string,
  path: string,
  body?: unknown
): Promise<ApiResponse<T>> {
  const res = await fetch(`${BASE_URL}${path}`, {
    method,
    headers: { "Content-Type": "application/json" },
    body: body ? JSON.stringify(body) : undefined,
  });
  return res.json();
}

export const api = {
  getQueue: () => request<Pesanan[]>("GET", "/queue"),

  addOrder: (data: {
    namaPelanggan: string;
    jenisSepatu: number;
    jenisLayanan: number;
  }) => request<Pesanan>("POST", "/queue", data),

  updateOrder: (index: number, data: Partial<Pesanan>) =>
    request<Pesanan>("PUT", "/queue/" + index, data),

  removeOrder: (index: number) =>
    request("DELETE", "/queue/" + index),

  processNext: () =>
    request<Pesanan>("DELETE", "/queue/process"),

  getHistory: () => request<Pesanan[]>("GET", "/history"),

  getLatest: () => request<Pesanan>("GET", "/history/latest"),

  getReport: () => request<ReportData>("GET", "/report"),
};
