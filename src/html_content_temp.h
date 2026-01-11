<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, viewport-fit=cover">
    <title>おにぎりにぎりきにぎにぎ</title>
    <!-- Fonts -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;700;900&family=Noto+Sans+JP:wght@400;700;900&display=swap" rel="stylesheet">
    <!-- Icons -->
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.4.0/css/all.min.css">
    
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
            font-family: 'Inter', 'Noto Sans JP', sans-serif;
            -webkit-font-smoothing: antialiased;
            overflow-x: hidden;
            padding-bottom: 80px; /* Space for bottom nav */
        }

        /* --- Header --- */
        header {
            padding: 20px;
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
            font-size: 1.2rem;
            font-weight: 900;
            background: linear-gradient(135deg, var(--primary), var(--accent));
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            letter-spacing: -0.5px;
            display: flex;
            align-items: center;
            gap: 10px;
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
            box-shadow: 0 0 10px currentColor;
            animation: pulse 2s infinite;
        }

        @keyframes pulse {
            0% { opacity: 1; transform: scale(1); }
            50% { opacity: 0.5; transform: scale(0.8); }
            100% { opacity: 1; transform: scale(1); }
        }

        /* --- Layout --- */
        .container {
            max-width: 600px;
            margin: 0 auto;
            padding: 20px;
        }

        .section-title {
            font-size: 0.85rem;
            color: var(--text-sub);
            text-transform: uppercase;
            letter-spacing: 1px;
            margin: 30px 0 10px 0;
            display: flex;
            justify-content: space-between;
        }

        /* --- Hero / Main Action --- */
        .hero {
            text-align: center;
            margin: 20px 0 40px 0;
            position: relative;
        }

        .squeeze-wrapper {
            position: relative;
            width: 220px;
            height: 220px;
            margin: 0 auto;
        }

        .squeeze-circle {
            width: 100%;
            height: 100%;
            border-radius: 50%; /* Keep the orbit/halo circular */
            background: rgba(255,255,255,0.1); 
            display: flex;
            align-items: center;
            justify-content: center;
            box-shadow: none; /* Soften the container shadow for the irregular button */
            position: relative;
            z-index: 10;
            transition: var(--transition);
        }

        .squeeze-btn {
            width: 180px;
            height: 170px; /* Slightly shorter/wider feel */
            /* Onigiri Shape: Tapered top, wider bottom */
            border-radius: 50% 50% 40% 40% / 70% 70% 30% 30%;
            border: 4px solid #f0f0f0;
            background: #ffffff; /* Rice Color */
            color: #333;
            font-size: 1.5rem;
            font-weight: 800;
            cursor: pointer;
            box-shadow: 0 10px 25px rgba(0,0,0,0.1);
            transition: var(--transition);
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            gap: 5px;
            -webkit-tap-highlight-color: transparent;
            position: relative;
            overflow: hidden;
        }

        /* The Nori (Seaweed) */
        .squeeze-btn::after {
            content: '';
            position: absolute;
            bottom: 0;
            left: 50%;
            transform: translateX(-50%);
            width: 80px;
            height: 50px;
            background: #2a2a2a;
            border-radius: 4px 4px 0 0;
            z-index: 0;
        }

        .squeeze-btn i, .squeeze-btn span {
            position: relative;
            z-index: 2;
        }
        
        .squeeze-btn i { font-size: 2rem; color: var(--primary); }
        .squeeze-btn span { font-size: 1rem; opacity: 0.8; color: #555; }

        .squeeze-btn:active {
            transform: scale(0.95) rotate(2deg); /* Little squish */
        }
        
        /* Lock Overlay */
        .lock-overlay {
            position: absolute;
            top: 0; left: 0; right: 0; bottom: 0;
            background: rgba(0,0,0,0.7);
            border-radius: 50%;
            z-index: 20;
            display: flex;
            align-items: center;
            justify-content: center;
            flex-direction: column;
            backdrop-filter: blur(4px);
            opacity: 0;
            pointer-events: none;
            transition: opacity 0.3s;
        }
        
        .is-locked .lock-overlay {
            opacity: 1;
            pointer-events: auto;
        }

        .lock-icon {
            font-size: 2rem;
            color: var(--text-sub);
            margin-bottom: 10px;
        }

        /* --- Visualization (Orbit) Removed --- */

        /* --- Cards --- */
        .card {
            background: var(--surface-color);
            border-radius: var(--card-radius);
            padding: 20px;
            margin-bottom: 15px;
            border: 1px solid rgba(0,0,0,0.05);
            box-shadow: 0 4px 12px rgba(0,0,0,0.03);
        }

        .grid-2 {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 15px;
        }
        
        .grid-4 {
            display: grid;
            grid-template-columns: repeat(4, 1fr);
            gap: 10px;
        }

        /* --- Buttons & Inputs --- */
        .btn {
            background: var(--surface-light);
            border: none;
            color: var(--text-main);
            padding: 15px;
            border-radius: var(--btn-radius);
            font-weight: 600;
            width: 100%;
            cursor: pointer;
            transition: var(--transition);
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 8px;
        }

        .btn i { font-size: 1.2rem; margin-bottom: 2px; }

        .btn:active, .btn.active {
            background: var(--primary);
            color: white;
            box-shadow: 0 5px 15px var(--primary-glow);
        }

        .btn-small { padding: 10px; font-size: 0.9rem; }
        
        .btn-danger { color: var(--danger); border: 1px solid rgba(231, 76, 60, 0.2); }
        .btn-danger:active { background: var(--danger); color: white; }

        /* --- Sliders --- */
        .range-wrapper {
            margin-top: 15px;
        }
        
        .range-header {
            display: flex;
            justify-content: space-between;
            margin-bottom: 10px;
            font-size: 0.9rem;
            color: var(--text-sub);
        }
        
        .range-value {
            color: var(--accent);
            font-family: monospace;
            font-weight: bold;
        }

        input[type=range] {
            width: 100%;
            -webkit-appearance: none;
            background: transparent;
        }
        
        input[type=range]::-webkit-slider-thumb {
            -webkit-appearance: none;
            height: 24px;
            width: 24px;
            border-radius: 50%;
            background: var(--text-main);
            margin-top: -10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.5);
            cursor: pointer;
        }
        
        input[type=range]::-webkit-slider-runnable-track {
            width: 100%;
            height: 4px;
            background: #333;
            border-radius: 2px;
        }

        /* --- Toggle Switch --- */
        .toggle-row {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 12px 0;
            border-bottom: 1px solid rgba(0,0,0,0.05);
        }
        .toggle-row:last-child { border-bottom: none; }

        .toggle-label {
            display: flex;
            flex-direction: column;
            gap: 2px;
        }
        .toggle-sub { font-size: 0.75rem; color: var(--text-sub); }

        .switch {
            position: relative;
            display: inline-block;
            width: 50px;
            height: 28px;
        }
        .switch input { opacity: 0; width: 0; height: 0; }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0; left: 0; right: 0; bottom: 0;
            background-color: #333;
            transition: .4s;
            border-radius: 34px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 20px;
            width: 20px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: .4s;
            border-radius: 50%;
        }
        input:checked + .slider { background-color: var(--success); }
        input:checked + .slider:before { transform: translateX(22px); }

        /* --- Stats / Charts --- */
        .stat-grid {
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            gap: 10px;
            margin-bottom: 20px;
        }
        
        .stat-item {
            background: var(--surface-color);
            padding: 15px;
            border-radius: 12px;
            text-align: center;
            box-shadow: 0 2px 8px rgba(0,0,0,0.02);
        }
        
        .stat-value { font-size: 1.5rem; font-weight: 900; color: var(--text-main); }
        .stat-label { font-size: 0.7rem; color: var(--text-sub); margin-top: 5px; }

        /* --- Footer --- */
        .bottom-nav {
            position: fixed;
            bottom: 0; width: 100%;
            background: rgba(255, 255, 255, 0.85);
            backdrop-filter: blur(20px);
            display: flex;
            justify-content: space-around;
            padding: 15px 0 25px 0; /* Extra padding for iPhone home bar */
            border-top: 1px solid rgba(0,0,0,0.05);
            z-index: 200;
        }
        
        .nav-item {
            color: var(--text-sub);
            text-align: center;
            font-size: 0.7rem;
            cursor: pointer;
            transition: 0.2s;
        }
        
        .nav-item i {
            display: block;
            font-size: 1.2rem;
            margin-bottom: 4px;
        }
        
        .nav-item.active { color: var(--primary); }

        /* --- Sensor/Telemetry --- */
        .sensor-panel {
            font-family: monospace;
            background: #000;
            border: 1px solid #333;
            padding: 10px;
            border-radius: 8px;
            color: var(--success);
            font-size: 0.8rem;
            margin-top: 10px;
        }
        
        /* Emergency Stop */
        .emergency-btn {
            background: var(--danger);
            color: white;
            padding: 15px;
            width: 100%;
            border-radius: var(--btn-radius);
            margin-top: 20px;
            font-weight: bold;
            text-transform: uppercase;
            letter-spacing: 2px;
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            border: none;
            box-shadow: 0 5px 20px rgba(231, 76, 60, 0.3);
        }

        /* --- Active Overlay --- */
        .active-overlay {
            position: fixed;
            top: 0; left: 0; right: 0; bottom: 0;
            background: var(--bg-color);
            z-index: 500;
            display: flex;
            align-items: center;
            justify-content: center;
            opacity: 1;
            transition: opacity 0.3s;
            padding: 20px;
        }
        
        .active-overlay.hidden {
            opacity: 0;
            pointer-events: none;
            display: none; /* simple hide */
        }

        .overlay-content {
            width: 100%;
            max-width: 400px;
            text-align: center;
        }

        .active-status {
            display: flex;
            align-items: center;
            justify-content: center;
            gap: 10px;
            font-size: 1.2rem;
            color: var(--warning);
            margin-bottom: 30px;
            font-weight: bold;
        }

        @keyframes pop {
            0% { transform: scale(0); opacity: 0; }
            100% { transform: scale(1); opacity: 1; }
        }

        .status-dot.large {
            width: 12px; height: 12px;
            background: var(--warning);
        }

        .timer-display {
            font-size: 5rem;
            font-weight: 900;
            font-variant-numeric: tabular-nums;
            line-height: 1;
            color: var(--text-main);
            margin-bottom: 5px;
        }

        .timer-unit { font-size: 1.5rem; color: var(--text-sub); }
        .timer-total { color: var(--text-sub); margin-bottom: 40px; }

        .progress-container {
            width: 100%;
            height: 12px;
            background: rgba(0,0,0,0.1);
            border-radius: 6px;
            overflow: hidden;
            margin-bottom: 40px;
        }

        .progress-bar {
            height: 100%;
            width: 0%;
            background: var(--success);
            transition: width 0.1s linear;
            box-shadow: 0 0 10px rgba(52, 199, 89, 0.4);
        }

        .active-details {
            background: var(--surface-color);
            padding: 20px;
            border-radius: 12px;
            margin-bottom: 30px;
            box-shadow: 0 4px 15px rgba(0,0,0,0.05);
        }

        .detail-row {
            display: flex;
            justify-content: space-between;
            padding: 10px 0;
            border-bottom: 1px solid rgba(0,0,0,0.05);
        }
        .detail-row:last-child { border-bottom: none; }
        .detail-row span:first-child { color: var(--text-sub); }
        .detail-row span:last-child { font-weight: bold; }

    </style>
