//Imports
const express = require('express');

const app = express();

//Engine de Vizualização (View Engine)
app.set('views', './views');
app.set('view engine', 'pug');

//Seta a pasta public
app.use(express.static(__dirname + '/public'));

// node-aREST
const rest = require("arest")(app);
// Adiciona o esp 
//rest.addDevice('http','192.168.2.12');

// Rotas da Interface 
app.get('/', function(req, res){
    res.render('interface');
});

// Servidor 
const server = app.listen(3000, () => {
    console.log(`SensorsPI - Porta: ${server.address().port}`);
});