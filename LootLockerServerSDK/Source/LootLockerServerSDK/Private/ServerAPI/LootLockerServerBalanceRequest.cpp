// Copyright (c) 2021 LootLocker

#include "LootLockerServerBalanceRequest.h"
#include "LootLockerServerEndpoints.h"
#include "LootLockerServerHttpClient.h"
#include "LootLockerServerResponse.h"

ULootLockerServerBalanceRequest::ULootLockerServerBalanceRequest()
{
}

void ULootLockerServerBalanceRequest::ListBalancesInWallet(const FString& WalletID, const FLootLockerServerListBalancesForWalletResponseBP& OnCompleteBP, const FLootLockerServerListBalancesForWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerListBalancesForWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::ListBalancesInWallet, { WalletID }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerServerBalanceRequest::GetWalletByWalletID(const FString& WalletID, const FLootLockerServerGetWalletResponseBP& OnCompleteBP, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByWalletId, { WalletID }, {}, OnCompleteBP, OnComplete);
}

void ULootLockerServerBalanceRequest::GetWalletByHolderID(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerGetWalletResponseBP& OnCompleteBP, const FLootLockerServerGetWalletResponseDelegate& OnComplete)
{
	const auto Inspector = FLootLockerServerGetWalletResponseDelegate::CreateLambda([HolderULID, HolderType, OnCompleteBP, OnComplete](const FLootLockerServerGetWalletResponse& Response)
		{
			if (Response.Success)
			{
				OnCompleteBP.ExecuteIfBound(Response);
				OnComplete.ExecuteIfBound(Response);
				return;
			}

			// Create Wallet and then get again
			const auto CreateWalletResponseHandler = FLootLockerServerCreateWalletResponseDelegate::CreateLambda([HolderULID, OnCompleteBP, OnComplete, Response](const FLootLockerServerCreateWalletResponse& CreateWalletResponse)
				{
					if (!CreateWalletResponse.Success)
					{
						OnCompleteBP.ExecuteIfBound(Response);
						OnComplete.ExecuteIfBound(Response);
						return;
					}

					ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByHolderId, { HolderULID }, {}, OnCompleteBP, OnComplete);
				});
			CreateWallet(HolderULID, HolderType, FLootLockerServerCreateWalletResponseBP(), CreateWalletResponseHandler);
		});
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerGetWalletResponse>(FLootLockerServerEmptyRequest{}, ULootLockerServerEndpoints::GetWalletByHolderId, { HolderULID }, {}, FLootLockerServerGetWalletResponseBP(), Inspector);
}

void ULootLockerServerBalanceRequest::CreditBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerCreditWalletResponseBP& OnCompleteBP, const FLootLockerServerCreditWalletResponseDelegate& OnComplete)
{

	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreditWalletResponse>(FLootLockerServerCreditRequest{ Amount, CurrencyID, WalletID }, ULootLockerServerEndpoints::CreditBalanceToWallet, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerServerBalanceRequest::DebitBalanceToWallet(const FString& WalletID, const FString& CurrencyID, const FString& Amount, const FLootLockerServerDebitWalletResponseBP& OnCompleteBP, const FLootLockerServerDebitWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerDebitWalletResponse>(FLootLockerServerDebitRequest{ Amount , CurrencyID, WalletID }, ULootLockerServerEndpoints::DebitBalanceToWallet, {}, {}, OnCompleteBP, OnComplete);
}

void ULootLockerServerBalanceRequest::CreateWallet(const FString& HolderULID, const ELootLockerServerWalletHolderTypes& HolderType, const FLootLockerServerCreateWalletResponseBP& OnCompleteBP, const FLootLockerServerCreateWalletResponseDelegate& OnComplete)
{
	ULootLockerServerHttpClient::SendRequest<FLootLockerServerCreateWalletResponse>(FLootLockerServerCreateWalletRequest{ HolderULID, ULootLockerServerConfig::GetEnum(TEXT("ELootLockerServerWalletHolderTypes"), static_cast<int32>(HolderType)).ToLower() },
		ULootLockerServerEndpoints::CreateWallet, {}, {}, OnCompleteBP, OnComplete);
}
