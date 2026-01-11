import React, { useRef } from 'react';

interface SliderProps extends React.InputHTMLAttributes<HTMLInputElement> {
  label?: string;
  valueDisplay?: React.ReactNode;
}

export const Slider: React.FC<SliderProps> = ({ label, valueDisplay, className = '', ...props }) => {
  return (
    <div className={`w-full ${className}`}>
      <div className="flex justify-between items-center mb-2">
        {label && <label className="font-bold text-[var(--text-main)]">{label}</label>}
        {valueDisplay && <span className="font-bold text-[var(--primary)]">{valueDisplay}</span>}
      </div>
      <input
        type="range"
        className="w-full h-2 bg-[var(--surface-light)] rounded-lg appearance-none cursor-pointer accent-[var(--primary)] touch-none"
        {...props}
      />
      <style>{`
        input[type=range]::-webkit-slider-thumb {
          -webkit-appearance: none;
          height: 32px; /* No.22 Touch Area */
          width: 32px;
          border-radius: 50%;
          background: var(--surface-color);
          border: 2px solid var(--primary);
          box-shadow: 0 2px 6px rgba(0,0,0,0.2);
          margin-top: -12px;
        }
        input[type=range]::-webkit-slider-runnable-track {
          height: 8px;
          border-radius: 4px;
        }
      `}</style>
    </div>
  );
};
