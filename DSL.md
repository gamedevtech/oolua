|Name|Portable|Description|
|:---|:-------|:----------|
|[OOLUA\_CLASS](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#62)|Yes|Used for portable code which is to have bases exposed|
|[OOLUA\_BASIC](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#63)|Yes|Required when using OOLUA\_CLASS to expose a class|
|[OOLUA\_BASES\_START](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#65)|Yes|Starts the list of base classes, required when using OOLUA\_CLASS|
|[OOLUA\_BASES\_END](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#65)|Yes|Ends the list of base classes, required when using OOLUA\_CLASS|
|[OOLUA\_CLASS\_NO\_BASES](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#16)|Yes|Helper macro which informs the library there are no base classes for this class to be exposed. |
|[OOLUA\_CLASS\_WITH\_BASES](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#71)|Yes|Helper macro which informs the library there is at least one base class|
|[OOLUA\_PROXY\_CLASS](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#87)|No|Varadic macro which can be used to start the generating of a proxy class. If supported can be used with and without bases.|
|[OOLUA\_CLASS\_END](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#90)|Yes|Ends the generation of a proxy class.|
|  |  |
|[OOLUA\_TYPEDEFS](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#13)|Yes|Starts the list of additional information|
|[OOLUA\_END\_TYPES](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#13)|Yes|Ends the list of additional information (Deprecated)|
|[OOLUA\_TYPEDEFS\_END](http://code.google.com/p/oolua/source/browse/tags/1.4.0/include/proxy_class.h#290)|Yes|Alias for OOLUA\_END\_TYPES so that it matches the format of other names|
|[OOLUA\_NO\_TYPEDEFS](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#56)|Yes|Defines that there is no additional information needed for the class|
|  |  |
|[OOLUA\_MEM\_FUNC](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#11)|No|Varadic macro for generating a member function|
|[OOLUA\_MEM\_FUNC\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#74)|No|Varadic macro for generating a constant member function |
|OOLUA\_MEM\_FUNC\_RENAME|No|Varadic macro for generating a member function which is to be renamed|
|[OOLUA\_MEM\_FUNC\_CONST\_RENAME](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_member_function_calls.h#17)|No|Varadic macro for generating a constant member function which is to be renamed |
|[OOLUA\_MEM\_FUNC\_X](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_const_func.h#10)|Yes|Generates a function which has X parameters|
|[OOLUA\_MEM\_FUNC\_X\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_const_func.h#9)|Yes|Generates a constant function which has X parameters|
|[OOLUA\_MEM\_FUNC\_X\_RENAME](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_out_params.h#15)|Yes|Generates a function with X parameters which is to be renamed|
|OOLUA\_MEM\_FUNC\_X\_CONST\_RENAME |Yes|Generates a constant function with X parameters which is to be renamed|
|[OOLUA\_DEDUCE\_FUNC](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_max_params.h#18) |Yes|Generates a function which deduces the function signature if there is no ambiguity|
|[OOLUA\_DEDUCE\_FUNC\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#29) |Yes|Generates a constant function which deduces the constant function signature if there is no ambiguity|
|  |  |
|[OOLUA\_C\_FUNCTION](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_static_and_c_functions.cpp#9)|No| Varadic macro for generating a C function's body|
|[OOLUA\_C\_FUNCTION\_X](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_static_and_c_functions.cpp#8)|Yes | Generates a C function's body which has X parameters|
|  |  |
|[OOLUA\_PUBLIC\_MEMBER\_GET ](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_public_instances.h#14)|Yes|Generates a constant function which returns a public data member|
|OOLUA\_PUBLIC\_MEMBER\_SET |Yes|Generates a function which returns a public data member|
|[OOLUA\_PUBLIC\_MEMBER\_GET\_SET](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_public_instances.h#13) |Yes|Generates both a get and set functions for a public data member|
|  |  |
|[OOLUA\_ENUMS](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_enum.h#12)|Yes |Starts the set of class enums which will be bound using OOLUA\_ENUM\_ENTRY|
|[OOLUA\_ENUM\_ENTRY](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_enum.h#13)|Yes |Informs the library of a class enum to be exposed to Lua|
|[OOLUA\_ENUMS\_END](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_enum.h#15)|Yes |Ends the set of class enums that were started with OOLUA\_ENUMS|
|  |  |
|[OOLUA\_CONSTRUCTORS\_BEGIN](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_class_constructors.h#10)|Yes|Starts the generation of constructors to make available |
|[OOLUA\_CONSTRUCTORS\_END](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_class_constructors.h#22)|Yes|Ends the generation of constructors |
|[OOLUA\_ONLY\_DEFAULT\_CONSTRUCTOR](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.h#57)|Yes|Helper macro which only makes available a public default constructor |
|[OOLUA\_CONSTRUCTOR\_X](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_class_constructors.h#20)|Yes|Generates a constructor which takes X parameters |
|[OOLUA\_CONSTRUCTOR](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_class_constructors.h#21)|No|Varadic macro which generates a constructor |
|  |  |
|[EXPORT\_OOLUA\_FUNCTIONS\_X\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.cpp#9)|Yes|Exports X functions for the class |
|[EXPORT\_OOLUA\_FUNCTIONS\_X\_NON\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.cpp#8)|Yes|Exports X constant functions for the class|
|[EXPORT\_OOLUA\_FUNCTIONS\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.cpp#6)|No|Varadic macro which exports constant functions for the class|
|[EXPORT\_OOLUA\_FUNCTIONS\_NON\_CONST](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.cpp#5)|No|Varadic macro which exports functions for the class|
|[EXPORT\_OOLUA\_NO\_FUNCTIONS](http://code.google.com/p/oolua/source/browse/tags/1.4.0/unit_tests/bind_classes/expose_hierarchy.cpp#42)|Yes|Helper macro which defines the class has no functions to export |