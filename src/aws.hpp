#ifndef AWS_HPP
#define AWS_HPP

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "secret.h"

static WiFiClientSecure httpsClient;
static PubSubClient mqttClient(httpsClient);

void connectAWSIoT() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP8266")) {
      Serial.println("AWSIoT Connected.");
    } else {
      Serial.print("Failed. Error state=");
      Serial.print(mqttClient.state());
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setupAWS() {
  // AWSへの接続処理
  //証明書、秘密鍵のオブジェクト作成
  BearSSL::X509List cert(ROOT_CA);
  BearSSL::X509List client_crt(CERTIFICATE);
  BearSSL::PrivateKey key(PRIVATE_KEY);

  httpsClient.setTrustAnchors(&cert);
  httpsClient.setClientRSACert(&client_crt, &key);
  mqttClient.setServer(CLOUD_ENDPOINT, CLOUD_PORT);
  // mqttClient.setCallback(mqttCallback);
  connectAWSIoT();
}

void publish(float tmp) {
  char message[128] = {0};
  sprintf(message, "{\"value\": %f}", tmp);

  if (!mqttClient.publish(CLOUD_TOPIC, message)) {
    Serial.println("Failed to publish\n");
  } else {
    Serial.print("Succeed to publish: ");
    Serial.println(message);
  }
}

#endif