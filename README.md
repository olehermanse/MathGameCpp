## Video
[Arithmetic Game for Kids(YouTube)](https://www.youtube.com/watch?v=eTIW9aVn1QM)

## Download

```
git clone git@github.com:olehermanse/MathGameCpp.git
cd MathGameCpp
```

## Compile
```
cocos new -p com.olehermanse.mathgamecpp -l cpp -d ./temp MathGameCpp
cp -R temp/MathGameCpp/cocos2d ./
rm -rf temp
cmake .
make -j2
```
There is 1 error in cocos2d (on OSX), I have submitted a Pull Request to fix it here:
https://github.com/cocos2d/cocos2d-x/pull/18048

## Run
```
./bin/MathGameCpp
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
