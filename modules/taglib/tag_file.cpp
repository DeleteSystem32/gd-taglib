#include "tag_file.h"

void TagFile::open_path_absolute(const String &path){
	close();

	//
#ifdef _WIN32
	//windows handles strings differently
	_stream = memnew(TagLib::FileStream(TagLib::FileName(path.c_str()), true));
#else
	_stream = memnew(TagLib::FileStream(path.utf8().get_data(), true));
#endif

	//here, check if any of the special supported types (needed for album art support)
	//isSupported seems to fail w/ full stops in path
	String ext = path.get_extension().to_upper();
	//if(TagLib::MPEG::File::isSupported(_stream)){
	if(ext == "MP3"){
		// create mpeg tag accessor
		
		tags = memnew(TagAccessorMPEG());
		//print_line("created mpeg accessor for " + path);
	}

	//else if(TagLib::FLAC::File::isSupported(_stream)){
	else if(ext == "FLAC"){
		//create flac tag accessor
		tags = memnew(TagAccessorFLAC());
		
	}

	else{
		//create generic file accessor
		tags = memnew(TagAccessorGeneric());
	}

	if(tags){
		tags->open_bytes(_stream);
	}
	
}

void TagFile::open_file(Ref<_File> file){
	//close();
	if(file->is_open()){
		open_path_absolute(file->get_path_absolute());
	}
}

void TagFile::open_bytes(const PoolByteArray &bytes){
	PoolByteArray::Read r = bytes.read();
	_stream = memnew(TagLib::ByteVectorStream(TagLib::ByteVector((const char*)r.ptr(), bytes.size())));

	//here, check if any of the special supported types (needed for album art support)

	if(TagLib::MPEG::File::isSupported(_stream)){
		tags = memnew(TagAccessorMPEG());
	}

	else if(TagLib::FLAC::File::isSupported(_stream)){
		tags = memnew(TagAccessorFLAC());
		
	}

	else{
		tags = memnew(TagAccessorGeneric());
	}

	if(tags){
		tags->open_bytes(_stream);
	}
}

void TagFile::close(){
	if(tags){
		memdelete(tags);
		tags = NULL;
	}

	if(_stream){
		memdelete(_stream);
		_stream = NULL;
	}
}

Dictionary TagFile::get_metadata(){	
	return tags ? tags->get_metadata() : Dictionary();
}

String TagFile::get_title(){
	return tags ? tags->get_title() : "";
}

String TagFile::get_title_sort(){
	return tags ? tags->get_title_sort() : "";
}

String TagFile::get_artist(){
	return tags ? tags->get_artist() : "";
}

String TagFile::get_artist_sort(){
	return tags ? tags->get_artist_sort() : "";
}

String TagFile::get_album_artist(){
	return tags ? tags->get_album_artist() : "";
}	

String TagFile::get_album_artist_sort(){
	return tags ? tags->get_album_artist_sort() : "";
}

String TagFile::get_album(){
	return tags ? tags->get_album() : "";
}

String TagFile::get_album_sort(){
	return tags ? tags->get_album_sort() : "";
}

int TagFile::get_year(){
	return tags ? tags->get_year() : 0;
}

String TagFile::get_genre(){
	return tags ? tags->get_genre() : "";
}

int TagFile::get_track(){
	return tags ? tags->get_track() : 0;
}

int TagFile::get_total_tracks(){
	return tags ? tags->get_total_tracks() : 0;
}

int TagFile::get_disc(){
	return tags ? tags->get_disc() : 0;
}

int TagFile::get_total_discs(){
	return tags ? tags->get_total_discs() : 0;
}

Ref<Image> TagFile::get_album_art(){
	return tags ? tags->get_album_art() : nullptr;
}

Dictionary TagFile::get_audio_properties(){
	return tags ? tags->get_audio_properties() : Dictionary();
}

int TagFile::get_bitrate(){
	return tags ? tags->get_bitrate() : 0;
}

int TagFile::get_sample_rate(){
	return tags ? tags->get_sample_rate() : 0;
}

int TagFile::get_length(){
	return tags ? tags->get_length() : 0;
}

int TagFile::get_length_in_seconds(){
	return tags ? tags->get_length_in_seconds() : 0;
}

int TagFile::get_length_in_ms(){
	return tags ? tags->get_length_in_ms() : 0;
}

void TagFile::_bind_methods(){
	ClassDB::bind_method(D_METHOD("open_path_absolute", "path"), &TagFile::open_path_absolute);
	//ClassDB::bind_method(D_METHOD("open_bytes", "bytes"), &TagFile::open_bytes);
	//ClassDB::bind_method(D_METHOD("open_file", "file"), &TagFile::open_file);

	ClassDB::bind_method(D_METHOD("close"), &TagFile::close);

	//getters
	ClassDB::bind_method(D_METHOD("get_metadata"), &TagFile::get_metadata);
	ClassDB::bind_method(D_METHOD("get_audio_properties"), &TagFile::get_audio_properties);

	//properties
	ClassDB::bind_method(D_METHOD("get_bitrate"), &TagFile::get_bitrate);
	ClassDB::bind_method(D_METHOD("get_sample_rate"), &TagFile::get_sample_rate);
	ClassDB::bind_method(D_METHOD("get_length"), &TagFile::get_length);
	ClassDB::bind_method(D_METHOD("get_length_in_seconds"), &TagFile::get_length_in_seconds);
	ClassDB::bind_method(D_METHOD("get_length_in_ms"), &TagFile::get_length_in_ms);

	//tags
	ClassDB::bind_method(D_METHOD("get_album_art"), &TagFile::get_album_art);
	ClassDB::bind_method(D_METHOD("get_title"), &TagFile::get_title);
	ClassDB::bind_method(D_METHOD("get_title_sort"), &TagFile::get_title_sort);
	ClassDB::bind_method(D_METHOD("get_artist"), &TagFile::get_artist);
	ClassDB::bind_method(D_METHOD("get_artist_sort"), &TagFile::get_artist_sort);
	ClassDB::bind_method(D_METHOD("get_album_artist"), &TagFile::get_album_artist);
	ClassDB::bind_method(D_METHOD("get_album_artist_sort"), &TagFile::get_album_artist_sort);
	ClassDB::bind_method(D_METHOD("get_album"), &TagFile::get_album);
	ClassDB::bind_method(D_METHOD("get_album_sort"), &TagFile::get_album_sort);
	ClassDB::bind_method(D_METHOD("get_year"), &TagFile::get_year);
	ClassDB::bind_method(D_METHOD("get_genre"), &TagFile::get_genre);
	ClassDB::bind_method(D_METHOD("get_track"), &TagFile::get_track);
	ClassDB::bind_method(D_METHOD("get_total_tracks"), &TagFile::get_total_tracks);
	ClassDB::bind_method(D_METHOD("get_disc"), &TagFile::get_disc);
	ClassDB::bind_method(D_METHOD("get_total_discs"), &TagFile::get_total_discs);

}

TagFile::TagFile(){
	_stream = NULL;
	tags = NULL;
}

TagFile::~TagFile(){
	close();
}