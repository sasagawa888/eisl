# Easy-ISLisp

Easy-ISLisp (EISL) はISLisp標準の解釈実行器及び翻訳系です。
![EISL](documents/eisl.png)

Kenichi Sasagawa氏が制作しました。

ISLispについては英語版Wikipedia（[ISLisp](https://en.wikipedia.org/wiki/ISLISP)）もご覧下さい。

次の動画ではEISLの紹介と導入方法の説明を行っています。
[![Introduction of Easy-ISLisp](http://img.youtube.com/vi/KfrRyKMcTw8/0.jpg)](https://www.youtube.com/watch?v=OkDb4ttbAZU)


## 導入方法

1. Gitでクローンした，又は単にダウンロードしたEasy-ISLispのディレクトリに移動する。
- 端末上で`sudo make install`と入力する。

注意
Easy-ISLispはncursesライブラリを必要とします。ncursesライブラリをインストールしてください。

```sh
sudo apt install libncurses-dev
```


2. Easy-ISLispを更新する場合
- 端末上で`sudo make clean`と入力する。
- 端末上で`sudo make install`と入力する。

　　　
# サポートOS
- Raspberry Pi OS
- Ubuntu
- Linux MINT

上記以外のOSにつきましては自己責任でお願いします。

## 実行

* GNU/Linuxをお使いの場合: 端末上で`eisl`と入力する。

Linux版では，対話状態で編集ができます。
編集機能を無効にしたい場合は，`-r`オプションを付けて起動して下さい。
```console
$ eisl -r
```

### Emacs サポート
sasanidasさんによってISLisp-modeが開発、公開されています。ビデオをご覧ください。
https://gitlab.com/sasanidas/islisp-mode
https://vimeo.com/614514131


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

# 入門記事
M HiroiさんがISLispの入門記事を公開なさっています。
http://www.nct9.ne.jp/m_hiroi/clisp/islisp.html

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


## エディタを起動する

EISLはエディタを備えています。
エディタを利用するには`edit`関数を用いて下さい。

併せてご覧ください: [Edlis](documents/EDLIS.md)

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
(delay-seconds howlong) <===> void delay(unsigned int howLong)
(delay-microseconds howlong) <===> void delayMicroseconds(unsigned int howLong)
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
        (delay-seconds 1)
        (digital-write pin 0)
        (delay-seconds 1)))


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
- `(atom x)` xが非consならTをそうでないならNILを返す
- `(eval x)` S式 x を評価する
- `(nconc x y)` リストｘとリストｙを破壊的にappendする。 
- `(random n)` 0からnまでの無作為な整数
- `(random-real)` 0から1までの無作為な浮動小数
- `(set-random n)` 乱数生成の種として非負整数ｎを与える 
- `(gbc)` ガーベッジコレクション (GC) を実行.
  - `(gbc t)` GC実行時に通達する。
  - `(gbc nil)` GC実行時に通達しない。
- `(heapdump n)`ｎ番目のセルからダンプリストを表示する。
- `(instance n)`ｎ番目のセルの実体を表示する。
- `(defmodule name body)` tests/module.lsp 参照
- `(import lib)` ライブラリをインポートする。
- `(quit)` インタプリタを終了する。
- `(getenv var)`  OSから環境変数を取得する　例　(getenv "EASY_ISLISP)
- `(line-argument n)` OSからｎ番目の起動オプションを取得する。ゼロスタート
- `(line-argument)` OSからすべての起動オプションを取得する。
- `(print obj)` objを標準ストリームに出力する。
- `(system cmd)` コマンド(cmd)をbashに送る　例 (system "ls")
- `(funcp x)` xがユーザー定義関数名ならばTをそうでなければNILを返す。
- `(subrp x)` xが組込関数ならばTをそうでなければNILを返す。
- `(macrop x)` xがマクロならばTをそうでなければNILを返す。
- `(fixnump x)` xが32bit小整数ならばTを、そうでなければNILを返す。
- `(longnump x)` xが64bit小整数ならばTを、そうでなければNILを返す。
- `(bignump x)` xが巨大整数ならばTをそうでなければNILを返す。
- `(macroexpand-1 x)` S式であるｘを１度だけマクロ展開する。
- `(macroexpand-all x)` S式であるｘを完全にマクロ展開する。

# 並列関数
- `(mp-create n)` n個のプロセスを生成する。PARA.mdを参照
- `(mp-call fun a1 ... an)` マルチプロセス並列でfunに引数を適用する。PARA.mdを参照
- `(mp-exec s1 ... sn)`  prognの並列版。PARA.mdを参照
- `(mp-and s1 ... sn)`  andの並列部分実行版。PARA.mdを参照
- `(mp-or s1 ... sn)`  orの並列部分実行版。PARA.mdを参照
- `(mp-eval n exp)`  n番目の子lispでexpを評価する。PARA.mdを参照
- `(mp-close)`  すべてのプロセスを閉じる。PARA.mdを参照
- `(mt-create n)` n個のスレッドを生成する。PARA1.mdを参照
- `(mt-call fun a1 ... an)` マルチスレッド並列でfunに引数を適用する。PARA1.mdを参照
- `(mt-exec s1 ... sn)`  prognの並列版。PARA1.mdを参照
- `(mt-let forms body)`  letの並列版。PARA1.mdを参照
- `(mt-lock s1 ... sn)`  ミューテックスをかけたprogn。PARA1.mdを参照
- `(mt-close)`  すべてのスレッドを閉じる。PARA1.mdを参照
- `(dp-create n)` n個の分散を生成する。PARA2.mdを参照
- `(dp-call fun a1 ... an)` 分散並列でfunに引数を適用する。PARA2.mdを参照
- `(dp-exec s1 ... sn)`  prognの分散並列版。PARA2.mdを参照
- `(dp-part sw s1 ... sn)`  prognの分散並列部分実行版。PARA2.mdを参照
- `(dp-eval n exp)`  n番目の子lispでexpを評価する。PARA2.mdを参照
- `(dp-transfer fn)`  ファイルをすべての子lispに転送する。PARA2.mdを参照
- `(dp-compile fn)`  ファイルを親lisp及びすべての子lispでコンパイルする。PARA2.mdを参照
- `(dp-load fn)`  ファイルを親lisp及びすべての子lispにロードする。PARA2.mdを参照
- `(dp-close)`  すべての子機との通信を閉じる。PARA2.mdを参照
- `(dp-halt)`　　すべての子機との通信を閉じるとともにシャットダウンする。PARA2.mdを参照

# TCP/IP
- `(create-server-socket n)` ポート番号ｎでサーバーとしてのソケットを生成する。
- `(create-client-socket n ip)` ポート番号ｎでIPアドレスに対しソケットを生成する。
- `(send-socket socket str)` socketに対して文字列strを送信する。
- `(recv-socket socket)` socketから文字列を受信する。 