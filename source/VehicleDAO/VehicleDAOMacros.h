#pragma once
#ifdef _WIN32
    #ifdef VEHICLEDAO_EXPORTS
        #define VEHICLEDAO_API __declspec(dllexport)
    #else
        #define VEHICLEDAO_API __declspec(dllimport)
    #endif //VEHICLEDAO_EXPORTS
#else //_WIN32
    #define VEHICLEDAO_API
#endif //_WIN32