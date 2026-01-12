import React, { useState, useEffect, useRef } from 'react';
import { useAppStore } from '../../store/useAppStore';
import { ApiClient } from '../../store/apiClient';
import { API_ENDPOINTS, PRESETS, TRANSLATIONS } from '../../constants/config';
import { Button } from '../../components/ui/Button';
import { Slider } from '../../components/ui/Slider';
import { Confetti } from '../../components/ui/Confetti'; // Kept for Haptic/other uses if needed, or remove if unused in SqueezeView directly
import { CelebrationOverlay } from '../../components/ui/CelebrationOverlay';
import { useHaptic } from '../../hooks/useHaptic';
import { Play, Square, MoveVertical } from 'lucide-react';
import type { PresetName } from '../../types';

export const SqueezeView: React.FC = () => {
    const { 
        lang, activePresetName, angle, duration, isSqueezing, activePin, servoPins,
        setPreset, setAngle, setDuration, setSqueezing, setActivePin,
        incrementCount, addDuration, incrementPresetStat 
    } = useAppStore();
    
    const t = TRANSLATIONS[lang];
    const { vibrate } = useHaptic();
    const [timeLeft, setTimeLeft] = useState(0);
    const [showResult, setShowResult] = useState(false);
    const timerRef = useRef<number | null>(null);
    const dragStartRef = useRef<number | null>(null);
    const startAngleRef = useRef<number>(0);
    const isDraggingRef = useRef<boolean>(false);

    // Initial Sync
    useEffect(() => {
        if (activePresetName !== 'custom') {
            const p = PRESETS[activePresetName as keyof typeof PRESETS] || PRESETS.normal;
            setPreset(activePresetName, p.angle, p.duration);
        }
    }, []);

    const handleStart = async () => {
        if (isSqueezing) return;
        vibrate(100);
        setSqueezing(true);
        setTimeLeft(duration);
        
        try {
            await ApiClient.post(API_ENDPOINTS.squeeze, { 
                // pin: undefined, // Send no pin to trigger "ALL" mode in backend
                angle, 
                duration 
            });
        } catch (e) {
            console.error("Failed to start squeeze", e);
        }

        const startTime = Date.now();
        const initialDuration = duration * 1000;

        timerRef.current = window.setInterval(() => {
            const elapsed = Date.now() - startTime;
            const remaining = Math.max(0, (initialDuration - elapsed) / 1000);
            setTimeLeft(remaining);

            if (remaining <= 0) {
                finish();
            }
        }, 100);
    };

    const finish = () => {
        if (timerRef.current) clearInterval(timerRef.current);
        setSqueezing(false);
        incrementCount();
        addDuration(duration);
        incrementPresetStat(activePresetName);
        vibrate([100, 50, 100]);
        setShowResult(true);
    };

    const stop = async () => {
        if (timerRef.current) clearInterval(timerRef.current);
        setSqueezing(false);
        vibrate(50);
        try {
            await ApiClient.post(API_ENDPOINTS.stop, {});
        } catch (e) {}
    };

    const handlePresetClick = (name: PresetName) => {
        if (isSqueezing) return;
        vibrate(40);
        if (name === 'custom') {
            setPreset(name);
        } else {
            const p = PRESETS[name as keyof typeof PRESETS];
            setPreset(name, p.angle, p.duration);
        }
    };


    const handleManualAngleChange = (newAngle: number) => {
        setAngle(newAngle);
        // Real-time update to hardware
        ApiClient.debug(activePin, newAngle).catch(() => {});
    };

    const presets: PresetName[] = ['soft', 'normal', 'hard', 'barikata', 'custom'];

    return (
        <div className="flex flex-col gap-6 p-4 pb-24">
            {/* Status Card */}
            <div className="card text-center py-8 relative overflow-hidden">
                <div className={`text-xl font-bold mb-2 ${isSqueezing ? 'text-[var(--primary)] animate-pulse' : 'text-gray-400'}`}>
                    {isSqueezing ? t.status_squeezing : t.status_ready}
                </div>

                <div className="text-6xl font-black font-mono tracking-tighter text-[var(--text-main)]">
                    {isSqueezing ? timeLeft.toFixed(1) : duration.toFixed(1)}<span className="text-2xl ml-1">s</span>
                </div>
                {/* Progress Bar */}
                {isSqueezing && (
                    <div className="absolute bottom-0 left-0 h-1 bg-[var(--primary)] transition-all ease-linear"
                         style={{ width: `${(timeLeft / duration) * 100}%` }} />
                )}
            </div>

            {/* Main Action - Moved to Middle */}
            <Button 
                variant={isSqueezing ? "danger" : "primary"}
                fullWidth 
                className="h-24 text-2xl shadow-xl touch-none"
                onClick={(e) => {
                    if (isDraggingRef.current) {
                        e.preventDefault();
                        e.stopPropagation();
                        return;
                    }
                    isSqueezing ? stop() : handleStart();
                }}
                onTouchStart={(e) => {
                    if (isSqueezing) return;
                    dragStartRef.current = e.touches[0].clientY;
                    startAngleRef.current = angle;
                    isDraggingRef.current = false;
                }}
                onTouchMove={(e) => {
                    if (isSqueezing || dragStartRef.current === null) return;
                    const currentY = e.touches[0].clientY;
                    const deltaY = dragStartRef.current - currentY; // Up is positive
                    
                    // Threshold to start dragging
                    if (Math.abs(deltaY) > 10) {
                        isDraggingRef.current = true;
                        if (activePresetName !== 'custom') {
                            setPreset('custom');
                        }
                    }

                    if (isDraggingRef.current) {
                        // Sensitivity: 1px = 0.5 degree
                        const diff = Math.round(deltaY * 0.5); 
                        let newAngle = startAngleRef.current + diff;
                        newAngle = Math.max(0, Math.min(270, newAngle));
                        
                        if (newAngle !== angle) {
                            handleManualAngleChange(newAngle);
                            // Haptic feedback for steps (every 10 degrees?)
                            if (newAngle % 10 === 0) vibrate(5);
                        }
                    }
                }}
                onTouchEnd={() => {
                    dragStartRef.current = null;
                    // Reset flag after a short delay so onClick doesn't fire immediately if it was a drag
                    setTimeout(() => { isDraggingRef.current = false; }, 100);
                }}
            >
                {isSqueezing ? (
                    <><Square fill="currentColor" size={32} className="mr-2" /> {t.btn_stop}</>
                ) : (
                    <><Play fill="currentColor" size={32} className="mr-2" /> {t.btn_squeeze}</>
                )}
            </Button>

            {/* Presets */}
            <div className="grid grid-cols-2 gap-3 sm:grid-cols-3">
                {presets.map(p => (
                    <Button 
                        key={p} 
                        variant={activePresetName === p ? 'primary' : 'secondary'}
                        onClick={() => handlePresetClick(p)}
                        className="text-sm h-12"
                        disabled={isSqueezing}
                    >
                        {t[`pst_${p}` as keyof typeof t] || p}
                    </Button>
                ))}
            </div>

            {/* Manual Controls (Only for Custom) */}
            <div className={`card p-6 transition-all ${activePresetName === 'custom' ? 'opacity-100' : 'opacity-50 pointer-events-none'}`}>
                <Slider 
                    label={t.lbl_strength} 
                    value={angle} 
                    min={0} max={270} 
                    onChange={(e) => handleManualAngleChange(Number(e.target.value))}
                    valueDisplay={`${angle}°`}
                />
                <div className="h-4" />
                <Slider 
                    label={t.lbl_duration} 
                    value={duration} 
                    min={0.5} max={10.0} step={0.1}
                    onChange={(e) => setDuration(Number(e.target.value))}
                    valueDisplay={`${duration.toFixed(1)}s`}
                />
            </div>

            {/* Result Overlay */}
            {showResult && (
                <CelebrationOverlay 
                    onClose={() => setShowResult(false)}
                    presetName={t[`pst_${activePresetName}` as keyof typeof t] || activePresetName}
                    duration={duration}
                    count={useAppStore.getState().count}
                    lang={lang}
                />
            )}
        </div>
    );
};
