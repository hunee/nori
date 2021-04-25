#freetype

./configure CFLAGS="-arch i386" --without-zlib --without-png --without-bzip2
make clean
make
cp objs/.libs/libfreetype.a libfreetype-i386.a

./configure CFLAGS="-arch x86_64" --without-zlib --without-png --without-bzip2
make clean
make
cp objs/.libs/libfreetype.a libfreetype-x86_64.a