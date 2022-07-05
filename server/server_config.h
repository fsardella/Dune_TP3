#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include <stdint.h>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/node.h>
#include <string>

class Config {
 public:
    std::string PORT;
    std::string MAP_PATHS;
    std::string MAP_NAMES_PATH;
    int CLOCK_DELTA;

    uint32_t INITIAL_MONEY;
    
    uint32_t WORM_DELAY;

    // BUILDINGS
    uint16_t BASE_LIFE;

    int32_t AIR_TRAP_ENERGY;
    uint32_t AIR_TRAP_PRICE;
    uint16_t AIR_TRAP_LIFE;
    uint16_t AIR_TRAP_CTIME;
    
    int32_t LIGHT_FACTORY_ENERGY;
    uint32_t LIGHT_FACTORY_PRICE;
    uint16_t LIGHT_FACTORY_LIFE;
    uint16_t LIGHT_FACTORY_CTIME;
    
    int32_t HEAVY_FACTORY_ENERGY;
    uint32_t HEAVY_FACTORY_PRICE;
    uint16_t HEAVY_FACTORY_LIFE;
    uint16_t HEAVY_FACTORY_CTIME;
    
    int32_t REFINERY_ENERGY;
    uint32_t REFINERY_PRICE;
    uint16_t REFINERY_LIFE;
    uint32_t REFINERY_CAPACITY;
    uint16_t REFINERY_CTIME;
    
    int32_t SILO_ENERGY;
    uint32_t SILO_PRICE;
    uint16_t SILO_LIFE;
    uint32_t SILO_CAPACITY;
    uint16_t SILO_CTIME;

    int32_t BARRACK_ENERGY;
    uint32_t BARRACK_PRICE;
    uint16_t BARRACK_LIFE;
    uint16_t BARRACK_CTIME;

    int32_t PALACE_ENERGY;
    uint32_t PALACE_PRICE;
    uint16_t PALACE_LIFE;
    uint16_t PALACE_CTIME;

    // WEAPONS
    uint16_t ASSAULT_RIFLE_COOLDOWN;
    uint16_t ASSAULT_RIFLE_DAMAGE;
    uint16_t ASSAULT_RIFLE_BONUS;
    
    uint16_t CANNON_COOLDOWN;
    uint16_t CANNON_DAMAGE;
    
    uint16_t ROCKET_LAUNCHER_COOLDOWN;
    uint16_t ROCKET_LAUNCHER_DAMAGE;
    
    uint16_t SOUND_WAVES_COOLDOWN;
    uint16_t SOUND_WAVES_DAMAGE;
    uint16_t SOUND_WAVES_BONUS;

    uint16_t TTCANNON_COOLDOWN;
    uint16_t TTCANNON_DAMAGE;
    uint16_t TTCANNON_BONUS;

    uint16_t PLASMA_COOLDOWN;
    uint16_t PLASMA_DAMAGE;
    uint16_t PLASMA_BONUS;    

    // INFANTRY
    uint16_t LIGHT_INFANTRY_RANGE;
    uint16_t LIGHT_INFANTRY_SPEED;
    uint16_t LIGHT_INFANTRY_CTIME;
    uint16_t LIGHT_INFANTRY_PRICE;
    uint16_t LIGHT_INFANTRY_LIFE;
    
    uint16_t HEAVY_INFANTRY_RANGE;
    uint16_t HEAVY_INFANTRY_SPEED;
    uint16_t HEAVY_INFANTRY_CTIME;
    uint16_t HEAVY_INFANTRY_PRICE;
    uint16_t HEAVY_INFANTRY_LIFE;

    uint16_t FREMEN_RANGE;
    uint16_t FREMEN_SPEED;
    uint16_t FREMEN_CTIME;
    uint16_t FREMEN_PRICE;
    uint16_t FREMEN_LIFE;
    
    uint16_t SARDAUKAR_RANGE;
    uint16_t SARDAUKAR_SPEED;
    uint16_t SARDAUKAR_CTIME;
    uint16_t SARDAUKAR_PRICE;
    uint16_t SARDAUKAR_LIFE;

    // VEHICLES
    uint16_t TRIKE_RANGE;
    uint16_t TRIKE_SPEED;
    uint16_t TRIKE_CTIME;
    uint16_t TRIKE_PRICE;
    uint16_t TRIKE_LIFE;

    uint16_t RAIDER_RANGE;
    uint16_t RAIDER_SPEED;
    uint16_t RAIDER_CTIME;
    uint16_t RAIDER_PRICE;
    uint16_t RAIDER_LIFE;

    uint16_t SONIC_TANK_RANGE;
    uint16_t SONIC_TANK_SPEED;
    uint16_t SONIC_TANK_CTIME;
    uint16_t SONIC_TANK_PRICE;
    uint16_t SONIC_TANK_LIFE;

    uint16_t TANK_RANGE;
    uint16_t TANK_SPEED;
    uint16_t TANK_CTIME;
    uint16_t TANK_PRICE;
    uint16_t TANK_LIFE;

    uint16_t DEVIATOR_RANGE;
    uint16_t DEVIATOR_SPEED;
    uint16_t DEVIATOR_CTIME;
    uint16_t DEVIATOR_PRICE;
    uint16_t DEVIATOR_LIFE;

    uint16_t DEVASTATOR_RANGE;
    uint16_t DEVASTATOR_SPEED;
    uint16_t DEVASTATOR_CTIME;
    uint16_t DEVASTATOR_PRICE;
    uint16_t DEVASTATOR_LIFE;
    uint16_t DEVASTATOR_EXPLOSION;

    uint16_t HARVESTER_RANGE;
    uint16_t HARVESTER_SPEED;
    uint16_t HARVESTER_CTIME;
    uint16_t HARVESTER_PRICE;
    uint16_t HARVESTER_LIFE;
    uint32_t HARVESTER_HARVEST_LIMIT;
    uint16_t HARVESTER_HARVESTTIME;
    uint16_t HARVESTER_RECHARGETIME;
    
    explicit Config(std::string YAMLpath);
    Config() {} // NOT INTENDED TO USE
    ~Config();
};     
        
#endif
