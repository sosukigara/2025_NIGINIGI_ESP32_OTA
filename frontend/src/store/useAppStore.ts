import { create } from 'zustand';
import { persist } from 'zustand/middleware';
import type { AppState, PresetName } from '../types';

export const useAppStore = create<AppState>()(
  persist(
    (set) => ({
      count: 0,
      totalDuration: 0,
      isSqueezing: false,
      angle: 180,
      duration: 3.0,
      activePresetName: 'normal',
      minLimit: 90,
      returnSpeed: 0.1,
      isPaused: false,
      pausedAt: 0,
      lang: 'ja',
      presetStats: { soft: 0, normal: 0, hard: 0, barikata: 0, custom: 0 },
      customSettings: { angle: 180, duration: 3.0 },
      servoPin: 25,
      servoOffset: 0,
      history: [],
      theme: 'system',

      syncData: async () => {
          // 1. Fetch from server
          try {
            const { ApiClient } = await import('./apiClient');
            const serverStats = await ApiClient.getStats();
            
            set((state) => {
                const newCount = Math.max(state.count, serverStats.count);
                const newDuration = Math.max(state.totalDuration, serverStats.duration);
                
                // If local was updated by server, persist it
                // If local > server, we should push to server
                if (state.count > serverStats.count || state.totalDuration > serverStats.duration) {
                     ApiClient.syncStats({ count: state.count, duration: state.totalDuration });
                }
                
                return { count: newCount, totalDuration: newDuration };
            });
          } catch(e) {
              console.log("Sync failed (offline?)", e);
          }
      },

      resetData: async () => {
          // Attempt server reset, but don't block local reset if it fails (offline mode)
          try {
              const { ApiClient } = await import('./apiClient');
              await ApiClient.resetStats();
          } catch (e) {
              console.warn("Server reset failed (offline?), resetting local only", e);
          }
          // Always reset local state
          set({ 
            count: 0, 
            totalDuration: 0, 
            presetStats: { soft: 0, normal: 0, hard: 0, barikata: 0, custom: 0 },
            history: [] 
          });
      },

      setTheme: (theme) => set({ theme }),

      setSqueezing: (isSqueezing) => set({ isSqueezing }),
      incrementCount: () => {
          set((state) => {
              const next = state.count + 1;
              const newItem = {
                  id: Date.now().toString(),
                  timestamp: Date.now(),
                  preset: state.activePresetName,
                  duration: state.duration
              };
              // Add new item to history (limit to last 50 to save space if needed, or keep all)
              const newHistory = [newItem, ...state.history].slice(0, 50); 

              // Trigger sync in background
              import('./apiClient').then(({ ApiClient }) => {
                  ApiClient.syncStats({ count: next, duration: state.totalDuration });
              });
              return { count: next, history: newHistory };
          });
      },
      addDuration: (time) => {
          set((state) => {
              const next = state.totalDuration + time;
              // Trigger sync in background (debouncing or consolidated sync might be better but this is simple)
              import('./apiClient').then(({ ApiClient }) => {
                  ApiClient.syncStats({ count: state.count, duration: next });
              });
              return { totalDuration: next };
          });
      },
      setPreset: (name, angle, duration) => set((state) => {
        if (name === 'custom') {
            return {
                activePresetName: name,
                angle: state.customSettings.angle,
                duration: state.customSettings.duration
            };
        }
        return {
            activePresetName: name,
            angle: angle ?? state.angle,
            duration: duration ?? state.duration
        };
      }),
      setAngle: (angle) => set((state) => ({ 
          angle,
          customSettings: state.activePresetName === 'custom' 
            ? { ...state.customSettings, angle } 
            : state.customSettings
      })),
      setDuration: (duration) => set((state) => ({ 
          duration,
          customSettings: state.activePresetName === 'custom' 
            ? { ...state.customSettings, duration } 
            : state.customSettings
      })),
      togglePause: () => set((state) => ({ isPaused: !state.isPaused })),
      incrementPresetStat: (name) => set((state) => {
        const key = name as keyof typeof state.presetStats;
        const current = state.presetStats[key] || 0;
        return {
            presetStats: {
                ...state.presetStats,
                [key]: current + 1
            }
        };
      }),
      setLang: (lang) => set({ lang }),
      setServoPin: (servoPin) => set({ servoPin }),
      setServoOffset: (servoOffset) => set({ servoOffset })
    }),
    {
      name: 'onigiri-storage',
      partialize: (state) => ({
        count: state.count,
        totalDuration: state.totalDuration,
        lang: state.lang,
        presetStats: state.presetStats,
        customSettings: state.customSettings,
        servoPin: state.servoPin,
        servoOffset: state.servoOffset,
        theme: state.theme,
        history: state.history
      }),
    }
  )
);
