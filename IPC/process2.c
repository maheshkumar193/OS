#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
  const int SIZE = 4096; // size in bytes of shared memory object

  const char* name = "OS"; // name of shared memory object

  int shm_fd; // shared memory file descriptor

  char *ptr; // pointer to shared memory object

  // open shared memory object
  shm_fd = shm_open(name, O_RDONLY, 0666);

  // memory map the shared memory object
  ptr = (char*)mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

  // read from shared memory object
  printf("%s", ptr);

  // remove shared object
  shm_unlink(name);
  return 0;
}