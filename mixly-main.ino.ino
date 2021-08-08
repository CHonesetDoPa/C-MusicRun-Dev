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
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A7, OUTPUT);
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

  if (digitalRead(7) == LOW) {
    delay(80);
    if (digitalRead(7) == LOW) {
      my_device.mcu_set_wifi_mode(SMART_CONFIG);
    }
  }
  // Process physical keys and beeps if pressed
  if (digitalRead(A0) == LOW) {

  } else if (digitalRead(13) == LOW) {
    int i = 0;
    while (digitalRead(13) == LOW) {
      for (int i = (i); i <= (i + 1); i = i + (1)) {
        tone(5, 532);
        digitalWrite(3, HIGH);
        mem1 = true;
        my_device.mcu_dp_update(DPID_SWITCH1, mem1, 1);
      }
    }
    mem1 = false;
    my_device.mcu_dp_update(DPID_SWITCH1, mem1, 1);
  } else if (digitalRead(12) == LOW) {
    tone(5, 587);
    digitalWrite(3, HIGH);
    mem2 = true;
    my_device.mcu_dp_update(DPID_SWITCH2, mem2, 1);
  } else if (digitalRead(11) == LOW) {
    tone(5, 659);
    digitalWrite(3, HIGH);
    mem3 = true;
    my_device.mcu_dp_update(DPID_SWITCH3, mem3, 1);
  } else if (digitalRead(10) == LOW) {
    tone(5, 698);
    digitalWrite(3, HIGH);
    mem4 = true;
    my_device.mcu_dp_update(DPID_SWITCH4, mem4, 1);
  } else if (digitalRead(9) == LOW) {
    tone(5, 784);
    digitalWrite(3, HIGH);
    mem5 = true;
    my_device.mcu_dp_update(DPID_SWITCH5, mem5, 1);
  } else if (digitalRead(8) == LOW) {
    tone(5, 880);
    digitalWrite(3, HIGH);
    mem6 = true;
    my_device.mcu_dp_update(DPID_SWITCH6, mem6, 1);
  } else if (digitalRead(6) == LOW) {
    tone(5, 988);
    digitalWrite(3, HIGH);
    mem6 = true;
    my_device.mcu_dp_update(DPID_SWITCH7, mem7, 1);
  } else if (mem1 == true) {
    while (mem1 == true) {
    }
  } else if (mem2 == true) {
    while (mem2 == true) {
    }
  } else if (mem3 == true) {
    while (mem3 == true) {
    }
  } else if (mem4 == true) {
    while (mem4 == true) {
    }
  } else if (mem5 == true) {
    while (mem5 == true) {
    }
  } else if (mem6 == true) {
    while (mem6 == true) {
    }
  } else if (mem7 == true) {
    while (mem7 == true) {
    }
  } else {
    noTone(5);
    dp_update_all;

  }

  my_device.uart_service();

  // TODO: Implement remote key presses via Tuya

  // According to SDK's example 'start.ino', there should be a Pin7. When pressed, the device
  // enters 'Connection Network Mode', but for simplicity, that won't be implemented here.
  // Go ahead and copy/paste the code for 'Connection Network Mode' here if you want.
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
