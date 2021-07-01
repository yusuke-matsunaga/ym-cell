
/// @file ClibCellLibraryTest.cc
/// @brief ClibCellLibraryTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.

#include "gtest/gtest.h"
#include "ym/ClibCellLibrary.h"
#include "ym/StreamMsgHandler.h"
#include "ym/MsgMgr.h"


BEGIN_NAMESPACE_YM_CLIB

TEST(ClibCellLibraryTest, read_mislib)
{
  try {
    string filename = string(DATA_DIR) + string("/lib2.genlib");
    ClibCellLibrary library;
    bool stat = library.read_mislib(filename);

    EXPECT_TRUE( stat );

    EXPECT_EQ( 29, library.cell_num() );
  }
  catch ( AssertError obj ) {
    cout << obj << endl;
    EXPECT_TRUE( false );
  }
}

TEST(ClibCellLibraryTest, read_liberty)
{
  try {
    StreamMsgHandler handler(cout);
    MsgMgr::attach_handler(&handler);
    string filename = string(DATA_DIR) + string("/HIT018.typ.snp");
    ClibCellLibrary library;
    bool stat = library.read_liberty(filename);

    EXPECT_TRUE( stat );

    EXPECT_EQ( 310, library.cell_num() );
  }
  catch ( AssertError obj ) {
    cout << obj << endl;
    EXPECT_TRUE( false );
  }
}

TEST(ClibCellLibraryTest, dump_restore)
{
  try {
    string filename = string(DATA_DIR) + string("/HIT018.typ.snp");
    ClibCellLibrary library;
    bool stat = library.read_liberty(filename);

    EXPECT_TRUE( stat );

    EXPECT_EQ( 310, library.cell_num() );

    string dump_filename = "./foo.dump";

    {
      ofstream s(dump_filename);
      ASSERT_TRUE ( s.operator bool() );
      library.dump(s);
    }

    ClibCellLibrary library2;
    {
      ifstream s(dump_filename);
      ASSERT_TRUE ( s.operator bool() );
      library2.restore(s);
    }

    EXPECT_EQ( library.cell_num(), library2.cell_num() );
  }
  catch ( AssertError obj ) {
    cout << obj << endl;
    EXPECT_TRUE( false );
  }
}

END_NAMESPACE_YM_CLIB
