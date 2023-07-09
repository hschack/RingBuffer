#include <Arduino.h>
#include <stdint.h>

HardwareSerial Serial2(PA3, PA2);

#define BUFFER_SIZE 32

uint8_t buffer[BUFFER_SIZE];
int head = 0;
int tail = 0;
int count = 0; // Number of elements in the buffer

bool addToBuffer(uint8_t data);
bool removeFromBuffer(uint8_t& data);

void setup() 
{
  Serial2.begin(115200);
}

void loop() 
{
  // Add some sample data to the buffer
  for (int i = 0; i < 40; i++) {
    if (!addToBuffer(i)) {
      // Buffer is full, handle the overflow
      // For example, discard the new data or perform necessary action
    }
  }

  // Print the data from the buffer
  uint8_t data;
  while (removeFromBuffer(data)) 
  {
    Serial2.println(data);
  }

  delay(1000);
}

bool addToBuffer(uint8_t data) 
{
  int next = (head + 1) % BUFFER_SIZE;

  // Check if the buffer is full
  if (next != tail) {
    buffer[head] = data;
    head = next;
    count++;
    return true; // Buffer is not full
  }
  else {
    // Buffer is full, discard the new data
    return false; // Buffer is full
  }
}

bool removeFromBuffer(uint8_t& data) 
{
  if (count > 0) {
    data = buffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    count--;
    return true; // Data is available
  }
  else {
    // Buffer is empty, no data available
    return false; // No data available
  }
}