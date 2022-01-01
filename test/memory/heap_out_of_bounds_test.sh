# complie
gcc heap_out_of_bounds.c -o ./bin/heap_out_of_bounds

# test
./bin/heap_out_of_bounds access_not_alloc
./bin/heap_out_of_bounds heap_grow
./bin/heap_out_of_bounds heap_grow_access
