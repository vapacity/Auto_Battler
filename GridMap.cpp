// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMap.h"
#include "HexNode.h"

//构造函数
AGridMap::AGridMap()
{
	PrimaryActorTick.bCanEverTick = true;
}

//游戏第一帧调用
void AGridMap::BeginPlay()
{
	Super::BeginPlay();
	//重新生成棋盘
	GenerateGridMap();
}

//初始化属性时调用
void AGridMap::PostInitProperties()
{
	Super::PostInitProperties();
	GenerateGridMap();
}

#if WITH_EDITOR
//编辑器中改变属性时调用
void AGridMap::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	//当行、列、大小改变时重新生成棋盘
	if (PropertyChangedEvent.Property->GetName() == "Roll"
		|| PropertyChangedEvent.Property->GetName() == "Colume"
		|| PropertyChangedEvent.Property->GetName() == "Size")
	{
		//重新生成棋盘
		GenerateGridMap();
	}

}
#endif

//生成棋盘入口
void AGridMap::GenerateGridMap()
{
	for (auto a : NodeMap)
	{
		//标记垃圾回收
		if (a.Value)
			a.Value->MarkPendingKill();
	}
	//重置Map
	NodeMap.Reset();
	//重新生成棋格
	GenerateNodes(Size, Roll, Colume);
}

//生成棋格入口
void AGridMap::GenerateNodes(float InSize, int InRoll, int InColume)
{
	switch (MapType)
	{
	case EGridType::None:
		break;
		//六边形棋格
	case EGridType::Hex:
		GenerateHexNodes(InSize, InRoll, InColume);
		break;
	default:
		break;
	}
	//初始化棋格
	InitNodes();
}

//生成六边形棋格
void AGridMap::GenerateHexNodes(float InHexSize, int InRoll, int InColume)
{
	FVector tHexLocation;
	for (int i = 0; i < InRoll; ++i)
	{
		for (int j = 0; j < InColume; ++j)
		{
			//UE中横向坐标轴为Y，纵向坐标轴为X，需要调换在二维坐标系XY的值
			FGridVector tHexVector = FGridVector(j, i);
			tHexLocation.X = 1.5 * InHexSize * i;
			tHexLocation.Y = i % 2 == 0 ? (FMath::Sqrt(3) * InHexSize * j) : (FMath::Sqrt(3) * InHexSize * j + FMath::Sqrt(3) * 0.5 * InHexSize);
			tHexLocation.Z = 0;
			tHexLocation += GetActorLocation();
			/*这里的为什么要NewObject?,不直接用this*/
			UHexNode* tNode = NewObject<UHexNode>(this);
			//棋格初始化
			tNode->InitNode(this, tHexLocation, tHexVector, InHexSize);
			NodeMap.Add(tHexVector, tNode);
		}
	}
}

//初始化棋格入口
void AGridMap::InitNodes()
{
	switch (MapType)
	{
	case EGridType::None:
		break;
		//六边形棋格
	case EGridType::Hex:
		InitHexNodes();
		break;
	default:
		break;
	}
}

//初始化六边形棋格
void AGridMap::InitHexNodes()
{
	//设置六边形棋格相邻棋格，判断对应坐标棋格是否存在，并赋值
	for (auto a : NodeMap)
	{
		//a的类型是TMAP<键值，实际值>，a.value是UHexNode类型吗？
		UHexNode* tHexNode = Cast<UHexNode>(a.Value);
		if (!tHexNode)
			continue;
		FGridVector tRightUp = a.Key.Y % 2 == 0 ? a.Key + FGridVector(0, 1) : a.Key + FGridVector(1, 1);
		if (NodeMap.Contains(tRightUp) && NodeMap[tRightUp]->IsA(UHexNode::StaticClass()))
			tHexNode->RightUpNode = Cast<UHexNode>(NodeMap[tRightUp]);

		FGridVector tRight = a.Key + FGridVector(1, 0);
		if (NodeMap.Contains(tRight) && NodeMap[tRight]->IsA(UHexNode::StaticClass()))
			tHexNode->RightNode = Cast<UHexNode>(NodeMap[tRight]);

		FGridVector tRightDown = a.Key.Y % 2 == 0 ? a.Key + FGridVector(0, -1) : a.Key + FGridVector(1, -1);
		if (NodeMap.Contains(tRightDown) && NodeMap[tRightDown]->IsA(UHexNode::StaticClass()))
			tHexNode->RightDownNode = Cast<UHexNode>(NodeMap[tRightDown]);

		FGridVector tLeftDown = a.Key.Y % 2 == 0 ? a.Key + FGridVector(-1, -1) : a.Key + FGridVector(0, -1);
		if (NodeMap.Contains(tLeftDown) && NodeMap[tLeftDown]->IsA(UHexNode::StaticClass()))
			tHexNode->LeftDownNode = Cast<UHexNode>(NodeMap[tLeftDown]);

		FGridVector tLeft = a.Key + FGridVector(-1, 0);
		if (NodeMap.Contains(tLeft) && NodeMap[tLeft]->IsA(UHexNode::StaticClass()))
			tHexNode->LeftNode = Cast<UHexNode>(NodeMap[tLeft]);

		FGridVector tLeftUp = a.Key.Y % 2 == 0 ? a.Key + FGridVector(-1, 1) : a.Key + FGridVector(0, 1);
		if (NodeMap.Contains(tLeftUp) && NodeMap[tLeftUp]->IsA(UHexNode::StaticClass()))
			tHexNode->LeftUpNode = Cast<UHexNode>(NodeMap[tLeftUp]);

	}
}

