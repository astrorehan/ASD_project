"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";
import { ClipboardList, History, BarChart3 } from "lucide-react";

const NAV_ITEMS = [
  { href: "/", label: "Antrean", icon: ClipboardList },
  { href: "/history", label: "Riwayat", icon: History },
  { href: "/report", label: "Laporan", icon: BarChart3 },
];

export default function NavBar() {
  const pathname = usePathname();

  return (
    <nav className="bg-blue-600 text-white shadow-md">
      <div className="max-w-5xl mx-auto px-4">
        <div className="flex items-center justify-between h-16">
          <div className="flex items-center gap-2">
            <span className="text-xl font-bold">👟</span>
            <span className="font-bold tracking-wide text-lg">Shoe Laundry</span>
          </div>
          <div className="flex gap-1">
            {NAV_ITEMS.map(({ href, label, icon: Icon }) => (
              <Link
                key={href}
                href={href}
                className={`flex items-center gap-2 px-4 py-2 rounded-lg transition-colors ${
                  pathname === href
                    ? "bg-white text-blue-600 font-semibold"
                    : "text-blue-100 hover:bg-blue-500 hover:text-white"
                }`}
              >
                <Icon size={18} />
                <span className="text-sm font-medium">{label}</span>
              </Link>
            ))}
          </div>
        </div>
      </div>
    </nav>
  );
}
