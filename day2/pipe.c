// Program to demonstrate basic operations on pipes.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int main()
{
    int pdes[2];

    int rval, num;

    system("clear");

    printf("\n MP: PID = %d \t PPID = %d \n", getpid(), getppid());

    printf("\n program to demonstrate basic operations on pipes \n");

    rval = pipe(pdes); // creating a pipe

    if (rval == -1)
    {
        perror("PIPE-ERR:");
        exit(1);
    }

    printf("\n MP: Read Pipe value is %d \t Write Pipe value is %d of the pipe \n", pdes[0], pdes[1]);

    printf("\n enter the number to write to pipe \t");
    scanf("%d", &num);

    rval = write(pdes[1], &num, sizeof(num));
    if (rval == -1)
        perror("PIPE-WR-ERR:");
    else
    {
        printf("\n MP: %d bytes written to pipe \n", rval);
        rval = read(pdes[0], &num, sizeof(num));
        if (rval == 0)
            perror("PIPE-RD-ERR:");
        else if (rval == -1)
        {
            perror("Error Reading");
        }

        else
            printf("\n MP: Data read from pipe is %d\n", num);
    }

    close(pdes[0]); //releasing the pipe
    close(pdes[1]); //releasing the pipe
}
