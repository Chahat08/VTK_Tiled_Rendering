# VTK_Basic

## Usage
```
start "" VTK_Basic.exe %SCENE_WIDTH% %SCENE_HEIGHT% %INSTANCE_WIDTH% %INSTANCE_HEIGHT% %INSTANCE_POSITION_X% %INSTANCE_POSITION_Y% %PHYSICAL_HEIGHT% %PHYSICAL_DISTANCE%
```

### Example batch script
Creates 4 instances, each of size 500 pixels in a 2x2 window layout.

```
start "" VTK_Basic.exe 1000 1000 500 500 0 0 2.5 3.0
start "" VTK_Basic.exe 1000 1000 500 500 500 0 2.5 3.0
start "" VTK_Basic.exe 1000 1000 500 500 0 500 2.5 3.0
start "" VTK_Basic.exe 1000 1000 500 500 500 500 2.5 3.0
```
