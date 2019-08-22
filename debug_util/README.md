# debug_tuil

## VarDB
* 変数の値を記録して，表示する
* 任意の型に対して利用可能なように`std::string`で値を記録する
  * ある程度の範囲で場合分けをする場合には，`Append()`を行う前にユーザが量子化を行う
  * 基本的な量子化(e.g. log)などや動的にまとめる機能を追加すると便利かもしれない