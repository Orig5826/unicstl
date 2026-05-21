/**
 * @file perf_log.c
 * @author wenjf (orig5826@163.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-13
 * 
 * @copyright Copyright (c) 2026
 * 
 * 性能日志模块，用于记录函数执行时间等信息。
 * 
 * @note
 *    已知道plans=3，更简洁的方案是定义3个元素为darray的数组，这里的实现是为了演示二维动态数组的使用。
 * 
 */
#include "perf_log.h"
#include "perf.h"

static darray_t plans = NULL;

bool perf_log_new(void)
{
    plans = darray_new(sizeof(darray_t), PERF_TEST_TIEMS);
    if(plans == NULL)
    {
        log_warn("plans->new failed\n");
        goto done;
    }

    for(size_t i = 0; i < plans->capacity(plans); ++i)
    {
        darray_t items = darray_new(sizeof(log_args_t), 16);
        if(items == NULL)
        {
            log_warn("items->new failed\n");
            goto done;
        }
        plans->append(plans, &items);
    }

    return true;
done:
    perf_log_free();
    return false;
}

void perf_log_free(void)
{
    while(!plans->empty(plans))
    {
        darray_t items;
        plans->pop(plans, &items);
        darray_free(&items);
    }
    darray_free(&plans);
}

bool perf_log_append(const char *name, size_t id, double time_ms)
{
    log_debug("id=%d, name=%s, time=%f\n", id, name, time_ms);
    log_args_t args = {
         // .name = name, 
        .id = id,
        .elapsed = time_ms,
    };

    size_t len = strlen(name) > 32 ? 32 : strlen(name) + 1;
    memmove(args.name, name, strlen(name) + 1);
    args.name[31] = '\0';

    darray_t items = NULL;
    if(!plans->get(plans, id, &items))
    {
        log_debug("not find items\n");
        return false;
    }

    if(!items->append(items, &args))
    {
        log_debug("items->append failed\n");
        return false;
    }

    log_debug("size = %d\n", items->size(items));
    log_args_t args2;
    if(!items->get(items, 0, &args2))
    {
        log_debug("items->get failed\n");
        return false;
    }
    log_info("name=%s, id=%d, time=%f\n", args2.name, args2.id, args2.elapsed);

    log_debug("perf_log_append end\n");
    return true;
}

bool perf_log_clear(void)
{
    darray_t items = NULL;
    for(size_t i = 0; i < plans->capacity(plans); ++i)
    {
        if(!plans->get(plans, i, &items))
        {
            log_debug("plans->get failed\n");
            return false;
        }

        items->clear(items);
    }

    log_debug("perf_log_clear\n");
    return true;
}

// name[32] | T1 | T2 | T3 | ...
#define PERF_FORMAT_FUNC        "%-32s"
#define PERF_FORMAT_DATA        "%10.3f"

static void perf_log_print_header(void)
{
    size_t count = plans->capacity(plans);

    printf(PERF_FORMAT_FUNC, "       function       ");
    for(size_t i = 0; i < count; ++i)
    {
        printf("   T%-2d(us)", i);
    }
    printf("\n");

    printf(PERF_FORMAT_FUNC, " -------------------- ");
    for(size_t i = 0; i < count; ++i)
    {
        printf("%10s", " --------- ");
    }
    printf("\n");
}

bool perf_log_print(void)
{
    perf_log_print_header();

    bool name_printed = false;

    darray_t items = NULL;
    if(!plans->get(plans, 0, &items))
    {
        return false;
    }
    size_t count = items->size(items);

    log_debug("count=%d\n", count);
    for(size_t i = 0; i < count; ++i)
    {
        name_printed = false;
        for(size_t j = 0; j < plans->capacity(plans); j++)
        {
            log_debug("i=%d, j=%d\n", i, j);

            if(!plans->get(plans, j, &items))
            {
                log_debug("plans->get failed\n");
                return false;
            }

            log_debug("size = %d\n", items->size(items));

            log_args_t args;
            if(!items->get(items, i, &args))
            {
                log_debug("items->get failed\n");
                return false;
            }

            if(!name_printed)
            {
                name_printed = true;
                printf(PERF_FORMAT_FUNC, args.name);
            }
            printf(PERF_FORMAT_DATA, args.elapsed);
        }
        printf("\n");
    }
    log_debug("perf_log_print end\n");
    return true;
}
