// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that makes waves of light splash out from each keypress
#include "Kaleidoscope-LED-Wavepool.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for unicode input
#include "Kaleidoscope-Unicode.h"

// Support for host OS detection
#include "Kaleidoscope-HostOS.h"

// Third-party plugin: "The Matrix'-like effect
#include "Kaleidoscope-LEDEffect-DigitalRain.h"

#include "LED-CapsLock.h"

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_SWITCH_OS,
       MACRO_OS_INFO,
       MACRO_ANY,
       MACRO_ISSUENUMBER,
       MACRO_A_AE, // aAäÄ
       MACRO_E_EURO, // e€
       MACRO_O_OE, // oOöÖ
       MACRO_U_UE, // uUüÜ
       MACRO_S_SS  // sSß
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { PRIMARY, NUMPAD, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(

  [PRIMARY] = KEYMAP_STACKED
  (M(MACRO_SWITCH_OS), Key_1,         Key_2,         Key_3,           Key_4, Key_5, Key_LEDEffectNext,
   Key_Backtick,       Key_Q,         Key_W,         M(MACRO_E_EURO), Key_R, Key_T, M(MACRO_ISSUENUMBER),
   Key_Escape,         M(MACRO_A_AE), M(MACRO_S_SS), Key_D,           Key_F, Key_G,
   Key_Tab,            Key_Z,         Key_X,         Key_C,           Key_V, Key_B, Key_PageDown,
   Key_LeftControl,    Key_Backspace, Key_LeftShift, Key_LeftGui,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY), Key_6,          Key_7,         Key_8,            Key_9,         Key_0,         LockLayer(NUMPAD),
   Key_Enter,    Key_Y,          M(MACRO_U_UE), Key_I,            M(MACRO_O_OE), Key_P,         Key_Equals,
                 Key_H,          Key_J,         Key_K,            Key_L,         Key_Semicolon, Key_Quote,
   MEH(Key_T),   Key_N,          Key_M,         Key_Comma,        Key_Period,    Key_Slash,     Key_Minus,
   Key_LeftAlt,  Key_RightShift, Key_Spacebar,  Key_RightControl,
   ShiftToLayer(FUNCTION)),

  [NUMPAD] =  KEYMAP_STACKED
  (M(MACRO_OS_INFO), ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         ___,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           Key_CapsLock,
   Key_Tab,  ___,              Key_mouseUp, ___,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  ___,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)
) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

static void switchOsMacro(uint8_t keyState) {
  if (!keyToggledOn(keyState)) { return; }
  kaleidoscope::hostos::Type currentOs = HostOS.os(), nextOs = currentOs;
  switch (currentOs) {
  case kaleidoscope::hostos::LINUX:
    nextOs = kaleidoscope::hostos::WINDOWS;
    break;
  default:
    nextOs = kaleidoscope::hostos::LINUX;
    break;
  }
  HostOS.os(nextOs);
}

static void osInfoMacro(uint8_t keyState) {
  if (!keyToggledOn(keyState)) { return; }
  kaleidoscope::hostos::Type currentOs = HostOS.os();
  switch (currentOs) {
  case kaleidoscope::hostos::LINUX:
    Macros.type(PSTR("linux"));
    break;
  case kaleidoscope::hostos::WINDOWS:
    Macros.type(PSTR("windows"));
    break;
  case kaleidoscope::hostos::OSX:
    Macros.type(PSTR("osx"));
    break;
  case kaleidoscope::hostos::OTHER:
    Macros.type(PSTR("other"));
    break;
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */


static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState)) {
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);
    toggledOn = true;
  }

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey, toggledOn);
}

static void issueNumberMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("DEV_LOND2PLUS-"));
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

class LongPress {

private:
  bool fired = false;
  uint32_t start_time;

public:
  virtual void onToggledOn();
  virtual void onLongPress();

  void onKeyswitchEvent(uint8_t key_state) {
    if (keyToggledOn(key_state)) {
      fired = false;
      start_time = Kaleidoscope.millisAtCycleStart();
      onToggledOn();
    } else if (keyIsPressed(key_state) && keyWasPressed(key_state) &&
               !fired && Kaleidoscope.millisAtCycleStart() > start_time + 200) {
      onLongPress();
      fired = true;
    }
  }

};

static void backspace() {
  Macros.play(MACRO(T(Backspace)));
}

