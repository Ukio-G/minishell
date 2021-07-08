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
```c
int main(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("Hello from the child process!\n");
        _exit(EXIT_SUCCESS);
    }
    else {
        int status;
        (void)waitpid(pid, &status, 0);
    }
    return EXIT_SUCCESS;
}
```
Системный вызов Fork используется для создания нового процесса, который называется дочерним процессом, который выполняется одновременно с процессом, вызывающим fork () (родительский процесс). После создания нового дочернего процесса оба процесса выполнят следующую инструкцию, следующую за системным вызовом fork ().
После fork() процесс-потомок чаще всего выполняет системный вызов exec(), загружающий в пространство процесса новую программу (именно так, и только так, в Unix-системе выполняется запуск программы в отдельном процессе). Так, первый (нулевой) процесс Unix (ядро системы) создаёт свою копию, чтобы запустить init (процесс с PID = 1), который в свою очередь создаёт дочерние процессы для запуска инициализации системы и терминалов.

Родительский процесс может либо продолжить выполнение, либо дождаться завершения дочернего процесса. Ребенок, обнаружив, что это ребенок, полностью заменяет себя другой программой, так что код и адресное пространство исходной программы теряются.

Если родитель решит дождаться смерти ребенка, он получит код выхода программы, которую выполнил ребенок. Чтобы предотвратить превращение ребенка в зомби, родитель должен вызывать своих дочерних элементов в ожидании либо периодически, либо после получения сигнала SIGCHLD, который указывает на завершение дочернего процесса.
### wait
### waitpid
```c
#include <sys/types.h>
#include <sys/wait.h>

       pid_t wait(int *status);
       pid_t waitpid(pid_t pid, int *status, int options);

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main()
{
    pid_t cpid;
    if (fork()== 0)
        exit(0);           /* terminate child */
    else
        cpid = wait(NULL); /* reaping parent */
    printf("Parent pid = %d\n", getpid());
    printf("Child pid = %d\n", cpid);
    
    return 0;
}
```

```c
// C program to demonstrate waitpid()
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

void waitexample()
{
    int i, stat;
    pid_t pid[5];
    for (i=0; i<5; i++)
    {
        if ((pid[i] = fork()) == 0)
        {
        sleep(1);
        exit(100 + i);
        }
    }

    // Using waitpid() and printing exit status
    // of children.
    for (i=0; i<5; i++)
    {
        pid_t cpid = waitpid(pid[i], &stat, 0);
        if (WIFEXITED(stat))
            printf("Child %d terminated with status: %d\n", cpid, WEXITSTATUS(stat));
    }
}

// Driver code
int main()
{
    waitexample();
    return 0;
}

```

`wait`, `waitpid` - ожидает завершения процесса.
Функция  `wait`  приостанавливает  выполнение  текущего  процесса  до тех пор, пока дочерний
процесс не прекратит выполнение или до появления сигнала, который либо  завершает  текущий
процесс,  либо требует вызвать функцию-обработчик.  Если дочерний процесс к моменту вызова
функции уже завершился (так  называемый  "зомби"),  то  функция  немедленно  возвращается.
Системные ресурсы, связанные с дочерним процессом, освобождаются.

Функция  `waitpid`  приостанавливает  выполнение текущего процесса до тех пор, пока дочерний
процесс, указанный в параметре `pid`, не завершит выполнение, или пока не  появится  сигнал,
который  либо  завершает  текущий  процесс  либо требует вызвать функцию-обработчик.  Если
указанный дочерний процесс  к  моменту  вызова  функции  уже  завершился  (так  называемый
"зомби"),  то  функция  немедленно  возвращается.  Системные ресурсы, связанные с дочерним
процессом, освобождаются.
Параметр `pid` может принимать несколько значений:

- **меньше -1** означает, что нужно ждать  любого  дочернего  процесса,  чей  идентификатор  группы
процессов равен абсолютному значению pid.
- **-1** означает ожидать любого дочернего процесса; функция wait ведет себя точно так же.
- **0** означает  ожидать  любого  дочернего  процесса,  чей идентификатор группы процессов
равен таковому у текущего процесса.
- **больше 0** означает ожидать дочернего процесса, чем идентификатор равен pid. 
 Значение options создается путем битовой операции ИЛИ над следующими константами:

`WNOHANG`
означает вернуть управление немедленно, если ни один дочерний процесс  не  завершил
выполнение.
       
