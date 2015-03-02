#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>


#define BUFF_SIZE 100


#define FLAG_SHOW_INDOE 1
#define FLAG_RECURSE_MASK 2
#define FLAG_SHOW_BLOCKS 4
#define FLAG_SHOW_SIZE 8
#define FLAG_SHOW_DIRECTORY 16
#define FLAG_SHOW_ALL_FILES 32
#define FLAG_SHOW_ALL_ATTRS 64
#define FLAG_SHOW_FILE_TYPE 128
#define FLAG_SHOW_LINKS 256
#define FLAG_SHOW_OWNER 512

typedef enum {BLOCK_DEVICE, CHARACTER_DEVICE, DIRECTORY, FIFO_PIPE, SYMLINK, REGULAR_FILE, SOCKET, UNKNOWN} FILE_TYPE;

struct file_stat{
  char name[256];
  FILE_TYPE type;
  long inode;
  long links;
  char user[64];
  char group[64];
  long long size;
  long long number_of_blocks;
};

int stat_file(char *path, char *name, struct file_stat *stat_buf);
void print_stat(struct file_stat *st, int flags);


int main(int argc, char **argv){
	char *dir;
  DIR *dir_d;
  struct dirent *dir_inode;
  int stat;
  struct file_stat stat_buf;
  //Options:
  int flags = 0;
  int opt;

  int argv_count = 0;
  char full_path[512];

  int i;
  for(i = 1; i < argc; i++)
    if(argv[i][0] != '-')
      argv_count++;

  while ((opt = getopt(argc, argv, "irbsdaAtlo")) != -1) {
      switch (opt) {
        case 'i':
          flags |= FLAG_SHOW_INDOE;
          break;
        case 'r':
          flags |= FLAG_RECURSE_MASK;
          break;
        case 'b':
          flags |= FLAG_SHOW_BLOCKS;
          break;
        case 's':
          flags |= FLAG_SHOW_SIZE;
          break;
        case 'd':
          flags |= FLAG_SHOW_DIRECTORY;
          break;
        case 'a':
          flags |= FLAG_SHOW_ALL_FILES;
          break;
        case 'A':
          flags |= FLAG_SHOW_ALL_ATTRS;
          break;
        case 't':
          flags |= FLAG_SHOW_FILE_TYPE;
          break;
        case 'l':
          flags |= FLAG_SHOW_LINKS;
          break;   
        case 'o':
          flags |= FLAG_SHOW_OWNER;
          break;   
        default:
           fprintf(stderr, "Usage: %s [-option] <path>\n", argv[0]);
           exit(EXIT_FAILURE);
      }
  }

  if (argv_count > 1){
    fprintf(stderr, "Usage: %s [-option] <path>\n", argv[0]);
    exit(1);
  }else if (argv_count == 1)
    dir = "/";
  else
    dir = argv[optind];

  
  if((dir_d = opendir(dir)) == NULL){
    perror("opendir");
    exit(1);
  }

  while((dir_inode = readdir(dir_d)) != NULL){

    if(dir_inode->d_name[0] != '.' || (flags & FLAG_SHOW_ALL_FILES)){
      

      if(stat_file(dir, dir_inode->d_name, &stat_buf) != 0){
        sprintf(full_path, "Stat error while opening %s%s", dir, dir_inode->d_name);
        perror(full_path);
      }else
        print_stat(&stat_buf, flags);

    }
  }

  closedir(dir_d);  
  
  return 0;

}

int stat_file(char *path, char *name, struct file_stat *stat_buf){
  int fd;
  struct stat buf;
  char full_path[512];

  if (path[strlen(path) - 1] != '/')
    strcat(path, "/");

  sprintf(full_path, "%s%s", path, name);

  if ((fd=open(full_path, O_RDONLY)) < 0){
     return -1;
  }

  if (stat(full_path, &buf) == -1) {
    return -1;
  }

 strcpy(stat_buf->name, name);
 switch (buf.st_mode & S_IFMT) {
   case S_IFBLK: stat_buf->type = BLOCK_DEVICE;   break;
   case S_IFCHR: stat_buf->type = CHARACTER_DEVICE;  break;
   case S_IFDIR: stat_buf->type = DIRECTORY;   break;
   case S_IFIFO: stat_buf->type = FIFO_PIPE; break;
   case S_IFLNK: stat_buf->type = SYMLINK;   break;
   case S_IFREG: stat_buf->type = REGULAR_FILE;   break;
   case S_IFSOCK: stat_buf->type = SOCKET;   break;
   default:  stat_buf->type = UNKNOWN;  break;
 }

 stat_buf->inode = (long)buf.st_ino;
 stat_buf->links = (long) buf.st_nlink;
 strcpy(stat_buf->user, getpwuid(buf.st_uid)->pw_name);
 strcpy(stat_buf->group, getgrgid(buf.st_gid)->gr_name);
 stat_buf->size = (long long) buf.st_size;
 stat_buf->number_of_blocks = (long long) buf.st_blocks;

 return close(fd);
}

void print_stat(struct file_stat *st, int flags){
  if(flags & FLAG_SHOW_FILE_TYPE || flags & FLAG_SHOW_ALL_ATTRS)
    switch (st->type) {
     case BLOCK_DEVICE:  printf("b ");   break;
     case CHARACTER_DEVICE:  printf("c ");   break;
     case DIRECTORY:  printf("d ");   break;
     case FIFO_PIPE:  printf("p ");   break;
     case SYMLINK:  printf("l ");   break;
     case REGULAR_FILE:  printf("f ");   break;
     case SOCKET: printf("s ");   break;
     default:       printf("- ");   break;
   }
   if(flags & FLAG_SHOW_INDOE || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%8ld ", st->inode);
   if(flags & FLAG_SHOW_LINKS || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%8ld ", st->links);
   if(flags & FLAG_SHOW_LINKS || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%8ld  ", st->links);
   if(flags & FLAG_SHOW_OWNER || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%4s:%4s  ", st->user, st->group);
   if(flags & FLAG_SHOW_SIZE || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%5lldb ", st->size);
   if(flags & FLAG_SHOW_BLOCKS || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%5lldb ", st->number_of_blocks);
   printf("%s \n", st->name);
}



