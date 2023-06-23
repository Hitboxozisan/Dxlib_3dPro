#include "common.h"
#include "ImageManager.h"
#include "EnumIterator.h"
#include "ImageData.h"

using namespace ImageData;

ImageManager::ImageManager()
{
	// �񋓌^�̃C�e���[�^���쐬
	typedef EnumIterator<ImageType, ImageType::TitleLogo, ImageType::ImageAmount> itItr;

	for (auto itr : itItr())
	{
		images[itr] = LoadGraph(FILE_PATH[itr].c_str());
	}

}

ImageManager::~ImageManager()
{

}
