
/// @file read_liberty.cc
/// @brief liberty 形式のファイル読み込みのテストプログラム
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2022 Yusuke Matsunaga
/// All rights reserved.

#include "ym/ClibCellLibrary.h"


BEGIN_NAMESPACE_YM

int
read_liberty(
  int argc,
  char** argv
)
{
  string filename{TESTFILE};

  auto library = ClibCellLibrary::read_liberty(filename);

  library.display(cout);

  string dump_filename = "./foo.dump";

  {
    ofstream s(dump_filename);
    ASSERT_COND ( s.is_open() );
    library.dump(s);
  }

  ClibCellLibrary library2;
  {
    ifstream s(dump_filename);
    ASSERT_COND ( s.is_open() );
    library2.restore(s);
  }

  return 0;
}

END_NAMESPACE_YM


int
main(
  int argc,
  char** argv
)
{
  return YM_NAMESPACE::read_liberty(argc, argv);
}
