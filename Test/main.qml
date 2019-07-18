import QtQuick 2.5
import QtQuick.Window 2.0
import A 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    Text {
        id: name
        text: qsTr("text")
    }
    A{
        id: a
    }
    Component.onCompleted: {
        name.text = a.a();
    }
}
