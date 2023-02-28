# marathon_contest_template  
## フォルダ  
in 入力ファイル  
out 出力ファイル  
scores e512testの比較用スコアファイル  
submits 提出したソースコード  
compile e512testでコンパイルした実行ファイル  
javatester ***Vis.javaからtester.jarをコンパイルするためのスクリプト  
## e512test.py  
マルチスレッドテストスクリプト  
このフォルダに無いと動かない物  
- topcoder marathon match
  - tester.jar
- atcoder heuristic contest
  - gen, vis, tester
```
コマンド例
e512test.py 開始位置 件数  
e512test.py 開始位置 件数 ビジュアライザオプション
e512test.py 開始位置 件数 ビジュアライザオプション -maxthread1  
e512test.py 開始位置 件数 ビジュアライザオプション -maxthread4  
```

## setting.ini  
e512test.pyの設定  
テストするソールファイル名  
実行時に追加するパス  
スコア比較大小の設定  
スレッド数  
コンパイルオプション  
ビジュアライザオプション  

## in_files_rename
対象 ファイル名に数字が入っているテキストファイル  
./in/input0001.txt -> ./in/1.txt

## test1_1.bat
```cmd /k e512test.py 1 1 -maxthread1```
## wsl_test1_1.bat
```cmd /k wsl python3 e512test.py 1 1 -maxthread1```

## submitfiles_to_sipfile.py
topcoder提出zip作成スクリプト  
submitfiles_to_zipfile.py ファイルパス（省略可）  


## ahcwvis-output-to-json-0-50.py
0-50のoutputファイルをjsonにまとめる  
## ahcwvis-tampermonkey-userscript.js
AHC Web版ヴィジュアライザのOutput:の隣あたりにFileボタンを追加  
jsonを読み込みシードごとにoutputを張り付ける  