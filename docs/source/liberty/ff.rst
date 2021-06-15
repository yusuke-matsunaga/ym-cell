
.. _ff_group:

ff Group statement
^^^^^^^^^^^^^^^^^^^

::

  ff ( string, string ) {
    clear : "Boolean expression" ;
    clear_preset_var1 : L | H | N | T | X ;
    clear_preset_var2 : L | H | N | T | X ;
    clocked_on : "Boolean expression" ;
    clocked_on_also : "Boolean expression" ;
    next_state : "Boolean expression" ;
    preset : "Boolean expression" ;
  }

.. _ff_bank_group:

ff_bank Group statement
^^^^^^^^^^^^^^^^^^^^^^^^

::

  ff_bank ( string, string, integer ) {
    clear : "Boolean expression" ;
    clear_preset_var1 : L | H | N | T | X ;
    clear_preset_var2 : L | H | N | T | X ;
    clocked_on : "Boolean expression" ;
    clocked_on_also : "Boolean expression" ;
    next_state : "Boolean expression" ;
    preset : "Boolean expression" ;
  }

中身は ff group と同じ
