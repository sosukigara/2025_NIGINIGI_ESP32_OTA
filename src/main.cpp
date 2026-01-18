// 動作確認済みバージョン (Once it works!)
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
#include <ESP32Servo.h>
#include <Preferences.h>

// UIファイル (前回作成したものをそのまま使用)
// --- UI Content ---
const char* html_main = R"rawliteral(
<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, viewport-fit=cover">
<title>Onigiri Journal</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600;800&family=Noto+Sans+JP:wght@400;700;900&display=swap" rel="stylesheet">
<link href="https://fonts.googleapis.com/icon?family=Material+Icons+Round" rel="stylesheet">

<style>
:root {
  --bg: #f2f2f7;
  --card-bg: #ffffff;
  --text-main: #1c1c1e;
  --text-sub: #8e8e93;
  --accent-purple: #5e5ce6;
  --accent-blue: #007aff;
  --danger: #ff3b30;
  --yt-red: #ff0000;
  --success: #34c759;
  
  --shadow: 0 4px 12px rgba(0,0,0,0.03);
  --radius: 16px;
}

* {
  -webkit-tap-highlight-color: transparent;
  user-select: none;
  -webkit-touch-callout: none;
  box-sizing: border-box;
}

body {
  background: var(--bg);
  color: var(--text-main);
  font-family: 'Inter', 'Noto Sans JP', sans-serif;
  margin: 0; padding: 20px;
  min-height: 100vh;
  padding-bottom: 120px;
  transition: opacity 0.3s;
}

/* Connection Lost State */
body.offline { opacity: 0.6; pointer-events: none; }
body.offline::after {
  content: "再接続中...";
  position: fixed; top: 50%; left: 50%; transform: translate(-50%, -50%);
  background: rgba(0,0,0,0.8); color: white; padding: 12px 24px;
  border-radius: 30px; font-weight: bold; pointer-events: none; z-index: 2000;
}

/* Header */
.header { 
  margin-bottom: 20px; padding-top: 0; 
  display: flex; justify-content: space-between; align-items: center;
} 
.header h1 {
  font-size: 1.9rem; font-weight: 800; margin: 0; letter-spacing: -0.02em;
}
.btn-icon {
  background: none; border: none; padding: 8px; margin-right: -8px;
  color: var(--text-main); cursor: pointer; border-radius: 50%;
  display: flex; align-items: center; justify-content: center;
}
.btn-icon:active { background: rgba(0,0,0,0.05); }

/* Status Dot */
.conn-dot {
  width: 10px; height: 10px; background: var(--success);
  border-radius: 50%; margin-right: 8px;
  transition: background 0.3s;
}
.offline .conn-dot { background: var(--danger); }

/* Cards */
.card {
  background: var(--card-bg);
  border-radius: var(--radius);
  padding: 20px; 
  margin-bottom: 20px;
  box-shadow: var(--shadow);
  overflow: hidden;
}

