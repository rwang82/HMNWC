echo off
echo ---��ȷ������ǰ������Debug��Release����ģʽ
pause

xcopy /Y .\include\json\*.* ..\..\common\json
xcopy /Y .\build\vs71\debug\lib_json\json_vc71_libmtd.lib ..\..\Debug\lib
xcopy /Y .\build\vs71\release\lib_json\json_vc71_libmt.lib ..\..\Release\lib


echo ---�������
pause