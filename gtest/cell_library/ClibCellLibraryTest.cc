
/// @file ClibCellLibraryTest.cc
/// @brief ClibCellLibraryTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017 Yusuke Matsunaga
/// All rights reserved.


#include "gtest/gtest.h"
#include "ym/ClibCellLibrary.h"
#include "ym/FileIDO.h"
#include "ym/FileODO.h"
#include "ym/MsgHandler.h"
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
    MsgMgr::reg_handler(new StreamMsgHandler(&cout));
    string filename = string(DATA_DIR) + string("/HIT018.typ.snp");
    ClibCellLibrary library;
    bool stat = library.read_liberty(filename);

    EXPECT_TRUE( stat );

    EXPECT_EQ( 310, library.cell_num() );

    display_library(cout, library);
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
      FileODO odo;
      bool r = odo.open(dump_filename);
      ASSERT_TRUE ( r );
      library.dump(odo);
    }

    ClibCellLibrary library2;
    {
      FileIDO ido;
      bool r = ido.open(dump_filename);
      ASSERT_TRUE ( r );
      library2.restore(ido);
    }

    EXPECT_EQ( library.cell_num(), library2.cell_num() );

    display_library(cout, library2);
  }
  catch ( AssertError obj ) {
    cout << obj << endl;
    EXPECT_TRUE( false );
  }
}

END_NAMESPACE_YM_CLIB
