
/// @file ClibCellLibraryTest.cc
/// @brief ClibCellLibraryTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "gtest/gtest.h"
#include "ym/ClibCellLibrary.h"


BEGIN_NAMESPACE_YM_CLIB

TEST(ClibCellLibraryTest, read_mislib)
{
  try {
    string filename = string(DATA_DIR) + string("/lib2.genlib");
    ClibCellLibrary library;
    bool stat = library.read_mislib(filename);

    EXPECT_TRUE( stat );
  }
  catch ( AssertError obj ) {
    cout << obj << endl;
    EXPECT_TRUE( false );
  }
}

TEST(ClibCellLibraryTest, read_liberty)
{
  try {
    string filename = string(DATA_DIR) + string("/HIT018.typ.snp");
    ClibCellLibrary library;
    bool stat = library.read_liberty(filename);

    EXPECT_TRUE( stat );
  }
  catch ( AssertError obj ) {
    cout << obj << endl;
    EXPECT_TRUE( false );
  }
}

END_NAMESPACE_YM_CLIB
