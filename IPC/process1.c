#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char* argv[]) {
  const int SIZE = 4096; // size in bytes of shared memory object

  printf("%d\n", argc);

  for (int i = 0; i < argc; i++) printf("%s\n", argv[i]);

  const char* name = "OS"; // name of shared memory object

  const char* msg0 = "Hello";

  const char* msg1 = "World!";

  int shm_fd; // shared memory file descriptor

  char *ptr; // pointer to shared memory object

  // create shared memory object
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  printf("%d\n", shm_fd);

  // configure size of shared memory object
  ftruncate(shm_fd, SIZE);

  // memory map the shared memory object
  ptr = (char *)mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  if (ptr == MAP_FAILED) {
    printf("Mapping Failed\n");
    return 1;
  }

  // write into shared memory object
  printf("%s", "shared memory concept");
  sprintf(ptr, "%s", msg0);
  ptr += strlen(msg0);
  sprintf(ptr, "%s", msg1);
  ptr += strlen(msg1);
  return 0;
}