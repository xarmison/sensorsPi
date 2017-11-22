//Gráfricos
let tempGraph, umiGraph, ldrGraph;

$(document).ready(() => {
    //Dados
    let temeperaturas, umidades, ldr = [];

    //Gŕafico da temperatura
    const temp_ctx = document.getElementById("tempGraph").getContext('2d');

    tempGraph = new Chart(temp_ctx, {
        type: 'line',
        data: {
            datasets: [{
                label: "Temperatura",
                data: temeperaturas,
                borderWidth: 3,
                borderColor: 'rgba(15, 58, 198, 0.85)',
                backgroundColor: 'transparent'
            }]
        },
        options: {
            title: {
                display: true,
                fontSize: 20,
                text: "Temperaturas no DHT11"
            },
            labels: {
                fontStyle: "bold"
            }
        }
    });

    //Gŕafico da umidade
    const umi_ctx = document.getElementById("umiGraph").getContext('2d');

    umiGraph = new Chart(umi_ctx, {
        type: 'line',
        data: {
            datasets: [{
                label: "Umidade",
                data: umidades,
                borderWidth: 3,
                borderColor: 'rgba(15, 198, 121, 0.85)',
                backgroundColor: 'transparent'
            }]
        },
        options: {
            title: {
                display: true,
                fontSize: 20,
                text: "Umidade no DHT11"
            },
            labels: {
                fontStyle: "bold"
            }
        }
    });

    //Gráfico do LDR
    const ldr_ctx = document.getElementById("ldrGraph").getContext('2d');

    ldrGraph = new Chart(ldr_ctx, {
        type: 'line',
        data: {
            datasets: [{
                label: "Luminosidade",
                data: umidades,
                borderWidth: 3,
                borderColor: 'rgba(198, 100, 15, 0.85)',
                backgroundColor: 'transparent'
            }]
        },
        options: {
            title: {
                display: true,
                fontSize: 20,
                text: "Luminosidade no LDR"
            },
            labels: {
                fontStyle: "bold"
            }
        }        
    });

});
