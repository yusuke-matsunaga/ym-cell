#ifndef ASTMGR_H
#define ASTMGR_H

/// @file AstMgr.h
/// @brief AstMgr のヘッダファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/dotlib_nsdef.h"
#include "dotlib/AttrType.h"
#include "dotlib/AstCPType.h"
#include "ym/ShString.h"
#include "ym/FileRegion.h"
#include "ym/SimpleAlloc.h"


BEGIN_NAMESPACE_YM_DOTLIB

class EmptyHandler;
class FloatFloatHandler;
class FloatStrHandler;
class FloatVectorHandler;
class IntFloatHandler;
class IntFloatVectorHandler;
class IntVectorHandler;
class StrHandler;
class StrFloatHandler;
class StrIntHandler;
class StrStrHandler;
class StrStrIntHandler;
class StrStrStrHandler;
class StrFloatHandler;
class StrListHandler;

class LibraryHandler;
class CellHandler;
class DomainHandler;
class FFHandler;
class InputVoltageHandler;
class LatchHandler;
class OutputVoltageHandler;
class PinHandler;
class TemplateHandler;
class TableHandler;
class TimingHandler;

//////////////////////////////////////////////////////////////////////
/// @class AstMgr AstMgr.h "AstMgr.h"
/// @brief dotlib の AST ノードを管理するクラス
///
/// AST ノードは DotlibParser 内で生成されるが，DotlibParser が削除された
/// 後も存在している必要があるので AST ノードのオーナーとして AstMgr を
/// 用いる．
//////////////////////////////////////////////////////////////////////
class AstMgr
{
public:

  /// @brief コンストラクタ
  AstMgr();

  /// @brief デストラクタ
  ///
  /// ここで生成した全てのノードが削除される．
  ~AstMgr();


public:
  //////////////////////////////////////////////////////////////////////
  // 外部インターフェイス
  //////////////////////////////////////////////////////////////////////

  /// @brief 初期化する．
  ///
  /// 以前，生成されたオブジェクトは破壊される．
  void
  clear();

  /// @brief 根のノードを返す．
  const AstLibrary*
  library_node() const;


public:
  //////////////////////////////////////////////////////////////////////
  // AstExpr を生成する関数
  //////////////////////////////////////////////////////////////////////

  /// @brief + 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_plus(const AstExpr* opr1,
	   const AstExpr* opr2);

  /// @brief - 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_minus(const AstExpr* opr1,
	    const AstExpr* opr2);

  /// @brief * 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_mult(const AstExpr* opr1,
	   const AstExpr* opr2);

  /// @brief / 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_div(const AstExpr* opr1,
	  const AstExpr* opr2);

  /// @brief NOT 演算子を表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] opr オペランド
  const AstExpr*
  new_not(const FileRegion& loc,
	  const AstExpr* opr);

  /// @brief AND 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_and(const AstExpr* opr1,
	  const AstExpr* opr2);

  /// @brief OR 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_or(const AstExpr* opr1,
	 const AstExpr* opr2);

  /// @brief XOR 演算子を表す AstExpr を生成する．
  /// @param[in] opr1, opr2 オペランド
  const AstExpr*
  new_xor(const AstExpr* opr1,
	  const AstExpr* opr2);

  /// @brief ブール値(0 or 1)を表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] val 値
  const AstExpr*
  new_bool_expr(const FileRegion& loc,
		bool val);

  /// @brief 実数値を表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] val 値
  const AstExpr*
  new_float_expr(const FileRegion& loc,
		 double val);

  /// @brief VDDを表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  const AstExpr*
  new_vdd_expr(const FileRegion& loc);

  /// @brief VSSを表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  const AstExpr*
  new_vss_expr(const FileRegion& loc);

  /// @brief VCCを表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  const AstExpr*
  new_vcc_expr(const FileRegion& loc);

  /// @brief 文字列を表す AstExpr を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] str 値
  const AstExpr*
  new_str_expr(const FileRegion& loc,
	       const ShString& str);


public:
  //////////////////////////////////////////////////////////////////////
  // simple attribute の値を表す AstNode を作る関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ブール値を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstBool*
  new_bool(const FileRegion& loc,
	   bool value);

  /// @brief clear_preset_var の値を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstCPType*
  new_cptype(const FileRegion& loc,
	     AstCPType::Type value);

  /// @brief 整数値を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstInt*
  new_int(const FileRegion& loc,
	  int value);

  /// @brief 実数値を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstFloat*
  new_float(const FileRegion& loc,
	    double value);

  /// @brief float のベクタ型の AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値(double のベクタ)
  const AstFloatVector*
  new_float_vector(const FileRegion& loc,
		   const vector<double>& value);

  /// @brief 整数値のベクタを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value_list 値のリスト
  const AstIntVector*
  new_int_vector(const FileRegion& loc,
		 const vector<int>& value_list);

  /// @brief 文字列シンボルを表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstString*
  new_string(const FileRegion& loc,
	     ShString value);

  /// @brief technology を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstTechnology*
  new_technology(const FileRegion& loc,
		 ClibTechnology value);

  /// @brief delay model を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstDelayModel*
  new_delay_model(const FileRegion& loc,
		  ClibDelayModel value);

  /// @brief direction を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstDirection*
  new_direction(const FileRegion& loc,
		ClibDirection value);

  /// @brief timing_sense を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstTimingSense*
  new_timing_sense(const FileRegion& loc,
		   ClibTimingSense value);

  /// @brief timing_type を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstTimingType*
  new_timing_type(const FileRegion& loc,
		  ClibTimingType value);

  /// @brief var_type を表す AstNode を生成する．
  /// @param[in] loc ファイル上の位置
  /// @param[in] value 値
  const AstVarType*
  new_var_type(const FileRegion& loc,
	       ClibVarType value);


