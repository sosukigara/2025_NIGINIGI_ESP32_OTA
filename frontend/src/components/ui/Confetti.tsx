import React, { useEffect, useRef } from 'react';

export const Confetti: React.FC = () => {
    const containerRef = useRef<HTMLDivElement>(null);

    useEffect(() => {
        const colors = ['#ff0000', '#00ff00', '#0000ff', '#ffff00', '#ff00ff', '#00ffff'];
        const container = containerRef.current;
        if (!container) return;

        for (let i = 0; i < 50; i++) {
            const confetti = document.createElement('div');
            confetti.classList.add('confetti');
            confetti.style.left = Math.random() * 100 + '%';
            confetti.style.animationDelay = Math.random() * 2 + 's';
            confetti.style.backgroundColor = colors[Math.floor(Math.random() * colors.length)];
            container.appendChild(confetti);
        }

        return () => {
            if (container) container.innerHTML = '';
        };
    }, []);

    return (
        <div ref={containerRef} className="absolute inset-0 pointer-events-none overflow-hidden z-50">
            <style>{`
                .confetti {
                    position: absolute;
                    width: 10px;
                    height: 10px;
                    top: -10px;
                    animation: confetti-fall 3s linear infinite;
                }
                @keyframes confetti-fall {
                    0% { transform: translateY(0) rotate(0deg); opacity: 1; }
                    100% { transform: translateY(100vh) rotate(720deg); opacity: 0; }
                }
            `}</style>
        </div>
    );
};
