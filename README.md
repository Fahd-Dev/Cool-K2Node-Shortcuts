# Before
<img width="500" height="501" alt="لقطة شاشة 2026-05-07 033429" src="https://github.com/user-attachments/assets/8e1bfc3b-93e9-4a4c-80c2-5fd6b85b4ef6" />

# After
<img width="572" height="342.5" alt="لقطة شاشة 2026-05-07 033449" src="https://github.com/user-attachments/assets/38a527fe-9805-451b-933b-9edd8a270690" />


# Setting up Library
1. Make sure your ``PublicDependencyModuleNames.AddRange(new string[] { ... });`` in your ``.Build.cs`` file have: 
``` cpp
"BlueprintGraph", "KismetCompiler", "UnrealEd"
```
2. Download ``CoolShortcuts.h``.
3. Drag and Drop the file into your project directory via your IDE; Compile project if needed

**That's it!**

---

# TIP
**To include the file without typing its full directory path, follow these steps**
1. Create a folder in this directory (Source->ProjectName) and name it whatever you want \
	<sup>Files in this folder can be included using only their filename</sup>
   
2. Put ``CoolShortcuts.h`` inside it
3. Add this in your ``.build.cs`` at the top
```c#
using System.IO;
```
And This in the class
```c#
PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "FolderName") });
```
Replace "FolderName" with the name you chose in step 1

---


# All macros are explained in ``CoolShortcuts.h``
