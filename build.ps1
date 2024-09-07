Import-Module "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell -VsInstallPath "C:\Program Files\Microsoft Visual Studio\2022\Community" -StartInPath .

if (!(Test-Path build -PathType Container)) {
    mkdir build
}


cd build
cmake -G "NMake Makefiles" ..
nmake
cd ..

if (Test-Path D:) {
    copy build\test.uf2 E:test.uf2
}

