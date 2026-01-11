import React, { useEffect, useState } from 'react';
import { Button } from './Button';

interface ModalProps {
    isOpen: boolean;
    onClose: () => void;
    title: string;
    children: React.ReactNode;
    footer?: React.ReactNode;
}

export const Modal: React.FC<ModalProps> = ({ isOpen, onClose, title, children, footer }) => {
    const [visible, setVisible] = useState(false);
    const [animate, setAnimate] = useState(false);

    useEffect(() => {
        if (isOpen) {
            setVisible(true);
            setTimeout(() => setAnimate(true), 10);
        } else {
            setAnimate(false);
            const timer = setTimeout(() => setVisible(false), 300);
            return () => clearTimeout(timer);
        }
    }, [isOpen]);

    if (!visible) return null;

    return (
        <div className={`fixed inset-0 z-[100] flex items-center justify-center p-4 transition-all duration-300 ${animate ? 'bg-black/60 backdrop-blur-sm' : 'bg-black/0 backdrop-blur-none'}`}
             onClick={onClose}>
            <div 
                className={`bg-[#1c1c1e] border border-white/10 w-full max-w-sm rounded-[2rem] shadow-2xl p-6 transform transition-all duration-300 ${animate ? 'scale-100 opacity-100 translate-y-0' : 'scale-95 opacity-0 translate-y-4'}`}
                onClick={e => e.stopPropagation()}
            >
                <h3 className="text-xl font-bold text-white mb-2 text-center">{title}</h3>
                <div className="text-gray-400 text-center mb-6 text-sm leading-relaxed">
                    {children}
                </div>
                {footer}
            </div>
        </div>
    );
};
