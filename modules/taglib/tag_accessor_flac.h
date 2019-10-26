#ifndef TAG_ACCESSOR_FLAC
#define TAG_ACCESSOR_FLAC

#include "tag_accessor.h"
#include <flacfile.h>
#include <id3v2tag.h>

class TagAccessorFLAC : public TagAccessor {

	GDCLASS(TagAccessorFLAC, TagAccessor);

protected:
	static void _bind_methods();

public:
	TagAccessorFLAC();
	//~TagFileFLAC();

	void open_bytes(TagLib::IOStream *stream);

	Ref<Image> get_album_art() const;

};

#endif