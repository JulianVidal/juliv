# Juliv58

A 58 key layout for the lily58 keyboard. Custom symbols layer, numpad, navigation layer and function layer.

## Features

- **RGB Matrix:** 74 LEDs (58 per-key + 16 underglow) with independent control
- **OLED Displays:** Master shows layer/WPM/modifiers/brightness, Slave shows Bongo Cat animation
- **Custom Keycodes:** RGB_UGL (underglow toggle), RGB_KEY (per-key toggle)

# How to compile

I use the RP2040 Pro Micro, similar pinout to the ATMEGA Pro micro but with
different firmware. So in QMK it needs to be converted to the correct file type
.uf2.

```bash
# If you have added the default keyboard and keymap
qmk compile -e CONVERT_TO=rp2040_ce

# Without environment configuration
qmk compile -kb lily58 -km juliv -e CONVERT_TO=rp2040_ce
```

# Flashing

The Pro Micro RP2040 is flashed by double clicking the reset button, it will
act as storage space, drag in the .uf2 firmware and it will automatically flash
and reconnect as a keyboard.

If it doesn't work hold boot button while plugging into pc.
