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
  margin: 0; padding: 20px;
  min-height: 100vh;
  box-sizing: border-box;
  -webkit-font-smoothing: antialiased;
  padding-bottom: 120px; /* Space for bottom bar */
}

/* Header */
.header { margin-bottom: 24px; padding-top: 10px; }
.header h1 {
  font-size: 2rem; font-weight: 800; margin: 0;
  letter-spacing: -0.02em;
}
.header-date { font-size: 0.9rem; color: var(--text-sub); font-weight: 600; margin-top: 4px; }

/* Cards Common */
.card {
  background: var(--card-bg);
  border-radius: var(--radius);
  padding: 20px;
  margin-bottom: 16px;
  box-shadow: var(--shadow);
  overflow: hidden;
}

/* 1. Status/Monitor Card (YouTube Style) */
.card-monitor {
  display: flex; flex-direction: column;
  position: relative;
  padding-bottom: 25px; /* Space for scrubber */
}
.monitor-row { 
  display: flex; 
  flex-direction: column; /* Stack vertically for centering */
  align-items: center;    /* Center horizontally */
  justify-content: center;
  gap: 12px;              /* Gap between badge and time */
  margin-bottom: 30px; 
}
.status-badge {
  background: #f2f2f7; color: var(--text-sub);
  padding: 6px 12px; border-radius: 20px;
  font-size: 0.9rem; font-weight: 700;
}
.running .status-badge { background: #fee2e2; color: var(--yt-red); }

.time-big {
  font-size: 3.5rem; /* Made bigger since it's centered */
  font-weight: 800; 
  font-variant-numeric: tabular-nums; 
  letter-spacing: -2px;
  line-height: 1;
}

/* YouTube Style Progress Bar */
.yt-progress-container {
  width: 100%; height: 4px; border-radius: 2px;
  background: #e5e5ea; position: relative;
  cursor: default; /* No pointer cursor implies no interaction */
}
.yt-progress-fill {
  position: absolute; left: 0; top: 0; height: 100%;
  background: var(--yt-red); border-radius: 2px;
  width: 0%; transition: width 0.1s linear;
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
.card-preset h3 { margin: 0 0 16px 0; font-size: 1rem; color: var(--text-sub); text-transform: uppercase; letter-spacing: 0.05em; }
.preset-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; }
.preset-btn {
  background: var(--bg); border: 2px solid transparent;
  padding: 12px; border-radius: 12px;
  font-size: 0.95rem; font-weight: 700; color: var(--text-main);
  text-align: center; cursor: pointer; transition: 0.2s;
}
.preset-btn.active {
  background: #fff; border-color: var(--accent-blue); color: var(--accent-blue);
  box-shadow: 0 4px 10px rgba(0,122,255,0.15);
}

/* 3. Settings Card (List Style) */
.card-settings { padding: 20px; } /* Added padding for stacked layout */
.setting-item {
  padding: 12px 0;
  display: flex; flex-direction: column; /* Stacked for better control */
  border-bottom: 1px solid #f2f2f7;
}
.setting-item:last-child { border-bottom: none; }

.s-header {
  display: flex; justify-content: space-between; align-items: center;
  margin-bottom: 12px;
}
.s-label { font-size: 1rem; font-weight: 700; color: var(--text-main); }
.s-val { font-size: 1rem; font-weight: 700; color: var(--accent-purple); font-variant-numeric: tabular-nums; }

/* Custom Large Range Slider */
input[type=range] {
  -webkit-appearance: none;
  width: 100%;
  height: 44px; /* Large touch target */
  background: transparent;
  cursor: pointer;
  margin: 0;
}
input[type=range]:focus { outline: none; }

/* Track */
input[type=range]::-webkit-slider-runnable-track {
  width: 100%; height: 12px;
  background: #e5e5ea;
  border-radius: 6px;
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
  margin-top: -10px; /* Center on track: (12 - 32)/2 */
  transition: transform 0.1s;
}
input[type=range]:active::-webkit-slider-thumb { transform: scale(1.1); background: #f2f2f7; }

/* Grip Count Buttons */
.chk-group { display: flex; gap: 12px; justify-content: flex-end; }
.chk-btn {
  width: 48px; height: 48px; border-radius: 50%;
  background: #f2f2f7; color: var(--text-sub);
  display: flex; align-items: center; justify-content: center;
  font-size: 1.1rem; font-weight: 700;
  cursor: pointer; transition: 0.2s;
}
.chk-btn.active {
  background: var(--text-main); color: white;
  box-shadow: 0 4px 10px rgba(0,0,0,0.2); transform: scale(1.05);
}

/* Bottom Action Bar */
.bottom-bar {
  position: fixed; bottom: 30px; left: 20px; right: 20px;
  z-index: 100;
  display: flex; gap: 12px;
  filter: drop-shadow(0 10px 20px rgba(0,0,0,0.1));
}

.action-btn {
  flex: 1; height: 64px;
  border-radius: 32px; border: none;
  font-size: 1.1rem; font-weight: 800;
  display: flex; align-items: center; justify-content: center; gap: 8px;
  cursor: pointer; box-shadow: inset 0 1px 1px rgba(255,255,255,0.4);
  transition: transform 0.1s;
}
.action-btn:active { transform: scale(0.98); }

.btn-start { background: var(--text-main); color: white; }
.btn-stop { background: var(--bg); color: var(--danger); display: none; }
.running .btn-start { display: none; }
.running .btn-stop { display: flex; background: white; }

</style>
</head>
<body>
</style>
</head>
<body>

<!-- VIEW: MAIN -->
<div id="view-main">
  <div class="header">
    <h1>にぎにぎ</h1>
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

  <!-- Navigation to Advanced Settings -->
  <div class="card" onclick="showSettings()" style="padding:16px 20px; display:flex; justify-content:space-between; align-items:center; cursor:pointer; margin-bottom:120px;">
    <span style="font-weight:700; font-size:1rem; color:var(--text-main);">詳細設定</span>
    <span class="material-icons-round" style="color:var(--text-sub);">chevron_right</span>
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
  fetch('/api/start');
  curCount = 0;
  totalTime = tgtCount * 1.5;
  startTime = Date.now();
  updTimeDisp();
  loopT = setInterval(() => {
    let elapsed = (Date.now() - startTime) / 1000;
    let pct = Math.min((elapsed / totalTime) * 100, 100);
    document.getElementById('yt-fill').style.width = pct + "%";
    let rem = Math.max(0, Math.ceil(totalTime - elapsed));
    document.getElementById('time-display').innerText = fmtTime(rem);
    if(elapsed >= totalTime) finish();
  }, 50);
}

function stop() {
  if(navigator.vibrate) navigator.vibrate(50);
  isRunning = false;
  clearInterval(loopT);
  document.body.classList.remove('running');
  document.getElementById('status-badge').innerText = "一時停止";
  fetch('/api/stop');
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
