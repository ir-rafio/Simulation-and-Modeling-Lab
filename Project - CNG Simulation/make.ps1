## MakeFile alternative

function compile
{
    echo "........compiling.........."
    g++ -c .\src\*.cpp -I.\include 
    echo "..........moving............"
    #Move-Item -Path *.o -Destination .\obj -force
    echo ".........linking............"
    g++ -o "Run" .\*.o
    echo "...........done............."
}

function clean{
    echo "........clean.........."
    #rm .\obj\*.o
    rm .\*.o
    rm .\*.out
    rm .\*.csv
    rm .\trace\*.csv
    echo "...........done............."
}
function cleanall{
    echo "........clean.........."
    #rm .\obj\*.o
    rm .\*.o
    rm .\"Run".exe
    rm .\*.out
    rm .\*.csv
    rm .\trace\*.csv
    echo "...........done............."
}

function Helpmenu{
        echo "Write -c for compile, clean for deleting the .o files and cleanall for .o and .exe file"
        echo "And -e to execute the game"
        echo "Or you can pass -a/all to all three (compile,clean,execute)"
}

function RunAgain{
    $param2= Read-Host "Enter the command: "
    switch ($param2){
            "-h" {Helpmenu; Break}
            "help" {Helpmenu; Break}
            "compile" {compile}
            "-c" {compile}
            "clean" {clean}
            "cleanall" {cleanall; Break}
            "execute" {.\"Run".exe; Break}
            "-e" {.\"Run".exe; Break}
            "all" {
                    compile;
                    clean;
                    #.\"Run".exe;
                    Break
                    }
            "-a" {
                    compile;
                    clean;
                    #.\"Run".exe;
                    Break
                }
        }

        RunAgain;
}

$params =$args[0]

switch ($params){
    "" {Helpmenu; RunAgain; Break}
    "-h" {Helpmenu; Break}
    "help" {Helpmenu; Break}
    "compile" {compile}
    "-c" {compile}
    "clean" {clean}
    "cleanall" {cleanall; Break}
    "execute" {.\"Run".exe; Break}
    "-e" {.\"Run".exe; Break}
    "all"
    {
        compile;
        clean;
        #.\"Run".exe;
        Break
    }
    "-a"
    {
        compile;
        clean;
        #.\"Run".exe;
        Break
    }
}