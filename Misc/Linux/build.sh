
mkdir ../../Build
pushd ../../Build

rm *
g++ -o keypad -D PLATFORM_LINUX=1 -L /usr/X11R6/lib -I ../Headers -I ../Linux/Headers -I ../Windows/Headers ../keypad.cpp ../Linux/*.cpp ../Code/*.cpp -std=c++11 -lpthread -lX11

popd