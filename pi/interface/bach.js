//Imports
const cons = require('consolidate');
const express = require('express');
const app = express();

// Engine de vizualização(View Engine) HTML
app.engine('html', cons.swig)
app.set('views', 'views/');
app.set('view engine', 'html');

//Seta a pasta public
app.use('/static', express.static(__dirname + '/public'));

// node-aREST
//const rest = require("arest")(app);

// Adiciona o esp 
//rest.addDevice('http', '192.168.2.6');

// Rotas da Interface 
app.get('/', function (req, res) {
    res.render('index');
});

// Servidor 
const server = app.listen(3000, () => {
    console.log(`SensorsPI - Porta: ${server.address().port}`);
});