public:
  //////////////////////////////////////////////////////////////////////
  // complex attribute の値を表す AstNode を作る関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ( float, float ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstFloat2*
  new_float2(const FloatFloatHandler& handler);

  /// @brief ( float, string ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstFloatStr*
  new_float_str(const FloatStrHandler& handler);

  /// @brief ( integer, float ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstIntFloat*
  new_int_float(const IntFloatHandler& handler);

  /// @brief ( integer, float_vector ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstIntFloatVector*
  new_int_float_vector(const IntFloatVectorHandler& handler);

  /// @brief ( string, float ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstStrFloat*
  new_str_float(const StrFloatHandler& handler);

  /// @brief ( string, int ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstStrInt*
  new_str_int(const StrIntHandler& handler);

  /// @brief ( string, string, ... ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstStrList*
  new_str_list(const StrListHandler& handler);

  /// @brief ( string, string ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstStr2*
  new_str2(const StrStrHandler& handler);

  /// @brief ( string, string, string ) 型の AstNode を生成する．
  /// @param[in] handler ハンドラ
  const AstStr3*
  new_str3(const StrStrStrHandler& handler);


public:
  //////////////////////////////////////////////////////////////////////
  // group statement の値を表す AstNode を作る関数
  //////////////////////////////////////////////////////////////////////

  /// @brief ライブラリを表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstLibrary*
  new_library(const StrHandler& header,
	      const LibraryHandler& group);

  /// @brief セルを表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstCell*
  new_cell(const StrHandler& header,
	   const CellHandler& group);

  /// @brief ピンを表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstPin*
  new_pin(const StrListHandler& header,
	  const PinHandler& group);

  /// @brief cell_degradation を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstCellDegradation*
  new_cell_degradation(const FileRegion& loc,
		       const AstString* name,
		       const AstString* calc_mode,
		       const AstFloatVector* index_1,
		       const AstFloatVector* values,
		       const AstFloatVector* coefs,
		       const AstIntVector* orders,
		       const AstVariableRange* variable_1_range,
		       const AstDomain* domain);

  /// @brief ff を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstFF*
  new_ff(const StrStrHandler& header,
	 const FFHandler& group);

  /// @brief ff_bank を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstFFBank*
  new_ff_bank(const StrStrIntHandler& header,
	      const FFHandler& group);

  /// @brief latch を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstLatch*
  new_latch(const StrStrHandler& header,
	    const LatchHandler& group);

  /// @brief latch_bank を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstLatchBank*
  new_latch_bank(const StrStrIntHandler& header,
		 const LatchHandler& group);

  /// @brief lut template を表す AstNode を生成する．
  /// @param[in] header ヘッダのハンドラ
  /// @param[in] group グループ本体のハンドラ
  const AstTemplate*
  new_template(const StrHandler& header,
	       const TemplateHandler& group);

  /// @brief lut を表す AstNode を生成する．
  /// @param[in] header ヘッダのハンドラ
  /// @param[in] group グループ本体のハンドラ
  const AstLut*
  new_lut(const StrHandler& header,
	  const TableHandler& group);

  /// @brief input voltage を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstInputVoltage*
  new_input_voltage(const StrHandler& header,
		    const InputVoltageHandler& group);

  /// @brief output voltage を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstOutputVoltage*
  new_output_voltage(const StrHandler& header,
		     const OutputVoltageHandler& group);

  /// @brief domain を表す AstNode を生成する．
  /// @param[in] header ヘッダを読み込んだハンドラ
  /// @param[in] group グループ本体を読み込んだハンドラ
  const AstDomain*
  new_domain(const StrHandler& header,
	     const DomainHandler& group);

  /// @brief timing を表す AstNode を生成する．
  /// @param[in] header ヘッダのハンドラ
  /// @param[in] group グループ本体のハンドラ
  const AstTiming*
  new_timing(const StrListHandler& header,
	     const TimingHandler& group);

  /// @brief 使用メモリ量の一覧を出力する．
  /// @param[in] s 出力先のストリーム
  void
  show_stats(ostream& s) const;


private:
  //////////////////////////////////////////////////////////////////////
  // データメンバ
  //////////////////////////////////////////////////////////////////////

  // メモリアロケータ
  SimpleAlloc mAlloc;

  // 根のノード
  AstLibrary* mLibraryNode;

  // 個々の要素の使用数
  int mBoolNum;
  int mBoolExprNum;
  int mDelayModelNum;
  int mDirectionNum;
  int mFloatNum;
  int mFloat2Num;
  int mFloatExprNum;
  int mFloatStrNum;
  int mFloatVectNum;
  int mFloatVectElemSize;
  int mIntNum;
  int mIntFloatNum;
  int mIntFloatVectorNum;
  int mIntVectNum;
  int mIntVectElemSize;
  int mStrNum;
  int mStr2Num;
  int mStr3Num;
  int mStrFloatNum;
  int mStrIntNum;
  int mStrVectNum;
  int mStrVectElemSize;
  int mOprNum;
  int mNotNum;
  int mDomainNum;
  int mSymbolExprNum;
  int mStrExprNum;
  int mListNum;
  int mListElemSize;
  int mTemplateNum;
  int mLutNum;
  int mInputVolNum;
  int mOutputVolNum;
  int mPieceWiseNum;
  int mTechnologyNum;
  int mTimingSenseNum;
  int mTimingTypeNum;
  int mVarTypeNum;
  int mVarRangeNum;
  int mFFNum;
  int mFFBankNum;
  int mLatchNum;
  int mLatchBankNum;
  int mAttrNum;
};

END_NAMESPACE_YM_DOTLIB

#endif // ASTMGR_H
