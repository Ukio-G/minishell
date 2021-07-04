# Документация с примерами:


## Readline GNU library
### readline
```c
char *readline(char *prompt)
```
Читает со стандартного ввода нажатия до нажатия enter, записывает в буффер `rl_line_buffer`

### rl_on_new_line
### rl_replace_line,
### rl_redisplay
### add_history
### fork
### wait
### waitpid
### wait3
### wait4
### signal
### kill
### exit
### getcwd
```c
/* Signature */
char * getcwd(char *buf, size_t size);

int main()
{
	char buffer[512];
	getcwd(buffer, 512);
	/* buffer теперь содержит путь до программы, которая была запущена */
}
```
Копирует абсолютный путь до текущего рабочего каталога в буффер `buf`, который не превышает размер `size`

### chdir

## Получения информации о доступе к файлам

Функции `stat`, `lstat`, `fstat` заполняют следующую структуру:

```c
struct stat { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
    dev_t    st_dev;    /* device inode resides on */
    ino_t    st_ino;    /* inode's number */
    mode_t   st_mode;   /* inode protection mode */
    nlink_t  st_nlink;  /* number of hard links to the file */
    uid_t    st_uid;    /* user-id of owner */
    gid_t    st_gid;    /* group-id of owner */
    dev_t    st_rdev;   /* device type, for special file inode */
    struct timespec st_atimespec;  /* time of last access */
    struct timespec st_mtimespec;  /* time of last data modification */
    struct timespec st_ctimespec;  /* time of last file status change */
    off_t    st_size;   /* file size, in bytes */
    quad_t   st_blocks; /* blocks allocated for file */
    u_long   st_blksize;/* optimal file sys I/O ops blocksize */
    u_long   st_flags;  /* user defined flags for file */
    u_long   st_gen;    /* file generation number */
};

	/* Значение поля st_mode можно расшифровать
	 * Используя побитовые операции с константами: */

#define S_IFMT 0170000           /* type of file */
#define        S_IFIFO  0010000  /* named pipe (fifo) */
#define        S_IFCHR  0020000  /* character special */
#define        S_IFDIR  0040000  /* directory */
#define        S_IFBLK  0060000  /* block special */
#define        S_IFREG  0100000  /* regular */
#define        S_IFLNK  0120000  /* symbolic link */
#define        S_IFSOCK 0140000  /* socket */
#define        S_IFWHT  0160000  /* whiteout */
#define S_ISUID 0004000  /* set user id on execution */
#define S_ISGID 0002000  /* set group id on execution */
#define S_ISVTX 0001000  /* save swapped text even after use */
#define S_IRUSR 0000400  /* read permission, owner */
#define S_IWUSR 0000200  /* write permission, owner */
#define S_IXUSR 0000100  /* execute/search permission, owner */
```

### stat
```c
#include <sys/stat.h>
int stat(const char *restrict path, struct stat *restrict buf);
```
Сбор информации о файле, на который указывает `path`. Допустимо не иметь прав на чтение, однако файл и промежуточные каталоги должны существовать.

`path` может быть как абсолютным, так и относительным.

Если `path` указывает на симлинк — то будет выведена информация о файле, на который указывает симлинк. 

Узнать размер, права доступа и тип к некоторого файла:

```c
#include <stdio.h>
#include <sys/stat.h>

void print_size(struct stat *s, char *filename)
{
	printf("Size of file %s: %lli bytes, %lli blocks\n", filename, s->st_size, s->st_blocks);
}

void print_permissions(struct stat *s, char *filename)
{
	/* Для владельца, группы владельца и для всех остальных */
	/* могут быть права на чтение, запись и выполнение (rwx соответственно) */
	mode_t mode = s->st_mode;

	printf("mode value of file %s: (octal) %#o\n", filename, mode);
	// Other
	printf("All: %c%c%c\n", (mode & 01) ? 'x' : '-', (mode & 02) ? 'w' : '-', (mode & 04) ? 'r' : '-');
	// Group
	printf("Group: %c%c%c\n", (mode & 010) ? 'x' : '-', (mode & 020) ? 'w' : '-', (mode & 040) ? 'r' : '-');
	// Owner
	printf("Owner: %c%c%c\n", (mode & 0100) ? 'x' : '-', (mode & 0200) ? 'w' : '-', (mode & 0400) ? 'r' : '-');
}

void print_file_type(struct stat *s, char *filename)
{
	/* В UNIX все - файл. В том числе и устройства, ссылки, пайпы, сокеты, каталоги... */
	/* Для каждого типа файла в структуре stat поле st_mode устанавливает определенное значение. */
	/*
	 *  1 = 1 = 1
	 *  1000 = 8 = 10
	 *  1000000 = 64 = 100
		#define        S_IFIFO  0010000   named pipe (fifo)
		#define        S_IFCHR  0020000   character special
		#define        S_IFDIR  0040000   directory
		#define        S_IFBLK  0060000   block special
		#define        S_IFREG  0100000   regular
		#define        S_IFLNK  0120000   symbolic link
		#define        S_IFSOCK 0140000   socket
		#define        S_IFWHT  0160000   whiteout
	*/

	printf("File %s is ", filename);
	
	/* Занулить биты, которые не относятся к типу файла */
	mode_t mode = (s->st_mode >> (3 * 4)) << (3 * 4);
	
	if (mode == S_IFIFO)
		printf("Pipe");
	if (mode == S_IFCHR)
		printf("Char device");
	if (mode == S_IFDIR)
		printf("Directory");
	if (mode == S_IFBLK)
		printf("Block device");
	if (mode == S_IFREG)
		printf("Regular file");
	if (mode == S_IFLNK)
		printf("Symlink");
	if (mode == S_IFSOCK)
		printf("Socket");
	printf("\n");
}

int main(int argc, char **argv)
{

	struct stat s;
	char *filename = argv[1];
	stat(filename, &s);
	print_size(&s, filename);
	print_permissions(&s, filename);
	print_file_type(&s, filename);
	return 0;
}
```

### lstat

```c
#include <sys/stat.h>
int lstat(const char *restrict path, struct stat *restrict buf);
```


### fstat
### unlink
### execve
### dup
### dup2
### pipe
### opendir
### readdir
### closedir
### strerror
### errno
### isatty
### ttyname
### ttyslot
### ioctl
### getenv
### tcsetattr
### tcgetattr
### tgetent
### tgetflag
### tgetnum
### tgetstr
### tgoto
### tputs
