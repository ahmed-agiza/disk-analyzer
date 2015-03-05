#ifndef FILE_ANALYZER_H
#define FILE_ANALYZER_H

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

#include <QList>


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

#define MAX_NAME_SIZE 256
#define MAX_USER_SIZE 64
#define MAX_GROUP_SIZE 64
#define MAX_FULL_PATH_SIZE 512

typedef enum {BLOCK_DEVICE, CHARACTER_DEVICE, DIRECTORY, FIFO_PIPE, SYMLINK, REGULAR_FILE, SOCKET, UNKNOWN} FILE_TYPE;

struct file_stat{
    char name[MAX_NAME_SIZE];
    char directory[MAX_FULL_PATH_SIZE];
    FILE_TYPE type;
    long inode;
    long links;
    char user[MAX_USER_SIZE];
    char group[MAX_GROUP_SIZE];
    long long size;
    long long total_size;
    long long number_of_blocks;
    int depth;
};

QList<file_stat> stat_file(char *path, char *name, struct file_stat *stat_buf, int flags, int *return_code, int level);
void print_stat(struct file_stat *st, int flags);
long long get_dir_size(char *r_dir, QList<file_stat>&, int level);
int get_human_format(long long number, char *format);
QList<file_stat> analyze_directory(file_stat * = 0, char* = "/", int = FLAG_RECURSE_MASK, int* = 0);

QList<file_stat> analyze_directory(file_stat *dir_buf, char *dir, int flags, int *return_code){
    QList<file_stat> fileStatsList;
    char full_path[MAX_FULL_PATH_SIZE], h_format[10];
    DIR *dir_d;
    struct dirent *dir_inode;
    struct stat buf;
    int fd;
    struct file_stat stat_buf;

    if(strcmp(dir, ".") != 0 && strcmp(dir, "..") != 0){

        if ((fd=open(dir, O_RDONLY)) < 0){
            fprintf(stderr, "Cannot open %s or does not exist\n", dir);
            *return_code = -1;
            return fileStatsList;
        }

        if (fstat(fd, &buf) == -1) {
            perror("stat");
            *return_code = -1;
            return fileStatsList;
        }

        close(fd);
        strcpy(dir_buf->name, dir);
        switch (buf.st_mode & S_IFMT) {
            case S_IFBLK: dir_buf->type = BLOCK_DEVICE;   break;
            case S_IFCHR: dir_buf->type = CHARACTER_DEVICE;  break;
            case S_IFDIR: dir_buf->type = DIRECTORY;   break;
            case S_IFIFO: dir_buf->type = FIFO_PIPE; break;
            case S_IFLNK: dir_buf->type = SYMLINK;   break;
            case S_IFREG: dir_buf->type = REGULAR_FILE;   break;
            case S_IFSOCK: dir_buf->type = SOCKET;   break;
            default:  dir_buf->type = UNKNOWN;  break;
        }

        dir_buf->inode = (long)buf.st_ino;
        dir_buf->links = (long) buf.st_nlink;
        strcpy(dir_buf->user, getpwuid(buf.st_uid)->pw_name);
        strcpy(dir_buf->group, getgrgid(buf.st_gid)->gr_name);
        dir_buf->size = (long long) buf.st_size;
        dir_buf->total_size = (long long) buf.st_size;
        dir_buf->depth = 0;
        dir_buf->number_of_blocks = (long long) buf.st_blocks;
    }

    if((dir_d = opendir(dir)) == NULL){
        perror("opendir");
        *return_code = -1;
        return fileStatsList;
    }



    while((dir_inode = readdir(dir_d)) != NULL){

        if(dir_inode->d_name[0] != '.' || (flags & FLAG_SHOW_ALL_FILES)){
            int return_code = 7;
            QList<file_stat> childFileStatsList = stat_file(dir, dir_inode->d_name, &stat_buf, flags, &return_code, 1);
            if(return_code != 0){
                fprintf(stderr, "Stat error %d\n%s %s\n", return_code, dir, dir_inode->d_name);
            }else{
                //print_stat(&stat_buf, flags);
                fileStatsList.append(stat_buf);
                fileStatsList.append(childFileStatsList);
                dir_buf->total_size += stat_buf.total_size;
            }

        }
    }

    if (flags & FLAG_SHOW_HUMAN_FORMAT){
        get_human_format(dir_buf->total_size, h_format);
        printf("Total directory size: %s\n", h_format);
    }else{
        printf("Total directory size: %lldB\n", dir_buf->total_size);
    }

    closedir(dir_d);
    *return_code = 0;
    return fileStatsList;
}



QList<file_stat> stat_file(char *path, char *name, struct file_stat *stat_buf, int flags, int *return_code, int level){
    int fd;
    struct stat buf;
    char full_path[MAX_FULL_PATH_SIZE];
    QList<file_stat> childFileStatsList;

    if (path[strlen(path) - 1] != '/')
        strcat(path, "/");

    sprintf(full_path, "%s%s", path, name);

    if ((fd=open(full_path, O_RDONLY)) < 0){
        perror("Open error");
        *return_code = -1;
        return childFileStatsList;
    }

    if (stat(full_path, &buf) == -1) {
        *return_code = -1;
        perror("Stat syscall error");
        return childFileStatsList;
    }

    strcpy(stat_buf->name, name);
    strcpy(stat_buf->directory, path);
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
        stat_buf->total_size += get_dir_size(full_path, childFileStatsList, level + 1);
    }

    stat_buf->number_of_blocks = (long long) buf.st_blocks;
    stat_buf->depth = level;

   close(fd);
   *return_code = 0;
   return childFileStatsList;
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

long long get_dir_size(char *r_dir, QList<file_stat> &childFileStatsList, int level){
    DIR *dir_d;
    struct dirent *dir_inode;
    file_stat stat_buf;
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

            int return_code;
            stat_file(r_dir, dir_inode->d_name, &stat_buf, 0, &return_code, level);
            if(return_code != 0){
                fprintf(stderr, "Stat error %d", return_code);
            }else{
                childFileStatsList.append(stat_buf);
            }

            total_size += stat_buf.size;
            if(stat_buf.type == DIRECTORY){
                sprintf(full_path, "%s%s", r_dir, dir_inode->d_name);
                total_size += get_dir_size(full_path, childFileStatsList, level + 1);
            }
        }
    }

    closedir(dir_d);
    return total_size;
}

int get_human_format(long long number, char *format){
    if (number <= 1000){
        return sprintf(format, "%lldB", number);
    }else if (number <= 1000000){
        return sprintf(format, "%1.1fKBs", (float)number / 1000.0);
    }else if(number <= 1000000000){
        return sprintf(format, "%1.1fMBs", (float)number / 1000000.0);
    }else{
        return sprintf(format, "%1.1fGBs", (float)number / 1000000000.0);
    }
}



#endif // FILE_ANALYZER_H
