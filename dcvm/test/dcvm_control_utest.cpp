#include <dcvm/dcvm.h>
#include "dcvm_systemapi_test.h"

#include <memory>
#include <gtest/gtest.h>
#include "dcvm_utest_helper.hpp"

using namespace dcvm_utests;

TEST(DCVMControl, dcvm_library_initialization)
{
    DCVM *pDCVM = nullptr;

    DCVM_ERROR err = dcvm_Init(GetDCVMSystemApi(), nullptr, nullptr);
    EXPECT_FALSE(DCVM_SUCCESS(err));
    EXPECT_EQ(DCVM_ERR_BAD_PARAMS, err);

    err = dcvm_Init(GetDCVMSystemApi(), &pDCVM, nullptr);

    dcvm_Release(pDCVM, nullptr);

    EXPECT_EQ(g_MemoryCounter, 0);
}

TEST(DCVMControl, dcvm_library_cloud_provider)
{
    {
        dcvm_utests::PDCVM pDCVM = dcvm_utests::CreateDCVM();

        dcvm_char_t *pProviderId = nullptr;
        auto err = dcvm_ControlAddCloudProvider(nullptr, GetDCVMCloudProviderApi(), nullptr, nullptr);
        EXPECT_TRUE(DCVM_FAILED(err));
        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);

        err = dcvm_ControlAddCloudProvider(pDCVM.get(), GetDCVMCloudProviderApi(), &pProviderId, nullptr);
        EXPECT_TRUE(DCVM_SUCCESS(err));
        ASSERT_TRUE(pProviderId != nullptr);
        EXPECT_EQ(DCVMUtestString_t(pProviderId), DCVMUtestString_t(g_pCloudProviderStubId));

        dcvm_ReleaseBuffer(pProviderId);
        pProviderId = nullptr;

        dcvm_char_t *pProvidersIds = nullptr;
        dcvm_size_t size = 0;

        err = dcvm_ControlGetCloudProviders(nullptr, nullptr, nullptr, nullptr);
        EXPECT_TRUE(DCVM_ERR_BAD_PARAMS, err);

        err = dcvm_ControlGetCloudProviders(pDCVM.get(), &pProvidersIds, &size, nullptr);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        ASSERT_NE(pProvidersIds, nullptr);
        EXPECT_EQ(size, SIZEOF_DCVM_CHAR_T_STRING(g_pCloudProviderStubId));
        EXPECT_EQ(DCVMUtestString_t(pProvidersIds), DCVMUtestString_t(g_pCloudProviderStubId));

        dcvm_ReleaseBuffer(pProvidersIds);
        pProvidersIds = nullptr;

        err = dcvm_ControlGetAuthorzationUri(nullptr, nullptr, nullptr, nullptr);
        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);

        dcvm_char_t *pUri = nullptr;
        err = dcvm_ControlGetAuthorzationUri(pDCVM.get(), DCVM_TEXT("FakeProvider"), &pUri, nullptr);
        EXPECT_EQ(err, DCVM_ERR_PROVIDER_IS_NOT_FOUND);

        err = dcvm_ControlGetAuthorzationUri(pDCVM.get(), g_pCloudProviderStubId, &pUri, nullptr);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        ASSERT_NE(pUri, nullptr);
        EXPECT_EQ(DCVMUtestString_t(pUri), DCVMUtestString_t(g_pCloudProviderStubOAuthUri));

        dcvm_ReleaseBuffer(pUri);
    }

    EXPECT_EQ(g_MemoryCounter, 0);
}

