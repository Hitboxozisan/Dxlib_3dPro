#pragma once

/// <summary>
/// ノードの進行・管理を行う
/// シングルトンではなく各自所持する
/// </summary>
class NodeManager
{
public:
	NodeManager();
	~NodeManager();

	void Initialize();
	void Update();

	void EntryNode();


private:

};

