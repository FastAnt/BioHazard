import QtQuick 2.7
import QtQuick.Window 2.2
import lux.study.GameEngine 1.0

Window {
    id : root
    visible: true
    width: 1
    height: 1


    Item
    {
        anchors.fill: parent
        GameEngine
        {
            id: game_engine
            width: 960
            height: 1100
            Component.onCompleted:
            {

                game_engine.initGame( Qt.application.arguments[1] ) ;
                loader.sourceComponent = src;
                game_engine.doTurn();

            }
        }
        Loader
        {
            id:loader
            objectName: "game_field"
            width: 960
            height: 1100
            Rectangle
            {
                anchors.fill: parent
                color: "white"
            }
        }
        Component
        {
            id: src
            Grid {
//                objectName: "game_field"
                id: game_field
                columns:  30
                rows: 30
                spacing: 2
                x: 0
                y: 0
                width: 960
                height: 1100
                Repeater
                {
                    model: 900
                    Rectangle
                    {
                        id:root
                        width:30
                        height:30
                        //color: "blue"
                        opacity:0.5
                        property int idx: root.Positioner.index
                        color: game_engine.get_cell_color(root.Positioner.index);
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked:
                            {
                                root.color = "red";
                            }
                        }
                        Text {
                            anchors.centerIn: parent
                            text: game_engine.get_cell_task_id(root.Positioner.index);
                        }
                    }
                }
            }
        }

    }

}
