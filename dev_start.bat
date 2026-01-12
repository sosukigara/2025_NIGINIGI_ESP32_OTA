@echo off
chcp 65001 >nul
echo ---------------------------------------------------
echo  にぎにぎ 開発サーバー＆プレビュー起動
echo ---------------------------------------------------

cd /d "%~dp0frontend"

:: サーバーを別ウィンドウで起動
echo サーバーを起動しています...
start "Onigiri React Server" npm run dev -- --host 127.0.0.1

:: 起動待ち（5秒）
echo 起動を待機中...
timeout /t 5 /nobreak >nul

:: ブラウザで開く
echo ブラウザを開きます...
start http://127.0.0.1:5173/

echo.
echo 準備完了しました！
echo サーバーは別ウィンドウで実行中です。
echo 終了時はそのウィンドウを閉じてください。
pause
