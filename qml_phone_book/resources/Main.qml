
import QtQuick 2.5
import QtQuick.Controls 1.0

import it.mmcs.phonemodel 1.0

Rectangle {
    width: 360
    height: 360

    PhoneModel {
        id: phoneModel
    }

    TableView {
        id: view

        anchors.margins: 10
        anchors.fill: parent
        model: phoneModel
        clip: true

        TableViewColumn {
            width: 150
            title: "Name"
            role: "name"
        }

        TableViewColumn {
            width: 150
            title: "Phone"
            role: "phone"
        }

        itemDelegate: Item {
            Text {
                anchors.centerIn: parent
                renderType: Text.NativeRendering
                text: styleData.value
            }
        }
    }
}

