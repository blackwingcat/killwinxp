// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"


extern "C"

static int storagebox2[16] = {
    0 };
thread_local int storagebox1[16] = {
    0 };

__declspec(dllexport)
int random_range(int min_inclusive, int max_inclusive)
{
    std::random_device seed_gen;
    thread_local std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<int> dist(min_inclusive, max_inclusive);
    return dist(engine);
}

__declspec(dllexport)
void WINAPI funzero(HWND hwnd, HINSTANCE hi, char* xx, int vv) {
    MessageBoxA(0,xx,"test0",0);
}


__declspec(dllexport)
int WINAPI fun(HWND hwnd, HINSTANCE hi, char* xx, int vv)
{
    int i;
    int r;
    char pic[256];
    *pic = 0;
    for (i = 0; i < 8; i++) {
        do {
            r = random_range(0, 15);
        } while (storagebox1[r] == -1);
        wsprintfA(pic + strlen(pic), "[%d]", r);
        storagebox1[r] = -1;
    }
    lstrcatA(pic, "\r\n");
    lstrcpyA(xx, pic);
    //MessageBoxA(hwnd,pic,"test",0);
    for (r = i = 0; i < 16; i++) {
        if (storagebox1[i] != -1) r++;

    }
    return r;
}
__declspec(dllexport)
int WINAPI fun2(HWND hwnd, HINSTANCE hi, char* xx, int vv)
{
    int i;
    int r;
    char pic[256];
    *pic = 0;
    for (i = 0; i < 8; i++) {
        do {
            r = random_range(0, 15);
        } while (storagebox2[r] == -1);
        wsprintfA(pic + strlen(pic), "[%d]", r);
        storagebox2[r] = -1;
    }
    lstrcatA(pic, "\r\n");
    lstrcpyA(xx, pic);
    for (r = i = 0; i < 16; i++) {
        if (storagebox2[i] != -1) r++;

    }
    return r;
    //    MessageBoxA(hwnd, pic, "test2", 0);
}


//static 
DWORD dwTlsIndex = 0;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    LPVOID lpvData;
    BOOL fIgnore;
    int i;
    FILE* fs;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        fs = fopen("t.txt","ab+");
        fprintf(fs, "P");
        fclose(fs);
        for (i = 0; i < 16; i++) {
            storagebox1[i] = i + 1;
        }
        //        if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES)
//            return FALSE;
        break;
    case DLL_THREAD_ATTACH:
        fs = fopen("t.txt", "ab+");
        fprintf(fs, "T");
        fclose(fs);
        for (i = 0; i < 16; i++) {
            storagebox2[i] = i + 1;
        }
        /*        lpvData = (LPVOID)LocalAlloc(LPTR, 256);
        if (lpvData != NULL)
            fIgnore = TlsSetValue(dwTlsIndex, lpvData);
*/        
        break;
    case DLL_PROCESS_DETACH:
        fs = fopen("t.txt", "ab+");
        fprintf(fs, "[P]");
        fclose(fs);
        break;
    case DLL_THREAD_DETACH:
        fs = fopen("t.txt", "ab+");
        fprintf(fs, "[T]");
        fclose(fs);
        break;
        /*    case DLL_THREAD_DETACH:
        lpvData = TlsGetValue(dwTlsIndex);
        if (lpvData != NULL)
    LocalFree((HLOCAL)lpvData); 
        break;
    case DLL_PROCESS_DETACH:
        lpvData = TlsGetValue(dwTlsIndex);
        if (lpvData != NULL)
            LocalFree((HLOCAL)lpvData);

        // Release the TLS index.

        TlsFree(dwTlsIndex); 
        break;
*/
    }
    return TRUE;
}

