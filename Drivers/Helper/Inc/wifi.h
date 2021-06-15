//
// Created by Apple on 2021/6/11.
//

#ifndef STM32_WIFI_H
#define STM32_WIFI_H

extern uint8_t WiFiAT[] = "AT\r\n";
extern uint8_t WiFiJoinAHotPoint[] = "AT+CWJAP=\"EHSY-GuestWIFI\",\"ehsy.com\"\r\n";
extern uint8_t WiFiAvailableWiFis[] = "AT+CWLAP\r\n";
extern uint8_t WiFiMyIp[] = "AT+CIFSR\r\n";
extern uint8_t WiFiTCPConnect[] = "AT+CIPSTART=\"TCP\",\"192.168.58.159\",9090\r\n";
extern uint8_t WiFiTCPSend[] = "AT+CIPSEND=331\r\n";
extern uint8_t WiFiTCPClose[] = "AT+CIPCLOSE\r\n";
extern uint8_t WiFiOnMultiTCP[] = "AT+CIPMUX=1\r\n";
extern uint8_t WiFiOffMultiTCP[] = "AT+CIPMUX=0\r\n";
extern uint8_t WiFiStartServer[] = "AT+CIPSERVER=1,8080\r\n";

#endif //STM32_WIFI_H
