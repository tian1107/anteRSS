#pragma once

#include <anteRSSParser\DownloadManagerUnthreaded.h>

namespace anteRSSParserWrapper
{
	ref class DownloadManagerWrapper
	{
	private:
		anteRSSParser::DownloadManagerUnthreaded * manager;
	public:
		DownloadManagerWrapper();
	};
}
