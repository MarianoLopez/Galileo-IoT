const server = require('./server_config');
const Galileo = require('./galileo_gpio');
const client = require('./eureka_config');
// ------------------------- init ---------------------------------------------
var app = server.app;
const temperatureSensor = new Galileo.TemperatureSensor(2);
const led = new Galileo.Led(4);
// ------------------ API ------------------------------------------------------
app.get('/temperature', function (req, res) {
  res.status(200);
  res.json({ temperature: temperatureSensor.getValue() });
});

app.get('/led/:state', function (req, res) {
   led.setValue(req.params.state);
   res.status(200);
   res.end("ok");     
});

app.get('/', function (req, res) {
  var msg = 'Hello from NodeJS';
  res.status(200);
  res.end(msg);
});