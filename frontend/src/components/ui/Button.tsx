import React from 'react';
import { useHaptic } from '../../hooks/useHaptic';

interface ButtonProps extends React.ButtonHTMLAttributes<HTMLButtonElement> {
  variant?: 'primary' | 'secondary' | 'danger' | 'ghost';
  fullWidth?: boolean;
}

export const Button: React.FC<ButtonProps> = ({ 
  children, 
  variant = 'primary', 
  fullWidth = false, 
  className = '', 
  onClick,
  ...props 
}) => {
  const { vibrate } = useHaptic();

  const handleClick = (e: React.MouseEvent<HTMLButtonElement>) => {
    vibrate(50);
    onClick?.(e);
  };

  const baseStyles = "font-bold rounded-2xl transition-all active:scale-95 disabled:opacity-50 disabled:cursor-not-allowed flex items-center justify-center gap-2";
  const variants = {
    primary: "bg-[var(--primary)] text-white shadow-lg shadow-orange-500/30",
    secondary: "btn-secondary shadow-sm",
    danger: "bg-red-500 text-white shadow-lg shadow-red-500/30",
    ghost: "bg-transparent text-[var(--text-sub)] hover:bg-gray-100 dark:hover:bg-white/10"
  };
  const sizeStyles = "min-h-[64px] px-6 py-4"; // No.22 Touch Area

  return (
    <button
      className={`${baseStyles} ${variants[variant]} ${sizeStyles} ${fullWidth ? 'w-full' : ''} ${className}`}
      onClick={handleClick}
      {...props}
    >
      {children}
    </button>
  );
};
