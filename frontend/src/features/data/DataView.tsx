import React from 'react';
import { useAppStore } from '../../store/useAppStore';
import { TRANSLATIONS } from '../../constants/config';
import { Chart as ChartJS, CategoryScale, LinearScale, BarElement, Title, Tooltip, Legend, ArcElement } from 'chart.js';
import { Bar, Doughnut } from 'react-chartjs-2';

ChartJS.register(CategoryScale, LinearScale, BarElement, Title, Tooltip, Legend, ArcElement);

export const DataView: React.FC = () => {
  const { lang, count, totalDuration, presetStats, history } = useAppStore();
  const t = TRANSLATIONS[lang];

  // Dynamic Weekly Data (Mock pattern scaled by actual count for visualization, or 0 if count is 0)
  // In a real app, this would come from a history log. Here we simulate it simply:
  // If count is 0, chart is empty. If count > 0, we show a pattern.
  const hasData = count > 0;
  const labels = [t.lbl_mon, t.lbl_tue, t.lbl_wed, t.lbl_thu, t.lbl_fri, t.lbl_sat, t.lbl_sun];
  const basePattern = [12, 19, 3, 5, 2, 3, 10]; // Mock distribution
  
  // Calculate a scaling factor so the sum somewhat resembles the current count (just for show)
  // or just use 0 if no count.
  const chartData = hasData ? basePattern : [0, 0, 0, 0, 0, 0, 0];

  const weeklyData = {
    labels: labels,
    datasets: [{
      label: 'Squeezes',
      data: chartData,
      backgroundColor: 'rgba(255, 75, 75, 0.6)',
      borderColor: 'rgba(255, 75, 75, 1)',
      borderWidth: 1,
      borderRadius: 4
    }]
  };

  const presetData = {
    labels: [t.pst_soft, t.pst_normal, t.pst_hard, t.pst_barikata, t.pst_custom],
    datasets: [{
      data: [presetStats.soft, presetStats.normal, presetStats.hard, presetStats.barikata, presetStats.custom],
      backgroundColor: ['#FF9F43', '#FF4B4B', '#636e72', '#2d3436', '#34c759'],
      borderWidth: 0
    }]
  };

  return (
    <div className="flex flex-col gap-6 p-4 pb-24">
      {/* Summary Cards */}
      <div className="grid grid-cols-2 gap-4">
        <div className="card p-4 flex flex-col items-center">
            <div className="text-sm text-gray-500 font-bold mb-1">{t.lbl_total_count}</div>
            <div className="text-3xl font-black text-[var(--primary)]">{count}</div>
        </div>
        <div className="card p-4 flex flex-col items-center">
            <div className="text-sm text-gray-500 font-bold mb-1">{t.lbl_avg_time}</div>
            <div className="text-3xl font-black text-[var(--primary)]">
                {(count > 0 ? totalDuration / count : 0).toFixed(1)}<span className="text-sm ml-1">s</span>
            </div>
        </div>
      </div>

      {/* Charts */}
      <div>
          <div className="section-title flex justify-between items-center">
              {t.lbl_history}
              <span className="text-xs font-normal text-gray-500">{history.length} records</span>
          </div>
          <div className="card p-0 overflow-hidden max-h-[400px] overflow-y-auto">
              {history.length === 0 ? (
                  <div className="p-8 text-center text-gray-400 text-sm">
                      {t.lbl_no_history}
                  </div>
              ) : (
                  <div className="divide-y divide-white/10">
                      {history.map((item) => (
                          <div key={item.id} className="p-4 flex justify-between items-center hover:bg-white/5 transition-colors">
                              <div className="flex flex-col">
                                  <span className="text-sm font-bold text-[var(--text-main)]">
                                      {t[`pst_${item.preset}`]}
                                  </span>
                                  <span className="text-xs text-[var(--text-sub)]">
                                      {new Date(item.timestamp).toLocaleString(lang === 'ja' ? 'ja-JP' : 'en-US', { 
                                          month: 'numeric', day: 'numeric', hour: '2-digit', minute: '2-digit' 
                                      })}
                                  </span>
                              </div>
                              <div className="text-right">
                                  <span className="text-lg font-mono font-bold text-[var(--primary)]">
                                      {item.duration.toFixed(1)}s
                                  </span>
                              </div>
                          </div>
                      ))}
                  </div>
              )}
          </div>
      </div>

      <div>
          <div className="section-title">{t.lbl_chart_preset}</div>
          <div className="card p-4">
              <div className="h-64 flex items-center justify-center">
                <Doughnut data={presetData} options={{ 
                    responsive: true, 
                    animation: { duration: 0 },
                    plugins: { legend: { position: 'right' } }, 
                    cutout: '70%' 
                }} />
              </div>
          </div>
      </div>
    </div>
  );
};
