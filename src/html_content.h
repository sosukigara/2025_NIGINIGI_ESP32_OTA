const char* htmlPage = R"rawliteral(<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, viewport-fit=cover">
    <title>おにぎりにぎりき PRO</title>
    <!-- Fonts -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;700;900&family=Noto+Sans+JP:wght@400;700;900&family=Noto+Sans+Khmer:wght@400;700&display=swap" rel="stylesheet">
    
    <style>
        :root {
            --bg-color: #f2f2f7;
            --surface-color: #ffffff;
            --surface-light: #e5e5ea;
            --primary: #FF4B4B;
            --primary-glow: rgba(255, 75, 75, 0.25);
            --accent: #FF9F43;
            --text-main: #1c1c1e;
            --text-sub: #8e8e93;
            --success: #34c759;
            --warning: #ffcc00;
            --danger: #ff3b30;
            --card-radius: 20px;
            --btn-radius: 12px;
            --transition: all 0.3s cubic-bezier(0.25, 0.8, 0.25, 1);
        }

        body {
            margin: 0;
            background-color: var(--bg-color);
            color: var(--text-main);
            font-family: 'Inter', 'Noto Sans JP', 'Noto Sans Khmer', sans-serif;
            -webkit-font-smoothing: antialiased;
            -moz-osx-font-smoothing: grayscale;
            overflow-x: hidden;
            padding-bottom: 5.5rem;
            user-select: none;
            -webkit-user-select: none;
        }

        /* --- Header --- */
        header {
            padding: 15px 20px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            background: rgba(255, 255, 255, 0.85);
            backdrop-filter: blur(20px);
            position: sticky;
            top: 0;
            z-index: 100;
            border-bottom: 1px solid rgba(0,0,0,0.05);
        }

        .brand {
            font-size: 1.15rem;
            font-weight: 900;
            background: linear-gradient(135deg, var(--primary), var(--accent));
            background-clip: text;
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            letter-spacing: -0.5px;
            display: flex;
            align-items: center;
            gap: 10px;
            white-space: nowrap;
        }

        .status-badge {
            font-size: 0.7rem;
            padding: 4px 10px;
            background: var(--surface-light);
            border-radius: 20px;
            color: var(--success);
            display: flex;
            align-items: center;
            gap: 5px;
        }

        .status-dot {
            width: 8px;
            height: 8px;
            background: currentColor;
            border-radius: 50%;
            animation: pulse 2s infinite;
        }

        @keyframes pulse {
            0% { opacity: 1; transform: scale(1); }
            50% { opacity: 0.5; transform: scale(0.8); }
            100% { opacity: 1; transform: scale(1); }
        }

        /* --- Layout --- */
        .container {
            width: 100%;
            max-width: 500px;
            margin: 0 auto;
            padding: 1rem 1.25rem;
            box-sizing: border-box;
        }

        .section-title {
            font-size: 0.85rem;
            color: var(--text-sub);
            text-transform: uppercase;
            letter-spacing: 1px;
            margin: 25px 0 10px 0;
            display: flex;
            justify-content: space-between;
        }

        /* --- Hero / Main Action --- */
        .hero {
            text-align: center;
            margin: 20px 0 30px 0;
            position: relative;
        }

        .onigiri-btn {
            width: 220px;
            height: 200px;
            margin: 0 auto;
            background: #ffffff;
            clip-path: polygon(50% 0%, 100% 85%, 85% 100%, 15% 100%, 0% 85%);
            border-radius: 40px; /* Note: clip-path overrides this, using rounded polygon if possible */
            border: none;
            cursor: pointer;
            transition: var(--transition);
            box-shadow: 0 15px 35px rgba(0, 0, 0, 0.1);
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            padding-bottom: 30px;
            position: relative;
            overflow: hidden;
            border-bottom: 5px solid #e0e0e0;
        }

        /* Better Onigiri Shape with CSS Clip-path */
        .onigiri-btn {
            clip-path: path('M 110,10 C 140,10 210,140 210,160 C 210,190 170,200 110,200 C 50,200 10,190 10,160 C 10,140 80,10 110,10 Z');
            background: white;
            padding: 0;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
        }

        .onigiri-btn::after {
            content: '';
            position: absolute;
            bottom: 0;
            left: 50%;
            transform: translateX(-50%);
            width: 80px;
            height: 50px;
            background: #1c1c1e;
            border-radius: 8px 8px 0 0;
            z-index: 1;
        }

        .onigiri-btn:active {
            transform: scale(0.92) translateY(5px);
            box-shadow: 0 5px 15px rgba(0,0,0,0.2);
        }
        .onigiri-btn.animate {
            animation: pulse-click 0.5s cubic-bezier(0.175, 0.885, 0.32, 1.275);
        }
        @keyframes pulse-click {
            0% { transform: scale(1); }
            30% { transform: scale(0.9); }
            100% { transform: scale(1); }
        }

        .onigiri-btn .emoji {
            font-size: 3.5rem;
            margin-bottom: 5px;
            filter: drop-shadow(0 2px 4px rgba(0,0,0,0.1));
            position: relative;
            z-index: 2;
        }

        .onigiri-btn .text {
            font-size: 1.8rem;
            font-weight: 900;
            color: var(--text-main);
            position: relative;
            z-index: 2;
            letter-spacing: 4px;
            margin-top: -10px;
        }

        /* --- Icons (SVG) --- */
        .icon { width: 1.25rem; height: 1.25rem; fill: currentColor; }
        .icon-large { width: 2rem; height: 2rem; }

        /* --- Hero --- */
        .hero { text-align: center; margin: 20px 0 30px 0; }
        .squeeze-wrapper { position: relative; width: 200px; height: 200px; margin: 0 auto; }
        .squeeze-circle { width: 100%; height: 100%; border-radius: 50%; background: white; display: flex; align-items: center; justify-content: center; box-shadow: 0 10px 30px rgba(0,0,0,0.05); }
        .squeeze-btn {
            width: 190px; height: 175px;
            border-radius: 50% 50% 15% 15% / 100% 100% 20% 20%;
            border: 2px solid #efeff4; background: #ffffff; color: #333; cursor: pointer;
            transition: var(--transition); display: flex; flex-direction: column; align-items: center; 
            justify-content: flex-start; padding-top: 25px; gap: 10px; overflow: hidden; position: relative;
            box-shadow: 0 10px 30px rgba(0,0,0,0.06);
            -webkit-tap-highlight-color: transparent;
        }
        .squeeze-btn::after {
            content: ''; position: absolute; bottom: 0; left: 50%; transform: translateX(-50%); 
            width: 90px; height: 50px; background: #1c1c1e; border-radius: 4px 4px 0 0; z-index: 1;
        }
        .squeeze-btn:active { transform: scale(0.96); opacity: 0.95; }
        .squeeze-btn span { font-weight: 800; font-size: 1.15rem; color: #333; position: relative; z-index: 2; margin-top: 0; }
        .squeeze-btn .icon { color: var(--primary); position: relative; z-index: 2; width: 3rem; height: 3rem; flex-shrink: 0; }

        /* --- Cards & Buttons --- */
        .card { background: var(--surface-color); border-radius: var(--card-radius); padding: 18px; margin-bottom: 12px; border: 1px solid rgba(0,0,0,0.05); box-shadow: 0 4px 12px rgba(0,0,0,0.03); }
        .grid-4 { display: grid; grid-template-columns: repeat(4, 1fr); gap: 8px; }
        .grid-2 { display: grid; grid-template-columns: 1fr 1fr; gap: 12px; }
        .stat-card { text-align: center; padding: 15px; }
        .stat-value { font-size: 1.8rem; font-weight: 900; color: var(--primary); display: block; }
        .stat-label { font-size: 0.7rem; color: var(--text-sub); text-transform: uppercase; }
        .btn {
            background: var(--surface-light); border: none; color: var(--text-main); padding: 16px 12px; border-radius: var(--btn-radius); font-weight: 700; cursor: pointer; transition: var(--transition);
            display: flex; flex-direction: column; align-items: center; justify-content: center; gap: 5px; width: 100%; min-height: 56px;
            -webkit-tap-highlight-color: transparent;
        }
        .btn:active { transform: scale(0.95); opacity: 0.9; }
        .btn.active { background: var(--primary); color: white; box-shadow: 0 4px 15px var(--primary-glow); }
        
        /* Preset Colors */
        .btn[data-preset="soft"].active { background: linear-gradient(135deg, #FF9F43, #FFB167); }
        .btn[data-preset="normal"].active { background: linear-gradient(135deg, #FF4B4B, #FF7676); }
        .btn[data-preset="hard"].active { background: linear-gradient(135deg, #636e72, #2d3436); }
        .btn[data-preset="barikata"].active { background: linear-gradient(135deg, #2d3436, #000000); }

        .btn-small-text { font-size: 0.85rem; letter-spacing: 0.5px; }
        .btn-danger { background: var(--danger); color: white; font-weight: 800; box-shadow: 0 8px 20px rgba(255, 59, 48, 0.3); }

        /* --- Sliders --- */
        .range-wrapper { margin-top: 10px; }
        .range-header { display: flex; justify-content: space-between; align-items: flex-end; margin-bottom: 8px; font-size: 0.9rem; color: var(--text-sub); }
        .range-value { color: var(--primary); font-size: 2rem; font-weight: 900; font-family: 'Inter', sans-serif; line-height: 1; }
        input[type=range] { width: 100%; -webkit-appearance: none; appearance: none; background: transparent; }
        input[type=range]::-webkit-slider-thumb { -webkit-appearance: none; appearance: none; height: 28px; width: 28px; border-radius: 50%; background: var(--surface-color); border: 2px solid var(--text-main); margin-top: -12px; box-shadow: 0 4px 12px rgba(0,0,0,0.15); cursor: pointer; }
        input[type=range]::-webkit-slider-runnable-track { width: 100%; height: 6px; background: #e0e0e0; border-radius: 3px; }

        /* --- Toasts --- */
        #toast-container { position: fixed; top: 15px; left: 50%; transform: translateX(-50%); z-index: 1000; display: flex; flex-direction: column; gap: 8px; pointer-events: none; }
        .toast { background: rgba(0,0,0,0.85); color: white; padding: 10px 20px; border-radius: 20px; font-size: 0.85rem; backdrop-filter: blur(10px); animation: toastIn 0.3s forwards, toastOut 0.3s 2.7s forwards; }
        @keyframes toastIn { from { transform: translateY(-15px); opacity: 0; } to { transform: translateY(0); opacity: 1; } }
        @keyframes toastOut { from { transform: translateY(0); opacity: 1; } to { transform: translateY(-15px); opacity: 0; } }

        /* --- Nav --- */
        .bottom-nav { position: fixed; bottom: 0; width: 100%; background: rgba(255,255,255,0.95); backdrop-filter: blur(25px); display: flex; justify-content: space-around; padding: 10px 0 30px 0; border-top: 1px solid rgba(0,0,0,0.05); z-index: 200; box-shadow: 0 -5px 20px rgba(0,0,0,0.02); }
        .nav-item { color: var(--text-sub); text-align: center; font-size: 0.75rem; transition: var(--transition); flex: 1; display: flex; flex-direction: column; align-items: center; gap: 6px; cursor: pointer; position: relative; }
        .nav-item.active { color: var(--primary); font-weight: 800; }
        .nav-item .icon { width: 1.6rem; height: 1.6rem; transition: var(--transition); }
        .nav-item.active .icon { transform: translateY(-2px); filter: drop-shadow(0 4px 8px var(--primary-glow)); }
        .nav-item::after { content: ''; position: absolute; bottom: -8px; width: 4px; height: 4px; background: var(--primary); border-radius: 50%; opacity: 0; transition: var(--transition); }
        .nav-item.active::after { opacity: 1; transform: scale(1.5); }

        /* --- Overlays --- */
        .active-overlay { position: fixed; top: 0; left: 0; right: 0; bottom: 0; background: rgba(255,255,255,0.98); z-index: 500; display: none; align-items: center; justify-content: center; padding: 20px; backdrop-filter: blur(10px); }
        .active-overlay.visible { display: flex; animation: fadeIn 0.4s cubic-bezier(0.16, 1, 0.3, 1); }
        .overlay-content { width: 100%; max-width: 400px; text-align: center; }
        
        /* Circular Progress */
        .progress-ring-wrapper { position: relative; width: 240px; height: 240px; margin: 0 auto 30px; }
        .progress-ring { transform: rotate(-90deg); }
        .progress-ring__circle {
            transition: stroke-dashoffset 0.1s linear;
            stroke: var(--primary);
            stroke-linecap: round;
        }
        .progress-ring__background { stroke: #efeff4; }
        
        .timer-display { position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%); display: flex; flex-direction: column; align-items: center; }
        .timer-current { font-size: 4.5rem; font-weight: 900; color: var(--text-main); line-height: 1; }
        .timer-unit { font-size: 1.25rem; font-weight: 700; color: var(--text-sub); margin-top: 5px; }

        .progress-container { display: none; } /* Hide old linear progress */

        .hidden { display: none !important; }
        select { border: 1px solid #ddd; border-radius: 6px; padding: 5px; background: white; }
    </style>
</head>
<body>
    <!-- SVG Library -->
    <svg style="display:none">
        <symbol id="icon-house" viewBox="0 0 576 512"><path d="M575.8 255.5c0 18-15 32.1-32 32.1h-32l.7 160.2c0 25.5-20.6 46.1-46.1 46.1H354.1c-14.1 0-25.5-11.4-25.5-25.5V361.9c0-14.1-11.4-25.5-25.5-25.5h-32c-14.1 0-25.5 11.4-25.5 25.5v106.5c0 14.1-11.4 25.5-25.5 25.5H110c-25.5 0-46.1-20.6-46.1-46.1l.6-160.2H32c-17.1 0-32-14.1-32-32.1 0-9 3.5-17.5 9.9-24L252.1 6.1c11.6-11.6 30.4-11.6 42 0L565.9 231.5c6.4 6.5 9.9 15 9.9 24z"/></symbol>
        <symbol id="icon-chart" viewBox="0 0 448 512"><path d="M160 80c0-26.5 21.5-48 48-48h32c26.5 0 48 21.5 48 48v352c0 26.5-21.5 48-48 48h-32c-26.5 0-48-21.5-48-48V80zM0 272c0-26.5 21.5-48 48-48h32c26.5 0 48 21.5 48 48v160c0 26.5-21.5 48-48 48H48c-26.5 0-48-21.5-48-48V272zM368 176h32c26.5 0 48 21.5 48 48v208c0 26.5-21.5 48-48 48h-32c-26.5 0-48-21.5-48-48V224c0-26.5 21.5-48 48-48z"/></symbol>
        <symbol id="icon-gear" viewBox="0 0 512 512"><path d="M495.9 166.6c3.2 8.7 .5 18.4-6.4 24.6l-43.3 39.4c1.1 8.3 1.7 16.8 1.7 25.4s-.6 17.1-1.7 25.4l43.3 39.4c6.9 6.2 9.6 15.9 6.4 24.6l-44.6 122.1c-3.1 8.7-11.5 14.6-20.8 14.6c-2.4 0-4.8-.4-7.1-1.2l-54.7-19c-14.9 11.4-31.5 20.8-49.4 27.6l-10.3 56.4c-2 10.8-11.4 18.8-22.4 18.8h-89.2c-11 0-20.4-8-22.4-18.8l-10.3-56.4c-17.9-6.8-34.5-16.2-49.4-27.6l-54.7 19c-2.3 .8-4.7 1.2-7.1 1.2c-9.3 0-17.7-5.9-20.8-14.6l-44.6-122.1c-3.2-8.7-.5-18.4 6.4-24.6l43.3-39.4c-1.1-8.3-1.7-16.8-1.7-25.4s.6-17.1 1.7-25.4l-43.3-39.4c-6.9-6.2-9.6-15.9-6.4-24.6l44.6-122.1c3.1-8.7 11.5-14.6 20.8-14.6c2.4 0 4.8 .4 7.1 1.2l54.7 19c14.9-11.4 31.5-20.8 49.4-27.6l10.3-56.4c2-10.8 11.4-18.8 22.4-18.8h89.2c11 0 20.4 8 22.4 18.8l10.3 56.4c17.9 6.8 34.5-16.2 49.4-27.6l54.7-19c2.3-.8 4.7-1.2 7.1-1.2c9.3 0-17.7-5.9-20.8-14.6l44.6-122.1zM256 336a80 80 0 1 0 0-160 80 80 0 1 0 0 160z"/></symbol>
        <symbol id="icon-squeeze" viewBox="0 0 512 512"><path d="M128 32C92.7 32 64 60.7 64 96V313.7c-26.1 10.3-44.5 35.8-44.5 65.5V448c0 35.3 28.7 64 64 64h288c53 0 96-43 96-96s-43-96-96-96H352V96c0-35.3-28.7-64-64-64H128z"/></symbol>
        <symbol id="icon-pause" viewBox="0 0 448 512"><path d="M128 432c0 26.5-21.5 48-48 48s-48-21.5-48-48V80c0-26.5 21.5-48 48-48s48 21.5 48 48V432zm256 0c0 26.5-21.5 48-48 48s-48-21.5-48-48V80c0-26.5 21.5-48 48-48s48 21.5 48 48V432z"/></symbol>
        <symbol id="icon-stop" viewBox="0 0 448 512"><path d="M400 32H48C21.5 32 0 53.5 0 80v352c0 26.5 21.5 48 48 48h352c26.5 0 48-21.5 48-48V80c0-26.5-21.5-48-48-48z"/></symbol>
        <symbol id="icon-save" viewBox="0 0 448 512"><path d="M433.9 129.9l-83.9-83.9c-9.4-9.4-22.2-14.1-35.3-14.1h-20.7V176c0 17.7-14.3 32-32 32H96c-17.7 0-32-14.3-32-32V32H48C21.5 32 0 53.5 0 80v352c0 26.5 21.5 48 48 48h352c26.5 0 48-21.5 48-48V165.3c0-13.1-4.7-25.9-14.1-35.4zM352 432H96V288c0-17.7 14.3-32 32-32h192c17.7 0 32 14.3 32 32v144z"/></symbol>
    </svg>

    <div id="toast-container"></div>

    <header>
        <div class="brand">
            <div style="display:flex; flex-direction:column">
                <span data-i18n="brand1">おにぎりにぎりき</span>
                <span data-i18n="brand2">にぎにぎ</span>
            </div>
        </div>
        <div class="status-badge">
            <div class="status-dot"></div> <span data-i18n="status_ready">準備完了</span>
        </div>
    </header>

    <div class="container" id="main-view">
        <section class="hero">
            <button class="onigiri-btn" onclick="squeeze()">
                <div class="text" data-i18n="btn_squeeze">握る</div>
            </button>
        </section>

        <div class="section-title"><span data-i18n="hdr_presets">プリセット</span></div>
        <section class="grid-4" id="presetArea">
            <button class="btn active" data-preset="soft"><div class="btn-small-text" data-i18n="pst_soft">やわらか</div></button>
            <button class="btn" data-preset="normal"><div class="btn-small-text" data-i18n="pst_normal">ふつう</div></button>
            <button class="btn" data-preset="hard"><div class="btn-small-text" data-i18n="pst_hard">かため</div></button>
            <button class="btn" data-preset="barikata"><div class="btn-small-text" data-i18n="pst_barikata">ばりかた</div></button>
        </section>

        <div class="section-title" data-i18n="hdr_manual">手動調整</div>
        <section class="card">
            <div class="range-wrapper">
                <div class="range-header"><span data-i18n="lbl_strength_angle">強さ (角度)</span><span class="range-value" id="angleVal">180°</span></div>
                <input type="range" min="0" max="270" value="180" oninput="updateVal('angleVal', this.value+'°'); onManualChange()">
            </div>
            <div class="range-wrapper">
                <div class="range-header"><span data-i18n="lbl_duration">時間</span><span class="range-value" id="timeVal">3.0s</span></div>
                <input type="range" min="0.5" max="10" step="0.5" value="3.0" oninput="updateVal('timeVal', this.value+'s'); onManualChange()">
            </div>
        </section>
    </div>

    <div id="active-overlay" class="active-overlay">
        <div class="overlay-content">
            <div class="progress-ring-wrapper">
                <svg class="progress-ring" width="240" height="240">
                    <circle class="progress-ring__background" stroke-width="12" fill="transparent" r="108" cx="120" cy="120"/>
                    <circle id="progress-ring-circle" class="progress-ring__circle" stroke-width="12" fill="transparent" r="108" cx="120" cy="120"/>
                </svg>
                <div class="timer-display">
                    <div id="timer-current" class="timer-current">0.0</div>
                    <div class="timer-unit">SEC</div>
                </div>
            </div>
            <div class="card">
                <div style="display:flex; justify-content:space-between; align-items:center">
                    <div style="text-align:left">
                        <div style="font-size:0.75rem; color:var(--text-sub)" data-i18n="lbl_settings">設定</div>
                        <div id="active-preset-name" style="font-weight:900; color:var(--text-main); font-size:1.1rem">--</div>
                    </div>
                    <div id="connection-status-indicator" style="font-size:0.75rem; color:var(--success); display:flex; align-items:center; gap:5px">
                        <div class="status-dot" style="width:6px; height:6px; animation:none"></div>
                        CONNECTED
                    </div>
                </div>
            </div>
            <div style="display:grid; grid-template-columns:1fr 1fr; gap:12px; margin-top:20px">
                <button class="btn" id="pauseBtn" onclick="togglePause()" style="height:55px"><span data-i18n="btn_pause">一時停止</span></button>
                <button class="btn btn-danger" onclick="stopActive()" style="height:55px"><span data-i18n="btn_stop">中止</span></button>
            </div>
        </div>
    </div>

    <div id="result-overlay" class="active-overlay">
        <div class="overlay-content">
            <div style="color:var(--success); font-size:3rem; margin-bottom:10px">✓</div>
            <h2 data-i18n="msg_complete">完成しました！</h2>
            <div class="card" style="margin:20px 0">
                <div style="display:flex; justify-content:space-between; margin-bottom:5px">
                    <span data-i18n="lbl_type">種類</span> <span id="res-type">--</span>
                </div>
                <div style="display:flex; justify-content:space-between">
                    <span data-i18n="lbl_time">時間</span> <span id="res-time">--</span>
                </div>
            </div>
            <button class="btn active" onclick="closeResult()">OK</button>
        </div>
    </div>

    <div class="container hidden" id="data-view">
        <div class="section-title" data-i18n="hdr_stats">統計</div>
        <div class="grid-2">
            <div class="card stat-card">
                <span class="stat-label" data-i18n="lbl_total_count">総握り回数</span>
                <span class="stat-value" id="stat-total">0</span>
            </div>
            <div class="card stat-card">
                <span class="stat-label" data-i18n="lbl_avg_time">平均時間</span>
                <span class="stat-value" id="stat-avg">0.0<small style="font-size:0.8rem">s</small></span>
            </div>
        </div>

        <div class="section-title" data-i18n="hdr_history">履歴</div>
        <section class="card" style="padding:0">
            <ul id="history-list" style="list-style:none; padding:0; margin:0"></ul>
        </section>
    </div>

    <div class="container hidden" id="settings-view">
        <div class="section-title" data-i18n="hdr_basic_settings">基本設定</div>
        <section class="card">
            <div class="range-header">
                <span data-i18n="lbl_max_squeeze">最大制限 (安全)</span>
                <span class="range-value" id="limitVal">90°</span>
            </div>
            <input type="range" min="0" max="270" value="90" oninput="updateVal('limitVal', this.value+'°'); state.minLimit=this.value;">
            
            <div class="range-header" style="margin-top:20px">
                <span data-i18n="lbl_return_speed">戻り速度</span>
                <span class="range-value" id="speedVal">0.1s</span>
            </div>
            <input type="range" min="0.1" max="2.0" step="0.1" value="0.1" oninput="updateVal('speedVal', this.value+'s'); state.returnSpeed=this.value;">
        </section>
        
        <div class="section-title" data-i18n="hdr_advanced_settings">詳細設定 / デバッグ</div>
        <section class="card">
            <div class="range-header">
                <span data-i18n="lbl_servo_debug">サーボ手動位置</span>
                <span class="range-value" id="debugVal">270°</span>
            </div>
            <input type="range" min="0" max="270" value="270" oninput="updateVal('debugVal', this.value+'°'); sendDebug(this.value)">
            <p style="font-size:0.75rem; color:var(--danger); margin-top:8px; font-weight:600" data-i18n="msg_debug_warn">⚠ 注意: 即座に動作します</p>
        </section>

        <div class="section-title" data-i18n="hdr_system">システム</div>
        <section class="card">
            <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:15px">
                <span data-i18n="lbl_language" style="font-size:1rem; font-weight:600">言語 / Language</span>
                <select id="langSelect" onchange="changeLang(this.value)" style="padding:8px 15px; font-size:1rem">
                    <option value="ja">日本語</option>
                    <option value="km">ភាសាខ្មែរ</option>
                </select>
            </div>
            <div style="display:flex; justify-content:space-between; align-items:center; border-top:1px solid #eee; padding-top:15px; margin-bottom:15px">
                <span data-i18n="lbl_device_name" style="font-size:1rem; font-weight:600">SSID</span>
                <span id="deviceName" style="font-weight:700; color:var(--text-sub); font-size:1.1rem">--</span>
            </div>
            <div style="display:flex; justify-content:space-between; align-items:center; border-top:1px solid #eee; padding-top:15px; margin-bottom:15px">
                <span data-i18n="lbl_your_device" style="font-size:1rem; font-weight:600">あなたのデバイス</span>
                <span id="yourDevice" style="font-weight:700; color:var(--primary); font-size:1.1rem">--</span>
            </div>
            <div style="display:flex; justify-content:space-between; align-items:center; border-top:1px solid #eee; padding-top:15px">
                <span data-i18n="lbl_connected_devices" style="font-size:1rem; font-weight:600">接続デバイス数</span>
                <span id="deviceCount" style="font-weight:900; color:var(--primary); font-size:1.2rem">--</span>
            </div>
            <div id="deviceListWrapper" style="margin-top:10px; font-size:0.85rem; color:var(--text-sub); border-top:1px dashed #eee; padding-top:10px; display:none">
                <div style="font-weight:700; margin-bottom:5px" data-i18n="lbl_accessing_devices">アクセス中の一覧:</div>
                <div id="deviceList" style="display:flex; flex-wrap:wrap; gap:5px"></div>
            </div>
        </section>
        
        <div style="padding: 10px 0 20px">
            <button class="btn active" onclick="saveSettings()" style="height:60px; font-size:1.1rem; flex-direction:row; justify-content:center; gap:10px">
                <svg class="icon" style="width:1.5rem; height:1.5rem"><use href="#icon-save"/></svg>
                <span data-i18n="btn_save">設定を保存</span>
            </button>
        </div>
    </div>

    <nav class="bottom-nav">
        <div class="nav-item active" onclick="switchTab('main')"><svg class="icon"><use href="#icon-house"/></svg><span data-i18n="nav_control">操作</span></div>
        <div class="nav-item" onclick="switchTab('data')"><svg class="icon"><use href="#icon-chart"/></svg><span data-i18n="nav_data">データ</span></div>
        <div class="nav-item" onclick="switchTab('settings')"><svg class="icon"><use href="#icon-gear"/></svg><span data-i18n="nav_settings">設定</span></div>
    </nav>

    <script>
        const translations = {
            'ja': {
                'brand1': 'おにぎりにぎりき', 'brand2': 'にぎにぎ', 'status_ready': '準備完了',
                'lbl_settings': '設定', 'btn_pause': '一時停止', 'btn_resume': '再開', 'btn_stop': '中止',
                'msg_complete': '完成しました！', 'btn_squeeze': '握る', 'hdr_presets': 'プリセット',
                'pst_soft': 'やわらか', 'pst_normal': 'ふつう', 'pst_hard': 'かため', 'pst_barikata': 'ばりかた', 'pst_custom': 'カスタム',
                'hdr_manual': '手動調整', 'lbl_strength_angle': '強さ (角度)', 'lbl_duration': '時間',
                'hdr_history': '履歴', 'hdr_safety': '安全設定', 'lbl_max_squeeze': '最大制限',
                'hdr_debug': 'デバッグ', 'lbl_servo_debug': 'サーボ移動', 'msg_debug_warn': '注意: 即座に動作します',
                'hdr_system': 'システム', 'lbl_language': '言語', 'btn_save': '保存', 'nav_control': '操作',
                'nav_data': 'データ', 'nav_settings': '設定', 'lbl_connected_devices': '接続デバイス', 'lbl_type': '種類', 'lbl_time': '時間',
                'lbl_return_speed': '戻り速度', 'msg_save_ok': '保存しました', 'msg_lang_ok': '言語を変更しました', 'msg_stop_ok': '中止しました',
                'hdr_stats': '統計', 'lbl_total_count': '総握り回数', 'lbl_avg_time': '平均時間', 'hdr_basic_settings': '基本設定', 'hdr_advanced_settings': '詳細設定 / デバッグ', 'lbl_device_name': 'SSID (この機器)', 'lbl_your_device': 'あなたのデバイス', 'lbl_accessing_devices': 'アクセス中の端末'
            },
            'km': {
                'brand1': 'អ្នកផលិតអូនីហ្គីរី', 'brand2': 'ប្រូ', 'status_ready': 'រួចរាល់',
                'lbl_settings': 'កំណត់', 'btn_pause': 'ផ្អាក', 'btn_resume': 'បន្ត', 'btn_stop': 'ឈប់',
                'msg_complete': 'រួចរាល់!', 'btn_squeeze': 'ច្របាច់', 'hdr_presets': 'ការកំណត់ជាមុន',
                'pst_soft': 'ទន់', 'pst_normal': 'ធម្មតា', 'pst_hard': 'រឹង', 'pst_barikata': 'រឹងខ្លាំង', 'pst_custom': 'ផ្ទាល់ខ្លួន',
                'hdr_manual': 'ដោយដៃ', 'lbl_strength_angle': 'មុំ', 'lbl_duration': 'ពេល',
                'hdr_history': 'ប្រវត្តិ', 'hdr_safety': 'សុវត្ថិភាព', 'lbl_max_squeeze': 'ដែនកំណត់',
                'hdr_debug': 'Debug', 'lbl_servo_debug': 'មុំ Servo', 'msg_debug_warn': 'ប្រយ័ត្ន៖ រត់ភ្លាមៗ',
                'hdr_system': 'ប្រព័ន្ធ', 'lbl_language': 'ភាសា', 'btn_save': 'រក្សាទុក', 'nav_control': 'បញ្ជា',
                'nav_data': 'ទិន្នន័យ', 'nav_settings': 'កំណត់', 'lbl_connected_devices': 'ឧបករណ៍', 'lbl_type': 'ប្រភេទ', 'lbl_time': 'ពេល',
                'lbl_return_speed': 'ល្បឿនត្រឡប់', 'msg_save_ok': 'បានរក្សាទុក', 'msg_lang_ok': 'បានប្តូរភាសា', 'msg_stop_ok': 'បានឈប់',
                'hdr_stats': 'ស្ថិតិ', 'lbl_total_count': 'ចំនួនសរុប', 'lbl_avg_time': 'ពេលមធ្យម', 'hdr_basic_settings': 'ការកំណត់មូលដ្ឋាន', 'hdr_advanced_settings': 'ការកំណត់កម្រិតខ្ពស់', 'lbl_device_name': 'ឈ្មោះ AP', 'lbl_your_device': 'ឧបករណ៍របស់អ្នក', 'lbl_accessing_devices': 'ឧបករណ៍ក្នុងប្រព័ន្ធ'
            }
        };

        let state = { count: 0, totalDuration: 0, isSqueezing: false, angle: 180, duration: 3.0, activePresetName: 'normal', minLimit: 90, returnSpeed: 0.1, isPaused: false };
        let activeTimer = null, startTime = 0, currentLang = 'ja';
        const presets = { 'soft': { angle: 220, duration: 4.0 }, 'normal': { angle: 180, duration: 3.0 }, 'hard': { angle: 140, duration: 2.5 }, 'barikata': { angle: 100, duration: 2.0 } };

        document.addEventListener('DOMContentLoaded', () => {
            currentLang = localStorage.getItem('app_lang') || 'ja';
            document.getElementById('langSelect').value = currentLang;
            setLanguage(currentLang);
            updateDeviceCount();
            detectYourDevice();
            
            // Load Stats
            state.count = parseInt(localStorage.getItem('stats_count') || '0');
            state.totalDuration = parseFloat(localStorage.getItem('stats_duration') || '0');
            updateStatsUI();
            
            setInterval(updateDeviceCount, 5000);

            document.querySelectorAll('#presetArea .btn').forEach(btn => {
                btn.onclick = () => {
                    document.querySelectorAll('#presetArea .btn').forEach(b => b.classList.remove('active'));
                    btn.classList.add('active');
                    state.activePresetName = btn.dataset.preset;
                    const p = presets[state.activePresetName];
                    state.angle = p.angle; state.duration = p.duration;
                    updateSliders();
                };
            });
        });

        function setLanguage(lang) {
            currentLang = lang;
            document.querySelectorAll('[data-i18n]').forEach(el => {
                const key = el.dataset.i18n;
                if(translations[lang][key]) el.innerText = translations[lang][key];
            });
        }

        function changeLang(lang) {
            localStorage.setItem('app_lang', lang);
            setLanguage(lang);
            showToast(translations[lang].msg_lang_ok);
        }

        function showToast(msg) {
            const toast = document.createElement('div');
            toast.className = 'toast'; toast.innerText = msg;
            document.getElementById('toast-container').appendChild(toast);
            setTimeout(() => toast.remove(), 3000);
        }

        function updateVal(id, val) { document.getElementById(id).innerText = val; }
        function onManualChange() {
            document.querySelectorAll('#presetArea .btn').forEach(b => b.classList.remove('active'));
            state.activePresetName = 'custom';
            state.angle = parseInt(document.querySelector('#main-view input[oninput*="angleVal"]').value);
            state.duration = parseFloat(document.querySelector('#main-view input[oninput*="timeVal"]').value);
        }

        function updateSliders() {
            const aS = document.querySelector('#main-view input[oninput*="angleVal"]');
            const tS = document.querySelector('#main-view input[oninput*="timeVal"]');
            aS.value = state.angle; updateVal('angleVal', state.angle+'°');
            tS.value = state.duration; updateVal('timeVal', state.duration.toFixed(1)+'s');
        }

        function squeeze() {
            if(state.isSqueezing) return;
            state.isSqueezing = true;
            state.isPaused = false;
            document.getElementById('active-preset-name').innerText = (translations[currentLang][`pst_${state.activePresetName}`] || translations[currentLang].pst_custom).toUpperCase();
            
            const btn = document.querySelector('.onigiri-btn');
            btn.classList.add('animate');
            setTimeout(() => btn.classList.remove('animate'), 500);

            // Try to call the API
            fetch(`/squeeze?angle=${state.angle}&duration=${state.duration}`).catch(err => {
                console.error("API Error:", err);
                showToast("Connection limited. Squeezer might not respond.");
            });

            document.getElementById('active-overlay').classList.add('visible');
            startTime = performance.now();
            startTimer();
        }

        function startTimer() {
            const circle = document.getElementById('progress-ring-circle');
            const cur = document.getElementById('timer-current');
            const radius = circle.r.baseVal.value;
            const circumference = radius * 2 * Math.PI;
            
            circle.style.strokeDasharray = `${circumference} ${circumference}`;
            circle.style.strokeDashoffset = circumference;

            const durMs = state.duration * 1000;
            
            if(activeTimer) clearInterval(activeTimer);
            
            activeTimer = setInterval(() => {
                if(state.isPaused) {
                    startTime += 50; // Offset start time to compensate for pause
                    return;
                }
                const elapsed = performance.now() - startTime;
                const prog = Math.min(elapsed / durMs, 1);
                
                cur.innerText = (elapsed / 1000).toFixed(1);
                
                const offset = circumference - (prog * circumference);
                circle.style.strokeDashoffset = offset;
                
                if(prog >= 1) { 
                    clearInterval(activeTimer); 
                    setTimeout(finish, 800); 
                }
            }, 50);
        }

        function finish() {
            state.isSqueezing = false; 
            state.count++;
            state.totalDuration += state.duration;
            
            localStorage.setItem('stats_count', state.count);
            localStorage.setItem('stats_duration', state.totalDuration);
            updateStatsUI();

            const type = translations[currentLang][`pst_${state.activePresetName}`] || translations[currentLang].pst_custom;
            document.getElementById('res-type').innerText = type;
            document.getElementById('res-time').innerText = state.duration.toFixed(1) + 's';
            document.getElementById('active-overlay').classList.remove('visible');
            document.getElementById('result-overlay').classList.add('visible');
            addToHistory(type);
        }

        function updateStatsUI() {
            document.getElementById('stat-total').innerText = state.count;
            const avg = state.count > 0 ? (state.totalDuration / state.count).toFixed(1) : '0.0';
            document.getElementById('stat-avg').innerHTML = `${avg}<small style="font-size:0.8rem">s</small>`;
        }

        function closeResult() { document.getElementById('result-overlay').classList.remove('visible'); }
        function stopActive() { clearInterval(activeTimer); state.isSqueezing = false; fetch('/stop'); document.getElementById('active-overlay').classList.remove('visible'); showToast(translations[currentLang].msg_stop_ok); }

        function togglePause() {
            const t = translations[currentLang];
            if(state.isPaused) {
                state.isPaused = false;
                startTime += (performance.now() - state.pausedAt);
                const remain = Math.max(0, state.duration - (performance.now()-startTime)/1000);
                fetch(`/squeeze?angle=${state.angle}&duration=${remain.toFixed(2)}`);
                document.getElementById('pauseBtn').innerText = t.btn_pause;
            } else {
                state.isPaused = true;
                state.pausedAt = performance.now();
                fetch('/stop');
                document.getElementById('pauseBtn').innerText = t.btn_resume || '再開';
            }
        }

        function switchTab(t) {
            ['main','data','settings'].forEach(id => document.getElementById(id+'-view').classList.add('hidden'));
            document.getElementById(t+'-view').classList.remove('hidden');
            document.querySelectorAll('.nav-item').forEach((n,i) => { n.classList.remove('active'); if(['main','data','settings'][i] === t) n.classList.add('active'); });
            if(t==='settings') fetch('/config').then(r=>r.json()).then(d=>{ 
                state.minLimit=d.limit; state.returnSpeed=d.speed;
                document.getElementById('limitVal').innerText=d.limit+'°'; 
                document.querySelector('#settings-view input[oninput*="limitVal"]').value=d.limit;
                document.getElementById('speedVal').innerText=d.speed+'s'; 
                document.querySelector('#settings-view input[oninput*="speedVal"]').value=d.speed;
            }).catch(()=>{});
        }

        function saveSettings() { fetch(`/save?limit=${state.minLimit}&speed=${state.returnSpeed}`).then(()=>showToast(translations[currentLang].msg_save_ok)); }
        function sendDebug(val) { fetch(`/debug?angle=${val}`).catch(()=>{}); }
        function updateDeviceCount() { fetch('/status').then(r=>r.json()).then(d=>{
            document.getElementById('deviceCount').innerText=d.clients;
            if(d.name) document.getElementById('deviceName').innerText=d.name;
            if(d.devices && d.devices.length > 0) {
                document.getElementById('deviceListWrapper').style.display = 'block';
                document.getElementById('deviceList').innerHTML = d.devices.map(name => `<span style="background:var(--surface-light); padding:2px 8px; border-radius:10px; font-size:0.7rem">${name}</span>`).join('');
            }
        }).catch(()=>{}); }
        function detectYourDevice() {
            const ua = navigator.userAgent;
            let model = "Unknown Device";
            if (/iPhone/.test(ua)) {
                model = "iPhone";
                if (/iPhone OS 16/.test(ua)) model = "iPhone (iOS 16)";
                if (/iPhone OS 17/.test(ua)) model = "iPhone (iOS 17)";
            } else if (/Android/.test(ua)) {
                const match = ua.match(/Android\s+([^\s;]+);?\s+([^)]+)/);
                if (match && match[2]) {
                    model = match[2].split(';')[0].replace(/Build\/.*/, '').trim();
                } else {
                    model = "Android Device";
                }
            } else if (/Windows/.test(ua)) {
                model = "Windows PC";
            } else if (/Macintosh/.test(ua)) {
                model = "Mac";
            }
            document.getElementById('yourDevice').innerText = model;
            fetch(`/register_client?name=${encodeURIComponent(model)}`).catch(()=>{});
        }

        function addToHistory(n) { const li = document.createElement('li'); li.style.padding='10px'; li.style.borderBottom='1px solid #efeff4'; li.style.fontSize='0.9rem'; li.innerText=`${new Date().toLocaleTimeString()} - ${n}`; document.getElementById('history-list').prepend(li); }
    </script>
</body>
</html>
)rawliteral";
