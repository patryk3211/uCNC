#include "../cnc.h"

#if defined(ENABLE_WIRE_RPM)

#include "wire_rpm.h"

#define WIRE_RPM_SAMPLE_COUNT 50

// One sample = 10ms
static uint8_t samples[WIRE_RPM_SAMPLE_COUNT];
static uint16_t sampleSum = 0;
static uint8_t writeHead = 0;

static void receive_sample(uint8_t value) {
  sampleSum -= samples[writeHead];
  samples[writeHead] = value;
  sampleSum += value;
  writeHead = (writeHead + 1) % WIRE_RPM_SAMPLE_COUNT;
}

#if defined(ENABLE_IO_MODULES)
#define RECEIVER_IDLE 0
#define RECEIVER_BEGIN_LOW 1
#define RECEIVER_AWAIT_DATA 2
#define RECEIVER_DATA_RETURN 3
#define RECEIVER_AWAIT_PARITY 4
#define RECEIVER_PARITY_RETURN 5
#define RECEIVER_NO_ACTION 255

#define DATA_RECEIVED 1
#define DATA_PARITY_ERROR 2
#define DATA_RECEIVER_ERROR 4

#define BIT_LENGTH 14
#define ON_TIME_ONE 35
#define TIME_OUT_TIME 80

#define WIRE_BIT_MASK (1 << (DIN_PINS_OFFSET - RPM_WIRE_DIN))

static uint32_t t0 = 0;
static uint32_t debounce = 0;

static uint16_t receivedData = 0;
static uint8_t calculatedParity = 0;
static uint8_t receivedParity = 0;
static uint8_t status = 0;
static uint8_t recvState = 0;
static uint8_t bitsLeft = 0;

static bool pin_changed(void* args) {
  // Take the time measurement as soon as possible
  uint32_t time = mcu_micros();

  uint8_t* icargs = (uint8_t*)args;
  uint8_t diff = icargs[1];

  if(!(diff & WIRE_BIT_MASK))
    // Not our pin
    return EVENT_CONTINUE;

  if(time - debounce < 15) {
    // Debounce the signal
    return EVENT_HANDLED;
  }
  debounce = time;

  uint8_t state = icargs[0] & WIRE_BIT_MASK;

  // Not setting this variable means returns the receiver
  // to a known state preventing any dead-locking.
  uint8_t nextState = RECEIVER_NO_ACTION;
  switch(recvState) {
    case RECEIVER_IDLE:
      if(!state) {
        // Low means potential start
        t0 = time;
        nextState = RECEIVER_BEGIN_LOW;
      } else {
        // Continue being idle
        nextState = RECEIVER_IDLE;
      }
      break;
    case RECEIVER_BEGIN_LOW:
      if(state) {
        // Returned to high
        uint32_t timeDiff = time - t0;
        if(timeDiff > 50 && timeDiff < 80) {
          // Low pulse in range for a start condition
          bitsLeft = BIT_LENGTH;
          receivedData = 0;
          calculatedParity = 0;
          nextState = RECEIVER_AWAIT_DATA;
        } else {
          // Not in the correct time range
          nextState = RECEIVER_IDLE;
        }
      }
      break;
    case RECEIVER_AWAIT_DATA:
      if(!state) {
        // Low pulse, save time stamp
        t0 = time;
        nextState = RECEIVER_DATA_RETURN;
      }
      break;
    case RECEIVER_DATA_RETURN:
      if(state) {
        // Returned to high
        uint32_t timeDiff = time - t0;
        if(timeDiff > TIME_OUT_TIME)
          break;

        if(timeDiff > ON_TIME_ONE) {
          // Longer low pulse means 1
          receivedData |= (1 << (BIT_LENGTH - bitsLeft));
          calculatedParity = !calculatedParity;
        } else {
          // Shorter low pulse means 0
          // Do nothing, the bit is already zero
        }

        if(bitsLeft-- == 0) {
          // All bits received
          nextState = RECEIVER_AWAIT_PARITY;
        } else {
          // Continue receiving bits
          nextState = RECEIVER_AWAIT_DATA;
        }
      }
      break;
    case RECEIVER_AWAIT_PARITY:
      if(!state) {
        // Low pulse, save time stamp
        t0 = time;
        nextState = RECEIVER_PARITY_RETURN;
      }
      break;
    case RECEIVER_PARITY_RETURN:
      if(state) {
        // Returned to high
        uint32_t timeDiff = time - t0;
        if(timeDiff > TIME_OUT_TIME)
          break;

        if(timeDiff > ON_TIME_ONE) {
          // Longer low pulse means 1
          receivedParity = 1;
        } else {
          // Shorter low pulse means 0
          receivedParity = 0;
        }

        status = DATA_RECEIVED;
        if(calculatedParity != receivedParity) {
          status |= DATA_PARITY_ERROR;
        } else {
          receive_sample(receivedData);
        }
        nextState = RECEIVER_IDLE;
      }
      break;
  }

  if(nextState == RECEIVER_NO_ACTION) {
    status = DATA_RECEIVER_ERROR;
    recvState = RECEIVER_IDLE;
  } else {
    recvState = nextState;
  }
  return EVENT_HANDLED;
}
CREATE_EVENT_LISTENER(input_change, pin_changed);

#endif

DECL_MODULE(wire_rpm) {
  ADD_EVENT_LISTENER(input_change, pin_changed);
}

uint16_t wire_rpm_get_speed() {
  return sampleSum * (1000 / (WIRE_RPM_SAMPLE_COUNT * 10)) * 60;
}

#endif
