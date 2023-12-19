#include <Wire.h>
#include <WiFi.h>

#define MAX_NETWORKS 10

const char* knownNetworks[MAX_NETWORKS] = {"SSID #0", "SSID #1", "SSID #2", "SSID #3"};
double features[MAX_NETWORKS];

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}

void loop() {
    int numNetworks = WiFi.scanNetworks();

    for (int i = 0; i < numNetworks; i++) {
        Serial.println(WiFi.SSID(i));

        delay(3000);
        scan();
        printFeatures();
        delay(3000);
        scan();
        classify();
    }
}

void scan() {
    int numNetworks = WiFi.scanNetworks();

    resetFeatures();

    // assign RSSIs to feature vector
    for (int i = 0; i < numNetworks; i++) {
        const char* ssid = WiFi.SSID(i).c_str();
        int networkIndex = findNetworkIndex(ssid);

        // only create feature if the current SSID is a known one
        if (networkIndex != -1)
            features[networkIndex] = WiFi.RSSI(i);
    }
}

int findNetworkIndex(const char* ssid) {
    for (int i = 0; i < MAX_NETWORKS; i++) {
        if (strcmp(ssid, knownNetworks[i]) == 0)
            return i;
    }
    return -1; // SSID not found
}

// reset all features to 0
void resetFeatures() {
    const int numFeatures = sizeof(features) / sizeof(double);

    for (int i = 0; i < numFeatures; i++)
        features[i] = 0;
}

void printFeatures() {
    const int numFeatures = sizeof(features) / sizeof(double);

    for (int i = 0; i < numFeatures; i++) {
        Serial.print(features[i]);
        Serial.print(i == numFeatures - 1 ? '\n' : ',');
    }
}

void classify() {
    Serial.print("You are in ");
    // Implement the classification logic if needed
}