`WUNTRACED`
означает  возвращать  управление также для остановленных дочерних процессов, о чьем
статусе еще не было сообщено.
Если status не равен `NULL`, то функции `wait` и `waitpid`  сохраняют  информацию  о  статусе  в
переменной, на которую указывает `status`.
Этот  статус  можно исследовать с помощью нижеследующих макросов (они принимают в качестве
аргумента буфер (типа int), — а не указатель на буфер!):
      
- `WIFEXITED(status)`
              не равно нулю, если дочерний процесс нормально завершился.
       
- `WEXITSTATUS(status)`
              возвращает восемь младших битов  возвращаемого  значения  завершившегося  дочернего
              процесса.   Эти  биты  могли  быть  установлены  в  аргументе  функции `exit()` или в
              аргументе оператора `return` в  функции  `main()`.   Этот  макрос  можно  использовать,
              только если `WIFEXITED` вернул ненулевое значение.
       
- `WIFSIGNALED(status)`
              возвращает    истинное   значение,   если   дочерний   процесс   завершился   из-за
              неперехваченного сигнала.
       
- `WTERMSIG(status)`
              возвращает номер сигнала, который привел к  завершению  дочернего  процесса.   Этот
              макрос можно использовать только если `WIFSIGNALED` вернул ненулевое значение.
       
- `WIFSTOPPED(status)`
              возвращает истинное значение, если дочерний процесс, из-за которого функция вернула
              управление, в настоящий момент остановлен; это возможно только  если  использовался
              флаг `WUNTRACED`.
       
- `WSTOPSIG(status)`
              возвращает  номер  сигнала,  из-за  которого дочерний процесс был остановлен.  Этот
              макрос можно использовать только если `WIFSTOPPED` вернул ненулевое значение.

Возвращаемое значение.
Идентификатор дочернего процесса, который завершил выполнение,  -1  в  случае  ошибки  или
нуль,  если  использовался `WNOHANG`, но ни один дочерний процесс еще не завершил выполнение
(в этом случае errno устанавливается должным образом).

### wait3, wait4
```c
#include <sys/types.h>
       #include <sys/time.h>
       #include <sys/resource.h>
       #include <sys/wait.h>

       pid_t wait3(int *wstatus, int options,
                   struct rusage *rusage);

       pid_t wait4(pid_t pid, int *wstatus, int options,
                   struct rusage *rusage);
```
Системные вызовы `wait3` и `wait4` аналогичны `waitpid`, но дополнительно возвращают информацию об использовании ресурсов дочернего элемента в структуре, на которую указывает `rusage`.
Структура `rusage` определяется следующим образом:
```c
struct rusage {
    struct timeval  ru_utime;    /* user time used */
    struct timeval  ru_stime;    /* system time used */
    long ru_maxrss;   /* max resident set size */
    long ru_ixrss;    /* integral shared memory size */
    long ru_idrss;    /* integral unshared data " */
    long ru_isrss;    /* integral unshared stack " */
    long ru_minflt;   /* page reclaims */
    long ru_majflt;   /* page faults */
    long ru_nswap;    /* swaps */
    long ru_inblock;  /* block input operations */
    long ru_oublock;  /* block output operations */
    long ru_msgsnd;   /* messages sent */
    long ru_msgrcv;   /* messages received */
    long ru_nsignals; /* signals received */
    long ru_nvcsw;    /* voluntary context switches */
    long ru_nivcsw;   /* involuntary " */
};
```

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

## Получение информации о доступе к файлам

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

#### Пример кода:
Узнать размер, права доступа и тип некоторого файла:

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
Работает и заполняет ту же самую структуру, что и stat, но в случае, если `path` указывает на символическую ссылку возвращает данные о самой ссылке, а не о файле, на который ссылается ссылка

### fstat

```c
#include <sys/stat.h>
int fstat(int filedes, struct stat *restrict buf);
```
Работает и заполняет ту же самую структуру, что и stat, но в качестве первого аргумента принимает не путь до файла, а файловый дескриптор


### unlink
### execve
```c
#include <process.h>
#include <errno.h>    /* Только для контроля ошибок */
int execve(const char * name, const char *argv[], const char *envp[]);
```
`exec` - функции  создают  и выполняют новый порожденный
процесс.  Успешное  выполнение  exec вызывает замену в
памяти родительского процесса на порожденный  процесс,
для которого должно быть достаточно памяти. `exec` пере-
записывает новую программу на место текущей и начинает
исполнение. 

`argv` - это массив указателей на строки, переданный новой программе в качестве аргументов командной строки. По соглашению первая из этих строк (т.е. `argv[0]`) должна содержать имя файла, связанного с исполняемым файлом. Массив `argv` должен заканчиваться указателем `NULL` (таким образом, в новой программе `argv[argc]` будет `NULL`.)

