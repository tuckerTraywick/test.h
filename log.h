#ifndef LOG_H
#define LOG_H

#include <stdbool.h> // bool
#include <stdio.h> // FILE, fputs(), fprintf()

#define LOG_FORMAT " %s:%d:%s "

#define logDebug(string) if (enableDebug) {fprintf(debugOut, "[DEBUG]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfDebug(string, ...) if (enableDebug) {fprintf(debugOut, "[DEBUG]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logInfo(string) if (enableInfo) {fprintf(infoOut, "[INFO]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfInfo(string, ...) if (enableInfo) {fprintf(infoOut, "[INFO]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logWarning(string) if (enableWarning) {fprintf(warningOut, "[WARNING]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfWarning(string, ...) if (enableWarning) {fprintf(warningOut, "[WARNING]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define logError(string) if (enableError) {fprintf(errorOut, "[ERROR]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__);}
#define logfError(string, ...) if (enableError) {fprintf(errorOut, "[ERROR]" LOG_FORMAT string "\n", __FILE__, __LINE__, __func__, __VA_ARGS__);}

#define putsDebug(string) if (enableDebug) {fputs((string), debugOut);}
#define printfDebug(string, ...) if (enableDebug) {fprintf(debugOut, (string), __VA_ARGS__);}

#define putsInfo(string) if (enableInfo) {fputs((string), infoOut);}
#define printfInfo(string, ...) if (enableInfo) {fprintf(infoOut, (string), __VA_ARGS__);}

#define putsWarning(string) if (enableWarning) {fputs((string), debugOut);}
#define printfWarning(string, ...) if (enableWarning) {fprintf(debugOut, (string), __VA_ARGS__);}

#define putsError(string) if (enableError) {fputs((string), debugOut);}
#define printfError(string, ...) if (enableError) {fprintf(debugOut, (string), __VA_ARGS__);}

// Global variables need to be set by code that uses this header.
FILE* debugOut = NULL;
FILE *infoOut = NULL;
FILE *warningOut = NULL;
FILE *errorOut = NULL;

bool enableDebug = true;
bool enableInfo = true;
bool enableWarning = true;
bool enableError = true;

#endif // LOG_H
