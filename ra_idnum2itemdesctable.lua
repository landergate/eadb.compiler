tbl = {
}
main = function()
    for ItemID, DESC in pairs(tbl) do
        result, msg = AddItem(ItemID, DESC.unidentifiedDisplayName, DESC.unidentifiedResourceName, DESC.identifiedDisplayName, DESC.identifiedResourceName, DESC.slotCount, DESC.ClassNum)
        if not result == true then
            return false, msg
        end
        for k, v in pairs(DESC.unidentifiedDescriptionName) do
            result, msg = AddItemUnidentifiedDesc(ItemID, v)
            if not result == true then
                return false, msg
            end
        end
        for k, v in pairs(DESC.identifiedDescriptionName) do
            result, msg = AddItemIdentifiedDesc(ItemID, v)
            if not result == true then
                return false, msg
            end
        end
        k = DESC.unidentifiedResourceName
        v = DESC.identifiedDisplayName
    end
    return true, "good"
end
