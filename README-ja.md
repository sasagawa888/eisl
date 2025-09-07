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

## デバッグ用関数
documents/DEBUG.md を参照してください。

## 拡張関数
documents/EXTENDED.md を参照してください。

# 並列関数
documents/PARA.md を参照してください。

# TCP/IP
documents/TCPIP.md を参照してください。
