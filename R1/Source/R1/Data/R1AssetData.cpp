


#include "Data/R1AssetData.h"

#include "UObject/ObjectSaveContext.h"

void UR1AssetData::PreSave(FObjectPreSaveContext ObjectSaveContext)
{	// PDA 저장하는 순간 호출
	Super::PreSave(ObjectSaveContext);

	AssetNameToPath.Empty();	// clear 비우는 함수
	AssetLabelToSet.Empty();

	AssetGroupNameToSet.KeySort([](const FName& A, const FName& B)
		{
			return (A.Compare(B) < 0);
		});

	for (const auto& Pair : AssetGroupNameToSet)
	{
		const FAssetSet& AssetSet = Pair.Value;
		for (FAssetEntry AssetEntry : AssetSet.AssetEntries)
		{
			FSoftObjectPath& AssetPath = AssetEntry.AssetPath;
			/*const FString& AssetName = AssetPath.GetAssetName();
			if (AssetName.StartsWith(TEXT("BP_")) || AssetName.StartsWith(TEXT("B_")) || AssetName.StartsWith(TEXT("WBP_")) ||
				AssetName.StartsWith(TEXT("GE_")) || AssetName.StartsWith(TEXT("GA_")) || AssetName.StartsWith(TEXT("ABP_")))
			{
				FString AssetPathString = AssetPath.GetAssetPathString();
				AssetPathString.Append(TEXT("_C"));
				AssetPath = FSoftObjectPath(AssetPathString);
			}*/

			AssetNameToPath.Emplace(AssetEntry.AssetName, AssetEntry.AssetPath);
			for (const FName& Label : AssetEntry.AssetLabels)	// 라벨 찾아서 빠르게 탐색할 수 있음
			{
				AssetLabelToSet.FindOrAdd(Label).AssetEntries.Emplace(AssetEntry);
			}
		}
	}
}


// 캐싱된 거 긁어오기
FSoftObjectPath UR1AssetData::GetAssetPathByName(const FName& AssetName)
{
	FSoftObjectPath* AssetPath = AssetNameToPath.Find(AssetName);
	ensureAlwaysMsgf(AssetPath, TEXT("Can't find Asset Path from Asset Name[%s]."), *AssetName.ToString());
	return *AssetPath;
}

const FAssetSet& UR1AssetData::GetAssetSetByLabel(const FName& Label)
{
	const FAssetSet* AssetSet = AssetLabelToSet.Find(Label);
	ensureAlwaysMsgf(AssetSet, TEXT("Can't find Asset Path from Asset Name[%s]."), *Label.ToString());
	return *AssetSet;
}
