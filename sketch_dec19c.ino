// Include Libraries
#include <esp_now.h>
#include <WiFi.h>


// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0xFC, 0xB4 , 0x67, 0x4E, 0xCD, 0xC8};

// Define a data
char a[32];
char a_receive[32];
long time_start = 0;
long time_end = 0;
long duration;
// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&a_receive, incomingData, sizeof(a_receive));
  time_end=millis();
  duration=time_end-time_start;
  Serial.print("time start: ");
  Serial.println(time_start);
  Serial.print("time end: ");
  Serial.println(time_end);
  Serial.print("duration: ");
  Serial.println(duration);
  Serial.println();
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("Character Value: ");
  Serial.println(a_receive);
  Serial.println();

}


void setup() {

  // Set up Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
 
 
  strcpy(a, "class1");
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &a, sizeof(a));
  time_start=millis();
 

  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(2000);
}