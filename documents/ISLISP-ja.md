# ISLisp 関数一覧

## array
- (BASIC-ARRAY-P obj) `boolean` obj が配列または文字列, ベクタ かどうかをチェックする
- (BASIC-ARRAY*-P obj) `boolean` obj が多次元配列であるかをチェックする
- (GENERAL-ARRAY*-P obj) `boolean` obj が多次元配列であるかをチェックする
- (CREATE-ARRAY dimensions initial-element +) `<basic-array>` 配列を生成する
- (AREF basic-array z *) `<object>` 配列 basic-array の z 番目の要素を取り出す
- (GAREF general-array z *) `<object>` 配列 general-array の z 番目の要素を取り出す
- (SET-AREF obj basic-array z *) `<object>` 配列 basic-array の z 番目に要素 obj をセットする
- (SET-GAREF obj general-array z *) `<object>` 配列 general-array の z 番目に要素 obj をセットする
- (ARRAY-DIMENSIONS basic-array) `<list>` 配列 basic-array の次元をリストで返す

## char
- (CHARACTERP obj) `boolean` obj が文字であるかをチェックする
- (CHAR= char1 char2) `boolean` char1 と char2 の文字が等しいかをチェックする
- (CHAR/= char1 char2) `boolean` char1 と char2 の文字が等しくないかをチェックする
- (CHAR< char1 char2) `boolean` char1 の文字コードが char2 よりも大きいかをチェックする
- (CHAR> char1 char2) `boolean` char1 の文字コードが char2 よりも小さいかをチェックする
- (CHAR<= char1 char2) `boolean` char1 の文字コードが char2 よりも大きいかまたは等しいかをチェックする
- (CHAR>= char1 char2) `boolean` char1 の文字コードが char2 よりも小さいまたは等しいかをチェックする

## cond
- (error error-string obj *) `<object>` エラーをシグナルする
- (cerror continue-string error-string obj *) `<object>` 継続可能なエラーをシグナルする
- (signal-condition condition continuable) `<object>` コンディションを操作するためにシグナルする
- (ignore-errors form *) `<object>` エラーが出ても無視する(特殊形式)
- (report-condition condition stream) `<condition>` コンディション condition をストリーム stream にレポートする 
- (condition-continuable condition) `<object>` 継続可能かをチェックする
- (continue-condition condition value +) `<object>` コンディションから継続する
- (with-handler handler form *) `<object>` ハンドラを評価してフォームを実行する(特殊形式)
- (arithmetic-error-operation arithmetic-error) `<function>` 算術演算エラーのオペレータを返す
- (arithmetic-error-operands arithmetic-error) `<list>` 算術演算エラーのオペランドを返す
- (domain-error-object domain-error) `<object>`  ドメインエラー domain-error で生成されたオブジェクトを返す
- (domain-error-expected-class domain-error) `<class>` ドメインエラー domain-error で生成された望ましかったドメインを返す
- (parse-error-string parse-error) `<string>` 解析エラー parse-error で生成された文字列を返す
- (parse-error-expected-class parse-error) `<class>`  解析エラー parse-error で生成された望ましいクラスを返す
- (simple-error-format-string simple-error) `<string>` simple-error で生成された文字列を返す
- (simple-error-format-arguments simple-error) `<list>` simple-error で生成された引数リストを返す
- (stream-error-stream stream-error) `<stream>` ストリームエラー stream-error で生成されたストリームを返す
- (undefined-entity-name undefined-entity) `<symbol>` 未定義エンティティ undefined-entity で生成されたシンボルを返す
- (undefined-entity-namespace undefined-entity) `<symbol>` 未定義エンティティ undefined-entity で生成された名前空間を返す

