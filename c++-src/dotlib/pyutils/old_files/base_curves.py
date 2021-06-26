#! /usr/bin/env python3

### @file base_curves.py
### @brief 'base_curves' のパース用のコードを生成するスクリプト
### @author Yusuke Matsunaga (松永 裕介)
###
### Copyright (C) 2018 Yusuke Matsunaga
### All rights reserved.

from parse_gen import HandlerData, parse_gen

base_curves_data = HandlerData(attr_name='base_curves',
                               header='',
                               simple={ 'base_curve_type': 'string' },
                               complex={}
                               group={})
def gen_pin_data():
    pin_data = HandlerData(attr_name='pin',
                           header='sStrHeader',
                           simple={},
                           complex={'power_gating_pin': 'string_int'},
                           group={'dc_current': 'dc_current',
                                  'electromigration': 'electromigration',
                                  'input_signal_swing': 'signal_swing',
                                  'internal_power': 'internal_power',
                                  'max_trans': 'trans',
                                  'min_pulse_width': 'pulse_width',
                                  'minimum_period': 'minimum_period',
                                  'pin_capacitance': 'pin_capacitance',
                                  'timing': 'timing',
                                  'tlatch': 'tlatch'})

    for trans in ( 'fall', 'rise' ):
        key = '{}_capacitance_range'.format(trans)
        pin_data.complex[key] = 'float_float'

    for pos in ( 'first', 'last' ):
        key = 'ccsn_{}_state'.format(pos)
        pin_data.group[key] = 'ccsn'

    for hl in ( 'above_high', 'high', 'low', 'below_low' ) :
        key = 'hyperbolic_nose_{}'.foramt(hl)
        pin_data.group[key] = 'hyperbolic_noise'

    for io in ( 'input', 'output' ):
        key = '{}_signal_swing'.format(io)
        pin_data.group[key] = 'signal_swing'
