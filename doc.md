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
