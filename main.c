#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

const char *VERSION;
const char *HELP;

void panic(char *msg);
void print_file_size(char *path);

int main(int argc, char **argv) {
  if (argc == 1) {
    puts(VERSION);
    puts(HELP);
  } else if (argc == 2) {
    if (strcmp(argv[1], "-v") == 0) {
      puts(VERSION);
    } else if (strcmp(argv[1], "-h") == 0) {
      puts(VERSION);
      puts(HELP);
    } else {
      print_file_size(argv[1]);
    }
  } else {
    panic("error: Unknown command!");
  }
  return 0;
}

const char *VERSION = "sz 1.0.0";
const char *HELP = "A Linux utility for viewing file sizes.\n"
                   "It displays file sizes in human readable format.\n"
                   "\n"
                   "Usage:\n"
                   "  sz <no args>  -> Print sz version and help.\n"
                   "  sz -v         -> Print sz version.\n"
                   "  sz -h         -> Print sz help.\n"
                   "  sz file.txt   -> Print file size.\n"
                   "\n"
                   "Author: csm\n"
                   "License: MIT\n";

void panic(char *msg) {
  puts(msg);
  exit(1);
}

void print_file_size(char *path) {
  struct stat info;
  bool is_symlink = false;
  double size = 0;

  if (lstat(path, &info) != 0) {
    char *msg = malloc(sizeof(char) * 500);
    if (msg == NULL) {
      panic("internal error!");
    }

    sprintf(msg, "error: Unable to read path '%s'.", path);
    panic(msg);
  }

  if (S_ISREG(info.st_mode)) {
    size = (double)info.st_size;
  } else if (S_ISLNK(info.st_mode)) {
    is_symlink = true;
    size = (double)info.st_size;
  } else {
    panic("error: Given path is not a file.");
  }

  const char *units[] = {"B", "KiB", "MiB", "GiB", "TiB"};
  int i = 0;
  while (size >= 1024 && i < 4) {
    size /= 1024;
    i += 1;
  }

  if (is_symlink) {
    puts("type: Symlink");
  } else {
    puts("type: File");
  }
  printf("size: %.2f %s\n", size, units[i]);
}
