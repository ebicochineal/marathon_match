# 環境
#### Win10ノート(i5-3320M)  
java 1.8.0_112  
cpp mingw64 x86_64-6.2.0-posix-seh-rt_v5-rev1  

#### Ubuntuデスクトップ(Core2Q9550)  
java 1.8.0_171  
cpp gcc version 7.2.0  
電気代節約のためマラソンマッチの時だけ起動  
  
  
# topcoder_mm_template  
## フォルダ  
best mtestの比較用スコアファイル  
submits 提出したソースコード  
compile mtestでコンパイルした実行ファイル  
tester tester.javaからtester.jarをコンパイルするためのスクリプトが入ってる  
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