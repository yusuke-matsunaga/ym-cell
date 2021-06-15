.. _liberty:

liberty 形式の読み込みについて
===============================

全体の構成
-----------

基本的な構文として

  - simple attribute
  - complex attribute
  - group statement

の3種類がある．

根本は library group statement (:ref:`library_group`)
でその下に再帰的に属性を持つ．
liberty の文法では先頭のトークンを読み込んだ時点で上記の
３種類の属性の区別ができるので，各属性ごとに個別のパースクラス
を用意する．


simple attributeのパース
------------------------

::

  <属性名> : <属性値> ;

のシンタックスで表される．
属性の種類に依らずにセミコロン(;)までを読み込む．
属性値とそれを表すAstのクラス(後述)は以下の通り．

.. table::
   :align: left
   :widths: auto

   ====================== ======================
   属性の型               対応する Ast クラス
   ====================== ======================
   int                    AstInt
   bool		          AstBool
   'clear_preset_var_n'   AstCPType
   'delay_model'          AstDelayModel
   'direction'		  AstPinDirection
   expr                   AstExpr
   float		  AstFloat
   function               AstExpr
   string		  AstString
   'technology'           AstTechnology
   'timing_sense'	  AstTimingSense
   'timing_type'	  AstTimingType
   'variable_type'	  AstVarType
   ====================== ======================

このなかの delay_model, direction, technology, timing_sense, timing_type,
variable_type は string 型の特定な文字列のみを受け付ける．
また，論理式(expr)は見かけは simple attribute だが，
属性値の部分に空白を含むためパーサー的には別に扱う．
ややこしいのは文字列中に式を書いた function 記述という型もある．
こちらは一旦文字列としてパースしてから式に変換する．
前者は ExprHandler，後者は FuncHandler で扱う．

実装ファイルは DotlibParser_simple.cc にある．

string のパースについて
^^^^^^^^^^^^^^^^^^^^^^^^

