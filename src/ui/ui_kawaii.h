#ifndef UI_KAWAII_H
#define UI_KAWAII_H

const char* html_kawaii = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, maximum-scale=1.0">
<title>Kawaii Rice Ball</title>
<link href="https://fonts.googleapis.com/css2?family=M+PLUS+Rounded+1c:wght@800&display=swap" rel="stylesheet">
<style>
body { 
  background-color: #ffe4e1; 
  background-image: radial-gradient(#ffb6c1 15%, transparent 16%);
  background-size: 20px 20px;
  font-family: 'M PLUS Rounded 1c', sans-serif;
  text-align: center;
  overflow: hidden;
  user-select: none;
}
h1 { color: #ff69b4; text-shadow: 2px 2px 0 #fff; font-size: 2em; margin: 10px 0; }
.character { font-size: 100px; transition: transform 0.2s; display: inline-block; filter: drop-shadow(0 5px 0 rgba(0,0,0,0.1)); }
.character.shake { animation: shake 0.5s infinite; }
.character.jump { animation: jump 0.5s ease; }
@keyframes shake { 0% { transform: rotate(0deg); } 25% { transform: rotate(10deg); } 75% { transform: rotate(-10deg); } 100% { transform: rotate(0deg); } }
@keyframes jump { 0% { transform: scale(1); } 50% { transform: scale(1.5) translateY(-20px); } 100% { transform: scale(1); } }

.btn {
  background: #ff69b4; color: white; border: none; padding: 15px 40px; border-radius: 50px; font-size: 1.5em; font-family: inherit;
  box-shadow: 0 10px 0 #d14785, 0 15px 20px rgba(0,0,0,0.2);
  margin-top: 20px; transition: all 0.1s; cursor: pointer;
  position: relative; top: 0;
}
.btn:active { top: 10px; box-shadow: 0 0 0 #d14785, 0 0 0 rgba(0,0,0,0.2); }
.btn.stop { background: #ffaaaa; box-shadow: 0 10px 0 #cc8888; }
.btn.stop:active { box-shadow: 0 0 0 #cc8888; }

.clouds { position: absolute; top: 0; left: 0; width: 100%; height: 100%; pointer-events: none; z-index: -1; }
.cloud { position: absolute; background: white; border-radius: 50%; opacity: 0.8; animation: moveCloud 20s linear infinite; }
@keyframes moveCloud { from { transform: translateX(-100%); } to { transform: translateX(100vw); } }

.slider-container { background: white; padding: 20px; border-radius: 20px; margin: 20px; box-shadow: 0 5px 15px rgba(255,182,193,0.5); }
input[type=range] { width: 100%; accent-color: #ff69b4; }
</style>
</head>
<body>

<h1>Let's Cook!</h1>
<div class="character" id="char">🍙</div>
<p id="msg">Press Start!</p>

<div class="slider-container">
  <label>Power: <span id="pow">50</span>%</label>
  <input type="range" min="0" max="100" value="50" oninput="document.getElementById('pow').innerText=this.value">
</div>

<button class="btn" id="btn" onclick="toggle()">MAKE!</button>

<script>
let cooking = false;
let char = document.getElementById('char');
let btn = document.getElementById('btn');
let msg = document.getElementById('msg');

function toggle() {
  if (cooking) {
    // STOP
    cooking = false;
    char.classList.remove('shake');
    msg.innerText = "Stopped.";
    btn.innerText = "MAKE!";
    btn.classList.remove('stop');
    fetch('/api/stop');
  } else {
    // START
    cooking = true;
    char.innerText = "🍙";
    char.classList.add('shake');
    msg.innerText = "Cooking...";
    btn.innerText = "STOP";
    btn.classList.add('stop');
    fetch('/api/start');
    
    setTimeout(() => {
      if (cooking) finish();
    }, 3000);
  }
}

function finish() {
  cooking = false;
  char.classList.remove('shake');
  char.classList.add('jump');
  char.innerText = "✨🍙✨";
  msg.innerText = "YUMMY!";
  btn.innerText = "MAKE!";
  btn.classList.remove('stop');
  if(navigator.vibrate) navigator.vibrate([100,100,100]); // Rhythm
  setTimeout(() => char.classList.remove('jump'), 500);
}
</script>
</body>
</html>
)rawliteral";

#endif
