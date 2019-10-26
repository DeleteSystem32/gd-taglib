#include "tag_accessor_generic.h"

void TagAccessorGeneric::open_bytes(TagLib::IOStream *stream){
    _fileref = memnew(TagLib::FileRef(stream));
}

TagLib::File* TagAccessorGeneric::get_file(){
    if(_fileref){
        return _fileref->file();
    }
    return NULL;
}

void TagAccessorGeneric::close(){
    if(_fileref){
        memdelete(_fileref);
        _fileref = NULL;
    }
    TagAccessor::close();
}

void TagAccessorGeneric::_bind_methods(){

}

TagAccessorGeneric::TagAccessorGeneric(){
    _fileref = NULL;
}