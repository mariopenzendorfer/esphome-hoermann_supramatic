#pragma once

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/cover/cover.h"

namespace esphome
{
    namespace hoermann_supramatic
    {
        class HoermannSupramaticCover : public Component, public cover::Cover
        {
        public:
            void setup() override;
            void loop() override;
            void dump_config() override;
            cover::CoverTraits get_traits() override;

        protected:
            void control(const cover::CoverCall &call) override;
        }
    }
}
