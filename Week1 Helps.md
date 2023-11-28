## 11.27—12.3（待更新）

### 本周任务:

自学ue4的C++用法，b站、官方文档

阅读项目代码（抄的b站top1视频源码，含有自动寻路代码，可结合视频学习）

代码阅读顺序：GridNode.h -> GridNode.cpp -> HexNode.h -> HexNode.cpp -> GridMap.h -> GridMap.cpp

### UCLASS

`UCLASS` 是 Unreal Engine 4 (UE4) 中的一个宏，用于声明一个类，并为其添加一些元信息，以便 UE4 能够正确地处理和管理这个类。它通常用于声明蓝图可用的类、Actor 类、GameMode 类等。

基本的使用方式如下：

```C++
cppCopy codeUCLASS()
class YOURGAME_API AYourClass : public AActor
{
    GENERATED_BODY()

public:
    // 类的声明部分
};
```

这里是一些 `UCLASS` 宏的常见参数和用法：

- **Class Group（类组）：** `UCLASS(ClassGroup="Custom", meta=(BlueprintSpawnableComponent))`
  - `ClassGroup` 参数允许你将类分组，这在编辑器中有时用于更好的组织类。
- **Abstract Class（抽象类）：** `UCLASS(Abstract, meta=(BlueprintSpawnableComponent))`
  - `Abstract` 参数用于声明一个抽象类，即不能直接实例化的类。通常用于作为基类。
- **Blueprint Spawnable（可在蓝图中生成）：** `UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))`
  - `Blueprintable` 参数允许你将类实例化为蓝图。这在创建蓝图类时非常有用。
- **Not Placeable（不可放置）：** `UCLASS(meta=(IsBlueprintBase = "false"))`
  - `IsBlueprintBase` 参数指定类是否可以直接放置在场景中。如果设置为 `false`，则类不能被直接放置，但仍可用于派生其他类。
- **EditInlineNew（内联编辑新对象）：** `UCLASS(EditInlineNew, meta=(BlueprintSpawnableComponent))`
  - `EditInlineNew` 参数指示可以在编辑器中直接在属性窗口内创建新对象。
- **Class Within（类所在）：** `UCLASS(ClassGroup=YourGroup, ClassWithin=YourParentClass::StaticClass())`
  - `ClassWithin` 参数用于指定类所在的上下文，有时用于更好的组织类。

### UPROPERTY

`UPROPERTY` 是 Unreal Engine 4 (UE4) 中的一个宏，用于声明类的属性（成员变量）。使用 `UPROPERTY` 宏可确保 UE4 引擎正确处理和管理这些属性，并允许在编辑器中进行设置。

以下是一个基本的 `UPROPERTY` 的使用示例：

```C++
cppCopy codeUCLASS()
class YOURGAME_API AYourClass : public AActor
{
    GENERATED_BODY()

public:
    // 声明一个 UPROPERTY，这里是一个浮点数属性
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YourCategory")
    float YourFloatProperty;

    // 类的其他成员和函数声明
};
```

在这个示例中，`YourFloatProperty` 是一个浮点数类型的属性，通过 `UPROPERTY` 宏进行声明。这个属性具有以下标识符：

- **`EditAnywhere`：** 表示该属性可以在编辑器中的任何地方进行编辑。这使得在编辑器中设置这个属性的值成为可能。
- **`BlueprintReadWrite`：** 表示这个属性可以在蓝图中进行读写。这是允许在蓝图中使用这个属性的关键。
- **`Category`：** 表示在编辑器中将这个属性放置在指定的分类下，以更好地组织属性。

`UPROPERTY` 宏可以接受多个标识符，每个标识符都表示不同的属性设置。常见的标识符包括：

- **`EditAnywhere`：** 允许在编辑器中编辑属性。
- **`BlueprintReadOnly` 和 `BlueprintReadWrite`：** 允许在蓝图中进行只读或读写。
- **`VisibleAnywhere` 和 `VisibleDefaultsOnly`：** 控制属性在编辑器中的可见性。
- **`Category`：** 将属性放置在指定的分类下。

这些标识符允许你更精确地定义属性在编辑器和蓝图中的行为。`UPROPERTY` 的使用是 UE4 中类定义的重要组成部分，用于定义类的外部可访问的成员变量。

### UENUM

`UENUM` 是 Unreal Engine 4 (UE4) 中的一个宏，用于声明枚举类型。它允许你在 UE4 的蓝图和代码中创建自定义的枚举类型，以便更方便地使用一组相关的命名常数。

以下是一个基本的 `UENUM` 的使用示例：

```C++
cppCopy codeUENUM(BlueprintType)
enum class EYourEnum : uint8
{
    Value1,
    Value2,
    Value3 UMETA(DisplayName = "Custom Display Name"),
    // ... 可以继续添加更多的枚举值
};
```

在这个示例中：

- `EYourEnum` 是枚举的名称。
- `uint8` 是底层存储类型，指定了枚举值的底层存储类型（可以是 `uint8`、`int32` 等）。
- `Value1`、`Value2` 和 `Value3` 是枚举类型的具体值。`Value3` 的声明演示了如何给枚举值添加自定义的显示名称。
- `UMETA(DisplayName = "Custom Display Name")` 允许你为枚举值设置自定义的显示名称。在蓝图中使用这个枚举时，显示名称将更具描述性。
- `BlueprintType` 允许该枚举在蓝图中使用。

