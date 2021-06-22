
/// @file Parser_handler.cc
/// @brief Parser の実装ファイル(ハンドラの初期化)
/// @author Yusuke Matsunaga (松永 裕介)
///
/// Copyright (C) 2005-2011, 2014, 2018, 2021 Yusuke Matsunaga
/// All rights reserved.

#include "dotlib/Parser.h"
#include "dotlib/AstValue.h"
#include "dotlib/AstAttr.h"
#include "dotlib/TokenType.h"


BEGIN_NAMESPACE_YM_DOTLIB

// static member の定義

FixedElemHeader Parser::sEmptyHeader({});

FixedElemHeader Parser::sFloatFloatHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float(); }
  }
);

FixedElemHeader Parser::sFloatStrHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); }
  }
);

FixedElemHeader Parser::sFloatVectorHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float_vector(); }
  }
);

FixedElemHeader Parser::sIntFloatHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_int(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float(); }
  }
);

FixedElemHeader Parser::sIntFloatVectorHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_int(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float_vector(); }
  }
);

FixedElemHeader Parser::sIntVectorHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_int_vector(); }
  }
);

FixedElemHeader Parser::sStrFloatHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_float(); },
  }
);

FixedElemHeader Parser::sStrHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); }
  }
);

FixedElemHeader Parser::sStrIntHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_int(); }
  }
);

FixedElemHeader Parser::sStrStrHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); }
  }
);

FixedElemHeader Parser::sStrStrIntHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_int(); }
  }
);

FixedElemHeader Parser::sStrStrStrHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); },
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); }
  }
);

FixedElemHeader Parser::sTechnologyHeader(
  {
    [](Scanner& scanner) -> AstValuePtr { return scanner.read_technology(); }
  }
);

ListHeader Parser::sFloatVectorListHeader(
  [](Scanner& scanner) -> AstValuePtr { return scanner.read_float_vector(); }
);

ListHeader Parser::sStrListHeader(
  [](Scanner& scanner) -> AstValuePtr { return scanner.read_string(); }
);

AttrHandlerDict Parser::sCellGroupDict;
AttrHandlerDict Parser::sDomainGroupDict;
AttrHandlerDict Parser::sFFGroupDict;
AttrHandlerDict Parser::sInputVoltageGroupDict;
AttrHandlerDict Parser::sLatchGroupDict;
AttrHandlerDict Parser::sLibraryGroupDict;
AttrHandlerDict Parser::sOutputVoltageGroupDict;
AttrHandlerDict Parser::sPinGroupDict;
AttrHandlerDict Parser::sTableGroupDict;
AttrHandlerDict Parser::sTemplateGroupDict;
AttrHandlerDict Parser::sTimingGroupDict;

END_NAMESPACE_YM_DOTLIB
