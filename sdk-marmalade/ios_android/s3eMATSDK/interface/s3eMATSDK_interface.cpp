/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */

#include "s3eExt.h"
#include "IwDebug.h"
#include "s3eDevice.h"


#include "s3eMATSDK.h"


// For MIPs (and WP8) platform we do not have asm code for stack switching 
// implemented. So we make LoaderCallStart call manually to set GlobalLock
#if defined __mips || defined S3E_ANDROID_X86 || (defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP))
#define LOADER_CALL
#endif

/**
 * Definitions for functions types passed to/from s3eExt interface
 */
typedef       void(*MATStartMobileAppTracker_t)(const char* adId, const char* convKey);
typedef       void(*MATTrackInstall_t)();
typedef       void(*MATTrackUpdate_t)();
typedef       void(*MATTrackInstallWithReferenceId_t)(const char* refId);
typedef       void(*MATTrackActionForEventIdOrName_t)(const char* eventIdOrName, bool isId, const char* refId);
typedef       void(*MATTrackActionForEventIdOrNameItems_t)(const char* eventIdOrName, bool isId, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature);
typedef       void(*MATTrackAction_t)(const char* eventIdOrName, bool isId, const char* revenue, const char* currency);
typedef       void(*MATSetPackageName_t)(const char* packageName);
typedef       void(*MATSetCurrencyCode_t)(const char* currencyCode);
typedef       void(*MATSetOpenUDID_t)(const char* openUDID);
typedef       void(*MATSetUIID_t)(const char* uiid);
typedef       void(*MATSetUserId_t)(const char* userId);
typedef       void(*MATSetRevenue_t)(const char* revenue);
typedef       void(*MATSetSiteId_t)(const char* siteId);
typedef       void(*MATSetTRUSTeId_t)(const char* tpid);
typedef       void(*MATSetAppAdTracking_t)(bool enable);
typedef       void(*MATSetDelegate_t)(bool enable);
typedef       void(*MATSetJailbroken_t)(bool isJailbroken);
typedef       void(*MATSetShouldAutoDetectJailbroken_t)(bool shouldAutoDetect);
typedef       void(*MATSetMACAddress_t)(const char* mac);
typedef       void(*MATSetODIN1_t)(const char* odin1);
typedef       void(*MATSetUseCookieTracking_t)(bool useCookieTracking);
typedef       void(*MATSetAge_t)(int age);
typedef       void(*MATSetGender_t)(int gender);
typedef       void(*MATSetLocation_t)(const char* latitude, const char* longitude, const char* altitude);
typedef       void(*MATStartAppToAppTracking_t)(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect);
typedef       void(*MATSetRedirectUrl_t)(const char* redirectUrl);
typedef       void(*MATSetAppleAdvertisingIdentifier_t)(const char* advertiserId);
typedef       void(*MATSetAppleVendorIdentifier_t)(const char* vendorId);
typedef       void(*MATSetShouldAutoGenerateAppleVendorIdentifier_t)(bool shouldAutoGenerate);
typedef       void(*MATSetShouldAutoGenerateAppleAdvertisingIdentifier_t)(bool shouldAutoGenerate);
typedef       void(*MATSDKParameters_t)();
typedef       void(*MATSetDebugMode_t)(bool shouldDebug);
typedef       void(*MATSetAllowDuplicates_t)(bool allowDuplicates);

/**
 * struct that gets filled in by s3eMATSDKRegister
 */
