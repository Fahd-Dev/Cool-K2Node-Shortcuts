# Showcase

<img width="800" height="450" alt="Speedrun (1)" src="https://github.com/user-attachments/assets/a8f067c9-37c0-4bbb-8539-85648242e593" />

<sup>There's more macros</sup>

---

# Setting up Library
1. Make sure in your **Editor Module** ``PublicDependencyModuleNames.AddRange(new string[] { ... });`` in ``.Build.cs`` file have: 
``` cpp
"BlueprintGraph", "KismetCompiler", "UnrealEd"
```
2. Download [`CoolShortcuts.h`](./CoolShortcuts.h).
3. Drag and Drop the file into your project directory via your IDE. Compile project if needed

**That's it!**

---

# Tip
**To include the library without typing its full directory path, follow these steps**
1. Create a folder anywhere (In the Editor Module) and name it whatever you want \
	<sup>Files in this folder can be included using only their filename</sup>
   
2. Put ``CoolShortcuts.h`` inside it
3. Add this in your ``.build.cs`` at the top
```csharp
using System.IO;
```
And This in the class
```csharp
PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "FolderDirectory") });
```

---

## And Checkout this Tool
[![K2Nodes](https://img.shields.io/badge/Open-K2Node_Interface-blue?style=for-the-badge)](https://fahd-dev.github.io/Cool-K2Node-Shortcuts/)

# All macros are explained in [`CoolShortcuts.h`](./CoolShortcuts.h)