/* Monitor Card */
.card-monitor {
  display: flex; flex-direction: column;
  position: relative;
  padding-bottom: 22px; 
}
.monitor-row { 
  display: flex; flex-direction: column; 
  align-items: center; justify-content: center;
  gap: 8px; margin-bottom: 18px;
}
.status-badge {
  background: #f2f2f7; color: var(--text-sub);
  padding: 6px 14px; border-radius: 24px;
  font-size: 0.9rem; font-weight: 700;
  transition: 0.3s;
}
.running .status-badge { background: #fee2e2; color: var(--yt-red); }

/* Time Display */
.time-big {
  font-size: clamp(3.2rem, 16vw, 4.8rem); 
  font-weight: 800; 
  font-variant-numeric: tabular-nums; 
  letter-spacing: -2px; line-height: 1;
  opacity: 0; 
  transition: opacity 0.3s;
}
body.ready .time-big { opacity: 1; }

/* Progress Bar */
.yt-progress-container {
  width: 100%; height: 8px; 
  background: #e5e5ea; position: relative;
  border-radius: 4px; overflow: hidden;
  opacity: 0; 
  transition: opacity 0.3s;
}
.running .yt-progress-container { opacity: 1; } 

.yt-progress-fill {
  position: absolute; left: 0; top: 0; height: 100%;
  background: var(--yt-red); border-radius: 4px;
  width: 0%; 
}

/* Preset Buttons */
.card-preset h3 { margin: 0 0 10px 0; font-size: 1rem; color: var(--text-sub); text-transform: uppercase; letter-spacing: 0.05em; }
.preset-grid { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 10px; }
.preset-btn {
  background: var(--bg); border: 2px solid transparent;
  padding: 14px 4px; border-radius: 14px; /* padding調整 */
  font-size: 0.95rem; font-weight: 700; color: var(--text-main);
  text-align: center; cursor: pointer; transition: 0.2s;
  white-space: nowrap; /* 折り返し防止 */
}
.preset-btn:active { transform: scale(0.98); }
.preset-btn.active {
  background: #fff; border-color: var(--accent-blue); color: var(--accent-blue);
  box-shadow: 0 4px 10px rgba(0,122,255,0.15);
}

/* Settings List */
.card-settings { padding: 18px; } 
.setting-item {
  padding: 12px 0; display: flex; flex-direction: column; 
  border-bottom: 1px solid #f2f2f7;
}
.setting-item:last-child { border-bottom: none; }
.s-header {
  display: flex; justify-content: space-between; align-items: center;
  margin-bottom: 10px;
}
.s-label { font-size: 1rem; font-weight: 700; color: var(--text-main); }
.s-val { font-size: 1.1rem; font-weight: 700; color: var(--accent-purple); font-variant-numeric: tabular-nums; }

/* Sliders */
input[type=range] {
  -webkit-appearance: none; width: 100%; height: 44px; 
  background: transparent; cursor: pointer; margin: 0;
}
input[type=range]:focus { outline: none; }
input[type=range]::-webkit-slider-runnable-track {
  width: 100%; height: 14px; 
  background: #e5e5ea; 
  border-radius: 7px;
}
#inp-str::-webkit-slider-runnable-track {
  background: linear-gradient(90deg, #e5e5ea 0%, #a0a0ff 50%, #5e5ce6 100%);
}

input[type=range]::-webkit-slider-thumb {
  -webkit-appearance: none; height: 32px; width: 32px;
  border-radius: 50%; background: #ffffff;
  border: 0.5px solid rgba(0,0,0,0.04);
  box-shadow: 0 4px 10px rgba(0,0,0,0.15);
  margin-top: -9px; transition: transform 0.1s;
}
input[type=range]:active::-webkit-slider-thumb { transform: scale(1.1); background: #f2f2f7; }

/* Count Buttons */
.chk-group { display: flex; gap: 10px; justify-content: flex-end; }
.chk-btn {
  width: 48px; height: 48px; border-radius: 50%;
  background: #f2f2f7; color: var(--text-sub);
  display: flex; align-items: center; justify-content: center;
  font-size: 1.2rem; font-weight: 700; cursor: pointer; transition: 0.2s;
}
.chk-btn.active {
  background: var(--text-main); color: white;
  box-shadow: 0 4px 10px rgba(0,0,0,0.2); transform: scale(1.05);
}

/* Bottom Bar */
.bottom-bar {
  position: fixed; bottom: 30px; left: 18px; right: 18px;
  z-index: 100; display: flex; gap: 12px;
  filter: drop-shadow(0 10px 20px rgba(0,0,0,0.1));
}
.action-btn {
  flex: 1; height: 68px; border-radius: 34px; border: none;
  font-size: 1.2rem; font-weight: 800;
  display: flex; align-items: center; justify-content: center; gap: 8px;
  cursor: pointer; box-shadow: inset 0 1px 1px rgba(255,255,255,0.4);
  transition: transform 0.1s;
}
.action-btn:active { transform: scale(0.98); }
.btn-start { background: var(--text-main); color: white; }
.btn-stop { background: var(--danger); color: white; display: none; }
.running .btn-start { display: none; }
.running .btn-stop { display: flex; }

/* Toggle Switch */
.switch { position: relative; display: inline-block; width: 50px; height: 28px; }
.switch input { opacity: 0; width: 0; height: 0; }
.slider {
  position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0;
  background-color: #e5e5ea; transition: .4s; border-radius: 28px;
}
.slider:before {
  position: absolute; content: ""; height: 20px; width: 20px;
  left: 4px; bottom: 4px; background-color: white; transition: .4s; border-radius: 50%;
  box-shadow: 0 2px 4px rgba(0,0,0,0.2);
}
input:checked + .slider { background-color: var(--accent-blue); }
input:checked + .slider:before { transform: translateX(22px); }

/* Completion Modal */
.completion-modal {
  position: fixed; top: 0; left: 0; right: 0; bottom: 0;
  background: rgba(0,0,0,0.7); /* 少し薄暗く */
  backdrop-filter: blur(4px);   /* 背景ぼかしでリッチに */
  -webkit-backdrop-filter: blur(4px);
  display: none; align-items: center; justify-content: center;
  z-index: 1000;
  animation: fadeIn 0.3s;
}
.completion-modal.show { display: flex; }

.completion-content {
  background: var(--card-bg);
  border-radius: 28px;
  padding: 32px 28px; /* パディング調整 */
  text-align: center;
  max-width: 85%; width: 340px;
  box-shadow: 0 20px 40px rgba(0,0,0,0.2);
  animation: scaleIn 0.3s cubic-bezier(0.34, 1.56, 0.64, 1);
}

.completion-title {
  font-size: 1.6rem; /* 少し控えめに */
  font-weight: 800;
  color: var(--text-main);
  margin-bottom: 24px; /* 間隔を広げる */
}

.completion-details {
  text-align: left;
  background: var(--bg);
  padding: 16px 20px;
  border-radius: 16px;
  margin-bottom: 24px;
}

.detail-row {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 10px 0;
  border-bottom: 1px solid rgba(0,0,0,0.05);
}
.detail-row:last-child { border-bottom: none; }

.detail-label {
  font-size: 0.9rem;
  color: var(--text-sub);
  font-weight: 600;
}

.detail-value {
  font-size: 1.0rem;
  color: var(--text-main);
  font-weight: 700;
}

.completion-btn {
  background: var(--text-main); /* 黒ボタンで引き締める */
  color: white;
  border: none;
  padding: 16px 32px;
  border-radius: 30px;
  font-size: 1.0rem;
  font-weight: 700;
  cursor: pointer;
  transition: transform 0.2s;
  width: 100%;
}
.completion-btn:active { transform: scale(0.96); opacity: 0.9; }

@keyframes fadeIn {
  from { opacity: 0; }
  to { opacity: 1; }
}

@keyframes scaleIn {
  from { transform: scale(0.9); opacity: 1; }
  to { transform: scale(1); opacity: 1; }
}

/* Responsive */
@media (max-height: 750px) {
  body { padding: 12px; padding-bottom: 100px; }
  .header { margin-bottom: 10px; }
  .header h1 { font-size: 1.6rem; }
  .card { padding: 14px; margin-bottom: 10px; }
  .time-big { font-size: 3.5rem; }
  .status-badge { font-size: 0.8rem; padding: 4px 10px; }
  .action-btn { height: 56px; font-size: 1.1rem; }
}
</style>
</head>
<body>

<!-- VIEW: MAIN -->
<div id="view-main">
  <div class="header">
    <div style="display:flex; align-items:center;">
      <div class="conn-dot" id="conn-dot"></div>
      <h1>にぎにぎ</h1>
    </div>
    <button class="btn-icon" onclick="showSettings()">
      <span class="material-icons-round" style="font-size: 28px;">settings</span>
    </button>
  </div>

  <!-- 1. Monitor -->
  <div class="card card-monitor">
    <div class="monitor-row">
      <div class="status-badge" id="status-badge">待機中</div>
      <div class="time-big" id="time-display">--:--</div>
    </div>
    <div class="yt-progress-container">
      <div class="yt-progress-fill" id="yt-fill"></div>
    </div>
  </div>

  <!-- 2. Preset -->
  <div class="card card-preset">
    <h3>プリセット</h3>
    <div class="preset-grid" style="grid-template-columns: 1fr 1fr 1fr;">
      <div class="preset-btn" onclick="setPreset('soft',this)">やわらか</div>
      <div class="preset-btn active" onclick="setPreset('normal',this)">ふつう</div>
      <div class="preset-btn" onclick="setPreset('kosen',this)">高専生用</div>
    </div>
  </div>

  <!-- 3. Settings (Basic) -->
  <div class="card card-settings">
    <div class="setting-item">
      <div class="s-header">
        <span class="s-label">握りの強さ</span>
        <span class="s-val" id="str-disp">50%</span>
      </div>
      <input type="range" id="inp-str" min="0" max="100" value="50" oninput="updVal('str-disp', this.value, '%')">
    </div>
    
    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between; padding:16px 0;">
      <span class="s-label">回数</span>
      <div class="chk-group">
        <div class="chk-btn" onclick="setCount(1,this)">1</div>
        <div class="chk-btn" onclick="setCount(2,this)">2</div>
        <div class="chk-btn active" onclick="setCount(3,this)">3</div>
        <div class="chk-btn" onclick="setCount(4,this)">4</div>
      </div>
    </div>
  </div>

  <!-- Bottom Actions -->
  <div class="bottom-bar">
    <button class="action-btn btn-start" onclick="start()">
      <span class="material-icons-round">play_arrow</span>
      開始
    </button>
    <button class="action-btn btn-stop" onclick="stop()">
      <span class="material-icons-round">stop_circle</span>
      停止
    </button>
  </div>
</div>

<!-- VIEW: SETTINGS -->
<div id="view-settings" style="display:none; padding-bottom:40px;">
  <div class="header" style="display:flex; align-items:center; gap:10px;">
    <button onclick="showMain()" style="background:none; border:none; color:var(--text-main); cursor:pointer; padding:0;">
      <span class="material-icons-round" style="font-size:2rem;">arrow_back</span>
    </button>
    <h1>詳細設定</h1>
  </div>
  
  <div class="card card-settings">
    <div class="setting-item">
      <span class="s-label">システム情報</span>
      <div style="margin-top:8px; font-size:0.9rem; color:var(--text-sub);">
        <div>Build: <span style="font-family:monospace;">{{BUILD_TIME}}</span></div>
        <div>IP: <span style="font-family:monospace;" id="ip-disp">...</span></div>
      </div>
    </div>
    
    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between;">
      <span class="s-label">保持時間 (秒)</span>
      <input type="number" id="inp-hold" value="0.5" step="0.1" style="width:80px; padding:12px; border-radius:12px; border:1px solid #ddd; text-align:center; font-size:1.1rem; font-weight:700;" onchange="saveHold(this.value)">
    </div>

    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between;">
      <span class="s-label">到達時間 (秒)</span>
      <input type="number" id="inp-reach" value="0.5" step="0.1" style="width:80px; padding:12px; border-radius:12px; border:1px solid #ddd; text-align:center; font-size:1.1rem; font-weight:700;" onchange="saveReach(this.value)">
    </div>

    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between;">
      <span class="s-label">外部出力 (Pin 13)</span>
      <label class="switch">
        <input type="checkbox" id="chk-pin13" onchange="togglePin13(this)">
        <span class="slider round"></span>
      </label>
    </div>
    
    <div class="setting-item">
      <div class="s-header">
        <span class="s-label">手動操作 (0=開, 100=閉)</span>
        <span class="s-val" id="man-val">0%</span>
      </div>
      <input type="range" min="0" max="100" value="0" oninput="manualServo(this.value)">
    </div>
  </div>
</div>

<!-- Completion Modal -->
<div class="completion-modal" id="completion-modal">
  <div class="completion-content">
    <div class="completion-title">完成！</div>
    <div class="completion-details">
      <div class="detail-row">
        <span class="detail-label">プリセット</span>
        <span class="detail-value" id="detail-preset">-</span>
      </div>
      <div class="detail-row">
        <span class="detail-label">強さ</span>
        <span class="detail-value" id="detail-strength">-</span>
      </div>
      <div class="detail-row">
        <span class="detail-label">回数</span>
        <span class="detail-value" id="detail-count">-</span>
      </div>
    </div>
    <button class="completion-btn" onclick="closeCompletionModal()">OK</button>
  </div>
</div>

<script>
let tgtCount = 3;
let lastStatus = "IDLE";

// Animation Variables
let isRunning = false;
let isManualStop = false; 
let sessionTotalDur = 1.0; 
let sessionStartTime = 0;
let lastStartAction = 0; 

// 完了画面用
let runPreset = "";
let runStrength = 0;
let runCount = 0;

document.getElementById('ip-disp').innerText = window.location.hostname;

function fetchSettings() {
  fetch('/api/settings?load=1')
    .then(r=>r.json())
    .then(d=>{
      if(d.hold) document.getElementById('inp-hold').value = d.hold;
      if(d.reach) document.getElementById('inp-reach').value = d.reach;
      if(d.pin13 !== undefined) document.getElementById('chk-pin13').checked = (d.pin13 == 1);
      
      updTimeDisp();
      setTimeout(() => document.body.classList.add('ready'), 50);
    }).catch(e => {
        updTimeDisp();
        document.body.classList.add('ready');
    });
}
fetchSettings();

function saveHold(v) { fetch('/api/settings?hold=' + v).then(()=>updTimeDisp()); }
function saveReach(v) { fetch('/api/settings?reach=' + v).then(()=>updTimeDisp()); }
function togglePin13(el) { fetch('/api/pin13?val=' + (el.checked ? 1 : 0)); }

function manualServo(pct) {
  document.getElementById('man-val').innerText = pct + "%";
  fetch('/api/manual?val=' + pct);
}

function updVal(id, v, unit) { document.getElementById(id).innerText = v + unit; }
function fmtTime(s) {
  let min = Math.floor(s / 60);
  let sec = Math.floor(s % 60);
  return min + ":" + (sec < 10 ? "0" : "") + sec;
}

function updTimeDisp() {
  if (isRunning) return; 
  const h = parseFloat(document.getElementById('inp-hold').value) || 0.5;
  const r = parseFloat(document.getElementById('inp-reach').value) || 0.5;
  const total = tgtCount * (h + r + 0.3);
  document.getElementById('time-display').innerText = fmtTime(Math.ceil(total));
  sessionTotalDur = total;
}

function setCount(n, el) {
  tgtCount = n;
  document.querySelectorAll('.chk-btn').forEach(b => b.classList.remove('active'));
  el.classList.add('active');
  if(!isRunning) updTimeDisp();
}

function setPreset(mode, el) {
  document.querySelectorAll('.preset-btn').forEach(b => b.classList.remove('active'));
  el.classList.add('active');
  const s = document.getElementById('inp-str');
  if(mode==='soft') { s.value=30; }
  if(mode==='normal') { s.value=50; }
  if(mode==='kosen') { s.value=100; }
  updVal('str-disp', s.value, '%');
}

function showSettings() {
  document.getElementById('view-main').style.display = 'none';
  document.getElementById('view-settings').style.display = 'block';
}
function showMain() {
  document.getElementById('view-settings').style.display = 'none';
  document.getElementById('view-main').style.display = 'block';
}

function start() {
  const s = document.getElementById('inp-str').value;
  
  isManualStop = false;
  isRunning = true;
  document.body.classList.add('running');
  document.getElementById('status-badge').innerText = "準備中..."; 
  
  lastStartAction = Date.now();
  sessionStartTime = lastStartAction;
  
  const activePreset = document.querySelector('.preset-btn.active');
  runPreset = activePreset ? activePreset.innerText : 'カスタム';
  runStrength = s;
  runCount = tgtCount;

  const h = parseFloat(document.getElementById('inp-hold').value) || 0.5;
  const r = parseFloat(document.getElementById('inp-reach').value) || 0.5;
  sessionTotalDur = tgtCount * (h + r + 0.3);
  if(sessionTotalDur < 1) sessionTotalDur = 1;

  fetch(`/api/start?str=${s}&cnt=${tgtCount}`).catch(()=>{});
}

function stop() { 
  isManualStop = true;
  fetch('/api/stop').catch(()=>{}); 
}

function setOnline(isOnline) {
  if(isOnline) {
    document.body.classList.remove('offline');
  } else {
    document.body.classList.add('offline');
  }
}

// --- SMOOTH ANIMATION LOOP ---
function animateLoop() {
  if (isRunning && sessionTotalDur > 0) {
    const now = Date.now();
    const elapsedSec = (now - sessionStartTime) / 1000;
    const remaining = Math.max(0, sessionTotalDur - elapsedSec);
    
    document.getElementById('time-display').innerText = fmtTime(Math.ceil(remaining));

    let pct = (elapsedSec / sessionTotalDur) * 100;
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
    document.getElementById('yt-fill').style.width = pct + "%";
  }
  requestAnimationFrame(animateLoop);
}
requestAnimationFrame(animateLoop);

// --- SYNC WITH SERVER ---
function syncStatus() {
  fetch('/api/status')
    .then(r => r.json())
    .then(d => {
      setOnline(true);
      
      if(d.state !== 'IDLE') {
        if (!isRunning) {
          isRunning = true;
          document.body.classList.add('running');
          sessionStartTime = Date.now() - (d.elap || 0);
        }

        let txt = "動作中";
        if(d.state === 'PREPARE_SQUEEZE') txt = "準備中...";
        if(d.state === 'SQUEEZING') txt = "握り中";
        if(d.state === 'HOLDING') txt = "保持中";
        if(d.state === 'RELEASING') txt = "解放中";
        document.getElementById('status-badge').innerText = `${txt} (${d.cycle+1}/${d.total})`;

        sessionTotalDur = d.dur || 1; 
        const estimatedStart = Date.now() - (d.elap || 0);
        if (Math.abs(estimatedStart - sessionStartTime) > 500) {
           sessionStartTime = estimatedStart;
        }

      } else {
        if (isRunning) {
           if (Date.now() - lastStartAction >= 2000) {
             finishSession();
           }
        }
      }
      lastStatus = d.state;
    })
    .catch(e => {
      setOnline(false);
    });
}
setInterval(syncStatus, 1000);

function finishSession() {
  isRunning = false;
  document.body.classList.remove('running');
  document.getElementById('status-badge').innerText = "待機中";
  document.getElementById('yt-fill').style.width = '0%';
  updTimeDisp(); 
  
  if (!isManualStop) {
    showCompletionModal();
  }
}

function showCompletionModal() {
  const modal = document.getElementById('completion-modal');
  document.getElementById('detail-preset').innerText = runPreset;
  document.getElementById('detail-strength').innerText = runStrength + '%';
  document.getElementById('detail-count').innerText = runCount + '回';
  modal.classList.add('show');
}

function closeCompletionModal() {
  document.getElementById('completion-modal').classList.remove('show');
}
</script>
</body>
</html>
)rawliteral";

// --- 設定値 ---
const char* ssid     = "Extender-G-FA88";
const char* password = "jritucr4nff7u";

WebServer server(80);
Preferences preferences;

Servo servo1, servo2, servo3;
const int PIN_SERVO1 = 25;
const int PIN_SERVO2 = 26;
const int PIN_SERVO3 = 27;

// --- サーボ設定 (ここを調整) ---
// 一般的な270度サーボのパルス幅 (500us〜2500us)
// ※もし動きが逆（閉じるつもりで開く）なら、この数値を入れ替えてください
const int US_AT_0_DEG   = 500;   // 0度 (閉/強) のときのパルス幅
const int US_AT_270_DEG = 2500;  // 270度 (開/弱) のときのパルス幅

// 状態管理
enum State { IDLE, PREPARE_SQUEEZE, SQUEEZING, HOLDING, RELEASING, WAIT_CYCLE };
State currentState = IDLE;
State lastState = IDLE; 

unsigned long stateStartTime = 0;
unsigned long sessionStartTime = 0;

// パラメータ
float holdTimeSec = 0.5;
float reachTimeSec = 0.5;
int targetStrength = 50; // 0-100%
int targetCount = 3;
int currentCycle = 0;
int pin13State = 0;

// ヘルパー: 全サーボにパルス幅(us)を指定
void setAllServosUs(int us) {
    servo1.writeMicroseconds(us);
    servo2.writeMicroseconds(us);
    servo3.writeMicroseconds(us);
}

// ヘルパー: 角度(0-270)をパルス幅に変換して移動
void setAllServosAngle(int angle) {
    // 安全リミット
    if (angle < 0) angle = 0;
    if (angle > 270) angle = 270;
    
    // 0度=500us, 270度=2500us にマッピング
    int us = map(angle, 0, 270, US_AT_0_DEG, US_AT_270_DEG);
    setAllServosUs(us);
}

// ヘルパー: 強さ(0-100%)をパルス幅に変換
// 0%(弱) = 270度, 100%(強) = 0度
int strengthToUs(int strength) {
    if (strength < 0) strength = 0;
    if (strength > 100) strength = 100;
    
    // 強度0 -> 270度(US_AT_270_DEG)
    // 強度100 -> 0度(US_AT_0_DEG)
    return map(strength, 0, 100, US_AT_270_DEG, US_AT_0_DEG);
}

// API: Start
void handleApiStart() {
    if (server.hasArg("str")) targetStrength = server.arg("str").toInt();
    if (server.hasArg("cnt")) targetCount = server.arg("cnt").toInt();
    
    if (targetStrength > 100) targetStrength = 100;
    if (targetStrength < 0) targetStrength = 0;

    Serial.printf("[API] Start: Str=%d%%, Cnt=%d\n", targetStrength, targetCount);
    
    currentCycle = 0;
    sessionStartTime = millis();
    currentState = PREPARE_SQUEEZE; 
    
    server.send(200, "text/plain", "OK");
}

void handleApiStop() {
    Serial.println("[API] Stop");
    currentState = IDLE;
    // 停止時はデフォルト位置（270度）へ戻る
    setAllServosAngle(270);
    server.send(200, "text/plain", "OK");
}

void handleApiSettings() {
    if (server.hasArg("hold")) {
        holdTimeSec = server.arg("hold").toFloat();
        preferences.putFloat("hold", holdTimeSec);
    }
    if (server.hasArg("reach")) {
        reachTimeSec = server.arg("reach").toFloat();
        preferences.putFloat("reach", reachTimeSec);
    }
    if (server.hasArg("load")) {
        // 設定読み込み用（処理なし、下のJSONを返すだけ）
    }
    
    String json = "{";
    json += "\"hold\":" + String(holdTimeSec) + ",";
    json += "\"reach\":" + String(reachTimeSec) + ",";
    json += "\"pin13\":" + String(pin13State);
    json += "}";
    server.send(200, "application/json", json);
}

void handleApiPin13() {
    if (server.hasArg("val")) {
        pin13State = server.arg("val").toInt();
        digitalWrite(13, pin13State ? HIGH : LOW);
        preferences.putInt("pin13", pin13State);
    }
    server.send(200, "text/plain", "OK");
}

void handleApiStatus() {
    String s;
    switch (currentState) {
        case IDLE: s = "IDLE"; break;
        case PREPARE_SQUEEZE: s = "PREPARE_SQUEEZE"; break;
        case SQUEEZING: s = "SQUEEZING"; break;
        case HOLDING: s = "HOLDING"; break;
        case RELEASING: s = "RELEASING"; break;
        case WAIT_CYCLE: s = "WAIT_CYCLE"; break;
    }

    float cycleDur = reachTimeSec + holdTimeSec + 0.3; 
    float totalDur = targetCount * cycleDur;
    
    String json = "{";
    json += "\"state\":\"" + s + "\",";
    json += "\"cycle\":" + String(currentCycle) + ",";
    json += "\"total\":" + String(targetCount) + ",";
    json += "\"elap\":" + String(millis() - sessionStartTime) + ",";
    json += "\"pin13\":" + String(pin13State) + ",";
    json += "\"dur\":" + String(totalDur);
    json += "}";
    server.send(200, "application/json", json);
}

void handleApiManual() {
    if (server.hasArg("val")) {
        int pct = server.arg("val").toInt(); // 0(開) - 100(閉)
        if (pct < 0) pct = 0;
        if (pct > 100) pct = 100;

        // strengthToUs: 0% -> 270度(開), 100% -> 0度(閉)
        int targetUs = strengthToUs(pct);
        
        currentState = IDLE; // 自動モードをキャンセル
        setAllServosUs(targetUs);
        
        Serial.printf("[API] Manual: %d%% -> %dus\n", pct, targetUs);
    }
    server.send(200, "text/plain", "OK");
}

void handleRoot() {
    String html = html_main;
    html.replace("{{BUILD_TIME}}", __DATE__ " " __TIME__);
    server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    
    preferences.begin("job", false);
    holdTimeSec = preferences.getFloat("hold", 0.5);
    reachTimeSec = preferences.getFloat("reach", 0.5);
    pin13State = preferences.getInt("pin13", 0);
    
    pinMode(13, OUTPUT);
    digitalWrite(13, pin13State ? HIGH : LOW);
    
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    
    servo1.setPeriodHertz(50);
    servo2.setPeriodHertz(50);
    servo3.setPeriodHertz(50);
    
    // パルス幅設定してAttach
    servo1.attach(PIN_SERVO1, US_AT_0_DEG, US_AT_270_DEG);
    servo2.attach(PIN_SERVO2, US_AT_0_DEG, US_AT_270_DEG);
    servo3.attach(PIN_SERVO3, US_AT_0_DEG, US_AT_270_DEG);
    
    // ★起動時の初期位置: 270度 (開)
    setAllServosAngle(270);
    
    WiFi.begin(ssid, password);
    Serial.print("Connecting WiFi");
    int retry = 0;
    while (WiFi.status() != WL_CONNECTED && retry < 20) {
        delay(500);
        Serial.print(".");
        retry++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected.");
        Serial.print("IP: "); Serial.println(WiFi.localIP());
        configTime(9 * 3600, 0, "pool.ntp.org");
    } else {
        Serial.println("\nWiFi Connect Failed. Running offline.");
    }

    server.on("/", handleRoot);
    server.on("/api/status", handleApiStatus);
    server.on("/api/start", handleApiStart);
    server.on("/api/stop", handleApiStop);
    server.on("/api/settings", handleApiSettings);
    server.on("/api/pin13", handleApiPin13);
    server.on("/api/manual", handleApiManual);
    server.onNotFound([](){ server.send(404, "text/plain", "Not Found"); });

    server.begin();
    Serial.println("Ready.");
}

void loop() {
    server.handleClient();
    
    unsigned long now = millis();
    
    if (currentState != lastState) {
        stateStartTime = now;
        lastState = currentState;
        Serial.printf("State: %d\n", currentState);
    }

    switch (currentState) {
        case IDLE:
            break;

        case PREPARE_SQUEEZE:
            // 握る動作の前に「全開(270度)」にする
            setAllServosAngle(270);
            if (now - stateStartTime > 300) { // 物理的な移動待ち
                currentState = SQUEEZING;
            }
            break;
            
        case SQUEEZING:
            {
                unsigned long duration = reachTimeSec * 1000;
                unsigned long elapsed = now - stateStartTime;
                
                // 開始: 0%(270度), 終了: targetStrength%(0度に近い)
                int startUs = US_AT_270_DEG;
                int targetUs = strengthToUs(targetStrength);

                if (elapsed >= duration) {
                    setAllServosUs(targetUs);
                    currentState = HOLDING;
                } else {
                    float progress = (float)elapsed / (float)duration;
                    // イージング（滑らかに）
                    // progress = progress * progress * (3 - 2 * progress); 
                    
                    int currentUs = startUs + (targetUs - startUs) * progress;
                    setAllServosUs(currentUs);
                }
            }
            break;
            
        case HOLDING:
            if (now - stateStartTime >= (holdTimeSec * 1000)) {
                currentState = RELEASING;
            }
            break;
            
        case RELEASING:
            // 素早く全開(270度)に戻す
            setAllServosAngle(270);
            
            if (now - stateStartTime >= 300) {
                currentState = WAIT_CYCLE;
            }
            break;
            
        case WAIT_CYCLE:
            currentCycle++;
            if (currentCycle < targetCount) {
                currentState = SQUEEZING; 
            } else {
                Serial.println("Finished.");
                setAllServosAngle(270); // Final return to open
                currentState = IDLE;
            }
            break;
    }
}
