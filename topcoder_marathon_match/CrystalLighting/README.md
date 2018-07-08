CrystalLighting  
  
暫定順位 49/127  
  
問題  
- クリスタルの色通りにランタンで光を当てるとポイントが貰える。青黄赤20、緑紫橙30、違う色-10
- 光を反射(曲げる)するミラーと壁をいくつか設置可能
- ランタンの光が別のランタンに当たるとダメ

アプローチ
- (1) 全スコア計算。最初に壁ミラーすべておいて最後にランタン計算する。遅い
- (2) ランタンのみのスコア計算。１つごとにどれだけ良くなるか計算。条件の半分を満たしていたらスコアを+10条件を満たすことができない光を当ててしまったら-10
- [1] 区画を分けてその区画で一番スコアの高いのを置いていく。
- [2] ランダムにランタンを取り除いてもう一度置き直す。
- [3] 時間(5500ms)まで[2]を繰り返して一番良いものを選ぶ。
- [4] 置いたものを取り除いてスコアが伸びそうなとこを消す。500ms
- [5] ２つの同じ色のランタンが１つで済みそうなとこを探して置き換える。２つのランタンの光が交わる場所にミラーが置けないか探す。
- [6] 動かして壁ミラーを置いてみたり、壁、ミラー、ランタンを置いてスコアが伸びそうな所があったら置く。動かしてさらに色や物を変えたりしてスコアが伸びそうなところを探す。
- [7] 時間(9500ms)まで[5-6]繰り返し
- [8] 置いたものを取り除いてスコアが伸びそうなとこを消す。
- [1-2]では(2)でスコアを計算して置いて最後に(1)で前より良いのを選ぶ。[3-8]は(1)で計算｡ミラーも壁も１つ置くごとにスコア出したかったけどかなり面倒で避けてしまった。
  