## control
- (quote obj) `<object>` obj の参照を返す(特殊形式)
- (setq var form) `<object>` 変数 var にフォーム form の評価結果を代入する(特殊形式)
- (setf place form) `<object>` 場所 place にフォーム form の評価結果を代入する(特殊形式)
- (let ((var form) *) body-form *) `<object>` 局所変数を定義し、その環境で実行する(特殊形式)
- (let* ((var form) *) body-form *) `<object>`  letと同様であるが局所変数を順次束縛するところが異なる(特殊形式)
- (dynamic var) `<object>` 動的変数を宣言する(特殊形式)
- (setf (dynamic var) form) `<object>` 動的変数に値を代入する(特殊形式)
- (dynamic-let ((var form) *) body-form *) `<object>` 動的変数の一時的束縛をする(特殊形式)
- (if test-form then-form else-form+) `<object>` 条件の結果で分岐する(特殊形式)
- (cond (test form *) *) `<object>` 条件の結果で分岐する(特殊形式)
- (case keyform ((key *) form *) * (t form *)+) `<object>` keyform の値によって多岐に分岐する(特殊形式)
- (case-using predform keyform ((key *) form *) * (t form *) +) `<object>` case 文とほぼ同様であるが,述語関数 predform を比較に使う(特殊形式)
- (progn form*) `<object>` 順次実行を行なう(特殊形式)
- (while test-form body-form *) `<null>` test-form が nil でない間 body-form を実行する(特殊形式)
- (for (iteration-spec *) (end-test result *) form *) `<object>` iteration-spec で示された初期値とステッパを用い end-test が nil でない間繰り返し実行する(特殊形式)
- (block name form *) `<object>` ブロックタグを付けて順次実行する(特殊形式)
- (return-from name result-form) transfers-control-and-data name ブロックを抜ける(特殊形式)
- (catch tag-form form *) `<object>` tag-form をキャッチし、form を実行する(特殊形式)
- (throw tag-form result-form) transfers-control-and-data tag-form をスローする(特殊形式)
- (tagbody tagbody-tag * form *) `<object>` tagbody-tagを付けて順次実行する(特殊形式)
- (go tagbody-tag) transfers-control tag-bodyブロックに制御を移す(特殊形式)
- (unwind-protect form cleanup-form *) `<object>`  formの評価を終了するときは必ず cleanup-form を実行する(特殊形式)

## declare
- (THE class-name form) `<object>` form の実行結果のクラスを class-name と宣言する(特殊形式)
- (ASSURE class-name form) `<object>` form の実行結果のクラスを class-name と主張する、異なる場合はエラーとなる(特殊形式)
- (CONVERT obj class-name) `<object>` obj をクラス class-name に変換する(特殊形式)

## files
- (probe-file filename) `boolean` filename のファイルが存在するかをチェックする
- (file-position stream) `<integer>` stream の現在のファイル位置を返す
- (set-file-position stream z) `<integer>`  stream のファイル位置を z に設定する
- (file-length filename element-class) `<integer>` filename のファイルを element-class のファイルとしてのサイズを返す

## formeval
- (functionp obj) `boolean` obj が関数であるかをチェックする
- (function function-name) `<function>` function-name を名前とする関数を返す(特殊形式)
- (lambda lambda-list form *) `<function>` ラムダ式を生成する(特殊形式)
- (labels ((function-name lambda-list form *) *) body-forms *) `<object>`  局所関数の束縛をする、順次束縛（再帰的定義が可能）である点が flet と異なる(特殊形式)
- (flet ((function-name lambda-list form *) *) body-forms *) `<object>`  局所関数の束縛をする(特殊形式)
- (apply function obj * list) `<object>` 関数を適用する
- (funcall function obj *) `<object>` 関数を呼び出す
- (defconstant name form) `<symbol>` 定数を宣言する(特殊形式)
- (defglobal name form) `<symbol>` 広域変数を宣言する(特殊形式)
- (defdynamic name form) `<symbol>` 動的変数を宣言する(特殊形式)
- (defun function-name lambda-list form *) `<symbol>` 関数を定義する(特殊形式)

## io
- (read input-stream + eos-error-p + eos-value +) `<object>` input-stream からS式として読む
- (read-char input-stream + eos-error-p + eos-value +) `<object>` input-stream から1文字読む
- (preview-char input-stream + eos-error-p + eos-value +) `<object>`  次に読み込む文字を返す（1文字先読み。ファイルポジションは変化しない）
- (read-line input-stream + eos-error-p + eos-value +) `<object>` 1行を文字列として読む
- (stream-ready-p input-stream) `boolean` ストリームが読み込み可能になっているか
- (format output-stream format-string obj *) `<null>` format-string に従って obj を出力する
- (format-char output-stream char) `<null>` 1文字出力する
- (format-float output-stream float) `<null>` 浮動小数点数として出力する
- (format-fresh-line output-stream) `<null>` 改行する
- (format-integer output-stream integer radix) `<null>` 整数として出力する
- (format-object output-stream obj escape-p) `<null>` オブジェクトとして出力する
- (format-tab output-stream column) `<null>` タブを出力する
- (read-byte input-stream eos-error-p + eos-value +) `<integer>` バイトとして読む
- (write-byte z output-stream) `<integer>` バイトとして書く

