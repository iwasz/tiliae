.. Tiliae documentation master file, created by
   sphinx-quickstart on Fri Jan 24 22:58:42 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to Tiliae's documentation!
==================================

Contents:

.. toctree::
   :maxdepth: 2


Reflection
==========
You enable reflection in CMakeLists.txt by adding: ::

 ADD_DEFINITIONS (-DREFLECTION_ENABLED)

Macros. Short version:

+-------+------------------------------+ 
| Macro | What it is                   | Arguments											  Notes
+=======+==============================+ 
| b_    | Base class                   | List of strings representing names of base classes. Use exactly the names as in ``E_`` and ``e__`` but as string.
+-------+                              | 
| b__   |                              | 
+-------+------------------------------+ 
| d__   | Abstract class               | 													  Use as the first macro of a abstract class.
+-------+------------------------------+ 
| g_    | Collection                   |                                                     Use like this : ``typedef std::list<std::string> StringList; g_ (StringList)``. Only some basic types of std::* collections are supported.
+-------+------------------------------+ 
| C_    | Constructor                  | 
+-------+                              |
| C__   |                              | 
+-------+------------------------------+ 
| fn_   | ? Obsolete ?                 | 
+-------+------------------------------+ 
| F_    | ? Obsolete ?                 | 
+-------+------------------------------+ 
| m_    | Method                       | 
+-------+                              | 
| m__   |                              | 
+-------+------------------------------+ 
| M_    | Overloaded method            | 
+-------+                              | 
| M__   |                              | 
+-------+------------------------------+ 
| Mc_   | Overloaded const method      | 
+-------+                              | 
| Mc__  |                              | 
+-------+------------------------------+ 
| S_    | Setter                       | 
+-------+                              | 
| S__   |                              | 
+-------+------------------------------+ 
| E_    | End of class                 | 
+-------+                              | 
| e__   |                              | 
+-------+------------------------------+ 
| tb_   | Template class footer begin  | 
+-------+------------------------------+ 
| t__   | Template class               | 
+-------+------------------------------+ 
| te_   | Template class footer end    | 
+-------+------------------------------+ 
| p_    | Property (return by value)   | 
+-------+------------------------------+ 
| pe_   | Property (enum)              | 
+-------+------------------------------+ 
| P_    | Property (return by handler) | 
+-------+------------------------------+ 

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

