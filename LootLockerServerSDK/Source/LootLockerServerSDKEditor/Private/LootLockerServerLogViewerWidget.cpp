// Copyright (c) 2025 LootLocker
#include "LootLockerServerLogViewerWidget.h"
#include "Widgets/Input/SSearchBox.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SCheckBox.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "LootLockerServerLogger.h"
#include "Widgets/Input/SHyperlink.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/SBoxPanel.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

void SLootLockerServerLogViewerWidget::BindToPIEEvents()
{
#if WITH_EDITOR
    FEditorDelegates::BeginPIE.AddRaw(this, &SLootLockerServerLogViewerWidget::OnBeginPIE);
#endif
}

void SLootLockerServerLogViewerWidget::Construct(const FArguments& InArgs)
{
    FLootLockerServerLogger::OnHttpLogEntry.AddRaw(this, &SLootLockerServerLogViewerWidget::AddHttpLogEntry);
    // Add Clear on Play support
    BindToPIEEvents();
    ChildSlot
    [
        SNew(SVerticalBox)
        + SVerticalBox::Slot().AutoHeight().Padding(2)
        [
            SAssignNew(SearchBox, SSearchBox)
            .OnTextChanged(this, &SLootLockerServerLogViewerWidget::OnSearchTextChanged)
        ]
        + SVerticalBox::Slot().AutoHeight().Padding(2)
        [
            SNew(SHorizontalBox)
            + SHorizontalBox::Slot().AutoWidth().Padding(2)
            [
                SNew(SButton)
                .Text(FText::FromString("Clear Log"))
                .OnClicked(this, &SLootLockerServerLogViewerWidget::OnClearLogClicked)
            ]
        ]
        + SVerticalBox::Slot().FillHeight(1).Padding(2)
        [
            SAssignNew(LogListView, SListView<FLootLockerServerLogEntryPtr>)
            .ListItemsSource(&FilteredEntries)
            .OnGenerateRow(this, &SLootLockerServerLogViewerWidget::OnGenerateRow)
            .SelectionMode(ESelectionMode::Single)
        ]
    ];
    RefreshFilter();
}

void SLootLockerServerLogViewerWidget::AddLogEntry(const FString& Message, ELootLockerServerLogLevel Level)
{
    FLootLockerServerLogEntryPtr Entry = MakeShared<FLootLockerServerLogEntry>();
    Entry->Message = Message;
    Entry->Level = Level;
    Entry->Timestamp = FDateTime::Now();
    Entry->bIsRequestLog = false;
    Entry->Summary = Message;
    LogEntries.Add(Entry);
    RefreshFilter();
}

void SLootLockerServerLogViewerWidget::AddHttpLogEntry(const FLootLockerServerHttpLogEntry& HttpEntry)
{
    FLootLockerServerLogEntryPtr Entry = MakeShared<FLootLockerServerLogEntry>();
    Entry->bIsRequestLog = true;
    Entry->HttpMethod = HttpEntry.Method;
    Entry->RequestPath = HttpEntry.Path;
    Entry->StatusCode = HttpEntry.StatusCode;
    Entry->Duration = FString::Printf(TEXT("%.6f"), HttpEntry.Duration);
    Entry->Timestamp = HttpEntry.Timestamp;
    Entry->Level = HttpEntry.bSuccess ? ELootLockerServerLogLevel::Log : ELootLockerServerLogLevel::Error;
    Entry->Message = FString::Printf(TEXT("Request Data: %s\nResponse Data: %s\nRequest Headers: %s"),
        *HttpEntry.RequestData,
        *HttpEntry.ResponseData,
        *HttpEntry.RequestHeaders);
    Entry->ErrorDocUrl = HttpEntry.ErrorData.Doc_url;
    // Build summary
    if (!HttpEntry.bSuccess)
    {
        FString ErrorSummary;
        if (!HttpEntry.ErrorData.Code.IsEmpty() && !HttpEntry.ErrorData.Message.IsEmpty())
        {
            ErrorSummary = FString::Printf(TEXT("\nError Code: %s\nError Message: %s"), *HttpEntry.ErrorData.Code, *HttpEntry.ErrorData.Message);
        }
        else if (!HttpEntry.ErrorData.Message.IsEmpty())
        {
            ErrorSummary = FString::Printf(TEXT("\nError Message: %s"), *HttpEntry.ErrorData.Message);
        }
        else if (!HttpEntry.ErrorData.Code.IsEmpty())
        {
            ErrorSummary = FString::Printf(TEXT("\nError Code: %s"), *HttpEntry.ErrorData.Code);
        }
        else
        {
            ErrorSummary = TEXT("\nRequest failed");
        }
        Entry->Summary = FString::Printf(TEXT("%s %s  Status: %d%s"), *Entry->HttpMethod, *Entry->RequestPath, Entry->StatusCode, *ErrorSummary);
    }
    else
    {
        Entry->Summary = FString::Printf(TEXT("%s %s  Status: %d"), *Entry->HttpMethod, *Entry->RequestPath, Entry->StatusCode);
    }
    LogEntries.Add(Entry);
    RefreshFilter();
}

