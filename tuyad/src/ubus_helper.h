#ifndef UBUS_HELPER_H
#define UBUS_HELPER_H

#include <libubus.h>
#include <libubox/blobmsg_json.h>

/* Constants */
#define UBUS_TIMEOUT_MS 3000

/* Memory data structure */
struct MemData {
    uint64_t total;
    uint64_t free;
    uint64_t shared;
    uint64_t buffered;
};

/* UBUS policies */
enum memory_policy_type {
    TOTAL_MEMORY = 0,
    FREE_MEMORY,
    SHARED_MEMORY,
    BUFFERED_MEMORY,
    __MEMORY_MAX
};

enum info_policy_type {
    MEMORY_DATA = 0,
    __INFO_MAX
};

/* Function declarations */
void memory_data_callback(struct ubus_request *req, int type, struct blob_attr *msg);
int fetch_memory_data(struct ubus_context **ctx, struct MemData *memory);
int establish_ubus_connection(struct ubus_context **ctx);
int terminate_ubus_connection(struct ubus_context **ctx);

#endif
