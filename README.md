## rtimer

simple C lib for using timer functions in your project   
supported platforms:  `unix` | `macos` | `windows` | `stm32`   

for start using:  
`$ cd ~/your_project_root_directory`    
`git submodule add git@gitlab.com:RoboticsHardwareSolutions/rlibs/rtimer.git`   
 
OR   
`$ cd ~/your_project_root_directory`  
`$ mkdir rtimer`  
after copy content of repository to folder rcan  
   
For using in CMake project add in CMakeLists.txt next string 
```
include(rtimer/librtimer.cmake)

include_directories( ... ${RTIMER_DIRECTORIES})

add_executable(... ${RTIMER_EXECUTABLE_FILES})
```

## example: 
 
 ```


 ```
