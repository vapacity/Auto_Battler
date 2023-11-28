## 11.27—12.3（待更新）

### 本周任务:

自学ue4的C++用法，b站、官方文档

阅读项目代码（抄的b站top1视频源码，含有自动寻路代码，可结合视频学习）

代码阅读顺序：GridNode.h -> GridNode.cpp -> HexNode.h -> HexNode.cpp -> GridMap.h -> GridMap.cpp

## UE中的基类字母表示

A（Actor）: 表示继承自 AActor 类的类，通常用于表示在场景中的物体或角色。
U（Object）: 表示继承自 UObject 类的类，用于表示 Unreal Engine 中的对象。
F（Struct）: 表示一个结构体，用于组织和存储数据，而不包含行为。
E（Enum）: 表示一个枚举类型，用于定义一组命名的整数值。
I（Interface）: 表示一个接口，用于定义一组抽象的方法，可以被其他类实现。
G（Global）: 表示全局变量或单例模式中的全局实例。
S（Widget）: 在 Unreal Engine 中，用于表示用户界面的 Slate Widget。
T（Template）: 表示模板类或模板函数，允许编写通用的代码。



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



### GridNode::DrawNode参数解释：

- `TArray<FVector>& InVertices`：顶点数组，描述节点的三维空间位置。
- `TArray<int32>& InIndices`：索引数组，定义顶点之间的连接关系，用于构建节点的三角形网格。
- `TArray<FVector>& InNormals`：法线数组，描述节点表面的法线方向，用于光照计算。
- `TArray<FVector2D>& InUV`：UV 数组，表示节点表面上每个顶点的二维纹理坐标。
- `TArray<FColor>& InVertexColors`：顶点颜色数组，定义节点各个顶点的颜色信息。
- `TArray<FVector>& InTangents`：切线数组，描述节点表面的切线方向，通常与法线一起用于光照计算。
- `FVector InOffset`：偏移向量，用于对节点进行位置调整。

### TArray

#### 一，TArray 的创建、初始化、赋值

TArray 的创建、初始化、赋值的主要形式如下。其中，列表既可以用作构造函数的参数，也可以用来初始化和赋值。Init() 可以在TArray 在放置若干个相同元素。

```cpp
TArray<FString> Arr;
//Arr is []

TArray<FString> SecArr({ TEXT("Are"), TEXT("you"), TEXT("OK") });
//SecArr is [Are you OK]

TArray<FString> ThirdArr = { TEXT("Are"), TEXT("you"), TEXT("OK") };
//ThirdArr is [Are you OK]

ThirdArr.Init(TEXT("Hello"), 3);
//ThirdArr is [Hello Hello Hello]

Arr = { TEXT("Hello"), TEXT("World") };
//Arr is [Hello World]
```

#### 二，TArray 的元素添加

###### 添加单个元素

向TArray 中添加单个元素，有很多中方法：Add、Push、Emplace、AddUnique、Insert。在具体使用上，它们也有一些差别，归纳如下：

1. 前四种是在数组尾部追加元素，Insert 可在数组的任意位置插入元素；
2. Add 和 Push类似，但是将元素复制或移动到数组中，而Emplace 则使用给定参数构建元素类型的新实例；通常来说，Emplace 的效率高于Add；
3. 如果不存在相同元素（用运算符=判断），AddUnique 才会向数组中添加元素。

各个函数的使用方式如下：

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK") };
Arr.Add(TEXT(","));
//Arr is [Are you OK ,]

Arr.Push(TEXT("Hello"));
//Arr is [Are you OK , Hello]

Arr.Emplace(TEXT("World"));
//Arr is [Are you OK , Hello World]

Arr.AddUnique(TEXT(","));
//Arr is [Are you OK , Hello World]
Arr.AddUnique(TEXT("I"));
//Arr is [Are you OK , Hello World I]

Arr.Insert(TEXT("Head"), 0);
//Arr is [Head Are you OK , Hello World I]
```

###### 添加多个元素

向数组中添加多个元素，可采用Append() 方法或 += 操作符完成，使用方法如下：

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK") };

TArray<FString> SecArr({ TEXT("How"), TEXT("Do"), TEXT("You") });
Arr.Append(SecArr);
//Arr is [Are you OK How Do You]

TArray<FString> ThirdArr({ TEXT("I"), TEXT("Am"), TEXT("Fine") });
Arr += ThirdArr;
//Arr is [Are you OK How Do You I Am Fine]
```

#### 三，TArray 的三种遍历

TArray 的遍历一共有三种形式：范围for 循环、索引、迭代器，这一点上和vector 类似。下面展示了这几种遍历的使用方法。

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK") };

for (auto& s : Arr)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
}

for (int i = 0; i < Arr.Num(); i++)
{
	UE_LOG(LogTemp, Warning, TEXT("%d: %s"), i, *Arr[i]);
}

