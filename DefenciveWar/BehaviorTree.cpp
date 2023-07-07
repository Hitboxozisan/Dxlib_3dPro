#include "BehaviorTree.h"
#include "NodeBase.h"
#include "ActBase.h"
#include "Singleton.h"
#include "Random.h"
#include "DxLib.h"

BehaviorTree::BehaviorTree()
	:random(Singleton<Random>::GetInstance())
{
	Initialize();
}

BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::Initialize()
{
	// ツリーの初期化
	aiTree.empty();
}

void BehaviorTree::EntryNode(std::string inName, std::string inParent, int inHierarchy, int inPriority, BehaviorTree::SelectRule inRule, ActBase* inAction)
{
	NodeBase* node = new NodeBase(inName, inHierarchy, inPriority, inRule, inAction);
	
	// 始端ノードの場合
	if (aiTree.empty())
	{
		aiTree.push_back(node);
		return;
	}
	
	// 誰が親か確認
	// 親の子ノードに追加する
	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
	{
		if ((*itr)->GetName() == inParent)
		{
			// 子のノードとして追加
			(*itr)->EntryChild(node);

			// 選択方法がシークエンスの場合は
			//if ((*itr)->GetRule() == SelectRule::Sequence)
			//{
			//	// シークエンスノードに登録
			//	sequenceNode.push(node); 
			//}
		}
	}
	
	// ツリーに追加
	aiTree.push_back(node);
}

NodeBase* BehaviorTree::SelectNode(NodeBase* inNode)
{
	activeNode.clear();
	std::vector<NodeBase*> inChild = inNode->GetChild();
	NodeBase* node = nullptr;

	// 子のノードの中から実行可能なノードを選択
	for (auto itr = inChild.begin(); itr != inChild.end(); itr++)
	{
		// ノードが実行可能か
		if ((*itr)->IsExecutabel())
		{
			activeNode.push_back(*itr);
		}
	}

	// 子の	実行可能ノードから選択する
	switch (inNode->GetRule())
	{
	case SelectRule::None:
		node = *activeNode.begin();
		break;
	case SelectRule::Priority:
		node = SelectPriority();
		break;
	case SelectRule::Sequence:
		node = SelectSequence(inNode);
		break;
	case SelectRule::Random:
		node = SelectRandom();
		break;
	}

	// ノードが決定した場合
	if (node != NULL)
	{
		// 行動がない場合は次の行動を選択
		if (node->GetAction() == NULL)
		{
			node = SelectNode(node);
		}
	}
	
	
	return node;
}

/// <summary>
/// ノードが存在するか
/// </summary>
/// <param name="inName"></param>
/// <returns></returns>
bool BehaviorTree::SearchNode(std::string inName)
{
	if (aiTree.empty())
	{
		return false;
	}

	for (auto itr = aiTree.begin(); itr != aiTree.end(); itr++)
	{
		if ((*itr)->GetName() == inName)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// ノードが使用済みか
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
bool BehaviorTree::IsUsedNode(NodeBase* inNode)
{
	for (auto itr = usedNode.begin(); itr != usedNode.end(); itr++)
	{
		if ((*itr)->GetName() == inNode->GetName())
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// シークエンスの途中か
/// </summary>
/// <returns></returns>
NodeBase* BehaviorTree::SequenceEnRoute()
{
	NodeBase* node = NULL;

	// シークエンスの途中なら次のシークエンスを返す
	if (!sequenceNode.empty())
	{
		if (sequenceNode.top()->GetAction() == NULL)
		{
			sequenceNode.pop();
		}
		else
		{
			node = sequenceNode.top();
		}
		
		// 使用するノードをシークエンスから削除する
		sequenceNode.pop();
		return node;
	}
	else
	{
		return NULL;
	}
}

/// <summary>
/// ノードを推論
/// </summary>
/// <returns></returns>
NodeBase* BehaviorTree::InferenceNode()
{
	// 使用済みノードのリセット
	usedNode.clear();
	NodeBase* node = *aiTree.begin();

	// 末端ノードになるまで繰り返す
	while (!node->GetChildEmpty())
	{
		// 子の中からどのノードを選ぶか選択
		node = SelectNode(node);
	}

	return node;
}

/// <summary>
/// 使用済みノードの初期化
/// </summary>
void BehaviorTree::ResetUsedNode()
{
	usedNode.clear();
}

/// <summary>
/// Priority選択
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SelectPriority()
{
	int priority = 100;
	NodeBase* node = NULL;

	for (auto itr = activeNode.begin(); itr != activeNode.end(); itr++)
	{
		if ((*itr)->GetPriority() <= priority &&
			!IsUsedNode((*itr)))
		{
			priority = (*itr)->GetPriority();
			node = (*itr);
		}
	}

	return node;
}

/// <summary>
/// Sequence選択
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SelectSequence(NodeBase* inParent)
{
	for (auto itr = activeNode.begin(); itr != activeNode.end(); itr++)
	{
		sequenceNode.push(*itr);
	}
	NodeBase* result = sequenceNode.top();
	sequenceNode.pop();

	return result;
}

/// <summary>
/// Random選択
/// 各ノード均一な確率
/// </summary>
/// <param name="inNode"></param>
/// <returns></returns>
NodeBase* BehaviorTree::SelectRandom()
{
	int rand = random.GetRandomInt(0, activeNode.size());

	return activeNode[rand];
}
