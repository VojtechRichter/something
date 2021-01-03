#include "./something_game.hpp"
#include "./something_weapon.hpp"

void Weapon::render(SDL_Renderer *renderer, Game *game, Index<Entity> entity)
{
    switch (type) {
    case Weapon_Type::Stomp:
    case Weapon_Type::Gun: {} break;
    case Weapon_Type::Placer: {
        bool can_place = false;
        auto target_tile = game->where_entity_can_place_block(entity, &can_place);
        can_place = can_place && placer.amount > 0;
        tile_defs[placer.tile].top_texture.render(
            renderer,
            rect(game->camera.to_screen(
                     vec2((float) target_tile.x,
                          (float) target_tile.y) * TILE_SIZE),
                 TILE_SIZE, TILE_SIZE),
            SDL_FLIP_NONE,
            can_place ? CAN_PLACE_BLOCK_COLOR : CANNOT_PLACE_BLOCK_COLOR);
    } break;
    }
}

void Weapon::shoot(Game *game, Index<Entity> shooter)
{
    switch (type) {
    case Weapon_Type::Gun: {
        Projectile projectile = gun.projectile;
        projectile.pos = game->entities[shooter.unwrap].pos;
        projectile.vel = normalize(game->entities[shooter.unwrap].gun_dir) * PROJECTILE_SPEED;
        projectile.shooter = shooter;
        game->spawn_projectile(projectile);
    } break;

    case Weapon_Type::Placer: {
        bool can_place = false;
        auto target_tile = game->where_entity_can_place_block(shooter, &can_place);
        if (can_place && placer.amount > 0) {
            game->grid.set_tile(target_tile, placer.tile);
            placer.amount -= 1;
        }
    } break;

    case Weapon_Type::Stomp: {
        game->entities[shooter.unwrap].stomp(&game->grid);
    } break;
    }
}

Sprite Weapon::icon() const
{
    switch (type) {
    case Weapon_Type::Gun: {
        auto frames = assets.get_by_index(gun.projectile.active_animat.frames_index);
        assert(frames.count > 0);
        return frames.sprites[0];
    }

    case Weapon_Type::Placer:
        return tile_defs[placer.tile].top_texture;

    case Weapon_Type::Stomp:
        assert(DIRT_GOLEM_ANIMAT.count > 0);
        return DIRT_GOLEM_ANIMAT.sprites[0];
    }

    assert(0 && "Unreachable");

    return {};
}

Weapon water_gun()
{
    Weapon result = {};
    result.shoot_sample = {true, SPLASH_SOUND_INDEX};
    result.type = Weapon_Type::Gun;
    result.gun.projectile = water_projectile(vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), {0});
    return result;
}

Weapon fire_gun()
{
    Weapon result = {};
    result.shoot_sample = {true, FIREBALL_SOUND_INDEX};
    result.type = Weapon_Type::Gun;
    result.gun.projectile = fire_projectile(vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), {0});
    return result;
}

Weapon rock_gun()
{
    // TODO(#306): no sound for the rock gun
    Weapon result = {};
    result.type = Weapon_Type::Gun;
    result.gun.projectile = rock_projectile(vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), {0});
    return result;
}

Weapon ice_gun()
{
    // TODO(#307): no sound for the ice gun
    Weapon result = {};
    result.type = Weapon_Type::Gun;
    result.gun.projectile = ice_projectile(vec2(0.0f, 0.0f), vec2(0.0f, 0.0f), {0});
    return result;
}

Weapon dirt_block_placer(int amount)
{
    // TODO(#308): no sound for the dirt block placer
    Weapon result = {};
    result.type = Weapon_Type::Placer;
    result.placer.tile = TILE_DIRT_0;
    result.placer.amount = amount;
    return result;
}

Weapon ice_block_placer(int amount)
{
    // TODO(#309): no sound for the ice block placer
    Weapon result = {};
    result.type = Weapon_Type::Placer;
    result.placer.tile = TILE_ICE_0;
    result.placer.amount = amount;
    return result;
}

Weapon stomp_move()
{
    Weapon result = {};
    result.type = Weapon_Type::Stomp;
    return result;
}
