#ifndef UI_Standard_H
#define UI_Standard_H

const char* html_standard = R"rawliteral(
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
  
  --shadow: 0 4px 12px rgba(0,0,0,0.03);
  --radius: 16px;
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

/* 1. Status/Monitor Card (Simplified) */
.card-monitor {
  display: flex; flex-direction: column;
  position: relative;
}
.monitor-row { display: flex; align-items: center; justify-content: space-between; margin-bottom: 16px; }
.status-badge {
  background: #f2f2f7; color: var(--text-sub);
  padding: 6px 12px; border-radius: 20px;
  font-size: 0.8rem; font-weight: 700;
}
.running .status-badge { background: #e8f5e9; color: #2e7d32; }

.time-big {
  font-size: 2rem; font-weight: 800; font-variant-numeric: tabular-nums; letter-spacing: -1px;
}

.visualizer {
  height: 40px; display: flex; align-items: flex-end; gap: 4px; opacity: 0.3;
}
.running .visualizer { opacity: 1; }
.v-bar {
  flex: 1; background: var(--accent-purple); border-radius: 2px; height: 4px; transition: height 0.1s;
}

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
.card-settings { padding: 0; }
.setting-item {
  padding: 16px 20px;
  display: flex; align-items: center; justify-content: space-between;
  border-bottom: 1px solid #f2f2f7;
}
.setting-item:last-child { border-bottom: none; }
.s-label { font-size: 0.95rem; font-weight: 600; }
.s-val { font-weight: 700; color: var(--accent-purple); }

input[type=range] { width: 120px; accent-color: var(--accent-purple); }
.num-input {
  width: 50px; padding: 6px; border-radius: 8px; background: #f2f2f7;
  border: none; text-align: center; font-weight: 700; font-size: 1rem;
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

<div class="header">
  <div class="header-date">今日</div>
  <h1>おにぎり成形機</h1>
</div>

<!-- 1. Monitor -->
<div class="card card-monitor">
  <div class="monitor-row">
    <div class="status-badge" id="status-badge">待機中</div>
    <div class="time-big" id="time-display">10.0s</div>
  </div>
  <div class="visualizer" id="viz">
    <div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div>
    <div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div>
    <div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div>
    <div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div>
    <div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div><div class="v-bar"></div>
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
    <span class="s-label">握りの強さ</span>
    <div style="display:flex; align-items:center; gap:10px;">
      <input type="range" id="inp-str" min="0" max="100" value="50" oninput="updVal('str-disp', this.value)">
      <span class="s-val" id="str-disp">50%</span>
    </div>
  </div>
  
  <div class="setting-item">
    <span class="s-label">成形時間 (秒)</span>
    <input type="number" class="num-input" id="inp-time" value="10" min="1" max="60">
  </div>
  
  <div class="setting-item">
    <span class="s-label">作成個数</span>
    <input type="number" class="num-input" id="inp-count" value="1" min="1" max="3">
  </div>
</div>

<!-- Bottom Floating Actions -->
<div class="bottom-bar">
  <!-- Start Button -->
  <button class="action-btn btn-start" onclick="start()">
    <span class="material-icons-round">play_arrow</span>
    成形開始
  </button>
  
  <!-- Stop Button (Hidden by default) -->
  <button class="action-btn btn-stop" onclick="stop()">
    <span class="material-icons-round">stop_circle</span>
    停止
  </button>
</div>

<script>
let isRunning = false;
let loopT = null;
let startTime = 0;
let totalTime = 10;
let tgtCount = 0, curCount = 0;

function updVal(id, v) { document.getElementById(id).innerText = v + "%"; }

function setPreset(mode, el) {
  document.querySelectorAll('.preset-btn').forEach(b => b.classList.remove('active'));
  el.classList.add('active');
  const s = document.getElementById('inp-str');
  const t = document.getElementById('inp-time');
  const c = document.getElementById('inp-count');
  
  if(mode==='soft') { s.value=30; t.value=5; }
  if(mode==='normal') { s.value=50; t.value=10; }
  if(mode==='hard') { s.value=80; t.value=15; }
  if(mode==='kosen') { s.value=100; t.value=3; c.value=3; }
  
  updVal('str-disp', s.value);
}

function start() {
  if(navigator.vibrate) navigator.vibrate(50);
  isRunning = true;
  document.body.classList.add('running');
  document.getElementById('status-badge').innerText = "成形中...";
  fetch('/api/start');
  
  tgtCount = parseInt(document.getElementById('inp-count').value);
  curCount = 0;
  totalTime = parseInt(document.getElementById('inp-time').value);
  startTime = Date.now();
  
  loopT = setInterval(() => {
    let elapsed = (Date.now() - startTime) / 1000;
    let remain = Math.max(0, totalTime - elapsed);
    
    document.getElementById('time-display').innerText = remain.toFixed(1) + "s";
    
    // Viz
    let str = document.getElementById('inp-str').value;
    document.querySelectorAll('.v-bar').forEach(b => {
      b.style.height = (10 + Math.random() * str * 0.8) + "%";
    });
    
    if(remain <= 0) {
      curCount++;
      if(curCount < tgtCount) {
        startTime = Date.now();
      } else {
        finish();
      }
    }
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
  document.getElementById('status-badge').innerText = "完了";
  document.getElementById('time-display').innerText = "Done";
  if(navigator.vibrate) navigator.vibrate([200,100,200]);
}

// Init visualizer
document.querySelectorAll('.v-bar').forEach(b => b.style.height = "10%");
</script>
</body>
</html>
)rawliteral";

#endif
