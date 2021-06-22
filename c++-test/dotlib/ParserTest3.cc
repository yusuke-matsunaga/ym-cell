
/// @file ParserTest3.cc
/// @brief ParserTest の実装ファイル(3)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2021 Yusuke Matsunaga
/// All rights reserved.

#include "ParserTest.h"
#include "Parser.h"
#include "AstAttr.h"
#include "AstValue.h"


BEGIN_NAMESPACE_YM_DOTLIB

TEST_F(ParserTest, parse_input_voltage1)
{
  istringstream buf("( 1.0, 2 );\n"
		    ""
  );
  InputFileObj in{buf, info};
  Parser parser{in, false, false};

  auto dst = parser.parse_float_float(attr);

  ASSERT_TRUE( dst != nullptr );
  auto& value = dst->value();
  EXPECT_EQ( 2, value.complex_elem_size() );
  EXPECT_EQ( 1.0, value.complex_elem_value(0).float_value() );
  EXPECT_EQ( 2.0, value.complex_elem_value(1).float_value() );
}

END_NAMESPACE_YM_DOTLIB
