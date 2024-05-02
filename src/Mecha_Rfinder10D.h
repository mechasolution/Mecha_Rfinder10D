#ifndef SRC_MECHA_VOICERECOGNITION
#define SRC_MECHA_VOICERECOGNITION

#include <stdbool.h>
#include <stdint.h>

#include <Arduino.h>

class Mecha_Rfinder10D {
public:
  // Mecha_Rfinder10D(Stream &_port);
  bool init(Stream &port);

  void fetchNewData(void);

  bool isNewData(void);
  float getStrength(void);
  int getRange(void);

private:
  typedef struct {
    uint8_t start : 8;     // 1 byte
    uint32_t : 24;         // 1+1+1 byte
    int16_t strength : 16; // 2 byte
    uint32_t range : 32;   // 4 byte
    uint8_t end : 8;       // 1 byte
  } __attribute__((packed)) buffer_data_struct_t;

  Stream *port;
  uint8_t buffer[100];
  buffer_data_struct_t last_buffer;
  uint8_t buffer_ptr;
  bool is_start_chr_read;
  bool is_new_data;
};

#endif /* SRC_MECHA_VOICERECOGNITION */
