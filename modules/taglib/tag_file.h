#ifndef TAG_FILE_H
#define TAG_FILE_H

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

#include "tag_accessor_flac.h"
#include "tag_accessor_mpeg.h"
#include "tag_accessor_generic.h"

class TagFile : public Reference {

	GDCLASS(TagFile, Reference);

	TagLib::IOStream *_stream;

	//could actually have a struct containing all the info that gets populated on open
	//then, no need to keep stream in memory?
	

protected:

	TagAccessor *tags;
	static void _bind_methods();

public:
	TagFile();
	virtual ~TagFile();

	void open_path(const String &path);
	//void open_file(Ref<_File> file);
	void close();
	//void open_bytes(const PoolByteArray &bytes);

	String get_title();
	String get_title_sort();
	String get_artist();
	String get_album_artist();
	String get_album();
	int get_year();
	String get_genre();
	int get_track();
	int get_total_tracks();
	int get_disc();
	int get_total_discs();
	String get_album_sort();
	String get_artist_sort();
	String get_album_artist_sort();

	Dictionary get_audio_properties();
	int get_bitrate();
	int get_sample_rate();
	int get_length();
	int get_length_in_seconds();
	int get_length_in_ms();

	Dictionary get_metadata();
	Ref<Image> get_album_art();
};

#endif
