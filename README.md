## Tweedracer

A barebones starter platform for remote control cars.

Designed to be built incredibly quickly, and readily hacked upon.


![sideview](docs/side.jpeg)

https://user-images.githubusercontent.com/6027644/164622684-72c06576-6b1f-4820-a275-ad31c8ef8cd2.mp4



### What's in the kit?


![kit](docs/kit.jpg)

#### Included

- 2x DC geared motors
- 2x Wheels
- 2x O-rings (for tires)
- 1x Caster
- 1x ESP32 dev board
- 1x Switch
- 1x Battery holder
- 1x Motor driver

#### Not included, but still required

- Solder
- Wire
- Hot glue
- Cardboard
- Imagination

### Hardware

Wire up all of the components like this:

![wiring](docs/wiring.png)

Basic soldering skills are required, but this is not a challenging build.


### Build

At this point, everything should get attached to the chassis. In the example above, everything is just hot glued to a cardboard frame.

You own this, so go wild with customisation. Arts and crafts, 3D printing, swapping out components for nicer ones, the world is your oyster. Flames make it go faster.


### Firmware

This projects uses the ESP-IDF framework, version 4.4.

- [Follow the official Espressif directions](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#installation-step-by-step). The [VSCode extension strategy](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/vscode-setup.html) is nice on Linux/Mac OS, so perhaps try that first, but I have had issues with it working properly for me on Windows.
- Download this git repo, and then open up the `tweedracer\esp` folder in VSCode.
- Hit the gear icon on the bottom of VSCode for the menuconfig
- Go to the `Example Connection Configuration` and add in your wifi credentials
- Hit the save button and close menuconfig window
- In the file browser, navigate to `main.c` and change the mDNS names around lines 24 and 26
- Build and flash to your board using the fire icon on the bottom
- Navigate to http://[yourMDNSname.local] on your phone (or a laptop, or a smart TV, or some other smart appliance)
- Drag the ball on the screen around to drive
- Do either of the motors seem backwards or flipped? Swap the pin assignments in `motor.h` (LEDC_OUTPUT_LEFT/RIGHT and DIR_OUTPUT_LEFT/RIGHT) and rebuild/reflash


### Future Improvements (An exercise for the builder)



![piracy](docs/piracy.png)

There are [thousands](https://www.thingiverse.com/search?q=vw+beetle) of better form factors.

4-wheel drive?

More clever control schemes?

A better web interface, adding decay so that the car doesn't try to escape when you lose connection.

Spinnin lawnmower blades!