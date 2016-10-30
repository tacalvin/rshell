#!/bin/sh
echo "#ifndef $1_hh" > ./include/$1.h
echo "#define $1_hh" >> ./include/$1.h
echo "class $1" >> ./include/$1.h
echo "{" >> ./include/$1.h
echo "public:" >> ./include/$1.h
echo "  $1();" >> ./include/$1.h
echo "  ~$1();" >> ./include/$1.h
echo "private:" >> ./include/$1.h
echo "};" >> ./include/$1.h
echo "#endif" >> ./include/$1.h
echo "#include \"./include/$1.h\"" > $1.cpp

echo "$1::$1()" >> $1.cpp
echo "{}" >> $1.cpp
echo "$1::~$1()" >> $1.cpp
echo "{}" >> $1.cpp
