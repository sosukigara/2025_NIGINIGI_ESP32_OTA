import React from 'react';
import { useAppStore } from '../store/useAppStore';
import { TRANSLATIONS } from '../constants/config';
import { Wifi } from 'lucide-react';

export const Header: React.FC = () => {
  const lang = useAppStore(state => state.lang);
  const t = TRANSLATIONS[lang];

  return (
    <header className="fixed top-0 left-0 right-0 h-16 header-glass flex items-center justify-between px-4 z-50">
      <div className="flex items-center gap-2">
        <div className="w-8 h-8 rounded-full bg-gradient-to-tr from-[var(--primary)] to-orange-400 flex items-center justify-center text-white font-bold text-xs shadow-lg">
          {t.brand1[0]}
        </div>
        <div className="font-black text-lg tracking-tight text-[var(--text-main)]">
          {t.brand1}<span className="text-[var(--primary)]">{t.brand2}</span>
        </div>
      </div>
      <div className="flex items-center gap-2">
        <div className="w-2 h-2 rounded-full bg-green-500 animate-pulse"></div>
        <Wifi size={16} className="text-gray-400" />
      </div>
    </header>
  );
};
