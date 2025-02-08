# esphome-hoermann_supramatic

## Implementation in yaml

```
uart:
  tx_pin: GPIO1
  rx_pin: GPIO3
  baud_rate: 19200
  rx_buffer_size: 1024

hoermann_supramatic:

cover:
  - platform: hoermann_supramatic
    name: "Garagentor"
```

## RJ11

1 Not clear
2 24VDC
3 GND
4 Not clear
5 RS485, DATA-
6 RS485, DATA+