static bool wasShiftKeyActive() {
  return kaleidoscope::hid::wasModifierKeyActive(Key_LeftShift) ||
    kaleidoscope::hid::wasModifierKeyActive(Key_RightShift);
}

static bool isShifted() {
  return wasShiftKeyActive() || getCapsLockState();
}

static void toggleCapsLock() {
  Macros.play(MACRO(T(CapsLock)));
}

static void typeUnicode(uint32_t character) {
  bool capsLock = getCapsLockState();
  if (HostOS.os() == kaleidoscope::hostos::WINDOWS && wasShiftKeyActive()) {
    // Hex-input on Windows only works when shift is NOT pressed
    kaleidoscope::hid::releaseRawKey(Key_LeftShift);
    kaleidoscope::hid::releaseRawKey(Key_RightShift);
    kaleidoscope::hid::sendKeyboardReport();
  }
  if (capsLock) { toggleCapsLock(); }
  Unicode.type(character);
  if (capsLock) { toggleCapsLock(); }
}

class ALongPress final : public LongPress {
  void onToggledOn() { Macros.play(MACRO(T(A))); }
  void onLongPress() { backspace(); typeUnicode(isShifted() ? 0xC4 : 0xE4); }
} aLongPress;

class ELongPress final : public LongPress {
  void onToggledOn() { Macros.play(MACRO(T(E))); }
  void onLongPress() { backspace(); typeUnicode(0x20AC); }
} eLongPress;

class OLongPress final : public LongPress {
  void onToggledOn() { Macros.play(MACRO(T(O))); }
  void onLongPress() { backspace(); typeUnicode(isShifted() ? 0xD6 : 0xF6); }
} oLongPress;

class ULongPress final : public LongPress {
  void onToggledOn() { Macros.play(MACRO(T(U))); }
  void onLongPress() { backspace(); typeUnicode(isShifted() ? 0xDC : 0xFC); }
} uLongPress;

class SLongPress final : public LongPress {
  void onToggledOn() { Macros.play(MACRO(T(S))); }
  void onLongPress() { backspace(); typeUnicode(0xDF); }
} sLongPress;

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
  case MACRO_SWITCH_OS:
    switchOsMacro(keyState);
    break;
  case MACRO_OS_INFO:
    osInfoMacro(keyState);
    break;
  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  case MACRO_ISSUENUMBER:
    issueNumberMacro(keyState);
    break;
  case MACRO_E_EURO:
    eLongPress.onKeyswitchEvent(keyState);
    break;
  case MACRO_O_OE:
    oLongPress.onKeyswitchEvent(keyState);
    break;
  case MACRO_U_UE:
    uLongPress.onKeyswitchEvent(keyState);
    break;
  case MACRO_A_AE:
    aLongPress.onKeyswitchEvent(keyState);
    break;
  case MACRO_S_SS:
    sLongPress.onKeyswitchEvent(keyState);
    break;
  }
  return MACRO_NONE;
}


/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 01's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  COMBO_TOGGLE_CAPSLOCK
};

/** A tiny wrapper, to be used by MagicCombo.
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

static void toggleCapsLockAction(uint8_t combo_index) {
  toggleCapsLock();
}

/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS(
  [COMBO_TOGGLE_NKRO_MODE] = {
    .action = toggleKeyboardProtocol,
    .keys   = { R3C6, R2C6, R2C7 } // Left Fn + Esc + Shift
  },
  [COMBO_TOGGLE_CAPSLOCK] = {
    .action = toggleCapsLockAction,
    .keys   = { R2C7, R2C8 } // Left Shift + Right Shift
  }
);

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // The boot greeting effect pulses the LED button for 10 seconds after the
  // keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  TestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // We start with the LED effect that turns off all the LEDs.
  LEDOff,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // Third-party plugin: "The Matrix"-like effect
  LEDDigitalRainEffect,

  // The wavepool effect makes waves of light splash out from each keypress.
  WavepoolEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // Make both shift keys shine white if capslock is active
  LEDCapsLockEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The HostOS extension is not all that useful in itself, rather, it is a building block other
  // plugins and extensions can use to not repeat the same guesswork and logic.
  HostOS,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is called
  // 'BlazingTrail'. For details on other options, see
  // https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Stalker.md
  StalkerEffect.variant = STALKER(BlazingTrail);

  // see https://github.com/keyboardio/Kaleidoscope/blob/master/doc/plugin/LED-Wavepool.md
  WavepoolEffect.idle_timeout = 5000; // 5 seconds

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
