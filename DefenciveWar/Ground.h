#pragma once
class Ground
{
public:
	Ground();
	~Ground();

	void Initialize();
	void Update();
	void Draw();

private:

	class ModelManager& modelMgr;
	class BackgroundCubeManager* bgCubeMgr;

	VECTOR pos;
	VECTOR dir;

	int modelHandle;
	int ImageHandle;
};

