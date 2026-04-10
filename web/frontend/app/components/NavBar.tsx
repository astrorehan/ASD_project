"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";
import { useState } from "react";
import { ClipboardList, History, BarChart3, Menu, X } from "lucide-react";

const NAV_ITEMS = [
  { href: "/", label: "Antrean", icon: ClipboardList },
  { href: "/history", label: "Riwayat", icon: History },
  { href: "/report", label: "Laporan", icon: BarChart3 },
];

export default function NavBar() {
  const pathname = usePathname();
  const [menuOpen, setMenuOpen] = useState(false);

  return (
    <nav className="bg-blue-600 text-white shadow-md sticky top-0 z-40">
      <div className="max-w-5xl mx-auto px-4">
        <div className="flex items-center justify-between h-14 sm:h-16">
          <div className="flex items-center gap-2">
            <span className="text-xl font-bold">👟</span>
            <span className="font-bold tracking-wide text-base sm:text-lg">Shoe Laundry</span>
          </div>

          {/* Desktop nav */}
          <div className="hidden sm:flex gap-1">
            {NAV_ITEMS.map(({ href, label, icon: Icon }) => (
              <Link
                key={href}
                href={href}
                className={`flex items-center gap-2 px-3 py-2 rounded-lg transition-colors ${
                  pathname === href
                    ? "bg-white text-blue-600 font-semibold"
                    : "text-blue-100 hover:bg-blue-500 hover:text-white"
                }`}
              >
                <Icon size={16} />
                <span className="text-sm font-medium">{label}</span>
              </Link>
            ))}
          </div>

          {/* Mobile hamburger */}
          <button
            onClick={() => setMenuOpen(!menuOpen)}
            className="sm:hidden p-2 hover:bg-blue-500 rounded-lg transition-colors"
            aria-label="Toggle menu"
          >
            {menuOpen ? <X size={22} /> : <Menu size={22} />}
          </button>
        </div>

        {/* Mobile dropdown */}
        {menuOpen && (
          <div className="sm:hidden pb-3 space-y-1">
            {NAV_ITEMS.map(({ href, label, icon: Icon }) => (
              <Link
                key={href}
                href={href}
                onClick={() => setMenuOpen(false)}
                className={`flex items-center gap-3 px-3 py-2.5 rounded-lg transition-colors ${
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
        )}
      </div>
    </nav>
  );
}