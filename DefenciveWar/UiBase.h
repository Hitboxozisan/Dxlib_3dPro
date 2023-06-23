#pragma once

/// <summary>
/// Uiベースクラス
/// 各Uiはこのクラスを継承する
/// </summary>
class UiBase
{
public:
	UiBase();
	virtual ~UiBase();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	const bool GetExist() const { return exist; }

	bool exist;				// 存在しているか
protected:
	struct Param
	{
		VECTOR pos;
		VECTOR prevPos;
		int handle;
	};

	Param param;
	class ImageManager& imageMgr;
	class SceneGame* data;
private:
	
};

