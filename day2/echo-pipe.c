// Program to demonstrate Echo Server using pipes.  2 pipes need to be created.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

int main()
{
    int pipe1[2], pipe2[2];
    int rval, rval1, num, num1;
    int pid;

    system("clear");

    printf("\n MP: PID = %d \t PPID = %d \n", getpid(), getppid());

    printf("\n program to demonstrate Echo Server using pipes \n");

    rval = pipe(pipe1); // creating 1st pipe

    if (rval == -1)
    {
        perror("PIPE-ERR:");
        exit(1);
    }

    printf("\n MP: RD-DESCRP value is %d \t WR_DESCRP value is %d of the pipe1 \n", pipe1[0], pipe1[1]);

    rval1 = pipe(pipe2); // creating 2nd  pipe

    if (rval1 == -1)
    {
        close(pipe1[0]);
        close(pipe1[1]);
        perror("PIPE-ERR:");
        exit(1);
    }

    printf("\n MP: RD-DESCRP value is %d \t WR_DESCRP value is %d of the pipe2 \n", pipe2[0], pipe2[1]);

    pid = fork();

    if (pid == -1)
    {
        perror("FRK-ERR:");
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        exit(1);
    }

    if (pid == 0) // child process
    {
        printf("\n CP: enter the number to write to pipe1 \t");
        scanf("%d", &num);

        rval = write(pipe1[1], &num, sizeof(num));
        if (rval == 0)
            perror("PIPE-WR-ERR:");
        else
            printf("\n CP: %d bytes written to pipe \n", rval);

        rval = read(pipe2[0], &num1, sizeof(num1));
        printf("\n CP: Reading from pipe 2 \n");
        if (rval == 0)
            perror("PIPE-RD-ERR:");
        else
            printf("\n CP: Date read from pipe 2 is %d\n", num1);
        exit(0);
    }
    else // Parent Process
    {

        rval = read(pipe1[0], (int *)&num1, sizeof(num1));
        printf("\n PP: Reading from pipe1 \n");
        if (rval == 0)
            perror("PIPE-RD-ERR:");
        else
            printf("\n PP: Date read from pipe 1 is %d\n", num1);

        printf("\n PP: enter the number to write to pipe2 \t");
        scanf("%d", &num1);

        rval = write(pipe2[1], (int *)&num1, sizeof(num1));
        if (rval == 0)
            perror("PIPE-WR-ERR:");
        else
            printf("\n PP: %d bytes written to pipe 2 \n", rval);
        int wait();
        rval = wait(0);
    }
    //releasing the pipe
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
}