for (auto It = Arr.CreateIterator(); It; ++It)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(*It));
}
```

#### 四，TArray 的三种排序

TArry的排序方法也有三种：Sort、HeapSort、StableSort。他们的简单使用方法如下：

```cpp
Arr.Sort();
Arr.HeapSort();
Arr.StableSort();
```

三者并不相同，存在如下差异：

1. Sort 基于快速排序，是不稳定的排序；
2. HeapSort 基于堆排序，是不稳定的排序；
3. StableSort 基于归并排序，是稳定的排序。

默认情况下，上述三种排序方法都是使用元素类型的 < 运算符进行排序。我们可以使用lambda 自定义排序规则，如下，我们根据字符串长度对FString 排序。

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK") ,TEXT("Hello"), TEXT("World") };

Arr.StableSort(
	[](const FString& A, const FString& B) {return A.Len() < B.Len(); }
);
//Arr is [OK Are you Hello World]
```

#### 五，TArray 的元素删除

删除元素的方法比较多，有Remove()、RemoveSingle()、RemoveAll()、RemoveAt()、Empty()。总结下来，它们的用法如下：

1. Remove(Str)： 删除数组中所有与 Str 相同的元素，是否相同用 == 运算符判断；
2. RemoveSingle(Str)：删除数组中第一个与 Str 相同的元素，是否相同用 == 运算符判断；
3. RemoveAll(lambda)：删除数组中的多个元素，删除规则由lambda 表达式指定；
4. RemoveAt(i)：删除数组中索引为 i 的元素；
5. Empty()：并不是判断数组为空，而是清空所有元素；
6. Remove(Str) 与 RemoveSingle(Str) 的区别在于是删除单个元素，还是所有元素；
7. Remove(Str) 与 RemoveAll(lambda) 的区别在于删除规则的不同。

代码演示如下：

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
Arr.Remove(TEXT("OK"));
//Arr is [Are you]

Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
Arr.RemoveSingle(TEXT("OK"));
//Arr is [Are you OK]

Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
Arr.RemoveAll([](const FString& Str) {return Str.Len() == 2; });
//Arr is [Are you]

Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
Arr.RemoveAt(0);
//Arr is [you OK OK]

Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
Arr.Empty();
//Arr is []
```

#### 六，TArray 的查询

###### 根据索引获取元素对象的引用：[] 运算符、Last()、Top()

使用 [] 运算符、Last()、Top()都可以根据索引获取数组中的元素，并且获取的都是元素的引用，也就是说我们可以直接修改数组中的元素。如下代码所示，执行 Arr[0] = Arr[1] 之后，第 0 个元素的值也变成第 1 个元素的了；执行 Arr.Top() = Arr[1] 之后，最后一个元素的值也变成第 1 个元素的了。这三个方法的联系与区别如下：

1. Arr[i] 获取的是顺数第 i 个元素；
2. Last(i) 获取的是倒数第 i 个元素 ；
3. Top() 不能带参数，实际效果完全和 Last()一样。

三个方法的具体用法如下：

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK") ,TEXT("Hello"), TEXT("World") };
Arr[0] = Arr[1];
// Arr is [you you OK Hello World]

UE_LOG(LogTemp, Warning, TEXT("%s"), *Arr.Last());	//Output: World
UE_LOG(LogTemp, Warning, TEXT("%s"), *Arr.Last(1));	//Output: Hello
UE_LOG(LogTemp, Warning, TEXT("%s"), *Arr.Top());	//Output: World

Arr.Top() = Arr[1];
// Arr [you you OK Hello you]
```

###### 判断元素是否存在：Contains()、ContainsByPredicate()

判断数组中是否存在某元素，使用的方法是Contains() 及其变体ContainsByPredicate()。ContainsByPredicate() 允许使用一元谓词指定判断规则。具体用法如下：

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK") ,TEXT("Hello"), TEXT("World") };
bool bExist = Arr.Contains(TEXT("Are"));
bool bContain = Arr.ContainsByPredicate(
	[](const FString& Str) {return Str.Len() == 3; }
);
```

###### 查找元素所在的索引：Find()、FindLast()、IndexOfByKey()、IndexOfByPredicate()

查找元素所在的索引，使用的方法是Find()、FindLast()、IndexOfByKey()、IndexOfByPredicate()。如果查找成功，则返回元素所在的索引；查找失败，则返回 INDEX_NONE（值为-1的宏）。他们的用法总结如下：

1. Find(Str)：返回数组中第一个与 Str 相同的元素的索引，是否相同用 == 运算符判断；
2. FindLast(Str)：返回数组中最后一个与 Str 相同的元素的索引，是否相同用 == 运算符判断；
3. IndexOfByKey(Str)：与 Find(Str) 一样；
4. IndexOfByPredicate(lambda)：IndexOfByKey 的lambda 版，用lambda 表达式来指定查找元素的规则。

代码示例如下：

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
int Index = Arr.Find(TEXT("OK"));
//Index is 2

Index = Arr.Find(TEXT("I"));
//Index is INDEX_NONE

Index = Arr.FindLast(TEXT("OK"));
//Index is 3

Index = Arr.IndexOfByKey(TEXT("OK"));
//Index is 2

Index = Arr.IndexOfByPredicate([](const FString& Str) {return Str.Len() == 3; });
//Index is 0
```

