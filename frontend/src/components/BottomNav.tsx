import React from 'react';
import { useAppStore } from '../store/useAppStore';
import { TRANSLATIONS } from '../constants/config';
import { Gamepad2, BarChart2, Settings } from 'lucide-react';
import { useHaptic } from '../hooks/useHaptic';

export type Tab = 'control' | 'data' | 'settings';

interface BottomNavProps {
  activeTab: Tab;
  setActiveTab: (tab: Tab) => void;
}

export const BottomNav: React.FC<BottomNavProps> = ({ activeTab, setActiveTab }) => {
  const lang = useAppStore(state => state.lang);
  const t = TRANSLATIONS[lang];
  const { vibrate } = useHaptic();

  const handleSwitch = (tab: Tab) => {
    vibrate(30);
    // View Transitions Logic
    if (document.startViewTransition) {
        document.documentElement.dataset.transition = getDirection(activeTab, tab);
        document.startViewTransition(() => {
            setActiveTab(tab);
        });
    } else {
        setActiveTab(tab);
    }
  };

  const getDirection = (from: Tab, to: Tab) => {
      const order = ['control', 'data', 'settings'];
      return order.indexOf(to) > order.indexOf(from) ? 'forward' : 'backward';
  };

  const NavItem = ({ id, icon: Icon, label }: { id: Tab, icon: any, label: string }) => (
    <button
      onClick={() => handleSwitch(id)}
      className={`flex flex-col items-center justify-center gap-1 w-16 transition-all ${
        activeTab === id ? 'text-[var(--primary)] scale-110' : 'text-gray-400'
      }`}
    >
      <Icon size={24} strokeWidth={activeTab === id ? 3 : 2} />
      <span className="text-[0.65rem] font-bold">{label}</span>
    </button>
  );

  return (
    <nav className="fixed bottom-0 left-0 right-0 h-20 bottom-nav-glass flex items-start pt-3 justify-around z-50 pb-safe">
      <NavItem id="control" icon={Gamepad2} label={t.nav_control} />
      <NavItem id="data" icon={BarChart2} label={t.nav_data} />
      <NavItem id="settings" icon={Settings} label={t.nav_settings} />
    </nav>
  );
};
