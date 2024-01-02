# Auto_Battler
同济大学2022级软件工程程序设计范式期末项目

#### 项目分工

张文健（组长）：棋子类与玩家类的设计实现，备战场景与对战场景设计与实现

樊佳欣：游戏素材整合，多场景界面UI设计，棋子类技能实现，整体代码修缮，用户交互体验改善

岳叶晋川：商店类的设计实现，棋子数值设计

徐嘉豪：棋盘类与备战席类的设计实现（包含寻路算法），AI玩家对战策略的设计实现

何升阳：小小英雄类的设计实现，联机功的设计实现



#### 功能实现情况

基础功能：

- [x] 有初始界⾯和设置界⾯
- [x] ⽀持背景⾳效
- [x] ⽀持多种类型的卡牌
- [x] ⽀持卡牌升级功能
- [x] ⽀持⼩⼩英雄的移动
- [x] 场上卡牌⽀持红蓝⾎条，蓝条满时可以释放技能。
- [x] ⽀持创建房间和加⼊房间的功能
- [x] ⽀持练习模式，玩家可以和2个AI玩家对弈。
- [x] ⽀持联机模式，玩家可以和2个⼈类玩家联机对弈。

进阶功能：

- [x] 支持十种卡牌，其中5种具有进化后的不同形态。每种卡牌都有独特数值和技能。
- [x] 支持卡牌刷新和商店升级。商店卡牌出现概率随商店等级改变。
- [x] 支持对战音效。
- [x] 支持卡牌自动寻路与自动对战。

C++特性：

- [x] 抛出和捕获异常
- [x] Lambda表达式
- [x] STL容器
- [x] 迭代器
- [x] 类和多态



#### 类与继承关系图

![image-20240102220232672](C:\Users\vapacity\AppData\Roaming\Typora\typora-user-images\image-20240102220232672.png)



#### 棋子数值设计

![image-20240102220304654](C:\Users\vapacity\AppData\Roaming\Typora\typora-user-images\image-20240102220304654.png)

#### 项目亮点

##### 良好的交互体验

棋格高亮显示

![棋格高亮演示](C:\Users\vapacity\Downloads\演示gif\棋格高亮演示.gif)

棋子放置问题

![棋子放置、交换演示](C:\Users\vapacity\Downloads\演示gif\棋子放置、交换演示.gif)

![非法放置位置演示](C:\Users\vapacity\Downloads\演示gif\非法放置位置演示.gif)

用户提示

![缺钱演示](C:\Users\vapacity\Downloads\演示gif\缺钱演示.gif)

![满级演示](C:\Users\vapacity\Downloads\演示gif\满级演示.gif)



##### 有趣设计

卡牌捕获失败

![image-20240102220536870](C:\Users\vapacity\AppData\Roaming\Typora\typora-user-images\image-20240102220536870.png)

棋子进化有不同形态

皮丘进化为皮卡丘

![特殊进化1](C:\Users\vapacity\Downloads\演示gif\特殊进化1.gif)

皮卡丘进化为雷丘

![特殊进化2](C:\Users\vapacity\Downloads\演示gif\特殊进化2.gif)

##### 游戏还原度高

投掷物抵达目标后才扣血

![攻击与受伤演示](D:\Program Files (x86)\wechat files\WeChat Files\wxid_zm6p1oxxk8ms22\FileStorage\File\2024-01\攻击与受伤演示.gif)

近远程棋子

![对战演示](D:\Program Files (x86)\wechat files\WeChat Files\wxid_zm6p1oxxk8ms22\FileStorage\File\2024-01\对战演示.gif)
