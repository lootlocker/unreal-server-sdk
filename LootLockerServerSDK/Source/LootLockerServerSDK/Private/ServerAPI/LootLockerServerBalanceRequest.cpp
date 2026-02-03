// Copyright (c) 2021 LootLocker

#include "ServerAPI/LootLockerServerBalanceRequest.h"

#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerBalanceRequest::ULootLockerServerBalanceRequest()
{
}

void ULootLockerServerBalanceRequest::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerListBalancesForWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListBalancesInWallet, { WalletID }, {}, OnComplete);
}

void ULootLockerServerBalanceRequest::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByWalletId, { WalletID }, {}, OnComplete);
}

void ULootLockerServerBalanceRequest::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
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
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByHolderId, { HolderULID }, {}, Inspector);
}

void ULootLockerServerBalanceRequest::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseDelegate& OnComplete)
{

	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreditWalletResponse>(FLootLockerServerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerServerEndpoints::CreditBalanceToWallet, {}, {}, OnComplete);
}

void ULootLockerServerBalanceRequest::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerDebitWalletResponse>(FLootLockerServerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerServerEndpoints::DebitBalanceToWallet, {}, {}, OnComplete);
}

void ULootLockerServerBalanceRequest::CreateWallet(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerCreateWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreateWalletResponse>(FLootLockerServerCreateWalletRequest{ HolderULID, ULootLockerServerEnumUtils::GetEnum(TEXT("ELootLockerServerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() },
		ULootLockerServerEndpoints::CreateWallet, {}, {}, OnComplete);
}
