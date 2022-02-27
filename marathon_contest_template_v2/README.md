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
- atcoder halfmarathon interactive python
  - tester.py
- atcoder halfmarathon python
  - judge.py, generator.py

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
```
half_marathon_java
half_marathon_python
half_marathon_interactive_java
half_marathon_interactive_python
topcoder_marathon
// AHC001
// atcoder_heuristic_gen_redirect

// AHC002, AHC004
atcoder_heuristic

// HACK TO THE FUTURE for Youth＋
atcoder_heuristic_b
atcoder_heuristic_c

// AHC003
atcoder_heuristic_interactive

// AHC008
atcoder_heuristic_interactive2
```

## test1_1.bat
```cmd /k e512test.py 1 1 -maxthread1```
## wsl_test1_1.bat
```cmd /k wsl python3 e512test.py 1 1 -maxthread1```

## submitfiles_to_sipfile.py
topcoder提出zip作成スクリプト  
submitfiles_to_zipfile.py ファイルパス（省略可）  
