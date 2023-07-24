# Games using raylib 


## Dependencies
```
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Install Raylib
```
git clone https://github.com/raysan5/raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make up
sudo make install
sudo cp /usr/local/lib/libraylib.so.420 /usr/lib/
```

## Run/Debug
* Open workspace in VSCode, `Ctrl+Shift+B` to build current file.
* `build/a.out` will be the executable
* `F5` to debug build/a.out

## Structure
* Place all resources/textures etc in `build` dir
* code goes into `src/`