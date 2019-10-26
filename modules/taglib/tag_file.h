/*************************************************************************/
/*  tag_file.h                                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef TAG_FILE_H
#define TAG_FILE_H

#include "core/reference.h"
#include "core/os/file_access.h"
#include "core/image.h"
#include "core/bind/core_bind.h"
//#include "tag_accessor.h"
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

	void open_path_absolute(const String &path);
	void open_file(Ref<_File> file);
	void close();
	void open_bytes(const PoolByteArray &bytes);

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
