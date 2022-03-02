#pragma once


#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <esp_http_server.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"



esp_err_t get_handler(httpd_req_t*);
esp_err_t post_handler(httpd_req_t*);

httpd_handle_t start_webserver(void);

void stop_webserver(httpd_handle_t);

