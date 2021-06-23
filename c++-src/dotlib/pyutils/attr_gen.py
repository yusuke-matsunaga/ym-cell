#! /usr/bin/env python3

"""
AttrType.h, AttrType.cc, AttrDic.cc を生成するスクリプト

:file: attr_gen.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2021 Yusuke Matsunaga, All rights reserved.
"""

def read_data(filename):
    """属性名のリストのファイルを読み込み，
    文字列のリストの形で返す．

    :param filename: データファイル名
    """

    attr_list = []
    with open(filename, "rt") as fin:
        for attr in fin:
            attr = attr.rstrip().lstrip()
            attr_list.append(attr)
        return attr_list

    print("{}: No such file".format(filename))
    return None


def gen_attr_type_h(attr_list, filename):
    """AttrType.h を作る．

    :param attr_list: 属性名のリスト
    :param filename: 出力ファイル名
    """

    with open(filename, "wt", encoding="utf_8_sig") as fout:
        header = """#ifndef ATTRTYPE_H
#define ATTRTYPE_H

/// @file AttrType.h
/// @brief 属性を表す列挙型
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib_nsdef.h"


BEGIN_NAMESPACE_YM_DOTLIB

/// @brief 属性を表す列挙型
enum class AttrType {
"""
        fout.write(header)
        for attr in attr_list:
            fout.write("  {},\n".format(attr))
        footer = """};

/// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,     ///< [in] 出力先のストリーム
	   AttrType attr); ///< [in] 出力する値

END_NAMESPACE_YM_DOTLIB

BEGIN_NAMESPACE_STD

//////////////////////////////////////////////////////////////////////
// HashFunc<> の特殊化
//////////////////////////////////////////////////////////////////////
template<>
struct
hash<YM_NAMESPACE::nsClib::nsDotlib::AttrType>
{
  SizeType
  operator()(YM_NAMESPACE::nsClib::nsDotlib::AttrType key) const {
    return static_cast<SizeType>(key);
  }
};

END_NAMESPACE_STD

#endif // ATTRTYPE_H
"""
        fout.write(footer)
        return True

    print("{}: Could not open.")
    return False


def gen_attr_type_cc(attr_list, filename):
    """AttrType.cc を作る．

    :param attr_list: 属性名のリスト
    :param filename: 出力ファイル名
    """

    with open(filename, "wt", encoding="utf_8_sig") as fout:

        header = """
/// @file AttrType.cc
/// @brief AttrType の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018 Yusuke Matsunaga
/// All rights reserved.


#include "dotlib/AttrType.h"


BEGIN_NAMESPACE_YM_DOTLIB

// @brief AttrType の内容をストリームに出力する．
ostream&
operator<<(ostream& s,
	   AttrType attr)
{
  switch ( attr ) {
"""
        fout.write(header)
        for attr in attr_list:
            fout.write('  case AttrType::{0}: s << "{0}"; break;\n'.format(attr))

        footer = """  }
  return s;
}

END_NAMESPACE_YM_DOTLIB
"""
        fout.write(footer)


def gen_attr_dic_cc(attr_list, filename):
    """AttrDic.cc を作る．

    :param attr_list: 属性名のリスト
    :param filename: 出力ファイル名
    """

    with open(filename, "wt", encoding="utf_8_sig") as fout:

        header = """
/// @file AttrDic.cc
/// @brief AttrDic の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/AttrDic.h"


BEGIN_NAMESPACE_YM_DOTLIB

//////////////////////////////////////////////////////////////////////
// クラス AttrDic
//////////////////////////////////////////////////////////////////////

// @brief コンストラクタ
AttrDic::AttrDic()
{
"""
        fout.write(header)
        for attr in attr_list:
            fout.write('  mDic["{0}"] = AttrType::{0};\n'.format(attr))
        footer = """}

END_NAMESPACE_YM_DOTLIB
"""
        fout.write(footer)


filename="./attr_list.txt"
attr_list = read_data(filename)

gen_attr_type_h(attr_list, "A.h")
gen_attr_type_cc(attr_list, "B.cc")
gen_attr_dic_cc(attr_list, "C.cc")
