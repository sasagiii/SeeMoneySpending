import QtQuick
import QtQml

ListModel {
    id: listModel
    Component.onCompleted: {
        var spendingHis = dataManager.moneySpentHistory()
        for (var i = 0; i < spendingHis.length; i++) {
            var splitStrings = spendingHis[i].split(";")
            var date = splitStrings[0]
            var amount = splitStrings[1]
            listModel.append({
                                 "amont": amount,
                                 "date": date
                             })
        }
    }
}
