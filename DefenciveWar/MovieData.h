#pragma once
#include <unordered_map>
#include <string.h>
#include "MovieTypeData.h"

namespace MovieData
{
	// 各ムービーファイルパス
	std::unordered_map<int, const std::string> FILE_PATH =
	{
		{MovieType::Demo, "Data/Movie/Demo.mp4"},
	};

}