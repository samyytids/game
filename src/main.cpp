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
#include "scene1.h"
#include "custombg.h"

// Collision is 1 tile lower than it should be

int main(){
    bn::core::init();
    bn::camera_ptr camera = bn::camera_ptr::create(0,0);
    bn::unique_ptr<gm::StateMachine> state(new gm::StateMachine());
    bn::unique_ptr<gm::CustomBg> test_bg(new gm::CustomBg(bn::affine_bg_items::test_bg.create_bg(0,0), camera));
    gm::Hitbox hitbox = gm::Hitbox(bn::fixed_point(0,0), 8, 8);
    bn::unique_ptr<gm::Player> player(new gm::Player(state.get(), bn::sprite_items::gooch.create_sprite(0,0), bn::sprite_items::gooch.tiles_item(), camera, &hitbox, test_bg.get()));
    
    state->SetScene(gm::SceneType::TEST);

    bn::unique_ptr<gm::Scene> scene;

    while(true){
        switch (state->GetScene())
        {
        case gm::SceneType::TEST:
            scene.reset(new gm::Scene1(player.get(), test_bg.get(), camera));
            scene->execute();
            break;
        
        default:
            break;
        }
        bn::core::update();
    }
}
