// Arsenal-local helpers that upstream Bruce keeps in core RF files but which
// aren't present on this dev base. Defined here so the arsenal subsystem stays
// self-contained and doesn't have to patch src/modules/rf.
#include "arsenal.h"
#include "modules/rf/rf_utils.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <RCSwitch.h>
#include <globals.h>

void RCSwitch_send(uint64_t data, unsigned int bits, int pulse, int protocol, int repeat) {
    RCSwitch mySwitch = RCSwitch();

    if (bruceConfigPins.rfModule == CC1101_SPI_MODULE) {
        mySwitch.enableTransmit(bruceConfigPins.CC1101_bus.io0);
    } else {
        mySwitch.enableTransmit(bruceConfigPins.rfTx);
    }

    mySwitch.setProtocol(protocol);
    if (pulse) { mySwitch.setPulseLength(pulse); }
    mySwitch.setRepeatTransmit(repeat);
    mySwitch.send(data, bits);
    mySwitch.disableTransmit();

    deinitRfModule();
}
