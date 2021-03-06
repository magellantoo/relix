#include "game/game.h"
#include "object/object.h"
#include "object/objectManager.h"
#include "constants.h"
#include "log/log.h"
#include "input/input.h"
#include "render/render.h"

#include "stdlib.h"
#include "string.h"

void nothing() {
    // pass
}

int testkeyboardListener(struct Object *o, Event *ev) {
    writeLog(10, "Received keyboard event");
    KeyboardEvent k_ev = *(KeyboardEvent *)ev->data;
    switch (k_ev.type) {
        case KEYBOARD_NORMAL:
            switch (k_ev.value) {
                case 'q':
                case 'Q':
                    queueClear(&nothing);
                    break;
            }
            return 0;
        case KEYBOARD_ESCAPE:
            writeLog(10, "Received keyboard escape %d", k_ev.value);
            switch (k_ev.value) {
                case ARROW_UP:
                    o->pos.y--;
                    break;
                case ARROW_DOWN:
                    o->pos.y++;
                    break;
                case ARROW_LEFT:
                    o->pos.x--;
                    break;
                case ARROW_RIGHT:
                    o->pos.x++;
                    break;
            }
            return 0;
    }
    
    return 0;
}

int renderTestObj(Object *o, Screen *s) {
    o->pix.depth = o->pos.z;
    // Position on the screen
    Point rel_pos = (Point){
            o->pos.x - s->camera_bounds.left,
            o->pos.y - s->camera_bounds.top,
            0
    };

    if (putPixelL(s, rel_pos.x, rel_pos.y, o->pix)) {
        return 0;
    }

    return 1;
}


int main() {
    initGame();

    addLogLevel(LOG_INPUT_V);

    struct Object *o_1 = createObject();

    strcpy(o_1->pix.chr, "@");
    o_1->pix.fg = (Color){192, 128, 48, 1.0};
    o_1->render = &renderTestObj;

    listenEvent(o_1, EVENT_KEYBOARD, &testkeyboardListener);

    addObject(o_1);

    loop();

    closeGame(0);
    return 0;
}

