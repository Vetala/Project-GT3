--- Project Building ---

SDK Version: Ogre3d v-1.9.0 (ghadamon)
VS Compiler: Visual Studio 2012 (vs120)
VS Version:  Visual Studio 2015 (Community)

Guide: http://www.ogre3d.org/tikiwiki/Setting+Up+An+Application+-+Visual+Studio
*Some alterations have been made, such as copying dlls to output and setting the output dir

OGRE_HOME needs to point to the sdk directory in the environmental variables
to be able to compile this project.

The library files in this project were compiled using visual studio 2012.
You therefore need visual studio 2012 to build this project.

Open the project using visual studio 2015! (Platform toolset has been set)

--- Additional Notes ---
Tutorial: http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Basic+Tutorial+Introduction&structure=Tutorials

The tutorial framework, used here, uses media from the SDK media folder.
I tried to start everything afresh by copying the necessary files to the project dir.
In order for the program to run, files from the external directory are copied into the output dir.
Please don't change these files in external! Change them inside the output folder instead.

Also, don't change the location of the media,obj,external or bin folders.
