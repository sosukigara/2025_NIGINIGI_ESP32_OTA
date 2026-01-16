#ifndef UI_HUB_H
#define UI_HUB_H

const char* html_hub = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Material Hub</title>
  <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;500;700&display=swap" rel="stylesheet">
  <style>
    body { font-family: 'Roboto', sans-serif; background: #fdfcff; padding: 20px; display: flex; flex-direction: column; align-items: center; }
    h1 { color: #1a1c1e; margin-bottom: 30px; }
    .btn { 
      display: block; width: 100%; max-width: 340px; padding: 20px; margin-bottom: 16px;
      text-decoration: none; border-radius: 16px; font-weight: 500; font-size: 1.1rem;
      border: 1px solid transparent; transition: all 0.2s;
    }
    .btn:active { transform: scale(0.98); }
    
    .std { background: #eaddff; color: #21005d; }
    .dark { background: #303030; color: #fff; }
    .nat { background: #c4eed0; color: #00210e; }
    .btm { background: #e0e2ec; color: #001945; }
    .dash { background: #cce5ff; color: #001d32; }
    
    .desc { font-size: 0.85rem; display: block; opacity: 0.8; margin-top: 4px; font-weight:normal;}
  </style>
</head>
<body>
  <h1>Material Variations</h1>
  
  <a href="/standard" class="btn std">
    1. M3 Standard
    <span class="desc">Lavender / Default M3</span>
  </a>
  
  <a href="/dark" class="btn dark">
    2. Material Dark
    <span class="desc">OLED Black / Neon</span>
  </a>
  
  <a href="/nature" class="btn nat">
    3. Onigiri Nature
    <span class="desc">Green / Earth / Organic</span>
  </a>
  
  <a href="/bottom" class="btn btm">
    4. Bottom Sheet
    <span class="desc">Mobile App Style</span>
  </a>
  
  <a href="/dashboard" class="btn dash">
    5. Dashboard
    <span class="desc">Tech / Grid / Dense</span>
  </a>

</body>
</html>
)rawliteral";

#endif
