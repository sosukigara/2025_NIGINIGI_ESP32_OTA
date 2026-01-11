import React, { useState, useEffect } from 'react';
import { useAppStore } from './store/useAppStore';
import { Header } from './components/Header';
import { BottomNav, type Tab } from './components/BottomNav';
import { SqueezeView } from './features/control/SqueezeView';
import { DataView } from './features/data/DataView';
import { SettingsView } from './features/settings/SettingsView';

function App() {
  const [activeTab, setActiveTab] = useState<Tab>('control');
  const { theme, syncData } = useAppStore();

  useEffect(() => {
    // Initial Sync with ESP32
    syncData();
  }, []);

  useEffect(() => {
    const root = window.document.documentElement;
    const isDark = theme === 'dark' || (theme === 'system' && window.matchMedia('(prefers-color-scheme: dark)').matches);
    
    if (isDark) {
        root.classList.add('dark');
        document.querySelector('meta[name="theme-color"]')?.setAttribute('content', '#000000');
    } else {
        root.classList.remove('dark');
        document.querySelector('meta[name="theme-color"]')?.setAttribute('content', '#f2f2f7');
    }
  }, [theme]);

  return (
    <div className="min-h-screen pt-16 pb-20 overflow-x-hidden relative view-section">
      <Header />
      
      <main className="max-w-md mx-auto w-full min-h-full relative">
        <div style={{ display: activeTab === 'control' ? 'block' : 'none' }}>
            <SqueezeView />
        </div>
        <div style={{ display: activeTab === 'data' ? 'block' : 'none' }}>
            <DataView />
        </div>
        <div style={{ display: activeTab === 'settings' ? 'block' : 'none' }}>
            <SettingsView />
        </div>
      </main>

      <BottomNav activeTab={activeTab} setActiveTab={setActiveTab} />
    </div>
  );
}

export default App;
