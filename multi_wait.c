/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 26-1 */

#include <sys/wait.h>
#include <time.h>
#include "curr_time.h"              /* Declaration of currTime() */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int numDead;       /* Number of children so far waited for */
    pid_t childPid;    /* PID of waited for child */
    int j;

    if (argc < 2 || strcmp(argv[1], "--help") == 0)
//파일 디스트럽이 2 미만 or argv 두번째가 --help 둘다 포함안될 때 실행	
        usageErr("%s sleep-time...\n", argv[0]); //argv 첫번쨰 sleep time

    setbuf(stdout, NULL);           /* Disable buffering of stdout */

    for (j = 1; j < argc; j++) {    /* Create one child for each argument */
        switch (fork()) { //포크 실행
        case -1: //에러
            errExit("fork");
		//자식 프로세서
        case 0:                     /* Child sleeps for a while then exits */
            printf("[%s] child %d started with PID %ld, sleeping %s "
                    "seconds\n", currTime("%T"), j, (long) getpid(),
                    argv[j]);
			//현재시간,argc만큼 자식 포크 카운트, 자식id,argv[j] txt
            sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
			//argv 문자열 정수만큼 sleep
			//자식 프로세서는 sleep 이지만 부모는 계속 돌아가 형제 프로세서 만듬
            _exit(EXIT_SUCCESS);

	//부모 프로세서
        default:                    /* Parent just continues around loop */
            break;
        }
    }

    numDead = 0;
    for (;;) {                      /* Parent waits for each child to exit */
        childPid = wait(NULL);// 자식한테 받는 exit 값 없음
        if (childPid == -1) {
            if (errno == ECHILD) {
	// 에러번호가 기다리는 자식프로세스가 더이상 존재하지 않을 때
                printf("No more children - bye!\n");
                exit(EXIT_SUCCESS);//프로그램 종료
            } else {                /* Some other (unexpected) error */
                errExit("wait");// wait 에러
            }
        }

        numDead++; //numDead가 1
        printf("[%s] wait() returned child PID %ld (numDead=%d)\n",
                currTime("%T"), (long) childPid, numDead);
	//현재 시간, 자식 id, numDead=1
	}
}
