# ebicochinealのマラソンマッチ環境  

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