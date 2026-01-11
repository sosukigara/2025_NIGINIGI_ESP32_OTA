import React, { useEffect, useState } from 'react';
import { Confetti } from './Confetti';
import { Button } from './Button';
import { Trophy, Clock, Zap } from 'lucide-react';

interface CelebrationOverlayProps {
    onClose: () => void;
    presetName: string;
    duration: number;
    count: number; // Current total count to show progress
    lang: string;
}

export const CelebrationOverlay: React.FC<CelebrationOverlayProps> = ({ onClose, presetName, duration, count, lang }) => {
    const [step, setStep] = useState(0);

    useEffect(() => {
        // Sequence animations
        setTimeout(() => setStep(1), 100); // Overlay appearing
        setTimeout(() => setStep(2), 600); // Stats appearing
        setTimeout(() => setStep(3), 1200); // Button appearing
    }, []);

    const isJa = lang === 'ja';

    return (
        <div className="fixed inset-0 z-[100] flex flex-col items-center justify-center bg-black/80 backdrop-blur-md"
             onClick={onClose}>
            
            <Confetti />

            {/* Main Content */}
            <div className={`relative z-10 text-center transform transition-all duration-700 ${step >= 1 ? 'scale-100 opacity-100 translate-y-0' : 'scale-50 opacity-0 translate-y-10'}`}>
                
                {/* Simple Check Icon or minimalist visual */}
                <div className="mb-6 inline-flex items-center justify-center w-20 h-20 rounded-full bg-green-500/20 text-green-400 border border-green-500/30 shadow-[0_0_20px_rgba(74,222,128,0.3)] backdrop-blur-md">
                    <span className="text-4xl">✓</span>
                </div>

                <h1 className="text-4xl font-black text-white mb-8 tracking-wider">
                    {isJa ? '完了！' : 'Complete!'}
                </h1>

                {/* Stats Grid - Focused on the "Onigiri" details */}
                <div className={`grid grid-cols-2 gap-4 max-w-xs mx-auto mb-8 transition-all duration-700 delay-300 ${step >= 2 ? 'opacity-100 translate-y-0' : 'opacity-0 translate-y-4'}`}>
                    <div className="bg-white/10 border border-white/20 p-4 rounded-2xl backdrop-blur-md flex flex-col items-center justify-center">
                        <div className="text-gray-400 text-xs mb-1 flex items-center justify-center gap-1">
                            <Zap size={12} /> {isJa ? '硬さ' : 'Mode'}
                        </div>
                        <div className="text-xl font-bold text-white capitalize tracking-wide">{presetName}</div>
                    </div>
                    <div className="bg-white/10 border border-white/20 p-4 rounded-2xl backdrop-blur-md flex flex-col items-center justify-center">
                        <div className="text-gray-400 text-xs mb-1 flex items-center justify-center gap-1">
                            <Clock size={12} /> {isJa ? '時間' : 'Time'}
                        </div>
                        <div className="text-xl font-bold text-white font-mono">{duration.toFixed(1)}s</div>
                    </div>
                </div>
            </div>

            {/* Footer Button */}
            <div className={`absolute bottom-12 w-full px-6 transition-all duration-500 delay-700 ${step >= 3 ? 'opacity-100 translate-y-0' : 'opacity-0 translate-y-10'}`}>
                <Button 
                    fullWidth 
                    variant="primary" 
                    className="h-14 text-lg font-bold shadow-[0_0_30px_rgba(255,75,75,0.4)]"
                    onClick={onClose}
                >
                    {isJa ? '閉じる' : 'Close'}
                </Button>
            </div>
        </div>
    );
};
