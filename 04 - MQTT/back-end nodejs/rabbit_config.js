exports.host = "192.168.1.30"
exports.port = 5672
exports.events={
	temperature:"TEMPERATURE",
	led:"LED"
};

exports.exchange = {
	name: "galileo",
	type: "direct",
	options: {
		durable: true
	}
};

exports.credentials = {
	user:"rabbitmq",
	password:"rabbitmq"
};


exports.queue = {
	name: "galileo",
	options:{
		durable:true,
		exclusive:false
	}
};