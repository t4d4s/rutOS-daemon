#ifndef HELPER_UTILS_H
#define HELPER_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <mqtt_client_interface.h>
#include <tuyalink_core.h>
#include <cJSON.h>

void saveToLogs(const char* text);
void check_actionCode(const tuyalink_message_t* msg);
struct MemData gather_memory_information(void);
cJSON* convert_memory_to_json(struct MemData *memory_data);
void send_memory_information(tuya_mqtt_context_t* context, cJSON* memory_json);

#endif
