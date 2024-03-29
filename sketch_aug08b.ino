// Dependencies
#include <TuyaWifi.h>

// Defining Data Points (DP)
#define DPID_SWITCH1 101
#define DPID_SWITCH2 102
#define DPID_SWITCH3 103
#define DPID_SWITCH4 104
#define DPID_SWITCH5 105
#define DPID_SWITCH6 106
#define DPID_SWITCH7 107
#define DPID_STRING1 108

unsigned char dp_array[][2] =
{
  {DPID_SWITCH1, DP_TYPE_BOOL},
  {DPID_SWITCH2, DP_TYPE_BOOL},
  {DPID_SWITCH3, DP_TYPE_BOOL},
  {DPID_SWITCH4, DP_TYPE_BOOL},
  {DPID_SWITCH5, DP_TYPE_BOOL},
  {DPID_SWITCH6, DP_TYPE_BOOL},
  {DPID_SWITCH7, DP_TYPE_BOOL}
};

// Settings up mem registers just for uploading to Tuya's cloud
// See TuyaWifi::mcu_get_dp_download_data function signature/prototype for why these are unsigned char instead of bool
// Also: see the comment at mixly.ino at function 'unsigned char dp_process(...)'
unsigned char mem1;
unsigned char mem2;
unsigned char mem3;
unsigned char mem4;
unsigned char mem5;
unsigned char mem6;
unsigned char mem7;
int KEY_TIME;

// Prototyping functions
unsigned char dp_process(unsigned char dpid, const unsigned char value[], unsigned short length);
void dp_update_all(void);

// Settings
unsigned char pid[] = {"rtoqxyuwhnpr3aya"}; // Change me
unsigned char mcu_ver[] = {"1.0.0"};        // Change me

// Tuya object
TuyaWifi my_device;

