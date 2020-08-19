#include "tag_file.h"

void TagAccessor::close(){
	if(file){
        
		memdelete(file);
		file = NULL;
	}
}

String TagAccessor::to_godot_string(const TagLib::String &string){
	return String(string.toCWString());
}

Dictionary TagAccessor::get_metadata() const{	
	Dictionary dm;
	
	if(get_file() && get_file()->isValid()){
		TagLib::PropertyMap pm = get_file()->properties();
		TagLib::SimplePropertyMap::Iterator iter = pm.begin();
		while(iter != pm.end()){
			if(!iter->second.isEmpty()){
				dm[to_godot_string(iter->first)] = to_godot_string(iter->second.toString());
			}
			
			iter++;
		}
	}
	return dm;
}

String TagAccessor::get_title() const{
	if(get_file() && get_file()->isValid()){		
		return to_godot_string(get_file()->tag()->title());
	}
	return "";
}

String TagAccessor::get_title_sort() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->properties().contains("TITLESORT") ? to_godot_string(get_file()->properties()["TITLESORT"][0]) : get_title();
	}
	return "";
}

String TagAccessor::get_artist() const{
	if(get_file() && get_file()->isValid()){
		return to_godot_string(get_file()->tag()->artist());
	}
	return "";
}

String TagAccessor::get_artist_sort() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->properties().contains("ARTISTSORT") ? to_godot_string(get_file()->properties()["ARTISTSORT"][0]) : get_artist();
	}
	return "";
}

String TagAccessor::get_album_artist() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->properties().contains("ALBUMARTIST") ? to_godot_string(get_file()->properties()["ALBUMARTIST"][0]) : get_artist();
	}
	return "";
}

String TagAccessor::get_album_artist_sort() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->properties().contains("ALBUMARTISTSORT") ? to_godot_string(get_file()->properties()["ALBUMARTISTSORT"][0]) : get_album_artist();
	}
	return "";
}

String TagAccessor::get_album() const{
	if(get_file() && get_file()->isValid()){
		return to_godot_string(get_file()->tag()->album());
	}
	return "";
}

String TagAccessor::get_album_sort() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->properties().contains("ALBUMSORT") ? to_godot_string(get_file()->properties()["ALBUMSORT"][0]) : get_album();
	}
	return "";
}

int TagAccessor::get_year() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->tag()->year();
	}
	return 0;
}

String TagAccessor::get_genre() const{
	if(get_file() && get_file()->isValid()){
		return to_godot_string(get_file()->tag()->genre());
	}
	return "";
}

int TagAccessor::get_track() const{
	if(get_file() && get_file()->isValid()){
		return get_file()->tag()->track();
	}
	return 0;
}

int TagAccessor::get_total_tracks() const{
	if(get_file() && get_file()->isValid()){
		if(get_file()->properties().contains("TOTALTRACKS")){
			return get_file()->properties()["TOTALTRACKS"].toString().toInt();
		}
		else if(get_file()->properties().contains("TRACKNUMBER")){
			//likely string separated w/slash
			TagLib::StringList sl = get_file()->properties()["TRACKNUMBER"][0].split("/");
			if(sl.size()>=2){
				return sl[1].toInt();
			}
		}
	}
	return 0;
}

int TagAccessor::get_disc() const{
	if(get_file() && get_file()->isValid()){
		if(get_file()->properties().contains("DISCNUMBER")){
			return get_file()->properties()["DISCNUMBER"][0].toInt();
		}
	}
	return 0;
}

int TagAccessor::get_total_discs() const{
	if(get_file() && get_file()->isValid()){
		if(get_file()->properties().contains("DISCTOTAL")){
			return get_file()->properties()["DISCTOTAL"].toString().toInt();
		}
		else if(get_file()->properties().contains("DISCNUMBER")){
			//likely string separated w/slash
			TagLib::StringList sl = get_file()->properties()["DISCNUMBER"][0].split("/");
			if(sl.size()>=2){
				return sl[1].toInt();
			}
		}
	}
	return 0;
}

Dictionary TagAccessor::get_audio_properties() const{
	Dictionary apd;
	if(get_file() && get_file()->isValid()){
		TagLib::AudioProperties *ap = get_file()->audioProperties();
		apd["length"] = ap->length();
		apd["length_in_seconds"] = ap->lengthInSeconds();
		apd["length_in_milliseconds"] = ap->lengthInMilliseconds();
		apd["bitrate"] = ap->bitrate();
		apd["sample_rate"] = ap->sampleRate();
		apd["channels"] = ap->channels();
	}
	return apd;
}

int TagAccessor::get_bitrate() const{
	return (get_file() && get_file()->isValid()) ? get_file()->audioProperties()->bitrate() : 0;
}

int TagAccessor::get_sample_rate() const{
	return (get_file() && get_file()->isValid()) ? get_file()->audioProperties()->sampleRate() : 0;
}

int TagAccessor::get_length() const{
	return (get_file() && get_file()->isValid()) ? get_file()->audioProperties()->length() : 0;
}

int TagAccessor::get_length_in_seconds() const{
	return (get_file() && get_file()->isValid()) ? get_file()->audioProperties()->lengthInSeconds() : 0;
}

int TagAccessor::get_length_in_ms() const{
	return (get_file() && get_file()->isValid()) ? get_file()->audioProperties()->lengthInMilliseconds() : 0;
}

void TagAccessor::_bind_methods(){
}

TagAccessor::TagAccessor(){
	file = NULL;
}

TagAccessor::~TagAccessor(){
	close();
}