# acidcam-cli

Acid Cam distorts video to create art. It is designed to bo used with other software or on its own. There is multiple versions of the program for macOS, Linux, and Windows as well as a command line version of the program.

This project was created in hopes of providing some entertainment, or for the Glitch artist to give you a starting image/video to use with other tools.

I call the art that I create with Acid Cam an Acid Glitch, but you can call it whatever you want. It is just meant to be a tool to use with other programs to help aid in the creation of artistic images/videos.

Acid Cam's effects are created by using Acid Cam 'filters', or pieces of code that distort an image and can be combined to produce some interesting results. The project currently has 200 filters to mix and match.

Command Line Version of Acid Cam for Linux/Unix with OpenCV:

Use Ctrl+C to break processing and still be able to use what has already been filtered.

To compile, first Install OpenCV if you are using debian you can do this with:

	$ sudo apt-get install libopencv-dev

You will also require GCC or clang and autoconf, automake

	$ sudo apt-get install autoconf automake and libtool

Download libacidcam from: https://github.com/lostjared/libacidcam

Compile and install the library

	$ ./autogen.sh && ./configure && make && sudo make install

If you are running on Linux you should use this command so it can find the library:

	$ sudo ldconfig

Then download this archive and enter the directory you extracted to in the terminal then:

	$ ./autogen.sh && ./configure && make && sudo make install

After you do that if everything goes according to plan you can test it with:

	$ acidcam -l


Remember to put quotes around arguments that use spaces for like file names etc..


 Command Line Arguments

	-l [List filters]

	-L [List Filters by Name]

	-i filename [input video]

	-o filename [output video]
	
	-a "filename1.mov, filename2.mov ..." [additional files to apply effect]

	-f 0,1,2 [filter list]

	-e flip input frame

	-v [show video while being processed]

	-c R,G,B [value RGB offsets]
	
	-p plugin.acf [plugin written in C++ see plugins folder]

	-x [list plugins in current directory (end with .ac)]
	
	-n index [uses plugin index from list printed out with -x]

	-g filename [uses image file for blend with image filters]
	
	-b brightness [value from 0-255]

	-m gamma [value from 0-255]

	-s saturation [value from 0-255]

	-r color_map [value from 1-12]

	-k colorkey_image [filename for color keyed image (uses 255,0,255)]

	-S subfilter [subfilter used in some filters]

	-u Resolution to Resize ex 1920x1080 or 1280x720

	-F frame_rate force output frame rate

	-I frames skip any number of frames outputted to file

List of the Different Color maps you can apply with -r:

	1 Autum
	2 Bone
	3 Jet
	4 Winter
	5 Rainbow
	6 Ocean
	7 Summer
	8 Spring
	9 Cool
	10 HSV
	11 Pink
	12 Hot

	$ acidcam -i test.mov -o output.mov -f 1,2 -k /path/to/colorkey.png

You can also apply a color key image 
all the pixels in the image that have the color value 255,0,255 will contain the filtered data rest of the pixels will be the same


If you install from .deb package the programs name is acidcam-cli to not conflict
with name of Acid Cam Qt program name. To install download .deb for your platform and

	$ sudo dpkg -i acidcam-cli*deb

Once you have it installed you can use either .mov (quicktime) or .avi (xvid) for the filename extension.

Example:

	$ acidcam-cli -i input.mov -o output.mov -f 1,2,3

or resize video

	$ acidcam-cli -i input.mov -o output.mov -f 1,2,3 -u 1920x1080

Or to view progress:

	$ acidcam-cli -i input.mov -o output.mov -f 0 -v

To List filters:

	$ acidcam-cli -l

To List plugins:

	$ acidcam-cli -x

To use plugin:

	$ acidcam-cli -i input.mov -o output.mov -p path/to/shared.acf -f plugin

Or use:

	$ acidcam-cli -x

Lists the plugins found then use -n index

	$ acidcam-cli -i input.mov -o output.mov -n 0 -f plugin

or Add other filters:

	$ acidcam-cli -i input.mov -o output.mov -p path/to/shared.acf -f 0,plugin,1

or Apply a color map:

	$ acidcam-cli -i input.mov -o output.mov -f 28,1 -r 3
	
or Apply brightness/gamma/saturation

	$ acidcam -i input.mov -o output.mov -b 100 -m 2 -s 25 -f 0,1


A example of using acidcam-cli:

	$ acidcam -i jaredoffice.mov -o blend.mov -g pencil.nin.png -f 31,168 -a "peace.1080p.mov, test.mov" -e -r 3 -c 0,0,50

