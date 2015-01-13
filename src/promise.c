#include <stdlib.h>
#include "promise.h"

void promise_init(promise_t *promise)
{
    promise->state = PENDING;
    promise->result.data = NULL;
    promise->reject = NULL;
    promise->success_list_fn = NULL;
}

promise_t   *promise_then(promise_t *promise, promise_fn_t fn)
{
    promise_fn_list_t   *node;
    promise_fn_list_t   *newNode;

    node = promise->success_list_fn;
    newNode = malloc(sizeof(*newNode));
    newNode->next = NULL;
    if (!newNode)
        return NULL;
    newNode->fn = fn;
    if (!node)
        promise->success_list_fn = newNode;
    else
    {
        while (node->next) {
            node = node->next;
        }
        node->next = newNode;
    }
    return promise;
}


void    promise_catch(promise_t *promise, error_fn_t fn)
{
    promise->reject = fn;
}

void promise_resolve(promise_t *promise, void *data)
{
    promise_fn_list_t   *node = promise->success_list_fn;
    promise_fn_t        fn;
    result_t            result;
    promise_fn_list_t   *currentNode;

    if (promise->state != FULFILLED) {
        promise->state = PENDING;
        while (node) {
            fn = node->fn;
            result = (*fn)(data);
            if (result.result_type == PROMISE) {
                promise_t *promise_result = (promise_t *) (result.data);

                promise_result->success_list_fn = node->next;
                promise_result->reject = promise->reject;
                node->next = NULL;
            }
            currentNode = node;
            node = node->next;
            free(currentNode);
        }
        promise->success_list_fn = NULL;
        promise->state = FULFILLED;
    }
}

void promise_reject(promise_t *promise, void *reason)
{
    if (promise->reject)
        promise->reject(reason);
    promise->state = REJECTED;
}