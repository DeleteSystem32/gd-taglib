# gd-taglib

Experimental module for the [Godot Engine](https://github.com/godotengine/godot) to add read-only support for most common audio file tags. Implements [Taglib](https://taglib.org/). Tested to work on Godot 3.1 and 3.2 alpha. Could be useful for any game allowing user-supplied music files.

## Installation
Like with any other Godot module, you'll have to compile the engine yourself. Put everything from the modules and thirdparty folders into the respective folders in the Godot source directory, then compile follow the [compilation instructions](https://docs.godotengine.org/en/latest/development/compiling/) for your platform.

## Usage
The module adds a new Resource called "TagFile". Usage example:
```
var tf = TagFile.new()
tf.open_path_absolute("path/to/example.mp3")
print(tf.get_title())
tf.close()
```
