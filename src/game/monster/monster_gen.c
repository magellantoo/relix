#include "monster.h"

// Libarary
#include <stdlib.h>
#include <string.h>

// Engine
#include "object/objectManager.h"

// Game
#include "../character/character.h"
#include "../relix.h"

#include "log/log.h"

int updateMonsterDefault(Object *o) {
    CharacterData *data = o->data;
    if (data->health <= 0) {
        // Send death message
        Event action;
        action.id = EVENT_MESSAGE;
        action.data = malloc(sizeof(String **));
        *((String **) action.data) = createString();
        sputf(*((String **) action.data), "%s has died!", data->name->s);
        sendEvent(action);

        // Clear char info panel
        Event clear_panel;
        clear_panel.id = EVENT_CHAR_INFO;
        clear_panel.data = malloc(sizeof(CharacterData **));
        *((CharacterData **) clear_panel.data) = NULL;
        sendEvent(clear_panel);

        removeObject(o);
    }
    return 0;
}

void closeMonster(Object *o) {
    CharacterData *data = o->data;

    closeCharData(data);

    closeDefault(o);
}

Object *createMonster(MonsterEntry *entry) {
    Object *monster = createObject();

    // Set object data
    sputf(monster->type, TYPE_MONSTER);
    monster->solid = OBJ_SOLID;
    monster->update = &updateMonsterDefault;
    monster->close = &closeMonster;

    CharacterData *data = createCharData();

    monster->data = data;

    // Generate character data from entry
    stringCopy(data->name, entry->name);
    data->entry = entry;
    data->level = entry->level;
    int i;
    data->health = maxDice(entry->hit_dice);

    for (i = 1; i < entry->level; i++) {
        data->health += rollDice(entry->hit_dice);
    }
    data->max_health = data->health;

    // Generate sprite data from entry
    strncpy(monster->pix.chr, entry->chr->s, UNICODE_MAX);
    monster->pix.fg = entry->color;
    monster->pix.depth = MONSTER_DEPTH;

    /*
typedef struct MosnterEntry {
    // natural_weapon
    struct Dice nat_weapon;
    // natural_damage
    int nat_damage;
    // loot_quality
    int loot_qual;
} MonsterEntry;
*/
    return monster;
}
