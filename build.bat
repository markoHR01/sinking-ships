setlocal

:: Location of SDL2 files
set SDL2_DIR=C:\dev\libs\SDL2
set SDL2_TTF_DIR=C:\dev\libs\SDL2_ttf

set CXX=g++
set CXXFLAGS=-Wall -Iinclude ^
             -I%SDL2_DIR%\include ^
             -I%SDL2_DIR%\include\SDL2 ^
             -I%SDL2_TTF_DIR%\include
set LDFLAGS=-L%SDL2_DIR%\lib ^
            -L%SDL2_TTF_DIR%\lib ^
            -lSDL2main ^
            -lSDL2 ^
            -lSDL2_ttf ^
            -lws2_32

set SOURCES=source\main.cpp ^
            source\menu.cpp ^
            source\setup.cpp ^
            source\game.cpp ^
            source\rendering.cpp ^
            source\board.cpp ^
            source\ship.cpp ^
            source\game_state.cpp ^
            source\socket_factory.cpp ^
            source\socket_windows.cpp ^
            source\message.cpp ^
            source\network_thread.cpp

%CXX% %CXXFLAGS% %SOURCES% %LDFLAGS% -o sinking-ships.exe -Wl,-subsystem,windows

:: Move SDL2 .ddl files next to .exe file
copy /Y %SDL2_DIR%\bin\SDL2.dll .
copy /Y %SDL2_TTF_DIR%\bin\SDL2_ttf.dll .

endlocal
