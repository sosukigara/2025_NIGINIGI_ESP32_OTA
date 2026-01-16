#ifndef UI_Bottom_H
#define UI_Bottom_H

const char* html_bottom = R"rawliteral(
<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>Bottom Sheet</title>
<link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500&display=swap" rel="stylesheet">
<style>
body { background: #e0e2ec; font-family: 'Roboto', sans-serif; margin:0; height: 100vh; overflow:hidden; position:relative; }

/* Upper Visual Area */
.visual {
  height: 60vh; width: 100%; display: flex; align-items: center; justify-content: center;
  flex-direction: column;
}
.indicator {
  font-size: 8rem; transition: 0.5s cubic-bezier(0.4, 0, 0.2, 1);
  filter: drop-shadow(0 10px 10px rgba(0,0,0,0.1));
}
.status-label {
  margin-top: 20px; font-size: 2rem; color: #44474f; font-weight: bold; opacity: 0; transform: translateY(20px); transition: 0.5s;
}
.visual.active .indicator { transform: scale(1.5) rotate(-10deg); }
.visual.active .status-label { opacity: 1; transform: translateY(0); }

/* Bottom Sheet */
.sheet {
  position: absolute; bottom: 0; left: 0; width: 100%; height: 40vh;
  background: white; border-radius: 28px 28px 0 0;
  box-shadow: 0 -4px 20px rgba(0,0,0,0.1);
  padding: 30px; box-sizing: border-box;
  transition: transform 0.3s;
  display: flex; flex-direction: column; gap: 20px;
}
.sheet.closed { transform: translateY(280px); }

.handle {
  width: 40px; height: 4px; background: #74777f; border-radius: 2px;
  align-self: center; margin-bottom: 10px;
}

.btn-primary {
  width: 100%; padding: 18px; border-radius: 100px; border:none;
  background: #004a77; color: white; font-size: 1.1rem; font-weight: bold;
  margin-top: auto;
}
.slider-row { display: flex; align-items: center; gap: 15px; }
input { flex: 1; }
</style>
</head>
<body>

<div class="visual" id="vis">
  <div class="indicator">🍙</div>
  <div class="status-label">Completed!</div>
</div>

<div class="sheet" id="sheet">
  <div class="handle"></div>
  <h2 style="margin:0;">Configuration</h2>
  
  <div class="slider-row">
    <span>Force</span>
    <input type="range" min="0" max="100">
  </div>
  
  <button class="btn-primary" onclick="act()" id="btn">START</button>
</div>

<script>
let state = 0; // 0:Idle, 1:Run, 2:Done

function act() {
  if (state === 0) {
    // Start
    state = 1;
    document.getElementById('sheet').classList.add('closed');
    document.getElementById('vis').classList.add('active'); // Assume active state logic
    document.querySelector('.status-label').innerText = "Processing...";
    fetch('/api/start');
    
    setTimeout(() => {
      state = 2;
      document.querySelector('.status-label').innerText = "DONE!";
      document.querySelector('.indicator').innerText = "✨🍙✨";
      document.getElementById('btn').innerText = "RESET";
      document.getElementById('sheet').classList.remove('closed'); // Bring back sheet
      if(navigator.vibrate) navigator.vibrate(200);
    }, 2500);
  } else if (state === 2 || state === 1) {
    // Reset
    state = 0;
    document.getElementById('vis').classList.remove('active');
    document.querySelector('.status-label').innerText = "";
    document.querySelector('.indicator').innerText = "🍙";
    document.getElementById('btn').innerText = "START";
    if (state===1) fetch('/api/stop');
  }
}
</script>
</body>
</html>
)rawliteral";

#endif
