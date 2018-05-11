/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 26-3 */

#include <sys/wait.h>
#include "print_wait_status.h"          /* Declares printWaitStatus() */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int status;
    pid_t childPid;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
//argc가 2이상이고 argv[] 0번째가 --help일때
        usageErr("%s [exit-status]\n", argv[0]);

    switch (fork()) { //포크 실행, 프로세서 판별
    case -1: errExit("fork");

    case 0:             /* Child: either exits immediately with given
                           status or loops waiting for signals */
        printf("Child started with PID = %ld\n", (long) getpid());
		//자식 프로세서 id 출력
        if (argc > 1)                   /* Status supplied on command line? */
            exit(getInt(argv[1], 0, "exit-status"));
		//부모한테 argv 문자열 정수값 전달
        else                            /* Otherwise, wait for signals */
            for (;;)//에러일때
                pause();
        exit(EXIT_FAILURE);             /* Not reached, but good practice */

    default:            /* Parent: repeatedly wait on child until it
                           either exits or is terminated by a signal */
        for (;;) {
            childPid = waitpid(-1, &status, WUNTRACED
#ifdef WCONTINUED       /* Not present on older versions of Linux */
                                                | WCONTINUED
#endif
                    );//지정된 자식 프로세서 값을 받는 wait 함수
            if (childPid == -1)//자식 프로세서 에러
                errExit("waitpid");

            /* Print status in hex, and as separate decimal bytes */

            printf("waitpid() returned: PID=%ld; status=0x%04x (%d,%d)\n",
                    (long) childPid,
                    (unsigned int) status, status >> 8, status & 0xff);
//자식 id, 자식 exit 값, 자식 exit 값 시프트 >8,자식 exit 값 하위 8비트 출력
            printWaitStatus(NULL, status);//statloc 매크로함수 판별

            if (WIFEXITED(status) || WIFSIGNALED(status))
//정상적으로 종료한 경우 값 출력 또는 시그널에 의해 종료한 경우 값 출력한 경우
                exit(EXIT_SUCCESS);
        }
    }
}