// Here are some delicious arduino codes
void setup() {
  // Setting up pin layouts
  pinMode(3, OUTPUT);
  pinMode(A0, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(7, INPUT_PULLUP);
  digitalWrite(A0, HIGH);

  // Setting up Tuya IoT SDK
  Serial.begin(9600);
  my_device.init(pid, mcu_ver);
  my_device.set_dp_cmd_total(dp_array, 7);
  my_device.dp_process_func_register(dp_process);
  my_device.dp_update_all_func_register(dp_update_all);
  KEY_TIME = 80;
  // SETUP_MUSIC_PLAYER
  tone(5, 532); delay(KEY_TIME); noTone(5);
  tone(5, 587); delay(KEY_TIME); noTone(5);
  tone(5, 659); delay(KEY_TIME); noTone(5);
  tone(5, 698); delay(KEY_TIME); noTone(5);
  tone(5, 784); delay(KEY_TIME); noTone(5);
  tone(5, 880); delay(KEY_TIME); noTone(5);
  tone(5, 988); delay(KEY_TIME); noTone(5);
}

void music_start() {
  digitalWrite(3, HIGH);
  delay(1000);
  // TODO: Implement actual music player
}
void loop() {
  my_device.uart_service(); // Mysterious black box that updates mem1-7 (?)

  // Network Connection Mode
  if (digitalRead(7) == LOW) {
    delay(80);
    if (digitalRead(7) == LOW) {
      my_device.mcu_set_wifi_mode(SMART_CONFIG);
    }
  }

  // Process physical keys and beeps if pressed
  if (digitalRead(A0) == LOW)
  {
    digitalWrite(3, HIGH);
    // Do nothing, TODO: Adding functionality for the key 0
    my_device.mcu_dp_update(DPID_SWITCH1, false, 1);
    my_device.mcu_dp_update(DPID_SWITCH2, false, 1);
    my_device.mcu_dp_update(DPID_SWITCH3, false, 1);
    my_device.mcu_dp_update(DPID_SWITCH4, false, 1);
    my_device.mcu_dp_update(DPID_SWITCH5, false, 1);
    my_device.mcu_dp_update(DPID_SWITCH6, false, 1);
    my_device.mcu_dp_update(DPID_SWITCH7, false, 1);
  }
  else if (digitalRead(13) == LOW) 
  {
    tone(4, 532); // C5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH1, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH1, false, 1);
  }
  else if (digitalRead(12) == LOW) {
    tone(4, 587); // D5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH2, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH2, false, 1);
  }
  else if (digitalRead(11) == LOW) {
    tone(4, 659); // E5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH3, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH3, false, 1);
  }
  else if (digitalRead(10) == LOW) {
    tone(4, 698); // F5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH4, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH4, false, 1);
  }
  else if (digitalRead(9) == LOW) {
    tone(4, 784); // G5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH5, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH5, false, 1);
  }
  else if (digitalRead(8) == LOW) {
    tone(4, 880); // A5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH6, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH6, false, 1);
  }
  else if (digitalRead(6) == LOW) {
    tone(4, 988); // B5
    digitalWrite(3, HIGH);
    my_device.mcu_dp_update(DPID_SWITCH7, true, 1);
    delay(150);
    my_device.mcu_dp_update(DPID_SWITCH7, false, 1);
  }
  else
  {
    noTone(4);
    digitalWrite(3, LOW);
  }

  // TODO: Implement remote key presses via Tuya
  // Process Tuya IoT app input
  /*
    mem1 --> C5
    mem2 --> D5
    mem3 --> E5
    mem4 --> F5
    mem5 --> G5
    mem6 --> A5
    mem7 --> B5
  */
  if (mem1 == true) // C5
  {
    tone(5, 532); // C5
    digitalWrite(3, HIGH);
  }
  else if (mem2 == true)  // D5
  {
    tone(5, 587); // D5
    digitalWrite(3, HIGH);
  }
  else if (mem3 == true)  // E5
  {
    tone(5, 659); // E5
    digitalWrite(3, HIGH);
  }
  else if (mem4 == true)  // F5
  {
    tone(5, 698); // F5
    digitalWrite(3, HIGH);
  }
  else if (mem5 == true)  // G5
  {
    tone(5, 784); // G5
    digitalWrite(3, HIGH);
  }
  else if (mem6 == true)  // A5
  {
    tone(5, 880); // A5
    digitalWrite(3, HIGH);
  }
  else if (mem7 == true)  // B5
  {
    tone(5, 988); // B5
    digitalWrite(3, HIGH);
  }
  else  // Oh yes, we are becoming YandereDev
  {
    noTone(5);
    //dp_update_all();  // I don't think this is necessary, since my_device.uart_services() already deals with this (?)
    // mem1-7 are only app *inputs*, we don't need to update those in here
  }  
}

// Here are some Tuya functions, god I miss Object Oriented Programming and Python
unsigned char dp_process(unsigned char dpid, const unsigned char value[], unsigned short length)
{
  switch (dpid)
  {
    case DPID_SWITCH1:
      // Question: what does TuyaWifi::mcu_get_dp_download_data return?
      // Fucking hell... it returns unsigned char, idk if Arduino can convert unsigned char to bool, but I bet it doesn't
      // According to Tuya SDK's example 'DataPointType.ino', every data's type returned by TuyaWifi::mcu_get_dp_download_data is unsigned char
      // Thanks, Tuya developers
      mem1 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH1, mem1, 1);
      break;

    case DPID_SWITCH2:
      mem2 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH2, mem2, 1);
      break;

    case DPID_SWITCH3:
      mem3 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH3, mem3, 1);
      break;

    case DPID_SWITCH4:
      mem4 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH4, mem4, 1);
      break;

    case DPID_SWITCH5:
      mem5 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH5, mem5, 1);
      break;

    case DPID_SWITCH6:
      mem6 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH6, mem6, 1);
      break;

    case DPID_SWITCH7:
      mem7 = my_device.mcu_get_dp_download_data(dpid, value, length);
      my_device.mcu_dp_update(DPID_SWITCH7, mem7, 1);
      break;

    default:
      break;
  }
}

void dp_update_all(void)
{
  my_device.mcu_dp_update(DPID_SWITCH1, mem1, 1);
  my_device.mcu_dp_update(DPID_SWITCH2, mem2, 1);
  my_device.mcu_dp_update(DPID_SWITCH3, mem3, 1);
  my_device.mcu_dp_update(DPID_SWITCH4, mem4, 1);
  my_device.mcu_dp_update(DPID_SWITCH5, mem5, 1);
  my_device.mcu_dp_update(DPID_SWITCH6, mem6, 1);
  my_device.mcu_dp_update(DPID_SWITCH7, mem7, 1);
}
