#include "boot_screen.h"

#include <spdlog/spdlog.h>
#include <thread>

// #include "../../external/lvgl/src/misc/lv_event.h"
// #include "../../external/lv_lib_100ask/src/lv_100ask_nes/lv_100ask_nes.h"
// #include "../../external/lv_lib_100ask/examples/lv_100ask_nes/lv_100ask_example_nes.h"
#include "../constants.h"
#include <src/core/lv_obj_pos.h>
#include <src/display/lv_display.h>
#include <src/misc/lv_anim.h>
#include <src/widgets/lottie/lv_lottie.h>


#include "happ_instance.h"



void boot_screen::start()
{
    spdlog::debug("Presenting launch options");
    lvgl_renderer_inst->set_global_refresh_hint(COLOR_FAST);

    {
        // Hello
        // setup_animation();
    }

    {
        start_hack_app();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    lvgl_renderer_inst->set_global_refresh_hint(MONOCHROME);
    setup_boot_selection();

    // wait for the user to select an option
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait(lk, [this] { return state != IN_FLIGHT; });
    lk.unlock();

    lvgl_renderer_inst->refresh({ 0, 0 }, { SCREEN_WIDTH, SCREEN_HEIGHT }, FULL);
}

boot_screen::~boot_screen()
{
    for (auto obj : deletion_queue) {
        lv_obj_delete(obj);
    }
}

void boot_screen::setup_animation()
{
    welcome_json = get_resource_file("animations/hello.json");

    auto lottie_obj = lv_lottie_create(lv_screen_active());
    lv_lottie_set_src_data(lottie_obj, welcome_json.data(), welcome_json.size());
    lv_anim_set_repeat_count(lv_lottie_get_anim(lottie_obj), 1);

    int width = static_cast<int>(std::round(SCREEN_WIDTH / 1.5));
    int height = width / 3;
    lottie_buf.resize(width * height * 4);
    lv_lottie_set_buffer(lottie_obj, width, height, lottie_buf.data());

    lv_obj_align(lottie_obj, LV_ALIGN_CENTER, 0, 0);

    deletion_queue.push_back(lottie_obj);
}

lv_obj_t* boot_screen::create_boot_option(const char* title)
{
    auto btn = lv_obj_create(lv_screen_active());
    lv_obj_set_size(btn, LV_PCT(40), LV_SIZE_CONTENT);
    lv_obj_set_style_border_color(btn, lv_color_black(), 0);
    lv_obj_set_style_border_width(btn, 5, 0);
    lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
    lv_obj_set_style_radius(btn, 0, 0);
    lv_obj_set_flex_flow(btn, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_pad_all(btn, 40, 0);
    lv_obj_set_flex_align(btn, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // Create the title label
    auto title_label = lv_label_create(btn);
    lv_label_set_text(title_label, title);
    lv_obj_set_style_text_font(title_label, &ebgaramond_48, 0);
    lv_obj_set_size(title_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    // offset the title label
    lv_obj_set_style_margin_top(title_label, 10, 0);

    // Create the subtitle label
    auto subtitle_label = lv_label_create(btn);
    lv_label_set_text(subtitle_label, LV_SYMBOL_RIGHT);
    lv_obj_set_size(subtitle_label, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    // Add the box to the deletion queue
    deletion_queue.push_back(title_label);
    deletion_queue.push_back(subtitle_label);
    deletion_queue.push_back(btn);

    return btn;
}

void boot_screen::setup_boot_selection()
{
    auto remarkable = create_boot_option("reMarkable OS");
    lv_obj_align(remarkable, LV_ALIGN_BOTTOM_MID, 0, -425);

    lv_obj_add_event_cb(remarkable, [](lv_event_t* event) {
        spdlog::debug("Launching reMarkable OS");
        if (auto instance = boot_screen::instance.lock()) {
            instance->state = RM_STOCK_OS;
            instance->cv.notify_one();
        } }, LV_EVENT_CLICKED, nullptr);

    auto bifrost = create_boot_option("Bifrost");
    lv_obj_align(bifrost, LV_ALIGN_BOTTOM_MID, 0, -200);

    instance = shared_from_this();

    lv_obj_add_event_cb(bifrost, [](lv_event_t* event) {
        spdlog::debug("Launching Bifrost");
        if (auto instance = boot_screen::instance.lock()) {
            instance->state = BIFROST;
            instance->cv.notify_one();
        } }, LV_EVENT_CLICKED, nullptr);
}

std::weak_ptr<boot_screen> boot_screen::instance;
