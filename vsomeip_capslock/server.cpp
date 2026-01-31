#include <fstream>
#include <iostream>
#include <vsomeip/vsomeip.hpp>

#define SERVICE_ID  0x1234
#define INSTANCE_ID 0x5678
#define METHOD_ID   0x0001

std::shared_ptr<vsomeip::application> app;

bool read_capslock() {
    std::ifstream file("/sys/class/leds/input7::capslock/brightness");
    int state = 0;
    if (file.is_open())
        file >> state;
    return state == 1;
}

void on_request(const std::shared_ptr<vsomeip::message> &req) {
    bool on = read_capslock();

    // write to file
    std::ofstream out("/home/yasmine/Desktop/capslock_state.txt");
    out << (on ? "capslock on (: \n" : "capslock off :( \n");
    out.close();

    std::cout << "CapsLock is: " << (on ? "ON" : "OFF") << std::endl;

    // send response
    auto resp = vsomeip::runtime::get()->create_response(req);
    auto payload = vsomeip::runtime::get()->create_payload();

    payload->set_data({ static_cast<vsomeip::byte_t>(on) });
    resp->set_payload(payload);

    app->send(resp);
}

int main() {
    app = vsomeip::runtime::get()->create_application("capslock_server");
    app->init();

    app->register_message_handler(
        SERVICE_ID, INSTANCE_ID, METHOD_ID, on_request
    );

    app->offer_service(SERVICE_ID, INSTANCE_ID);

    std::cout << "SOME/IP server running...\n";
    app->start();
    return 0;
}
