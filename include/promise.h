#pragma once




enum e_result_type
{
    PROMISE,
    DATA
};

struct result_s
{
    enum e_result_type  result_type;
    void                *data;
};

typedef struct result_s result_t;

typedef result_t (*promise_fn_t)(void*);
typedef void     (*error_fn_t)(void*);

struct promise_fn_list_s
{
    promise_fn_t                fn;
    struct promise_fn_list_s    *next;
};

typedef struct promise_fn_list_s promise_fn_list_t;

enum e_promise_state
{
    PENDING,
    FULFILLED,
    REJECTED
};

struct promise_s
{
    enum e_promise_state    state;
    result_t                result;
    promise_fn_list_t       *success_list_fn;
    error_fn_t              reject;
};

typedef struct promise_s promise_t;

void        promise_init(promise_t *promise);
promise_t   *promise_then(promise_t *promise, promise_fn_t fn);
void        promise_catch(promise_t *promise, error_fn_t fn);
void        promise_resolve(promise_t *promise, void *data);
void        promise_reject(promise_t *promise, void *reason);