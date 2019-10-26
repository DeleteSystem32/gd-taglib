#ifndef TAG_ACCESSOR_GENERIC
#define TAG_ACCESSOR_GENERIC

#include "tag_accessor.h"
#include <fileref.h>

class TagAccessorGeneric : public TagAccessor {

	GDCLASS(TagAccessorGeneric, TagAccessor);

    TagLib::FileRef *_fileref;

protected:
	static void _bind_methods();
    TagLib::File *get_file();

public:
	TagAccessorGeneric();

    void close();

	void open_bytes(TagLib::IOStream *stream);

};

#endif