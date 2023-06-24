#pragma once

/// <summary>
/// Ui�x�[�X�N���X
/// �eUi�͂��̃N���X���p������
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

	bool exist;				// ���݂��Ă��邩
protected:
	struct Param
	{
		VECTOR pos;
		VECTOR prevPos;
		int handle;
	};

	Param param;
	class ImageManager& imageMgr;
	class DeltaTime& deltaTime;
	class SceneGame* data;
private:
	
};

