#ifndef __HM_EXPORTSDEF_H__
#define __HM_EXPORTSDEF_H__

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� HMLIB_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// HMLIB_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef HMLIB_EXPORTS
#define HMLIB_API __declspec(dllexport)
#else
#define HMLIB_API __declspec(dllimport)
#endif

#define EXTERN_C_START extern "C" {
#define EXTERN_C_END }


#endif //__HM_EXPORTSDEF_H__