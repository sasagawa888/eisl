# 関数検索システム
ISLisp関数検索システム

# 謝辞
このプログラムは五味先生が作成したものです。五味先生の許可を得て利用させていただきました。
ありがとうございます。

# 使用方法

(import "functionsj")


## Search Function 
関数名の先頭の一部を与えて、該当するシステム関数のシグネチャをリストにする

(search-function function-name [short])

```
    Exp. (search-function 'char) 
          --->
         (((CHARACTERP OBJ) BOOLEAN) 
          ((CHAR= CHAR1 CHAR2) BOOLEAN) 
           ... )
    Exp. (search-function 'char t) 
          --->
         (CHARACTERP CHAR= ...) 
```

## Say Function
 関数名の先頭の一部を与えて、該当するシステム関数の説明を整形して画面に表示する


```
   (say function-name [output-file]) function-name で始まる関数を表示する

   (say-all [output-file]) すべてのシステム関数の説明を整形して画面に表示する

```

