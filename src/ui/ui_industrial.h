#ifndef UI_INDUSTRIAL_H
#define UI_INDUSTRIAL_H

const char* html_industrial = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>IND-PRO 3000</title>
<link href="https://fonts.googleapis.com/css2?family=Share+Tech+Mono&display=swap" rel="stylesheet">
<style>
body { background: #1a1a1a; color: #00ff41; font-family: 'Share Tech Mono', monospace; padding: 20px; text-transform: uppercase; }
h2 { border-bottom: 2px solid #555; padding-bottom: 5px; }
.panel { border: 2px solid #444; background: #222; padding: 15px; margin-bottom: 20px; box-shadow: inset 0 0 20px #000; }
.lcd { background: #001100; color: #00ff41; border: 1px solid #004400; padding: 10px; font-size: 24px; text-align: right; box-shadow: inset 0 0 5px #00ff41; text-shadow: 0 0 5px #00ff41; margin-bottom: 10px; }
.btn { width: 100%; padding: 15px; margin: 5px 0; border: 1px solid #666; font-family: inherit; font-size: 18px; cursor: pointer; transition: 0.1s; }
.btn-start { background: #003300; color: #0f0; border-color: #0f0; }
.btn-start:active { background: #0f0; color: #000; }
.btn-emergency { background: repeating-linear-gradient(45deg, #300, #300 10px, #500 10px, #500 20px); color: red; border: 2px solid red; font-weight: bold; }
.btn-emergency:active { background: red; color: white; }
.toggle-group { display: flex; gap: 5px; }
.toggle-group .btn { flex: 1; font-size: 14px; background: #333; color: #888; }
.toggle-group .btn.active { background: #00ff41; color: #000; box-shadow: 0 0 10px #00ff41; }
input[type=range] { width: 100%; -webkit-appearance: none; background: transparent; }
input[type=range]::-webkit-slider-track { height: 10px; background: #333; border: 1px solid #555; }
input[type=range]::-webkit-slider-thumb { -webkit-appearance: none; height: 20px; width: 10px; background: #00ff41; border: 1px solid #000; margin-top: -6px; }
.status-led { width: 20px; height: 20px; border-radius: 50%; background: #300; display: inline-block; margin-right: 10px; border: 2px solid #555; }
.status-led.on { background: #f00; box-shadow: 0 0 10px #f00; }
.status-led.green { background: #030; }
.status-led.green.on { background: #0f0; box-shadow: 0 0 10px #0f0; }
</style>
</head>
<body>

<h2>system: ONIGIRI_MK3</h2>

<div class="panel">
  <div>STATUS_MONITOR</div>
  <div class="lcd" id="timer">00.00 s</div>
  <div><span class="status-led green" id="led-run"></span>RUNNING</div>
  <div><span class="status-led" id="led-err"></span>ERROR</div>
  <div>ANGLE: <span id="val-angle">000</span> deg</div>
  <div>FORCE: <span id="val-force">050</span> %</div>
</div>

<div class="panel">
  <div>MANUAL_OVERRIDE</div>
  <input type="range" min="0" max="100" value="50" id="slider" oninput="update()">
  <div class="toggle-group">
    <button class="btn" onclick="mode(1)">LOW</button>
    <button class="btn active" onclick="mode(2)">MED</button>
    <button class="btn" onclick="mode(3)">HIGH</button>
  </div>
</div>

<button class="btn btn-start" onclick="exec()">[ EXECUTE SEQUENCE ]</button>
<button class="btn btn-emergency" onclick="abort()">!!! EMERGENCY STOP !!!</button>

<script>
let t = 0;
let running = false;
let interval;

function update() {
  document.getElementById('val-force').innerText = String(document.getElementById('slider').value).padStart(3, '0');
}

function exec() {
  if (running) return;
  running = true;
  document.getElementById('led-run').classList.add('on');
  fetch('/api/start');
  
  t = 0;
  interval = setInterval(() => {
    t += 0.05;
    document.getElementById('timer').innerText = t.toFixed(2) + " s";
    // Mock
    let ang = Math.floor(Math.sin(t*5) * 45 + 45);
    document.getElementById('val-angle').innerText = String(ang).padStart(3, '0');
    
    if (t >= 5.0) { // 5 sec operation
      stop();
    }
  }, 50);
}

function stop() {
  running = false;
  clearInterval(interval);
  document.getElementById('led-run').classList.remove('on');
  document.getElementById('timer').innerText = "COMPLETE";
  if(navigator.vibrate) navigator.vibrate(500);
}

function abort() {
  stop();
  document.getElementById('led-err').classList.add('on');
  document.getElementById('timer').innerText = "ABORTED";
  fetch('/api/stop');
  if(navigator.vibrate) navigator.vibrate([100,50,100,50,100]);
  setTimeout(() => document.getElementById('led-err').classList.remove('on'), 2000);
}

function mode(n) {
  let btns = document.querySelectorAll('.toggle-group .btn');
  btns.forEach(b => b.classList.remove('active'));
  btns[n-1].classList.add('active');
  document.getElementById('slider').value = n * 30;
  update();
}
</script>
</body>
</html>
)rawliteral";

#endif
