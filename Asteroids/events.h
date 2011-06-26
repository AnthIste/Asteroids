#ifndef ASTEROIDS_EVENTS_H_
#define ASTEROIDS_EVENTS_H_

enum Event_t {
    // Asteroid events
    EVT_ASTEROID_SPAWN,
    EVT_ASTEROID_DESTROYED,

    // Spaceship events
    EVT_SPACESHIP_SPAWN,
    EVT_SPACESHIP_DESTROYED,
    EVT_SPACESHIP_THRUST,
    EVT_SPACESHIP_UNTHRUST,
    EVT_SPACESHIP_RESET,
    EVT_SPACESHIP_STARTTURN,
    EVT_SPACESHIP_STOPTURN,
    
    // Bullet events
    EVT_FIRE_BULLET,
    EVT_BULLET_SPAWN,
    EVT_BULLET_DESTROYED,

    // Game events
    EVT_GAME_RESTART,

    // Technical events
    EVT_ENTITY_CREATED,
    EVT_ENTITY_DESTROYED
};

#endif  // ASTEROIDS_EVENTS_H_