TEST(DCVMControl, dcvm_library_create_cloud_disk)
{
    {
        dcvm_utests::PDCVM pDCVM = dcvm_utests::CreateDCVM();

        dcvm_char_t *pProviderId = nullptr;
        auto err = dcvm_ControlAddCloudProvider(pDCVM.get(), GetDCVMCloudProviderApi(), &pProviderId, nullptr);
        EXPECT_TRUE(DCVM_SUCCESS(err));

        DCVMClientOAuthCode oauthCode = 
        {
            pProviderId
            , g_pCloudStubOAauthCode1
        };

        struct DCVMCloudDisk *pCloudDisk = nullptr;
        err = dcvm_ControlCreateCloudDisk(nullptr, nullptr, nullptr, nullptr);
        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);

        dcvm_size_t cloudDiskId = static_cast<dcvm_size_t>(-1);
        err = dcvm_ControlCreateCloudDisk(pDCVM.get(), &oauthCode, &cloudDiskId, nullptr);
        EXPECT_TRUE(DCVM_SUCCESS(err));
        EXPECT_NE(cloudDiskId, static_cast<dcvm_size_t>(-1));

        dcvm_ReleaseBuffer(pProviderId);
        pProviderId = nullptr;

        dcvm_size_t *pCloudDisksIds = nullptr;
        dcvm_size_t cntIds = static_cast<dcvm_size_t>(-1);

        err = dcvm_ControlGetCloudDisks(nullptr, nullptr, nullptr, nullptr);
        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);

        err = dcvm_ControlGetCloudDisks(pDCVM.get(), &pCloudDisksIds, &cntIds, nullptr);
        ASSERT_TRUE(DCVM_SUCCESS(err));
        ASSERT_NE(pCloudDisksIds, nullptr);
        ASSERT_EQ(cntIds, 1);
        EXPECT_EQ(cloudDiskId, pCloudDisksIds[0]);

        dcvm_ReleaseBuffer(pCloudDisksIds);

        err = dcvm_ControlGetCloudDiskInformation(nullptr, cloudDiskId, nullptr, nullptr, nullptr);
        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);

        DCVMCloudDiskInfo di = {};
        dcvm_size_t diSize = 0;
        err = dcvm_ControlGetCloudDiskInformation(pDCVM.get(), cloudDiskId, nullptr, &diSize, nullptr);
        EXPECT_TRUE(DCVM_SUCCESS(err));
        EXPECT_EQ(diSize, sizeof(di));

        err = dcvm_ControlGetCloudDiskInformation(pDCVM.get(), cloudDiskId, &di, &diSize, nullptr);
        EXPECT_TRUE(DCVM_SUCCESS(err));
        EXPECT_EQ(DCVMUtestString_t(di.providerInfo.id), DCVMUtestString_t(g_pCloudProviderStubId));
        EXPECT_EQ(DCVMUtestString_t(di.userInfo.name), DCVMUtestString_t(g_pCloudStubUserName));
        EXPECT_EQ(di.childrenCount, 0);
        EXPECT_EQ(di.pChildren, nullptr);
        EXPECT_NE(di.maxFileSize, 0);
        EXPECT_NE(di.totalSpace, 0);
        EXPECT_EQ(di.usedSpace, 0);
    }

    EXPECT_EQ(g_MemoryCounter, 0);
}

//TEST(DCVMControl, dcvm_library_initialize_cloud_disk)
//{
//    {
//        dcvm_utests::PDCVM pDCVM = dcvm_utests::CreateDCVM();
//
//        dcvm_char_t *pProviderId = nullptr;
//        auto err = dcvm_ControlAddCloudProvider(pDCVM.get(), GetDCVMCloudProviderApi(), &pProviderId, nullptr);
//        EXPECT_TRUE(DCVM_SUCCESS(err));
//
//        DCVMClientOAuthCode oauthCode = 
//        {
//            pProviderId
//            , g_pCloudStubOAauthCode1
//        };
//
//        dcvm_size_t cloudDiskId = static_cast<dcvm_size_t>(-1);
//        err = dcvm_ControlCreateCloudDisk(pDCVM.get(), &oauthCode, &cloudDiskId, nullptr);
//        ASSERT_TRUE(DCVM_SUCCESS(err));
//        ASSERT_NE(cloudDiskId, static_cast<dcvm_size_t>(-1));
//
//        dcvm_ReleaseBuffer(pProviderId);
//        pProviderId = nullptr;
//
//        err = dcvm_ControlInitCloudDisk(nullptr, cloudDiskId, 0, nullptr, nullptr);
//        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);
//
//        struct DCVMCloudDisk *pCloudDisk = nullptr;
//        err = dcvm_ControlInitCloudDisk(pDCVM.get(), static_cast<dcvm_size_t>(-1), 0, &pCloudDisk, nullptr);
//        EXPECT_EQ(err, DCVM_ERR_CLOUDDISK_IS_NOT_FOUND);
//
//        err = dcvm_ControlInitCloudDisk(pDCVM.get(), cloudDiskId, 0, &pCloudDisk, nullptr);
//        EXPECT_TRUE(DCVM_SUCCESS(err));
//        ASSERT_NE(pCloudDisk, nullptr);
//
//        err = dcvm_ControlReleaseCloudDisk(nullptr, nullptr, nullptr);
//        EXPECT_EQ(err, DCVM_ERR_BAD_PARAMS);
//
//        err = dcvm_ControlReleaseCloudDisk(pDCVM.get(), pCloudDisk, nullptr);
//        EXPECT_TRUE(DCVM_SUCCESS(err));
//    }
//
//    EXPECT_EQ(g_MemoryCounter, 0);
//}