#include "pa.hpp"
#include "view.hpp"
#include <pulse/pulseaudio.h>
#include <stdio.h>
#include <vector>

Pa pa;
View ui(&pa);

void notify_ui()
{
    ui.notify_draw();
}

// Handle window resize
void on_resize(int signum)
{
    ui.resize_view();
}

void notify_volume_change(uint32_t index, int dir)
{
    pa.set_volume(index, dir);
}

void move_input_sink(uint32_t input_index, uint32_t sink_index)
{
    pa.move_input_sink(input_index, sink_index);
}

int main(void)
{

    signal(SIGWINCH, &on_resize);

    pa.notify_update_cb = &notify_ui;
    ui.setInputVolume = &notify_volume_change;
    ui.moveInputSink = &move_input_sink;
    ui.run();

    return 0;
}