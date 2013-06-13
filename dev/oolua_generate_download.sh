#!/bin/bash 
pwd_on_entry=$PWD

cd ..
premake4 clean

mkdir ../../oolua-$1 
cp -r ./* ../../oolua-$1
mkdir ../../oolua-$1/docs
cp -r ../../docs/branches/dsl/html/* ../../oolua-$1/docs
cp ../../docs/branches/dsl/latex/refman.pdf $pwd_on_entry/oolua-$1.pdf

cd ../../oolua-$1
rm -rf ./lib 
rm -rf ./obj 
rm -rf ./bin 
rm -rf ./build_logs 
mv ./dev/docs.html ./docs.html
rm -rf ./dev 



find ./ -name "*.Doxyfile" -print0  | xargs -0 rm -Rf 
find ./ -name "*.dox" -print0  | xargs -0 rm -Rf 
find ./ -name ".svn" -print0  | xargs -0 rm -Rf 
find ./ -name ".DS_Store" -print0  | xargs -0 rm -Rf 


cd profile
if [ -d luabind ]; then
	rm -rf ./luabind 
fi

if [ -d src ]; then
	rm -rf ./src 
fi

if [ -d SLB3 ]; then
	rm -rf ./SLB3 
fi

if [ -d detail ]; then
	rm -rf ./detail 
fi

find ./ -name "LuaBridge.h" -print0  | xargs -0 rm -Rf 
find ./ -name "RefCountedObject.h" -print0  | xargs -0 rm -Rf
find ./ -name "RefCountedptr.h" -print0  | xargs -0 rm -Rf

cd ..

cd ..
#COPYFILE_DISABLE=true tar -zcf ../oolua-release-$1.tar.gz *
#COPYFILE_DISABLE=true tar cvf  ./oolua-$1.tar.gz ./oolua-$1 
tar -zcf ./oolua-$1.tar.gz ./oolua-$1
#zip -r ../oolua-release-$1.zip *
zip -r ./oolua-$1.zip ./oolua-$1

rm -rf ./oolua-$1
echo $PWD
mv ./oolua-${1}.tar.gz ${pwd_on_entry}/oolua-${1}.tar.gz
mv ./oolua-${1}.zip ${pwd_on_entry}/oolua-${1}.zip
cd $pwd_on_entry

#cd ..
#rm -rf ./oolua-release-$1

