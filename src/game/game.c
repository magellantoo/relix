#include "game.h"
#include "../input/input.h"
#include "../utility/clock.h"
#include "../utility/utility.h"
#include "../term/term.h"
#include "../term/screen.h"
#include "../log/log.h"
#include "../constants.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int initGame() {
    initLog();
    initScreen();
    initInput();

    signal(SIGINT, closeGame);
}

void closeGame(int a) {
    closeInput();
    closeScreen();
    closeLog();

    exit(0);
}

int loop() {
    // Create variables required for timing outside of loop scope
    struct Clock game_clock;
    initClock(&game_clock);

    unsigned long adjust_time = 0;
    unsigned int frame_count = 0;
    int loop_time = 0;
    int loop_time_saved = 0;

    while (1) {
        fflush(stdout);
        // !this->game_over) {
        // Reset clock
        delta(&game_clock);
        // Increment step count
        // this->step_count++;
        frame_count++;

        // Send EVENT_STEP to all objects
        // df::EventStep p_step_event = df::EventStep(this->step_count);
        // onEvent(&p_step_event);

        // Retrieve input
        // df::InputManager &input_manager = df::InputManager::getInstance();
        // input_manager.getInput();

        // df::WorldManager &world_manager = df::WorldManager::getInstance();
        // Call worldManager update
        // world_manager.update();

        // Send EVENT_BEFOREDRAW to all objects
        // df::EventBeforeDraw p_bd_event = df::EventBeforeDraw();
        // onEvent(&p_bd_event);

        // Call worldManager draw
        // world_manager.draw();
        //
        int i, j;


        for (i = 0; i < screen.ts.lines; i++) {
            int sat = (int)(((float)i / (float)screen.ts.lines) * 192.0) + 63;
            for (j = 0; j < screen.ts.cols; j++) {
                putPixelRgb(j, i, hslToRgb((Color){(i * 3 + j + frame_count / 5) % 256, sat, 255}));
                // putPixelRgb(j, i, (Color){i * 40, j * 40, 255});
                // putPixelHSL(i, j, (Color){255, 255, 255});
                // putPixelRgb(j, i, (Color){0, 0, 0});
                // putPixel(j, i, i * 16 + j);
            }
        }


        swapScreen();

        if (frame_count % 30 == 0) {
            loop_time_saved = loop_time;
        }
        printf("\e[1G\e[%dC", screen.margin_x);
        printf(" Loop time: %5d ", loop_time_saved);
        printf("Frame_count: %3d ", frame_count);
        printf("Times_init: %3d ", screen.times_init);
        printf("Lines: %3d ", screen.ts.lines);
        printf("Columns: %3d ", screen.ts.cols);
        fflush(stdout);

        // Swap graphics buffers
        // df::GraphicsManager &graphics_manager =
        //     df::GraphicsManager::getInstance();
        // graphics_manager.swapBuffers();

        // Adjust sleep time for additional framerate accuracy
        loop_time = split(&game_clock);
        unsigned long sleep_time = (FRAME_TIME - loop_time - adjust_time);
        // Reset clock before sleeping to calculate actual sleep time
        delta(&game_clock);
        // Multiply microseconds to obtain sleep time in nanoseconds
        if (sleep_time > 0) {
            uSleep(sleep_time);
            // Calculate adjust from difference between expected and actual sleep times
            adjust_time = split(&game_clock) - sleep_time;
        }
    }

    return 0;
}
