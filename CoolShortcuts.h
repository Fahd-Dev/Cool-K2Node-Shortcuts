// Copyright (c) 2026 Fahd-Dev. Licensed under MIT.
// Library Version: UE5.7 | v0.0.2 Alpha
// Github: https://github.com/Fahd-Dev/Cool-K2Node-Shortcuts

/**
 * =========================================================================================
 * COMPATIBILITY:                                                                          |
 * This version was developed and tested on Unreal Engine 5.7                              |
 * Compatibility with other versions is likely but not guaranteed.                         |
 * =========================================================================================
 * 
 */
 
#pragma once

//==============================================================================
//  Node Declaration & Implementation Macros
//==============================================================================

/**
 * @brief Declare with implementation for a K2Node.
 * 
 * @note IMPORTANT: Use this macro in The ".h". Will not work in the ".cpp".
 * @note REQUIRES: "BlueprintActionDatabaseRegistrar.h" and "BlueprintNodeSpawner.h"
 * 
 * @warning This macro could INCREASE the compiling time, if your project have a lot 
 * of K2Nodes, consider using these macros: DECLARE_K2NODE_ONLY with IMPLEMENT_K2NODE_ONLY.
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
 * @brief Declares GetNodeTitle, GetMenuCategory, GetTooltipText, GetMenuActions Functions.
 * 
 * @note This macro doesn't do anything without implementation.
 * @note RECOMMENDATION: you can use the IMPLEMENT_K2NODE_ONLY Macro in the ".cpp".
 */
#define DECLARE_K2NODE_ONLY() \
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override; \
    virtual FText GetTooltipText() const override; \
    virtual FText GetMenuCategory() const override; \
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

/**
 * @brief Implements the GetNodeTitle, GetMenuCategory, GetTooltipText, GetMenuActions Functions.
 * 
 * @note REQUIRES: "BlueprintActionDatabaseRegistrar.h" and "BlueprintNodeSpawner.h"
 * @note IMPORTANT: You must declare these functions in the ".h".
 * @note RECOMMENDATION: you can just use the macro named DECLARE_K2NODE_ONLY in the header.
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
 * @brief Handles the 'Search' keywords so your node shows up even if the user doesn't type the exact name.
 */
#define K2NODE_KEYWORD(Keyword) \
    virtual FText GetKeywords() const override { return FText::FromString(TEXT(Keyword)); }

/** 
 * @brief A custom color for the bar on top of the node.
 * 
 * @note IMPORTANT: IN HEADER ONLY.
 * @note NOTE: You need a declared K2Node for this to work.
 */
#define K2NODE_TITLE_COLOR(R, G, B) \
    virtual FLinearColor GetNodeTitleColor() const override { \
        return FLinearColor(R, G, B); \
    }

/** 
 * @brief Make a K2Node Pure.
 * 
 * @note IMPORTANT: IN HEADER ONLY.
 * @note NOTE: You need a declared K2Node for this to work.
 */
#define MAKE_K2NODE_PURE() \
    virtual bool IsNodePure() const override { \
        return true; \
    }

/**
 * @brief Make a K2Node Compact.
 * 
 * @param CompactText The text to display inside the compact node.
 * 
 * @note IMPORTANT: IN HEADER ONLY.
 * @note NOTE: You need a declared K2Node for this to work.
 */
#define MAKE_K2NODE_COMPACT(CompactText) \
    virtual bool ShouldDrawCompact() const override { return true; } \
    virtual FText GetCompactNodeTitle() const override { return FText::FromString(CompactText); }

//==============================================================================
//  Pin Creation Macros
//==============================================================================

/** @brief Shortcut for UEdGraphSchema_K2 */
#define K2Pin UEdGraphSchema_K2

/** @brief Shortcut for UEdGraphPin */
#define GraphPin UEdGraphPin

/**
 * @brief Will add two pins: an Input exec (PN_Execute) and an Output exec (PN_Then).
 * 
 * @note RECOMMENDATION: to connect them in the ExpandNode function you can use a macro named 
 * LINK_STANDARD_EXEC_PINS it will connect them for you.
 */
#define CREATE_STANDARD_EXEC_PINS() \
    do { \
        CreatePin(EGPD_Input, K2Pin::PC_Exec, K2Pin::PN_Execute); \
        CreatePin(EGPD_Output, K2Pin::PC_Exec, K2Pin::PN_Then); \
    } while(0)

