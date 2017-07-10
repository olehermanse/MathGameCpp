## Video
[Arithmetic Game for Kids(YouTube)](https://www.youtube.com/watch?v=eTIW9aVn1QM)

## Download

```
git clone git@github.com:olehermanse/MathGameCpp.git
cd MathGameCpp
```

## Compile
```
cocos new -p com.olehermanse.arithmeticgame -l cpp -d ./temp MathGameCpp
cp -R temp/MathGameCpp/cocos2d ./
rm -rf temp
cmake .
make -j2
```
If you get this error:
```
error: reference to 'Rect' is ambiguous
```
I have submitted a Pull Request to fix it here:
https://github.com/cocos2d/cocos2d-x/pull/18048

## Run
```
./bin/ArithmeticGame
```

## Cocos Command Line tool
The `cocos` command line tool requires a correctly configured project for your OS.
(XCode, Visual Studio, Android Studio, etc.)

Generating correct project files is hard, so I usually stick to command line `cmake` and make.
The cocos tool is still useful sometimes:
```
cocos compile -p ios
cocos run -p ios
```

If you get this error:
```
Building mode: debug
Building...
invalid literal for float(): 8.3.3

Build failed: Take a look at the output above for details.
```

I have submitted a Pull Request to fix this here:
https://github.com/cocos2d/cocos2d-console/pull/424

## LICENSE
This project is licensed under the MIT License, which is the same license as cocos2d-x.
See [LICENSE.txt](./LICENSE.txt) for more info.
