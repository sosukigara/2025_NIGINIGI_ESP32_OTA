export const API_ENDPOINTS = {
  status: '/api/status',
  squeeze: '/api/squeeze',
  stop: '/api/stop',
  register: '/api/register',
  settings: '/api/settings',
  save_settings: '/api/save_settings',
  restart: '/api/restart',
  reset: '/api/reset'
};

export const PRESETS = {
  soft: { angle: 160, duration: 2.5 },
  normal: { angle: 180, duration: 3.0 },
  hard: { angle: 210, duration: 3.5 },
  barikata: { angle: 240, duration: 4.0 }, // New preset 240
  custom: { angle: 180, duration: 3.0 }
};

export const TRANSLATIONS = {
  ja: {
    brand1: 'にぎにぎ', brand2: '', status_ready: '準備完了', status_squeezing: '握り中...',
    status_pausing: '一時停止', status_finished: '完成！', pst_soft: 'ふんわり', pst_normal: 'ふつう',
    pst_hard: 'かため', pst_barikata: 'ばりかた', pst_custom: 'カスタム', btn_squeeze: '握る',
    btn_stop: '中止', btn_pause: '一時停止', btn_resume: '再開', lbl_strength: '強さ (角度)',
    lbl_duration: '時間 (秒)', hdr_system: 'システム', lbl_language: '言語', btn_save: '保存',
    nav_control: '操作', nav_data: 'データ', nav_settings: '設定', lbl_connected_devices: '接続デバイス',
    lbl_theme: 'テーマ', theme_light: 'ライト', theme_dark: 'ダーク', theme_system: '自動',
    lbl_type: '種類', lbl_time: '時間', lbl_return_speed: '戻り速度', msg_save_ok: '保存しました',
    msg_lang_ok: '言語を変更しました', msg_stop_ok: '中止しました', hdr_stats: '統計',
    lbl_total_count: '総握り回数', lbl_avg_time: '平均時間', hdr_basic_settings: '基本設定',
    hdr_advanced_settings: '詳細設定 / デバッグ', lbl_device_name: 'SSID (この機器)',
    lbl_your_device: 'あなたのデバイス', lbl_accessing_devices: 'アクセス中の端末',
    lbl_firmware_date: 'FW更新日時', lbl_chart_weekly: '週間活動量', lbl_chart_preset: '好みの硬さ',
    hdr_hardware: 'ハードウェア設定', lbl_servo_pin: '制御ピン (GPIO)', lbl_servo_offset: '位置補正 (角度)',
    lbl_servo_debug: 'サーボ手動位置 (デバッグ)', msg_reset_confirm: '本当に統計データをリセットしますか？',
    btn_reset_stats: '統計リセット',
    lbl_reset: '統計リセット',
    btn_cancel: 'キャンセル',
    btn_reset_action: 'リセット実行',
    lbl_history: '握り履歴', lbl_no_history: '履歴はまだありません',
    msg_drag_adjust: 'ドラッグして強さを調整',
    lbl_angle: '角度',
    lbl_version: 'バージョン',
    lbl_mon: '月', lbl_tue: '火', lbl_wed: '水', lbl_thu: '木', lbl_fri: '金', lbl_sat: '土', lbl_sun: '日',
  },
  km: {
      brand1: 'អ្នកផលិតអូនីហ្គីរី', brand2: 'ប្រូ', status_ready: 'រួចរាល់', status_squeezing: 'កំពុងច្របាច់...',
      status_pausing: 'ផ្អាក', status_finished: 'រួចរាល់!', pst_soft: 'ទន់', pst_normal: 'ធម្មតា',
      pst_hard: 'រឹង', pst_barikata: 'រឹងខ្លាំង', pst_custom: 'កំណត់ខ្លួនឯង', btn_squeeze: 'ច្របាច់',
      btn_stop: 'ឈប់', btn_pause: 'ផ្អាក', btn_resume: 'បន្ត', lbl_strength: 'កម្លាំង',
      lbl_duration: 'រយៈពេល', hdr_system: 'ប្រព័ន្ធ', lbl_language: 'ភាសា', btn_save: 'រក្សាទុក',
      nav_control: 'បញ្ជា', nav_data: 'ទិន្នន័យ', nav_settings: 'កំណត់', lbl_connected_devices: 'ឧបករណ៍',
      lbl_theme: 'Theme', theme_light: 'Light', theme_dark: 'Dark', theme_system: 'Auto',
      lbl_type: 'ប្រភេទ', lbl_time: 'ពេល', lbl_return_speed: 'ល្បឿនត្រឡប់', msg_save_ok: 'បានរក្សាទុក',
      msg_lang_ok: 'បានប្តូរភាសា', msg_stop_ok: 'បានឈប់', hdr_stats: 'ស្ថិតិ', lbl_total_count: 'ចំនួនសរុប',
      lbl_avg_time: 'ពេលមធ្យម', hdr_basic_settings: 'ការកំណត់មូលដ្ឋាន', hdr_advanced_settings: 'ការកំណត់កម្រិតខ្ពស់',
      lbl_device_name: 'ឈ្មោះ AP', lbl_your_device: 'ឧបករណ៍របស់អ្នក', lbl_accessing_devices: 'ឧបករណ៍ក្នុងប្រព័ន្ធ',
      lbl_firmware_date: 'កាលបរិច្ឆេទ Firmware', lbl_chart_weekly: 'សកម្មភាពប្រចាំសប្តាហ៍',
      lbl_chart_preset: 'ចំណូលចិត្ត', hdr_hardware: 'Hardware', lbl_servo_pin: 'Servo Pin', lbl_servo_offset: 'Calibration',
      lbl_servo_debug: 'Servo Position (Debug)', msg_reset_confirm: 'Are you sure you want to reset stats?',
      btn_reset_stats: 'កំណត់ស្ថិតិឡើងវិញ',
      lbl_reset: 'កំណត់ស្ថិតិឡើងវិញ',
      btn_cancel: 'បោះបង់',
      btn_reset_action: 'កំណត់ឡើងវិញ',
      msg_drag_adjust: 'អូសដើម្បីកែតម្រូវ',
      lbl_angle: 'មុំ',
      lbl_version: 'Version',
      lbl_mon: 'ច័ន្ទ', lbl_tue: 'អង្គារ', lbl_wed: 'ពុធ', lbl_thu: 'ព្រហ', lbl_fri: 'សុក្រ', lbl_sat: 'សៅរ៍', lbl_sun: 'អាទិត្យ',
      lbl_history: 'ប្រវត្តិនៃការច្របាច់', lbl_no_history: 'មិនទាន់មានប្រវត្តិទេ',
  }
};
