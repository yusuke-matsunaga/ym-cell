
.. _latch_group:

latch Group statement
^^^^^^^^^^^^^^^^^^^^^^

::

  latch ( string, string ) {
    clear : "Boolean expression" ;
    clear_preset_var1 : L | H | N | T | X ;
    clear_preset_var2 : L | H | N | T | X ;
    data_in : "Boolean expression" ;
    enable : "Boolean expression" ;
    enable_also : "Boolean expression" ;
    preset : "Boolean expression" ;
  }

.. _latch_bank_group:

latch_bank Group statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

  latch_bank ( string, string, integer ) {
    clear : "Boolean expression" ;
    clear_preset_var1 : L | H | N | T | X ;
    clear_preset_var2 : L | H | N | T | X ;
    data_in : "Boolean expression" ;
    enable : "Boolean expression" ;
    enable_also : "Boolean expression" ;
    preset : "Boolean expression" ;
  }

中身は latch と同じ
