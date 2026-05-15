# Speedrun

<img width="800" height="450" alt="Speedrun (1)" src="https://github.com/user-attachments/assets/a8f067c9-37c0-4bbb-8539-85648242e593" />

<sup>There's more macros</sup>

# Setting up Library
1. Make sure your ``PublicDependencyModuleNames.AddRange(new string[] { ... });`` in your ``.Build.cs`` file have: 
``` cpp
"BlueprintGraph", "KismetCompiler", "UnrealEd"
```
2. Download [`CoolShortcuts.h`](./CoolShortcuts.h).
4. Drag and Drop the file into your project directory via your IDE. Compile project if needed

**That's it!**

---

# Tip
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


# All macros are explained in [`CoolShortcuts.h`](./CoolShortcuts.h)
