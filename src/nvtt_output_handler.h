#ifndef __NVTT_OUTPUTHANDLER_H
#define __NVTT_OUTPUTHANDLER_H
#include <vector>
#include <nvtt/nvtt.h>

using namespace std;


class NVTTOutputHandler: public nvtt::OutputHandler
{
public:
	NVTTOutputHandler();
	NVTTOutputHandler(int buffer_size);
	~NVTTOutputHandler();

	void
	beginImage( int size, int width, int height, int depth, int face,
				int miplevel);

	bool
	writeData(const void *data, int size);

	struct mipinfo {
		int offset;
		int size;
		int width, height, depth;
		int face;
	};

	vector<mipinfo> mip;

	char *buffer;
	int offset;
};

NVTTOutputHandler::NVTTOutputHandler()
{
	buffer = new char[16384];
}

NVTTOutputHandler::NVTTOutputHandler(int buffer_size)
{
	buffer = new char[buffer_size];
}

NVTTOutputHandler::~NVTTOutputHandler()
{
	delete [] buffer;
}

void
NVTTOutputHandler::beginImage( int size, int width, int height, int depth, int face,
				int miplevel)
{
	mipinfo info = {offset, size, width, height, depth, face};
	mip.push_back(info);
	return;
}

bool
NVTTOutputHandler::writeData(const void *data, int size)
{
    // Copy mipmap data
    memcpy( &buffer[offset], data, size );
    offset += size;
    return true;
}


#endif //ndef __NVTT_OUTPUTHANDLER_H
