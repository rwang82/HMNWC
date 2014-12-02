echo off
echo ---请确保拷贝前编译完Debug和Release两种模式
pause

xcopy /Y .\include\json\*.* ..\..\common\json
xcopy /Y .\build\vs71\debug\lib_json\json_vc71_libmtd.lib ..\..\Debug\lib
xcopy /Y .\build\vs71\release\lib_json\json_vc71_libmt.lib ..\..\Release\lib


echo ---拷贝完成
pause