#include <DFRobot_BMI160.h>
#include <val_flash_spi.h>

#define FLASH_CS 5
#define TOUCH_PIN 4
#define TOUCH_THRE 500
#define WRITE_INTERVAL 30000  

#define FLASH_START_ADDR 0x000000
#define FLASH_PAGE_SIZE  256   

uint32_t write_addr = FLASH_START_ADDR;
unsigned long lastWriteTime = 0;

typedef struct {
  int16_t accel[3];
  int16_t gyro[3];
} imu_data_t;

DFRobot_BMI160 bmi160;
const int8_t i2c_addr = 0x69;
ValFlashSPI flash(FLASH_CS);

void setup(){
  Serial.begin(115200);
  delay(100);

  //init the hardware bmin160
  if (bmi160.softReset() != BMI160_OK){
    Serial.println("reset false");
    while(1);
  }

  //set and init the bmi160 i2c address
  if (bmi160.I2cInit(i2c_addr) != BMI160_OK){
    Serial.println("init false");
    while(1);
  }

  flash.begin();

  Serial.println("Erasing 4KB sector (contains 256-byte page)...");
  flash.eraseSector(FLASH_START_ADDR);
  write_addr = FLASH_START_ADDR;
  lastWriteTime = millis();

  Serial.println("Setup complete");
  Serial.print("Page size: ");
  Serial.print(FLASH_PAGE_SIZE);
  Serial.println(" bytes");
  Serial.print("Max entries per page: ");
  Serial.println(FLASH_PAGE_SIZE / sizeof(imu_data_t));
  Serial.print("Bytes per entry: ");
  Serial.println(sizeof(imu_data_t));
}

void loop()
{
  imu_data_t data;
  int rslt = bmi160.getAccelGyroData((int16_t*)&data);

  if(millis() - lastWriteTime >= WRITE_INTERVAL)
  {
    if(rslt == 0)
    {
      if((write_addr - FLASH_START_ADDR + sizeof(imu_data_t)) > FLASH_PAGE_SIZE)
      {
        write_addr = FLASH_START_ADDR;
        Serial.println("Buffer wrapped around!");
        flash.eraseSector(FLASH_START_ADDR);
      }

      if(!flash.writeStruct(write_addr, data))
      {
        Serial.println("Write Failed");
      }
      else
      {
        //Serial.print("Write OK");
        write_addr += sizeof(imu_data_t);
      }
    }
    else
    {
      Serial.println("BMI160 read failed");
    }
    lastWriteTime = millis();
  }

  int touchvalue = touchRead(TOUCH_PIN);


  static unsigned long touchStartTime = 0;
  static bool touchActive = false;

  if(touchvalue < TOUCH_THRE)
  {
    if(!touchActive)
    {
      touchActive = true;
      touchStartTime = millis();
      Serial.println("Touch started...");
    }
    else if(millis() - touchStartTime > 2000)
    {
      // Long press detected - clear single page
      Serial.println("Long press detected! Clearing page...");
      flash.eraseSector(FLASH_START_ADDR);
      write_addr = FLASH_START_ADDR;
      lastWriteTime = millis();
      Serial.println("Page cleared. Starting fresh.");
      touchActive = false;
      delay(1000);
      return;
    }
  }
  else
  {
    if(touchActive)
    {

      uint32_t total_entries = FLASH_PAGE_SIZE / sizeof(imu_data_t);
      uint32_t current_entries = (write_addr - FLASH_START_ADDR) / sizeof(imu_data_t);

      for(int i = 0; i < 5; i++)
      {
        imu_data_t read_data;
        uint32_t read_addr;

        if(write_addr == FLASH_START_ADDR) {
          read_addr = FLASH_START_ADDR + FLASH_PAGE_SIZE - (i + 1) * sizeof(imu_data_t);
        } else {
          read_addr = write_addr - (i + 1) * sizeof(imu_data_t);
          if(read_addr < FLASH_START_ADDR) {
            read_addr = FLASH_START_ADDR + FLASH_PAGE_SIZE - (FLASH_START_ADDR - read_addr);
          }
        }

        flash.readStruct(read_addr, read_data);

        Serial.print("Data[");
        Serial.print(i);
        Serial.print("]");
        Serial.print(" Accel (g): ");
        for(int j=0;j<3;j++){
          Serial.print(read_data.accel[j] / 16384.0, 4); Serial.print("\t");
        }

        Serial.print("Gyro (rad/s): ");
        for(int j=0;j<3;j++){
          Serial.print(read_data.gyro[j] * 3.14159 / 180.0, 4); Serial.print("\t");
        }

        Serial.println();
      }
      touchActive = false;
    }
  }

  delay(500);
}