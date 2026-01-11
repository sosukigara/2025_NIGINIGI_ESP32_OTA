export type PresetName = "soft" | "normal" | "hard" | "barikata" | "custom";
export type Theme = 'light' | 'dark' | 'system';

export interface HistoryItem {
  id: string;
  timestamp: number;
  preset: PresetName;
  duration: number;
}

export interface PresetStats {
  soft: number;
  normal: number;
  hard: number;
  barikata: number;
  custom: number;
}

export interface AppState {
  count: number;
  totalDuration: number;
  history: HistoryItem[];
  isSqueezing: boolean;
  angle: number;
  duration: number;
  activePresetName: PresetName;
  minLimit: number;
  returnSpeed: number;
  isPaused: boolean;
  pausedAt: number;
  lang: "ja" | "km";
  presetStats: PresetStats;
  customSettings: { angle: number; duration: number };
  servoPin: number;
  servoOffset: number;
  theme: Theme;

  // Actions
  setSqueezing: (isSqueezing: boolean) => void;
  incrementCount: () => void;
  addDuration: (time: number) => void;
  setPreset: (name: PresetName, angle?: number, duration?: number) => void;
  setAngle: (angle: number) => void;
  setDuration: (duration: number) => void;
  togglePause: () => void;
  incrementPresetStat: (name: string) => void;
  setLang: (lang: "ja" | "km") => void;
  setServoPin: (pin: number) => void;
  setServoOffset: (offset: number) => void;
  syncData: () => Promise<void>;
  resetData: () => Promise<void>;
  setTheme: (theme: Theme) => void;
}
