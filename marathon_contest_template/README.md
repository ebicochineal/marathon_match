# marathon_contest_template  
## フォルダ  
in 入力ファイル  
out 出力ファイル  
scores e512testの比較用スコアファイル  
submits 提出したソースコード  
compile e512testでコンパイルした実行ファイル  
tester ***Vis.javaからtester.jarをコンパイルするためのスクリプト  
## e512test.py  
マルチスレッドテストスクリプト  
このフォルダにtesterがないと動かない  
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
マラソンタイプ指定
- half_marathon_java
- half_marathon_python
- half_marathon_interactive_java
- half_marathon_interactive_python
- topcoder_marathon
- atcoder_heuristic

## test.bat
cmd /k e512test.py  
## submitfiles_to_sipfile.py
topcoder提出zip作成スクリプト  
submitfiles_to_zipfile.py ファイルパス（省略可）  
