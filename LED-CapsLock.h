// -*- mode: c++ -*-
// LED-CapsLock
// Copyright (C) Tim Baumann 2019
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <Kaleidoscope.h>

static bool getCapsLockState() {
  return !!(kaleidoscope::hid::getKeyboardLEDs() & LED_CAPS_LOCK);
}

namespace kaleidoscope {
namespace plugin {

class LEDCapsLockEffect : public kaleidoscope::Plugin {
  public:
    // Event handlers.
    EventHandlerResult afterEachCycle();

};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::LEDCapsLockEffect LEDCapsLockEffect;
