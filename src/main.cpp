// Butano
#include "bn_log.h"
#include "bn_core.h"
#include "state.h"
#include "bn_keypad.h"
#include "bn_unique_ptr.h"
#include "player.h"
#include "bn_camera_ptr.h"
#include "bn_unordered_map.h"
#include "npc.h"
// #include "bn_sprite_items_test_npc.h"
// #include "bn_sprite_items_test_npc2.h"
#include "bn_sprite_items_gooch.h"
#include "bn_array.h"
#include "bn_sprite_tiles_item.h"
#include "bn_affine_bg_items_test_bg.h"
#include "custombg.h"

int main(){
    bn::core::init();
    bn::camera_ptr camera = bn::camera_ptr::create(0,0);
    bn::unique_ptr<gm::StateMachine> state(new gm::StateMachine());
    gm::CustomBg test_bg = gm::CustomBg(bn::affine_bg_items::test_bg.create_bg(0,0), camera);
    gm::Hitbox hitbox = gm::Hitbox(bn::fixed_point(0,0), 8, 8);
    bn::unique_ptr<gm::Player> player(new gm::Player(state.get(), bn::sprite_items::gooch.create_sprite(0,0), bn::sprite_items::gooch.tiles_item(), camera, &hitbox, &test_bg));
    bn::array<bn::string_view, 2> voice_lines = {bn::string_view("This is a string"), bn::string_view("This is also a string")};
    gm::NPC test_npc2 = gm::NPC(bn::sprite_items::gooch.create_sprite(16,0), bn::sprite_items::gooch.tiles_item(), camera);
    player->Spawn(bn::fixed_point(-8,0));
    while(true){
        player->CheckMovement();
        bn::core::update();
    }
}
