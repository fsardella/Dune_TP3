#include "server_config.h"


Config::Config(std::string YAMLpath) {
    YAML::Node node = YAML::LoadFile(YAMLpath);
    this->PORT = node["port"].as<std::string>();
    this->MAP_PATHS = node["maps"].as<std::string>();
    this->MAP_NAMES_PATH = node["maps_names"].as<std::string>();
    this->CLOCK_DELTA = node["clock"].as<int>();

    this->INITIAL_MONEY = node["initial_money"].as<uint32_t>();

    this->WORM_DELAY = node["worm"].as<uint32_t>();


    // BUILDINGS
    this->BASE_LIFE = node["base"]["life"].as<int16_t>();
    
    this->AIR_TRAP_ENERGY = node["air_trap"]["energy"].as<int32_t>();
    this->AIR_TRAP_PRICE = node["air_trap"]["price"].as<int32_t>();
    this->AIR_TRAP_LIFE = node["air_trap"]["life"].as<int16_t>();
    this->AIR_TRAP_CTIME = node["air_trap"]["ctime"].as<int16_t>();

    this->LIGHT_FACTORY_ENERGY = node["light_factory"]["energy"].as<int32_t>();
    this->LIGHT_FACTORY_PRICE = node["light_factory"]["price"].as<int32_t>();
    this->LIGHT_FACTORY_LIFE = node["light_factory"]["life"].as<int16_t>();
    this->LIGHT_FACTORY_CTIME = node["light_factory"]["ctime"].as<int16_t>();

    this->HEAVY_FACTORY_ENERGY = node["heavy_factory"]["energy"].as<int32_t>();
    this->HEAVY_FACTORY_PRICE = node["heavy_factory"]["price"].as<int32_t>();
    this->HEAVY_FACTORY_LIFE = node["heavy_factory"]["life"].as<int16_t>();
    this->HEAVY_FACTORY_CTIME = node["heavy_factory"]["ctime"].as<int16_t>();

    this->REFINERY_ENERGY = node["refinery"]["energy"].as<int32_t>();
    this->REFINERY_PRICE = node["refinery"]["price"].as<int32_t>();
    this->REFINERY_LIFE = node["refinery"]["life"].as<int16_t>();
    this->REFINERY_CAPACITY = node["refinery"]["capacity"].as<int32_t>();
    this->REFINERY_CTIME = node["refinery"]["ctime"].as<int16_t>();

    this->SILO_ENERGY = node["silo"]["energy"].as<int32_t>();
    this->SILO_PRICE = node["silo"]["price"].as<int32_t>();
    this->SILO_LIFE = node["silo"]["life"].as<int16_t>();
    this->SILO_CAPACITY = node["silo"]["capacity"].as<int32_t>();
    this->SILO_CTIME = node["silo"]["ctime"].as<int16_t>();

    this->BARRACK_ENERGY = node["barrack"]["energy"].as<int32_t>();
    this->BARRACK_PRICE = node["barrack"]["price"].as<int32_t>();
    this->BARRACK_LIFE = node["barrack"]["life"].as<int16_t>();
    this->BARRACK_CTIME = node["barrack"]["ctime"].as<int16_t>();

    this->PALACE_ENERGY = node["palace"]["energy"].as<int32_t>();
    this->PALACE_PRICE = node["palace"]["price"].as<int32_t>();
    this->PALACE_LIFE = node["palace"]["life"].as<int16_t>();
    this->PALACE_CTIME = node["palace"]["ctime"].as<int16_t>();


    // WEAPONS
    this->ASSAULT_RIFLE_COOLDOWN    = node["assault_rifle"]["cooldown"].as<int16_t>();
    this->ASSAULT_RIFLE_DAMAGE      = node["assault_rifle"]["damage"].as<uint16_t>();
    this->ASSAULT_RIFLE_BONUS       = node["assault_rifle"]["bonus"].as<uint16_t>();

    this->CANNON_COOLDOWN           = node["cannon"]["cooldown"].as<uint16_t>();
    this->CANNON_DAMAGE             = node["cannon"]["damage"].as<uint16_t>();

    this->ROCKET_LAUNCHER_COOLDOWN  = node["rocket_launcher"]["cooldown"].as<uint16_t>();
    this->ROCKET_LAUNCHER_DAMAGE    = node["rocket_launcher"]["damage"].as<uint16_t>();

    this->SOUND_WAVES_COOLDOWN      = node["sound_waves"]["cooldown"].as<uint16_t>();
    this->SOUND_WAVES_DAMAGE        = node["sound_waves"]["damage"].as<uint16_t>();
    this->SOUND_WAVES_BONUS         = node["sound_waves"]["bonus"].as<uint16_t>();

    this->TTCANNON_COOLDOWN         = node["ttcannon"]["cooldown"].as<uint16_t>();
    this->TTCANNON_DAMAGE           = node["ttcannon"]["damage"].as<uint16_t>();
    this->TTCANNON_BONUS            = node["ttcannon"]["bonus"].as<uint16_t>();

    this->PLASMA_COOLDOWN           = node["plasma"]["cooldown"].as<uint16_t>();
    this->PLASMA_DAMAGE             = node["plasma"]["damage"].as<uint16_t>();
    this->PLASMA_BONUS              = node["plasma"]["bonus"].as<uint16_t>();

    // INFANTRY
    
    this->LIGHT_INFANTRY_RANGE      = node["light_infantry"]["range"].as<uint16_t>();
    this->LIGHT_INFANTRY_SPEED      = node["light_infantry"]["speed"].as<uint16_t>();
    this->LIGHT_INFANTRY_CTIME      = node["light_infantry"]["ctime"].as<uint16_t>();
    this->LIGHT_INFANTRY_PRICE      = node["light_infantry"]["price"].as<uint16_t>();
    this->LIGHT_INFANTRY_LIFE       = node["light_infantry"]["life"].as<uint16_t>();

    this->HEAVY_INFANTRY_RANGE      = node["heavy_infantry"]["range"].as<uint16_t>();
    this->HEAVY_INFANTRY_SPEED      = node["heavy_infantry"]["speed"].as<uint16_t>();
    this->HEAVY_INFANTRY_CTIME      = node["heavy_infantry"]["ctime"].as<uint16_t>();
    this->HEAVY_INFANTRY_PRICE      = node["heavy_infantry"]["price"].as<uint16_t>();
    this->HEAVY_INFANTRY_LIFE       = node["heavy_infantry"]["life"].as<uint16_t>();

    this->FREMEN_RANGE              = node["fremen"]["range"].as<uint16_t>();
    this->FREMEN_SPEED              = node["fremen"]["speed"].as<uint16_t>();
    this->FREMEN_CTIME              = node["fremen"]["ctime"].as<uint16_t>();
    this->FREMEN_PRICE              = node["fremen"]["price"].as<uint16_t>();
    this->FREMEN_LIFE               = node["fremen"]["life"].as<uint16_t>();

    this->SARDAUKAR_RANGE           = node["sardaukar"]["range"].as<uint16_t>();
    this->SARDAUKAR_SPEED           = node["sardaukar"]["speed"].as<uint16_t>();
    this->SARDAUKAR_CTIME           = node["sardaukar"]["ctime"].as<uint16_t>();
    this->SARDAUKAR_PRICE           = node["sardaukar"]["price"].as<uint16_t>();
    this->SARDAUKAR_LIFE            = node["sardaukar"]["life"].as<uint16_t>();

    // VEHICLES
    this->TRIKE_RANGE               = node["trike"]["range"].as<uint16_t>();
    this->TRIKE_SPEED               = node["trike"]["speed"].as<uint16_t>();
    this->TRIKE_CTIME               = node["trike"]["ctime"].as<uint16_t>();
    this->TRIKE_PRICE               = node["trike"]["price"].as<uint16_t>();
    this->TRIKE_LIFE                = node["trike"]["life"].as<uint16_t>();

    this->RAIDER_RANGE              = node["raider"]["range"].as<uint16_t>();
    this->RAIDER_SPEED              = node["raider"]["speed"].as<uint16_t>();
    this->RAIDER_CTIME              = node["raider"]["ctime"].as<uint16_t>();
    this->RAIDER_PRICE              = node["raider"]["price"].as<uint16_t>();
    this->RAIDER_LIFE               = node["raider"]["life"].as<uint16_t>();

    this->SONIC_TANK_RANGE          = node["sonic_tank"]["range"].as<uint16_t>();
    this->SONIC_TANK_SPEED          = node["sonic_tank"]["speed"].as<uint16_t>();
    this->SONIC_TANK_CTIME          = node["sonic_tank"]["ctime"].as<uint16_t>();
    this->SONIC_TANK_PRICE          = node["sonic_tank"]["price"].as<uint16_t>();
    this->SONIC_TANK_LIFE           = node["sonic_tank"]["life"].as<uint16_t>();

    this->TANK_RANGE                = node["tank"]["range"].as<uint16_t>();
    this->TANK_SPEED                = node["tank"]["speed"].as<uint16_t>();
    this->TANK_CTIME                = node["tank"]["ctime"].as<uint16_t>();
    this->TANK_PRICE                = node["tank"]["price"].as<uint16_t>();
    this->TANK_LIFE                 = node["tank"]["life"].as<uint16_t>();

    this->DEVIATOR_RANGE            = node["deviator"]["range"].as<uint16_t>();
    this->DEVIATOR_SPEED            = node["deviator"]["speed"].as<uint16_t>();
    this->DEVIATOR_CTIME            = node["deviator"]["ctime"].as<uint16_t>();
    this->DEVIATOR_PRICE            = node["deviator"]["price"].as<uint16_t>();
    this->DEVIATOR_LIFE             = node["deviator"]["life"].as<uint16_t>();

    this->DEVASTATOR_RANGE          = node["devastator"]["range"].as<uint16_t>();
    this->DEVASTATOR_SPEED          = node["devastator"]["speed"].as<uint16_t>();
    this->DEVASTATOR_CTIME          = node["devastator"]["ctime"].as<uint16_t>();
    this->DEVASTATOR_PRICE          = node["devastator"]["price"].as<uint16_t>();
    this->DEVASTATOR_LIFE           = node["devastator"]["life"].as<uint16_t>();
    this->DEVASTATOR_EXPLOSION      = node["devastator"]["explosion"].as<uint16_t>();

    this->HARVESTER_RANGE           = node["harvester"]["range"].as<uint16_t>();
    this->HARVESTER_SPEED           = node["harvester"]["speed"].as<uint16_t>();
    this->HARVESTER_CTIME           = node["harvester"]["ctime"].as<uint16_t>();
    this->HARVESTER_PRICE           = node["harvester"]["price"].as<uint16_t>();
    this->HARVESTER_LIFE            = node["harvester"]["life"].as<uint16_t>();
    this->HARVESTER_HARVEST_LIMIT   = node["harvester"]["harvestlimit"].as<uint32_t>();
    this->HARVESTER_HARVESTTIME     = node["harvester"]["harvesttime"].as<uint16_t>();
    this->HARVESTER_RECHARGETIME    = node["harvester"]["rechargetime"].as<uint16_t>();
}


Config::~Config() {}
