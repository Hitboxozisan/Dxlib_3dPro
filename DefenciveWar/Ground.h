#pragma once
class Ground
{
public:
	Ground();
	~Ground();

	void Initialize();
	void Draw();

private:

	class ModelManager& modelMgr;

	VECTOR pos;
	VECTOR dir;

	int modelHandle;
	int ImageHandle;
};

