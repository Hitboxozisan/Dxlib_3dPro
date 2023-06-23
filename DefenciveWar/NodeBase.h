#pragma once

#include <vector>
#include <string>
#include "BehaviorTree.h"
#include "ActionBase.h"

class ExecJudgmentBase;
class BehaviorData;
class BossEnemy;

/// <summary>
/// 
/// </summary>
class NodeBase
{
public:
	NodeBase(std::string inName,
			 NodeBase *inParent,
			 NodeBase *inSibling,
			 int inPriority,
			 BehaviorTree::SelectRule inSelectRule,
			 ExecJudgmentBase* inJudgment,
			 ActionBase* inAction,
			 int inHierarchyNo);
	~NodeBase();

	

	NodeBase* SelectPriority(std::vector<NodeBase*>* list);	// �D�揇�ʑI��
	NodeBase* SelectRandom(std::vector<NodeBase*>* list);	// �����_���I��
	NodeBase* SelectOnOff(std::vector<NodeBase*>* list,
						  BehaviorData* data);				// �I���E�I�t�I��
	NodeBase* SelectSequence(std::vector<NodeBase*>* list,
							 BehaviorData* data);			// �V�[�P���X�I��
	

	NodeBase* SearchNode(std::string searchName);				// �m�[�h����
	NodeBase* Inference(BossEnemy* boss, BehaviorData* data);	// �m�[�h���_
	void PrintName();											// �m�[�h���\��

	ActionBase::State Run(BossEnemy* boss);		// ���s
	
	// �Q�b�^�[
	std::string GetName() { return name; };			// ���O�Q�b�^�[
	NodeBase* GetParent() { return parent; };		// �e�m�[�h�Q�b�^�[
	NodeBase* GetChild(int idx);					// �q�m�[�h�Q�b�^�[
	NodeBase* GetLastChild();						// �q�m�[�h�Q�b�^�[�i�����j
	NodeBase* GetTopChild();						// �q�m�[�h�Q�b�^�[�i�擪�j
	NodeBase* GetSibling() { return sibling; };		// �Z��m�[�h�Q�b�^�[
	int GetHirechyNo() { return hierarchyNo; };		// �K�w�ԍ��Q�b�^�[
	int GetPriority() { return priority; };			// �D�揇�ʃQ�b�^�[
	// �Z�b�^�[
	void SetParent(NodeBase* inParent) { parent = inParent; };			// �e�m�[�h�Q�b�^�[
	void AddChaild(NodeBase* inChild) { child.push_back(inChild); };	// �q�m�[�h�ǉ�
	void SetSibling(NodeBase* inSibling) { sibling = inSibling; };		// �Z��m�[�h�Z�b�^�[

	bool HasAction() { return action != NULL ? true : false; };			// �s���f�[�^�������Ă��邩
	bool Judgment(BossEnemy* boss);			// ���s�۔���

private:
	std::string name;						// ���O
	BehaviorTree::SelectRule selectRule;	// �I�����[��
	ExecJudgmentBase* execJudgment;			// ����N���X
	ActionBase* action;						// ���s�N���X
	unsigned int priority;					// �D�揇��
	NodeBase* parent;						// �e�m�[�h
	std::vector<NodeBase*> child;			// �q�m�[�h
	NodeBase* sibling;						// �Z��m�[�h
	int hierarchyNo;						// �K�w�ԍ�

};