`envp` - это массив указателей на строки, обычно имеющий форму ключ = значение, которые передаются как среда новой программы. Массив `envp` должен заканчиваться указателем `NULL`.

`hello.c`:
```c
#include<stdio.h>
int main(int argc, char **argv, char **env)
{
    printf("%s %s\n", argv[0], argv[1]);
    int i = 0;
    while(env[i])
        printf("%s\n", env[i++]);
    return (0);
}
```

`execve.c`:
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char **argv, char **env)
{	
	char *temp[] = {"hello","world", NULL};
	execve("./hello", temp, env);
	printf("Error");
	return (0);
}
```

### dup
### dup2
### pipe
### opendir, readdir, closedir
```c
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
int closedir(DIR *dirp);
struct dirent *readdir(DIR *dirp);
```
Функция `opendir()` открывает директорию для чтения с именем name и возвращает указатель на directory stream (DIR structure), при ошибке возвращает `NULL`  и код ошибки `errno` устанавливается равной либо `ENOENT` (каталог не найден), либо `ENOMEM` (недостаточно памя­ти). Функция `closedir()` закрывает директорию. Функция `closedir()` в случае успеха возвращает 0 и —1 в противном случае. При неудаче переменная `errno` устанавливается равной `EBADF` (недействительный каталог).
Функция `readdir()` возвращает следующую структуру `dirent` считанную из файла-директории. При достижении конца списка файлов в директории или возникновении ошибки возвращает `NULL`. Директория сама по себе представляет файл состоящий из специальных записей `dirent`, которые содержат данные о файлах в директории:
```c
struct dirent {
  ino_t          d_ino;       /* inode number */
  off_t          d_off;       /* offset to the next dirent */
  unsigned short d_reclen;    /* length of this record */
  unsigned char  d_type;      /* type of file; not supported
                                 by all file system types */
  char           d_name[256]; /* filename */
};
```
Пример использования указанных функций:
```c
#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR * dir;
	struct dirent * dir_info;
	dir = opendir("/home/dinara/study/dir_example");

	while ((dir_info = readdir(dir)) != NULL) 
	{
        printf("%d - %s [%d] %d\n",
            dir_info->d_ino, dir_info->d_name, dir_info->d_type, dir_info->d_reclen);
    };    
    closedir(dir);
	return (0);
}
```
### strerror
```c
#include<stdio.h>

char *strerror(int num);
```
Функия `strerror` возвращает указатель на сообщение об ошибке, связанное с номером ошибки.
Пример использования:
```c
//Следующий фрагмент программы в случае ошибки выведет сообщение об ошибке, связанное с глобальной переменной errno:
if (errno) printf (strerror(errno));
```
### errno
`errno` – переменная, хранящая целочисленный код последней ошибки. В каждом потоке существует своя локальная версия `errno`, чем и обусловливается её безопасность в многопоточной среде. Обычно `errno` реализуется в виде макроса, разворачивающегося в вызов функции, возвращающей указатель на целочисленный буфер. При запуске программы значение `errno` равно нулю.
Пример использования `errno` и `strerror`
```c
#icnlude <stdio.h>
#include <errno.h>

