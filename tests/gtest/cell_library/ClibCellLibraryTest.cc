
/// @file ClibCellLibraryTest.cc
/// @brief ClibCellLibraryTest の実装ファイル
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2017, 2022 Yusuke Matsunaga
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
    auto library = ClibCellLibrary::read_mislib(filename);

    EXPECT_EQ( 29, library.cell_num() );

    ostringstream s;
    library.display(s);

    string exp_filename = string(DATA_DIR) + string("/lib2.genlib.display");
    ifstream is1{exp_filename};
    ASSERT_TRUE( is1 );

    istringstream is2{s.str()};
    string buff1;
    string buff2;
    while ( getline(is1, buff1) ) {
      getline(is2, buff2);
      EXPECT_TRUE( is2 );
      EXPECT_EQ( buff1, buff2 );
    }
    getline(is2, buff2);
    EXPECT_FALSE( is2 );
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
    auto library = ClibCellLibrary::read_liberty(filename);

    EXPECT_EQ( 310, library.cell_num() );

    ostringstream s;
    library.display(s);

    string exp_filename = string(DATA_DIR) + string("/HIT018.typ.snp.display");
    ifstream is1{exp_filename};
    ASSERT_TRUE( is1 );

    istringstream is2{s.str()};
    string buff1;
    string buff2;
    while ( getline(is1, buff1) ) {
      getline(is2, buff2);
      EXPECT_TRUE( is2 );
      EXPECT_EQ( buff1, buff2 );
    }
    getline(is2, buff2);
    EXPECT_FALSE( is2 );
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
    auto library = ClibCellLibrary::read_liberty(filename);

    EXPECT_EQ( 310, library.cell_num() );

    string dump_buff;
    {
      ostringstream s;
      library.dump(s);
      dump_buff = s.str();
    }

    ClibCellLibrary library2;
    {
      istringstream s{dump_buff};
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