typedef struct s3eMATSDKFuncs
{
    MATStartMobileAppTracker_t m_MATStartMobileAppTracker;
    MATTrackInstall_t m_MATTrackInstall;
    MATTrackUpdate_t m_MATTrackUpdate;
    MATTrackInstallWithReferenceId_t m_MATTrackInstallWithReferenceId;
    MATTrackActionForEventIdOrName_t m_MATTrackActionForEventIdOrName;
    MATTrackActionForEventIdOrNameItems_t m_MATTrackActionForEventIdOrNameItems;
    MATTrackAction_t m_MATTrackAction;
    MATSetPackageName_t m_MATSetPackageName;
    MATSetCurrencyCode_t m_MATSetCurrencyCode;
    MATSetOpenUDID_t m_MATSetOpenUDID;
    MATSetUIID_t m_MATSetUIID;
    MATSetUserId_t m_MATSetUserId;
    MATSetRevenue_t m_MATSetRevenue;
    MATSetSiteId_t m_MATSetSiteId;
    MATSetTRUSTeId_t m_MATSetTRUSTeId;
    MATSetAppAdTracking_t m_MATSetAppAdTracking;
    MATSetDelegate_t m_MATSetDelegate;
    MATSetJailbroken_t m_MATSetJailbroken;
    MATSetShouldAutoDetectJailbroken_t m_MATSetShouldAutoDetectJailbroken;
    MATSetMACAddress_t m_MATSetMACAddress;
    MATSetODIN1_t m_MATSetODIN1;
    MATSetUseCookieTracking_t m_MATSetUseCookieTracking;
    MATSetAge_t m_MATSetAge;
    MATSetGender_t m_MATSetGender;
    MATSetLocation_t m_MATSetLocation;
    MATStartAppToAppTracking_t m_MATStartAppToAppTracking;
    MATSetRedirectUrl_t m_MATSetRedirectUrl;
    MATSetAppleAdvertisingIdentifier_t m_MATSetAppleAdvertisingIdentifier;
    MATSetAppleVendorIdentifier_t m_MATSetAppleVendorIdentifier;
    MATSetShouldAutoGenerateAppleVendorIdentifier_t m_MATSetShouldAutoGenerateAppleVendorIdentifier;
    MATSetShouldAutoGenerateAppleAdvertisingIdentifier_t m_MATSetShouldAutoGenerateAppleAdvertisingIdentifier;
    MATSDKParameters_t m_MATSDKParameters;
    MATSetDebugMode_t m_MATSetDebugMode;
    MATSetAllowDuplicates_t m_MATSetAllowDuplicates;
} s3eMATSDKFuncs;

static s3eMATSDKFuncs g_Ext;
static bool g_GotExt = false;
static bool g_TriedExt = false;
static bool g_TriedNoMsgExt = false;

