#ifndef LOG_H
#define LOG_H

#include <stdbool.h> // bool
#include <stdio.h> // FILE, fputs(), fprintf()

#define LOG_FORMAT " %s:%d:%s "

#define logDebug(string) if (debugOut != NULL) {fprintf(debugOut, "[DEBUG]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfDebug(string, ...) if (debugOut != NULL) {fprintf(debugOut, "[DEBUG]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logInfo(string) if (infoOut != NULL) {fprintf(infoOut, "[INFO]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfInfo(string, ...) if (infoOut != NULL) {fprintf(infoOut, "[INFO]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logWarning(string) if (warningOut != NULL) {fprintf(warningOut, "[WARNING]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfWarning(string, ...) if (warningOut != NULL) {fprintf(warningOut, "[WARNING]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logError(string) if (errorOut != NULL) {fprintf(errorOut, "[ERROR]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfError(string, ...) if (errorOut != NULL) {fprintf(errorOut, "[ERROR]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define putsDebug(string) if (debugOut != NULL) {fputs((string), debugOut);}
#define printfDebug(string, ...) if (debugOut != NULL) {fprintf(debugOut, (string), __VA_ARGS__);}

#define putsInfo(string) if (infoOut != NULL) {fputs((string), infoOut);}
#define printfInfo(string, ...) if (infoOut != NULL) {fprintf(infoOut, (string), __VA_ARGS__);}

#define putsWarning(string) if (warningOut != NULL) {fputs((string), debugOut);}
#define printfWarning(string, ...) if (warningOut != NULL) {fprintf(debugOut, (string), __VA_ARGS__);}

#define putsError(string) if (errorOut != NULL) {fputs((string), debugOut);}
#define printfError(string, ...) if (errorOut != NULL) {fprintf(debugOut, (string), __VA_ARGS__);}

// These variables need to be set by code that uses this header. Leave unset for no output.
FILE *debugOut;
FILE *infoOut;
FILE *warningOut;
FILE *errorOut;

#endif // LOG_H
