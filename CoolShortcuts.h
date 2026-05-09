// Copyright (c) 2026 Fahd-Dev
// Github: https://github.com/Fahd-Dev/Cool-K2Node-Shortcuts

// This file has   V E R Y  C O O L   Shortcuts that will save you A LOT of time when creating K2Nodes

/**
 * =========================================================================================
 * COMPATIBILITY:                                                                          |
 * This library was developed and tested on Unreal Engine 5.7.                             |
 * Compatibility with older versions is likely but not guaranteed.                         |
 * Please report any issues or breaking changes for older/newer versions to the author.    |
 * Also the Library is not finished and still being improved & adding more macros          |
 * =========================================================================================
 */

#pragma once

/**
 * Declare with implementation for a K2Node 
 * IMPORTANT: Use this macro in The ".h". Will not work in the ".cpp".
 * REQUIRES: "BlueprintActionDatabaseRegistrar.h" and "BlueprintNodeSpawner.h"
 * WARNING: This macro could INCREASE the compiling time, if your project have a lot of K2Nodes, consider using these macros: DECLARE_K2NODE_ONLY with IMPLEMENT_K2NODE_ONLY
 */
#define CREATE_K2NODE(ClassName, Title, Tooltip, Category) \
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { \
        return NSLOCTEXT("K2Node", #ClassName "_Title", Title); \
    } \
    virtual FText GetTooltipText() const override { \
        return NSLOCTEXT("K2Node", #ClassName "_Tooltip", Tooltip); \
    } \
    virtual FText GetMenuCategory() const override { \
        return NSLOCTEXT("K2Node", #ClassName "_Category", Category); \
    } \
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override { \
        UClass* ActionKey = GetClass(); \
        if (ActionRegistrar.IsOpenForRegistration(ActionKey)) { \
            UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass()); \
            check(NodeSpawner != nullptr); \
            ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner); \
        } \
    }

/**
 * Declares GetNodeTitle, GetMenuCategory, GetTooltipText, GetMenuActions Functions
 * NOTE: This macro doesn't do anything without implementation
 * RECOMMENDATION: you can use the IMPLEMENT_K2NODE_ONLY Macro in the ".cpp"
 */
#define DECLARE_K2NODE_ONLY() \
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override; \
    virtual FText GetTooltipText() const override; \
    virtual FText GetMenuCategory() const override; \
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

/**
 * Implements the GetNodeTitle, GetMenuCategory, GetTooltipText, GetMenuActions Functions
 * REQUIRES: "BlueprintActionDatabaseRegistrar.h" and "BlueprintNodeSpawner.h"
 * IMPORTANT: You must declare these functions in the ".h" 
 * RECOMMENDATION: you can just use the macro named DECLARE_K2NODE_ONLY in the header.
 */
#define IMPLEMENT_K2NODE_ONLY(ClassName, Title, Tooltip, Category) \
    FText ClassName::GetNodeTitle(ENodeTitleType::Type TitleType) const { \
        return NSLOCTEXT("K2Node", #ClassName "_Title", Title); \
    } \
    FText ClassName::GetTooltipText() const { \
        return NSLOCTEXT("K2Node", #ClassName "_Tooltip", Tooltip); \
    } \
    FText ClassName::GetMenuCategory() const { \
        return NSLOCTEXT("K2Node", #ClassName "_Category", Category); \
    } \
    void ClassName::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const { \
        UClass* ActionKey = GetClass(); \
        if (ActionRegistrar.IsOpenForRegistration(ActionKey)) { \
            UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass()); \
            check(NodeSpawner != nullptr); \
            ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner); \
        } \
    }

/**
 * Handles the 'Search' keywords so your node shows up 
 * even if the user doesn't type the exact name.
 */
#define K2NODE_KEYWORD(Keyword) \
    virtual FText GetKeywords() const override { return FText::FromString(TEXT(Keyword)); }

/** 
 * a custom color for the bar on top of the node
 * IMPORTANT: IN HEADER ONLY
 * NOTE: You need a declared K2Node for this to work
 */
#define K2NODE_TITLE_COLOR(R, G, B) \
    virtual FLinearColor GetNodeTitleColor() const override { \
        return FLinearColor(R, G, B); \
    }

/** 
 * Make a K2Node Pure
 * IMPORTANT: IN HEADER ONLY
 * NOTE: You need a declared K2Node for this to work
 */
#define MAKE_K2NODE_PURE() \
    virtual bool IsNodePure() const override { \
        return true; \
    }

/**
 * Make a K2Node Compact
 * IMPORTANT: IN HEADER ONLY
 * NOTE: You need a declared K2Node for this to work
 * SECONDNOTE: You don't need to use MAKE_K2NODE_PURE, or make the node pure manually
 */
#define MAKE_K2NODE_COMPACT(CompactText) \
    MAKE_K2NODE_PURE(); \
    virtual bool ShouldDrawCompact() const override { return true; } \
    virtual FText GetCompactNodeTitle() const override { return FText::FromString(CompactText); }

/**
 * Will add two pins: an Input exec (PN_Execute) and an Output exec (PN_Then)
 * RECOMMENDATION: to connect them in the ExpandNode function you can use a macro named LINK_STANDARD_EXEC_PINS it will connect them for you
 */
#define CREATE_STANDARD_EXEC_PINS() \
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute); \
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

// Type Examples: UObject, UCurveFloat, AActor, etc.
#define CREATE_OBJECT_PIN(Where, Type, PinName) CreatePin(EGPD_##Where, UEdGraphSchema_K2::PC_Object, Type::StaticClass(), PinName);

// Type Examples: FVector, FRotator, FLinearColor, etc.
#define CREATE_STRUCT_PIN(Where, Type, PinName) CreatePin(EGPD_##Where, UEdGraphSchema_K2::PC_Struct, Type::StaticStruct(), PinName);

// Type Example: PC_Real - PC_Float, etc.
#define CREATE_TWO_TYPE_PIN(Where, Type, Type2, PinName) CreatePin(EGPD_##Where, UEdGraphSchema_K2::Type, UEdGraphSchema_K2::Type2, PinName);

// Type Examples: PC_Boolean, PC_String, PC_NAME, etc.
#define CREATE_PIN(Where, Type, PinName) CreatePin(EGPD_##Where, UEdGraphSchema_K2::Type, PinName);

/** Sets the default value of a pin by name */
#define SET_PIN_DEFAULT(PinName, Value) \
    if (UEdGraphPin* _TargetPin = FindPin(TEXT(PinName))) { \
        _TargetPin->DefaultValue = LexToString(Value);; \
    }

// there will be more macros for creating pins in the future, so stay tuned for updates.


/**
 * Creates a "UK2Node_CallFunction*"" variable named After the Value you've put in the "NodeVarName"
 * Stores the specified NodeClass and NodeFunction inside it
 * 
 * The variable is compatible with your K2Node and accessible for further customization
 * REQUIRES: You need to include "KismetCompiler.h" and "K2Node_CallFunction.h" for this to work
 */
#define ADD_INTERNAL_NODE(NodeVarName, NodeClass, NodeFunction) \
    UK2Node_CallFunction* NodeVarName = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph); \
    NodeVarName->SetFromFunction(NodeClass::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(NodeClass, NodeFunction))); \
    NodeVarName->AllocateDefaultPins();