static bool _extLoad()
{
    if (!g_GotExt && !g_TriedExt)
    {
        s3eResult res = s3eExtGetHash(0xbb39d6f4, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        else
            s3eDebugAssertShow(S3E_MESSAGE_CONTINUE_STOP_IGNORE,                 "error loading extension: s3eMATSDK");
            
        g_TriedExt = true;
        g_TriedNoMsgExt = true;
    }

    return g_GotExt;
}

static bool _extLoadNoMsg()
{
    if (!g_GotExt && !g_TriedNoMsgExt)
    {
        s3eResult res = s3eExtGetHash(0xbb39d6f4, &g_Ext, sizeof(g_Ext));
        if (res == S3E_RESULT_SUCCESS)
            g_GotExt = true;
        g_TriedNoMsgExt = true;
        if (g_TriedExt)
            g_TriedExt = true;
    }

    return g_GotExt;
}

s3eBool s3eMATSDKAvailable()
{
    _extLoadNoMsg();
    return g_GotExt ? S3E_TRUE : S3E_FALSE;
}

void MATStartMobileAppTracker(const char* adId, const char* convKey)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[0] func: MATStartMobileAppTracker"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATStartMobileAppTracker(adId, convKey);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATTrackInstall()
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[1] func: MATTrackInstall"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATTrackInstall();

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATTrackUpdate()
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[2] func: MATTrackUpdate"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATTrackUpdate();

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATTrackInstallWithReferenceId(const char* refId)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[3] func: MATTrackInstallWithReferenceId"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATTrackInstallWithReferenceId(refId);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATTrackActionForEventIdOrName(const char* eventIdOrName, bool isId, const char* refId)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[4] func: MATTrackActionForEventIdOrName"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATTrackActionForEventIdOrName(eventIdOrName, isId, refId);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATTrackActionForEventIdOrNameItems(const char* eventIdOrName, bool isId, const MATArray* items, const char* refId, const char* revenueAmount, const char* currencyCode, uint8 transactionState, const char* receipt, const char* receiptSignature)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[5] func: MATTrackActionForEventIdOrNameItems"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATTrackActionForEventIdOrNameItems(eventIdOrName, isId, items, refId, revenueAmount, currencyCode, transactionState, receipt, receiptSignature);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATTrackAction(const char* eventIdOrName, bool isId, const char* revenue, const char* currency)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[6] func: MATTrackAction"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATTrackAction(eventIdOrName, isId, revenue, currency);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetPackageName(const char* packageName)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[7] func: MATSetPackageName"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetPackageName(packageName);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetCurrencyCode(const char* currencyCode)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[8] func: MATSetCurrencyCode"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetCurrencyCode(currencyCode);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetOpenUDID(const char* openUDID)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[9] func: MATSetOpenUDID"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetOpenUDID(openUDID);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetUIID(const char* uiid)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[10] func: MATSetUIID"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetUIID(uiid);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetUserId(const char* userId)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[11] func: MATSetUserId"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetUserId(userId);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetRevenue(const char* revenue)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[12] func: MATSetRevenue"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetRevenue(revenue);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetSiteId(const char* siteId)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[13] func: MATSetSiteId"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetSiteId(siteId);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetTRUSTeId(const char* tpid)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[14] func: MATSetTRUSTeId"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetTRUSTeId(tpid);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetAppAdTracking(bool enable)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[15] func: MATSetAppAdTracking"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetAppAdTracking(enable);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetDelegate(bool enable)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[16] func: MATSetDelegate"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetDelegate(enable);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetJailbroken(bool isJailbroken)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[17] func: MATSetJailbroken"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetJailbroken(isJailbroken);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetShouldAutoDetectJailbroken(bool shouldAutoDetect)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[18] func: MATSetShouldAutoDetectJailbroken"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetShouldAutoDetectJailbroken(shouldAutoDetect);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetMACAddress(const char* mac)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[19] func: MATSetMACAddress"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetMACAddress(mac);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetODIN1(const char* odin1)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[20] func: MATSetODIN1"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetODIN1(odin1);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetUseCookieTracking(bool useCookieTracking)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[21] func: MATSetUseCookieTracking"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetUseCookieTracking(useCookieTracking);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetAge(int age)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[22] func: MATSetAge"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetAge(age);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetGender(int gender)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[23] func: MATSetGender"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetGender(gender);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetLocation(const char* latitude, const char* longitude, const char* altitude)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[24] func: MATSetLocation"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetLocation(latitude, longitude, altitude);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATStartAppToAppTracking(const char* targetAppId, const char* advertiserId, const char* offerId, const char* publisherId, bool shouldRedirect)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[25] func: MATStartAppToAppTracking"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATStartAppToAppTracking(targetAppId, advertiserId, offerId, publisherId, shouldRedirect);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetRedirectUrl(const char* redirectUrl)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[26] func: MATSetRedirectUrl"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetRedirectUrl(redirectUrl);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetAppleAdvertisingIdentifier(const char* advertiserId)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[27] func: MATSetAppleAdvertisingIdentifier"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetAppleAdvertisingIdentifier(advertiserId);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetAppleVendorIdentifier(const char* vendorId)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[28] func: MATSetAppleVendorIdentifier"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetAppleVendorIdentifier(vendorId);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetShouldAutoGenerateAppleVendorIdentifier(bool shouldAutoGenerate)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[29] func: MATSetShouldAutoGenerateAppleVendorIdentifier"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetShouldAutoGenerateAppleVendorIdentifier(shouldAutoGenerate);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetShouldAutoGenerateAppleAdvertisingIdentifier(bool shouldAutoGenerate)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[30] func: MATSetShouldAutoGenerateAppleAdvertisingIdentifier"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetShouldAutoGenerateAppleAdvertisingIdentifier(shouldAutoGenerate);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSDKParameters()
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[31] func: MATSDKParameters"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSDKParameters();

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetDebugMode(bool shouldDebug)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[32] func: MATSetDebugMode"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetDebugMode(shouldDebug);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}

void MATSetAllowDuplicates(bool allowDuplicates)
{
    IwTrace(MATSDK_VERBOSE, ("calling s3eMATSDK[33] func: MATSetAllowDuplicates"));

    if (!_extLoad())
        return;

#ifdef LOADER_CALL
    s3eDeviceLoaderCallStart(S3E_TRUE, NULL);
#endif

    g_Ext.m_MATSetAllowDuplicates(allowDuplicates);

#ifdef LOADER_CALL
    s3eDeviceLoaderCallDone(S3E_TRUE, NULL);
#endif

    return;
}
