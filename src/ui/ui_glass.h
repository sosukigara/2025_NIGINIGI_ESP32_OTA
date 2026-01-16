#ifndef UI_GLASS_H
#define UI_GLASS_H

const char* html_glass = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no, maximum-scale=1.0">
<title>Glass UI</title>
<style>
body { 
  margin: 0; padding: 20px; height: 100vh;
  box-sizing: border-box;
  font-family: 'Segoe UI', sans-serif;
  color: white;
  background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
  display: flex; flex-direction: column; justify-content: center; align-items: center;
}
.glass {
  background: rgba(255, 255, 255, 0.1);
  backdrop-filter: blur(10px);
  -webkit-backdrop-filter: blur(10px);
  border-radius: 20px;
  border: 1px solid rgba(255, 255, 255, 0.2);
  padding: 30px;
  width: 100%; max-width: 320px;
  box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);
  text-align: center;
}
h2 { font-weight: 300; letter-spacing: 2px; margin-top: 0; }
.circle-loader {
  width: 100px; height: 100px; border-radius: 50%; border: 2px solid rgba(255,255,255,0.1);
  margin: 20px auto; position: relative;
  display: flex; justify-content: center; align-items: center;
  font-size: 1.5em; font-weight: bold;
}
.circle-loader::after {
  content: ''; position: absolute; top: -2px; left: -2px;
  width: 100px; height: 100px; border-radius: 50%;
  border: 2px solid transparent; border-top-color: #fff;
  transition: transform 0.2s linear;
  transform: rotate(0deg);
}
.spinning::after { animation: spin 1s linear infinite; }
@keyframes spin { 0%{transform: rotate(0deg);} 100%{transform: rotate(360deg);} }

input[type=range] {
  width: 100%; margin: 20px 0; -webkit-appearance: none; background: transparent;
}
input[type=range]::-webkit-slider-runnable-track {
  width: 100%; height: 6px; background: rgba(255,255,255,0.3); border-radius: 3px;
}
input[type=range]::-webkit-slider-thumb {
  -webkit-appearance: none; height: 20px; width: 20px; border-radius: 50%;
  background: white; margin-top: -7px; box-shadow: 0 0 10px rgba(0,0,0,0.2);
}

.btn {
  background: rgba(255,255,255,0.2); border: 1px solid rgba(255,255,255,0.4);
  color: white; padding: 15px 30px; border-radius: 30px;
  font-size: 1.1em; cursor: pointer; transition: 0.3s;
  width: 100%; margin-top: 10px;
}
.btn:hover { background: rgba(255,255,255,0.3); }
.btn:active { transform: scale(0.95); }

</style>
</head>
<body>

<div class="glass">
  <h2>ONIGIRI</h2>
  
  <div class="circle-loader" id="loader">
    <span id="pct">0%</span>
  </div>
  
  <div style="text-align:left; font-size:0.9em; margin-bottom:5px;">Strength</div>
  <input type="range" id="slider" min="0" max="100" value="50">
  
  <button class="btn" onclick="start()" id="btn">START FORMING</button>
</div>

<script>
let timer;
let p = 0;

function start() {
  let btn = document.getElementById('btn');
  let loader = document.getElementById('loader');
  
  if (btn.innerText === "RESET") {
    // Reset
    p = 0;
    document.getElementById('pct').innerText = "0%";
    btn.innerText = "START FORMING";
    return;
  }

  btn.innerText = "PROCESSING...";
  loader.classList.add('spinning');
  fetch('/api/start');
  
  // Fake process
  timer = setInterval(() => {
    p += 1;
    document.getElementById('pct').innerText = p + "%";
    if (p >= 100) {
      clearInterval(timer);
      loader.classList.remove('spinning');
      btn.innerText = "RESET";
      if(navigator.vibrate) navigator.vibrate(200);
      document.getElementById('pct').innerText = "OK";
    }
  }, 40);
}
</script>
</body>
</html>
)rawliteral";

#endif
