#ifndef BOOT_SCREEN_H
#define BOOT_SCREEN_H
#include <condition_variable>
#include <cstdint>
#include <vector>

#include "lvgl_renderer.h"
// #include "../../external/lvgl/src/misc/lv_event.h"
// #include "../../external/lv_lib_100ask/src/lv_100ask_nes/lv_100ask_nes.h"
// #include "../../external/lv_lib_100ask/examples/lv_100ask_nes/lv_100ask_example_nes.h"

enum launch_state {
    IN_FLIGHT,
    RM_STOCK_OS,
    BIFROST,
};

class boot_screen : public std::enable_shared_from_this<boot_screen> {
public:

    launch_state state = IN_FLIGHT;

    void start();

    explicit boot_screen(const std::shared_ptr<lvgl_renderer>& shared)
        : lvgl_renderer_inst(shared)
    {
    }

    ~boot_screen();

private:
    static std::weak_ptr<boot_screen> instance;

    std::vector<uint8_t> lottie_buf;
    std::vector<uint8_t> welcome_json;
    std::shared_ptr<lvgl_renderer> lvgl_renderer_inst;
    std::vector<lv_obj_t*> deletion_queue;

    std::condition_variable cv;
    std::mutex cv_m;

    void setup_animation();

    lv_obj_t* create_boot_option(const char* title);

    void setup_boot_selection();
};

#endif // BOOT_SCREEN_H
