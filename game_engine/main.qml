import QtQuick 2.9
import QtQuick.Window 2.2
import lux.study.GameEngine 1.0

Window {
    visible: true
    width: 960
    height: 960
    GameEngine
    {
        id: game_engine
    }
    Component.onCompleted:
    {
        game_engine.initGame( Qt.application.arguments[1] ) ;
        game_engine.doTurn();
    }
    Grid {
        columns:  30
        rows: 30
        spacing: 2
        id: grid
        x: 0
        y: 0
        width: 960
        height: 960
        Repeater
        {
            model: 900
            delegate :
                Rectangle
            {
                id:root
                width:30
                height:30
                color: "blue"
                opacity:0.5
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        root.color = "red";
                    }
                }
            }
        }

    }
}
