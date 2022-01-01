# complie
gcc stack_out_of_bounds.c -o bin/stack_out_of_bounds

# test
./bin/stack_out_of_bounds access_not_alloc
./bin/stack_out_of_bounds stack_grow
./bin/stack_out_of_bounds stack_grow_access
