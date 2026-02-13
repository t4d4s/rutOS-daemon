#include <libubox/blobmsg_json.h>
#include <libubus.h>
#include <syslog.h>
#include "ubus_helper.h"

static const struct blobmsg_policy memory_policy[__MEMORY_MAX] = {
    [TOTAL_MEMORY]    = { .name = "total", .type = BLOBMSG_TYPE_INT64 },
    [FREE_MEMORY]     = { .name = "free", .type = BLOBMSG_TYPE_INT64 },
    [SHARED_MEMORY]   = { .name = "shared", .type = BLOBMSG_TYPE_INT64 },
    [BUFFERED_MEMORY] = { .name = "buffered", .type = BLOBMSG_TYPE_INT64 },
};

static const struct blobmsg_policy info_policy[__INFO_MAX] = {
    [MEMORY_DATA] = { .name = "memory", .type = BLOBMSG_TYPE_TABLE },
};

void memory_data_callback(struct ubus_request *req, int type, struct blob_attr *msg)
{
    struct MemData *memory_data = (struct MemData *)req->priv;
    struct blob_attr *tb[__INFO_MAX];
    struct blob_attr *memory[__MEMORY_MAX];

    blobmsg_parse(info_policy, __INFO_MAX, tb, blob_data(msg), blob_len(msg));

    if (!tb[MEMORY_DATA]) {
        syslog(LOG_ERR, "No memory data received from UBUS");
        return;
    }

    blobmsg_parse(memory_policy, __MEMORY_MAX, memory, blobmsg_data(tb[MEMORY_DATA]),
                  blobmsg_data_len(tb[MEMORY_DATA]));

    memory_data->total    = blobmsg_get_u64(memory[TOTAL_MEMORY]);
    memory_data->free     = blobmsg_get_u64(memory[FREE_MEMORY]);
    memory_data->shared   = blobmsg_get_u64(memory[SHARED_MEMORY]);
    memory_data->buffered = blobmsg_get_u64(memory[BUFFERED_MEMORY]);
}

int fetch_memory_data(struct ubus_context **ctx, struct MemData *memory)
{
    uint32_t id;

    if (ubus_lookup_id(*ctx, "system", &id)) {
        syslog(LOG_ERR, "UBUS: Failed to look up system object");
        return 1;
    }

    int ret = ubus_invoke(*ctx, id, "info", NULL, memory_data_callback, memory, UBUS_TIMEOUT_MS);
    if (ret) {
        syslog(LOG_ERR, "UBUS: Failed to request memory info from procd (Error: %d)", ret);
        return 1;
    }

    return 0;
}


int establish_ubus_connection(struct ubus_context **ctx)
{
    *ctx = ubus_connect(NULL);
    if (!*ctx) {
        syslog(LOG_ERR, "UBUS: Failed to connect to ubus");
        return -3;
    }

    syslog(LOG_INFO, "UBUS: Connection established successfully");
    return 0;
}

int terminate_ubus_connection(struct ubus_context **ctx)
{
    if (!*ctx) {
        syslog(LOG_ERR, "UBUS: Context is already free");
        return 1;
    }

    ubus_free(*ctx);
    *ctx = NULL;
    syslog(LOG_INFO, "UBUS: Connection closed successfully");

    return 0;
}
