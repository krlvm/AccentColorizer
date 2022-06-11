#include "SettingsHelper.h"
#include <VersionHelpers.h>

bool IsRegistryValueEnabled(LPCWSTR key, LPCWSTR value)
{
    HKEY hKey;
    RegOpenKeyEx(
        HKEY_CURRENT_USER,
        key, 0, KEY_READ, &hKey
    );

    if (!hKey)
    {
        return FALSE;
    }

    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    LONG nError = RegQueryValueEx(
        hKey, value, 0, NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize
    );

    RegCloseKey(hKey);

    return ERROR_SUCCESS == nError ? nResult : FALSE;
}

bool IsMenuColorizationEnabled()
{
    if (!IsWindows10OrGreater())
    {
        return TRUE;
    }
    return INVALID_FILE_ATTRIBUTES == GetFileAttributes(L"C:\\Windows\\ContextMenuNormalizer.exe")
        && GetLastError() == ERROR_FILE_NOT_FOUND;
}

bool IsProgressBarColorizationEnabled()
{
    return IsRegistryValueEnabled(L"SOFTWARE\\AccentColorizer", L"ColorizeProgressBar");
}