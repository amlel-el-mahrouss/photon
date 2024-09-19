cl.exe /Zc:wchar_t /D"ZKA_WINDOWS=1" /EHsc /I"./" -I"../../vendor" /std:c++20 src/*.cc app/*.cc /link /out:PhotonBrowser.exe
