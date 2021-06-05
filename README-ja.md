# Easy-ISLisp

Easy-ISLisp (EISL) はISLisp標準の解釈実行器及び翻訳系です。

Kenichi Sasagawa氏が制作しました（[Easy-ISLispのコンパイラ - Qiita](https://qiita.com/sym_num/items/793adfe118514668e5b0)）。

ISLispについては英語版Wikipedia（[ISLisp](https://en.wikipedia.org/wiki/ISLISP)）もご覧下さい。

次の動画ではEISLの紹介と導入方法の説明を行っています（英語）
[![Introduction of Easy-ISLisp](http://img.youtube.com/vi/KfrRyKMcTw8/0.jpg)](https://youtu.be/KfrRyKMcTw8)


## 導入方法

1. Gitでクローンした，又は単にダウンロードしたEasy-ISLispのディレクトリに移動する。
- GNU/Linuxをお使いの場合: 端末上で`sudo make install`と入力する。
- macOSをお使いの場合： 端末上で `sudo make install OPSYS=macos`と入力する。
- OpenBSDをお使いの場合：  端末上で `sudo make install OPSYS=openbsd`と入力する。
- お望みなら "PREFIX=$HOME" (or wherever) という引数を与えることもできます。
注意
Edlisのコンパイルでcurses.hファイルが見つからないというエラーになる場合があります。この場合にはターミナルより次のように入力してください。

```sh
sudo apt install libncurses-dev
```

ver1.4以後はWindowsはサポートされません。WindowsでWSLをお使いください。
注：WindowsバージョンのVS-CODEをWSLで使用する場合
参照　[Windows Subsystem for Linux で Visual Studio Code の使用を開始する](https://docs.microsoft.com/ja-jp/windows/wsl/tutorials/wsl-vscode)

　　　
動作確認している環境は次の通りです。
- Ubuntu 16.04 GCC 5.4
- Ubuntu 18.04 GCC 7.3
- Raspberry Pi3 Raspbian GCC 6.3
- openSUSE Leap 42.3 GCC 4.8.5
- Debian GNU/Linux GCC 6.3 GCC 7.3
- Linux Mint GCC ver 5.4
- Linux Mint GCC ver9.3.0
- macOS 11.1 clang 12.0.0 
- OpenBSD


## 実行

* GNU/Linuxをお使いの場合: 端末上で`eisl`と入力する。

Linux版では，対話状態で編集ができます。
編集機能を無効にしたい場合は，`-r`オプションを付けて起動して下さい。
```console
$ eisl -r
```

他の起動オプショオンについては下記を参照してください。

```
$ eisl -h
List of options:
-c           -- EISL starts after reading compiler.lsp.
-f           -- EISL starts after reading formatter.lsp.
-h           -- display help.
-l filename  -- EISL starts after reading the file.
-r           -- EISL does not use editable REPL.
-s filename  -- EISL runs the file with script mode.
-v           -- dislplay version number.
```

## 終了
(quit)と入力するか、Escキーを押したあとでQキーを押すと処理系が終了します。

-rオプションで起動した場合には(quit)あるいはCTRL+Dで処理系が終了します。

## 対話状態での編集機能

キー束縛は次の通りです。

| キー入力 | 動作 |
|:---:|:---:|
| <kbd>Ctrl</kbd>+<kbd>F</kbd>又は<kbd>→</kbd> | 右に移動
| <kbd>Ctrl</kbd>+<kbd>B</kbd>又は<kbd>←</kbd> | 左に移動
| <kbd>Ctrl</kbd>+<kbd>P</kbd>又は<kbd>↑</kbd> | 履歴を遡る
| <kbd>Ctrl</kbd>+<kbd>N</kbd>又は<kbd>↓</kbd> | 履歴を進む
| <kbd>Ctrl</kbd>+<kbd>A</kbd> | 行頭へ移動
| <kbd>Ctrl</kbd>+<kbd>E</kbd> | 行末へ移動
| <kbd>Ctrl</kbd>+<kbd>J</kbd>，<kbd>ctrl</kbd>+<kbd>M</kbd>又は<kbd>Enter</kbd> | 改行を挿入
| <kbd>Ctrl</kbd>+<kbd>H</kbd>又は<kbd>back-space</kbd> | 前方削除
| <kbd>Ctrl</kbd>+<kbd>D</kbd> | 後方削除
| <kbd>Ctrl</kbd>+<kbd>K</kbd> | 行の現在以後を切り取り
| <kbd>Ctrl</kbd>+<kbd>Y</kbd> | 切り取った行を貼り付け
| <kbd>Esc</kbd><kbd>Tab</kbd> | 補完


## 目標

Lispの知名度が向上することを願っています。
Lispをもっと多くの人々が楽しんでくれることを願っています。
EISLは簡単に操作できることを目的にしています。


## 翻訳系

EISLは翻訳系 (compiler) を備えています。
GCC向けのソースコード及び〔GCCを介して〕オブジェクトコードを生成します。

### 用法

```consloe
$ eisl -c  # -cオプションを付けて起動する。
```
又は
```lisp
(load "library/compiler.lsp")

(compile-file "foo.lsp")

(load "foo.o")
```

### 使用例

```console
$ eisl -c
Easy-ISLisp Ver1.6
> (compile-file "tests/tarai.lsp")
type inference
initialize
pass1
pass2
compiling PACK
compiling TARAI
compiling FIB
compiling FIB*
compiling ACK
compiling GFIB
compiling TAK
compiling LISTN
compiling TAKL
compiling CTAK
compiling CTAK-AUX

finalize
invoke GCC
T
> (load "tests/tarai.o")
T
> (time (tarai 12 6 0))
Elapsed Time(second)=0.024106
<undef>
> (time (ack 4 1))
Elapsed Time(second)=3.728262
<undef>
>
```

翻訳系自身を翻訳することができます。
翻訳はずっと早くなります。

Raspberry Pi 3では，主記憶領域不足のせいで`compiler.o`ファイルが利用できません。
`compiler.lsp`を使って下さい。


## エディタを起動する

EISLはエディタを備えています。
エディタを利用するには`edit`関数を用いて下さい。

併せてご覧ください: [sasagawa888/Edlis: Simple CUI editor for Easy-ISLisp](https://github.com/sasagawa888/Edlis)

### 用法

```scheme
(edit file-name-string)
```

### 例

```lisp
(edit "tests/foo.lsp")
```


## WiringPi

Raspberry PiにおいてはEislはWiringPiの組込み関数を含みます。


```lisp
EISL <==================================> C
(wiringpi-spi-setup ch speed) <===> wiringPiSPISetup (SPI_CH, SPI_SPEED)
(wiringpi-setup-gpio ) <===> wiringPiSetupGpio()
(pin-mode n 'output) <====> pinMode(n, OUTPUT) or 'input -> INPUT 'pwm-output -> PWM-OUTPUT
(digital-write n v) <===> digitalWrite(n, v)
(digital-write-byte v) <===> digitalWriteByte(value)
(digital-read pin) <===> digitalRead(pin)
(delay howlong) <===> void delay(unsigned int howLong)
(pull-up-dn-control pin pud) <===> pullUpDnControl(pin,pud)
(pwm-set-mode 'pwm-mode-ms) <===> pwmSetMode(PWM_MODE_MS); or 'pwm-mode-bal -> PWM_MODE_BAL
(pwm-set-clock n) <===> pwmSetClock(n)
(pwm-set-range n) <===> pwmSetRange(n)
(pwm-write pin value) <===> pwmWrite(pin , value)
```


### 例

```lisp
;; LED点滅

(defglobal pin 5)
(defglobal flag nil)

(defun test (n)
   (cond ((null flag) (wiringpi-setup-gpio)(setq flag t)))
   (pin-mode pin 'output)
   (for ((i 0 (+ i 1)))
        ((> i n) t)
        (digital-write pin 1)
        (delay 1000)
        (digital-write pin 0)
        (delay 1000)))


;; サーボモータを制御する。
;; SG90 Micro servo Digital 9g

(defun setup ()
  (cond ((null flag) (wiringpi-setup-gpio ) (setq flag t)))
  (pin-mode 18 'pwm-output)
  (pwm-set-mode 'pwm-mode-ms)
  (pwm-set-clock 400)
  (pwm-set-range 1024))

(defun test (n)
   (pwm-write 18 n))
```


## デバッグ用関数
- `(trace fn1 fn2 ... fn)`
- `(untrace fn1 fn2 ... fn)`又は`(untrace)`
- `(backtrace)`
- `(break)`
- `(macroexpand-1)`


## 拡張関数
- `(random n)` 0からnまでの無作為な整数
- `(random-real)` 0から1までの無作為な浮動小数
- `(gbc)` ガーベッジコレクション (GC) を実行.
  - `(gbc t)` GC実行時に通達する。
  - `(gbc nil)` GC実行時に通達しない。
  - `(gbc 'copy)`GCの方法をコピーイングGCに切り換える。
  - `(gbc 'm&s)`GCの方法をマーク＆スイープGCに切り換える。
- `(heapdump n)`ｎ番目のセルからダンプリストを表示する。
- `(instance n)`ｎ番目のセルの実体を表示する。
- `(defmodule name body)` tests/module.lsp 参照