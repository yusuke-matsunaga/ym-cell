
.. _delay_models:

Delay Models
=============

参考文献: Library Compiler Users Guide: Modeling Timing, Signal
Integrity, and Power in Technology Libraries

liberty では以下に示す異なるタイプのディレイモデルに対応している．
ただし，ディレイモデルは一つのライブラリ中でただ一つのみ
指定できる．セルごとに異なるディレイモデルを指定することはできない．

::

   delay_model : generic_cmos | table_lookup | piecewise_cmos | cmos2 |
                 dcm | polynomial ;

セルの遅延とは
---------------

基本的にはセルの入力ピンの信号変化が起こってからセルの出力ピンの信号変
化が起こるまでの時間を遅延時間と呼ぶ．
実際のピン上の信号波形は連続的であるので明確に信号変化を表すタイミング
は決まっていないが，多くの場合，電圧が電源電圧の50%を横切ったタイミン
グを信号変化のタイミングと定義している．
また，実際にはセルの出力のピンではなく，その先に接続しているセルの入力
ピンを対象にしている場合も多い．


CMOS Generic Delay Model
-------------------------

`delay_model` 属性に `generic_cmos` を指定する．

遅延時間は以下の式で計算される．

.. math::

   D_{total} = D_I + D_S + D_C + D_T

各要素の意味は以下の通り．

:math:`D_I`
      Intrinsic Delay: ゲート（セル）そのものに起因する遅延時間．セル
      に対して固有値となる．

:math:`D_S`
      Slope Delay: 入力信号の立ち上がりの傾きに起因する遅延時間

:math:`D_C`
      Connect Delay: 出力ピンから接続先の入力ピンまでの到達時間

:math:`D_T`
      Transition Delay: 出力先の負荷に起因する遅延時間

遅延時間のスケーリング
^^^^^^^^^^^^^^^^^^^^^^

各要素は以下の式でスケーリングされる．

.. math::

   D_{scaled} = D \times (1 + \Delta_{process} \times K_{process})(1 +
   \Delta_{temp} \times K_{temp})(1 + \Delta_{voltage} \times
   K_{voltage})

各要素の意味は以下の通り．

:math:`D`
      元となる遅延値: :math:`D_I, D_S, D_C, D_T`

:math:`\Delta_{process}, \Delta_{temp}, \Delta{voltage}`
      それぞれ，プロセス，温度，電圧の変位を表すパラメータ．

      `operating_conditions` グループで指定される．

:math:`K_{process}, K_{temp}, K_{voltage}`
      それぞれ，プロセス，温度，電圧の対するスケーリングファクタ

スケールされた遅延時間は以下の式で表される．

.. math::

   D_{total(scaled)} = D_{I(scaled)} + D_{S(scaled)} + D_{C(scaled)} + D_{T(scaled)}

Slope Delay
^^^^^^^^^^^^

slope delay は入力ピンにおける信号変化の傾きに起因する遅延時間を表す．

.. math::

   D_S = S_S \times D_{T(prevstage)}

:math:`D_S`
      slope delay の値

:math:`S_S`
      傾きに依存する係数．
      具体的には `timing` グループ内の `slope_rise` と `slope_fall` の値
      を用いる．

:math:`D_{T(prevstage)}`
      前段のセルの出力ピンにおける遷移時間．

Intrinsic Delay
^^^^^^^^^^^^^^^^

intrinsic delay はセルに固有の遅延時間を表す．
具体的には `timing` グループ内の `intrinsic_rise` と `intrinsic_fall`
の値を用いる．

Transition Delay
^^^^^^^^^^^^^^^^^

transition delay は出力ピンにおける遷移時間を表す．
出力ピンの遷移時間は接続先のピンと配線の抵抗および容量に依存する．

.. math::

   D_T = R_{driver}(C_{wire} + C_{pins}) / \mbox{number_non_three_state_drivers}

:math:`R_{driver}`
      ドライバ自体の抵抗値．
      具体的には `rise_resistance` と `fall_resistance`
      の値を用いる．

:math:`C_{wire}`
      配線の容量．
      一般に配線容量は配線長に依存するが，実際にレイアウトされるまでは
      配線長は確定していない．そこで，ファンアウト数に基づいて配線長の
      推定を行い，その値から配線容量を求める．
      具体的には `wire_load` グループの `fanout_length` を用いて配線長を求める．
      さらに `capacitance` を掛けることで容量を求める．
      もしも `wire_load` グループが存在しない場合には :math:`C_{wire}`
      は 0 となる．

number_non_three_state_drivers
      スリーステートでないドライバの数．通常の配線なら1のはず．