/**
 * This will connect the PN_Execute & PN_Then Execs With the node in the Variable named after the "NodeName" Variable
 * RECOMMENDATION: you can use the CREATE_STANDARD_EXEC_PINS Macro in the "AllocateDefaultPins" Function, and it will work with this macro
 */
#define LINK_STANDARD_EXEC_PINS(NodeVar) \
    { \
        UEdGraphPin* _ExecIn = FindPin(UEdGraphSchema_K2::PN_Execute); \
        UEdGraphPin* _ExecOut = FindPin(UEdGraphSchema_K2::PN_Then); \
        UEdGraphPin* _CallExecIn = NodeVar->FindPin(UEdGraphSchema_K2::PN_Execute); \
        UEdGraphPin* _CallExecOut = NodeVar->FindPin(UEdGraphSchema_K2::PN_Then); \
        if (_ExecIn && _CallExecIn) \
        { \
            CompilerContext.MovePinLinksToIntermediate(*_ExecIn, *_CallExecIn); \
        } \
        if (_ExecOut && _CallExecOut) \
        { \
            CompilerContext.MovePinLinksToIntermediate(*_ExecOut, *_CallExecOut); \
        } \
    }

/** Links the return values from the K2Node with the Internal Node */
#define LINK_RETURN_VALUES(NodeVar) \
    { \
        UEdGraphPin* _InputPin = FindPin(UEdGraphSchema_K2::PN_ReturnValue); \
        UEdGraphPin* _TargetPin = NodeVar->FindPin(UEdGraphSchema_K2::PN_ReturnValue); \
        if (_InputPin && _TargetPin) \
        { \
            CompilerContext.MovePinLinksToIntermediate(*_InputPin, *_TargetPin); \
        } \
    }

/**
 * Connects two pins, one from the node and one from the internal node
 * so the Internal node can use the passed values
 */
#define LINK_PIN(NodeVar, InputPinName, WithPinName) \
    { \
        UEdGraphPin* _InputPin = FindPin(InputPinName); \
        UEdGraphPin* _TargetPin = NodeVar->FindPin(WithPinName); \
        if (_InputPin && _TargetPin) \
        { \
            CompilerContext.MovePinLinksToIntermediate(*_InputPin, *_TargetPin); \
        } \
    }

/* Gets & Declare the K2Node GUID and convert it to a string */
#define DECLARE_K2_GUID(GUID_VarName) FString GUID_VarName = NodeGuid.ToString();

/**
 * Injects this K2Node's unique GUID into a pin on an internal node.
 * NOTE: Perfect for stateful nodes that need a unique ID to track data in a Map or Singleton.
 * SECONDNOTE: it doesn't need the DECLARE_K2_GUID macro, but you can use it if you want to store the GUID in a variable for later use
 */
#define INJECT_K2NODE_GUID(NodeVar, TargetPinName) \
    { \
        FString _InternalGuid = NodeGuid.ToString(); \
        UEdGraphPin* _GPin = NodeVar->FindPin(TEXT(TargetPinName)); \
        if (_GPin) \
        { \
            _GPin->DefaultValue = _InternalGuid; \
        } \
    }

/**  
 * 3zgol? 🦜
 */
