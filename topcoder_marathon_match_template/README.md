# topcoder_mm_template  
## フォルダ  
scores mtestの比較用スコアファイル  
submits 提出したソースコード  
compile mtestでコンパイルした実行ファイル  
tester ***Vis.javaからtester.jarをコンパイルするためのスクリプト  
statistics_script 最終結果統計スクリプト  
## mtest.py  
マルチスレッドテストスクリプト  
このフォルダにtester.jarがないと動かない  
```
コマンド例
mtest.py 開始位置 件数  
mtest.py 開始位置 件数 topcoderビジュアライザオプション
mtest.py 開始位置 件数 topcoderビジュアライザオプション -maxthread1  
mtest.py 開始位置 件数 topcoderビジュアライザオプション -maxthread4  
```

## setting.ini  
mtest.pyの設定  
テストするソールファイル名  
実行時に追加するパス  
スコア比較大小の設定  
スレッド数  
コンパイルオプション  
ビジュアライザオプション  
## test.bat
cmd /k mtest.py  
## submitfiles_to_sipfile.py
新プラットフォームの提出zip作成スクリプト  
submitfiles_to_zipfile.py ファイルパス（省略可）  
