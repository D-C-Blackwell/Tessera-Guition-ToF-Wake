#include "guition_tof_wake.h"

#include <cmath>

namespace esphome::guition_tof_wake {

bool GuitionTofWake::settings(tessera::SettingsPage &page) {
  if (wake_distance_ == nullptr) return false;

  page.icon = "\U000F0D91";
  page.number(text("wake_distance"), 10, 200, 10, " cm",
              [this]() {
                return std::isnan(wake_distance_->state) ? 100 : static_cast<int>(std::lround(wake_distance_->state));
              },
              [this](int value) {
                auto call = wake_distance_->make_call();
                call.set_value(value);
                call.perform();
              });
  return true;
}

}  // namespace esphome::guition_tof_wake
