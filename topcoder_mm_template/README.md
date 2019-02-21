# topcoder_mm_template  
## フォルダ  
scores mtestの比較用スコアファイル  
submits 提出したソースコード  
compile mtestでコンパイルした実行ファイル  
tester ***Vis.javaからtester.jarをコンパイルするためのスクリプト  
statistics_script 最終結果統計スクリプト  
## mtest.py  
マルチスレッドでテストする  
このフォルダにtester.jarがないと動かない
## setting.ini  
mtest.pyの設定  
テストするソールファイル名  
実行時に追加するパス  
スコア比較大小の設定  
スレッド数  
コンパイルオプション  
## test.bat
cmd /k mtest.py

## mtest.py
マルチスレッドテストスクリプト  
mtest.py 開始位置 件数  

