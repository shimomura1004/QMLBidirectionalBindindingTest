import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480

    function dump(){
        for(var i=0; i < testcasemodel.count ; i++) {
            var row = listview.contentItem.children[i];
            var checkbox = row.children[0];
            var textinput = row.children[1];
            console.log("" + textinput.text + "|" + checkbox.checked + "|" + checkbox.checkedState);
        }
    }

    Column {
        Text {
            text: "check"
            MouseArea {
                anchors.fill: parent
                onClicked: testcasemodel.check()
            }
        }
        Text {
            text: "check in qml"
            MouseArea {
                anchors.fill: parent
                onClicked: dump()
            }
        }
        Text {
            text: "select all"
            MouseArea {
                anchors.fill: parent
                onClicked: testcasemodel.selectall()
            }
        }
        Text {
            text: "deselect all"
            MouseArea {
                anchors.fill: parent
                onClicked: testcasemodel.deselectall()
            }
        }
        Text {
            text: "reset title"
            MouseArea {
                anchors.fill: parent
                onClicked: testcasemodel.resettitle()
            }
        }
    }

    ListView {
        id: listview
        x: 100
        width: 200
        height: 100
        model: testcasemodel

        delegate: Row {
            CheckBox {
                id: checkbox
                text: model.name
            }

            Binding {
                target: checkbox
                property: "checked"
                value: model.checked
            }

            Binding {
                target: model
                property: "checked"
                value: checkbox.checked
            }
        }
    }
}
