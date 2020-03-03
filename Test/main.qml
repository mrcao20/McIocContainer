import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property var ws: null
    
    function aa() {
        var ff = $.a()
        console.log(ff);
//        var jo = {
//            c: {}
//        };
//        var o = $.b({
//            c: "d"
//        });
//        console.log(o["a"]);
//        console.log(o);
//        $.c(function(){
//            console.log("ccccccccc");
//        });
    }
    
    Text {
        id: name
        text: qsTr("text")
    }
    Button {
        onClicked: {
            aa();
        }
    }
    
    ListView {
        id: listView
        anchors.fill: parent
        delegate: Rectangle {
            color: "red"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            height: 20
            Text {
                color: "green"
                text: songName
            }
        }
        model: ListModel {
            ListElement {
                songName: "aaaaaa"
            }
        }
    }

    Component.onCompleted: {
        var obj = {
            str: "str1",
            h: {
                text: "text1"
            }
        };
        var data = {
            onOpen: function(){
                console.log("aaaaaaaaa");
                ws.send("bbbbbbbb");
            },
            isOpenSync: true,
            onMessage: function(msg){
                console.log(msg);
            },
            isMessageSync: true
        };
        ws = $.qs("qmlSocketTest", data);
//        $.get("referenceBean.getModel").syncThen(function(result){
//            console.log(result);
//            listView.model = result;
//        });
//        $.get("referenceBean.getModels").syncThen(function(result){
//            console.log(result);
//            for(var i in result) {
//                console.log(i, result[i]);
//            }

////            var l = result.length;
////            console.log(l);
////            for(i = 0; i < l; ++i) {
////                console.log(result[i]);
////            }
//            listView.model = result["0"];
//        });        
//        $.get("referenceBean.b").then(function(result){
//            console.log(result, result.c);
//        });
//        $.post("referenceBean.aaa", obj).then(function(result){
//            console.log("pppppppp");
//            console.log(result);
//        });
//        $.post = function() {
//            console.log("ggggggg");
//        }
//        $.post();

//        $.get("referenceBean.o").then(function(result) {
//            console.log(result, result.text);
//        });
    }
}
