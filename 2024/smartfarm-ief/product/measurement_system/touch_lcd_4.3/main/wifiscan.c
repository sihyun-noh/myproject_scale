/* Scan Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

/*
    This example shows how to scan for available set of APs.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "wifi_manager.h"
#include "sys_status.h"
#include "sysevent.h"
#include "wifi_manager_private.h"
#include "global.h"

#define DEFAULT_SCAN_LIST_SIZE CONFIG_EXAMPLE_SCAN_LIST_SIZE

static const char *TAG = "wifi_scan";

EventGroupHandle_t s_wifi_event_group;

char list_buff[10][100] = { 0 };
char (*str_buff)[100] = list_buff;
uint16_t ap_scan_num = 0;

void wifi_scan_done() {
  //  uint16_t ap_scan_num = 0;
  ap_info_t *ap_scan_list = NULL;
  printf("Scan nearby AP network\n");
  uint16_t scan_ap_num = wifi_scan_network(false, false, false, 500, 1, NULL, NULL);
  if (scan_ap_num > 0) {
    ap_scan_list = get_wifi_scan_list(&ap_scan_num);
    if (ap_scan_list) {
      printf("scan ap num [%d], [%d]\n", scan_ap_num, ap_scan_num);
      for (int i = 0; i < ap_scan_num; i++) {
        printf("ap_info_list[%d].ssid = %s\n", i, ap_scan_list[i].ssid);
        printf("ap_info_list[%d].rssi = %d\n", i, ap_scan_list[i].rssi);
        memset(str_buff + 1, 0x00, sizeof(*(str_buff + i)));
        sprintf(str_buff + i, "%s (%d) ", ap_scan_list[i].ssid, ap_scan_list[i].rssi);
        ESP_LOGI(TAG, "%s", *(str_buff + i));
      }
      free(ap_scan_list);
    }
  }
}

int sta_disconnect_handler(void *arg) {
  if (s_wifi_event_group) {
    xEventGroupSetBits(s_wifi_event_group, WIFI_DISCONNECT);
  }
  return 0;
}

int sta_ip_handler(void *arg) {
  if (s_wifi_event_group) {
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED);
  }
  return 0;
}

void wifi_scan_main() {
  // Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  ESP_LOGI(TAG, "wifi init");
  wifi_user_init();
  sys_stat_init();
  sysevent_create();
  wifi_sta_mode();
  s_wifi_event_group = xEventGroupCreate();
  vTaskDelay(100 / portTICK_PERIOD_MS);
  sysevent_get_with_handler(IP_EVENT, IP_EVENT_STA_GOT_IP, sta_ip_handler, NULL); /*add event register*/
  sysevent_get_with_handler(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, sta_disconnect_handler, NULL);

  //  xTaskCreate(wifiScan_Task, "mainwifisacntask", 4096, NULL, 1, NULL);
}
