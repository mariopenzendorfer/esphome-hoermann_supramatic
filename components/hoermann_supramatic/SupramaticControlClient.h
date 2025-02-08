#pragma once

namespace esphome
{
    namespace hoermann_supramatic
    {
        class SupramaticControl; // forward declaration

        class SupramaticControlClient
        {
        public:
            enum CoverState
            {
                STOPPED = 0,
                OPEN,
                CLOSED,
                OPENING,
                CLOSING,
            };

            struct Status
            {
                SupramaticControlClient::CoverState cover;
                bool venting;
                bool error;
                bool prewarn;
                bool light;
                bool option_relay;
            };

            // SupramaticControlClient(SupramaticControl *control)
            // {
            //     control->register_client(this);
            // }
            SupramaticControlClient() {}

            virtual void OnStatusUpdated(const Status &status) = 0;

            void set_control(SupramaticControl *control)
            {
                _control = control;
            }
        
        protected:
            SupramaticControl* _control;
        };
    }
}