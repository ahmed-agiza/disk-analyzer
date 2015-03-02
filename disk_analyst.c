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


#define FLAG_SHOW_INODE 1
#define FLAG_RECURSE_MASK 2
#define FLAG_SHOW_BLOCKS 4
#define FLAG_SHOW_SIZE 8
#define FLAG_SHOW_DIRECTORY 16
#define FLAG_SHOW_ALL_FILES 32
#define FLAG_SHOW_ALL_ATTRS 64
#define FLAG_SHOW_FILE_TYPE 128
#define FLAG_SHOW_LINKS 256
#define FLAG_SHOW_OWNER 512
#define FLAG_SHOW_HUMAN_FORMAT 1024

typedef enum {BLOCK_DEVICE, CHARACTER_DEVICE, DIRECTORY, FIFO_PIPE, SYMLINK, REGULAR_FILE, SOCKET, UNKNOWN} FILE_TYPE;

struct file_stat{
  char name[256];
  FILE_TYPE type;
  long inode;
  long links;
  char user[64];
  char group[64];
  long long size;
  long long total_size;
  long long number_of_blocks;
};

int stat_file(char *path, char *name, struct file_stat *stat_buf, int flags);
void print_stat(struct file_stat *st, int flags);
long long get_dir_size(char *r_dir);
int get_human_format(long long number, char *format);


int main(int argc, char **argv){
	char *dir;
  char full_path[512], h_format[10];
  DIR *dir_d;
  struct dirent *dir_inode;
  struct stat buf;
  int stat, fd, flags = 0, opt, argv_count = 0, i;
  struct file_stat stat_buf;
  long long total_size = 0;

  for(i = 1; i < argc; i++)
    if(argv[i][0] != '-')
      argv_count++;

  while ((opt = getopt(argc, argv, "irbsdaAtloh")) != -1) {
      switch (opt) {
        case 'i':
          flags |= FLAG_SHOW_INODE;
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
        case 'h':
          flags |= FLAG_SHOW_HUMAN_FORMAT;
          break;   
        default:
           fprintf(stderr, "Usage: %s [-option] <path>\n", argv[0]);
           exit(EXIT_FAILURE);
      }
  }

  if (argv_count > 1){
    fprintf(stderr, "Usage: %s [-option] <path>\n", argv[0]);
    exit(1);
  }else if (argv_count == 0)
    dir = "/";
  else
    dir = argv[optind];

  if(strcmp(dir, ".") != 0 && strcmp(dir, "..") != 0){
      
      if ((fd=open(dir, O_RDONLY)) < 0){
        fprintf(stderr, "Cannot open %s or does not exist\n", dir);
      }

      if (fstat(fd, &buf) == -1) {
               perror("stat");
      }

      close(fd);
      total_size = (long long) buf.st_size;
      
  }

  if((dir_d = opendir(dir)) == NULL){
    perror("opendir");
    exit(1);
  }



  while((dir_inode = readdir(dir_d)) != NULL){

    if(dir_inode->d_name[0] != '.' || (flags & FLAG_SHOW_ALL_FILES)){
      

      if(stat_file(dir, dir_inode->d_name, &stat_buf, flags) != 0){
        sprintf(full_path, "Stat error while opening %s%s", dir, dir_inode->d_name);
        perror(full_path);
      }else{
        print_stat(&stat_buf, flags);
        total_size += stat_buf.total_size;
      }
        
    }
  }

  if (flags & FLAG_SHOW_HUMAN_FORMAT){
      get_human_format(total_size, h_format);
      printf("Total directory size: %s\n", h_format);
  }else{
      printf("Total directory size: %lldB\n", total_size);
  }

  closedir(dir_d);  
  
  return 0;

}

int stat_file(char *path, char *name, struct file_stat *stat_buf, int flags){
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
 stat_buf->total_size = (long long) buf.st_size;
 if (((flags & FLAG_RECURSE_MASK) || (flags & FLAG_SHOW_ALL_ATTRS)) && stat_buf->type == DIRECTORY){
   // printf("Recursing: %s\n", full_path);
    stat_buf->total_size += get_dir_size(full_path);
 }
 
 stat_buf->number_of_blocks = (long long) buf.st_blocks;

 return close(fd);
}

void print_stat(struct file_stat *st, int flags){
  char h_format[10];
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
   if(flags & FLAG_SHOW_INODE || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%8ld ", st->inode);
   if(flags & FLAG_SHOW_LINKS || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%8ld ", st->links);
   if(flags & FLAG_SHOW_LINKS || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%8ld  ", st->links);
   if(flags & FLAG_SHOW_OWNER || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%4s:%4s  ", st->user, st->group);
   if(flags & FLAG_SHOW_SIZE || flags & FLAG_SHOW_ALL_ATTRS){
      if (flags & FLAG_SHOW_HUMAN_FORMAT){
        get_human_format(st->size, h_format);
        printf("%s ", h_format);
      }else
        printf("%lldB  ", st->size);
      
   }
   if(flags & FLAG_RECURSE_MASK || flags & FLAG_SHOW_ALL_ATTRS){
      if (flags & FLAG_SHOW_HUMAN_FORMAT){
        get_human_format(st->total_size, h_format);
        printf("%s ", h_format);
      }else
         printf("%lldB  ", st->total_size);
      
   }
   if(flags & FLAG_SHOW_BLOCKS || flags & FLAG_SHOW_ALL_ATTRS)
      printf("%5lldb ", st->number_of_blocks);
   printf("%s \n", st->name);
}

long long get_dir_size(char *r_dir){
  DIR *dir_d;
  struct dirent *dir_inode;
  int fd;
  struct stat buf;
  char full_path[256];
  long long total_size = 0;

  if (r_dir[strlen(r_dir) - 1] != '/')
    strcat(r_dir, "/");

  if((dir_d = opendir(r_dir)) == NULL){
    perror("opendir");
    printf("%s\n", r_dir);
    return 0;
  }


  while((dir_inode = readdir(dir_d)) != NULL){
    if(strcmp(dir_inode->d_name, ".") != 0 && strcmp(dir_inode->d_name, "..") != 0){    
      strcpy(full_path, r_dir);
      strcat(full_path, dir_inode->d_name);
      if ((fd=open(full_path, O_RDONLY)) < 0){
        perror("Opening Error");
        printf("%s\n", full_path);
            continue;
      }
      if (fstat(fd, &buf) == -1) {
                perror("stat");
                continue;
        }
        close(fd);
        total_size += (long long) buf.st_size;
        if(buf.st_mode & S_IFMT & S_IFDIR){
            total_size += get_dir_size(full_path);
        }
    }
    }

  closedir(dir_d);
  return total_size;
}

int get_human_format(long long number, char *format){
  if (number <= 1000){
    sprintf(format, "%lldB", number);
  }else if (number <= 1000000){
    sprintf(format, "%1.1fKBs", (float)number / 1000.0);
  }else if(number <= 1000000000){
    sprintf(format, "%1.1fMBs", (float)number / 1000000.0);
  }else{
    sprintf(format, "%1.1fGBs", (float)number / 1000000000.0);
  }
}


