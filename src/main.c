#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "lo/lo.h"

#include "device.h"
#include "device_monitor.h"
#include "clock.h"
#include "clocks/clock_crow.h"
#include "clocks/clock_internal.h"
#include "clocks/clock_midi.h"
#include "clocks/clock_scheduler.h"
#include "event.h"
#include "input.h"
#include "interface.h"
#include "metro.h"
#include "lua.h"
#include "osc.h"
#include "sdl.h"
#include "socket.h"

#define DEFAULT_OSC_PORT			10011
#define DEFAULT_SOCKET_PORT		11001

int main(int argc, char **argv) {
  printf("isms ////////\n");

  init_event();
  init_input();

  clock_init();
  clock_internal_init();
  clock_midi_init();
  clock_crow_init();
  clock_scheduler_init();

  init_osc(DEFAULT_OSC_PORT);
  init_socket(DEFAULT_SOCKET_PORT);
  init_metro();
  init_lua();
  init_interface();
  init_dev();

  if(argc>1) {
    char cmd[64];
    snprintf(cmd, 64, "isms.run('%s')\n", argv[1]);
    printf(">>>> %s\n",cmd);
    lua_run(cmd);
  }

  printf(">> device scan\n");
  dev_monitor_scan();
  printf(">> starting event loop\n");
  event_loop();

  deinit_dev();
  deinit_osc();
  clock_deinit();
  deinit_metro();
  deinit_lua();
  deinit_sdl();

  printf(">> farewell.\n");
  return 0;
}


