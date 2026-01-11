import React, { useState, useEffect } from 'react';
import { useAppStore } from '../../store/useAppStore';
import { TRANSLATIONS } from '../../constants/config';
import { Button } from '../../components/ui/Button';
import { Slider } from '../../components/ui/Slider';
import { useHaptic } from '../../hooks/useHaptic';
import { Modal } from '../../components/ui/Modal';

export const SettingsView: React.FC = () => {
    const { 
        lang, setLang, minLimit, returnSpeed, 
        servoPin, setServoPin, servoOffset, setServoOffset,
        theme, setTheme, resetData
    } = useAppStore();
    const t = TRANSLATIONS[lang];
    const { vibrate } = useHaptic();

    const [fwDate] = useState('2026/01/11 11:55');
    const [debugAngle, setDebugAngle] = useState(270);
    const [activeTheme, setActiveTheme] = useState(theme);
    const [showResetModal, setShowResetModal] = useState(false);

    // Sync local theme state with store
    useEffect(() => setActiveTheme(theme), [theme]);

    const toggleLang = () => {
        const newLang = lang === 'ja' ? 'km' : 'ja';
        setLang(newLang);
        vibrate(50);
    };

    const handleResetConfirm = async () => {
        await resetData();
        setShowResetModal(false);
    };

    const themes = [
        { id: 'light', label: t.theme_light },
        { id: 'dark', label: t.theme_dark },
        { id: 'system', label: t.theme_system },
    ] as const;

    return (
        <div className="flex flex-col gap-6 p-4 pb-24">
            <div className="section-title">{t.hdr_system}</div>
            <div className="card p-0 overflow-hidden">
                <div className="setting-row setting-row-border flex justify-between items-center p-4 border-b border-gray-100">
                    <span className="font-bold">{t.lbl_theme}</span>
                    <div className="flex bg-[var(--surface-light)] rounded-lg p-1">
                        {themes.map((th) => (
                            <button
                                key={th.id}
                                onClick={() => { setTheme(th.id); vibrate(20); }}
                                className={`
                                    px-3 py-1.5 rounded-md text-xs font-bold transition-all duration-200
                                    ${theme === th.id 
                                        ? 'bg-[var(--surface-color)] shadow-sm text-[var(--text-main)]' 
                                        : 'text-[var(--text-sub)] hover:text-[var(--text-main)]'
                                    }
                                `}
                            >
                                {th.label}
                            </button>
                        ))}
                    </div>
                </div>
                <div className="setting-row setting-row-border flex justify-between items-center p-4 border-b border-gray-100">
                    <span className="font-bold">{t.lbl_language}</span>
                    <Button variant="secondary" onClick={toggleLang} className="min-h-[44px] py-2 px-4 shadow-none border-gray-300">
                        {lang === 'ja' ? '日本語' : 'ខ្មែរ'}
                    </Button>
                </div>
                <div className="setting-row flex justify-between items-center p-4 border-b border-gray-100">
                    <span className="font-bold text-gray-400">{t.lbl_firmware_date}</span>
                    <span className="font-mono text-sm">{fwDate}</span>
                </div>
            </div>

            <div className="section-title">{t.hdr_hardware}</div>
            <div className="card p-4">
                 <div className="mb-6">
                    <div className="flex justify-between items-center mb-2">
                        <label className="font-bold text-[var(--text-main)]">{t.lbl_servo_pin}</label>
                        <div className="font-bold text-[var(--primary)] text-lg">GPIO {servoPin}</div>
                    </div>
                    <div className="flex gap-2">
                        {[25, 26, 27, 13].map(pin => (
                            <Button 
                                key={pin}
                                variant={servoPin === pin ? 'primary' : 'secondary'}
                                onClick={() => { setServoPin(pin); vibrate(50); }}
                                className="flex-1 min-h-[48px] text-sm"
                            >
                                {pin}
                            </Button>
                        ))}
                    </div>
                 </div>

                 <Slider 
                    label={t.lbl_servo_offset} 
                    value={servoOffset}
                    min={-20} max={20} step={1}
                    onChange={(e) => { setServoOffset(Number(e.target.value)); vibrate(10); }}
                    valueDisplay={`${servoOffset > 0 ? '+' : ''}${servoOffset}°`}
                 />
            </div>

            <div className="section-title">{t.hdr_advanced_settings}</div>
            <div className="card p-4">
                 <div className="mb-4 text-sm font-bold text-gray-500">{t.lbl_servo_debug}</div>
                 <Slider 
                    label={t.lbl_angle}
                    min={0} max={270} step={1}
                    value={debugAngle}
                    onChange={(e) => { 
                        const val = Number(e.target.value);
                        setDebugAngle(val);
                        // Direct Debug Call
                        fetch(`/debug?angle=${val}`).catch(()=>{});
                    }}
                    valueDisplay={`${debugAngle}°`}
                 />
          
                 <div className="pt-4 border-t border-white/10 space-y-3">
                    <Button 
                       variant="secondary" 
                       className="w-full text-red-500 bg-red-500/10 hover:bg-red-500/20 border-red-500/20"
                       onClick={() => setShowResetModal(true)}
                    >
                       {t.btn_reset_stats}
                    </Button>
                 </div>
                 <div className="mt-4 pt-4 border-t border-gray-100 opacity-50 pointer-events-none">
                    <Slider 
                        label={t.lbl_return_speed} 
                        defaultValue={returnSpeed}
                        min={0.01} max={0.5} step={0.01}
                        valueDisplay={`${returnSpeed}s`}
                        disabled
                    />
                 </div>
            </div>

            <Modal
                isOpen={showResetModal}
                onClose={() => setShowResetModal(false)}
                title={t.lbl_reset}
                footer={
                    <div className="flex gap-3">
                        <Button variant="secondary" fullWidth onClick={() => setShowResetModal(false)}>
                            {t.btn_cancel}
                        </Button>
                        <Button variant="danger" fullWidth onClick={handleResetConfirm}>
                            {t.btn_reset_action}
                        </Button>
                    </div>
                }
            >
                <div className="text-center">
                    <p className="mb-4">{t.msg_reset_confirm}</p>
                    <p className="text-xs text-red-400">This action cannot be undone.</p>
                </div>
            </Modal>
            
            <div className="text-center text-xs text-gray-300 mt-8">
                {t.lbl_version} 2.0 (React Refactor)
            </div>
        </div>
    );
};