int main(int argc, const char * argv[]) 
{
    // Generate unique filename.
    char *file_name = "file.c";

    errno = 0;
    FILE *file = fopen(file_name, "rb");
    // Save error number. 
    errno_t error_num = errno;
	
    if (file) {
        // Do something useful. 
        fclose(file);
    }
    else {
        char *errorbuf = strerror(error_num);
        fprintf(stderr, "Error message : %s\n", errorbuf);
    }
    
    return (0);
}
```
### isatty
```c
#include<unistd.h>
int isatty(int fd);
```
Функция `isatty()` возвращает ненулевое значение, если файловый дескриптор `fd` связан с символьным устройством, например, терминалом, консолью, принтером или последовательным портом; в противном случае она возвращает 0.
Пример использования:
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
	int fd = 0;
	if(isatty(fd))
	    printf ("is a character device");
	else 
	{
	    printf("is not a character device\n");
	    printf("%s\n", strerror(errno));
	}
  	return (0);
}
```
### ttyname
```c
#include <unistd.h>
char *ttyname(int fd);
```
Функция `ttyname` возвращает указатель на нультерминированную строку, содержащую имя терминала, ассоциированного с файловым дескриптором `fd` и `NULL`в случае ошибки (если файловый дескриптор не ассоциирован с терминалом)
Пример использования:
```c
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv)
{
	int fd = 1;
	if(isatty(fd)) 
	{
		printf ("is a character device\n");
		printf("terminal name is %s\n", ttyname(fd));
	}
	else 
	{
		printf("is not a character device\n");
		printf("%s\n", strerror(errno));
	}
  	return (0);
}
```
Результат работы программы:
```c
➜  test_path ./out                                                                                                                                                                                              
is a character device                                                                                                                                                                                           
terminal name is /dev/pts/1
➜  test_path 
```
### ttyslot
```c
#include <unistd.h>
int ttyslot(void);
```
Функция `ttyslot()` возвращает индекс текущей записи пользователя в некотором файле. 
### ioctl
```c
#include <sys/ioctl.h>
int ioctl(int fd, unsigned long request, ...);
```
Системный вызов `ioctl()` — это универсальное средство управления аппаратными устройствами. Первым аргументом функции является дескриптор файла того устройства, которым требуется управлять. Второй аргумент — это код запроса, обозначающего выполняемую операцию. Разным устройствам соответствуют разные запросы. В зависимости от запроса функции `ioctl()` могут потребоваться дополнительные аргументы.
Многие коды запросов перечислены на man-странице `ioctl_list`. При работе с функцией `ioctl()` нужно хорошо понимать, как работает драйвер соответствующего устройства.
Возвращает: 0 в случае успешного выполнения, -1 в случае ошибки. Пример использования (извлечение компакт-диска из устройства):
```c
#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
 /* Открытие файла устройства, указанного в командной строке. */
 int fd = open(argv[1], O_RDONLY);
 /* Извлечение компакт-диска из дисковода. */
 ioctl(fd, CDROMEJECT);
 /* Закрытие файла. */
 close(fd);
 return 0;
}
```
### getenv
```c
#include<stlib.h>
char *getenv(const char *name);
```
Функция `getenv()` возвращает указатель на информацию об окружении, ассоциированную со строкой `name` в таблице информации окружения. Возвращаемая строка ни в коем случае не должна быть изменена программой.
Окружение программы может включать такие вещи, как имена путей и устройств. Точное содержание этих данных определяется операционной системой.
Если функция вызвана с аргументом, который не соответствует никаким переменным окружения, то возвращается нулевой указатель.
Пример использования:
```c
#include<stdlib.h>
int main(int argc, char **argv)
{
    char *p = getenv("USER");
    if (p)
        printf("%s\n", p);
return (0);
}
```
### tcsetattr, tcgetattr
Тип `termios` — стандартный интерфейс, заданный стандартом POSIX и похожий на интерфейс `termio` системы System V. Интерфейс терминала управляется значениями в структуре типа termios и использует небольшой набор вызовов функций. И то и другое определено в заголовочном файле `termios.h`.
Значения, которые можно изменять для управления терминалом, разделены на группы, относящиеся к следующим режимам:

- ввод;

- вывод;

- управление;

- локальный (не поняла что это, еще посмотрю);

- специальные управляющие символы.

Минимальная структура типа `termios` обычно объявляется следующим образом (хотя в стандарте X/Open разрешено включение дополнительных полей):
```c
#include <termios.h>
struct termios {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_cc[NCCS];
};
```
Инициализировать структуру типа `termios` для терминала можно, вызвав функцию `tcgetattr` со следующим прототипом или описанием:
```c
#include <termios.h>
int tcgetattr(int fd, struct termios *termios_p);
```
Этот вызов записывает текущие значения переменных интерфейса терминала в структуру, на которую указывает параметр `termios_p`. Если впоследствии эти значения будут изменены, вы сможете перенастроить интерфейс терминала с помощью функции tcsetattr следующим образом:
```c
#include <termios.h>
int tcsetattr(int fd, int actions, const struct termios *termios_p);
```

Поле `actions` функции `tcsetattr` управляет способом внесения изменений. Есть три варианта:

- TCSANOW — изменяет значения сразу;

- TSCADRAIN — изменяет значения, когда текущий вывод завершен;

- TCSAFLUSH — изменяет значения, когда текущий вывод завершен, но отбрасывает любой ввод, доступный в текущий момент и все еще не возвращенный вызовом read.

_Примечание_
Учтите, что для программ очень важно восстановить настройки терминала, действующие до начала выполнения программы. За первоначальное сохранение значений и их восстановление после завершения выполнения всегда отвечает программа.
Все полезные настройки смотри тут: http://programming-lang.com/ru/comp_programming/metyu/0/j174.html
### tgetent
### tgetflag
### tgetnum
### tgetstr
### tgoto
### tputs
