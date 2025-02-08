import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import cover
from esphome.const import CONF_ID
import hoermann_supramatic as hs

DEPENDENCIES = ["cover"]

hoermann_supramatic_ns = cg.esphome_ns.namespace("hoermann_suparamatic")
HoermannSupramaticCoverComponent = hoermann_supramatic_ns.class_(
    "HoermannSupramaticCover", cg.Component, cover.Cover
)

CONFIG_SCHEMA = (
    cover.COVER_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(HoermannSupramaticCoverComponent),
        }
    )
    .extend(hs.SUPRAMATIC_CONTROL_CLIENT_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await cover.register_cover(var, config)