Connect Delay
^^^^^^^^^^^^^^

connect delay はセルの出力ピンの信号変化から接続先の入力ピンの信号変化
までの時間を表す．
これも厳密にはレイアウト後の配線情報が必要となるため，
論理設計の段階では見積もり値を用いている．
Library Compiler/Design Compiler では以下に示す３つのケースをサポート
している．
このケースは `operating_conditions` グループ内の `tree_type` 属性で
指定される．

best_case_tree
     ベストケースでは入力ピンが出力ピンに隣接しているとみなす．

     .. math::
	D_{C_{best}} = 0

worst_case_tree
     ワーストケースでは入力ピンが最遠橋にあると仮定する．

     .. math::
	D_{C_{worst}} = R_{wire}(C_{wire} + \sum_{pins} C_{pin})

balanced_tree
     バランス型では全ての入力ピンが均等に負荷分散されていると仮定する．
     以下の式で :math:`N` は接続している入力ピン数(ファンアウト数)を表
     す．

     .. math::
	D_{C_{balanced}} = \frac{R_{wire}}{N}(\frac{C_{wire}}{N} + C_{pin})

上述の式に現れる要素の意味は以下の通り．

:math:`R_{wire}`
      配線抵抗の見積もり値． 配線長の見積もり値に `wire_load` グループ
      の `resistance` を掛けたもの．

:math:`C_{wire}`
      配線容量の見積もり値．配線長の見積もり値に `wire_load` グループ
      の `capacitance` を掛けたもの．

:math:`C_{pin}`
      負荷となっているピンの容量． `pin` グループの `capacitance`
      で定義されている．

Interconnect Delay
^^^^^^^^^^^^^^^^^^^^

遷移時間と接続遅延を足したもの．

.. math::
   D_{interconnect} = D_T + D_C

遅延時間の計算例
^^^^^^^^^^^^^^^^

インバーターの出力に3つのNANDゲートが接続している例
入力信号は遷移時間 :math:`D_{T(prevstage)} = 1.2`
で達下がった場合の遅延時間
NANDの入力ピンの容量は :math:`1.1`
配線容量は :math:`2.6`

::

   intrinsic_rise = 1.4
   rise_resistance = 0.14
   slope_rise = 0.02
   Cpins = 3 * (1.1) = 3.3
   Cwire = 2.6
   DT(fall_previous_stage) = 1.2
   DC = 0 /* best-case */
   D = DI + DS + DT + DC
     = 1.4 +                /* DT */
       1.2 * 0.02 +         /* DS */
       0.14 * (3.3 + 2.6) + /* DT */
       0.0                  /* DC */
     = 2.25


CMOS Nonlinear Delay Model
---------------------------

CMOS 非線形遅延モデルは表引きと補完を用いてより高精度な遅延の見積もり
を行うモデルである．

CMOS非線形遅延モデルでは大まかには以下の式で計算される．

.. math::
   D_{total} = D_{cell} + D_{C}


:math:`D_{cell}`
      セルの入力ピンの信号変化からセルの出力ピンの信号変化までの遅延時間
      具体的には2種類の計算方法がある(後述).

:math:`D_C`
      接続遅延．セルの出力ピンの信号変化から接続先の入力ピンの信号変化
      までの遅延時間

:math:`D_{cell}` 用のテーブルが存在しない場合には以下の式が用いられる．

.. math::
   D_{cell} = D_{propagation} + D_{transition}

:math:`D_{propagation}`
      入力ピンの線号変化から出力ピンの信号変化の開始までの遅延時間．
      例えば，出力ピンの電位が10%に到達するまでの時間．

:math:`D_{transition}`
      出力ピンの信号電位の定められた2点間(例えば20%から80%)の遷移にか
      かる時間.

Cell Delay
^^^^^^^^^^^

セルの入力ピンの信号変化から出力ピンの信号変化までにかかる遅延時間．
通常は入力の遷移時間と出力の負荷容量の関数となる．
具体的には `timing` グループ中の `cell_rise`, `cell_fall`
を用いて指定する．

Propagateion Delay
^^^^^^^^^^^^^^^^^^^

Cell Delay と似ているが，こちらは出力ピンの信号変化の開始タイミング
までの遅延時間．
多くの場合，入力ピンの遷移時間と出力の負荷容量の関数となる．
具体的には `timing` グループ中の `rise_propagation`,
`fall_propagation` を用いて指定する．

Cell Delay と Propagation Delay は排他的であり，どちらか一方しか
定義できない．

Transition Delay
^^^^^^^^^^^^^^^^^^

