import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true

    maximumWidth: 1000
    maximumHeight: 740

    minimumWidth: 1000
    minimumHeight: 740

    width: 1000
    height: 740

    color: "#FAF8EF"
    opacity: 1

    title: qsTr("2048")

    Rectangle {

        id : background

        width: 600
        height : 600
        x : 100
        y : 70
        color : "#bbada0"
        radius: 10

        property var ha : [];
        property var gameover : 0;

        focus : true

        function dest(){

            for (var k=0;k<16;k++){
                ha[k].destroy();
            }

        }

        function refresh(){

            var M = vueGrille.tab;

            var c = 0;

            for (var i=0;i<4;i++){
                for (var j=0;j<4;j++){
                    var X;
                    var comp;
                    switch (M[i+4*j]) {
                       case 0:
                            comp = Qt.createComponent("Tile.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 2:
                            comp = Qt.createComponent("Deux.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 4:
                            comp = Qt.createComponent("Quatre.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 8:
                            comp = Qt.createComponent("Huit.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 16:
                            comp = Qt.createComponent("Seize.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 32:
                            comp = Qt.createComponent("TDeux.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 64:
                            comp = Qt.createComponent("SQuatre.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 128:
                            comp = Qt.createComponent("CVHuit.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 256:
                            comp = Qt.createComponent("DCCSix.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 512:
                            comp = Qt.createComponent("CCDouze.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 1024:
                            comp = Qt.createComponent("MVQuatre.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                       case 2048:
                            comp = Qt.createComponent("DMQHuit.qml");
                            ha[c] = comp.createObject(background, {"x": 20+145*i, "y": 20+145*j});
                            break;
                    }
                    c++;
                }
            }

            if (vueGrille.IsOver()){

                comp = Qt.createComponent("Over.qml");
                gameover = comp.createObject(background, {"x": 80, "y": 250});

            }

        }

        Keys.onPressed: {
          switch (event.key) {
            case Qt.Key_Up:
              vueGrille.sauvegarde();
              vueGrille.SwipeHaut();
              dest();
              refresh();
              text_score.text = "Score\n" + vueGrille.get_score();
              break;
            case Qt.Key_Down:
              vueGrille.sauvegarde();
              vueGrille.SwipeBas();
              dest();
              refresh();
              text_score.text = "Score\n" + vueGrille.get_score();
              break;
            case Qt.Key_Left:
              vueGrille.sauvegarde();
              vueGrille.SwipeGauche();
              dest();
              refresh();
              text_score.text = "Score\n" + vueGrille.get_score();
              break;
            case Qt.Key_Right:
              vueGrille.sauvegarde();
              vueGrille.SwipeDroite();
              dest();
              refresh();
              text_score.text = "Score\n" + vueGrille.get_score();
              break;
          }
        }

        Component.onCompleted : {

            refresh();

        }

    }

    Rectangle {

        id : start

        x : 750
        y : 73

        width : 130
        height : 40

        radius : 3

        color : "#8F7A66"

        MouseArea {
                anchors.fill: parent
                onClicked: {

                    background.gameover.text = "";
                    background.gameover = 0;

                    vueGrille.restart();
                    background.dest();
                    background.refresh();
                }
        }

        Text {

            text : "New Game"

            font.pixelSize: 20
            font.family: "Clear Sans"
            font.bold : true

            color : "#F9F6F2"

            anchors.centerIn: parent

        }
    }

    Rectangle {

        id : undo

        x : 750
        y : 130

        width : 130
        height : 40

        radius : 3

        color : "#8F7A66"

        MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (~vueGrille.get_Undone()){
                        vueGrille.load_sauvegarde();
                        background.dest();
                        background.refresh();
                    }
                }
        }

        Text {

            text : "Undo"

            font.pixelSize: 20
            font.family: "Clear Sans"
            font.bold : true

            color : "#F9F6F2"

            anchors.centerIn: parent

        }
    }


    Rectangle {

        id : score

        x : 750
        y : 187

        width : 130
        height : 60

        radius : 3

        color : "#BBADA0"

        Text {

            id : text_score

            text : "Score\n" + "0";

            font.pixelSize: 20
            font.family: "Clear Sans"
            font.bold : true

            color : "#F9F6F2"

            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
