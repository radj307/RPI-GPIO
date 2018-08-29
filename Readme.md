# RPI-GPIO, Keep it Simple, Small
RPI-GPIO is a very small and very simple C++ library, that can be used to manipulate te GPIO pins on a Raspberry Pi 2/2B/2B+ (other models could be supported in a not so distant future).

## Why ?
"Why would you bother writing such a tool, when there are tons of libraries out there, that already exist ?". Well, why not ? This is my first real life C++ project and I'm ok with reinventing the wheel, as long as I learn new things.

## What it can do
As of today, I have implemented the most basic functionalities : reading and writing to the GPIO pins.I haven't even had time to test it yet ! This project really is at its embryo state, for now !

## How to use it
Just compile it using `make`, then take the header files in `lib/include` and put them in your own sources. When compiling your project, you will just have to link against `lib/build/bin/rpigpio.a`.

## Roadmap
Here is a list of features and changes that I have planned for this project, in no particular order :
- Build :
    - Switch to a better build system
    - Continuous integration
- Testing :
    - Write some tests
    - Find a way to automate testing on a real machine
- Features :
    - Support all Raspberry Pi plateforms
    - Support more GPIO functionnalities (obviously)
    - Maybe write some command line tools ? (We don't want to go too deep into Wiring Pi's path)
- Misc :
    - Better error handling with exceptions
    - Compile to a dynamic library
    - **Find a good name**
- Documentation
    - Yeah write some documentation ! This could help people ... you know ... actually **use** the library

## Contribute
Want to add your personnal touch to this project ? You are very welcome to do so ! Feel free to open issues and submit PRs. If you are correcting some of my mistakes, I would really appreciate it if you also told me exactly what I did wrong and why your solution is the best.

## Licence
This project is currently licensed under the MIT Licence. This could change in a near or distant future, depending on the contributions.