TSharedRef<ITableRow> SLootLockerServerLogViewerWidget::OnGenerateRow(FLootLockerServerLogEntryPtr InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
    if (InItem->bIsRequestLog)
    {
        FSlateColor SummaryColor = (InItem->StatusCode >= 200 && InItem->StatusCode < 300)
            ? FSlateColor(FLinearColor(0.2f, 0.8f, 0.2f))
            : FSlateColor(FLinearColor(0.9f, 0.2f, 0.2f));
        TWeakPtr<SListView<FLootLockerServerLogEntryPtr>> WeakListView = LogListView;
        if (!InItem->bIsExpanded) InItem->bIsExpanded = false;
        return SNew(STableRow<FLootLockerServerLogEntryPtr>, OwnerTable)
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot().AutoHeight()
                [
                    SNew(SExpandableArea)
                    .InitiallyCollapsed(!InItem->bIsExpanded)
                    .OnAreaExpansionChanged_Lambda([InItem, WeakListView](bool bExpanded)
                    {
                        InItem->bIsExpanded = bExpanded;
                        if (TSharedPtr<SListView<FLootLockerServerLogEntryPtr>> ListView = WeakListView.Pin())
                        {
                            ListView->RequestListRefresh();
                        }
                    })
                    .HeaderContent()
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                        [
                            SNew(SMultiLineEditableTextBox)
                            .Text(FText::FromString(InItem->Summary))
                            .IsReadOnly(true)
                            .SelectAllTextWhenFocused(false)
                            .AlwaysShowScrollbars(false)
                            .AutoWrapText(true)
                            .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                            .ForegroundColor(SummaryColor)
                        ]
                        + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(8,0,0,0)
                        [
                            InItem->ErrorDocUrl.IsEmpty() ? SNullWidget::NullWidget :
                            SNew(SButton)
                            .ButtonStyle(FCoreStyle::Get(), "NoBorder")
                            .ToolTipText(FText::FromString(InItem->ErrorDocUrl))
                            .OnClicked_Lambda([Url = InItem->ErrorDocUrl]() {
                                FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
                                return FReply::Handled();
                            })
                            [
                                SNew(SImage)
                                .Image(FCoreStyle::Get().GetBrush("Icons.Help"))
                                .ColorAndOpacity(FSlateColor(FLinearColor(0.2f,0.5f,1.0f,1.0f)))
                            ]
                        ]
                    ]
                    .BodyContent()
                    [
                        SNew(SBorder)
                        .BorderBackgroundColor(FLinearColor(1,0,0,0.2f))
                        [
                            SNew(SVerticalBox)
                            + SVerticalBox::Slot().AutoHeight()
                            [
                                SNew(STextBlock)
                                .Text(FText::FromString(FString::Printf(TEXT("Timestamp: %s"), *InItem->Timestamp.ToString())))
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
                                .ColorAndOpacity(FSlateColor(FLinearColor(0.7f,0.7f,0.7f)))
                            ]
                            + SVerticalBox::Slot().AutoHeight()
                            [
                                SNew(STextBlock)
                                .Text(FText::FromString(FString::Printf(TEXT("Duration: %s s"), *InItem->Duration)))
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
                                .ColorAndOpacity(FSlateColor(FLinearColor(0.7f,0.7f,0.7f)))
                            ]
                            + SVerticalBox::Slot().AutoHeight()
                            [
                                SNew(SMultiLineEditableTextBox)
                                .Text(FText::FromString(InItem->Message))
                                .IsReadOnly(true)
                                .SelectAllTextWhenFocused(false)
                                .AlwaysShowScrollbars(false)
                                .AutoWrapText(true)
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                            ]
                        ]
                    ]
                ]
            ];
    }
    FSlateColor SummaryColor;
    switch (InItem->Level)
    {
        case ELootLockerServerLogLevel::Error:
            SummaryColor = FSlateColor(FLinearColor(0.9f, 0.2f, 0.2f));
            break;
        case ELootLockerServerLogLevel::Warning:
            SummaryColor = FSlateColor(FLinearColor(1.0f, 0.7f, 0.2f));
            break;
        default:
            SummaryColor = FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f));
            break;
    }
    TWeakPtr<SListView<FLootLockerServerLogEntryPtr>> WeakListView = LogListView;
    if (!InItem->bIsExpanded) InItem->bIsExpanded = false;
    return SNew(STableRow<FLootLockerServerLogEntryPtr>, OwnerTable)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot().AutoHeight()
            [
                SNew(SExpandableArea)
                .InitiallyCollapsed(!InItem->bIsExpanded)
                .OnAreaExpansionChanged_Lambda([InItem, WeakListView](bool bExpanded)
                {
                    InItem->bIsExpanded = bExpanded;
                    if (TSharedPtr<SListView<FLootLockerServerLogEntryPtr>> ListView = WeakListView.Pin())
                    {
                        ListView->RequestListRefresh();
                    }
                })
                .HeaderContent()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Center)
                    [
                        SNew(SMultiLineEditableTextBox)
                        .Text(FText::FromString(InItem->Summary.IsEmpty() ? InItem->Message : InItem->Summary))
                        .IsReadOnly(true)
                        .SelectAllTextWhenFocused(false)
                        .AlwaysShowScrollbars(false)
                        .AutoWrapText(true)
                        .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                        .ForegroundColor(SummaryColor)
                    ]
                    + SHorizontalBox::Slot().AutoWidth().VAlign(VAlign_Top).Padding(8,0,0,0)
                    [
                        InItem->ErrorDocUrl.IsEmpty() ? SNullWidget::NullWidget :
                        SNew(SButton)
                        .ButtonStyle(FCoreStyle::Get(), "NoBorder")
                        .ToolTipText(FText::FromString(InItem->ErrorDocUrl))
                        .OnClicked_Lambda([Url = InItem->ErrorDocUrl]() {
                            FPlatformProcess::LaunchURL(*Url, nullptr, nullptr);
                            return FReply::Handled();
                        })
                        [
                            SNew(SImage)
                            .Image(FCoreStyle::Get().GetBrush("Icons.Help"))
                            .ColorAndOpacity(FSlateColor(FLinearColor(0.2f,0.5f,1.0f,1.0f)))
                        ]
                    ]
                ]
                .BodyContent()
                [
                    SNew(SBorder)
                    .BorderBackgroundColor(FLinearColor(0,0,0,0.2f))
                    [
                        SNew(SVerticalBox)
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(STextBlock)
                            .Text(FText::FromString(FString::Printf(TEXT("Timestamp: %s"), *InItem->Timestamp.ToString())))
                            .Font(FCoreStyle::GetDefaultFontStyle("Regular", 8))
                            .ColorAndOpacity(FSlateColor(FLinearColor(0.7f,0.7f,0.7f)))
                        ]
                        + SVerticalBox::Slot().AutoHeight()
                        [
                            SNew(SMultiLineEditableTextBox)
                            .Text(FText::FromString(InItem->Message))
                            .IsReadOnly(true)
                            .SelectAllTextWhenFocused(false)
                            .AlwaysShowScrollbars(false)
                            .AutoWrapText(true)
                            .Font(FCoreStyle::GetDefaultFontStyle("Regular", 10))
                        ]
                    ]
                ]
            ]
        ];
}

