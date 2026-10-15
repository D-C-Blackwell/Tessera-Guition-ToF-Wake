#pragma once

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "esphome/components/smart_display/plugin_api.h"

namespace esphome::guition_tof_wake {

class GuitionTofWake : public Component, public tessera::Plugin {
 public:
  float get_setup_priority() const override { return setup_priority::LATE; }
  bool settings(tessera::SettingsPage &page) override;

  void set_wake_distance(number::Number *wake_distance) { wake_distance_ = wake_distance; }

 protected:
  number::Number *wake_distance_{nullptr};
};

}  // namespace esphome::guition_tof_wake
