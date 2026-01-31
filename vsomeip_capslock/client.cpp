#include <iostream>
#include <vsomeip/vsomeip.hpp>
#include <thread>

#define SERVICE_ID 0x1234
#define INSTANCE_ID 0x5678
#define METHOD_ID 0x0001

std::shared_ptr<vsomeip::application> app;

void on_response(const std::shared_ptr<vsomeip::message> &resp) {
  auto data = resp->get_payload()->get_data();
  bool on = data[0];
  std::cout << "CapsLock state received: " << (on ? "ON" : "OFF") << std::endl;
}

void on_availability(vsomeip::service_t service, vsomeip::instance_t instance,
                     bool is_available) {
  while (true) {
    if (!is_available)
      return;

    std::cout << "Service AVAILABLE, sending request...\n";

    auto request = vsomeip::runtime::get()->create_request();
    request->set_service(SERVICE_ID);
    request->set_instance(INSTANCE_ID);
    request->set_method(METHOD_ID);

    auto payload = vsomeip::runtime::get()->create_payload();
    payload->set_data({});
    request->set_payload(payload);

    app->send(request);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

int main() {
  app = vsomeip::runtime::get()->create_application("capslock_client");
  app->init();

  app->register_message_handler(SERVICE_ID, INSTANCE_ID, METHOD_ID,
                                on_response);

  app->register_availability_handler(SERVICE_ID, INSTANCE_ID, on_availability);

  app->request_service(SERVICE_ID, INSTANCE_ID);

  app->start();
  return 0;
}
