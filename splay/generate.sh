g++ -o3 splaygen.c -o splaygen

for i in 10 100 1000 10000 100000 1000000; do
    ./splaygen -s72 -t$i > T$i.in
    echo T$i generated.
done

./splaygen -s72 -b > seq.in
./splaygen -s72 -u > uniform.in
./splaygen -s72 -w > nonuniform.in