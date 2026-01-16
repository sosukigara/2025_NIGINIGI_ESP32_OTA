#ifndef UI_Standard_H
#define UI_Standard_H

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
  
  --shadow: 0 4px 12px rgba(0,0,0,0.03);
  --radius: 16px;
}

/* Global Reset for Mobile App Feel */
* {
  -webkit-tap-highlight-color: transparent;
  user-select: none;
  -webkit-touch-callout: none;
}

body {
  background: var(--bg);
  color: var(--text-main);
  font-family: 'Inter', 'Noto Sans JP', sans-serif;
  margin: 0; padding: 20px; /* Consistent Equal Padding */
  min-height: 100vh;
  box-sizing: border-box;
  -webkit-font-smoothing: antialiased;
  padding-bottom: 120px;
}

/* Header */
.header { 
  margin-bottom: 20px; padding-top: 0; 
  display: flex; justify-content: space-between; align-items: center;
} 
.header h1 {
  font-size: 1.9rem; font-weight: 800; margin: 0;
  letter-spacing: -0.02em;
}
.btn-icon {
  background: none; border: none; padding: 8px; margin-right: -8px;
  color: var(--text-main); cursor: pointer; border-radius: 50%;
  display: flex; align-items: center; justify-content: center;
}
.btn-icon:active { background: rgba(0,0,0,0.05); }
.header-date { font-size: 0.9rem; color: var(--text-sub); font-weight: 600; margin-top: 4px; }

/* Cards Common */
.card {
  background: var(--card-bg);
  border-radius: var(--radius);
  padding: 20px; 
  margin-bottom: 20px; /* Equal spacing */
  box-shadow: var(--shadow);
  overflow: hidden;
}

/* 1. Status/Monitor Card (YouTube Style) */
.card-monitor {
  display: flex; flex-direction: column;
  position: relative;
  padding-bottom: 22px; 
}
.monitor-row { 
  display: flex; 
  flex-direction: column; 
  align-items: center;    
  justify-content: center;
  gap: 8px;              
  margin-bottom: 18px; /* Pull up */
}
.status-badge {
  background: #f2f2f7; color: var(--text-sub);
  padding: 6px 14px; border-radius: 24px;
  font-size: 0.9rem; font-weight: 700;
}
.running .status-badge { background: #fee2e2; color: var(--yt-red); }

.time-big {
  font-size: clamp(3.2rem, 16vw, 4.8rem); 
  font-weight: 800; 
  font-variant-numeric: tabular-nums; 
  letter-spacing: -2px;
  line-height: 1;
}

/* YouTube Style Progress Bar */
.yt-progress-container {
  width: 100%; height: 8px; 
  background: #e5e5ea; position: relative;
  cursor: default; 
}
.yt-progress-fill {
  position: absolute; left: 0; top: 0; height: 100%;
  background: var(--yt-red); border-radius: 4px;
  width: 0%; /* No transition for JS animation */
}
.yt-scrubber {
  position: absolute; right: -6px; top: 50%; width: 12px; height: 12px;
  background: var(--yt-red); border-radius: 50%;
  transform: translateY(-50%) scale(0); 
  box-shadow: 0 2px 4px rgba(0,0,0,0.2);
  transition: transform 0.2s cubic-bezier(0.34, 1.56, 0.64, 1);
}
.card-monitor:hover .yt-scrubber, .running .yt-scrubber { transform: translateY(-50%) scale(1); }


/* 2. Preset Card (Simplified) */
.card-preset h3 { margin: 0 0 10px 0; font-size: 1rem; color: var(--text-sub); text-transform: uppercase; letter-spacing: 0.05em; }
.preset-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; }
.preset-btn {
  background: var(--bg); border: 2px solid transparent;
  padding: 14px; border-radius: 14px;
  font-size: 1rem; font-weight: 700; color: var(--text-main);
  text-align: center; cursor: pointer; transition: 0.2s;
}
.preset-btn.active {
  background: #fff; border-color: var(--accent-blue); color: var(--accent-blue);
  box-shadow: 0 4px 10px rgba(0,122,255,0.15);
}

/* 3. Settings Card (List Style) */
.card-settings { padding: 18px; } 
.setting-item {
  padding: 12px 0; 
  display: flex; flex-direction: column; 
  border-bottom: 1px solid #f2f2f7;
}
.setting-item:last-child { border-bottom: none; }

