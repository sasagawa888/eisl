# 謝辞
五味先生の関数検索システムのテキストを一部改変、流用させていただきました。ありがとうございます。

# Easy-ISLisp 関数一覧 *拡張分を含む

```
関数: BASIC-ARRAY-P
仕様: (BASIC-ARRAY-P OBJ) ---> BOOLEAN
説明: obj が配列または文字列, ベクタ かどうかをチェックする

関数: BASIC-ARRAY*-P
仕様: (BASIC-ARRAY*-P OBJ) ---> BOOLEAN
説明: obj が多次元配列であるかをチェックする

関数: GENERAL-ARRAY*-P
仕様: (GENERAL-ARRAY*-P OBJ) ---> BOOLEAN
説明: obj が多次元配列であるかをチェックする

関数: CREATE-ARRAY
仕様: (CREATE-ARRAY DIMENSIONS INITIAL-ELEMENT +) ---> <BASIC-ARRAY>
説明: 配列を生成する

関数: AREF
仕様: (AREF BASIC-ARRAY Z *) ---> <OBJECT>
説明: 配列 basic-array の z 番目の要素を取り出す

関数: GAREF
仕様: (GAREF GENERAL-ARRAY Z *) ---> <OBJECT>
説明: 配列 general-array の z 番目の要素を取り出す

関数: SET-AREF
仕様: (SET-AREF OBJ BASIC-ARRAY Z *) ---> <OBJECT>
説明: 配列 basic-array の z 番目に要素 obj をセットする

関数: SET-GAREF
仕様: (SET-GAREF OBJ GENERAL-ARRAY Z *) ---> <OBJECT>
説明: 配列 general-array の z 番目に要素 obj をセットする

関数: ARRAY-DIMENSIONS
仕様: (ARRAY-DIMENSIONS BASIC-ARRAY) ---> <LIST>
説明: 配列 basic-array の次元をリストで返す

関数: CHARACTERP
仕様: (CHARACTERP OBJ) ---> BOOLEAN
説明: obj が文字であるかをチェックする

関数: CHAR=
仕様: (CHAR= CHAR1 CHAR2) ---> BOOLEAN
説明: char1 と char2 の文字が等しいかをチェックする

関数: CHAR/=
仕様: (CHAR/= CHAR1 CHAR2) ---> BOOLEAN
説明: char1 と char2 の文字が等しくないかをチェックする

関数: CHAR<
仕様: (CHAR< CHAR1 CHAR2) ---> BOOLEAN
説明: char1 の文字コードが char2 よりも大きいかをチェックする

関数: CHAR>
仕様: (CHAR> CHAR1 CHAR2) ---> BOOLEAN
説明: char1 の文字コードが char2 よりも小さいかをチェックする

関数: CHAR<=
仕様: (CHAR<= CHAR1 CHAR2) ---> BOOLEAN
説明: char1 の文字コードが char2 よりも大きいかまたは等しいかをチェックする

関数: CHAR>=
仕様: (CHAR>= CHAR1 CHAR2) ---> BOOLEAN
説明: char1 の文字コードが char2 よりも小さいまたは等しいかをチェックする

関数: ERROR
仕様: (ERROR ERROR-STRING OBJ *) ---> <OBJECT>
説明: エラーをシグナルする

関数: CERROR
仕様: (CERROR CONTINUE-STRING ERROR-STRING OBJ *) ---> <OBJECT>
説明: 継続可能なエラーをシグナルする

関数: SIGNAL-CONDITION
仕様: (SIGNAL-CONDITION CONDITION CONTINUABLE) ---> <OBJECT>
説明: コンディションを操作するためにシグナルする

関数: IGNORE-ERRORS
仕様: (IGNORE-ERRORS FORM *) ---> <OBJECT>
説明: エラーが出ても無視する(特殊形式)

関数: REPORT-CONDITION
仕様: (REPORT-CONDITION CONDITION STREAM) ---> <CONDITION>
説明: コンディション condition をストリーム stream にレポートする

関数: CONDITION-CONTINUABLE
仕様: (CONDITION-CONTINUABLE CONDITION) ---> <OBJECT>
説明: 継続可能かをチェックする

関数: CONTINUE-CONDITION
仕様: (CONTINUE-CONDITION CONDITION VALUE +) ---> <OBJECT>
説明: コンディションから継続する

関数: WITH-HANDLER
仕様: (WITH-HANDLER HANDLER FORM *) ---> <OBJECT>
説明: ハンドラを評価してフォームを実行する(特殊形式)

関数: ARITHMETIC-ERROR-OPERATION
仕様: (ARITHMETIC-ERROR-OPERATION ARITHMETIC-ERROR) ---> <FUNCTION>
説明: 算術演算エラーのオペレータを返す

関数: ARITHMETIC-ERROR-OPERANDS
仕様: (ARITHMETIC-ERROR-OPERANDS ARITHMETIC-ERROR) ---> <LIST>
説明: 算術演算エラーのオペランドを返す

関数: DOMAIN-ERROR-OBJECT
仕様: (DOMAIN-ERROR-OBJECT DOMAIN-ERROR) ---> <OBJECT>
説明: ドメインエラー domain-error で生成されたオブジェクトを返す

関数: DOMAIN-ERROR-EXPECTED-CLASS
仕様: (DOMAIN-ERROR-EXPECTED-CLASS DOMAIN-ERROR) ---> <CLASS>　
説明: ドメインエラー domain-error で生成された望ましかったドメインを返す

関数: PARSE-ERROR-STRING
仕様: (PARSE-ERROR-STRING PARSE-ERROR) ---> <STRING>
説明: 解析エラー parse-error で生成された文字列を返す

関数: PARSE-ERROR-EXPECTED-CLASS
仕様: (PARSE-ERROR-EXPECTED-CLASS PARSE-ERROR) ---> <CLASS>
説明: 解析エラー parse-error で生成された望ましいクラスを返す

関数: SIMPLE-ERROR-FORMAT-STRING
仕様: (SIMPLE-ERROR-FORMAT-STRING SIMPLE-ERROR) ---> <STRING>
説明: simple-error で生成された文字列を返す

関数: SIMPLE-ERROR-FORMAT-ARGUMENTS
仕様: (SIMPLE-ERROR-FORMAT-ARGUMENTS SIMPLE-ERROR) ---> <LIST>
説明: simple-error で生成された引数リストを返す

関数: STREAM-ERROR-STREAM
仕様: (STREAM-ERROR-STREAM STREAM-ERROR) ---> <STREAM>
説明: ストリームエラー stream-error で生成されたストリームを返す

関数: UNDEFINED-ENTITY-NAME
仕様: (UNDEFINED-ENTITY-NAME UNDEFINED-ENTITY) ---> <SYMBOL>
説明: 未定義エンティティ undefined-entity で生成されたシンボルを返す

関数: UNDEFINED-ENTITY-NAMESPACE
仕様: (UNDEFINED-ENTITY-NAMESPACE UNDEFINED-ENTITY) ---> <SYMBOL>
説明: 未定義エンティティ undefined-entity で生成された名前空間を返す

関数: QUOTE
仕様: (QUOTE OBJ) ---> <OBJECT>
説明: obj の参照を返す(特殊形式)

関数: SETQ
仕様: (SETQ VAR FORM) ---> <OBJECT>
説明: 変数 var にフォーム form の評価結果を代入する(特殊形式)

関数: SETF
仕様: (SETF PLACE FORM) ---> <OBJECT>
説明: 場所 place にフォーム form の評価結果を代入する(特殊形式)

関数: LET
仕様: (LET ((VAR FORM) *) BODY-FORM *) ---> <OBJECT>
説明: 局所変数を定義し、その環境で実行する(特殊形式)

関数: LET*
仕様: (LET* ((VAR FORM) *) BODY-FORM *) ---> <OBJECT>
説明: letと同様であるが局所変数を順次束縛するところが異なる(特殊形式)

関数: DYNAMIC
仕様: (DYNAMIC VAR) ---> <OBJECT>
説明: 動的変数を宣言する(特殊形式)

関数: SETF
仕様: (SETF (DYNAMIC VAR) FORM) ---> <OBJECT>
説明: 動的変数に値を代入する(特殊形式)

関数: DYNAMIC-LET
仕様: (DYNAMIC-LET ((VAR FORM) *) BODY-FORM *) ---> <OBJECT>
説明: 動的変数の一時的束縛をする(特殊形式)

関数: IF
仕様: (IF TEST-FORM THEN-FORM ELSE-FORM+) ---> <OBJECT>
説明: 条件の結果で分岐する(特殊形式)

関数: COND
仕様: (COND (TEST FORM *) *) ---> <OBJECT>
説明: 条件の結果で分岐する(特殊形式)

関数: CASE
仕様: (CASE KEYFORM ((KEY *) FORM *) * (T FORM *) +) ---> <OBJECT>
説明: keyform の値によって多岐に分岐する(特殊形式)

関数: CASE-USING
仕様: (CASE-USING PREDFORM KEYFORM ((KEY *) FORM *) * (T FORM *) +) ---> <OBJECT>
説明: case 文とほぼ同様であるが,述語関数 predform を比較に使う(特殊形式)

関数: PROGN
仕様: (PROGN FORM*) ---> <OBJECT>
説明: 順次実行を行なう(特殊形式)

関数: WHILE
仕様: (WHILE TEST-FORM BODY-FORM *) ---> <NULL>
説明: test-form が nil でない間 body-form を実行する(特殊形式)

関数: FOR
仕様: (FOR (ITERATION-SPEC *) (END-TEST RESULT *) FORM *) ---> <OBJECT>
説明: iteration-spec で示された初期値とステッパを用い end-test が nil でない間繰り返し実行する(特殊形式)

関数: BLOCK
仕様: (BLOCK NAME FORM *) ---> <OBJECT>
説明: ブロックタグを付けて順次実行する(特殊形式)

関数: RETURN-FROM
仕様: (RETURN-FROM NAME RESULT-FORM) ---> TRANSFERS-CONTROL-AND-DATA
説明: name ブロックを抜ける(特殊形式)

関数: CATCH
仕様: (CATCH TAG-FORM FORM *) ---> <OBJECT>
説明: tag-form をキャッチし、form を実行する(特殊形式)

関数: THROW
仕様: (THROW TAG-FORM RESULT-FORM) ---> TRANSFERS-CONTROL-AND-DATA
説明: tag-form をスローする(特殊形式)

関数: TAGBODY
仕様: (TAGBODY TAGBODY-TAG * FORM *) ---> <OBJECT>
説明: tagbody-tagを付けて順次実行する(特殊形式)

関数: GO
仕様: (GO TAGBODY-TAG) ---> TRANSFERS-CONTROL
説明: tag-bodyブロックに制御を移す(特殊形式)

関数: UNWIND-PROTECT
仕様: (UNWIND-PROTECT FORM CLEANUP-FORM *) ---> <OBJECT>
説明: formの評価を終了するときは必ず cleanup-form を実行する(特殊形式)

関数: THE
仕様: (THE CLASS-NAME FORM) ---> <OBJECT>
説明: form の実行結果のクラスを class-name と宣言する(特殊形式)

関数: ASSURE
仕様: (ASSURE CLASS-NAME FORM) ---> <OBJECT>
説明: form の実行結果のクラスを class-name と主張する、異なる場合はエラーとなる(特殊形式)

関数: CONVERT
仕様: (CONVERT OBJ CLASS-NAME) ---> <OBJECT>
説明: obj をクラス class-name に変換する(特殊形式)

関数: PROBE-FILE
仕様: (PROBE-FILE FILENAME) ---> BOOLEAN　
説明: filename のファイルが存在するかをチェックする

関数: FILE-POSITION
仕様: (FILE-POSITION STREAM) ---> <INTEGER>
説明: stream の現在のファイル位置を返す

関数: SET-FILE-POSITION
仕様: (SET-FILE-POSITION STREAM Z) ---> <INTEGER>
説明:  stream のファイル位置を z に設定する

関数: FILE-LENGTH
仕様: (FILE-LENGTH FILENAME ELEMENT-CLASS) ---> <INTEGER>
説明: filename のファイルを element-class のファイルとしてのサイズを返す

関数: FUNCTIONP
仕様: (FUNCTIONP OBJ) ---> BOOLEAN
説明: obj が関数であるかをチェックする

関数: FUNCTION
仕様: (FUNCTION FUNCTION-NAME) ---> <FUNCTION>
説明: function-name を名前とする関数を返す(特殊形式)

関数: LAMBDA
仕様: (LAMBDA LAMBDA-LIST FORM *) ---> <FUNCTION>
説明: ラムダ式を生成する(特殊形式)

関数: LABELS
仕様: (LABELS ((FUNCTION-NAME LAMBDA-LIST FORM *) *) BODY-FORMS *) ---> <OBJECT>
説明: 局所関数の束縛をする、順次束縛（再帰的定義が可能）である点が flet と異なる(特殊形式)

関数: FLET
仕様: (FLET ((FUNCTION-NAME LAMBDA-LIST FORM *) *) BODY-FORMS *) ---> <OBJECT>
説明: 局所関数の束縛をする(特殊形式)

関数: APPLY
仕様: (APPLY FUNCTION OBJ * LIST) ---> <OBJECT>
説明: 関数を適用する

関数: FUNCALL
仕様: (FUNCALL FUNCTION OBJ *) ---> <OBJECT>
説明: 関数を呼び出す

関数: DEFCONSTANT
仕様: (DEFCONSTANT NAME FORM) ---> <SYMBOL>
説明: 定数を宣言する(特殊形式)

関数: DEFGLOBAL
仕様: (DEFGLOBAL NAME FORM) ---> <SYMBOL>
説明: 広域変数を宣言する(特殊形式)

関数: DEFDYNAMIC
仕様: (DEFDYNAMIC NAME FORM) ---> <SYMBOL>
説明: 動的変数を宣言する(特殊形式)

関数: DEFUN
仕様: (DEFUN FUNCTION-NAME LAMBDA-LIST FORM *) ---> <SYMBOL>
説明: 関数を定義する(特殊形式)

関数: READ
仕様: (READ INPUT-STREAM + EOS-ERROR-P + EOS-VALUE +) ---> <OBJECT>
説明: input-stream からS式として読む

関数: READ-CHAR
仕様: (READ-CHAR INPUT-STREAM + EOS-ERROR-P + EOS-VALUE +) ---> <OBJECT>
説明: input-stream から1文字読む

関数: PREVIEW-CHAR
仕様: (PREVIEW-CHAR INPUT-STREAM + EOS-ERROR-P + EOS-VALUE +) ---> <OBJECT>
説明: 次に読み込む文字を返す（1文字先読み。ファイルポジションは変化しない）

関数: READ-LINE
仕様: (READ-LINE INPUT-STREAM + EOS-ERROR-P + EOS-VALUE +) ---> <OBJECT>
説明: 1行を文字列として読む

関数: STREAM-READY-P
仕様: (STREAM-READY-P INPUT-STREAM) ---> BOOLEAN
説明: ストリームが読み込み可能になっているか

関数: FORMAT
仕様: (FORMAT OUTPUT-STREAM FORMAT-STRING OBJ *) ---> <NULL>
説明: format-string に従って obj を出力する

関数: FORMAT-CHAR
仕様: (FORMAT-CHAR OUTPUT-STREAM CHAR) ---> <NULL>
説明: 1文字出力する

関数: FORMAT-FLOAT
仕様: (FORMAT-FLOAT OUTPUT-STREAM FLOAT) ---> <NULL>
説明: 浮動小数点数として出力する

関数: FORMAT-FRESH-LINE
仕様: (FORMAT-FRESH-LINE OUTPUT-STREAM) ---> <NULL>
説明: 改行する

関数: FORMAT-INTEGER
仕様: (FORMAT-INTEGER OUTPUT-STREAM INTEGER RADIX) ---> <NULL>
説明: 整数として出力する

関数: FORMAT-OBJECT
仕様: (FORMAT-OBJECT OUTPUT-STREAM OBJ ESCAPE-P) ---> <NULL>
説明: オブジェクトとして出力する

関数: FORMAT-TAB
仕様: (FORMAT-TAB OUTPUT-STREAM COLUMN) ---> <NULL>
説明: タブを出力する

関数: READ-BYTE
仕様: (READ-BYTE INPUT-STREAM EOS-ERROR-P + EOS-VALUE +) ---> <INTEGER>
説明: バイトとして読む

関数: WRITE-BYTE
仕様: (WRITE-BYTE Z OUTPUT-STREAM) ---> <INTEGER>
説明: バイトとして書く

関数: CONSP
仕様: (CONSP OBJ) ---> BOOLEAN
説明: コンスかをチェックする

関数: CONS
仕様: (CONS OBJ1 OBJ2) ---> <CONS>
説明: コンスを生成する

関数: CAR
仕様: (CAR CONS) ---> <OBJECT>
説明: コンスの Car 部を取り出す

関数: CDR
仕様: (CDR CONS) ---> <OBJECT>
説明: コンスの Cdr 部を取り出す

関数: SET-CAR
仕様: (SET-CAR OBJ CONS) ---> <OBJECT>
説明: コンスの Car 部にセットする

関数: SET-CDR
仕様: (SET-CDR OBJ CONS) ---> <OBJECT>
説明: コンスの Cdr 部にセットする

関数: NULL
仕様: (NULL OBJ) ---> BOOLEAN
説明: NULL かチェックする

関数: LISTP
仕様: (LISTP OBJ) ---> BOOLEAN
説明: リストかチェックする

関数: CREATE-LIST
仕様: (CREATE-LIST I INITIAL-ELEMENT +) ---> <LIST>
説明: 長さ i 初期値 initial-element のリストを生成する

関数: LIST
仕様: (LIST OBJ *) ---> <LIST>
説明: obj を要素とするリストを生成する

関数: REVERSE
仕様: (REVERSE LIST) ---> <LIST>
説明: リストを逆順にする（元のリストは破壊しない）

関数: NREVERSE
仕様: (NREVERSE LIST) ---> <LIST>
説明: リストを逆順にする（元のリストは破壊される）

関数: APPEND
仕様: (APPEND LIST *) ---> <LIST>
説明: リストを連結する

関数: MEMBER
仕様: (MEMBER OBJ LIST) ---> <LIST>
説明: リスト list に obj が含まれていれば、obj を先頭とする部分リストを返す

関数: MAPCAR
仕様: (MAPCAR FUNCTION LIST +) ---> <LIST>
説明: リスト list の要素に関数 function を実行し結果のリストを返す

関数: MAPC
仕様: (MAPC FUNCTION LIST +) ---> <LIST>
説明: リスト list の要素に関数 function を実行し引数のリスト list を返す

関数: MAPCAN
仕様: (MAPCAN FUNCTION LIST +) ---> <LIST>
説明: MAPCAR の操作を list を破壊して行なう

関数: MAPLIST
仕様: (MAPLIST FUNCTION LIST +) ---> <LIST>
説明: リスト list の部分リストに関数 function を実行し、結果のリストを返す

関数: MAPL
仕様: (MAPL FUNCTION LIST +) ---> <LIST>
説明: リスト list の部分リストに関数 function を実行し、引数リスト list を返す

関数: MAPCON
仕様: (MAPCON FUNCTION LIST +) ---> <LIST>
説明: MAPLIST の操作を list を破壊して行なう

関数: ASSOC
仕様: (ASSOC OBJ ASSOCIATION-LIST) ---> <CONS>
説明: 連想リスト association-list に対して obj をキーとする値を返す

関数: DEFMACRO
仕様: (DEFMACRO MACRO-NAME LAMBDA-LIST FORM *) ---> <SYMBOL>
説明: マクロを定義する(特殊形式)

関数: IDENTITY
仕様: (IDENTITY OBJ) ---> <OBJECT>　
説明: obj をそのまま返す

関数: GET-UNIVERSAL-TIME
仕様: (GET-UNIVERSAL-TIME) ---> <INTEGER>
説明: ユニバーサルタイム（秒）を返す

関数: GET-INTERNAL-RUN-TIME
仕様: (GET-INTERNAL-RUN-TIME) ---> <INTEGER>
説明: 実行時間を返す

関数: GET-INTERNAL-REAL-TIME
仕様: (GET-INTERNAL-REAL-TIME) ---> <INTEGER>
説明: 経過時間を返す

関数: INTERNAL-TIME-UNITS-PER-SECOND
仕様: (INTERNAL-TIME-UNITS-PER-SECOND) ---> <INTEGER>
説明: 1秒当たりのインターナルタイム単位を返す

関数: NUMBERP
仕様: (NUMBERP OBJ) ---> BOOLEAN
説明: obj が数型であるかをチェックする

関数: PARSE-NUMBER
仕様: (PARSE-NUMBER STRING) ---> <NUMBER>
説明: 文字列 string を解析して数型に変換する

関数: =
仕様: (= X1 X2) ---> BOOLEAN
説明: 数値が等しいかをチェックする

関数: /=
仕様: (/= X1 X2) ---> BOOLEAN
説明: 数値が等しくないかをチェックする

関数: >=
仕様: (>= X1 X2) ---> BOOLEAN
説明: 数値 x1 が x2 以上であるかをチェックする

関数: <=
仕様: (<= X1 X2) ---> BOOLEAN
説明: 数値 x1 が x2 以下であるかをチェックする

関数: >
仕様: (> X1 X2) ---> BOOLEAN
説明: 数値 x1 が x2 より大きいかをチェックする

関数: <
仕様: (< X1 X2) ---> BOOLEAN
説明: 数値 x1 が x2 より小さいかをチェックする

関数: +
仕様: (+ X *) ---> <NUMBER>
説明: 数値を加算する

関数: *
仕様: (* X *) ---> <NUMBER>
説明: 数値を乗算する

関数: -
仕様: (- X Y *) ---> <NUMBER>
説明: 数値を減算する

関数: QUOTIENT
仕様: (QUOTIENT DIVIDEND DIVISOR +) ---> <NUMBER>
説明: 数値を除算する

関数: RECIPROCAL
仕様: (RECIPROCAL X) ---> <NUMBER>
説明: 数値を逆数にする

関数: MAX
仕様: (MAX X Y *) ---> <NUMBER>
説明: 数値の最大値を返す

関数: MIN
仕様: (MIN X Y *) ---> <NUMBER>
説明: 数値の最小値を返す

関数: ABS
仕様: (ABS X) ---> <NUMBER>
説明: 数値の絶対値を返す

関数: EXP
仕様: (EXP X) ---> <NUMBER>
説明: 数値の指数関数の値を返す

関数: LOG
仕様: (LOG X) ---> <NUMBER>
説明: 数値の自然対数の値を返す

関数: EXPT
仕様: (EXPT X1 X2) ---> <NUMBER>
説明: 数値をべき乗する

関数: SQRT
仕様: (SQRT X) ---> <NUMBER>
説明: 数値の平方根を返す

関数: SIN
仕様: (SIN X) ---> <NUMBER>
説明: 数値の sin 関数の値を返す

関数: COS
仕様: (COS X) ---> <NUMBER>
説明: 数値の cos 関数の値を返す

関数: TAN
仕様: (TAN X) ---> <NUMBER>
説明: 数値の tan 関数の値を返す

関数: ATAN
仕様: (ATAN X) ---> <NUMBER>
説明: 数値の atan 関数の値を返す

関数: ATAN2
仕様: (ATAN2 X1 X2) ---> <NUMBER>
説明: 数値の atan2 関数の値を返す

関数: SINH
仕様: (SINH X) ---> <NUMBER>
説明: 数値の sinh 関数の値を返す

関数: COSH
仕様: (COSH X) ---> <NUMBER>
説明: 数値の cosh 関数の値を返す

関数: TANH
仕様: (TANH X) ---> <NUMBER>
説明: 数値の tanh 関数の値を返す

関数: ATANH
仕様: (ATANH X) ---> <NUMBER>
説明: 数値の atanh 関数の値を返す

関数: FLOATP
仕様: (FLOATP OBJ) ---> BOOLEAN
説明: obj が浮動小数点数であるかをチェックする

関数: FLOAT
仕様: (FLOAT X) ---> <FLOAT>
説明: 数型 x を浮動小数点数に変換する

関数: FLOOR
仕様: (FLOOR X) ---> <INTEGER>
説明: 切り下げを行なう

関数: CEILING
仕様: (CEILING X) ---> <INTEGER>
説明: 切り上げを行なう

関数: TRUNCATE
仕様: (TRUNCATE X) ---> <INTEGER>
説明: 0方向に丸める

関数: ROUND
仕様: (ROUND X) ---> <INTEGER>
説明: 四捨五入を行なう

関数: INTEGERP
仕様: (INTEGERP OBJ) ---> BOOLEAN
説明: obj が整数であるかをチェックする

関数: DIV
仕様: (DIV Z1 Z2) ---> <INTEGER>
説明: 数値を整数除算する

関数: MOD
仕様: (MOD Z1 Z2) ---> <INTEGER>
説明: 数値を剰余計算する

関数: GCD
仕様: (GCD Z1 Z2) ---> <INTEGER>
説明: 最大公約数を返す

関数: LCM
仕様: (LCM Z1 Z2) ---> <INTEGER>
説明: 最小公倍数を返す

関数: ISQRT
仕様: (ISQRT Z) ---> <INTEGER>
説明: 整数平方根を返す

関数: DEFCLASS
仕様: (DEFCLASS CLASS-NAME (SC-NAME *) (SLOT-SPEC *) CLASS-OPT *) ---> <SYMBOL>
説明: クラス定義を行なう(特殊形式)

関数: GENERIC-FUNCTION-P
仕様: (GENERIC-FUNCTION-P OBJ) ---> BOOLEAN
説明: obj が包括関数であるかをチェックする

関数: DEFGENERIC
仕様: (DEFGENERIC FUNC-SPEC LAMBDA-LIST OPTION * METHOD-DESC *) ---> <SYMBOL>
説明: 包括関数を定義する(特殊形式)

関数: DEFMETHOD
仕様: (DEFMETHOD FUNC-SPEC METHOD-QUALIFIER * PARAMETER-PROFILE FORM *) ---> <SYMBOL>
説明: メソッド関数を定義する(特殊形式)

関数: CALL-NEXT-METHOD
仕様: (CALL-NEXT-METHOD) ---> <OBJECT>
説明: クラス優先順位の次のクラスのメソッドを呼び出す(特殊形式)

関数: NEXT-METHOD-P
仕様: (NEXT-METHOD-P) ---> BOOLEAN
説明: 次のメソッドが存在するかをチェックする(特殊形式)

関数: CREATE
仕様: (CREATE CLASS INITARG * INITVAL *) ---> <OBJECT>
説明: インスタンスオブジェクトを生成する(包括関数)

関数: INITIALIZE-OBJECT
仕様: (INITIALIZE-OBJECT INSTANCE INITIALIZATION-LIST) ---> <OBJECT>
説明: オブジェクトの初期化を行なう

関数: CLASS-OF
仕様: (CLASS-OF OBJ) ---> <CLASS>
説明: クラスを返す

関数: INSTANCEP
仕様: (INSTANCEP OBJ CLASS) ---> BOOLEAN
説明: インスタンスオブジェクトであるかをチェックする

関数: SUBCLASSP
仕様: (SUBCLASSP CLASS1 CLASS2) ---> BOOLEAN
説明: サブクラスであるかをチェックする

関数: CLASS
仕様: (CLASS CLASS-NAME) ---> <CLASS>
説明: 名前 class-name のクラスを返す(特殊形式)

関数: EQ
仕様: (EQ OBJ1 OBJ2) ---> BOOLEAN
説明: obj1 と obj2 が eq であるかをチェックする

関数: EQL
仕様: (EQL OBJ1 OBJ2) ---> BOOLEAN
説明: obj1 と obj2 が eql であるかをチェックする

関数: EQUAL
仕様: (EQUAL OBJ1 OBJ2) ---> BOOLEAN
説明: obj1 と obj2 が equal であるかをチェックする

関数: NOT
仕様: (NOT OBJ) ---> BOOLEAN
説明: obj の否定を返す

関数: AND
仕様: (AND FORM *) ---> <OBJECT>
説明: form の AND をする(特殊形式)

関数: OR
仕様: (OR FORM *) ---> <OBJECT>
説明: form の OR をする(特殊形式)

関数: LENGTH
仕様: (LENGTH SEQUENCE) ---> <INTEGER>
説明: 列 sequence の長さを返す

関数: ELT
仕様: (ELT SEQUENCE Z) ---> <OBJECT>
説明: 列 sequence の z 番目の要素を返す

関数: SET-ELT
仕様: (SET-ELT OBJ SEQUENCE Z) ---> <OBJECT>
説明: 列 sequence の z 番目に obj をセットする

関数: SUBSEQ
仕様: (SUBSEQ SEQUENCE Z1 Z2) ---> SEQUENCE
説明: 列 sequence の z1 番目から z2 番目の部分列を取り出す

関数: MAP-INTO
仕様: (MAP-INTO DESTINATION FUNCTION SEQ *) ---> SEQUENCE
説明: 列 sequence の要素に関数 function を適用して、その結果を列 destination に格納する

関数: STREAMP
仕様: (STREAMP OBJ) ---> BOOLEAN
説明: obj がストリームであるかをチェックする

関数: OPEN-STREAM-P
仕様: (OPEN-STREAM-P OBJ) ---> BOOLEAN
説明: obj がオープンされたストリームであるかをチェックする

関数: INPUT-STREAM-P
仕様: (INPUT-STREAM-P OBJ) ---> BOOLEAN
説明: obj が入力ストリームであるかをチェックする

関数: OUTPUT-STREAM-P
仕様: (OUTPUT-STREAM-P OBJ) ---> BOOLEAN
説明: obj が出力ストリームであるかをチェックする

関数: STANDARD-INPUT
仕様: (STANDARD-INPUT) ---> <STREAM>
説明: 標準入力を返す

関数: STANDARD-OUTPUT
仕様: (STANDARD-OUTPUT) ---> <STREAM>
説明: 標準出力を返す

関数: ERROR-OUTPUT
仕様: (ERROR-OUTPUT) ---> <STREAM>
説明: エラー出力を返す

関数: WITH-STANDARD-INPUT
仕様: (WITH-STANDARD-INPUT STREAM-FORM FORM *) ---> <OBJECT>
説明: 標準入力を stream-form の実行結果にして form を実行する(特殊形式)

関数: WITH-STANDARD-OUTPUT
仕様: (WITH-STANDARD-OUTPUT STREAM-FORM FORM *) ---> <OBJECT>
説明: 標準出力を stream-form の実行結果にして form を実行する(特殊形式)

関数: WITH-ERROR-OUTPUT
仕様: (WITH-ERROR-OUTPUT STREAM-FORM FORM *) ---> <OBJECT>
説明: エラー出力を stream-form の実行結果にして form を実行する(特殊形式)

関数: OPEN-INPUT-FILE
仕様: (OPEN-INPUT-FILE FILENAME ELEMENT-CLASS +) ---> <STREAM>
説明: ファイル名 filename のファイルを入力ストリームとしてオープンする

関数: OPEN-OUTPUT-FILE
仕様: (OPEN-OUTPUT-FILE FILENAME ELEMENT-CLASS +) ---> <STREAM>
説明: ファイル名 filename のファイルを出力ストリームとしてオープンする

関数: OPEN-IO-FILE
仕様: (OPEN-IO-FILE FILENAME ELEMENT-CLASS +) ---> <STREAM>
説明: ファイル名 filename のファイルを入出力ストリームとしてオープンする

関数: WITH-OPEN-INPUT-FILE
仕様: (WITH-OPEN-INPUT-FILE (NAME FILE ELEMENT-CLASS +) FORM *) ---> <OBJECT>
説明: ファイル名 file のファイルを入力ストリームとしてオープンして form を実行し、実行後クローズする（特殊形式）

関数: WITH-OPEN-OUTPUT-FILE
仕様: (WITH-OPEN-OUTPUT-FILE (NAME FILE ELEMENT-CLASS +) FORM *) ---> <OBJECT>
説明: ファイル名 file のファイルを出力ストリームとしてオープンして form を実行し、実行後クローズする（特殊形式）

関数: WITH-OPEN-IO-FILE
仕様: (WITH-OPEN-IO-FILE (NAME FILE ELEMENT-CLASS +) FORM *) ---> <OBJECT>
説明: ファイル名 file のファイルを入出力ストリームとしてオープンして form を実行し、実行後クローズする（特殊形式）

関数: CLOSE
仕様: (CLOSE STREAM) ---> IMPLEMENTATION-DEFINED
説明: ストリームをクローズする

関数: CREATE-STRING-INPUT-STREAM
仕様: (CREATE-STRING-INPUT-STREAM STRING) ---> <STREAM>
説明: 入力の文字列ストリームを生成する

関数: CREATE-STRING-OUTPUT-STREAM
仕様: (CREATE-STRING-OUTPUT-STREAM) ---> <STREAM>
説明: 出力の文字列ストリームを生成する

関数: GET-OUTPUT-STREAM-STRING
仕様: (GET-OUTPUT-STREAM-STRING STREAM) ---> <STRING>
説明: 出力ストリームに出力された文字列を返す

関数: STRINGP
仕様: (STRINGP OBJ) ---> BOOLEAN
説明: obj が文字列であるかをチェックする

関数: CREATE-STRING
仕様: (CREATE-STRING I INITIAL-ELEMENT+) ---> <STRING>
説明: 長さ i 初期値 initial-element の文字列を生成する

関数: STRING=
仕様: (STRING= STRING1 STRING2) ---> QUASI-BOOLEAN
説明: 文字列が等しいかをチェックする

関数: STRING/=
仕様: (STRING/= STRING1 STRING2) ---> QUASI-BOOLEAN
説明: 文字列が等しくないかをチェックする

関数: STRING<
仕様: (STRING< STRING1 STRING2) ---> QUASI-BOOLEAN
説明: 文字列 sting1 が string2 よりも小さいかをチェックする

関数: STRING>
仕様: (STRING> STRING1 STRING2) ---> QUASI-BOOLEAN
説明: 文字列 sting1 が string2 よりも大きいかをチェックする

関数: STRING>=
仕様: (STRING>= STRING1 STRING2) ---> QUASI-BOOLEAN
説明: 文字列 sting1 が string2 以下かをチェックする

関数: STRING<=
仕様: (STRING<= STRING1 STRING2) ---> QUASI-BOOLEAN
説明: 文字列 sting1 が string2 以上かをチェックする

関数: CHAR-INDEX
仕様: (CHAR-INDEX CHARACTER STRING START-POSITION +) ---> <OBJECT>
説明: 文字列 string 中に文字 character が現れる位置を返す

関数: STRING-INDEX
仕様: (STRING-INDEX SUBSTRING STRING START-POSITION +) ---> <OBJECT>
説明: 文字列 string に部分文字列 substring が現れる位置を返す

関数: STRING-APPEND
仕様: (STRING-APPEND STRING *) ---> <STRING>
説明: 文字列を連結する

関数: SYMBOLP
仕様: (SYMBOLP OBJ) ---> BOOLEAN
説明: シンボルかチェックする

関数: PROPERTY
仕様: (PROPERTY SYMBOL PROPERTY-NAME OBJ +) ---> <OBJECT>
説明: シンボルのプロパティを取り出す

関数: SET-PROPERTY
仕様: (SET-PROPERTY OBJ SYMBOL PROPERTY-NAME) ---> <OBJECT>
説明: シンボルにプロパティをセットする

関数: REMOVE-PROPERTY
仕様: (REMOVE-PROPERTY SYMBOL PROPERTY-NAME) ---> <OBJECT>
説明: シンボルからプロパティを削除する

関数: GENSYM
仕様: (GENSYM) ---> <SYMBOL>
説明: 名前なしシンボルを生成する

関数: BASIC-VECTOR-P
仕様: (BASIC-VECTOR-P OBJ) ---> BOOLEAN
説明: BASIC ベクタかチェックする

関数: GENERAL-VECTOR-P
仕様: (GENERAL-VECTOR-P OBJ) ---> BOOLEAN
説明: GENERIC VECTORかチェックする

関数: CREATE-VECTOR
仕様: (CREATE-VECTOR I INITIAL-ELEMENT +) ---> <GENERAL-VECTOR>
説明: 要素数 i 初期値 initial-element のベクタを生成する

関数: VECTOR
仕様: (VECTOR OBJ *) ---> <GENERAL-VECTOR>
説明: obj ... を要素とするベクタを生成する

関数: LOAD
仕様: (LOAD FILE) ---> T
説明: ファイル file をロードする（拡張）

関数: TIME
仕様: (TIME FORM) ---> <OBJECT>
説明: フォーム form を実行し経過時間を表示する（特殊形式）（拡張）


関数: EVAL
仕様: (EVAL FORM) ---> <OBJECT>
説明: フォーム form を評価する（拡張）


関数: COMPILE-FILE
仕様: (COMPILE-FILE FILE) ---> BOOLEAN
説明: ファイル file をコンパイルする(拡張)


関数: GBC
仕様: (GBC) ---> <NULL>
説明: gc を強制的に実行する (拡張)

関数: PRINT
仕様: (PRINT OBJECT) ---> <NULL>
説明: object を stream に表示する(拡張)

関数: QUIT
仕様: (QUIT) ---> TRANSFERS-CONTROL
説明: ISLisp処理系を終了する(拡張)

```
