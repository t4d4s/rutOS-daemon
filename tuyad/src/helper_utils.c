#include "helper_utils.h"
#include "ubus_helper.h"

void saveToLogs(const char* text)
{
    FILE *fptr;
    fptr = fopen("/tmp/tuya_action.log", "w");
    if (fptr == NULL) {
        syslog(LOG_ERR, "File doesn't exist!\n");
        exit(0);
    }
    else {
        syslog(LOG_INFO, "File created!\n");
    }
    if (strcmp(text, "") > 0) {
        fprintf(fptr, "Saved Parameter: %s\n", text);
        syslog(LOG_INFO, "Parameter saved!\n");
    }
    else {
        syslog(LOG_ERR, "Received parameter is empty!\n");
    }
    fclose(fptr);
}

void check_actionCode(const tuyalink_message_t* msg)
{
    //printf("%s\n", msg->data_string);
    
    cJSON *json = cJSON_Parse(msg->data_string);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            syslog(LOG_USER | LOG_INFO, "Could not parse JSON: %s", error_ptr);
        }
        return;
    }

    cJSON *inputParamsObj = cJSON_GetObjectItem(json, "inputParams");
    if (!cJSON_IsObject(inputParamsObj)) {
        cJSON_Delete(json);
        return;
    }

    cJSON *text = cJSON_GetObjectItem(inputParamsObj, "text");

    cJSON *action_code = cJSON_GetObjectItem(json, "actionCode");
    if (action_code && strcmp(action_code->valuestring, "logger") == 0 && text) {
        syslog(LOG_INFO, "Action Code: %s\n", action_code->valuestring);
        syslog(LOG_INFO, "Text: %s\n", text->valuestring);
        
        // Saving the text to logs
        saveToLogs(text->valuestring);
    } else {
        syslog(LOG_ERR, "The received message doesn't have actionCode 'logger' or text!\n");
    }

    // Cleaning up
    cJSON_Delete(json);
}

struct MemData gather_memory_information(void) {
    struct ubus_context *ubus_ctx = NULL;
    struct MemData memory_data = {0};

    // Establish ubus connection
    if (establish_ubus_connection(&ubus_ctx) != 0) {
        syslog(LOG_ERR, "Failed to establish ubus connection");
        return memory_data;
    }

    // Fetch memory data
    if (fetch_memory_data(&ubus_ctx, &memory_data) != 0) {
        syslog(LOG_ERR, "Failed to fetch memory data from ubus");
    } else {
        syslog(LOG_INFO, "Memory Data - Total: %llu, Free: %llu, Shared: %llu, Buffered: %llu", 
                memory_data.total, memory_data.free, memory_data.shared, memory_data.buffered);
    }

    // Terminate ubus connection
    terminate_ubus_connection(&ubus_ctx);

    return memory_data;
}

cJSON* convert_memory_to_json(struct MemData *memory_data) {
    cJSON *memory_json = cJSON_CreateObject();
    if (!memory_json) {
        syslog(LOG_ERR, "Failed to create JSON object for memory data");
        return NULL;
    }

    char total_str[32], free_str[32], shared_str[32], buffered_str[32];

    snprintf(total_str, sizeof(total_str), "%llu MB", memory_data->total / (1024 * 1024));
    snprintf(free_str, sizeof(free_str), "%llu MB", memory_data->free / (1024 * 1024));
    snprintf(shared_str, sizeof(shared_str), "%llu MB", memory_data->shared / (1024 * 1024));
    snprintf(buffered_str, sizeof(buffered_str), "%llu MB", memory_data->buffered / (1024 * 1024));

    cJSON_AddStringToObject(memory_json, "total", total_str);
    cJSON_AddStringToObject(memory_json, "free", free_str);
    cJSON_AddStringToObject(memory_json, "shared", shared_str);
    cJSON_AddStringToObject(memory_json, "buffered", buffered_str);

    return memory_json;
}


void send_memory_information(tuya_mqtt_context_t* context, cJSON* memory_json) {
    if (!memory_json) {
        syslog(LOG_ERR, "Invalid JSON object provided");
        return;
    }
    report_mqtt_data(context, memory_json);

    //cJSON_Delete(memory_json);
}