## list
- (CONSP obj) `boolean` コンスかをチェックする
- (CONS obj1 obj2) `<cons>` コンスを生成する
- (CAR cons) `<object>` コンスの Car 部を取り出す
- (CDR cons) `<object>` コンスの Cdr 部を取り出す
- (SET-CAR obj cons) `<object>` コンスの Car 部にセットする
- (SET-CDR obj cons) `<object>` コンスの Cdr 部にセットする
- (NULL obj) `boolean` NULL かチェックする
- (LISTP obj) `boolean` リストかチェックする
- (CREATE-LIST i initial-element +) `<list>` 長さ i 初期値 initial-element のリストを生成する
- (LIST obj *) `<list>` obj を要素とするリストを生成する
- (REVERSE list) `<list>` リストを逆順にする（元のリストは破壊しない）
- (NREVERSE list) `<list>` リストを逆順にする（元のリストは破壊される）
- (APPEND list *) `<list>` リストを連結する
- (MEMBER obj list) `<list>`  リスト list に obj が含まれていれば、obj を先頭とする部分リストを返す
- (MAPCAR function list +) `<list>` リスト list の要素に関数 function を実行し結果のリストを返す
- (MAPC function list +) `<list>`  リスト list の要素に関数 function を実行し引数のリスト list を返す
- (MAPCAN function list +) `<list>`  MAPCAR の操作を list を破壊して行なう
- (MAPLIST function list +) `<list>`  リスト list の部分リストに関数 function を実行し、結果のリストを返す
- (MAPL function list +) `<list>`  リスト list の部分リストに関数 function を実行し、引数リスト list を返す
- (MAPCON function list +) `<list>` MAPLIST の操作を list を破壊して行なう
- (ASSOC obj association-list) `<cons>`  連想リスト association-list に対して obj をキーとする値を返す

## macro
- (defmacro macro-name lambda-list form *) `<symbol>` マクロを定義する(特殊形式)

## misc
- (IDENTITY obj) `<object>` obj をそのまま返す
- (GET-UNIVERSAL-TIME) `<integer>` ユニバーサルタイム（秒）を返す
- (GET-INTERNAL-RUN-TIME) `<integer>` 実行時間を返す
- (GET-INTERNAL-REAL-TIME) `<integer>` 経過時間を返す
- (internal-time-units-per-second) `<integer>` 1秒当たりのインターナルタイム単位を返す

