const Eureka = require('eureka-js-client').Eureka;
const server = require('./server_config.js');
const serviceName = "galileo-service";
const eurekaServerAddress = "192.168.0.23";

const client = new Eureka({
  // application instance information
  instance: {
    app: serviceName,
    hostName: server.ip+':'+serviceName+':'+server.port,
    ipAddr: server.ip,
    statusPageUrl: 'http://'+server.ip+':'+server.port,
    port: {
      '$': server.port,
      '@enabled': 'true',
    },
    vipAddress: serviceName,
    dataCenterInfo: {
      '@class': 'com.netflix.appinfo.InstanceInfo$DefaultDataCenterInfo',
      name: 'MyOwn',
    },
    registerWithEureka: true,
    fetchRegistry: true
  },
  eureka: {
    // eureka server host / port
    host: eurekaServerAddress,
    port: 8761,
    servicePath: '/eureka/apps/',
    preferIpAddress:true
  },
});
client.logger.level('debug');
client.start(function(error){
	console.log(error || 'Eureka registration complete');
});

process.on('SIGINT', function() {
  console.log("stop....");
  client.stop();
  process.exit();
});


exports.client = client;