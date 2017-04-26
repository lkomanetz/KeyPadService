
mkdir ../../Build
pushd ../../Build

rm *
g++ -o test -I ../Headers -I ../Linux/Headers ../Linux/*.cpp ../Code/*.cpp -std=c++11 -lpthread

popd