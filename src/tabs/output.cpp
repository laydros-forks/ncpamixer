#include "output.hpp"

#include <string.h>
#include <ncursesw/ncurses.h>
#include <inttypes.h>

#include "../pa.hpp"

Output::Output()
{
}

Output::~Output()
{

}

void Output::handleInput(unsigned int input)
{
}

void Output::draw(int w, int h)
{
    int baseY = 3;

    for (auto &i : pa.PA_SINKS) {
        float perc = static_cast<float>(i.second.volume) /
                      (PA_VOLUME_NORM * 1.5f);

        volumeBar(w, h, 0, baseY, perc, i.second.peak);

        // if (i.first == selected_input_index) {
        //     attron(COLOR_PAIR(1));
        // }

        char label[255];

        if (i.second.mute) {
            snprintf(
                label,
                sizeof(label),
                "%s (muted)",
                i.second.name
            );
        } else {
            snprintf(
                label,
                sizeof(label),
                "%s (%d%%)",
                i.second.name,
                static_cast<int>(perc * 1.5f * 100.f)
            );
        }

        mvaddstr(baseY - 2, 1, label);

        unsigned int len = strlen(i.second.name);
        unsigned int sink_pos = w - 1 - len;

        mvaddstr(
            baseY - 2,
            sink_pos,
            i.second.name
        );

        // if (i.first == selected_input_index) {
        //     attroff(COLOR_PAIR(1));
        // }

        baseY += 5;
    }
}