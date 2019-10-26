#ifndef TAG_ACCESSOR_H
#define TAG_ACCESSOR_H

#include "core/reference.h"
#include "core/os/file_access.h"
#include "core/image.h"
#include "core/bind/core_bind.h"
#include <taglib.h>
#include <fileref.h>
#include <tag.h>
#include <tpropertymap.h>
#include <tfilestream.h>
#include <mpegfile.h>
#include <flacfile.h>
#include <tstring.h>
#include <tbytevectorstream.h>

class TagAccessor : public Object {

	GDCLASS(TagAccessor, Object);

protected:
	//virtual void _open_path_internal(const char *path){};
	//virtual void _open_bytes_internal(TagLib::IOStream* stream){};
	TagLib::File *file;
    virtual TagLib::File *get_file() const {return file;}

	static String to_godot_string(const TagLib::String &string);

	static void _bind_methods();

public:
	TagAccessor();
	virtual ~TagAccessor();

	//void open_path(String path);
	virtual void close();
	virtual void open_bytes(TagLib::IOStream *stream){}

	String get_title() const;
	String get_title_sort() const;
	String get_artist() const;
	String get_artist_sort() const;
	String get_album_artist() const;
	String get_album_artist_sort() const;
	String get_album() const;
	String get_album_sort() const;
	int get_year() const;
	String get_genre() const;
	int get_track() const;
	int get_total_tracks() const;
	int get_disc() const;
	int get_total_discs() const;
	

	Dictionary get_audio_properties() const;
	int get_bitrate() const;
	int get_sample_rate() const;
	int get_length() const;
	int get_length_in_seconds() const;
	int get_length_in_ms() const;

	Dictionary get_metadata() const;
	virtual Ref<Image> get_album_art() const {return nullptr;};
};

#endif
