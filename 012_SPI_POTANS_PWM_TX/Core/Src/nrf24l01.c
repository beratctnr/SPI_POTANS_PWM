#include "nrf24l01.h"

// SPI tanımı
extern SPI_HandleTypeDef NRF_SPI;

static void nrf24_writeRegister(uint8_t reg, uint8_t value);
static void nrf24_writeRegisterMulti(uint8_t reg, uint8_t *data, uint8_t length);
static void nrf24_readRegisterMulti(uint8_t reg, uint8_t *data, uint8_t length);
static void nrf24_ceHigh(void);
static void nrf24_ceLow(void);
static void nrf24_csnHigh(void);
static void nrf24_csnLow(void);

// **nRF24L01 Başlatma**
void nrf24_init(void)
{
    nrf24_csnHigh();
    nrf24_ceLow();
    HAL_Delay(5);
}

// **RF Modülü Konfigürasyonu**
void nrf24_config(uint8_t channel, uint8_t payloadSize)
{
    nrf24_writeRegister(0x05, channel);  // RF Kanalı
    nrf24_writeRegister(0x11, payloadSize);  // RX Payload boyutu
    nrf24_writeRegister(0x01, 0x01);  // Auto ACK Açık
    nrf24_writeRegister(0x02, 0x01);  // Data Pipe 0 Aktif
    nrf24_writeRegister(0x03, 0x03);  // Adres genişliği 5 bayt
    nrf24_writeRegister(0x06, 0x07);  // Data rate: 1Mbps, Güç: 0dBm
    nrf24_writeRegister(0x00, 0x0E);  // CRC ve güç açık
}

// **Verici Adresi Ayarla**
void nrf24_tx_address(uint8_t *address)
{
    nrf24_writeRegisterMulti(0x10, address, 5);
    nrf24_writeRegisterMulti(0x0A, address, 5);
}

// **Alıcı Adresi Ayarla**
void nrf24_rx_address(uint8_t *address)
{
    nrf24_writeRegisterMulti(0x0A, address, 5);
}

// **Verici Moduna Geç**
void nrf24_tx_mode(void)
{
    nrf24_writeRegister(0x00, 0x0E);
    nrf24_ceHigh();
    HAL_Delay(1);
}

// **Alıcı Moduna Geç**
void nrf24_rx_mode(void)
{
    nrf24_writeRegister(0x00, 0x0F);
    nrf24_ceHigh();
    HAL_Delay(1);
}

// **Veri Gönder**
uint8_t nrf24_send(uint8_t *data, uint8_t length)
{
    uint8_t status;

    // SPI haberleşmesini başlat
    nrf24_csnLow();

    // TX FIFO'ya veri yazmak için komut gönder
    uint8_t command = NRF24_CMD_W_TX_PAYLOAD;
    HAL_SPI_Transmit(&NRF_SPI, &command, 1, 100);

    // Veriyi gönder (length kadar bayt gönderiyoruz)
    HAL_SPI_Transmit(&NRF_SPI, data, length, 100);

    // SPI haberleşmesini bitir
    nrf24_csnHigh();

    // Kısa bir gecikme
    HAL_Delay(10);

    // Durum registerini oku
    nrf24_readRegisterMulti(0x07, &status, 1);

    // Eğer veri başarıyla gönderildiyse
    if (status & 0x20)
    {
        nrf24_writeRegister(0x07, 0x20);  // TX flag temizle
        return 1;  // Başarılı
    }

    return 0;  // Başarısız
}


// **Gelen Veri Var mı?**
uint8_t nrf24_dataReady(void)
{
    uint8_t status;
    nrf24_readRegisterMulti(0x07, &status, 1);
    return (status & 0x40); // RX flag kontrolü
}

// **Veriyi Oku**
void nrf24_getData(uint8_t *data, uint8_t length)
{
    nrf24_csnLow();

    // RX FIFO'dan veri okumak için komut gönder
    uint8_t command = NRF24_CMD_R_RX_PAYLOAD;
    HAL_SPI_Transmit(&NRF_SPI, &command, 1, 100);

    // Veriyi oku (length kadar bayt)
    HAL_SPI_Receive(&NRF_SPI, data, length, 100);

    nrf24_csnHigh();

    // RX flag temizle
    nrf24_writeRegister(0x07, 0x40);
}

// **SPI Register Yaz**
static void nrf24_writeRegister(uint8_t reg, uint8_t value)
{
    nrf24_csnLow();
    uint8_t command = NRF24_CMD_W_REGISTER | reg;
    HAL_SPI_Transmit(&NRF_SPI, &command, 1, 100);
    HAL_SPI_Transmit(&NRF_SPI, &value, 1, 100);
    nrf24_csnHigh();
}

// **SPI Register Çoklu Yaz**
static void nrf24_writeRegisterMulti(uint8_t reg, uint8_t *data, uint8_t length)
{
    nrf24_csnLow();
    uint8_t command = NRF24_CMD_W_REGISTER | reg;
    HAL_SPI_Transmit(&NRF_SPI, &command, 1, 100);
    HAL_SPI_Transmit(&NRF_SPI, data, length, 100);
    nrf24_csnHigh();
}

// **SPI Register Çoklu Oku**
static void nrf24_readRegisterMulti(uint8_t reg, uint8_t *data, uint8_t length)
{
    nrf24_csnLow();
    uint8_t command = NRF24_CMD_R_REGISTER | reg;
    HAL_SPI_Transmit(&NRF_SPI, &command, 1, 100);
    HAL_SPI_Receive(&NRF_SPI, data, length, 100);
    nrf24_csnHigh();
}

// **CE Yüksek (Aktif)**
static void nrf24_ceHigh(void)
{
    HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_SET);
}

// **CE Düşük (Pasif)**
static void nrf24_ceLow(void)
{
    HAL_GPIO_WritePin(NRF_CE_PORT, NRF_CE_PIN, GPIO_PIN_RESET);
}

// **CSN Yüksek (İşlem Yok)**
static void nrf24_csnHigh(void)
{
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_SET);
}

// **CSN Düşük (İşlem Başlat)**
static void nrf24_csnLow(void)
{
    HAL_GPIO_WritePin(NRF_CSN_PORT, NRF_CSN_PIN, GPIO_PIN_RESET);
}