</head>
<body>

    <header>
        <div class="brand">
            <i class="fa-solid fa-rice-ball"></i> おにぎりにぎりきにぎにぎ
        </div>
        <div class="status-badge">
            <div class="status-dot"></div> 準備完了
        </div>
    </header>

    <div class="container" id="main-view">
        
        <!-- Active Overlay (Hidden by default) -->
        <div id="active-overlay" class="active-overlay hidden">
            <div class="overlay-content">
                <div class="active-status">
                    <div class="status-dot large"></div>
                    <span>握っています...</span>
                </div>
                
                <div class="timer-display">
                    <span id="timer-current">0.0</span><span class="timer-unit">s</span>
                </div>
                <div class="timer-total">
                    残り <span id="timer-remaining">3.0</span>s
                </div>

                <div class="progress-container">
                    <div class="progress-bar" id="progress-bar"></div>
                </div>

                <div class="active-details">
                    <div class="detail-row">
                        <span>設定</span>
                        <span id="active-preset-name">カスタム</span>
                    </div>
                    <div class="detail-row">
                        <span>強度</span>
                        <span id="active-angle">180°</span>
                    </div>
                </div>

                <button class="btn btn-danger" onclick="stopActive()">
                    <i class="fa-solid fa-stop"></i> 中止
                </button>
            </div>
        </div>

        <!-- Result Overlay -->
        <div id="result-overlay" class="active-overlay hidden">
            <div class="overlay-content">
                <div class="active-status" style="color: var(--success); flex-direction: column; gap: 20px;">
                    <i class="fa-solid fa-check-circle" style="font-size: 4rem;"></i>
                    <h2 style="margin: 0; color: var(--text-main); font-size: 1.5rem;">完成しました！</h2>
                </div>
                
                <div style="font-size: 8rem; margin: 30px 0; animation: pop 0.4s cubic-bezier(0.175, 0.885, 0.32, 1.275);">
                    🍙
                </div>

                <div class="active-details">
                    <div class="detail-row">
                        <span>仕上がり</span>
                        <span id="result-preset-name">カスタム</span>
                    </div>
                    <div class="detail-row">
                        <span>作成時間</span>
                        <span id="result-time">3.0s</span>
                    </div>
                </div>

                <button class="btn active" onclick="closeResult()">
                    OK
                </button>
            </div>
        </div>

        <!-- Hero Section -->
        <section class="hero">
            <div class="squeeze-wrapper" id="squeezeWrapper">
            <div class="squeeze-wrapper" id="squeezeWrapper">
                <div class="squeeze-circle">
                    <button class="squeeze-btn" onclick="squeeze()">
                        <i class="fa-solid fa-hand-fist"></i>
                        <span>握る</span>
                    </button>
                </div>
                <!-- Child Lock Overlay Removed -->
            </div>
            
            <div style="margin-top: 20px; display: flex; justify-content: center; gap: 15px;">
                <button class="btn btn-small" style="width: auto; padding: 10px 20px;" onclick="reset()">
                    <i class="fa-solid fa-rotate-right"></i> リセット
                </button>
                <button class="btn btn-small" style="width: auto; padding: 10px 20px;" onclick="stop()">
                    <i class="fa-solid fa-pause"></i> 一時停止
                </button>
            </div>
        </section>

        <!-- Presets -->
        <div class="section-title">
            <span>プリセット</span>
            <span style="font-size: 1.2rem;" onclick="toggleEditMode()"><i class="fa-solid fa-pen-to-square"></i></span>
        </div>
        <section class="grid-4" id="presetArea">
            <button class="btn active">
                <i class="fa-regular fa-face-smile"></i>
                <div class="btn-small">やわらか</div>
            </button>
            <button class="btn">
                <i class="fa-solid fa-face-meh"></i>
                <div class="btn-small">ふつう</div>
            </button>
            <button class="btn">
                <i class="fa-solid fa-dumbbell"></i>
                <div class="btn-small">かため</div>
            </button>
            <button class="btn">
                <i class="fa-solid fa-gem"></i>
                <div class="btn-small">ばりかた</div>
            </button>
        </section>

        <!-- Fine Tuning -->
        <div class="section-title">手動調整</div>
        <section class="card">
            <div class="range-wrapper">
                <div class="range-header">
                    <span>強さ (角度)</span>
                    <span class="range-value" id="angleVal">180°</span>
                </div>
                <input type="range" min="0" max="270" value="180" oninput="updateVal('angleVal', this.value + '°')">
            </div>
            
            <div class="range-wrapper">
                <div class="range-header">
                    <span>時間</span>
                    <span class="range-value" id="timeVal">3.0s</span>
                </div>
                <input type="range" min="0.5" max="10" step="0.5" value="3.0" oninput="updateVal('timeVal', this.value + 's')">
            </div>

            <div class="toggle-row">
                <div class="toggle-label">
                    <span>二度握り</span>
                    <span class="toggle-sub">二回握って固めに仕上げます</span>
                </div>
                <label class="switch">
                    <input type="checkbox">
                    <span class="slider"></span>
                </label>
            </div>
        </section>

        <!-- Stats -->
        <div class="section-title">データ分析</div>
        <section class="stat-grid">
            <div class="stat-item">
                <div class="stat-value">0</div>
                <div class="stat-label">累計個数</div>
            </div>
            <div class="stat-item">
                <div class="stat-value">--</div>
                <div class="stat-label">平均時間</div>
            </div>
            <div class="stat-item">
                <div class="stat-value">--</div>
                <div class="stat-label">お気に入り</div>
            </div>
        </section>

        <!-- Safety & Settings Removed temporarily -->

        <button class="emergency-btn">
            <i class="fa-solid fa-triangle-exclamation"></i> 緊急停止
        </button>
        
        <div style="text-align: center; color: #444; margin-top: 30px; font-size: 0.8rem;">
            <div>最終更新: 2026/01/08 15:00</div>
            <div style="margin-top: 5px;">IPアドレス: 192.168.4.1</div>
        </div>

    </div>

    <!-- Settings View -->
    <div class="container hidden" id="settings-view" style="display: none;">
        <div class="section-title">安全設定</div>
        <section class="card">
            <div class="range-wrapper">
                <div class="range-header">
                    <span>最大握り込み (制限)</span>
                    <span class="range-value" id="limitVal">90°</span>
                </div>
                <input type="range" min="0" max="270" value="90" oninput="updateVal('limitVal', this.value + '°'); state.minLimit = parseInt(this.value);">
                <div style="font-size: 0.7rem; color: #888; margin-top: 5px;">
                    これ以上深く握らないように制限します (270° = 開放, 0° = 最大)
                </div>
            </div>
        </section>

        <div class="section-title">システム</div>
        <button class="btn active" onclick="saveSettings()">
            <i class="fa-solid fa-floppy-disk"></i> 設定を保存
        </button>
        
        <div style="text-align: center; color: #444; margin-top: 30px; font-size: 0.8rem;">
            <div>最終更新: 2026/01/08 15:00</div>
            <div style="margin-top: 5px;">IPアドレス: 192.168.4.1</div>
        </div>
    </div>

    <!-- Bottom Navigation -->
    <nav class="bottom-nav">
        <div class="nav-item active" onclick="switchTab('main')">
            <i class="fa-solid fa-gamepad"></i> 操作
        </div>
        <div class="nav-item">
            <i class="fa-solid fa-chart-line"></i> データ
        </div>
        <div class="nav-item" onclick="switchTab('settings')">
            <i class="fa-solid fa-sliders"></i> 設定
        </div>
    </nav>

    <script>
        // State
        let state = {
            count: 0,
            isSqueezing: false,
            angle: 180,
            duration: 3.0,
            activePresetName: 'カスタム',
            minLimit: 90
        };

        // Presets Data
        const presets = {
            'やわらか': { angle: 120, duration: 4.0 },
            'ふつう': { angle: 180, duration: 3.0 },
            'かため': { angle: 240, duration: 2.5 },
            'ばりかた': { angle: 270, duration: 2.0 }
        };

        let activeTimer = null;

        function updateVal(id, val) {
            document.getElementById(id).innerText = val;
        }

        // Initialize
        document.addEventListener('DOMContentLoaded', () => {
             const presetBtns = document.querySelectorAll('#presetArea .btn');
             presetBtns.forEach(btn => {
                 btn.addEventListener('click', () => {
                     presetBtns.forEach(b => b.classList.remove('active'));
                     btn.classList.add('active');
                     
                     const name = btn.querySelector('.btn-small').innerText;
                     state.activePresetName = name; // Track name
                     if(presets[name]) {
                         applyPreset(presets[name]);
                     }
                 });
             });
        });

        function applyPreset(p) {
            state.angle = p.angle;
            state.duration = p.duration;
            
            const angleSlider = document.querySelector('input[type=range][oninput*="angleVal"]');
            const timeSlider = document.querySelector('input[type=range][oninput*="timeVal"]');
            
            if(angleSlider) { angleSlider.value = state.angle; updateVal('angleVal', state.angle + '°'); }
            if(timeSlider) { timeSlider.value = state.duration; updateVal('timeVal', state.duration.toFixed(1) + 's'); }
        }

        function squeeze() {
            if(state.isSqueezing) return;
            state.isSqueezing = true;

            // Prepare Overlay Data
            document.getElementById('active-preset-name').innerText = state.activePresetName;
            document.getElementById('active-angle').innerText = state.angle + '°';
            
            // Call ESP32
            fetch(`/squeeze?angle=${state.angle}&duration=${state.duration}`).catch(e => console.log(e));

            // Show Overlay
            const overlay = document.getElementById('active-overlay');
            overlay.classList.remove('hidden');
            overlay.style.display = 'flex'; // Ensure flex
            
            // Start Timer Loop
            let startTime = performance.now();
            let durationMs = state.duration * 1000;
            
            const timerCurrent = document.getElementById('timer-current');
            const timerRemaining = document.getElementById('timer-remaining');
            const progressBar = document.getElementById('progress-bar');
            
            if(navigator.vibrate) navigator.vibrate([50]);

            activeTimer = setInterval(() => {
                let elapsed = performance.now() - startTime;
                let progress = Math.min(elapsed / durationMs, 1.0);
                
                // Update UI
                timerCurrent.innerText = (elapsed / 1000).toFixed(1);
                timerRemaining.innerText = Math.max(0, (durationMs - elapsed) / 1000).toFixed(1);
                progressBar.style.width = (progress * 100) + '%';
                
                if (progress >= 1.0) {
                    finishSqueeze();
                }
            }, 50);
        }

        function finishSqueeze() {
            clearInterval(activeTimer);
            if(navigator.vibrate) navigator.vibrate(200);
            
            setTimeout(() => {
                state.isSqueezing = false;
                state.count++;
                updateStats();
                showResult(); // Transition to result
            }, 500);
        }

        function showResult() {
            // Populate Result Data
            document.getElementById('result-preset-name').innerText = state.activePresetName;
            document.getElementById('result-time').innerText = state.duration.toFixed(1) + 's';
            
            // Switch Overlays
            document.getElementById('active-overlay').classList.add('hidden');
            setTimeout(() => document.getElementById('active-overlay').style.display = 'none', 300);

            const resOverlay = document.getElementById('result-overlay');
            resOverlay.classList.remove('hidden');
            resOverlay.style.display = 'flex';
        }

        function closeResult() {
            const resOverlay = document.getElementById('result-overlay');
            resOverlay.classList.add('hidden');
            setTimeout(() => resOverlay.style.display = 'none', 300);
            
            // Reset Active Bar hidden state from previous close
            document.getElementById('progress-bar').style.width = '0%';
        }

        function stopActive() {
            clearInterval(activeTimer);
            state.isSqueezing = false;
            fetch('/stop').catch(e => console.log(e));
            alert("中止しました");
            
            // Close Active Overlay
            const overlay = document.getElementById('active-overlay');
            overlay.classList.add('hidden');
            setTimeout(() => overlay.style.display = 'none', 300);
            document.getElementById('progress-bar').style.width = '0%';
        }
        
        function closeOverlay() {
            // Deprecated for direct use, logic moved to showResult/stopActive
        }

        function updateStatus(text, color) {
            const badge = document.querySelector('.status-badge');
            badge.innerHTML = `<div class="status-dot" style="color: ${color}"></div> ${text}`;
        }

        function updateStats() {
            const values = document.querySelectorAll('.stat-value');
            if(values[0]) values[0].innerText = state.count.toLocaleString();
        }

        function stop() {
            // Main screen stop button
            stopActive(); 
        }
        
        function switchTab(tab) {
             const main = document.getElementById('main-view');
             const settings = document.getElementById('settings-view');
             const navs = document.querySelectorAll('.nav-item');
             
             navs.forEach(n => n.classList.remove('active'));
             
             if (tab === 'main') {
                 main.style.display = 'block';
                 settings.style.display = 'none';
                 navs[0].classList.add('active');
             } else if (tab === 'settings') {
                 main.style.display = 'none';
                 settings.style.display = 'block';
                 navs[2].classList.add('active');
                 // Load current limit
                 fetch('/config').then(r=>r.json()).then(d=>{
                     state.minLimit = d.limit;
                     document.getElementById('limitVal').innerText = d.limit + '°';
                     document.querySelector('#settings-view input[type=range]').value = d.limit;
                 }).catch(e=>console.log(e));
             }
        }

        function saveSettings() {
            fetch(`/save?limit=${state.minLimit}`).then(()=>{
                alert("設定を保存しました");
            }).catch(()=>{
                alert("保存エラー");
            });
        }

        function reset() {
            if(confirm("位置をリセットしますか？")) {
                fetch('/reset').catch(e => console.log(e));
            }
        }
    </script>
</body>
</html>
