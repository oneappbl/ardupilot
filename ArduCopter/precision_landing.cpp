//
// functions to support precision landing
//

#include "Copter.h"

#if PRECISION_LANDING == ENABLED

void Copter::init_precland()
{
    //std::cout << "[DEBUG] : init precland"<< std::endl;
    copter.precland.init();
}

void Copter::update_precland()
{
    int32_t height_above_ground_cm = current_loc.alt;
    //std::cout << "[DEBUG] : height_above_ground_cm before if-else : "<< height_above_ground_cm << std::endl;

    //std::cout << "[DEBUG] : rangefinder_alt_ok : " << rangefinder_alt_ok() << std::endl;
    //std::cout << "[DEBUG] : terrain_use : " << terrain_use() << std::endl;

    // use range finder altitude if it is valid, else try to get terrain alt
    if (rangefinder_alt_ok()) {
        height_above_ground_cm = rangefinder_state.alt_cm;
        //std::cout << "[DEBUG] : using rangefinder height_above_ground_cm "<< std::endl;
    } else if (terrain_use()) {
        if (!current_loc.get_alt_cm(Location_Class::ALT_FRAME_ABOVE_TERRAIN, height_above_ground_cm)) {
            height_above_ground_cm = current_loc.alt;
            //std::cout << "[DEBUG] : using terrain height_above_ground_cm "<< std::endl;
        }
    }

    //std::cout << "[DEBUG] : height_above_ground_cm after if-else : "<< height_above_ground_cm << std::endl;
    copter.precland.update(height_above_ground_cm, rangefinder_alt_ok());
}
#endif
