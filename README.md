# Setting up Library
1. Make sure your ``PublicDependencyModuleNames.AddRange(new string[] { ... });`` in your ``.Build.cs`` file have: 
``` cpp
"BlueprintGraph", "KismetCompiler", "UnrealEd"
```
2. Download ``CoolShortcuts.h``.
3. Drag and Drop the file into your project directory via your IDE; Compile project if needed

**That's it!**

---

# Creating a K2Node Interface
## Setup K2Node Interface
_**You have two methods to Declare a K2Node**_

### Method 1
1. Include these at the top of your ``.h`` file:
``` h
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "DirectoryTo/CoolShortcuts.h"
```

2. Use This macro in your ``.h`` file:
``` h
DECLARE_K2NODE(UYour_Class, "Your Node Title", "ToolTip", "Category")
```
3. Compile your project

**_WARNING:_** This macro could INCREASE the compiling time

---

### Method 2
1. Include these at the top of your ``.h`` file:
``` h
#include "DirectoryTo/CoolShortcuts.h"
```
2. Use this macro in your ``.h`` file: ``DECLARE_K2NODE_ONLY``
3. Include these at the top of your ``.cpp`` file:
``` h
#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
```
4. Use this macro in the ``C++``:
``` cpp
IMPLEMENT_K2NODE_ONLY(UYour_Class, "Title", "Tooltip", "Category")
```

---

## Adding Pins
### Setup AllocateDefaultPins() function
1. Ovrride this function in your ``.h`` file:
``` cpp
virtual void AllocateDefaultPins() override;
```
2. Implement the function in your ``.cpp`` file:
``` cpp
void UYour_Class::AllocateDefaultPins()
{
	// Use macros here
}
```

---

### Pin Macros
_**You have 5 Macros for Adding Pins:**_

---

``` h
CREATE_STANDARD_EXEC_PINS
```
Adds two Exec Pins, _**Input**_ & _**Output**_

``` cpp
CREATE_OBJECT_PIN(Where, Type, "PinName")
```
Adds a UObject pin like: ``UCurveFloat``, ``AActor``, etc. 

``` cpp
CREATE_STRUCT_PIN(Where, Type, "PinName")
```
Adds a UStruct Pin like: ``FVector``, ``FRotator``, etc.

``` cpp
CREATE_TWO_TYPE_PIN(Where, Type, Type2, "PinName")
```
Adds a pin but you can use Two Types Like: ``PC_Real`` & ``PC_Float`` (Thats how you create a float pin) \
_**NOTE:**_ Both Types are ``UEdGraphSchema_K2``

``` cpp
CREATE_PIN(Where, Type, PinName)
```
Adds a Basic pin like: ``PC_Boolean``, ``PC_String``, ``PC_Int``, etc.
