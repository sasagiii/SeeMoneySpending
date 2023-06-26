import QtQuick
import QtQuick.Controls

ListModel {
    id: listModel

    Component.onCompleted: {
        var spendingHis = dataManager.moneySpentHistory()
        for (var i = 0; i < spendingHis.length; i++)
            addElement(spendingHis[i])
    }

    function addElement(dateAndAmount) {
        var splitStrings = dateAndAmount.split(";")
        var date = splitStrings[0]
        var amount = splitStrings[1]
        insert(0, {
                   "amont": amount,
                   "date": date
               })
    }
    function removeElement(index) {
        remove(index)
    }
}
