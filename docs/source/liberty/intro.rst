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

simple attribute は単一の値を持つ．
complex attribute は複数の値のリストを持つ．
group statement は他の simple/complex attribute や group statment
を子供に持つ．
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
属性名を読んだ時点でどのタイプの値を読むかがわかるので，
専用の関数を用いる．
属性の型と対応する `Parser` クラスの読み込み関数を示す．

.. table::
   :align: left
   :widths: auto

   ====================== ======================
   属性の型               対応する読み込み関数
   ====================== ======================
   int                    read_int()
   bool		          read_bool()
   'clear_preset_var_n'   AstCPType
   'delay_model'          read_delay_model()
   'direction'		  read_direction()
   expr                   read_expr()
   float		  read_float()
   function               read_function()
   string		  read_string()
   'technology'           read_technology()
   'timing_sense'	  read_timing_sense()
   'timing_type'	  read_timing_type()
   'variable_type'	  read_vartype()
   ====================== ======================

このなかの delay_model, direction, technology, timing_sense, timing_type,
variable_type は string 型の特定な文字列のみを受け付ける．
また，論理式(expr)は見かけは simple attribute だが，
属性値の部分に空白を含むためパーサー的には別に扱う．
ややこしいのは文字列中に式を書いた function 記述という型もある．
こちらは一旦文字列としてパースしてから式に変換する．

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

これらの属性には属性値の個数が決まっているものと，
可変のものがある．
前者は異なる型の属性値が混在する場合があるが，
後者はすべて同一の型の属性値となる．
前者のタイプの属性は `FixedElemHeader` クラスで扱う．
後者は `ListHeader` クラスで扱う．
どちらも読み込む属性値のハンドラを引数として与える．


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

   ================================================== =======================
   形式						      ハンドラ
   ================================================== =======================
   ( )						      sEmptyHeader
   ( float, float )                                   sFloatFloatHeader
   ( float, string )				      sFloatStrHeader
   ( "float, float, ..." )                            sFloatVectorHeader
   ( integer, float )				      sIntFloatHeader
   ( integer, "float, float, ..." )                   sIntFloatVectorHeader
   ( "integer, integer, ..." )			      sIntVectorHeader
   ( string )					      sStrHeader
   ( string, integer )				      sfStrIntHeader
   ( string, string )				      sStrStrHeader
   ( string, string, integer )			      sStrStrIntHeader
   ( string, string, string )			      sStrStrStrHeader
   ================================================== =======================
   ( "float, float, ...", "float, flot, ...", ... )   sFloatVectorListHeader
   ( string, string, ... )			      sStrListHeader
   ================================================== =======================

このうち最後の２つの形式は要素数が可変の形式である．


パーサーの基本構造
-------------------

属性には，必須/オプショナルなものと，唯一/複数のものがある．

パーサーの基本構造としては simple attribute, complex attribute,
group statement の各属性用のパース関数を作る．
そのなかで個々の属性に応じた処理を行うため DotlibHandler
というクラスを用いる．
この DotlibHandler を継承したクラスが実際のパース処理を行う．


パース結果を表すクラス
-----------------------

どの属性も， `属性名` と `対応する値` の組で表される．
`属性名` は `AttrKwd` クラスで，対応する値は `AstValue`
クラスで表す．属性全体は `AstAttr` クラスで表す．
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
