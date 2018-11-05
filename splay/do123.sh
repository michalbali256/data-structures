
for i in 10 100 1000 10000 100000 1000000; do
    ./splay -s T$i.in > res_s_T$i
    echo res_s_T$i "done."
    ./splay -n T$i.in > res_n_T$i
    echo res_n_T$i "done."    
done