/** @brief Type Examples: UObject, UCurveFloat, AActor, etc. */
#define CREATE_OBJECT_PIN(Where, Type, PinName) \
    CreatePin(EGPD_##Where, K2Pin::PC_Object, Type::StaticClass(), PinName)

/** @brief Type Examples: FVector, FRotator, FLinearColor, etc. */
#define CREATE_STRUCT_PIN(Where, Type, PinName) \
    CreatePin(EGPD_##Where, K2Pin::PC_Struct, TBaseStructure<Type>::Get(), PinName)

/** @brief Creates a pin with two categories like, PC_Real - PC_Float */
#define CREATE_TWO_TYPE_PIN(Where, Type, Type2, PinName) \
    CreatePin(EGPD_##Where, K2Pin::Type, K2Pin::Type2, PinName)

#define CREATE_ENUM_PIN(Where, Enum, PinName) \
    CreatePin(EGPD_##Where, UEdGraphSchema_K2::PC_Byte, StaticEnum<Enum>(), PinName)

/** @brief Type Examples: PC_Boolean, PC_String, PC_NAME, etc. */
#define CREATE_PIN(Where, Type, PinName) \
    CreatePin(EGPD_##Where, K2Pin::Type, PinName)

//==============================================================================
//  Pin Manipulation Macros
//==============================================================================

/** @brief Sets the default value of a pin by name */
#define SET_PIN_DEFAULT(PinName, Value) \
    do { \
        if (GraphPin* _TargetPin = FindPin(FName(PinName))) { \
            _TargetPin->DefaultValue = LexToString(Value); \
        } \
    } while(0)

/** @brief Sets the default value of an ENUM pin by name */
#define SET_ENUM_PIN_DEFAULT(PinName, Enum, Value) \
    do { \
        if (GraphPin* _TargetPin = FindPin(FName(PinName))) { \
            if (UEnum* _EnumPtr = StaticEnum<Enum>()) { \
                _TargetPin->DefaultValue = _EnumPtr->GetNameStringByValue((int64)Value); \
            } \
        } \
    } while(0)
    
/** @brief Hides a pin if the passed bool is true */
#define HIDE_PIN_IF(PinName, Condition) \
    do { \
        if (GraphPin* _TargetPin = FindPin(FName(PinName))) { \
            _TargetPin->bHidden = (Condition); \
        } \
    } while(0)

/** @brief Hides a pin */
#define HIDE_PIN(PinName) \
    do { \
        if (GraphPin* _TargetPin = FindPin(FName(PinName))) { \
            _TargetPin->bHidden = true; \
        } \
    } while(0)

/** @brief UnHide/Show -Whatever you call it- a Pin */
#define UNHIDE_PIN(PinName) \
    do { \
        if (GraphPin* _TargetPin = FindPin(FName(PinName))) { \
            _TargetPin->bHidden = false; \
        } \
    } while(0)

/** @brief Give the pin a tooltip */
#define PIN_TOOLTIP(PinName, Tooltip) \
    do { \
        if (GraphPin* _TargetPin = FindPin(FName(PinName))) { \
            _TargetPin->PinToolTip = Tooltip; \
        } \
    } while(0)

//==============================================================================
//  Dynamic Pin Creation (User‑added)
//==============================================================================

/**
 * @brief Automatically adds a new pin to the node.
 * 
 * It counts existing pins with the same prefix to ensure the index (0, 1, 2...) is correct.
 */
#define ADD_USER_PIN(Prefix, Where, Type) \
    do { \
        Modify(); \
        int32 _CurrentCount = 0; \
        for (GraphPin* _P : Pins) { \
            if (_P->PinName.ToString().StartsWith(TEXT(Prefix))) _CurrentCount++; \
        } \
        FName _NewName = FName(*FString::Printf(TEXT(Prefix "%d"), _CurrentCount)); \
        CREATE_PIN(Where, Type, _NewName); \
        GetGraph()->NotifyGraphChanged(); \
    } while(0)

//==============================================================================
//  Node Spawning & Internal Node Helpers
//==============================================================================

/**
 * @brief Creates a "UK2Node_CallFunction*" variable named After the Value you've put in the "NodeVarName".
 * 
 * Stores the specified NodeClass and NodeFunction inside it.
 * The variable is compatible with your K2Node and accessible for further customization.
 * 
 * @note REQUIRES: You need to include "KismetCompiler.h" and "K2Node_CallFunction.h" for this to work.
 */
#define ADD_INTERNAL_NODE(NodeVarName, NodeClass, NodeFunction) \
    UK2Node_CallFunction* NodeVarName = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph); \
    NodeVarName->SetFromFunction(NodeClass::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(NodeClass, NodeFunction))); \
    NodeVarName->AllocateDefaultPins();

/** 
 * @brief Spawns an internal Async Action node. 
 * 
 * This is required if you want to use the Delegate pins.
 * 
 * @note REQUIRES: #include "K2Node_AsyncAction.h"
 */
#define ADD_INTERNAL_ASYNC_NODE(NodeVarName, NodeClass, NodeFunction) \
    UK2Node_AsyncAction* NodeVarName = CompilerContext.SpawnIntermediateNode<UK2Node_AsyncAction>(this, SourceGraph); \
    do { \
        struct FAsyncAccess : public UK2Node_AsyncAction { \
            static void Set(UK2Node_AsyncAction* InNode, FName InFunc, UClass* InClass) { \
                FAsyncAccess* Me = static_cast<FAsyncAccess*>(InNode); \
                Me->ProxyFactoryFunctionName = InFunc; \
                Me->ProxyFactoryClass = InClass; \
                Me->ProxyClass = InClass; \
            } \
        }; \
        FAsyncAccess::Set(NodeVarName, GET_FUNCTION_NAME_CHECKED(NodeClass, NodeFunction), NodeClass::StaticClass()); \
    } while(0); \
    NodeVarName->AllocateDefaultPins();

/** 
 * @brief Spawns a visible node in the blueprint graph 
 * @note Use in "PostPlacedNewNode"
 */
#define ADD_VISIBLE_NODE(NodeClass, NodeVarName, OffsetX, OffsetY) \
    NodeClass* NodeVarName = NewObject<NodeClass>(GetGraph()); \
    NodeVarName->NodePosX = OffsetX; \
    NodeVarName->NodePosY = OffsetY; \
    NodeVarName->AllocateDefaultPins(); \
    GetGraph()->AddNode(NodeVarName, true, true);

/** 
 * @brief Spawns a visible CallFunction node at specific coordinates.
 * @note Use in "PostPlacedNewNode"
 */
#define ADD_VISIBLE_FUNC_NODE(NodeClass, NodeVarName, NodeFunction, OffsetX, OffsetY) \
    UK2Node_CallFunction* NodeVarName = NewObject<UK2Node_CallFunction>(GetGraph()); \
    NodeVarName->NodePosX = OffsetX; \
    NodeVarName->NodePosY = OffsetY; \
    if (UFunction* _Func = NodeClass::StaticClass()->FindFunctionByName(GET_FUNCTION_NAME_CHECKED(NodeClass, NodeFunction))) { \
        NodeVarName->SetFromFunction(_Func); \
    } \
    NodeVarName->AllocateDefaultPins(); \
    NodeVarName->ReconstructNode(); \
    GetGraph()->AddNode(NodeVarName, true, true);

/**
 * @brief Deletes the spawner node
 * @note Use In "PostPlacedNewNode"
 */
#define DELETE_SPAWNER_NODE() \
    do { \
        TWeakObjectPtr<UEdGraphNode> WeakThis(this); \
        UBlueprint* BP = GetBlueprint(); \
        if (!BP) break; \
        TWeakObjectPtr<UBlueprint> WeakBP(BP); \
        AsyncTask(ENamedThreads::GameThread, [WeakThis, WeakBP]() { \
            if (WeakThis.IsValid() && WeakBP.IsValid()) { \
                UEdGraphNode* Node = WeakThis.Get(); \
                UBlueprint* Blueprint = WeakBP.Get(); \
                if (Node && Node->GetGraph()) { \
                    FBlueprintEditorUtils::RemoveNode(Blueprint, Node, true); \
                    FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint); \
                } \
            } \
        }); \
    } while(0)

//==============================================================================
//  Linking & Compiler Helpers
//==============================================================================

/**
 * @brief This will connect the PN_Execute & PN_Then Execs With the node in the Variable named after the "NodeName" Variable.
 * 
 * @note RECOMMENDATION: you can use the CREATE_STANDARD_EXEC_PINS Macro in the "AllocateDefaultPins" Function, and it will work with this macro.
 */
#define LINK_STANDARD_EXEC_PINS(NodeVar) \
    do { \
        GraphPin* _ExecIn = FindPin(K2Pin::PN_Execute); \
        GraphPin* _ExecOut = FindPin(K2Pin::PN_Then); \
        GraphPin* _CallExecIn = NodeVar->FindPin(K2Pin::PN_Execute); \
        GraphPin* _CallExecOut = NodeVar->FindPin(K2Pin::PN_Then); \
        if (_ExecIn && _CallExecIn) { \
            CompilerContext.MovePinLinksToIntermediate(*_ExecIn, *_CallExecIn); \
        } \
        if (_ExecOut && _CallExecOut) { \
            CompilerContext.MovePinLinksToIntermediate(*_ExecOut, *_CallExecOut); \
        } \
    } while(0)

/** @brief Links the return values from the K2Node with the Internal Node */
#define LINK_RETURN_VALUES(NodeVar) \
    do { \
        GraphPin* _InputPin = FindPin(K2Pin::PN_ReturnValue); \
        GraphPin* _TargetPin = NodeVar->FindPin(K2Pin::PN_ReturnValue); \
        if (_InputPin && _TargetPin) { \
            CompilerContext.MovePinLinksToIntermediate(*_InputPin, *_TargetPin); \
        } \
    } while(0)

#define MOVE_LINK(NodeVar, K2NodePin, InternalPin) \
    do { \
        GraphPin* _InputPin = FindPin(FName(K2NodePin)); \
        GraphPin* _TargetPin = NodeVar->FindPin(FName(InternalPin)); \
        if (_InputPin && _TargetPin) { \
            CompilerContext.MovePinLinksToIntermediate(*_InputPin, *_TargetPin); \
        } \
    } while(0)

#define COPY_LINK(NodeVar, K2NodePin, InternalPin) \
    do { \
        GraphPin* _InputPin = FindPin(FName(K2NodePin)); \
        GraphPin* _TargetPin = NodeVar->FindPin(FName(InternalPin)); \
        if (_InputPin && _TargetPin) { \
            CompilerContext.CopyPinLinksToIntermediate(*_InputPin, *_TargetPin); \
        } \
    } while(0)

#define BREAK_LINK(Pin) \
    do { \
        if (GraphPin* _TargetPin = FindPin(Pin)) { \
            if (const K2Pin* Schema = CompilerContext.GetSchema()) { \
                Schema->BreakPinLinks(*_TargetPin, true); \
            } \
        } \
    } while(0)

/**
 * @brief Links a pin from an internal node to another pin from an internal node.
 */
#define LINK_INTERNAL_PIN(NodeA, PinA, NodeB, PinB) \
    do { \
        GraphPin* _PA = NodeA->FindPin(FName(PinA)); \
        GraphPin* _PB = NodeB->FindPin(FName(PinB)); \
        if (_PA && _PB) GetSchema()->TryCreateConnection(_PA, _PB); \
    } while(0)

#define BREAK_INTERNAL_LINK(Pin) \
    do { \
        GraphPin* _PA = NodeA->FindPin(FName(PinA)); \
        if (_PA && _PB) GetSchema()->TryCreateConnection(_PA, _PB); \
    } while(0)

/**
 * @brief Links the pins the user creates with "AddInputPin()" to an Array input on an internal node.
 * 
 * @note REQUIRES: "K2Node_MakeArray.h"
 */
#define LINK_USER_PINS(InternalNode, TargetPin, Prefix) \
    do { \
        UK2Node_MakeArray* _TmpArr = CompilerContext.SpawnIntermediateNode<UK2Node_MakeArray>(this, SourceGraph); \
        _TmpArr->AllocateDefaultPins(); \
        int32 _Idx = 0; \
        for (UEdGraphPin* _Pin : Pins) { \
            if (_Pin->PinName.ToString().StartsWith(FString(Prefix))) { \
                if (_Idx > 0) _TmpArr->AddInputPin(); \
                UEdGraphPin* _ArrIn = _TmpArr->FindPinChecked(*FString::Printf(TEXT("[%d]"), _Idx)); \
                if (_Pin && _ArrIn) CompilerContext.MovePinLinksToIntermediate(*_Pin, *_ArrIn); \
                _Idx++; \
            } \
        } \
        if (UEdGraphPin* _OutArr = _TmpArr->GetOutputPin()) { \
            GetSchema()->TryCreateConnection(_OutArr, InternalNode->FindPinChecked(FName(TargetPin))); \
        } \
    } while(0)

//==============================================================================
//  GUID Utilities
//==============================================================================

/** @brief Gets & Declare the K2Node GUID and convert it to a string */
#define GET_K2NODE_GUID(GUID_VarName) \
    FString GUID_VarName = NodeGuid.ToString();

/**
 * @brief Injects this K2Node's unique GUID into a pin on an internal node.
 * 
 * @note NOTE: Perfect for stateful nodes that need a unique ID to track data in a Map or Singleton.
 * @note SECOND-NOTE: it doesn't need the DECLARE_K2_GUID macro, but you can use it if you want to store the GUID in a variable for later use.
 */
#define INJECT_K2NODE_GUID(NodeVar, TargetPinName) \
    do { \
        FString _InternalGuid = NodeGuid.ToString(); \
        UEdGraphPin* _GPin = NodeVar->FindPin(FName(TargetPinName)); \
        if (_GPin) { \
            _GPin->DefaultValue = _InternalGuid; \
        } \
    } while(0)

// bye bye parrot ):