all: 
	gcc test.c functions.c kiss_widgets.c kiss_draw.c kiss_general.c kiss_posix.c -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers \
	-I ~/Library/Frameworks/SDL2_image.framework/Versions/A/Headers -F ~/Library/Frameworks/ \
	-framework SDL2 -framework SDL2_image \
	-I ~/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers -F ~/Library/Frameworks/ \
	-framework SDL2 -framework SDL2_ttf

