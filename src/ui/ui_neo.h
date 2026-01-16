#ifndef UI_IOS_H
#define UI_IOS_H

const char* html_ios = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, viewport-fit=cover">
<title>Onigiri iOS</title>
<style>
:root {
  --ios-bg: #f2f2f7;
  --ios-card: #ffffff;
  --ios-blue: #007aff;
  --ios-green: #34c759;
  --ios-red: #ff3b30;
  --ios-gray: #8e8e93;
  --ios-separator: #c6c6c8;
}
body {
  background: var(--ios-bg);
  font-family: -apple-system, BlinkMacSystemFont, "SF Pro Text", "Helvetica Neue", sans-serif;
  margin: 0; padding: 20px;
  min-height: 100vh; box-sizing: border-box;
  -webkit-font-smoothing: antialiased;
}
h1 { font-size: 2.1rem; font-weight: 800; margin: 20px 0 10px; color: #000; letter-spacing: -0.5px; }
.subtitle { color: var(--ios-gray); font-size: 1.1rem; margin-bottom: 30px; font-weight: 500; }

.card {
  background: var(--ios-card);
  border-radius: 14px;
  padding: 0;
  margin-bottom: 20px;
  box-shadow: 0 4px 12px rgba(0,0,0,0.05);
  overflow: hidden;
}

.list-item {
  padding: 16px 20px;
  display: flex; align-items: center; justify-content: space-between;
  border-bottom: 1px solid var(--ios-separator);
}
.list-item:last-child { border-bottom: none; }
.list-item label { font-size: 1.05rem; font-weight: 400; color: #000; }

/* Status Display */
.status-display {
  text-align: center; padding: 40px 20px;
  transition: background 0.3s;
}
.status-display.active { background: #eef7ff; }
.timer { font-size: 4rem; font-weight: 200; font-variant-numeric: tabular-nums; letter-spacing: -2px; line-height: 1; }
.status-label { color: var(--ios-blue); font-weight: 600; text-transform: uppercase; font-size: 0.8rem; margin-bottom: 10px; letter-spacing: 1px; }

/* Slider iOS style */
input[type=range] {
  width: 100%; -webkit-appearance: none; background: transparent;
}
input[type=range]::-webkit-slider-runnable-track {
  width: 100%; height: 4px; background: #e5e5ea; border-radius: 2px;
}
input[type=range]::-webkit-slider-thumb {
  -webkit-appearance: none; height: 28px; width: 28px; background: #ffffff;
  border-radius: 50%; box-shadow: 0 2px 6px rgba(0,0,0,0.2); margin-top: -12px;
}

/* Segmented Control */
.segmented-control {
  display: flex; background: #e3e3e8; border-radius: 9px; padding: 2px; margin: 10px 20px;
}
.seg-btn {
  flex: 1; border: none; background: transparent; padding: 6px 0; border-radius: 7px;
  font-size: 0.9rem; font-weight: 500; color: #000; transition: 0.2s;
}
.seg-btn.selected { background: #fff; box-shadow: 0 1px 3px rgba(0,0,0,0.1); font-weight: 600; }

/* Main Button */
.main-btn {
  width: 100%; padding: 18px; border-radius: 14px; border: none;
  font-size: 1.1rem; font-weight: 600; cursor: pointer;
  background: var(--ios-blue); color: white;
  transition: transform 0.1s;
}
.main-btn:active { transform: scale(0.98); opacity: 0.9; }
.main-btn.stop { background: var(--ios-red); }

/* Modal/Alert */
.modal-overlay {
  position: fixed; top: 0; left: 0; width: 100%; height: 100%;
  background: rgba(0,0,0,0.4); backdrop-filter: blur(10px); -webkit-backdrop-filter: blur(10px);
  display: flex; justify-content: center; align-items: center;
  opacity: 0; pointer-events: none; transition: 0.3s;
}
.modal-overlay.show { opacity: 1; pointer-events: auto; }
.modal {
  width: 270px; background: rgba(240,240,240,0.9); border-radius: 14px;
  text-align: center; overflow: hidden;
}
.modal-content { padding: 20px; border-bottom: 1px solid rgba(0,0,0,0.1); }
.modal h3 { margin: 5px 0; }
.modal p { margin: 5px 0; font-size: 0.9rem; }
.modal-btn {
  padding: 12px; width: 100%; background: transparent; border: none;
  color: var(--ios-blue); font-size: 1.1rem; font-weight: 600; border-top: 1px solid rgba(0,0,0,0.05);
}

</style>
</head>
<body>

<h1>Onigiri</h1>
<div class="subtitle">Rice Ball Maker</div>

<div class="card status-display" id="displayBox">
  <div class="status-label" id="statusLabel">READY</div>
  <div class="timer" id="timer">00</div>
</div>

<div class="card">
  <div class="segmented-control">
    <button class="seg-btn" onclick="setMode(1, this)">Soft</button>
    <button class="seg-btn selected" onclick="setMode(2, this)">Normal</button>
    <button class="seg-btn" onclick="setMode(3, this)">Hard</button>
  </div>
  <div class="list-item">
    <label>Press Force</label>
    <div style="width: 60%;">
      <input type="range" id="slider" min="0" max="100" value="50">
    </div>
  </div>
</div>

<button class="main-btn" id="actionBtn" onclick="toggle()">Start</button>

<div class="modal-overlay" id="finishModal">
  <div class="modal">
    <div class="modal-content">
      <h3>Completed</h3>
      <p>Rice ball is ready!</p>
      <div style="font-size:3rem; margin:10px 0;">🍙</div>
    </div>
    <button class="modal-btn" onclick="closeModal()">OK</button>
  </div>
</div>

<script>
let running = false;
let count = 0;
let t;

function toggle() {
  const btn = document.getElementById('actionBtn');
  const display = document.getElementById('displayBox');
  const timerEl = document.getElementById('timer');
  
  if (running) {
    // STOP
    running = false;
    clearInterval(t);
    btn.classList.remove('stop');
    btn.innerText = "Start";
    document.getElementById('statusLabel').innerText = "STOPPED";
    display.classList.remove('active');
    fetch('/api/stop');
  } else {
    // START
    running = true;
    count = 0;
    btn.classList.add('stop');
    btn.innerText = "Stop";
    document.getElementById('statusLabel').innerText = "FORMING";
    display.classList.add('active');
    fetch('/api/start');
    
    t = setInterval(() => {
      count++;
      timerEl.innerText = count < 10 ? "0"+count : count;
      if (count >= 100) {
        finish();
      }
    }, 40);
  }
}

function finish() {
  running = false;
  clearInterval(t);
  document.getElementById('finishModal').classList.add('show');
  if(navigator.vibrate) navigator.vibrate(200);
  
  const btn = document.getElementById('actionBtn');
  btn.classList.remove('stop');
  btn.innerText = "Start";
  document.getElementById('statusLabel').innerText = "DONE";
  document.getElementById('displayBox').classList.remove('active');
}

function closeModal() {
  document.getElementById('finishModal').classList.remove('show');
  document.getElementById('timer').innerText = "00";
  document.getElementById('statusLabel').innerText = "READY";
}

function setMode(n, el) {
  document.querySelectorAll('.seg-btn').forEach(b => b.classList.remove('selected'));
  el.classList.add('selected');
  const sl = document.getElementById('slider');
  if(n==1) sl.value=30;
  if(n==2) sl.value=50;
  if(n==3) sl.value=80;
}
</script>
</body>
</html>
)rawliteral";

#endif