.s-header {
  display: flex; justify-content: space-between; align-items: center;
  margin-bottom: 10px;
}
.s-label { font-size: 1rem; font-weight: 700; color: var(--text-main); }
.s-val { font-size: 1.1rem; font-weight: 700; color: var(--accent-purple); font-variant-numeric: tabular-nums; }

/* Custom Large Range Slider */
input[type=range] {
  -webkit-appearance: none;
  width: 100%;
  height: 44px; 
  background: transparent;
  cursor: pointer;
  margin: 0;
}
input[type=range]:focus { outline: none; }

/* Track */
input[type=range]::-webkit-slider-runnable-track {
  width: 100%; height: 14px;
  background: #e5e5ea;
  border-radius: 7px;
  border: none;
}
/* Thumb */
input[type=range]::-webkit-slider-thumb {
  -webkit-appearance: none;
  height: 32px; width: 32px;
  border-radius: 50%;
  background: #ffffff;
  border: 0.5px solid rgba(0,0,0,0.04);
  box-shadow: 0 4px 10px rgba(0,0,0,0.15);
  margin-top: -9px; 
  transition: transform 0.1s;
}
input[type=range]:active::-webkit-slider-thumb { transform: scale(1.1); background: #f2f2f7; }

/* Grip Count Buttons */
.chk-group { display: flex; gap: 10px; justify-content: flex-end; }
.chk-btn {
  width: 48px; height: 48px; 
  border-radius: 50%;
  background: #f2f2f7; color: var(--text-sub);
  display: flex; align-items: center; justify-content: center;
  font-size: 1.2rem; font-weight: 700;
  cursor: pointer; transition: 0.2s;
}
.chk-btn.active {
  background: var(--text-main); color: white;
  box-shadow: 0 4px 10px rgba(0,0,0,0.2); transform: scale(1.05);
}

/* Bottom Action Bar */
.bottom-bar {
  position: fixed; bottom: 30px; left: 18px; right: 18px;
  z-index: 100;
  display: flex; gap: 12px;
  filter: drop-shadow(0 10px 20px rgba(0,0,0,0.1));
}

.action-btn {
  flex: 1; height: 68px; 
  border-radius: 34px; border: none;
  font-size: 1.2rem; font-weight: 800;
  display: flex; align-items: center; justify-content: center; gap: 8px;
  cursor: pointer; box-shadow: inset 0 1px 1px rgba(255,255,255,0.4);
  transition: transform 0.1s;
}
.action-btn:active { transform: scale(0.98); }

.btn-start { background: var(--text-main); color: white; }
.btn-stop { background: var(--danger); color: white; display: none; }
.btn-resume { background: var(--accent-blue); color: white; display: none; }
.btn-cancel { background: var(--text-sub); color: white; display: none; }

/* State: Running */
.running .btn-start { display: none; }
.running .btn-stop { display: flex; }

/* State: Paused */
.paused .btn-start { display: none; }
.paused .btn-stop { display: none; }
.paused .btn-resume { display: flex; }
.paused .btn-cancel { display: flex; }

/* Responsive Compact Mode for Small Screens */
@media (max-height: 750px) {
  body { padding: 12px; padding-bottom: 100px; }
  .header { margin-bottom: 10px; }
  .header h1 { font-size: 1.6rem; }
  .btn-icon span { font-size: 24px !important; }
  
  .card { padding: 14px; margin-bottom: 10px; }
  
  .card-monitor { padding-bottom: 16px; }
  .monitor-row { gap: 4px; margin-bottom: 12px; }
  .time-big { font-size: 3.5rem; }
  .status-badge { font-size: 0.8rem; padding: 4px 10px; }
  
  .card-preset h3 { margin-bottom: 8px; font-size: 0.9rem; }
  .preset-btn { padding: 10px; font-size: 0.95rem; }
  
  .card-settings { padding: 14px; }
  .setting-item { padding: 8px 0; }
  input[type=range] { height: 36px; }
  input[type=range]::-webkit-slider-thumb { width: 26px; height: 26px; margin-top: -8px; }
  
  .bottom-bar { bottom: 16px; left: 12px; right: 12px; }
  .action-btn { height: 56px; font-size: 1.1rem; }
}

/* Toggle Switch */
.switch {
  position: relative; display: inline-block; width: 50px; height: 28px;
}
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

</style>
</head>
<body>

<!-- VIEW: MAIN -->
<div id="view-main">
  <div class="header">
    <h1>にぎにぎ</h1>
    <button class="btn-icon" onclick="showSettings()">
      <span class="material-icons-round" style="font-size: 28px;">settings</span>
    </button>
  </div>

  <!-- 1. Monitor (YouTube Style) -->
  <div class="card card-monitor">
    <div class="monitor-row">
      <div class="status-badge" id="status-badge">待機中</div>
      <div class="time-big" id="time-display">0:00</div>
    </div>
    
    <!-- Progress Bar -->
    <div class="yt-progress-container">
      <div class="yt-progress-fill" id="yt-fill"></div>
    </div>
  </div>

  <!-- 2. Preset -->
  <div class="card card-preset">
    <h3>プリセット</h3>
    <div class="preset-grid">
      <div class="preset-btn" onclick="setPreset('soft',this)">やわらか</div>
      <div class="preset-btn active" onclick="setPreset('normal',this)">ふつう</div>
      <div class="preset-btn" onclick="setPreset('hard',this)">かため</div>
      <div class="preset-btn" onclick="setPreset('kosen',this)">高専生用</div>
    </div>
  </div>

  <!-- 3. Settings -->
  <div class="card card-settings">
    <div class="setting-item">
      <div class="s-header">
        <span class="s-label">握りの強さ</span>
        <span class="s-val" id="str-disp">50%</span>
      </div>
      <input type="range" id="inp-str" min="0" max="100" value="50" oninput="updVal('str-disp', this.value, '%')">
    </div>
    
    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between; padding:16px 0;">
      <span class="s-label">握り回数</span>
      <div class="chk-group">
        <div class="chk-btn" onclick="setCount(1,this)">1</div>
        <div class="chk-btn" onclick="setCount(2,this)">2</div>
        <div class="chk-btn active" onclick="setCount(3,this)">3</div>
        <div class="chk-btn" onclick="setCount(4,this)">4</div>
      </div>
    </div>
  </div>

  <!-- Navigation Removed (Moved to Header) -->

  <!-- Bottom Floating Actions -->
  <div class="bottom-bar">
    <button class="action-btn btn-start" onclick="start()">
      <span class="material-icons-round">play_arrow</span>
      成形開始
    </button>
    
    <button class="action-btn btn-stop" onclick="stop()">
      <span class="material-icons-round">stop_circle</span>
      停止
    </button>
    
    <button class="action-btn btn-cancel" onclick="cancel()">
      <span class="material-icons-round">close</span>
      中止
    </button>
    
    <button class="action-btn btn-resume" onclick="resume()">
      <span class="material-icons-round">play_arrow</span>
      再開
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
    
    <!-- Hold Time Setting -->
    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between;">
      <span class="s-label">保持時間 (秒)</span>
      <input type="number" id="inp-hold" value="0.5" step="0.1" style="width:80px; padding:12px; border-radius:12px; border:1px solid #ddd; text-align:center; font-size:1.1rem; font-weight:700;" onchange="saveHold(this.value)">
    </div>

    <!-- Reach Time Setting -->
    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between;">
      <span class="s-label">握り時間 (秒)</span>
      <input type="number" id="inp-reach" value="0.5" step="0.1" style="width:80px; padding:12px; border-radius:12px; border:1px solid #ddd; text-align:center; font-size:1.1rem; font-weight:700;" onchange="saveReach(this.value)">
    </div>

    <!-- Toggle Pin 13 -->
    <div class="setting-item" style="flex-direction:row; align-items:center; justify-content:space-between;">
      <span class="s-label">外部出力 (Pin 13)</span>
      <label class="switch">
        <input type="checkbox" id="chk-pin13" onchange="togglePin13(this)">
        <span class="slider round"></span>
      </label>
    </div>
    
    <!-- Manual Control -->
    <div class="setting-item">
      <div class="s-header">
        <span class="s-label">手動操作 (全サーボ)</span>
        <span class="s-val" id="man-val">270°</span>
      </div>
      <input type="range" min="0" max="270" value="270" style="direction:rtl;" oninput="manualServo(this.value)">
      <div style="font-size:0.8rem; color:#aaa; margin-top:4px;">※ 左(270°)=緩 / 右(0°)=強</div>
    </div>
  </div>
</div>

<!-- Completion Overlay -->
<div id="comp-overlay" style="position:fixed; inset:0; background:rgba(0,0,0,0.85); z-index:200; display:none; flex-direction:column; align-items:center; justify-content:center; color:white; opacity:0; transition:opacity 0.3s;">
  <div style="font-size:4rem; margin-bottom:20px;">🍙</div>
  <h2 style="font-size:2rem; margin:0 0 10px 0;">完成！</h2>
  <p style="color:#ddd;">美味しいおにぎりができました</p>
  <button onclick="closeOverlay()" style="margin-top:30px; padding:12px 30px; border-radius:30px; background:white; color:black; font-weight:800; border:none; font-size:1.1rem;">閉じる</button>
</div>

<script>
document.getElementById('ip-disp').innerText = window.location.hostname;

// Load Settings
fetch('/api/settings?load=1')
  .then(r=>r.json())
  .then(d=>{
    if(d.hold) document.getElementById('inp-hold').value = d.hold;
    if(d.reach) document.getElementById('inp-reach').value = d.reach;
    if(d.pin13 !== undefined) document.getElementById('chk-pin13').checked = (d.pin13 == 1);
  });

function saveHold(v) { fetch('/api/settings?hold=' + v); }
function saveReach(v) { fetch('/api/settings?reach=' + v); }
function togglePin13(el) { fetch('/api/pin13?val=' + (el.checked ? 1 : 0)); }

function manualServo(v) {
  document.getElementById('man-val').innerText = v + "°";
  fetch('/api/manual?val=' + v);
}

function showSettings() {
  document.getElementById('view-main').style.display = 'none';
  document.getElementById('view-settings').style.display = 'block';
  window.scrollTo(0,0);
}

function showMain() {
  document.getElementById('view-settings').style.display = 'none';
  document.getElementById('view-main').style.display = 'block';
}

let isRunning = false;
let loopT = null;
let startTime = 0;
let totalTime = 4.5;
let tgtCount = 3;
let curCount = 0;

function updVal(id, v, unit) { document.getElementById(id).innerText = v + unit; }

function calcTotal() { return Math.ceil(tgtCount * 1.5); }
function updTimeDisp() { document.getElementById('time-display').innerText = fmtTime(calcTotal()); }

function setCount(n, el) {
  tgtCount = n;
  document.querySelectorAll('.chk-btn').forEach(b => b.classList.remove('active'));
  el.classList.add('active');
  if(!isRunning) updTimeDisp();
}

function fmtTime(s) {
  let min = Math.floor(s / 60);
  let sec = Math.floor(s % 60);
  return min + ":" + (sec < 10 ? "0" : "") + sec;
}

function setPreset(mode, el) {
  document.querySelectorAll('.preset-btn').forEach(b => b.classList.remove('active'));
  el.classList.add('active');
  const s = document.getElementById('inp-str');
  if(mode==='soft') { s.value=30; }
  if(mode==='normal') { s.value=50; }
  if(mode==='hard') { s.value=80; }
  if(mode==='kosen') { s.value=100; }
  setCount(3, document.querySelectorAll('.chk-btn')[2]); 
  updVal('str-disp', s.value, '%');
}

function start() {
  if(navigator.vibrate) navigator.vibrate(50);
  isRunning = true;
  document.body.classList.add('running');
  document.getElementById('status-badge').innerText = "成形中";
  
  // Send Params
  let str = document.getElementById('inp-str').value;
  fetch('/api/start?str=' + str + '&cnt=' + tgtCount);
  
  // Optimistic update
  isRunning = true;
  totalTime = tgtCount * 1.5; // Approx
  updTimeDisp();
}

// Client-side Interpolation State
let lastState = null;
let lastSyncTime = 0;

// High-frequency Render Loop (60fps)
function render() {
  requestAnimationFrame(render);
  
  if(!lastState) return;
  if(!isRunning && lastState.state !== 'PAUSED') return;
  
  const d = lastState;
  const now = Date.now();
  const delta = now - lastSyncTime; // ms since last sync
  
  // Cycle Config
  let t_reach = d.reach;
  let t_hold = d.hold;
  let t_rel = 0.3; 
  let t_cycle = t_reach + t_hold + t_rel;
  
  let totalMs = d.total * t_cycle * 1000;
  let completedMs = d.cycle * t_cycle * 1000;
  
  // Intra-cycle project logic
  // We assume logic: Reach -> Hold -> Release
  // We can just add delta to the server's elapsed for this state
  // But wait, if state changes locally before server says so, it might jump.
  // For simple smoothing: just add delta to the total duration accumulator.
  
  // Base offset from state start
  let baseStateOffset = 0;
  if(d.state === 'HOLDING') baseStateOffset = t_reach * 1000;
  if(d.state === 'RELEASING' || d.state === 'WAIT_CYCLE') baseStateOffset = (t_reach + t_hold) * 1000;
  
  // Current position in cycle = BaseOffset + ServerElapsed + LocalDelta
  let currentCycleMs = baseStateOffset + d.elap + delta;
  
  // Clamp to cycle duration?
  // If we overshoot, we shouldn't show > 100% of cycle, but for total progress it implies next cycle.
  // Ideally we wait for server sync to flip cycle.
  // Just showing "smooth progress" is the goal.
  
  let currentTotalMs = completedMs + currentCycleMs;
  
  // Progress %
  let pct = Math.min((currentTotalMs / totalMs) * 100, 100);
  document.getElementById('yt-fill').style.width = pct + "%";
  
  // Time Display
  let remMs = Math.max(0, totalMs - currentTotalMs);
  let remSec = Math.ceil(remMs / 1000);
  document.getElementById('time-display').innerText = fmtTime(remSec);
}
requestAnimationFrame(render);

// Global Polling (Sync every 1s)
setInterval(() => {
  fetch('/api/status')
    .then(r=>r.json())
    .then(d => {
      // Sync Data
      lastState = d;
      lastSyncTime = Date.now();
      
      const st = d.state;
      document.body.classList.remove('running', 'paused');
      
      if(st === 'SQUEEZING' || st === 'HOLDING' || st === 'RELEASING' || st === 'WAIT_CYCLE') {
        document.body.classList.add('running');
        document.getElementById('status-badge').innerText = "成形中 (" + (d.cycle+1) + "/" + d.total + ")";
        isRunning = true;
      } else if (st === 'PAUSED') {
        document.body.classList.add('paused');
        document.getElementById('status-badge').innerText = "一時停止";
        isRunning = false;
        
        // Force update GUI once for paused state
        document.getElementById('yt-fill').style.width = getLastPct(d) + "%";
      } else {
        document.getElementById('status-badge').innerText = "待機中";
        isRunning = false;
        document.getElementById('yt-fill').style.width = "0%";
      }

      if(!isRunning && st === 'IDLE') {
          // Sync logic
      }
    });
}, 1000);

function getLastPct(d) {
  // Helper for static display
  let t_cycle = d.reach + d.hold + 0.3;
  let total = d.total * t_cycle;
  let cur = (d.cycle * t_cycle) + (d.elap/1000.0);
  if(d.state==='HOLDING') cur += d.reach;
  if(d.state==='RELEASING') cur += d.reach + d.hold;
  return Math.min((cur/total)*100, 100);
}

function stop() {
  if(navigator.vibrate) navigator.vibrate(50);
  fetch('/api/pause');
}

function resume() {
  if(navigator.vibrate) navigator.vibrate(50);
  fetch('/api/resume');
}

function cancel() {
  if(navigator.vibrate) navigator.vibrate(50);
  fetch('/api/cancel');
}

function finish() {
  stop();
  document.getElementById('status-badge').innerText = "成形完了";
  document.getElementById('time-display').innerText = fmtTime(0);
  document.getElementById('yt-fill').style.width = "100%";
  let ov = document.getElementById('comp-overlay');
  ov.style.display = 'flex';
  setTimeout(()=> ov.style.opacity = 1, 10);
  if(navigator.vibrate) navigator.vibrate([200,100,200,100,500]);
}

function closeOverlay() {
  let ov = document.getElementById('comp-overlay');
  ov.style.opacity = 0;
  setTimeout(()=> ov.style.display = 'none', 300);
  document.getElementById('yt-fill').style.width = "0%";
  updTimeDisp();
}

updTimeDisp();
</script>
</body>
</html>
)rawliteral";

#endif
