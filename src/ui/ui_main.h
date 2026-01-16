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
  width: 0%; 
  transition: width 0s linear; /* Dynamically set by JS */
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
.btn-start { background: var(--text-main); color: white; }
.btn-stop { background: var(--danger); color: white; display: none; } /* Red Stop Button */
.running .btn-start { display: none; }
.running .btn-stop { display: flex; } /* Keep Red */

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
      <span class="s-label">握り時間 (秒)</span>
      <input type="number" id="inp-reach" value="0.5" step="0.1" style="width:80px; padding:12px; border-radius:12px; border:1px solid #ddd; text-align:center; font-size:1.1rem; font-weight:700;" onchange="saveReach(this.value)">
    </div>
    
    <div class="setting-item">
      <div class="s-header">
        <span class="s-label">手動操作 (全サーボ)</span>
        <span class="s-val" id="man-val">270°</span>
      </div>
      <input type="range" min="0" max="270" value="270" style="direction:rtl;" oninput="manualServo(this.value)">
    </div>
  </div>
</div>

<script>
let isRunning = false;
let isSessionActive = false;
let tgtCount = 3;

document.getElementById('ip-disp').innerText = window.location.hostname;

function fetchSettings() {
  fetch('/api/settings?load=1')
    .then(r=>r.json())
    .then(d=>{
      if(d.hold) document.getElementById('inp-hold').value = d.hold;
      if(d.reach) document.getElementById('inp-reach').value = d.reach;
      updTimeDisp();
    });
}
fetchSettings();

function saveHold(v) { fetch('/api/settings?hold=' + v).then(()=>updTimeDisp()); }
function saveReach(v) { fetch('/api/settings?reach=' + v).then(()=>updTimeDisp()); }
function manualServo(v) {
  document.getElementById('man-val').innerText = v + "°";
  fetch('/api/manual?val=' + v);
}

function updVal(id, v, unit) { document.getElementById(id).innerText = v + unit; }
function fmtTime(s) {
  let min = Math.floor(s / 60);
  let sec = Math.floor(s % 60);
  return min + ":" + (sec < 10 ? "0" : "") + sec;
}

function updTimeDisp() {
  const h = parseFloat(document.getElementById('inp-hold').value) || 0.5;
  const r = parseFloat(document.getElementById('inp-reach').value) || 0.5;
  const total = tgtCount * (h + r + 0.3);
  document.getElementById('time-display').innerText = fmtTime(Math.ceil(total));
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
  if(mode==='hard') { s.value=80; }
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
  fetch(`/api/start?str=${s}&cnt=${tgtCount}`);
}
function stop() { fetch('/api/stop'); }

function syncStatus() {
  fetch('/api/status')
    .then(r => r.json())
    .then(d => {
      const st = d.state;
      const bar = document.getElementById('yt-fill');
      const timeDisp = document.getElementById('time-display');
      
      document.body.classList.remove('running');
      if(st !== 'IDLE') {
        document.body.classList.add('running');
        document.getElementById('status-badge').innerText = `成形中 (${d.cycle+1}/${d.total})`;
        isRunning = true;
        
        // Dynamic CSS Animation
        const elap = (d.elap || 0) / 1000;
        const total = d.dur || 1;
        const rem = Math.max(0, total - elap);
        const pct = (elap / total) * 100;
        
        if(!isSessionActive) {
           bar.style.transition = 'none';
           bar.style.width = pct + '%';
           setTimeout(() => {
             bar.style.transition = `width ${rem}s linear`;
             bar.style.width = '100%';
           }, 50);
           isSessionActive = true;
        }
        timeDisp.innerText = fmtTime(Math.ceil(rem));
      } else {
        document.getElementById('status-badge').innerText = "待機中";
        isRunning = false;
        if(isSessionActive) {
          bar.style.transition = 'width 0.3s ease-out';
          bar.style.width = '100%';
          isSessionActive = false;
        } else {
          bar.style.transition = 'none';
          bar.style.width = '0%';
          updTimeDisp();
        }
      }
    });
}
setInterval(syncStatus, 1000);
</script>
</body>
</html>
)rawliteral";

#endif
