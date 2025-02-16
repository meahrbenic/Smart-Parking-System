
#define SENZOR "projekat/senzor"

#include "mbed.h"

#define MQTTCLIENT_QOS2 0

#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include <string.h>


#define MBED_CONF_APP_WIFI_SSID "ETF-WiFi-Guest"
#define MBED_CONF_APP_WIFI_PASSWORD "ETF-WiFi-Guest"

#include "ESP8266Interface.h"

ESP8266Interface wifi(PTE0, PTE1);

int arrivedcount = 0;

#define MQTT_CLIENT_NAME "FRDM_KL25Z42"


AnalogIn ir(A0);
int signal = -1;

char* str;
int prethodni_signal = -1;
bool taster_state=1;


int main(int argc, char* argv[]) {
   
    SocketAddress a;

    printf("\r\nConnecting to WiFi...\r\n");
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\r\nConnection error\r\n");
        return -1;
    }

    printf("Success\r\n\r\n");
    printf("MAC: %s\r\n", wifi.get_mac_address());
    wifi.get_ip_address(&a);
    printf("IP: %s\r\n", a.get_ip_address());
    wifi.get_netmask(&a);
    printf("Netmask: %s\r\n", a.get_ip_address());
    wifi.get_gateway(&a);
    printf("Gateway: %s\r\n", a.get_ip_address());
    printf("RSSI: %d\r\n\r\n", wifi.get_rssi());

    MQTTNetwork mqttNetwork(&wifi);


    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);

    const char* hostname = "broker.hivemq.com";
    int port = 1883;
    printf("Connecting to %s:%d\r\n", hostname, port);
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);
    else
        printf("Connected to broker!\r\n");

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = MQTT_CLIENT_NAME;
    data.username.cstring = "";
    data.password.cstring = "";
    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\r\n", rc);

    MQTT::Message message;

    // QoS 0
    char buf[100];

    while(1) {

        if(ir.read() > 1.3/3.3) signal = 1;
        else signal = 0;
        
        if (prethodni_signal != signal) {
            prethodni_signal = signal;
            sprintf(buf, "%d", prethodni_signal);
            message.qos = MQTT::QOS0;
            message.retained = false;
            message.dup = false;
            message.payload = (void*)buf;
            message.payloadlen = strlen(buf);
            rc = client.publish(SENZOR, message);
        }

        wait_us(1e6);
    }
}