## number
- (NUMBERP obj) `boolean` obj が数型であるかをチェックする
- (PARSE-NUMBER string) `<number>` 文字列 string を解析して数型に変換する
- (= x1 x2) `boolean` 数値が等しいかをチェックする
- (/= x1 x2) `boolean` 数値が等しくないかをチェックする
- (>= x1 x2) `boolean` 数値 x1 が x2 以上であるかをチェックする
- (<= x1 x2) `boolean` 数値 x1 が x2 以下であるかをチェックする
- (> x1 x2) `boolean` 数値 x1 が x2 より大きいかをチェックする
- (< x1 x2) `boolean` 数値 x1 が x2 より小さいかをチェックする
- (+ x *) `<number>` 数値を加算する
- (* x *) `<number>` 数値を乗算する
- (- x y *) `<number>` 数値を減算する
- (QUOTIENT dividend divisor +) `<number>` 数値を除算する
- (RECIPROCAL x) `<number>` 数値を逆数にする
- (MAX x y *) `<number>` 数値の最大値を返す
- (MIN x y *) `<number>` 数値の最小値を返す
- (ABS x) `<number>` 数値の絶対値を返す
- (EXP x) `<number>` 数値の指数関数の値を返す
- (LOG x) `<number>` 数値の自然対数の値を返す
- (EXPT x1 x2) `<number>` 数値をべき乗する
- (SQRT x) `<number>` 数値の平方根を返す
- (SIN x) `<number>` 数値の sin 関数の値を返す
- (COS x) `<number>` 数値の cos 関数の値を返す
- (TAN x) `<number>` 数値の tan 関数の値を返す
- (ATAN x) `<number>` 数値の atan 関数の値を返す
- (ATAN2 x1 x2) `<number>` 数値の atan2 関数の値を返す
- (SINH x) `<number>` 数値の sinh 関数の値を返す
- (COSH x) `<number>` 数値の cosh 関数の値を返す
- (TANH x) `<number>` 数値の tanh 関数の値を返す
- (ATANH x) `<number>` 数値の atanh 関数の値を返す
- (FLOATP obj) `boolean` obj が浮動小数点数であるかをチェックする
- (FLOAT x) `<float>` 数型 x を浮動小数点数に変換する
- (FLOOR x) `<integer>` 切り下げを行なう
- (CEILING x) `<integer>` 切り上げを行なう
- (TRUNCATE x) `<integer>` 0方向に丸める
- (ROUND x) `<integer>` 四捨五入を行なう
- (INTEGERP obj) `boolean` obj が整数であるかをチェックする
- (DIV z1 z2) `<integer>` 数値を整数除算する
- (MOD z1 z2) `<integer>` 数値を剰余計算する
- (GCD z1 z2) `<integer>` 最大公約数を返す
- (LCM z1 z2) `<integer>` 最小公倍数を返す
- (ISQRT z) `<integer>` 整数平方根を返す

## object
- (defclass class-name (sc-name *) (slot-spec *) class-opt *) `<symbol>`  クラス定義を行なう(特殊形式)
- (generic-function-p obj) `boolean` obj が包括関数であるかをチェックする
- (defgeneric func-spec lambda-list option * method-desc *) `<symbol>`  包括関数を定義する(特殊形式)
- (defmethod func-spec method-qualifier * parameter-profile form *) `<symbol>` メソッド関数を定義する(特殊形式)
- (call-next-method) `<object>` クラス優先順位の次のクラスのメソッドを呼び出す(特殊形式)
- (next-method-p) `boolean` 次のメソッドが存在するかをチェックする(特殊形式)
- (create class initarg * initval *) `<object>` インスタンスオブジェクトを生成する(包括関数)
- (initialize-object instance initialization-list) `<object>` オブジェクトの初期化を行なう
- (class-of obj) `<class>` クラスを返す
- (instancep obj class) `boolean` インスタンスオブジェクトであるかをチェックする
- (subclassp class1 class2) `boolean` サブクラスであるかをチェックする
- (class class-name) `<class>` 名前 class-name のクラスを返す(特殊形式)

## pred
- (EQ obj1 obj2) `boolean` obj1 と obj2 が eq であるかをチェックする
- (EQL obj1 obj2) `boolean` obj1 と obj2 が eql であるかをチェックする
- (EQUAL obj1 obj2) `boolean` obj1 と obj2 が equal であるかをチェックする
- (NOT obj) `boolean` obj の否定を返す
- (AND form *) `<object>` form の AND をする(特殊形式)
- (OR form *) `<object>` form の OR をする(特殊形式)

## seq
- (LENGTH sequence) `<integer>` 列 sequence の長さを返す
- (ELT sequence z) `<object>` 列 sequence の z 番目の要素を返す
- (SET-ELT obj sequence z) `<object>` 列 sequence の z 番目に obj をセットする
- (SUBSEQ sequence z1 z2) sequence 列 sequence の z1 番目から z2 番目の部分列を取り出す
- (MAP-INTO destination function seq *) sequence  列 sequence の要素に関数 function を適用して、その結果を列 destination に格納する

