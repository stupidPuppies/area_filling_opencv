# area_filling_opencv

## Installation (MSVC)
1. Clone this repository
2. Add OpenCV's DLL path to your system ```PATH``` variable
3. Open ```src/area_filling_opencv.pro``` and change the paths in the following lines to your own OpenCV path:
```
INCLUDEPATH += C:/opencv/3.4.0/build/include

LIBS += C:/opencv/3.4.0/build/x64/vc15/lib/opencv_world340d.lib
```
4. Open ```src/area_filling_opencv.pro``` using Qt Creator, select MSVC2017 as your default compiler, then compile and run

## Installation (mingw)
```

### preparation
```cmd
git clone https://github.com/stupidPuppies/OpenCV-MinGW-Build
```
- Copy `OpenCV-MinGW-Build\include` to `C:\Qt\Qt5.10.0\5.10.0\mingw53_32\include` 
- Copy `OpenCV-MinGW-Build\bin` to `C:\Qt\Qt5.10.0\Tools\mingw530_32\bin` 

**Notice: The QT path might be different in your computer.**