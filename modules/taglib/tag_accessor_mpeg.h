#ifndef TAG_ACCESSOR_MPEG
#define TAG_ACCESSOR_MPEG

#include "tag_file.h"

#include <mpegfile.h>
#include <id3v2tag.h>
#include <id3v2frame.h>
#include <id3v2header.h>
#include <attachedpictureframe.h>


class TagAccessorMPEG : public TagAccessor {

	GDCLASS(TagAccessorMPEG, TagAccessor);

protected:
	static void _bind_methods();

public:
	TagAccessorMPEG();
	//~TagAccessorMPEG();

	void open_bytes(TagLib::IOStream *stream);

	Ref<Image> get_album_art() const;

};

#endif