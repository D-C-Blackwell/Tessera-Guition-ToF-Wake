"""VL53L0X approach wake for a Guition Tessera screen."""
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import number, smart_display
from esphome.const import CONF_ID

DEPENDENCIES = ["smart_display", "number"]

CONF_WAKE_DISTANCE = "wake_distance"

guition_tof_wake_ns = cg.esphome_ns.namespace("guition_tof_wake")
GuitionTofWake = guition_tof_wake_ns.class_("GuitionTofWake", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(GuitionTofWake),
        cv.Required(CONF_WAKE_DISTANCE): cv.use_id(number.Number),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await smart_display.register_plugin(var, __file__)
    cg.add(var.set_wake_distance(await cg.get_variable(config[CONF_WAKE_DISTANCE])))
