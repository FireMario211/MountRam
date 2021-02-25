/**
  * MountRam v1.0.0
  *	Created by FireMario211 (2021)
  * meant as my first C project on Github okay, this coding probably doesnt look good

  * This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

  * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  * You should have received a copy of the GNU General Public License along with this program; if not, see <https://www.gnu.org/licenses>.


  */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/mount.h>

#define MAX_SIZE 256
const static char* version = "1.0.0";
void help() {
  const char* commands[5][3] = {
    {"--help", "-h", "Lists all available commands"},
    {"--setup", "-s", "Prompts you with questions and mounts ram"},
    {"--mount <Name> <Size> <Path>", "-M", "Manually sets up mounting the ram"},
    {"--umount <Path>", "-u", "Unmounts the Ram Directory (Must be mounted first)"},
    {"--version", "-v", "Shows the version"},
  };
  for (int i = 0; i < 4; i++) {
    printf("%s %5s %10s\n", commands[i][0], commands[i][1], commands[i][2]); // Prints from commands
  }
 
}

char* removeNL(char *var) {
  if ((strlen(var) > 0) && (var[strlen (var) - 1] == '\n'))
        var[strlen (var) - 1] = '\0';
  
  return var;
}

int mountRam(char* name, char* path, char* size) { // this doesnt really look like good coding
  if (name == NULL) {
    printf("[ERROR] You must enter in a mount name.");
    return 0;
  } 
  if (size == NULL) {
    printf("[ERROR] You must enter in the size.");
    return 0;
  }
  if (path == NULL) {
    printf("[ERROR] You must enter in the mounting point (Path).");
    return 0;
  }
  //FILE* status = fopen( "/proc/meminfo", "r" );
  //if (status == NULL) printf("[ERROR] Cannot open /proc");
  
  char data[32];
  int len;
  len = snprintf(data, sizeof(data), "size=%s,uid=0,gid=0,mode=777", size);
  if (len <= sizeof(data)) {
    if (mount(name, path, "tmpfs", MS_RELATIME, data)) {
      if (errno == EBUSY) {
        perror("\n[ERROR] Cannot mount: Busy\n");
      } else {
        printf("\n[ERROR] Cannot mount: %s\n", strerror(errno));
      }
    } else {
      printf("Successfully mounted!\n");
      return 1;
    }
  }
  return 0;
}

void setup() {
  char *name = malloc(MAX_SIZE), *path = malloc(MAX_SIZE), *size = malloc(MAX_SIZE);
  // Name
  printf("\nPlease insert the mount name (No spaces): "); // rammount
  fgets(name, MAX_SIZE, stdin);

  printf("\nPlease insert the path (Ex: /mnt/ram): "); // /mnt/ram
  fgets(path, MAX_SIZE, stdin);

  printf("\nPlease enter in the size (Ex: 1G): "); // 1G
  fgets(size, MAX_SIZE, stdin);

  name = removeNL(name);
  path = removeNL(path);
  size = removeNL(size);
  mountRam(name, path, size);
  
};

void unmount(char* path) {
  if (umount(path)) {
    if (errno == EBUSY) {
      perror("\n[ERROR] Cannot umount: Busy\n");
    } else {
      printf("\n[ERROR] Cannot umount: %s\n", strerror(errno));
    }
  } else {
    printf("Successfully unmounted \"%s\"\n", path);
  }
}

void handleOpt(char* arg[], int input) {
  switch(input) {
    case 'h': printf("usage: %s [OPTION]\n", arg[0]); help(); break;
    case 'v': printf("MountRam %s\n", version); break;
    case 's': setup(); break;
    case 'M': mountRam(arg[2], arg[4], arg[3]); break;
    case 'u': unmount(arg[2]); break;
  }
}

int main(int argc, char* argv[]) {
  int opt;
  const struct option long_options[] = {
      {"help", 0, NULL, 'h'},
      {"version", 0, NULL, 'v'},
      {"mount", 3, NULL, 'M'},
      {"setup", 0, NULL, 's'},
      {"umount", 1, NULL, 'u'},
      {NULL, 0, NULL, 0}
  };
  while ((opt = getopt_long(argc, argv, "h:v:M:s:u:", long_options, NULL)) != -1) {
      switch (opt) {
        case 'h':
        case 'v':
        case 's':
        case 'u':
        case 'M': handleOpt(argv, opt); break;
        default:
            fprintf(stderr, "Try using '%s [--help]' for help.\n", argv[0]); // Only triggered if entered value not in switch
            exit(EXIT_FAILURE);
      }
      return 1;
  }
  handleOpt(argv, 'h');
  return 0;
}