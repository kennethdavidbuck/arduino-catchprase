//
#define TIMER_DEBOUNCE        50
#define TIMER_TICK            0
#define TIMER_TOCK            1
#define POINTS_WIN            7
#define TIMER_NEW_ROUND       -1

// interrupt pins
#define PIN_CATEGORY          0
#define PIN_STOP_START        1
#define PIN_TEAM_ONE          2
#define PIN_TEAM_TWO          3
#define PIN_NEXT              7
#define PINS_LENGTH           4

const int PINS[PINS_LENGTH] = {
  PIN_TEAM_ONE,
  PIN_TEAM_TWO,
  PIN_CATEGORY,
  PIN_NEXT
};

// sound pins
#define PIN_SPEAKER           5

// game sound notes
#define NOTE_TEAM_ONE         NOTE_C4
#define NOTE_TEAM_TWO         NOTE_CS4
#define NOTE_CLOCK_TICK       NOTE_C4
#define NOTE_CLOCK_TOCK       NOTE_CS4

// sound durations
#define INCREMENT_DURATION    16

// game messages
#define MESSAGE_EMPTY          "                "
#define MESSAGE_TEAM_ONE_WIN   " TEAM ONE WINS! "
#define MESSAGE_TEAM_TWO_WIN   " TEAM TWO WINS! "
#define MESSAGE_SUCCESS        "    SUCCESS!    "

// game states
#define STATE_OVER            0
#define STATE_STOPPED         1
#define STATE_STARTED         2

// game events
#define EVENT_TEAM_ONE_SCORE  0
#define EVENT_TEAM_TWO_SCORE  1
#define EVENT_CATEGORY        2
#define EVENT_STOP_START      3
#define EVENT_NEXT            4
#define EVENTS_LENGTH         5