//根据棋盘坐标获取棋格
UGridNode* AGridMap::GetNode(FGridVector InCoord) const
{
	if (NodeMap.Contains(InCoord))
		return NodeMap[InCoord];
	else
		return nullptr;
}

//https://zhuanlan.zhihu.com/p/34352477 A*
//https://zhuanlan.zhihu.com/p/54510444 A*++
bool AGridMap::FindPath(TArray<UGridNode*>& Path, AActor* InActor, UGridNode* FromNode, UGridNode* ToNode, int StopSteps)
{
	Path.Empty();
	//安全判断
	if (!FromNode || !ToNode)
		return false;
	if (!NodeMap.FindKey(FromNode) || !NodeMap.FindKey(ToNode))
		return false;
	//获取实际所有终点
	TArray<UGridNode*> ToNodes = GetNodeNeighbors(ToNode, StopSteps);
	for (int i = ToNodes.Num() - 1; i >= 0; i--)
	{
		if (!ToNodes[i]->CanPass(InActor))
			ToNodes.RemoveAt(i);
	}
	//判断起点终点是否存在
	if (!FromNode->CanPass(InActor))
		return false;
	if (ToNodes.Num() == 0)
		return false;
	//判断是否已经到达终点
	if (ToNodes.Contains(FromNode))
		return true;

	//将要遍历的路点
	TArray<UGridNode*> openList;
	//已经完成遍历的路点
	TArray<UGridNode*> closeList;
	//当前所在路点
	UGridNode* nowNode;
	nowNode = FromNode;
	openList.Add(nowNode);
	bool bFinded = false;
	//A*寻路
	while (!bFinded)
	{
		//移除openList，加入closeList
		openList.Remove(nowNode);
		closeList.Add(nowNode);
		//获取相邻路点
		TArray<UGridNode*> neighbors = nowNode->GetNeighbors();
		for (auto neighbor : neighbors)
		{
			if (!neighbor)
				continue;
			//判断相邻路点是否为终点
			if (ToNodes.Contains(neighbor))
			{
				bFinded = true;
				ToNode = neighbor;
				neighbor->PreNode = nowNode;
			}
			//如果在closeList或不能通行则跳过
			if (closeList.Contains(neighbor) || !neighbor->CanPass(InActor))
				continue;
			//如果不在openlist，则加入openlist的队尾，以备后用
			if (!openList.Contains(neighbor))
			{
				openList.Add(neighbor);
				neighbor->PreNode = nowNode;
			}
		}
		//取出队首的路点，设置为下次循环遍历的路点
		if (openList.Num() <= 0)
			break;
		else
			nowNode = openList[0];
	}
	openList.Empty();
	closeList.Empty();
	//找到了路径
	if (bFinded)
	{
		UGridNode* tNode = ToNode;
		while (tNode != FromNode)
		{
			Path.Add(tNode);
			tNode = Cast<UGridNode>(tNode->PreNode);
		}
		//获取的路径时从终点->起点的路径，需要反转回起点->终点的路径
		Algo::Reverse(Path);

		return true;
	}

	return false;

}

//判断路径是否存在
bool AGridMap::IsPathExist(AActor* InActor, UGridNode* FromNode, UGridNode* ToNode, int StopSteps)
{
	//回传FindPath的值
	TArray<UGridNode*> Path;
	return FindPath(Path, InActor, FromNode, ToNode, StopSteps);
}

//获取相邻棋格
TArray<UGridNode*> AGridMap::GetNodeNeighbors(UGridNode* InNode, int InStep) const
{
	int neighborSteps = InStep;
	TArray<UGridNode*> nowCheckList;
	TArray<UGridNode*> nextCheckList;
	TArray<UGridNode*> findList;
	nextCheckList.AddUnique(InNode);
	findList.AddUnique(InNode);

	//使用While，向外层层判断
	while (neighborSteps > 0)
	{
		nowCheckList = nextCheckList;
		nextCheckList.Empty();
		for (UGridNode* a : nowCheckList)
		{
			if (!a)
				continue;
			TArray<UGridNode*> neighbors = a->GetNeighbors();
			for (UGridNode* b : neighbors)
			{
				if (findList.Contains(b))
					continue;
				findList.AddUnique(b);
				nextCheckList.AddUnique(b);
			}
		}
		neighborSteps -= 1;
	}

	return findList;
}
