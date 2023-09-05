#include <iostream>
#include <string>
#include <cstring>
#include <mqtt/async_client.h>

class MqttPublisher : public virtual mqtt::callback, public virtual mqtt::iaction_listener {
public:
    MqttPublisher(const std::string& serverURI, const std::string& clientId)
        : serverURI_(serverURI), clientId_(clientId), mqttClient_(serverURI, clientId) {
        mqttClient_.set_callback(*this);
        mqtt::connect_options connOpts;
        connOpts.set_keep_alive_interval(20);
        connOpts.set_clean_session(true);
        mqttClient_.connect(connOpts, nullptr, *this);
    }

    ~MqttPublisher() {
        mqttClient_.disconnect()->wait();
    }

    void publish(const std::string& topic, const std::string& message) {
        mqtt::message_ptr pubmsg = mqtt::make_message(topic, message);
        mqttClient_.publish(pubmsg)->wait();
    }

    // MQTT callback functions
    void connection_lost(const std::string& cause) override {
        std::cout << "\nConnection lost: " << cause << std::endl;
    }

    void message_arrived(mqtt::const_message_ptr msg) override {}

    void delivery_complete(mqtt::delivery_token_ptr token) override {}

    // Action listener callback functions
    void on_failure(const mqtt::token& tok) override {
        std::cout << "Connection attempt failed: " << tok.get_message() << std::endl;
    }

    void on_success(const mqtt::token& tok) override {
        std::cout << "Connection success!" << std::endl;
    }

private:
    const std::string serverURI_;
    const std::string clientId_;
    mqtt::async_client mqttClient_;
};

int main() {
    // Replace the following values with your actual MQTT broker information.
    std::string serverURI = "tcp://mqtt.example.com:1883";
    std::string clientId = "my_client_id";

    MqttPublisher mqttPublisher(serverURI, clientId);

    // Replace this JSON string with your actual JSON data.
    std::string jsonData = "{\"name\": \"John\", \"age\": 30}";

    std::string topic = "my_topic"; // Replace this with the MQTT topic you want to publish to.

    mqttPublisher.publish(topic, jsonData);

    return 0;
}
