#pragma once

#include <vector>
#include <stdint.h>

#include "esphome.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"

#include "SupramaticCommand.h"
#include "SupramaticControlClient.h"

namespace esphome
{
    namespace hoermann_supramatic
    {
        class SupramaticControl : public Component, public uart::UARTDevice
        {
        public:
            const char *TAG = "supramatic_control_cover";

            enum Action
            {
                ACTION_STOP = 0,
                ACTION_OPEN,
                ACTION_CLOSE,
                ACTION_VENTING,
                ACTION_TOGGLE_LIGHT,
                ACTION_EMERGENCY_STOP,
                ACTION_IMPULSE
            };

            void
            setup() override;
            void loop() override;
            void dump_config() override;

            void set_action(SupramaticControl::Action action);

            void register_client(SupramaticControlClient *client);

            void register_supramatic_control_client(SupramaticControlClient *node)
            {
                node->set_control(this);
                register_client(node);
            }

            void set_sensor_error(binary_sensor::BinarySensor *sensor_error)
            {
                this->_sensor_error = sensor_error;
            }

            void set_sensor_prewarn(binary_sensor::BinarySensor *sensor_prewarn)
            {
                this->_sensor_prewarn = sensor_prewarn;
            }

            void set_sensor_optrelay(binary_sensor::BinarySensor *sensor_optrelay)
            {
                this->_sensor_optrelay = sensor_optrelay;
            }

            void set_sensor_pressure(sensor::Sensor *sensor_pressure)
            {
                this->_sensor_pressure = sensor_pressure;
            }

            void set_sensor_humidity(sensor::Sensor *sensor_humidity)
            {
                this->_sensor_humidity = sensor_humidity;
            }

            void set_sensor_temperature(sensor::Sensor *sensor_temperature)
            {
                this->_sensor_temperature = sensor_temperature;
            }

            // void set_control_impulse(button::Button *control_impulse)
            // {
            //     this->_control_impulse = control_impulse;
            // }

            // void set_control_emergstop(button::Button *control_emergstop)
            // {
            //     this->_control_emergstop = control_emergstop;
            // }

            // void set_control_venting(switch_::Switch *control_venting)
            // {
            //     this->_control_venting = control_venting;
            // }

            // void set_control_light(light::LightOutput *control_light)
            // {
            //     this->_control_light = control_light;
            // }

            // void set_control_cover(cover::Cover *control_cover)
            // {
            //     this->_control_cover = control_cover;
            // }

        private:
            uint16_t _broadcastStatus{0};
            uint8_t _counter{0};
            SupramaticCommand *_command{SupramaticCommand::IDLE};
            SupramaticControlClient::Status _status;
            std::vector<SupramaticControlClient *> _clients;

            binary_sensor::BinarySensor *_sensor_error{nullptr};
            binary_sensor::BinarySensor *_sensor_prewarn{nullptr};
            binary_sensor::BinarySensor *_sensor_optrelay{nullptr};
            sensor::Sensor *_sensor_pressure{nullptr};
            sensor::Sensor *_sensor_humidity{nullptr};
            sensor::Sensor *_sensor_temperature{nullptr};
            // button::Button *_control_impulse{nullptr};
            // button::Button *_control_emergstop{nullptr};
            // switch_::Switch *_control_venting{nullptr};
            // light::LightOutput *_control_light{nullptr};
            // cover::Cover *_control_cover{nullptr};

            void send_command(SupramaticCommand *command, uint8_t counter);
            void parse_status();
        };
    }
}