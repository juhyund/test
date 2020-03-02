/* vim:set ts=4:sw=4:cino=>4: */
#ifndef _PCIS_CE_DLL_H_
#define _PCIS_CE_DLL_H_

#ifdef LIBSPEC_CE
#undef LIBSPEC_CE
#endif

#if defined(EXPORT_CE)
#define LIBSPEC_CE __declspec(dllexport)
#elif defined(IMPORT_CE)
#define LIBSPEC_CE __declspec(dllimport)
#else
#define LIBSPEC_CE
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* _PCIS_CE_DLL_H_ */