## stream
- (streamp obj) `boolean` obj がストリームであるかをチェックする
- (open-stream-p obj) `boolean` obj がオープンされたストリームであるかをチェックする
- (input-stream-p obj) `boolean` obj が入力ストリームであるかをチェックする
- (output-stream-p obj) `boolean` obj が出力ストリームであるかをチェックする
- (standard-input) `<stream>` 標準入力を返す
- (standard-output) `<stream>` 標準出力を返す
- (error-output) `<stream>` エラー出力を返す
- (with-standard-input stream-form form *) `<object>`  標準入力を stream-form の実行結果にして form を実行する(特殊形式)
- (with-standard-output stream-form form *) `<object>` 標準出力を stream-form の実行結果にして form を実行する(特殊形式)
- (with-error-output stream-form form *) `<object>`  エラー出力を stream-form の実行結果にして form を実行する(特殊形式)
- (open-input-file filename element-class +) `<stream>` ファイル名 filename のファイルを入力ストリームとしてオープンする
- (open-output-file filename element-class +) `<stream>` ファイル名 filename のファイルを出力ストリームとしてオープンする
- (open-io-file filename element-class +) `<stream>` ファイル名 filename のファイルを入出力ストリームとしてオープンする
- (with-open-input-file (name file element-class +) form *) `<object>` ファイル名 file のファイルを入力ストリームとしてオープンして form を実行し、実行後クローズする（特殊形式）
- (with-open-output-file (name file element-class +) form *) `<object>` ファイル名 file のファイルを出力ストリームとしてオープンして form を実行し、実行後クローズする（特殊形式）
- (with-open-io-file (name file element-class +) form *) `<object>` ファイル名 file のファイルを入出力ストリームとしてオープンして form を実行し、実行後クローズする（特殊形式）
- (close stream) implementation-defined ストリームをクローズする
- (create-string-input-stream string) `<stream>` 入力の文字列ストリームを生成する
- (create-string-output-stream) `<stream>` 出力の文字列ストリームを生成する
- (get-output-stream-string stream) `<string>` 出力ストリームに出力された文字列を返す

## string
- (STRINGP obj) `boolean` obj が文字列であるかをチェックする
- (CREATE-STRING i initial-element+) `<string>` 長さ i 初期値 initial-element の文字列を生成する
- (STRING= string1 string2) quasi-boolean 文字列が等しいかをチェックする
- (STRING/= string1 string2) quasi-boolean 文字列が等しくないかをチェックする
- (STRING< string1 string2) quasi-boolean 文字列 sting1 が string2 よりも小さいかをチェックする
- (STRING> string1 string2) quasi-boolean 文字列 sting1 が string2 よりも大きいかをチェックする
- (STRING>= string1 string2) quasi-boolean 文字列 sting1 が string2 以下かをチェックする
- (STRING<= string1 string2) quasi-boolean 文字列 sting1 が string2 以上かをチェックする
- (CHAR-INDEX character string start-position +) `<object>` 文字列 string 中に文字 character が現れる位置を返す
- (STRING-INDEX substring string start-position +) `<object>` 文字列 string に部分文字列 substring が現れる位置を返す
- (STRING-APPEND string *) `<string>` 文字列を連結する

## symbol
- (SYMBOLP obj) `boolean` シンボルかチェックする
- (PROPERTY symbol property-name obj +) `<object>` シンボルのプロパティを取り出す
- (SET-PROPERTY obj symbol property-name) `<object>` シンボルにプロパティをセットする
- (REMOVE-PROPERTY symbol property-name) `<object>` シンボルからプロパティを削除する
- (GENSYM) `<symbol>` 名前なしシンボルを生成する

## vector
- (BASIC-VECTOR-P obj) `boolean` BASIC ベクタかチェックする
- (GENERAL-VECTOR-P obj) `boolean` GENERIC VECTORかチェックする
- (CREATE-VECTOR i initial-element +) `<general-vector>`  要素数 i 初期値 initial-element のベクタを生成する
- (VECTOR obj *) `<general-vector>` obj ... を要素とするベクタを生成する

## extension of Easy-ISLisp
- (load file) T ファイル file をロードする（拡張）
- (time form) `<object>` フォーム form を実行し経過時間を表示する（特殊形式）（拡張）
- (eval form) `<object>` フォーム form を評価する（拡張）
- (compile-file file) `boolean` ファイル file をコンパイルする(拡張)
- (gbc) `<null>` gc を強制的に実行する (拡張)
- (quit) transfers-control ISLisp処理系を終了する(拡張)

