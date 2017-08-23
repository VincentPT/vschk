#pragma once
#ifdef VEHICLEDAO_EXPORTS
#define VEHICLEDAO_API __declspec(dllexport)
#else
#define VEHICLEDAO_API __declspec(dllimport)
#endif