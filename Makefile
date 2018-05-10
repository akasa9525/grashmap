CXXFLAGS += -O3 -DNDEBUG -std=c++11 -Wno-deprecated-declarations -Isrc -I /usr/local//include
CPPFLAGS += 

UNAME_S=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CXXFLAGS += -mmacosx-version-min=10.7 -stdlib=libc++
else
	CXXFLAGS += -include src/common/memcpyLink.h -Wl,--wrap=memcpy
	CFLAGS += -include src/common/memcpyLink.h
endif

SOURCE_1=src/map/mash_map.cpp
SOURCE_2=src/align/align.cpp

all : mashmap 

mashmap : 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SOURCE_1) -o mashmap -L/usr/local//lib -lgsl -lgslcblas -lstdc++ -lz -lm -lpthread 

mashmap-align : 
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SOURCE_2) -o mashmap-align -L/usr/local//lib -lgsl -lgslcblas -lstdc++ -lz -lm -lpthread 

install : mashmap
	mkdir -p /usr/local/bin/
	cp `pwd`/mashmap /usr/local/bin/

clean :
	-rm -f mashmap
	-rm -f mashmap-align
