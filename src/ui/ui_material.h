#ifndef UI_MATERIAL_H
#define UI_MATERIAL_H

const char* html_material = R"rawliteral(
<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>Material You</title>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
<link href="https://fonts.googleapis.com/icon?family=Material+Icons+Round" rel="stylesheet">
<style>
:root {
  --md-sys-color-primary: #6750a4;
  --md-sys-color-on-primary: #ffffff;
  --md-sys-color-primary-container: #eaddff;
  --md-sys-color-on-primary-container: #21005d;
  --md-sys-color-surface: #fffbe6;
  --md-sys-color-surface-variant: #e7e0ec;
  --md-sys-color-on-surface: #1c1b1f;
  --md-sys-color-outline: #79747e;
  --md-sys-color-error: #b3261e;
  --md-sys-color-tertiary: #7d5260;
}
body { background: var(--md-sys-color-surface); color: var(--md-sys-color-on-surface); font-family: 'Roboto', sans-serif; margin: 0; padding: 20px; min-height: 100vh; box-sizing: border-box; display: flex; flex-direction: column; }

/* FAB (Floating Action Button) */
.fab-large {
  position: fixed; bottom: 30px; right: 20px; left: 20px; height: 80px; border-radius: 24px;
  background: var(--md-sys-color-primary-container); color: var(--md-sys-color-on-primary-container);
  border: none; font-size: 1.2rem; font-weight: 500; display: flex; align-items: center; justify-content: center; gap: 12px;
  box-shadow: 0 4px 8px 3px rgba(0,0,0,0.15); transition: all 0.3s cubic-bezier(0.2, 0.0, 0, 1.0); overflow: hidden;
}
.fab-large:active { transform: scale(0.97); box-shadow: 0 2px 4px 2px rgba(0,0,0,0.15); }
.fab-large.running { background: var(--md-sys-color-primary); color: var(--md-sys-color-on-primary); width: 80px; left: calc(50% - 40px); border-radius: 40px; }
.fab-icon { font-family: 'Material Icons Round'; font-size: 32px; }

