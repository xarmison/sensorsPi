// Funcção para controlar o lamp
$(document).ready(function() {

    // Refresh sensor data
    refreshSensors();
    setInterval(refreshSensors, 5000);

});
    
function refreshSensors() {

    $.get('/sensor_module/temperature', function(json_data) {
    $("#temperatura").text(json_data.temperature + ' *C');

    $.get('/sensor_module/humidity', function(json_data) {
        $("#umidade_ar").text(json_data.humidity + ' %');
    });
    });

}
