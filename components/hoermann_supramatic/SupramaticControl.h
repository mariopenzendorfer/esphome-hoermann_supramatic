#pragma once

#include "esphome.h"
#include "esphome/core/component.h"

static const char *TAG = "supramatic_control";

namespace esphome
{
    namespace smartmeter
    {
        class SupramaticControl : public Component,
                                  public uart::UARTDevice
        {
        public:
            void setup() override;
            void loop() override;
            void dump_config() override;

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

            void set_control_impulse(button::Button *control_impulse)
            {
                this->_control_impulse = control_impulse;
            }

            void set_control_emergstop(button::Button *control_emergstop)
            {
                this->_control_emergstop = control_emergstop;
            }

            void set_control_venting(switch_::Switch *control_venting)
            {
                this->_control_venting = control_venting;
            }

            void set_control_light(light::LightOutput *control_light)
            {
                this->_control_light = control_light;
            }

            void set_control_cover(cover::Cover *control_cover)
            {
                this->_control_cover = control_cover;
            }

        private:
            int receiveBufferIndex = 0;                     // Current position of the receive buffer
            const static int receiveBufferSize = 1024;      // Size of the receive buffer
            unsigned char receiveBuffer[receiveBufferSize]; // Stores the packet currently being received
            unsigned long lastRead = 0;                     // Timestamp when data was last read
            int readTimeout = 1000;                         // Time to wait after last byte before considering data complete

            binary_sensor::BinarySensor *_sensor_error{nullptr};
            binary_sensor::BinarySensor *_sensor_prewarn{nullptr};
            binary_sensor::BinarySensor *_sensor_optrelay{nullptr};
            sensor::Sensor *_sensor_pressure{nullptr};
            sensor::Sensor *_sensor_humidity{nullptr};
            sensor::Sensor *_sensor_temperature{nullptr};
            button::Button *_control_impulse{nullptr};
            button::Button *_control_emergstop{nullptr};
            switch_::Switch *_control_venting{nullptr};
            light::LightOutput *_control_light{nullptr};
            cover::Cover *_control_cover{nullptr};
        };
    }
}