セルの出力ピンの信号変化にかかる時間．
例えば 20% から 80% のレベルに遷移するまでの時間．
多くの場合，入力ピンの遷移時間と出力の負荷容量の関数となる．
具体的には `timing` グループ中の `rise_transition`, `fall_transition`
を用いて指定する．

Connect Delay
^^^^^^^^^^^^^^

セルの出力ピンの信号変化が接続先のセルの入力ピンの信号変化に到達するま
での時間．内容は CMOS Generic Delay Model と同一である．


Scalable Polynomial Delay Model
--------------------------------

CMOS 非線形遅延モデルよりもコンパクトで高速な手法．
lookup table の代わりに高次元多項式を用いる．
例えば関数D(x, y)をそれぞれxの1次元多項式と
yの2次元多項式を用いて以下の様に表す．

.. math::
   D(x, y) = (a_0 + a_1 \times x)(b_0 + b_1 \times y + b_2 \times y^2)

この場合，:math:`a_0, a_1, b_0, b_1, b_2` の計5個の係数でこの関数を
記述することができる．

... [未完]

CMOS piecewise Linear Delay Model
----------------------------------

パラメータの範囲を区切り，同一の範囲内では CMOS Generic Delay Model
と同様の線形モデルを使用する遅延モデル．
基本的な計算式は CMOS Geneirc Delay Model と同様である．

パラメータの範囲の定義には `library` グループ中の `piece_define` 属性
を用いる．

::

   piece_define("length0 [length1 length2 ...]");
   piece_define("cap0 [cap1 cap2 ...]");

配線長が :math:`length0` と :math:`length1` の間の値を持つ場合，
配線長の区間は 0 に対応する．
容量も同様に :math:`cap0` と :math:`cap1` の間の値を持つ場合，
容量の区間は 0 に対応する．
区間は任意の値がいずれかの区間に対応するように定義されていなければならない．

区間に対応した値を持つ要素は区間番号と値をペアにした
`Complex Attribute` を用いて定義されていなければならない．
以下にピンの立ち上がり時の抵抗の例を示す．

::

   rise_pin_resistance ( 0, 0.2); /* 区間0 */
   rise_pin_resistance ( 1, 0.4); /* 区間1 */
   rise_pin_resistance ( 2, 0.6); /* 区間2 */
   rise_pin_resistance ( 3, 0.8); /* 区間3 */

常に全ての区間に対応した値を定義しなければならないわけではない．
例えば上の例で区間0と区間2のみを定義した場合，
区間1と区間3はそれぞれ区間0と区間2の値を用いて補完される．

Intrinsic Delay
^^^^^^^^^^^^^^^^^

区間線形モデルに置いても intrinsic delayは
`timing` グループの `intrinsic_rise` と `intrinsic_fall`
を用いて定義される．

Slope Delay
^^^^^^^^^^^^^^

slope delay も CMOS Generic Delay Model と同様に
`timing` グループの `slope_rise` と `slope_fall` を
用いて定義される．

Transition Delay
^^^^^^^^^^^^^^^^^

遷移遅延は出力ピンの信号変化にかかる時間を表している．

以下の式で計算される．

.. math::

   D_T = R_{tdrive_i}(C_{pins} + C_{wire}) + Y_{adj_j}

:math:`R_{tdrive_i}`
      ドライバ(出力)ピンの抵抗値．
      `timing` グループ中の `rise_pin_resistance` および
      `fall_pin_resistance` 属性を用いて定義される．
      CMOS Generic Delay Model の場合と異なり，
      これらの属性は区間と値のペアを持つ `Complex Attribute`
      となる．

:math:`C_{pns}`
      接続先のピンの容量の総和．
      `pin` グループの `capacitance` 属性の値を用いる．

:math:`C_{wire}`
      配線容量の見積もり値．
      `wire_load` グループ中の `fanout_length` 属性
      を用いて配線長を見積もり，`capacitance` の値を
      掛けて容量を計算する．

:math:`Y_{adj_i}`
      Y-intercept の値を表す．
      `timing` グループ中の `rise_delay_intercept`
      および `fall_delay_intercept` 属性の値を用いる．
      この属性は区間と値のペアとなる．

Connect Delay
^^^^^^^^^^^^^^

接続遅延は出力ピンの信号変化が接続先の入力ピンの信号変化に
伝わるまでの時間を表す．CMOS Generic Delay Model と同様．


Delay Calculation Module (DCM) Delay Model
-------------------------------------------

DCM を用いた場合，liberty 中の遅延関係のパラメータは無視される．