###### 查找元素对象：FindByKey()、FindByPredicate()、FilterByPredicate()

FindByKey()、FindByPredicate()、FilterByPredicate() 可用来获取数组中的元素对象。FindByKey()、FindByPredicate() 获取的都是指向元素的指针，FilterByPredicate() 获取的是所有符合条件的元素，用法总结如下：

1. FindByKey(Str)：获取数组中第一个与 Str 相同的元素的指针，获取失败返回nullptr；
2. FindByPredicate(lambda)：FindByKey 的lambda 版，用lambda 表达式来指定查找元素的规则；
3. FilterByPredicate(lambda)：获取数组中所有使lambda 表达式为true 的元素，但这些元素都是拷贝，返回一个数组。

```cpp
TArray<FString> Arr = { TEXT("Are"), TEXT("you"), TEXT("OK"), TEXT("OK") };
FString* StrPtr = Arr.FindByKey(TEXT("OK"));
//StrPtr 是一个指向字符串"OK"的指针

StrPtr = Arr.FindByPredicate([](const FString& Str) {return Str.Len() == 3; });
//StrPtr 是一个指向字符串"Are"的指针

TArray<FString> StrArr = Arr.FilterByPredicate([](const FString& Str) {return Str.Len() == 3; });
//StrArr is [Are you]
```



### UMeshComponent

 是 Unreal Engine 中用于表示和管理静态或动态网格的基类。具体的方法和功能可能会依赖于特定的 `UMeshComponent` 子类，例如 `UStaticMeshComponent` 或 `USkeletalMeshComponent`。以下是一些 `UMeshComponent` 常见的方法，注意具体的子类可能还包括其他特定于其类型的方法：

1. **`SetMaterial`**：

   ```cpp
   cppCopy code
   void UMeshComponent::SetMaterial(int32 ElementIndex, UMaterialInterface* Material);
   ```

   用于设置组件上指定索引处的材质。

2. **`SetMaterialByName`**：

   ```cpp
   cppCopy code
   void UMeshComponent::SetMaterialByName(FName MaterialSlotName, UMaterialInterface* Material);
   ```

   根据材质槽名称设置材质。

3. **`SetScalarParameterValueOnMaterials`**：

   ```cpp
   cppCopy code
   void UMeshComponent::SetScalarParameterValueOnMaterials(FName ParameterName, float ParameterValue);
   ```

   在关联的材质上设置标量参数的值。

4. **`SetVectorParameterValueOnMaterials`**：

   ```cpp
   cppCopy code
   void UMeshComponent::SetVectorParameterValueOnMaterials(FName ParameterName, FLinearColor ParameterValue);
   ```

   在关联的材质上设置向量参数的值。

5. **`GetMaterials`**：

   ```cpp
   cppCopy code
   TArray<UMaterialInterface*> UMeshComponent::GetMaterials();
   ```

   返回组件上所有的材质。

6. **`SetCastShadow`**：

   ```cpp
   cppCopy code
   void UMeshComponent::SetCastShadow(bool bNewCastShadow);
   ```

   设置组件是否投射阴影。

7. **`OnComponentHit`**：

   ```cpp
   cppCopy codevoid UMeshComponent::OnComponentHit(
       UPrimitiveComponent* HitComponent,
       AActor* OtherActor,
       UPrimitiveComponent* OtherComp,
       FVector NormalImpulse,
       const FHitResult& Hit);
   ```

   当组件被击中时触发的事件。

8. **`OnComponentBeginOverlap`**：

   ```cpp
   cppCopy codevoid UMeshComponent::OnComponentBeginOverlap(
       UPrimitiveComponent* OverlappedComponent,
       AActor* OtherActor,
       UPrimitiveComponent* OtherComp,
       int32 OtherBodyIndex,
       bool bFromSweep,
       const FHitResult& SweepResult);
   ```

   当组件开始与其他组件重叠时触发的事件。

9. **`OnComponentEndOverlap`**：

   ```cpp
   cppCopy codevoid UMeshComponent::OnComponentEndOverlap(
       UPrimitiveComponent* OverlappedComponent,
       AActor* OtherActor,
       UPrimitiveComponent* OtherComp,
       int32 OtherBodyIndex);
   ```

   当组件结束与其他组件的重叠时触发的事件。

10. **`CreateDynamicMaterialInstance`**：

```cpp
cppCopy code
UMaterialInstanceDynamic* UMeshComponent::CreateDynamicMaterialInstance(int32 ElementIndex, UMaterialInterface* SourceMaterial);
```

在运行时创建一个动态材质实例。