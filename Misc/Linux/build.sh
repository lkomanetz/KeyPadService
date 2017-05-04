
mkdir ../../Build
pushd ../../Build

rm *
g++ -o test -L /usr/X11R6/lib -I ../Headers -I ../Linux/Headers ../Linux/*.cpp ../Code/*.cpp -std=c++11 -lpthread -lX11

popd