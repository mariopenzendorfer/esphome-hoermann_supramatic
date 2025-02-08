#pragma once

#include <vector>
#include <stdint.h>

namespace esphome
{
    namespace hoermann_supramatic
    {
        class SupramaticCommand
        {
        public:
            static SupramaticCommand * SCAN;
            static SupramaticCommand * IDLE;
            static SupramaticCommand * OPEN;
            static SupramaticCommand * CLOSE;
            static SupramaticCommand * VENTING;
            static SupramaticCommand * TOGGLE_LIGHT;
            static SupramaticCommand * EMERGENCY_STOP;
            static SupramaticCommand * IMPULSE;

            SupramaticCommand(unsigned int opcode);

            SupramaticCommand();

            unsigned char *get_bytes(unsigned int counter);

            unsigned char *get_bytes();

            unsigned int get_length();
        
        private:
            std::vector<uint8_t> _bytes;
            uint8_t _counterInit;
        };
    }
}