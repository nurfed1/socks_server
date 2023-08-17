#include <windows.h>

void OnProcessAttach(HINSTANCE, DWORD, LPVOID);
// void StartW();

typedef struct {
    HINSTANCE hinstDLL;  // handle to DLL module
    DWORD fdwReason;     // reason for calling function // reserved
    LPVOID lpReserved;   // reserved
} ThreadItParams;

DWORD WINAPI ThreadIt(LPVOID lpParam) {
    ThreadItParams params = *((ThreadItParams*)lpParam);
    OnProcessAttach(params.hinstDLL, params.fdwReason, params.lpReserved);
    free(lpParam);
    return 0;
}

// __declspec(dllexport) DWORD WINAPI Start()
// {
//     OnProcessAttach(NULL, NULL, NULL);
//     return 0;
// }

BOOL WINAPI DllMain(
    HINSTANCE _hinstDLL,  // handle to DLL module
    DWORD _fdwReason,     // reason for calling function
    LPVOID _lpReserved)   // reserved
{
    switch (_fdwReason) {
    case DLL_PROCESS_ATTACH:
            // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        {
            ThreadItParams* lpThrdParam = (ThreadItParams*)malloc(sizeof(ThreadItParams));
            lpThrdParam->hinstDLL = _hinstDLL;
            lpThrdParam->fdwReason = _fdwReason;
            lpThrdParam->lpReserved = _lpReserved;
            HANDLE hThread = CreateThread(NULL, 0, ThreadIt, lpThrdParam, 0, NULL);
            // CreateThread() because otherwise DllMain() is highly likely to deadlock.
        }
        break;
    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;
    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;
    }
    return TRUE; // Successful.
}

