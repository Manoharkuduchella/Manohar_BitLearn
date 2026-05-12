#include <val_flash_spi.h>

#define FLASH_CS 5
#define FLASH_ADDR 0x000000

ValFlashSPI flash(FLASH_CS); // velocidade padrão (4 MHz)

struct Dados {
  uint32_t id;
  float temperatura;
  char nome[16];
};

void setup() {
  Serial.begin(115200);
  while (!Serial);

  flash.begin();

  //Dados dados = {4321, 24.5, "TesteBasico"};
  flash.eraseSector(FLASH_ADDR);
  //flash.writeStruct(FLASH_ADDR, dados);
  if(!(flash.writeByte(FLASH_ADDR, (uint8_t)0x3A)))
  {
    Serial.println("Write Failed");
  }
  else
  {
    Serial.println("Write successful");
  }

  //Dados lidos;
  //flash.readStruct(FLASH_ADDR, lidos);
  
  uint8_t val = flash.readByte(FLASH_ADDR);
  Serial.print("Read:");
  Serial.println(val, HEX);
  //Serial.print("ID: "); Serial.println(lidos.id);
  //Serial.print("Temp: "); Serial.println(lidos.temperatura);
  //Serial.print("Nome: "); Serial.println(lidos.nome);
}

void loop() {}
