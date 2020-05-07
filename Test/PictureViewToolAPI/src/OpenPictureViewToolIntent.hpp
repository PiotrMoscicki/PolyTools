#pragma once

#include <memory>
#include <pp/IntentInfo.hpp>

class PictureViewTool;

//-------------------------------------------------------------------------------------------------------
class OpenPictureViewToolIntent
{
public:
	using Result = std::unique_ptr<PictureViewTool>;
	static inline pp::IntentInfo Info = { "OpenPictureViewToolIntent", 1 };
};
