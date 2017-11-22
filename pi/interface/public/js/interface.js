// Funcção para controlar o lamp
$(document).ready(() => {

    // Refresh sensor data
    refreshSensors();
    setInterval(refreshSensors, 1000);
    setInterval(removeAllData, 60000);

});

//Adiciona novos dados ao gráfico com o horario atual como rotulo
function addData(chart, data) {
    let time = new Date();
    chart.data.labels.push(time.getHours() + ':' + time.getMinutes() + ':' + time.getSeconds());
    chart.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    chart.update();
}

//Limpa os dados de um gráfico
function removeData(chart) {
    chart.data.labels = [];
    chart.data.datasets.forEach((dataset) => {
        dataset.data = [];
    });
    chart.update();
}
//limpa os dados de todos os gráfico
function removeAllData(){
    removeData(tempGraph);
    removeData(umiGraph);
    removeData(ldrGraph);
}



function refreshSensors() {
    /*
    $.get('http://192.168.2.6/sensors/temperature', (json_data) => {
        $("#temperatura").text(json_data.temperature + ' °C');
        addData(tempGraph, json_data.temperature);
    });
            
    $.get('http://192.168.2.6/sensors/humidity', function (json_data) {
        $("#umidade_ar").text(json_data.humidity + ' %');
        addData(umiGraph, json_data.humidity);
    });

    $.get('http://192.168.2.6/sensors/ldr', function (json_data) {
        $("#ldr").text(json_data.ldr);
        addData(ldrGraph, json_data.ldr);
    });

    $.get('http://192.168.2.6/sensors/distance', function (json_data) {
        $("#distance").text(json_data.distance + ' cm');
    });
    */
    $.get('http://192.168.2.6/rfid', (json_data) => {
        $("#rfid_log").text("ID do cartão: " + json_data.uid);
        $("#rfid_log").text("\n" + json_data.acess);
    });
    
}