`string` 型の値が必要とされる場合にはダブルクォート(")で括られた
任意の文字列と数字以外の文字から始まる非空白文字の連続のどちらでも
受け付ける．
つまり， `"ff"` と `ff` はどちらも同じ値となる．


complex attributeのパース
--------------------------

::

   <属性名> ( <属性値1>, <属性値2>, ... ) ;

のシンタックスで表される．
左カッコに対する右カッコの後のセミコロン(;)までを読み込む．
属性値は simple attribute と同じ．ただし expr はない．
個々の属性ごとに属性値の型は決まっている．

こちらもめんどくさいのは見かけは一つの文字列だが，
中が空白で区切られた数値の場合がある(lookup table の values 属性等)．
そのため特別なハンドラを用意する．

後述の group statement のヘッダと complex attribute
は全く同じ形式なので同一のハンドラ(HeaderHandler)で読み込む．


group statementのパース
------------------------

::

   <属性名> ( <属性値1>, <属性値2>, ... ) {
      <属性記述1>
      <属性記述2>
      ...
   }

のシンタックスで表される．
左カッコに対する右カッコの後の左中カッコに対応する右中カッコ
までを読み込む．これらは simple attribute や complex attribute と異なり
最後のセミコロンはない．
最初の行は行末の '{' 以外は complex attribute と同様である．
属性記述には simple attribute, complex attribute, group statement が記述できる．

具体的な group statement の例は :ref:`group` を参照せよ．

complex attribute と group statement のヘッダ部分に現れる形式は以下の表の通り．

.. table::
   :align: left
   :widths: auto

   ================================================== =======================   ====================
   形式						      ハンドラクラス            対応する Ast クラス
   ================================================== =======================   ====================
   ( )						      EmptyHandler
   ( float, float )                                   FloatFloatHandler         AstFloat2
   ( float, string )				      FloatStrHandler           AstFloatStr
   ( "float, float, ..." )                            FloatVectorHandler        AstFloatVector
   ( "float, float, ...", "float, flot, ...", ... )   FloatVectorListHandler    AstFloatVectorList
   ( integer, float )				      IntFloatHandler           AstIntFloat
   ( integer, "float, float, ..." )                   IntFloatVectorHandler     AstIntFloatVector
   ( "integer, integer, ..." )			      IntVectorHandler          AstIntVector
   ( string )					      StrHandler                AstString
   ( string, integer )				      StrIntHandler             AstStrInt
   ( string, string, ... )			      StrListHandler            AstStrList
   ( string, string )				      StrStrHandler             AstStr2
   ( string, string, integer )			      StrStrIntHandler          AstStr2Int
   ================================================== =======================   ====================


パーサーの基本構造
-------------------

属性には，必須/オプショナルなものと，唯一/複数のものがある．

パーサーの基本構造としては simple attribute, complex attribute,
group statement の各属性用のパース関数を作る．
そのなかで個々の属性に応じた処理を行うため DotlibHandler
というクラスを用いる．
この DotlibHandler を継承したクラスが実際のパース処理を行う．

パースした構文木を表すために AstNode というクラスを用意する．
実際には AstNode の派生クラスの木構造で構文木を表す．

例えば xxx という型をパースする DotlibParser のメンバ関数は

::

  bool
  DotlibParser::parse_xxx(const AstXxx*& dst,
  			  AttrType attr_type,
			  const FileRegion& attr_loc);

というインターフェイスを持つ．
dst にパース結果が入る．

もしも同一の属性をもつ要素を複数持つ場合には，

::

  bool
  DotlibParser::parse_xxx(vector<const AstXxx*>& dst_list,
  			  AttrType attr_type,
			  const FileRegion& attr_loc);

というインターフェイスを持つ．
dst_list にパース結果が追加される．

complex attribute の属性ととそれに対応する AstNode の派生クラスを以下に示す．

.. table::
   :align: left
   :widths: auto

   ====================	=============================
   属性の形式           パース結果を格納するAstクラス
   ====================	=============================
   'coefs'              AstFloatVector
   (float, float)       (AstFloat, AstFloat)
   'index_n'            AstFloatVector
   'orders'             AstIntVector
   'piece wise'         AstPieceWise
   'unit'               (AstString, AstFloat)
   'values'             AstFloatVector
   'variable_n_range'   AstVariableRange
   ====================	=============================

group statement の代表的な属性とそれに対応する AstNode の派生クラスを以下に示す．

.. table::
   :align: left
   :widths: auto

   =================== ==============================
   属性の形式           パース結果を格納するAstクラス
   =================== ==============================
   'bus'               AstBus
   'bundle'            AstBundle
   'cell'              AstCell
   'cell_degradation'  AstCellDegradation
   'domain'            AstDomain
   'ff'                AstFF
   'ff_bank'           AstFFBank
   'input_voltage'     AstInputVoltage
   'latch'             AstLatch
   'latch_bank'        AstLatchBank
   'library'           AstLibrary
   'lu_table'          AstLut
   'output_voltage'    AstOutputVoltage
   'pin'               AstPin
   'statetable'        AstStatetable
   'template'          AstTemplate
   'timing'            AstTiming
   =================== ==============================

AstXXX はコンストラクタで値を設定したらあとは const にしたいので，
AstXXX を読み込む XXXHandler に一旦必要な値を保持しておいて
XXXHandler を AstXXX のコンストラクタに渡す．
いわゆるビルダークラスパターンを用いる.

このような二度手間にしている理由は3つ．

* 可変長のリストをビルダクラス中では vector<> で保持しておいて
  AstXXX のコンストラクタでは固定長の配列として確保する．
* パース途中でエラーが起こった場合に AstXXX のオブジェクトを確保
  しない．ビルダークラスのオブジェクトは自動変数として確保しておくの
  でエラー時には自動的に削除される．
* AstXXX のコンストラクタのパラメータが簡潔になる．

AstXXX, XXXHandler と関連した情報を持つのでもととなるデータから
これらのクラスのヘッダファイルとソースファイルを自動生成する
Python スクリプトを用意する．
一旦，ファイルを作ってしまえば仕様変更がない限り再度生成する必要はな
いので，生成後のファイルに手直しをすることも可能．


Group のパースの流れ
---------------------

DotlibParser::parse_xxx() 中で適切な HeaderHandler と GroupHandler
を用いて DotlibParser::parse_group_statement(header_handler, group_handler)
を呼び出す．
結果が true なら AstMgr::new_XXX(header_handler, group_handler) で
新しい構文木を生成する．


整理されていないおぼえ書き
---------------------------

::

   include_file ( filename );

という構文があるが，結構，制限があるし，今はあまり使われていないみたい．
ここでは無視する．

- routing_layers は routability information の前に定義されなければなら
  ない．
  この属性は唯一

- voltage_map ( voltage_name_(id), voltage_value_(float) ) ;
  string と float の組．
  複数ありうる．

- input_voltage や output_voltage に出てくる expression は
  以下みたいな感じ？

  ::

     expression : float_number
                | 'VDD'
		| 'VSS'
		| 'VCC'
		| '(' expression ')'
		| '+' expression
		| '-' expression
		| expression '+' expression
		| expression '-' expression
		| expression '*' expression
		| expression '/' expression
