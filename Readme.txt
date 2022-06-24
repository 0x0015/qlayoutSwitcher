qlayoutSwitcher: a simple Qt keyboard layout switcher.

Really, just runs the command defined in qlayoutSwitcher.json, with different args.

building:
    $ git clone --recursive [this repo]
    $ cd qlayoutSwitcher
    $ mkdir build;cd build
    $ qmake ..
    $ make -j
    $ cp ../qlayoutSwitcher.json .
