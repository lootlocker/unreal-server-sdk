#pragma once
#include "Widgets/SCompoundWidget.h"
#include "LootLockerServerLogger.h"
#include "Widgets/Views/SListView.h"
#include "Templates/SharedPointer.h"
#include "Containers/Map.h"

class SSearchBox;

struct FLootLockerServerLogEntry
{
    FString Message;
    ELootLockerServerLogLevel Level;
    FDateTime Timestamp;
    bool bIsRequestLog = false;
    FString RequestPath;
    FString HttpMethod;
    int32 StatusCode = -1;
    FString Summary;
    FString Duration;
    bool bIsExpanded = false;
    FString ErrorDocUrl;
};

typedef TSharedPtr<FLootLockerServerLogEntry> FLootLockerServerLogEntryPtr;

class SLootLockerServerLogViewerWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLootLockerServerLogViewerWidget) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
    virtual ~SLootLockerServerLogViewerWidget() override;
    void BindToPIEEvents();

    void AddLogEntry(const FString& Message, ELootLockerServerLogLevel Level);
    void AddHttpLogEntry(const FLootLockerServerHttpLogEntry& HttpEntry);
    void ClearLog(); // Add this for PIE clear support

private:
    TArray<FLootLockerServerLogEntryPtr> LogEntries;
    TArray<FLootLockerServerLogEntryPtr> FilteredEntries;
    TSharedPtr<SListView<FLootLockerServerLogEntryPtr>> LogListView;
    TSharedPtr<SSearchBox> SearchBox;
    FString SearchText;
    ELootLockerServerLogLevel MinLevel = ELootLockerServerLogLevel::Verbose;
    bool bClearOnPIE = false;
    void RefreshFilter();
    void RefreshFilter(const FLootLockerServerHttpLogEntry& Entry);
    void OnSearchTextChanged(const FText& InText);
    FReply OnClearLogClicked();
    TSharedRef<ITableRow> OnGenerateRow(FLootLockerServerLogEntryPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);
    void OnBeginPIE(bool);
};
