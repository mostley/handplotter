# Android app

## Setup

### OSX

1. install XCode
2. accept the xcode developers license (```sudo xcodebuild -license```)
3. install brew
4. install python (2.7.13)
5. make sure python is in your PATH environment variable
6. run the following commands

```
$ brew install pkg-config sdl2 sdl2_image sdl2_ttf sdl2_mixer gstreamer cmake jpeg libpng libtiff openexr eigen tbb
$ pip install -U Cython
$ pip install kivy numpy
```

7. add the science tap to homebrew

```
$ brew tap homebrew/science
```
8. install opencv
```
brew install opencv3 --with-contrib --with-python3 --HEAD
``