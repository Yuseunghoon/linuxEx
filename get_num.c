/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2017.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU Lesser General Public License as published   *
* by the Free Software Foundation, either version 3 or (at your option)   *
* any later version. This program is distributed without any warranty.    *
* See the files COPYING.lgpl-v3 and COPYING.gpl-v3 for details.           *
\*************************************************************************/

/* Listing 3-6 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "get_num.h"

//null이거나 비워있을 때 처리 함수
static void
gnFail(const char *fname, const char *msg, const char *arg, const char *name)
{
//문자열 getlong, 문자열 null or empty string, arg 첫글자, argv txt 
    fprintf(stderr, "%s error", fname);//fd 2번에 getlong error 문자열 입력
    if (name != NULL)
        fprintf(stderr, " (in %s)", name);
    fprintf(stderr, ": %s\n", msg);
    if (arg != NULL && *arg != '\0')
        fprintf(stderr, "        offending text: %s\n", arg);

    exit(EXIT_FAILURE);
}

static long
getNum(const char *fname, const char *arg, int flags, const char *name)
{
//문자열 getlong, arg 첫글자, 0100, argv txt
    long res;
    char *endptr;
    int base;

    if (arg == NULL || *arg == '\0')
        gnFail(fname, "null or empty string", arg, name);

//0100&0100 ? true 0 : flase 0100&0200 ? ture 8 : false 0100&0400 ? ture 16: false 10
    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :
                        (flags & GN_BASE_16) ? 16 : 10;

    errno = 0;//에러 발생했는지 확인을  위해 0 설정 뒤  호출 후 다시 확인
    res = strtol(arg, &endptr, base);
//arg 첫글자의 포인터 위치, null, 진수->문자열을 정수로 변환
		
    if (errno != 0)//에러 발생 시
//null이거나 비워있을 때 처리 함수
        gnFail(fname, "strtol() failed", arg, name);
    if (*endptr != '\0')//에러 발생 시
        gnFail(fname, "nonnumeric characters", arg, name);

//(0100&01) && 문자열 정수<0 때
    if ((flags & GN_NONNEG) && res < 0)
        gnFail(fname, "negative value not allowed", arg, name);

//(0100&02) && 문자열 정수<=0 때
    if ((flags & GN_GT_0) && res <= 0)
        gnFail(fname, "value must be > 0", arg, name);

    return res;//문자열 정수 리턴
}

long
getLong(const char *arg, int flags, const char *name)
{
    return getNum("getLong", arg, flags, name);//arg 문자열 정수 리턴
}

int
getInt(const char *arg, int flags, const char *name)
{
    long res;

    res = getNum("getInt", arg, flags, name);

    if (res > INT_MAX || res < INT_MIN)
        gnFail("getInt", "integer out of range", arg, name);

    return (int) res;
}
