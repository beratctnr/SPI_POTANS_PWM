#ifndef NRF24L01_H
#define NRF24L01_H

#include "stm32f0xx_hal.h"

// **nRF24L01 Pin Tanımlamaları (Senin Verdiğin Pinler)**
#define NRF_CE_PIN GPIO_PIN_9
#define NRF_CE_PORT GPIOB

#define NRF_CSN_PIN GPIO_PIN_10
#define NRF_CSN_PORT GPIOB

#define NRF_SPI hspi1  // SPI Kullanımı (PB3-SCK, PB4-MISO, PB5-MOSI)

// **nRF24L01 Komutları**
#define NRF24_CMD_R_REGISTER 0x00
#define NRF24_CMD_W_REGISTER 0x20
#define NRF24_CMD_R_RX_PAYLOAD 0x61
#define NRF24_CMD_W_TX_PAYLOAD 0xA0
#define NRF24_CMD_FLUSH_TX 0xE1
#define NRF24_CMD_FLUSH_RX 0xE2
#define NRF24_CMD_REUSE_TX_PL 0xE3
#define NRF24_CMD_NOP 0xFF

void nrf24_init(void);
void nrf24_config(uint8_t channel, uint8_t payloadSize);
void nrf24_tx_address(uint8_t *address);
void nrf24_rx_address(uint8_t *address);
void nrf24_tx_mode(void);
void nrf24_rx_mode(void);
uint8_t nrf24_dataReady(void);
uint8_t nrf24_send(uint8_t *data, uint8_t length);  // Çok baytlı veri göndermek için güncellendi
void nrf24_getData(uint8_t *data, uint8_t length);  // Çok baytlı veri almak için güncellendi



#endif
