/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Listing 24-2 */

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    setbuf(stdout, NULL);     //stdout의 버퍼링을 막는다.

    fd = mkstemp(template); //파일 생성, 끝 6자리 문자열은 xxxxxx 치환
    if (fd == -1)
        errExit("mkstemp");

    printf("File offset before fork(): %lld\n",
            (long long) lseek(fd, 0, SEEK_CUR)); //64비트 파일 대비 캐스팅

    flags = fcntl(fd, F_GETFL);// 열려진 파일지정자에 대한 플레그 값 읽기
	//파일 속성 설정
    if (flags == -1)
        errExit("fcntl - F_GETFL");
    printf("O_APPEND flag before fork() is: %s\n",
            (flags & O_APPEND) ? "on" : "off");
	//O_APPEND 파일 끝부분에 저장

    switch (fork()) {
    case -1://fork error
        errExit("fork");

	case 0:     // 자식 : 파일 오프셋과 상태 플래그를 변경, exit 성공
        if (lseek(fd, 1000, SEEK_SET) == -1)
            errExit("lseek");

        flags = fcntl(fd, F_GETFL);        //현재 플래그 읽기
        if (flags == -1)
            errExit("fcntl - F_GETFL");
        flags |= O_APPEND;                  /* Turn O_APPEND on */
        if (fcntl(fd, F_SETFL, flags) == -1)
            errExit("fcntl - F_SETFL");
        _exit(EXIT_SUCCESS); // 자식 EXIT_SUCCESS 0 값 보내주고 곧바로 종료

    default:    /* Parent: can see file changes made by child */
        if (wait(NULL) == -1)
//자식한테 exit 값을 받지 않음
            errExit("wait");                /* Wait for child exit */
        printf("Child has exited\n");

        printf("File offset in parent: %lld\n",
                (long long) lseek(fd, 0, SEEK_CUR));//부모에서의 커서의 위치

        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            errExit("fcntl - F_GETFL");
        printf("O_APPEND flag in parent is: %s\n",
                (flags & O_APPEND) ? "on" : "off"); //O_APPEND 설정
        exit(EXIT_SUCCESS);
    }
}
