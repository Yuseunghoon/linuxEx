/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 24-3 */

#define _BSD_SOURCE     /* To get sbrk() declaration from <unistd.h> in case
                           _XOPEN_SOURCE >= 600; defining _SVID_SOURCE or
                           _GNU_SOURCE also suffices */
#include <sys/wait.h>
#include "tlpi_hdr.h"

static int
func(int arg)
{
    int j;

    for (j = 0; j < 0x100; j++)//사이즈 계속 증가
        if (malloc(0x8000) == NULL) //0x8000 동적할당이 널과 같다면
            errExit("malloc");
    printf("Program break in child:  %10p\n", sbrk(0));
	//sbrk는 이전 세그먼트에 +0, 0이면 데이터 세그먼트의 최하위 주소 호출

    return arg;
}

int
main(int argc, char *argv[])
{
    int arg = (argc > 1) ? getInt(argv[1], 0, "arg") : 0;
	//argc>1 일때 문자열 정수값 :!일때 0
    pid_t childPid;
    int status;

    setbuf(stdout, NULL);           /* Disable buffering of stdout */

    printf("Program break in parent: %10p\n", sbrk(0));

    childPid = fork(); //fork 실행하고 자식 프로세서 ID 값 저장
    if (childPid == -1)
        errExit("fork");

    if (childPid == 0)              /* Child calls func() and */
        exit(func(arg));            /* uses return value as exit status */

    /* Parent waits for child to terminate. It can determine the
       result of func() by inspecting 'status' */

    if (wait(&status) == -1) //자식 프로세서에서 exit 파악
        errExit("wait");

    printf("Program break in parent: %10p\n", sbrk(0));

    printf("Status = %d %d\n", status, WEXITSTATUS(status)); //status의 하위 8비트만 출력

    exit(EXIT_SUCCESS);
}
