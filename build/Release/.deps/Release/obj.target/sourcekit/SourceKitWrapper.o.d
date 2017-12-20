cmd_Release/obj.target/sourcekit/SourceKitWrapper.o := c++ '-DNODE_GYP_MODULE_NAME=sourcekit' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_DARWIN_USE_64_BIT_INODE=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-DBUILDING_NODE_EXTENSION' -I/Users/mac/.node-gyp/9.2.0/include/node -I/Users/mac/.node-gyp/9.2.0/src -I/Users/mac/.node-gyp/9.2.0/deps/uv/include -I/Users/mac/.node-gyp/9.2.0/deps/v8/include  -Os -gdwarf-2 -mmacosx-version-min=10.7 -arch x86_64 -Wall -Wendif-labels -W -Wno-unused-parameter -std=gnu++0x -stdlib=libc++ -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-strict-aliasing -MMD -MF ./Release/.deps/Release/obj.target/sourcekit/SourceKitWrapper.o.d.raw   -c -o Release/obj.target/sourcekit/SourceKitWrapper.o ../SourceKitWrapper.cpp
Release/obj.target/sourcekit/SourceKitWrapper.o: ../SourceKitWrapper.cpp \
  ../sourcekitd.h
../SourceKitWrapper.cpp:
../sourcekitd.h:
