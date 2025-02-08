#include "SupramaticControl.h"

namespace esphome
{
    namespace hoermann_supramatic
    {
        void SupramaticControl::setup()
        {
        }

        void SupramaticControl::loop()
        {
            std::vector<uint8_t> buffer;

            while (available())
            {
                buffer.push_back(read());

                delay(10);
            }

            if (buffer.empty())
            {
                return;
            }

            uint8_t address = buffer[0];
            uint8_t length = buffer[1] & 0x0F;
            uint8_t counter = (buffer[1] & 0xF0) + 0x10;

            if (address == 0x00)
            {
                if (length == 0x02)
                {
                    _broadcastStatus = buffer[2] | ((uint16_t)buffer[3] << 8);
                    parse_status();
                }
                else
                {
                    ESP_LOGI(TAG, "Invalid message %d %d", address, length);
                }
            }
            else if (address == 0x28)
            {
                uint8_t command = buffer[2];

                if (length == 0x02 && command == 0x01)
                {
                    send_command(SupramaticCommand::SCAN, counter);

                    ESP_LOGI(TAG, "Sending scan command");
                }
                else if (length == 0x01 && command == 0x20)
                {
                    send_command(_command, counter);

                    if(_command != SupramaticCommand::IDLE)
                    {
                        ESP_LOGI(TAG, "Sending command");
                    }

                    _command = SupramaticCommand::IDLE;
                }
                else
                {
                    ESP_LOGI(TAG, "Invalid message %d %d", address, length);
                }
            }
            else
            {
                ESP_LOGI(TAG, "Invalid message %d %d", address, length);
            }
        }

        void SupramaticControl::dump_config()
        {
        }

        void SupramaticControl::send_command(SupramaticCommand *command, uint8_t counter)
        {
            write_array(command->get_bytes(counter), command->get_length());
        }

        void SupramaticControl::set_action(SupramaticControl::Action action)
        {
            ESP_LOGI(SupramaticControl::TAG, "Received action %d", action);

            switch (action)
            {
            case ACTION_STOP:
            {
                uint8_t status = _broadcastStatus & 0x60;
                if ((status == 0x40) || (status == 0x60))
                {
                    this->_command = SupramaticCommand::IMPULSE;
                }
            }
            break;
            case ACTION_OPEN:
                this->_command = SupramaticCommand::OPEN;
                break;
            case ACTION_CLOSE:
                this->_command = SupramaticCommand::CLOSE;
                break;
            case ACTION_VENTING:
                this->_command = SupramaticCommand::VENTING;
                break;
            case ACTION_TOGGLE_LIGHT:
                this->_command = SupramaticCommand::TOGGLE_LIGHT;
                break;
            case ACTION_EMERGENCY_STOP:
                this->_command = SupramaticCommand::EMERGENCY_STOP;
                break;
            case ACTION_IMPULSE:
                this->_command = SupramaticCommand::IMPULSE;
                break;
            default:
                this->_command = SupramaticCommand::IDLE;
                break;
            }
        }

        void SupramaticControl::parse_status()
        {
            ESP_LOGI(SupramaticControl::TAG, "Received status %x", _broadcastStatus);

            uint8_t statusByte0 = (uint8_t)_broadcastStatus & 0x00FF;
            uint8_t statusByte1 = (uint8_t)(_broadcastStatus >> 8) & 0x00FF;

            if ((statusByte0 & 0x01) == 0x01)
            {
                _status.cover = SupramaticControlClient::CoverState::OPEN;
            }
            else if ((statusByte0 & 0x02) == 0x02)
            {
                _status.cover = SupramaticControlClient::CoverState::CLOSED;
            }
            else if ((statusByte0 & 0x60) == 0x40)
            {
                _status.cover = SupramaticControlClient::CoverState::OPENING;
            }
            else if ((statusByte0 & 0x60) == 0x60)
            {
                _status.cover = SupramaticControlClient::CoverState::CLOSING;
            }
            else
            {
                _status.cover = SupramaticControlClient::CoverState::STOPPED;
            }

            _status.option_relay = (statusByte0 & 0x04) == 0x04;
            _status.light = (statusByte0 & 0x08) == 0x08;
            _status.error = (statusByte0 & 0x10) == 0x10;
            _status.venting = (statusByte0 & 0x80) == 0x80;
            _status.prewarn = (statusByte1 & 0x01) == 0x01;

            for (SupramaticControlClient *client : _clients)
            {
                client->OnStatusUpdated(_status);
            }
        }

        void SupramaticControl::register_client(SupramaticControlClient *client)
        {
            _clients.push_back(client);
        }
    }
}