#! /usr/bin/env python3

"""
パーサーの記述を生成するスクリプト

:file: parse_gen.py
:author: Yusuke Matsunaga (松永 裕介)
:copyright: Copyright (C) 2021 Yusuke Matsunaga, All rights reserved.
"""

import argparse
from handlerdata import HandlerData

parser = argparse.ArgumentParser()
parser.add_argument('-c', '--check', help='check integrity',
                    action='store_true')
parser.add_argument('-f', '--write-functions', help="write functions' description to 'FILENAME'",
                    nargs=1, metavar='FILENAME')
parser.add_argument('-d', '--write-dict', help="write dict's entries to 'FILENAME'",
                    nargs=1, metavar='FILENAME')

args = parser.parse_args()
if not args:
    exit(1)

import library_data
import cell_data
import pin_data
import timing_data

hd = HandlerData()

hd.merge(library_data.hd)
hd.merge(cell_data.hd)
hd.merge(pin_data.hd)
hd.merge(timing_data.hd)


if args.check:
    if not hd.check():
        exit(1)

if args.write_functions:
    filename, = args.write_functions
    with open(filename, 'wt', encoding='utf_8_sig') as fout:
        hd.print_functions(fout=fout)

if args.write_dict:
    filename, = args.write_dict
    with open(filename, 'wt', encoding='utf_8_sig') as fout:
        hd.print_dict(fout=fout)
