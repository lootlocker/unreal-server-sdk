// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerBalanceRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerBalanceRequest::ULootLockerServerBalanceRequest()
{
}

FString ULootLockerServerBalanceRequest::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseDelegate& OnComplete)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerListBalancesForWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListBalancesInWallet, { WalletID }, {}, OnComplete);
}

FString ULootLockerServerBalanceRequest::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByWalletId, { WalletID }, {}, OnComplete);
}

FString ULootLockerServerBalanceRequest::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
	const auto Inspector = FLootLockerServerGetWalletResponseDelegate::CreateLambda([HolderULID, HolderType, OnComplete](const FLootLockerServerGetWalletResponse& Response)
		{
			if (Response.Success)
			{
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			// Create Wallet and then get again
			const auto CreateWalletResponseHandler = FLootLockerServerCreateWalletResponseDelegate::CreateLambda([HolderULID, OnComplete, Response](const FLootLockerServerCreateWalletResponse& CreateWalletResponse)
				{
					if (!CreateWalletResponse.Success)
					{
						OnComplete.ExecuteIfBound(Response);
						return;
					}

					ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByHolderId, { HolderULID }, {}, OnComplete);
				});
			CreateWallet(HolderULID, HolderType, CreateWalletResponseHandler);
		});
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByHolderId, { HolderULID }, {}, Inspector);
}

FString ULootLockerServerBalanceRequest::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseDelegate& OnComplete)
{

	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreditWalletResponse>(FLootLockerServerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerServerEndpoints::CreditBalanceToWallet, {}, {}, OnComplete);
}

FString ULootLockerServerBalanceRequest::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseDelegate& OnComplete)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerDebitWalletResponse>(FLootLockerServerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerServerEndpoints::DebitBalanceToWallet, {}, {}, OnComplete);
}

FString ULootLockerServerBalanceRequest::CreateWallet(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerCreateWalletResponseDelegate& OnComplete)
{
	return ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreateWalletResponse>(FLootLockerServerCreateWalletRequest{ HolderULID, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() },
		ULootLockerServerEndpoints::CreateWallet, {}, {}, OnComplete);
}
