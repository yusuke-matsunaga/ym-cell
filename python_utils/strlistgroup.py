#! /usr/bin/env python3

### @file strlistgroup.py
### @brief StrListHeaderHandler のパース関数登録用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.


class StrListGroupClassDef :

    def __init__(self) :
        pass

    @property
    def header_class(self) :
        return 'StrListHeaderHandler'

    ### @brief アクセッサー関数の宣言を生成する．
    def gen_accessor_decl(self, fout) :
        fout.write('\n')
        fout.write('  /// @brief 名前のリストの要素数を返す．\n')
        fout.write('  int\n')
        fout.write('  name_num() const;\n')
        fout.write('\n')
        fout.write('  /// @brief 名前のリストの要素を返す．\n')
        fout.write('  /// @param[in] pos 位置番号 ( 0 <= pos < name_num() )\n')
        fout.write('  const AstString*\n')
        fout.write('  name(int pos) const;\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init(self, fout) :
        fout.write('  mNameNum(header.name_list().size()),\n')
        fout.write('  mNameList(alloc.get_array<const AstString*>(mNameNum)),\n')

    ### @brief アクセッサー関数のインライン定義を生成する．
    def gen_accessor_impl(self, fout) :
        class_name = self.ast_class
        fout.write('\n')
        fout.write('// @brief 名前のリストの要素数を返す．\n')
        fout.write('inline\n')
        fout.write('int\n')
        fout.write('{}::name_num() const\n'.format(class_name))
        fout.write('{\n')
        fout.write('  return mNameNum;\n')
        fout.write('}\n')
        fout.write('\n')
        fout.write('// @brief 名前のリストの要素を返す．\n')
        fout.write('// @param[in] pos 位置番号 ( 0 <= pos < name_num() )\n')
        fout.write('inline\n')
        fout.write('const AstString*\n')
        fout.write('{}::name(int pos) const\n'.format(class_name))
        fout.write('{\n')
        fout.write('  ASSERT_COND( pos >= 0 && pos < name_num() );\n')
        fout.write('\n')
        fout.write('  return mNameList[pos];\n')
        fout.write('}\n')

    ### @brief メンバ定義を生成する．
    def gen_member_def(self, fout) :
        fout.write('\n')
        fout.write('  // ピン名のリストの要素数\n')
        fout.write('  int mNameNum;\n')
        fout.write('\n')
        fout.write('  // ピン名のリスト\n')
        fout.write('  const AstString** mNameList;\n')

    ### @brief メンバの初期化文を生成する．
    def gen_member_init2(self, fout) :
        fout.write('  for ( auto i: Range(mNameNum) ) {\n')
        fout.write('    mNameList[i] = header.name_list()[i];\n')
        fout.write('  }\n')