void SLootLockerServerLogViewerWidget::OnSearchTextChanged(const FText& InText)
{
    SearchText = InText.ToString();
    RefreshFilter();
}

void SLootLockerServerLogViewerWidget::RefreshFilter()
{
    FilteredEntries.Empty();
    for (const FLootLockerServerLogEntryPtr& Entry : LogEntries)
    {
        if (Entry->Level <= MinLevel && (SearchText.IsEmpty() || Entry->Message.Contains(SearchText)))
        {
            FilteredEntries.Add(Entry);
        }
    }
    if (LogListView.IsValid())
    {
        LogListView->RequestListRefresh();
    }
}

FReply SLootLockerServerLogViewerWidget::OnClearLogClicked()
{
    LogEntries.Empty();
    RefreshFilter();
    return FReply::Handled();
}

void SLootLockerServerLogViewerWidget::ClearLog()
{
    LogEntries.Empty();
    FilteredEntries.Empty();
    if (LogListView.IsValid())
    {
        LogListView->RequestListRefresh();
    }
}

void SLootLockerServerLogViewerWidget::OnBeginPIE(bool)
{
    if (bClearOnPIE)
    {
        ClearLog();
    }
}

SLootLockerServerLogViewerWidget::~SLootLockerServerLogViewerWidget()
{
    FLootLockerServerLogger::OnHttpLogEntry.RemoveAll(this);
#if WITH_EDITOR
    FEditorDelegates::BeginPIE.RemoveAll(this);
#endif
}
