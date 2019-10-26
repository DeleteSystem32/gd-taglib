#include "tag_accessor_mpeg.h"

void TagAccessorMPEG::open_bytes(TagLib::IOStream *stream){
    file = memnew(TagLib::MPEG::File(stream, TagLib::ID3v2::FrameFactory::instance()));
}

Ref<Image> TagAccessorMPEG::get_album_art() const{
    if(file && file->isValid()){
        TagLib::MPEG::File *mp3file = dynamic_cast<TagLib::MPEG::File*>(file);
        if(mp3file && mp3file->hasID3v2Tag()){
            TagLib::ID3v2::FrameList frames = mp3file->ID3v2Tag()->frameListMap()["APIC"];
            if(!frames.isEmpty()){
                for(TagLib::ID3v2::FrameList::ConstIterator it = frames.begin(); it != frames.end(); it++){
                    TagLib::ID3v2::AttachedPictureFrame *picframe = (TagLib::ID3v2::AttachedPictureFrame*)(*it);
                    if(picframe->type() == TagLib::ID3v2::AttachedPictureFrame::FrontCover){
                        TagLib::String mime = picframe->mimeType();

                        if(mime == "image/png" || mime == "image/jpeg" || mime == "image/jpg"){
                            PoolByteArray pb;
                            pb.resize(picframe->picture().size());
                            PoolByteArray::Write w = pb.write();
                            memcpy(w.ptr(), picframe->picture().data(), picframe->picture().size());

                            Ref<Image> img;
                            img.instance();

                            if(mime == "image/png"){
                                img->load_png_from_buffer(pb);
                            }

                            else if(mime == "image/jpeg" || mime == "image/jpg"){
                                img->load_jpg_from_buffer(pb);
                            }
                            return img;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
    
}

void TagAccessorMPEG::_bind_methods(){
}

TagAccessorMPEG::TagAccessorMPEG(){

}

