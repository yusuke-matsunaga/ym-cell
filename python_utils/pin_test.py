#! /usr/bin/env python3

### @file pin_test.py
### @brief PinClassDef のテストプログラム
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

import sys
import argparse
import os.path

from gen_handler_code import gen_ast_header, gen_ast_source
from gen_handler_code import gen_handler_header, gen_handler_source
from pin import PinClassDef


if __name__ == '__main__' :

    parser = argparse.ArgumentParser()

    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--ast_header',
                            action = 'store_true',
                            help = 'generate AstPin.h')
    mode_group.add_argument('--ast_source',
                            action = 'store_true',
                            help = 'generate AstPin.cc')
    mode_group.add_argument('--handler_header',
                            action = 'store_true',
                            help = 'generate PinHandler.h')
    mode_group.add_argument('--handler_source',
                            action = 'store_true',
                            help = 'generate PinHandler.cc')

    args = parser.parse_args()
    if not args :
        exit(1)

    fout = sys.stdout
    class_def = PinClassDef()

    if args.ast_header :
        gen_ast_header(fout, class_def)
    elif args.ast_source :
        gen_ast_source(fout, class_def)
    elif args.handler_header :
        gen_handler_header(fout, class_def)
    elif args.handler_source :
        gen_handler_source(fout, class_def)
