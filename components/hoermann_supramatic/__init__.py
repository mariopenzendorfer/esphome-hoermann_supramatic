import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor, binary_sensor, cover, light, button, switch
from esphome.const import (
    CONF_ID,
    DEVICE_CLASS_PRESSURE,
    DEVICE_CLASS_PROBLEM,
    DEVICE_CLASS_HUMIDITY,
    DEVICE_CLASS_SAFETY,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_SWITCH,
    DEVICE_CLASS_BUTTON,
    STATE_CLASS_MEASUREMENT,
    UNIT_HECTOPASCAL,
    UNIT_CELSIUS,
    UNIT_PERCENT,
)

DEPENDENCIES = ["uart"]

hoermann_supramatic_ns = cg.esphome_ns.namespace("hoermann_suparamatic")
SupramaticControlComponent = hoermann_supramatic_ns.class_(
    "SupramaticControl", cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(SupramaticControlComponent),
            cv.Optional("error"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_PROBLEM
            ),
            cv.Optional("prewarn"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_SAFETY
            ),
            cv.Optional("optrelay"): binary_sensor.binary_sensor_schema(
                device_class=DEVICE_CLASS_SWITCH
            ),
            cv.Optional("pressure"): sensor.sensor_schema(
                accuracy_decimals=1,
                unit_of_measurement=UNIT_HECTOPASCAL,
                device_class=DEVICE_CLASS_PRESSURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("humidity"): sensor.sensor_schema(
                accuracy_decimals=1,
                unit_of_measurement=UNIT_PERCENT,
                device_class=DEVICE_CLASS_HUMIDITY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional("temperature"): sensor.sensor_schema(
                accuracy_decimals=1,
                unit_of_measurement=UNIT_CELSIUS,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(uart.UART_DEVICE_SCHEMA)
)

CONF_SUPRAMATIC_CONTROL_CLIENT_ID = "supramatic_control_client_id"

SUPRAMATIC_CONTROL_CLIENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SUPRAMATIC_CONTROL_CLIENT_ID): cv.use_id(SupramaticControlComponent),
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if "error" in config:
        cg.add(
            var.set_sensor_prewarn(
                await binary_sensor.new_binary_sensor(config["error"])
            )
        )

    if "prewarn" in config:
        cg.add(
            var.set_sensor_prewarn(
                await binary_sensor.new_binary_sensor(config["prewarn"])
            )
        )

    if "optrelay" in config:
        cg.add(
            var.set_sensor_optrelay(
                await binary_sensor.new_binary_sensor(config["optrelay"])
            )
        )

    if "pressure" in config:
        cg.add(var.set_sensor_pressure(await sensor.new_sensor(config["pressure"])))

    if "humidity" in config:
        cg.add(var.set_sensor_humidity(await sensor.new_sensor(config["humidity"])))

    if "temperature" in config:
        cg.add(
            var.set_sensor_temperature(await sensor.new_sensor(config["temperature"]))
        )

    # cg.add(
    #     var.set_control_impulse(
    #         await button.new_button(button.button_schema(CLASS_IMPULSE_BUTTON, device_class=DEVICE_CLASS_BUTTON))
    #     )
    # )

    # cg.add(
    #     var.set_control_emergstop(
    #         await button.new_button(button.button_schema(CLASS_EMERGSTOP_BUTTON, device_class=DEVICE_CLASS_BUTTON))
    #     )
    # )

    # cg.add(var.set_control_light(await light.new_light(light.light())))

    # cg.add(var.set_control_venting(await switch.new_switch(switch.switch_schema())))
