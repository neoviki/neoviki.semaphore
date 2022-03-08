gcc -lpthread -I../src/ ../src/neoviki_semaphore_lock.c writer.c -o writer
gcc -lpthread -I../src/ ../src/neoviki_semaphore_lock.c writer_lock_and_die.c -o writer_lock_and_die
gcc -lpthread -I../src/ ../src/neoviki_semaphore_lock.c reader.c -o reader
gcc -lpthread -I../src/ ../src/neoviki_semaphore_lock.c destroy.c -o destroy
