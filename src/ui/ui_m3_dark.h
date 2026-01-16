#ifndef UI_Dark_H
#define UI_Dark_H

const char* html_dark = R"rawliteral(
<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>M3 Dark</title>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
<link href="https://fonts.googleapis.com/icon?family=Material+Icons+Round" rel="stylesheet">
<style>
:root {
  --bg: #000000; --surface: #1e1e1e; --primary: #d0bcff; --on-bg: #e6e1e5;
  --accent-green: #00ff41;
}
body { background: var(--bg); color: var(--on-bg); font-family: 'Roboto', sans-serif; margin: 0; padding: 20px; display: flex; flex-direction: column; height: 100vh; box-sizing: border-box;justify-content:center;}

.display-area {
  flex: 1; display: flex; flex-direction: column; align-items: center; justify-content: center;
  position: relative;
}
.circle-progress {
  width: 200px; height: 200px; border-radius: 50%; border: 4px solid #333;
  display: flex; align-items: center; justify-content: center;
  position: relative;
  box-shadow: 0 0 20px rgba(0,0,0,0.5);
  transition: box-shadow 0.3s;
}
.running .circle-progress { box-shadow: 0 0 40px rgba(208, 188, 255, 0.4); border-color: rgba(208, 188, 255, 0.2); }
.onigiri-emoji { font-size: 5rem; transition: transform 0.2s; }
.running .onigiri-emoji { animation: pulse 0.5s infinite alternate; }
@keyframes pulse { from{transform:scale(1);} to{transform:scale(1.1);} }

.controls {
  background: var(--surface); padding: 25px; border-radius: 28px 28px 0 0; margin: 0 -20px -20px;
}
.slider-group { margin-bottom: 25px; }
input[type=range] { width: 100%; accent-color: var(--primary); }

.btn-main {
  width: 100%; padding: 18px; border-radius: 50px; border: none;
  background: var(--primary); color: #381e72; font-weight: bold; font-size: 1.1rem;
  box-shadow: 0 4px 10px rgba(208, 188, 255, 0.3); transition: 0.2s;
}
.btn-main:active { transform: scale(0.98); box-shadow: 0 2px 5px rgba(208, 188, 255, 0.3); }

/* Completed */
body.done { background: #00210e; }
body.done .circle-progress { border-color: var(--accent-green); box-shadow: 0 0 50px var(--accent-green); }
body.done .onigiri-emoji { transform: scale(1.5) rotate(10deg); }
</style>
</head>
<body>

<div class="display-area" id="disp">
  <div class="circle-progress">
    <div class="onigiri-emoji">🍙</div>
  </div>
  <h2 id="status" style="margin-top:20px;">Ready</h2>
</div>

<div class="controls">
  <div class="slider-group">
    <div style="display:flex; justify-content:space-between; margin-bottom:10px;">
      <span>Power</span>
      <span id="pow">50</span>
    </div>
    <input type="range" min="0" max="100" value="50" oninput="document.getElementById('pow').innerText=this.value">
  </div>
  
  <button class="btn-main" onclick="toggle()" id="btn">START</button>
</div>

<script>
let running = false;
let t;

function toggle() {
  if(running) {
    // STOP
    running = false;
    clearTimeout(t);
    document.getElementById('disp').classList.remove('running');
    document.getElementById('btn').innerText = "START";
    document.getElementById('status').innerText = "Stopped";
    fetch('/api/stop');
  } else {
    // START
    running = true;
    document.body.className = '';
    document.getElementById('disp').classList.add('running');
    document.getElementById('btn').innerText = "STOP";
    document.getElementById('status').innerText = "Forming...";
    fetch('/api/start');
    
    t = setTimeout(() => {
      finish();
    }, 3000); // 3 sec demo
  }
}

function finish() {
  running = false;
  document.getElementById('disp').classList.remove('running');
  document.body.className = 'done';
  document.getElementById('status').innerText = "COMPLETED";
  document.getElementById('btn').innerText = "RESET";
  if(navigator.vibrate) navigator.vibrate(200);
}
</script>
</body>
</html>
)rawliteral";

#endif
