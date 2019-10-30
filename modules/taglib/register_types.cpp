#include "register_types.h"

#include "tag_file.h"

#ifdef TOOLS_ENABLED
#include "core/engine.h"
#endif

void register_taglib_types() {

	ClassDB::register_class<TagFile>();
}

void unregister_taglib_types() {
}
