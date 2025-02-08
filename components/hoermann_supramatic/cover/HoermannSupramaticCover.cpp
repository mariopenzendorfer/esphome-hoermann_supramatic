#include "HoermannSupramaticCover.h"

namespace esphome
{
    namespace hoermann_supramatic
    {
        void HoermannSupramaticCover::setup()
        {
        }

        void HoermannSupramaticCover::loop()
        {
        }

        void HoermannSupramaticCover::dump_config()
        {
        }

        cover::CoverTraits HoermannSupramaticCover::get_traits()
        {
            cover::CoverTraits traits;
            traits.set_is_assumed_state(false);
            traits.set_supports_position(false);
            traits.set_supports_stop(true);
            traits.set_supports_toggle(true);
            traits.set_supports_tilt(false);
            return traits;
        }

        void HoermannSupramaticCover::control(const cover::CoverCall &call)
        {
            if( call.get_stop() )
            {
                _control->set_action(SupramaticControl::ACTION_STOP);
            }
            else if (call.get_position().has_value())
            {
                float pos = call.get_position().value();

                if( pos == 1.0f)
                {
                    _control->set_action(SupramaticControl::ACTION_OPEN);
                }
                else
                {
                    _control->set_action(SupramaticControl::ACTION_CLOSE);
                }
            }
        }

        void HoermannSupramaticCover::OnStatusUpdated(const Status& status)
        {
            if (status.cover == CoverState::OPEN)
            {
                this->position = 1.0f;
            }
            else if (status.cover == CoverState::CLOSED)
            {
                this->position = 0.0f;
            }
            else if (status.cover == CoverState::CLOSING)
            {
                this->position = 0.25f;
            }
            else if (status.cover == CoverState::OPENING)
            {
                this->position = 0.75f;
            }
            else
            {
                this->position = 0.5f;
            }

            this->publish_state();
        }
    } // namespace hoermann_supramatic
} // namespace esphome
