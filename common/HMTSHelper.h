#ifndef __HMTSHELPER_H__
#define __HMTSHELPER_H__

class HMTSHelper {
public:
    HMTSHelper();
    virtual ~HMTSHelper();

public:
    bool safeEnterFunc() const;
    void safeExitFunc() const;
    void cancelAllAccess() const;
    HANDLE getExitEvent() const { return m_hTSEventExit; }

private:
    HANDLE m_hTSEventAccessSafe;
    HANDLE m_hTSEventExit;
    mutable DWORD m_dwTSFlag;
};

#endif //__HMTSHELPER_H__





















