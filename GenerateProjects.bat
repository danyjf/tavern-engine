@ECHO OFF

IF "%1"=="" (
    ECHO One of the following generators is required as the first argument:
    ECHO.   vs2022
    ECHO.   ninja
    ECHO Ex. GenerateProjects ^<generator^>
    PAUSE
    EXIT /b
)

IF "%1"=="vs2022" (
    CALL cmake -S . -B ./Build/ -G "Visual Studio 17 2022" -A x64
    EXIT /b
)

IF "%1"=="ninja" (
    IF "%2"=="" (
        ECHO When using this generator the build type must be passed as the second argument:
        ECHO.   debug
        ECHO.   release
        ECHO Ex. GenerateProjects ^<generator^> ^<build_type^>
        PAUSE
        EXIT /b
    )

    IF "%2"=="debug" (
        CALL cmake -S . -B ./Build/ -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang.exe -DCMAKE_C_COMPILER=clang.exe
        EXIT /b
    )
    IF "%2"=="release" (
        CALL cmake -S . -B ./Build/ -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang.exe -DCMAKE_C_COMPILER=clang.exe
        EXIT /b
    )
)

