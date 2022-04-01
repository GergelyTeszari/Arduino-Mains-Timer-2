# Arduino-Mains-Timer-2
Two-hole mains hub timer with configurable timing per socket.
The program controls two relays, one of which can also cut the power of the Arduino itself when the timers expire.

# Feature Description:

There are three buttons and three LEDs in the finished circuit that need to be connected to the appropriate pins. The buttons are in a pull up configuration. The function of the LEDs is simple: they function as a display, while the buttons are the user interface.

When the first button is pressed after starting, the LEDs count upwards showing a binary number. Each value is interpreted as a binary number as many times as half an hour as the LEDs indicate, so the program can be timed from zero to seven, that is, from no timing to three and a half hours. The number can overflow from 7 to 0 instead of 8.

In the default case, the first relay is programmed together with the second, so the second is switched off together with the first relay. This is good because one of the relays can be used for the actual timing of something, while the other can be the power switch for the Arduino, thus shutting itself off when the timings expire.

If you want to set two separate timers instead, press the second key. The three LEDs will flash together to indicate that the first timer has been stored, switched to dual timer mode, and the program is waiting for the second timer value to be entered. In this case, the timing of the second relay can be set in the same way as before, by pressing the first button. At this stage, the program no longer responds to the second button, only the LEDs flash, indicating that the program is waiting to overwrite or approve the timing value of the second relay.

When we are satisfied with the same or different timer values, timers can be started with the third button. This is also indicated by the three LEDs flashing.

# After the start of the timers

After the timer started, pressing button one activates the night mode, which means that the LEDs no longer display the remaining time as a binary number in half an hour units. This way, the light from the LEDs will not disturb us in our sleep.

By pressing the second button after the start of the timer, the counter increments the value once by half an hour, and by holding it down, it continuously increases the timer by half an hour. So if extra time needed later during the timing process, we can add it on the fly. The number can overflow from 7 to 0 instead of 8 here too.

Pressing the third button during a timing process aborts the timers, discarding both the same and different timers.

However, only two relays can be timed by this version of the program, since it is a program made for a self-made shield, the program for timing more relays can also be found on this GitHub page.
