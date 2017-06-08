#include "stdafx.h"
#include "DownloadManagerWrapper.h"

namespace anteRSSParserWrapper
{
	DownloadManagerWrapper::DownloadManagerWrapper()
	{
		manager = new anteRSSParser::DownloadManagerUnthreaded();
	}

}