在蓝图或代码中，你可以像下面这样使用这个枚举：

```C++
cppCopy code
EYourEnum MyEnumValue = EYourEnum::Value1;
```

或者在蓝图中，你可以使用这个枚举类型创建一个变量，并在蓝图中设置其值。

`UENUM` 的使用使得在代码和蓝图之间更容易共享和理解枚举类型。

### PrimaryActorTick

在 Unreal Engine 4 (UE4) 中，`PrimaryActorTick` 是一个用于管理和配置 Actor 主时钟的结构体。这结构体是 `FTickFunction` 类型的一个成员，用于指定 Actor 的主时钟（Primary Tick）的相关属性和行为。

`PrimaryActorTick` 结构体通常用于在 Actor 类中设置主时钟的 Tick 相关属性，例如 Tick 间隔、是否启用 Tick、Tick 优先级等。

以下是一个简单的示例，展示了如何在 Actor 类中使用 `PrimaryActorTick`：

```C++
cppCopy code#include "GameFramework/Actor.h"

class AMyActor : public AActor
{
    GENERATED_BODY()

public:
    // 构造函数
    AMyActor()
    {
        // 配置主时钟的 Tick 间隔为 0.5 秒
        PrimaryActorTick.TickInterval = 0.5f;

        // 启用主时钟 Tick
        PrimaryActorTick.bCanEverTick = true;
    }

    // 主时钟 Tick 函数
    virtual void Tick(float DeltaTime) override
    {
        Super::Tick(DeltaTime);

        // 在这里处理主时钟每帧的逻辑
    }
};
```

在这个例子中，`PrimaryActorTick` 结构体被用于设置 Actor 的主时钟的 Tick 间隔，并启用了主时钟的 Tick 功能。`Tick` 函数被覆盖，以处理主时钟每帧的逻辑。

`PrimaryActorTick` 结构体的其他属性还包括 `StartWithTickEnabled`（设置 Actor 创建时是否启用 Tick）和 `TickGroup`（定义 Actor 在哪个 Tick 组中执行）等。这些属性允许你更精确地配置 Actor 的 Tick 行为。

### Super

`Super` 是一个关键字，用于在派生类中调用其基类（父类）的成员函数或属性。在面向对象编程中，`super` 或 `base` 关键字通常用于引用基类的成员，以便在派生类中重用基类的功能。

在 Unreal Engine 4 (UE4) 中，`Super` 主要用于蓝图编程和 C++ 编程中的派生类中。以下是一些常见用法：

### 在 C++ 中调用基类的成员函数：

```
cppCopy codeclass AMyActor : public AActor
{
public:
    virtual void BeginPlay() override
    {
        // 调用基类 AActor 的 BeginPlay 函数
        Super::BeginPlay();

        // 在这里添加派生类自己的初始化逻辑
    }
};
```

在这个例子中，`AMyActor` 是一个派生自 `AActor` 的类。在 `BeginPlay` 函数中，通过 `Super::BeginPlay()` 调用了基类 `AActor` 的 `BeginPlay` 函数，以确保基类的初始化逻辑被正确执行。

#### 在蓝图中调用基类的事件或函数：

在蓝图中，你可以使用 `Call Parent Function` 节点来调用父类的函数或事件。这是通过连接到基类节点并选择要调用的函数来完成的。

总体而言，`Super` 在 UE4 中用于确保在派生类中正确地调用基类的成员。这是一种重要的模式，以确保代码的正确性和可维护性。



### 生成六边形棋格 图解

![image-20231127201510339](C:\Users\vapacity\AppData\Roaming\Typora\typora-user-images\image-20231127201510339.png)

### CAST

在 Unreal Engine 4 (UE4) 中，`Cast` 是一个用于进行类型转换的函数。它允许你将一个指向某个类实例的指针或引用转换为另一个类的指针或引用。这种类型转换是安全的，因为它会在运行时检查对象的实际类型，并确保转换是有效的。

基本的使用方式如下：

```C++
cppCopy code#include "YourClass.h"

// 将指针或引用从一个类转换为另一个类
AYourClass* YourClassInstance = Cast<AYourClass>(SomeOtherClassInstance);
```

其中：

- `AYourClass` 是你要转换到的类的类型。
- `SomeOtherClassInstance` 是要转换的实例的指针或引用。

`Cast` 函数返回转换后的指针或引用，如果转换失败（即实际类型不是目标类型或者目标类型不是源类型的子类），则返回 `nullptr`。

以下是一个示例，演示了如何使用 `Cast` 进行类型转换：

```C++
cppCopy code#include "MyActor.h"
#include "MyCharacter.h"

void ExampleFunction(AActor* ActorInstance)
{
    // 将 Actor 转换为 MyCharacter 类型
    AMyCharacter* CharacterInstance = Cast<AMyCharacter>(ActorInstance);

    if (CharacterInstance)
    {
        // 转换成功，可以在这里使用 CharacterInstance
        // ...
    }
    else
    {
        // 转换失败，ActorInstance 不是 MyCharacter 类型
        // ...
    }
}
```

这个示例中，`ActorInstance` 是一个指向 `AActor` 类实例的指针。通过使用 `Cast<AMyCharacter>(ActorInstance)`，我们尝试将其转换为 `AMyCharacter` 类型。如果转换成功，`CharacterInstance` 将是一个有效的指针，可以在代码中使用。如果转换失败，`CharacterInstance` 将是 `nullptr`，你可以据此进行相应的处理。