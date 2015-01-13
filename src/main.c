#include <stdlib.h>
#include <stdio.h>
#include "promise.h"

result_t    say_hello(void *data)
{
    result_t    result;
    char        *name = (char*)(data);

    printf("Hello %s\n", name);
    result.data = data;
    result.result_type = DATA;
    return result;
}

void error_handler(void *reason)
{
    printf("Hey ca va\n");
}

int main() {
    promise_t   promise;

    promise_init(&promise);
    promise_then(&promise, &say_hello);
    promise_then(&promise, &say_hello);
    promise_catch(&promise, &error_handler);
    promise_resolve(&promise, "jalal");
    printf("%d", sizeof(promise));
    return 0;
}