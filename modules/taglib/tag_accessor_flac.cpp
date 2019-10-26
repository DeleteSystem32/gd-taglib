#include "tag_accessor_flac.h"

void TagAccessorFLAC::open_bytes(TagLib::IOStream *stream){
    file = memnew(TagLib::FLAC::File(stream, TagLib::ID3v2::FrameFactory::instance()));
}

Ref<Image> TagAccessorFLAC::get_album_art() const{
    if(file && file->isValid()){
        TagLib::FLAC::File *flacfile = dynamic_cast<TagLib::FLAC::File*>(file);
        if(flacfile){
            for(unsigned int i = 0; i< flacfile->pictureList().size(); i++){
                if(flacfile->pictureList()[i]->type() == TagLib::FLAC::Picture::FrontCover){
                    Ref<Image> img;
                    img.instance();
                    PoolByteArray pb;						
                    pb.resize(flacfile->pictureList()[i]->data().size());
                    PoolVector<uint8_t>::Write w = pb.write();
                    copymem(w.ptr(), flacfile->pictureList()[i]->data().data(), flacfile->pictureList()[i]->data().size());

                    TagLib::String mime = flacfile->pictureList()[i]->mimeType();


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
    return nullptr;
    
}

void TagAccessorFLAC::_bind_methods(){
}

TagAccessorFLAC::TagAccessorFLAC(){

}

