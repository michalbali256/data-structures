
cd splay
mkdir release
cd release
cmake ../
cmake --build .
cd ../../

mkdir install
cd install

cp ../splay/release/splay .
cp ../generator/splaygen.c .
cp ../generate.sh .
cp ../do*.sh .
cp ../plot.py .