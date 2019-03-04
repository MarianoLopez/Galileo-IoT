const sleepInMs = 15000;

const Galileo = require('./galileo_gpio');
const temperatureSensor = new Galileo.TemperatureSensor(2);
const led = new Galileo.Led(4);

const rabbit_config = require("./rabbit_config");
var amqp = require('amqplib/callback_api');
amqp.connect('amqp://'+rabbit_config.credentials.user+':'+rabbit_config.credentials.password+'@'+rabbit_config.host+':'+rabbit_config.port, function(err, conn) {
  if(err){
  	console.error("AMQP",err.message);
  }else{
  	sender(conn);
  	receiver(conn);
  }
});

// ------------------ send temperature every %sleepInMs ------------------------------------------------------
function sender(conn){
	conn.createChannel(function(err, ch) {
	    if(err){
				console.error("AMQP",err);
		}else{
			ch.assertExchange(rabbit_config.exchange.name, rabbit_config.exchange.type, rabbit_config.exchange.options);
		    setInterval(function(){
		    	var msg = JSON.stringify({ temperature: temperatureSensor.getValue() });
		    	ch.publish(rabbit_config.exchange.name, rabbit_config.events.temperature, new Buffer(msg));
		    	console.log(" [x] Sent %s in %s", msg,rabbit_config.events.temperature);	
		    }, sleepInMs);
		}
	});
}

// ------------------ lister to rabbit_config.events.led ------------------------------------------------------
function receiver(conn){
	conn.createChannel(function(err,ch){
		ch.assertExchange(rabbit_config.exchange.name, rabbit_config.exchange.type, rabbit_config.exchange.options);
		ch.assertQueue(rabbit_config.queue.name,rabbit_config.queue.options,function(err,q){
			if(err){
				console.error("AMQP",err);
			}else{
				ch.bindQueue(q.queue,rabbit_config.exchange.name,rabbit_config.events.led);
				ch.consume(q.queue, function(msg){
					console.log("[X] receive %s:'%s'",msg.fields.routingKey,msg.content.toString());	
					var json = JSON.parse(msg.content.toString());
					led.setValue(json.state? 1: 0);
				},{noAck:true});
			}
		});
	});
}