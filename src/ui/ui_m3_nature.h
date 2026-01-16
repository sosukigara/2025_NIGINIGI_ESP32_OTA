#ifndef UI_Nature_H
#define UI_Nature_H

const char* html_nature = R"rawliteral(
<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
<title>Onigiri Nature</title>
<link href="https://fonts.googleapis.com/css2?family=Noto+Sans+JP:wght@400;700&display=swap" rel="stylesheet">
<style>
:root { --primary: #386a20; --on-primary: #ffffff; --bg: #fdfcf4; --surface: #f7fceb; }
body { background: var(--bg); color: #1a1c19; font-family: 'Noto Sans JP', sans-serif; margin:0; padding:20px; text-align:center; min-height:100vh; display:flex; flex-direction:column; align-items:center; }

h1 { color: var(--primary); font-size: 1.5rem; letter-spacing: 0.1em; }

.draw-area {
  width: 240px; height: 240px; background: #fff; border-radius: 50%;
  margin: 30px auto; position: relative;
  box-shadow: inset 0 0 40px rgba(56, 106, 32, 0.1);
  display: flex; align-items:center; justify-content:center;
}
.triangle {
  width: 0; height: 0; 
  border-left: 60px solid transparent; border-right: 60px solid transparent; border-bottom: 100px solid #cfeacc;
  transition: transform 0.2s cubic-bezier(0.175, 0.885, 0.32, 1.275);
  transform-origin: bottom center;
}
#nori {
  position: absolute; bottom: -10px; left: -20px; width: 40px; height: 30px; background: #222;
}

.card {
  background: var(--surface); padding: 20px; border-radius: 16px; width: 100%; max-width: 320px;
  box-shadow: 0 4px 6px rgba(0,0,0,0.05); margin-bottom: 20px; box-sizing: border-box;
}
.slider-wood {
  -webkit-appearance: none; width: 100%; height: 8px; background: #dcdcc0; border-radius: 4px;
}
.slider-wood::-webkit-slider-thumb {
  -webkit-appearance: none; width: 24px; height: 24px; background: var(--primary); border-radius: 50%;
}

.btn-leaf {
  background: var(--primary); color: var(--on-primary); border: none; padding: 16px 32px;
  border-radius: 20px 0 20px 0; font-size: 1.2rem; font-weight: bold; cursor: pointer;
  box-shadow: 0 4px 8px rgba(56, 106, 32, 0.3); transition: 0.2s;
}
.btn-leaf:active { transform: scale(0.95); border-radius: 10px; }

</style>
</head>
<body>

<h1>ONIGIRI MAKER</h1>

<div class="draw-area">
  <div class="triangle" id="rice">
    <div id="nori"></div>
  </div>
</div>

<div class="card">
  <p style="margin:0 0 10px 0; color:#555;">握りの強さ</p>
  <input type="range" class="slider-wood" min="50" max="150" value="100" oninput="upd(this.value)">
</div>

<button class="btn-leaf" onclick="start()" id="btn">握る</button>

<script>
function upd(v) {
  // Change shape based on slider
  let scale = v / 100;
  document.getElementById('rice').style.transform = `scaleY(${scale}) scaleX(${1/scale})`;
}

function start() {
  let b = document.getElementById('btn');
  if(b.innerText === "完了") {
    b.innerText = "握る";
    document.getElementById('rice').style.borderBottomColor = "#cfeacc";
    return;
  }
  
  b.innerText = "調理中...";
  fetch('/api/start');
  let rice = document.getElementById('rice');
  
  let i = 0;
  let t = setInterval(() => {
    i++;
    // Breathe animation
    let s = 1 + Math.sin(i/2)*0.1;
    rice.style.transform = `scale(${s})`;
    
    if(i > 20) {
      clearInterval(t);
      finish();
    }
  }, 100);
}

function finish() {
  document.getElementById('btn').innerText = "完了";
  document.getElementById('rice').style.transform = "scale(1)";
  document.getElementById('rice').style.borderBottomColor = "#aaddcc"; // Darker green
  if(navigator.vibrate) navigator.vibrate(200);
}
</script>
</body>
</html>
)rawliteral";

#endif