/* Status Card */
.status-card {
  background: var(--md-sys-color-surface-variant); color: var(--md-sys-color-on-surface);
  border-radius: 28px; padding: 30px; margin-bottom: 24px; text-align: center;
  position: relative; overflow: hidden; height: 180px; display: flex; flex-direction: column; justify-content: center; align-items: center;
}
.status-text { font-size: 2rem; font-weight: bold; z-index: 2; transition: opacity 0.3s; }
.progress-bar {
  position: absolute; bottom: 0; left: 0; height: 100%; width: 0%;
  background: rgba(103, 80, 164, 0.15); transition: width 0.1s linear; z-index: 1;
}
.onigiri-anim {
  font-size: 5rem; position: absolute; opacity: 0; transform: translateY(50px) scale(0.5); visibility: hidden;
}
.completed .onigiri-anim {
  visibility: visible; opacity: 1; transform: translateY(0) scale(1.2); transition: all 0.6s cubic-bezier(0.34, 1.56, 0.64, 1);
}
.completed .status-text { opacity: 0; }
.completed { background: #c4eed0; color: #00210e; }

/* Control Panel */
.control-panel { background: #fff; border-radius: 28px; padding: 24px; box-shadow: 0 1px 3px 1px rgba(0,0,0,0.1); }
h3 { margin: 0 0 20px 0; font-weight: 500; font-size: 1.1rem; }

/* Slider M3 */
.slider-container { margin-bottom: 30px; }
input[type=range] {
  -webkit-appearance: none; width: 100%; background: transparent; height: 40px;
}
input[type=range]::-webkit-slider-runnable-track {
  width: 100%; height: 16px; background: var(--md-sys-color-surface-variant); border-radius: 8px;
}
input[type=range]::-webkit-slider-thumb {
  -webkit-appearance: none; height: 24px; width: 24px;
  background: var(--md-sys-color-primary); border-radius: 50%;
  margin-top: -4px; box-shadow: 0 2px 4px 0 rgba(0,0,0,0.2); border: 2px solid white;
}

/* Chips */
.chips { display: flex; gap: 10px; overflow-x: auto; padding-bottom: 5px; }
.chip {
  padding: 0 16px; height: 32px; border-radius: 8px; border: 1px solid var(--md-sys-color-outline);
  background: transparent; font-weight: 500; font-family: inherit; color: var(--md-sys-color-on-surface);
  white-space: nowrap; display: flex; align-items: center;
}
.chip.selected { background: var(--md-sys-color-tertiary); color: white; border-color: transparent; }

/* Ripple */
.ripple { position: absolute; border-radius: 50%; background: rgba(255, 255, 255, 0.3); transform: scale(0); animation: ripple 0.6s linear; pointer-events: none; }
@keyframes ripple { to { transform: scale(4); opacity: 0; } }

</style>
</head>
<body>

<h1>Onigiri</h1>

<div class="status-card" id="card">
  <div class="progress-bar" id="prog"></div>
  <div class="status-text" id="status">Ready</div>
  <div class="onigiri-anim">🍙</div>
</div>

<div class="control-panel">
  <h3>Strength</h3>
  <div class="slider-container">
    <input type="range" min="0" max="100" value="50" id="slider" oninput="updateVal()">
  </div>
  <div class="chips">
    <button class="chip" onclick="setMode(1, this)">Soft</button>
    <button class="chip selected" onclick="setMode(2, this)">Normal</button>
    <button class="chip" onclick="setMode(3, this)">Hard</button>
  </div>
</div>

<button class="fab-large" id="mainBtn" onclick="toggle()">
  <span class="fab-icon">play_arrow</span>
  <span id="btnText">Start Forming</span>
</button>

<script>
let running = false;
let progress = 0;
let timer;

function toggle() {
  const btn = document.getElementById('mainBtn');
  const card = document.getElementById('card');
  
  if (running) {
    // STOP
    stopAction();
  } else {
    // START
    running = true;
    progress = 0;
    card.classList.remove('completed');
    btn.classList.add('running');
    btn.innerHTML = '<span class="fab-icon">stop</span>';
    document.getElementById('status').innerText = "Forming...";
    fetch('/api/start');
    
    timer = setInterval(() => {
      progress += 1;
      document.getElementById('prog').style.width = progress + '%';
      if (progress >= 100) {
        finishAction();
      }
    }, 40);
  }
}

function stopAction() {
  running = false;
  clearInterval(timer);
  const btn = document.getElementById('mainBtn');
  btn.classList.remove('running');
  btn.innerHTML = '<span class="fab-icon">play_arrow</span><span id="btnText">Start Forming</span>';
  document.getElementById('status').innerText = "Stopped";
  document.getElementById('prog').style.width = '0%';
  fetch('/api/stop');
}

function finishAction() {
  clearInterval(timer);
  running = false;
  const btn = document.getElementById('mainBtn');
  const card = document.getElementById('card');
  
  card.classList.add('completed');
  btn.classList.remove('running');
  btn.style.display = 'none'; // Hide button to focus on success
  
  if(navigator.vibrate) navigator.vibrate([100,50,100]);
  
  setTimeout(() => {
    btn.innerHTML = '<span class="fab-icon">play_arrow</span><span id="btnText">Make Another</span>';
    btn.style.display = 'flex';
    document.getElementById('status').innerText = "Ready";
    document.getElementById('prog').style.width = '0%';
    card.classList.remove('completed');
  }, 2500);
}

function setMode(n, el) {
  document.querySelectorAll('.chip').forEach(c => c.classList.remove('selected'));
  el.classList.add('selected');
  const s = document.getElementById('slider');
  if(n==1) s.value=30;
  if(n==2) s.value=50;
  if(n==3) s.value=80;
}
</script>
</body>
</html>
)rawliteral";

#endif
