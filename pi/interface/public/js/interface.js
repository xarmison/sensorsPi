// Funcção para controlar o lamp
$(document).ready(function() {

    // Recarrega dados dos sensores
    refreshSensors();
    setInterval(refreshSensors, 5000);

});
    
function refreshSensors() {

    $.get('/sensor_module/temperature', function(json_data) {
        
    $("#temperature").text('Temperature: ' + json_data.temperature + ' C');

    $.get('/sensor_module/humidity', function(json_data) {
        $("#humidity").text('Humidity: ' + json_data.humidity + ' %');
    });
    });

}