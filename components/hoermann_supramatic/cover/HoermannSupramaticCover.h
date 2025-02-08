#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/cover/cover.h"
#include "esphome/components/hoermann_supramatic/SupramaticControlClient.h"

namespace esphome
{
    namespace hoermann_supramatic
    {
        class HoermannSupramaticCover : public Component, public cover::Cover, public SupramaticControlClient
        {
        public:
            const char *TAG = "supramatic_control_cover";

            void setup() override;
            void loop() override;
            void dump_config() override;
            cover::CoverTraits get_traits() override;

            virtual void OnStatusUpdated(const Status& status) override;

        protected:
            void control(const cover::CoverCall &call) override;
        };
    }
}
